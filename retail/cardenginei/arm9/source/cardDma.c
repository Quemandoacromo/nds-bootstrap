/*
    NitroHax -- Cheat tool for the Nintendo DS
    Copyright (C) 2008  Michael "Chishm" Chisholm

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include <nds/ndstypes.h>
#include <nds/arm9/exceptions.h>
#include <nds/arm9/cache.h>
#include <nds/system.h>
#include <nds/dma.h>
#include <nds/interrupts.h>
#include <nds/ipc.h>
#include <nds/timers.h>
#include <nds/fifomessages.h>
#include <nds/memory.h> // tNDSHeader
#include "module_params.h"
#include "ndma.h"
#include "tonccpy.h"
#include "hex.h"
#include "igm_text.h"
#include "nds_header.h"
#include "cardengine.h"
#include "locations.h"
#include "cardengine_header_arm9.h"
#include "unpatched_funcs.h"

#define EXCEPTION_VECTOR_SDK1	(*(VoidFn *)(0x27FFD9C))

#define saveOnFlashcard BIT(0)
#define extendedMemory BIT(1)
#define ROMinRAM BIT(2)
#define dsiMode BIT(3)
#define enableExceptionHandler BIT(4)
#define isSdk5 BIT(5)
#define overlaysInRam BIT(6)
#define cacheFlushFlag BIT(7)
#define cardReadFix BIT(8)
#define cacheDisabled BIT(9)
#define slowSoftReset BIT(10)
#define dsiBios BIT(11)

//#ifdef DLDI
#include "my_fat.h"
#include "card.h"
//#endif

//extern void user_exception(void);

extern cardengineArm9* volatile ce9;

extern vu32* volatile sharedAddr;

extern tNDSHeader* ndsHeader;
extern aFile* romFile;
extern aFile* savFile;

extern u32* cacheDescriptor;
extern u32* cacheCounter;
extern u32 accessCounter;

bool isDma = false;

void endCardReadDma() {
    if(ce9->patches->cardEndReadDmaRef) {
        volatile void (*cardEndReadDmaRef)() = ce9->patches->cardEndReadDmaRef;
        (*cardEndReadDmaRef)();
    } else if(ce9->thumbPatches->cardEndReadDmaRef) {
        callEndReadDmaThumb();
    }    
}

#ifndef DLDI
//#ifdef ASYNCPF
static u32 asyncSector = 0;
//static u32 asyncQueue[5];
//static int aQHead = 0;
//static int aQTail = 0;
//static int aQSize = 0;
//#endif

bool dmaReadOnArm7 = false;
bool dmaReadOnArm9 = false;

extern int allocateCacheSlot(void);
extern int getSlotForSector(u32 sector);
extern vu8* getCacheAddress(int slot);
extern void updateDescriptor(int slot, u32 sector);

/*#ifdef ASYNCPF
void addToAsyncQueue(sector) {
	asyncQueue[aQHead] = sector;
	aQHead++;
	aQSize++;
	if(aQHead>4) {
		aQHead=0;
	}
	if(aQSize>5) {
		aQSize=5;
		aQTail++;
		if(aQTail>4) aQTail=0;
	}
}

u32 popFromAsyncQueueHead() {	
	if(aQSize>0) {
	
		aQHead--;
		if(aQHead == -1) aQHead = 4;
		aQSize--;
		
		return asyncQueue[aQHead];
	} else return 0;
}
#endif*/

static void waitForArm7(bool ipc) {
	extern void sleepMs(int ms);

	if (!ipc) {
		IPC_SendSync(0x4);
	}
	while (sharedAddr[3] != (vu32)0) {
		if (ipc) {
			IPC_SendSync(0x4);
			sleepMs(1);
		}
	}
}

//#ifdef ASYNCPF
void triggerAsyncPrefetch(sector) {	
	if(asyncSector == 0) {
		int slot = getSlotForSector(sector);
		// read max 32k via the WRAM cache
		// do it only if there is no async command ongoing
		if(slot==-1) {
			//addToAsyncQueue(sector);
			// send a command to the arm7 to fill the main RAM cache
			u32 commandRead = (isDma ? 0x020FF80A : 0x020FF808);

			slot = allocateCacheSlot();

			vu8* buffer = getCacheAddress(slot);

			cacheDescriptor[slot] = sector;
			cacheCounter[slot] = 0x0FFFFFFF; // async marker
			asyncSector = sector;		

			// write the command
			sharedAddr[0] = buffer;
			sharedAddr[1] = ce9->cacheBlockSize;
			sharedAddr[2] = sector;
			sharedAddr[3] = commandRead;

			IPC_SendSync(0x4);

			// do it asynchronously
			/*waitForArm7();*/
		}	
	}	
}

