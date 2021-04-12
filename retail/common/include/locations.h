#ifndef LOCATIONS_H
#define LOCATIONS_H

#define TARGETBUFFER9I 0x2800000
#define TARGETBUFFER7I 0x2B80000

#define EXCEPTION_STACK_LOCATION 0x23EFFFC

#define ROM_FILE_LOCATION         0x37D5000
#define ROM_FILE_LOCATION_ALT     0x3015000
#define ROM_FILE_LOCATION_MAINMEM 0x277FF80
#define ROM_FILE_LOCATION_SDK5    0x2F7FF80
#define SAV_FILE_LOCATION         (ROM_FILE_LOCATION + 32) //+ sizeof(aFile)
#define SAV_FILE_LOCATION_ALT     (ROM_FILE_LOCATION_ALT + 32) //+ sizeof(aFile)
#define SAV_FILE_LOCATION_MAINMEM (ROM_FILE_LOCATION_MAINMEM + 32) //+ sizeof(aFile)
#define SAV_FILE_LOCATION_SDK5    (ROM_FILE_LOCATION_SDK5 + 32) //+ sizeof(aFile)
#define GBA_FILE_LOCATION         (ROM_FILE_LOCATION + 64) //+ sizeof(aFile)
#define GBA_FILE_LOCATION_ALT     (ROM_FILE_LOCATION_ALT + 64) //+ sizeof(aFile)
#define GBA_FILE_LOCATION_MAINMEM (ROM_FILE_LOCATION_MAINMEM + 64) //+ sizeof(aFile)
#define GBA_FILE_LOCATION_SDK5    (ROM_FILE_LOCATION_SDK5 + 64) //+ sizeof(aFile)
#define GBA_SAV_FILE_LOCATION         (ROM_FILE_LOCATION + 96) //+ sizeof(aFile)
#define GBA_SAV_FILE_LOCATION_ALT     (ROM_FILE_LOCATION_ALT + 96) //+ sizeof(aFile)
#define GBA_SAV_FILE_LOCATION_MAINMEM (ROM_FILE_LOCATION_MAINMEM + 96) //+ sizeof(aFile)
#define GBA_SAV_FILE_LOCATION_SDK5    (ROM_FILE_LOCATION_SDK5 + 96) //+ sizeof(aFile)

#define LOAD_CRT0_LOCATION 0x06860000 // LCDC_BANK_D

#define IMAGES_LOCATION    0x02340000

#define CARDENGINE_ARM9_LOCATION_BUFFERED1 0x023E0000
#define CARDENGINE_ARM9_LOCATION_BUFFERED2 0x023E5000

#define CARDENGINE_ARM7_LOCATION             0x023FE800
#define CARDENGINE_ARM9_LOCATION_DLDI_8KB    0x023DC000
#define CARDENGINE_ARM9_LOCATION_DLDI_12KB   0x023DB000
#define CARDENGINE_ARM9_LOCATION_DLDI_EXTMEM 0x023E0000

#define DONOR_ROM_ARM7_LOCATION                      0x02680000
#define DONOR_ROM_ARM7_SIZE_LOCATION                 0x026B0000
#define CHEAT_ENGINE_BUFFERED_LOCATION	             0x026E0000
#define INGAME_MENU_LOCATION                         0x026F8000

#define BLOWFISH_LOCATION_B4DS                       0x023ECE00
#define BLOWFISH_LOCATION                            0x027B4C00
//#define DSI_BLOWFISH_LOCATION                        0x027EA800
#define ARM7_FIX_BUFFERED_LOCATION                   0x027B5E00
#define CARDENGINEI_ARM7_BUFFERED_LOCATION           0x027B6000
#define CARDENGINEI_ARM7_SDK5_BUFFERED_LOCATION      0x027C9800
#define CARDENGINEI_ARM9_BUFFERED_LOCATION           0x027DA000
#define CARDENGINEI_ARM9_CACHED_BUFFERED_LOCATION    0x027DE000
#define CARDENGINEI_ARM9_ROMINRAM_BUFFERED_LOCATION  0x027E3000
#define CARDENGINEI_ARM9_DLDI_BUFFERED_LOCATION      0x027E5000
#define CARDENGINEI_ARM9_SDK5_BUFFERED_LOCATION      0x027EC000
#define CARDENGINEI_ARM9_SDK5_DLDI_BUFFERED_LOCATION 0x027F1000