void processAsyncCommand() {
	if(asyncSector != 0) {
		int slot = getSlotForSector(asyncSector);
		if(slot!=-1 && cacheCounter[slot] == 0x0FFFFFFF) {
			// get back the data from arm7
			if(sharedAddr[3] == (vu32)0) {
				updateDescriptor(slot, asyncSector);
				asyncSector = 0;
			}			
		}	
	}
}

void getAsyncSector() {
	if(asyncSector != 0) {
		int slot = getSlotForSector(asyncSector);
		if(slot!=-1 && cacheCounter[slot] == 0x0FFFFFFF) {
			// get back the data from arm7
			waitForArm7(true);

			updateDescriptor(slot, asyncSector);
			asyncSector = 0;
		}	
	}	
}
//#endif

static inline bool checkArm7(void) {
    IPC_SendSync(0x4);
	return (sharedAddr[3] == (vu32)0);
}

extern bool IPC_SYNC_hooked;
extern void hookIPC_SYNC(void);
extern void enableIPC_SYNC(void);

static int currentLen=0;

void continueCardReadDmaArm9() {
    if(dmaReadOnArm9) {
        vu32* volatile cardStruct = ce9->cardStruct0;
        u32	dma = cardStruct[3]; // dma channel

        dmaReadOnArm9 = false;

		u32 commandRead=0x026FFB0A;

        u32 src = cardStruct[0];
        u8* dst = (u8*)(cardStruct[1]);
        u32 len = cardStruct[2];

        // Update cardi common
  		cardStruct[0] = src + currentLen;
  		cardStruct[1] = (vu32)(dst + currentLen);
  		cardStruct[2] = len - currentLen;

        src = cardStruct[0];
        dst = (u8*)(cardStruct[1]);
        len = cardStruct[2]; 

        u32 sector = (src/ce9->cacheBlockSize)*ce9->cacheBlockSize;

		#ifdef ASYNCPF
		processAsyncCommand();
		#endif

        if (len > 0) {
			accessCounter++;  

            // Read via the main RAM cache
        	int slot = getSlotForSector(sector);
        	vu8* buffer = getCacheAddress(slot);
			#ifdef ASYNCPF
			u32 nextSector = sector+ce9->cacheBlockSize;
			#endif
        	// Read max CACHE_READ_SIZE via the main RAM cache
        	if (slot == -1) {
				#ifdef ASYNCPF
				getAsyncSector();
				#endif

        		// Send a command to the ARM7 to fill the RAM cache
        		slot = allocateCacheSlot();

        		buffer = getCacheAddress(slot);

				fileRead((char*)buffer, *romFile, sector, ce9->cacheBlockSize, 0);

                //dmaReadOnArm7 = true;

                //updateDescriptor(slot, sector);	
                //return;

        	}
			#ifdef ASYNCPF
			if(cacheCounter[slot] == 0x0FFFFFFF) {
				// prefetch successfull
				getAsyncSector();

				triggerAsyncPrefetch(nextSector);
			} else {
				int i;
				for(i=0; i<5; i++) {
					if(asyncQueue[i]==sector) {
						// prefetch successfull
						triggerAsyncPrefetch(nextSector);
						break;
					}
				}
			}
			#endif
        	updateDescriptor(slot, sector);	

        	u32 len2 = len;
        	if ((src - sector) + len2 > ce9->cacheBlockSize) {
        		len2 = sector - src + ce9->cacheBlockSize;
        	}

        	if (len2 > 512) {
        		len2 -= src % 4;
        		len2 -= len2 % 32;
        	}

            currentLen = len2;

			// Copy via dma
			// Write the command
			sharedAddr[0] = (vu32)dst;
			sharedAddr[1] = len2;
			sharedAddr[2] = (vu32)buffer+(src-sector);
			sharedAddr[3] = commandRead;

			if (dst >= 0x03000000) {
				ndmaCopyWordsAsynch(0, (u8*)buffer+(src-sector), dst, len2);
			}

            dmaReadOnArm9 = true;
			IPC_SendSync(0x4);
        } else {
          //disableIrqMask(IRQ_DMA0 << dma);
          //resetRequestIrqMask(IRQ_DMA0 << dma);
          //disableDMA(dma);
		  isDma = false;
          endCardReadDma();
		}
    }
}

void continueCardReadDmaArm7() {
    if(dmaReadOnArm7) {
        if(!checkArm7()) return;

        dmaReadOnArm7 = false;

        /*vu32* volatile cardStruct = ce9->cardStruct0;

        u32 src = cardStruct[0];
        u8* dst = (u8*)(cardStruct[1]);
        u32 len = cardStruct[2];
        u32	dma = cardStruct[3]; // dma channel

		if (len > ce9->cacheBlockSize && (u32)dst < 0x02700000 && (u32)dst > 0x02000000) {*/
			endCardReadDma();
		/*} else {
			u32 sector = (src/ce9->cacheBlockSize)*ce9->cacheBlockSize;

			u32 len2 = len;
			if ((src - sector) + len2 > ce9->cacheBlockSize) {
				len2 = sector - src + ce9->cacheBlockSize;
			}

			if (len2 > 512) {
				len2 -= src % 4;
				len2 -= len2 % 32;
			}

			int slot = getSlotForSector(sector);
			vu8* buffer = getCacheAddress(slot);

			// TODO Copy via dma
			ndmaCopyWordsAsynch(0, (u8*)buffer+(src-sector), dst, len2);
			dmaReadOnArm9 = true;
			currentLen= len2;

			IPC_SendSync(0x3);
		}*/
	}
}

void cardSetDma(void) {
	isDma = true;

	vu32* volatile cardStruct = ce9->cardStruct0;

    disableIrqMask(IRQ_CARD);
    disableIrqMask(IRQ_CARD_LINE);

	enableIPC_SYNC();

	u32 src = cardStruct[0];
	u8* dst = (u8*)(cardStruct[1]);
	u32 len = cardStruct[2];
    u32 dma = cardStruct[3]; // dma channel     

	u32 commandRead=0x025FFB0A;
	u32 sector = (src/ce9->cacheBlockSize)*ce9->cacheBlockSize;
	u32 page = (src / 512) * 512;

	accessCounter++;  

	//#ifdef ASYNCPF
	processAsyncCommand();
	//#endif

	if ((ce9->valueBits & cacheDisabled) /*|| (len > ce9->cacheBlockSize && (u32)dst < 0x03000000 && (u32)dst >= 0x02000000)*/) {
		// Write the command
		sharedAddr[0] = (vu32)dst;
		sharedAddr[1] = len;
		sharedAddr[2] = src;
		sharedAddr[3] = commandRead;

		dmaReadOnArm7 = true;
	} else {
		// Read via the main RAM cache
		int slot = getSlotForSector(sector);
		vu8* buffer = getCacheAddress(slot);
		#ifdef ASYNCPF
		u32 nextSector = sector+ce9->cacheBlockSize;
		#endif
		getAsyncSector();
		// Read max CACHE_READ_SIZE via the main RAM cache
		if (slot == -1) {    
			#ifdef ASYNCPF
			getAsyncSector();
			#endif

			// Send a command to the ARM7 to fill the RAM cache
			slot = allocateCacheSlot();

			buffer = getCacheAddress(slot);

			fileRead((char*)buffer, *romFile, sector, ce9->cacheBlockSize, 0);

			//dmaReadOnArm7 = true;

			//updateDescriptor(slot, sector);
		} 
		#ifdef ASYNCPF
		if(cacheCounter[slot] == 0x0FFFFFFF) {
			// prefetch successfull
			getAsyncSector();

			triggerAsyncPrefetch(nextSector);
		} else {
			int i;
			for(i=0; i<5; i++) {
				if(asyncQueue[i]==sector) {
					// prefetch successfull
					triggerAsyncPrefetch(nextSector);
					break;
				}
			}
		}
		#endif
		updateDescriptor(slot, sector);	

		u32 len2 = len;
		if ((src - sector) + len2 > ce9->cacheBlockSize) {
			len2 = sector - src + ce9->cacheBlockSize;
		}

		if (len2 > 512) {
			len2 -= src % 4;
			len2 -= len2 % 32;
		}

		currentLen = len2;

		// Copy via dma
		dmaReadOnArm9 = true;

		// Write the command
		sharedAddr[0] = (vu32)dst;
		sharedAddr[1] = len2;
		sharedAddr[2] = (vu32)buffer+(src-sector);
		sharedAddr[3] = 0x026FFB0A;

		if (dst >= 0x03000000) {
			ndmaCopyWordsAsynch(0, (u8*)buffer+(src-sector), dst, len2);
		}
	}
	IPC_SendSync(0x4);
}
#else
void cardSetDma(void) {
	cardRead(NULL);
	endCardReadDma();
}
#endif

extern bool isNotTcm(u32 address, u32 len);

u32 cardReadDma() {
	vu32* volatile cardStruct = ce9->cardStruct0;
    
	u32 src = cardStruct[0];
	u8* dst = (u8*)(cardStruct[1]);
	u32 len = cardStruct[2];
    u32 dma = cardStruct[3]; // dma channel

    if(dma >= 0 
        && dma <= 3 
        //&& func != NULL
        && len > 0
        && !(((int)dst) & 3)
        && isNotTcm(dst, len)
        // check 512 bytes page alignement 
        && !(((int)len) & 511)
        && !(((int)src) & 511)
	) {
		isDma = true;
		cacheFlush();
        if(ce9->patches->cardEndReadDmaRef || ce9->thumbPatches->cardEndReadDmaRef) {
			// new dma method
			cardSetDma();
            return true;
		} /*else {
			dma=4;
            clearIcache();
		}*/
    } /*else {
        dma=4;
        clearIcache();
    }*/

    return false;
}