#define CARDENGINEI_ARM7_LOCATION                  0x037C8400
#define CARDENGINEI_ARM7_LOCATION_ALT              0x03008400
#define CARDENGINEI_ARM7_SDK5_LOCATION             0x02EE8400
#define CARDENGINEI_ARM9_LOCATION                  0x02780000
#define CARDENGINEI_ARM9_CACHED_LOCATION1          0x02001000
#define CARDENGINEI_ARM9_CACHED_LOCATION2          0x02002000
#define CARDENGINEI_ARM9_CACHED_LOCATION_ROMINRAM  0x023DE000
#define CARDENGINEI_ARM9_CACHED_MID_LOCATION       0x023F0000
#define CARDENGINEI_ARM9_CACHED_END_LOCATION       0x023FD000
#define CARDENGINEI_ARM9_SDK5_LOCATION             0x023F4000
#define CARDENGINEI_ARM9_TWLSDK_LOCATION           0x02EF8000 // Used for DSi-Enhanced games in DSi mode
#define CARDENGINEI_ARM9_GSDD_LOCATION             0x037F0000 // WRAM-A slot 0

#define CARDENGINE_SHARED_ADDRESS     0x027FFB0C

#define LOADER_RETURN_LOCATION                     (u32)CARDENGINEI_ARM7_BUFFERED_LOCATION+0xA000
#define LOADER_RETURN_SDK5_LOCATION                (u32)CARDENGINEI_ARM7_SDK5_BUFFERED_LOCATION+0xA000

#define RESET_PARAM      0x27FFC20
#define RESET_PARAM_SDK5 0x2FFFC20

//#define TEMP_MEM 0x02FFE000 // __DSiHeader

#define NDS_HEADER_4MB     0x023FFE00
#define NDS_HEADER         0x027FFE00
#define NDS_HEADER_SDK5    0x02FFFE00 // __NDSHeader
#define NDS_HEADER_POKEMON 0x027FF000

#define DSI_HEADER         0x027FE000
#define DSI_HEADER_SDK5    0x02FFE000 // __DSiHeader

#define ROM_LOCATION_EXT      0x0C400000
#define ROM_LOCATION_EXT_P2   0x03700000
#define ROM_LOCATION          0x0C800000
#define ROM_SDK5_LOCATION     0x0D000000

#define CACHE_ADRESS_START               0x02800000
#define CACHE_ADRESS_START_low           0x02480000
#define retail_CACHE_ADRESS_START_TWLSDK 0x02F80000

#define retail_CACHE_ADRESS_SIZE        0x800000
#define retail_CACHE_ADRESS_SIZE_low    0x278000
#define retail_CACHE_ADRESS_SIZE_SDK5   0x700000
#define retail_CACHE_ADRESS_SIZE_TWLSDK 0x40000

#define retail_CACHE_SLOTS_16KB      0x200
#define retail_CACHE_SLOTS_32KB      0x100
#define CACHE_SLOTS_16KB_low         0xA0
#define CACHE_SLOTS_32KB_low         0x50
#define retail_CACHE_SLOTS_16KB_SDK5 0x1C0
#define retail_CACHE_SLOTS_32KB_SDK5 0xE0

#define dev_CACHE_ADRESS_START_SDK5 0x0D000000

#define dev_CACHE_ADRESS_SIZE      0x1800000
#define dev_CACHE_ADRESS_SIZE_SDK5 0x1000000

#define dev_CACHE_SLOTS_16KB      0x600
#define dev_CACHE_SLOTS_32KB      0x300
#define dev_CACHE_SLOTS_16KB_SDK5 0x400
#define dev_CACHE_SLOTS_32KB_SDK5 0x200

//#define HGSS_CACHE_ADRESS_SIZE 0x1E0000

#define HGSS_CACHE_SLOTS 0xF

#endif // LOCATIONS_H
