#ifndef LOCATIONS_H
#define LOCATIONS_H

#define TARGETBUFFERHEADER 0x02BFF000

#define EXCEPTION_STACK_LOCATION      0x02380000

#define ROM_FILE_LOCATION         0x37F7F80
#define ROM_FILE_LOCATION_ALT     0x303FF80
#define ROM_FILE_LOCATION_MAINMEM 0x2780000
#define ROM_FILE_LOCATION_TWLSDK  0x2F7FF00
#define SAV_FILE_LOCATION         (ROM_FILE_LOCATION + 32) //+ sizeof(aFile)
#define SAV_FILE_LOCATION_ALT     (ROM_FILE_LOCATION_ALT + 32) //+ sizeof(aFile)
#define SAV_FILE_LOCATION_MAINMEM (ROM_FILE_LOCATION_MAINMEM + 32) //+ sizeof(aFile)
#define SAV_FILE_LOCATION_TWLSDK  (ROM_FILE_LOCATION_TWLSDK + 32) //+ sizeof(aFile)
#define OVL_FILE_LOCATION         (ROM_FILE_LOCATION + 64) //+ sizeof(aFile)
#define OVL_FILE_LOCATION_ALT     (ROM_FILE_LOCATION_ALT + 64) //+ sizeof(aFile)
#define OVL_FILE_LOCATION_MAINMEM (ROM_FILE_LOCATION_MAINMEM + 64) //+ sizeof(aFile)
#define OVL_FILE_LOCATION_TWLSDK  (ROM_FILE_LOCATION_TWLSDK + 64) //+ sizeof(aFile)
/* #define GBA_FILE_LOCATION         (ROM_FILE_LOCATION + 64) //+ sizeof(aFile)
#define GBA_FILE_LOCATION_ALT     (ROM_FILE_LOCATION_ALT + 64) //+ sizeof(aFile)
#define GBA_FILE_LOCATION_MAINMEM (ROM_FILE_LOCATION_MAINMEM + 64) //+ sizeof(aFile)
#define GBA_SAV_FILE_LOCATION         (ROM_FILE_LOCATION + 96) //+ sizeof(aFile)
#define GBA_SAV_FILE_LOCATION_ALT     (ROM_FILE_LOCATION_ALT + 96) //+ sizeof(aFile)
#define GBA_SAV_FILE_LOCATION_MAINMEM (ROM_FILE_LOCATION_MAINMEM + 96) //+ sizeof(aFile) */
#define FONT_FILE_LOCATION_TWLSDK  (ROM_FILE_LOCATION_TWLSDK + 96) //+ sizeof(aFile)

#define LOAD_CRT0_LOCATION      0x06840000 // LCDC_BANK_C
#define LOAD_CRT0_LOCATION_B4DS 0x06860000 // LCDC_BANK_D

#define IPS_LOCATION       0x022F8000
#define IMAGES_LOCATION    0x02338000 // Also IPS location for B4DS mode

#define CHEAT_ENGINE_LOCATION_B4DS_BUFFERED     0x023FE400
#define CARDENGINE_ARM7_LOCATION_BUFFERED       0x023FD000
#define CARDENGINE_ARM9_LOCATION_BUFFERED       0x023E0000

#define CHEAT_ENGINE_LOCATION_B4DS           0x027DE000
#define CARDENGINE_ARM7_LOCATION             0x0380E000
#define CARDENGINE_ARM9_LOCATION_DLDI        0x023DA800
#define CARDENGINE_ARM9_LOCATION_DLDI_ALT    0x023F9800
#define CARDENGINE_ARM9_LOCATION_DLDI_ALT2   0x023FA800
#define CARDENGINE_ARM9_LOCATION_DLDI_EXTMEM 0x027B0000

#define DONOR_ROM_ARM7_LOCATION                      0x02680000
#define DONOR_ROM_ARM7_SIZE_LOCATION                 0x026B0000
#define DONOR_ROM_ARM7I_SIZE_LOCATION                0x026B0004
#define DONOR_ROM_MBK6_LOCATION                      0x026B0008
#define DONOR_ROM_DEVICE_LIST_LOCATION               0x026B000C
#define ARM9_DEC_SIZE_LOCATION                       0x026B0010
#define INGAME_MENU_EXT_LOCATION                     0x026B8000
#define INGAME_MENU_EXT_LOCATION_B4DS                0x02380000
#define CHEAT_ENGINE_BUFFERED_LOCATION	             0x026E0000
#define INGAME_MENU_LOCATION                         0x026F6000
#define INGAME_MENU_LOCATION_B4DS                    0x023E6000
#define INGAME_MENU_LOCATION_TWLSDK                  0x02F46400
#define INGAME_MENU_LOCATION_DSIWARE                 INGAME_MENU_LOCATION_TWLSDK
#define UNPATCHED_FUNCTION_LOCATION                  0x027FFA40
#define UNPATCHED_FUNCTION_LOCATION_SDK5             0x02FFFA40

#define BLOWFISH_LOCATION_B4DS                       0x023ECE00
#define BLOWFISH_LOCATION                            0x027B4C00
//#define DSI_BLOWFISH_LOCATION                        0x027EA800
#define ARM7_FIX_BUFFERED_LOCATION                   0x027B5E00
#define CARDENGINEI_ARM7_BUFFERED_LOCATION           0x027B6000
#define CARDENGINEI_ARM9_BUFFERED_LOCATION           0x027DA000
#define CARDENGINEI_ARM9_CACHED_BUFFERED_LOCATION    0x027DE000
#define CARDENGINEI_ARM9_ROMINRAM_BUFFERED_LOCATION  0x027E3000
#define CARDENGINEI_ARM9_DLDI_BUFFERED_LOCATION      0x027E5000
#define CARDENGINEI_ARM9_SDK5_BUFFERED_LOCATION      0x027EC000
#define CARDENGINEI_ARM9_SDK5_DLDI_BUFFERED_LOCATION 0x027F1000

#define CARDENGINEI_ARM7_LOCATION                  0x037C0400
#define CARDENGINEI_ARM7_LOCATION_ALT              0x03008400
#define CARDENGINEI_ARM7_SDK5_LOCATION             0x02F68400
#define CARDENGINEI_ARM7_DSIWARE_LOCATION          0x02F58400
#define CARDENGINEI_ARM9_LOCATION                  0x027B0000
#define CARDENGINEI_ARM9_CACHED_LOCATION1          0x02001000
#define CARDENGINEI_ARM9_CACHED_LOCATION2          0x02002000
#define CARDENGINEI_ARM9_CACHED_LOCATION1_ROMINRAM 0x027BE000
#define CARDENGINEI_ARM9_CACHED_LOCATION2_ROMINRAM 0x023E0000
#define CARDENGINEI_ARM9_LOCATION_DSI_WRAM         0x03700000
#define CARDENGINEI_ARM9_TWLSDK_LOCATION           0x02F78800 // Used for DSi-Enhanced games in DSi mode
#define CARDENGINEI_ARM9_DSIWARE_LOCATION          0x02F40000
#define CARDENGINEI_ARM9_GSDD_LOCATION             0x037F0000 // WRAM-A slot 0

#define CARDENGINE_SHARED_ADDRESS_SDK1 0x027FFA0C
#define CARDENGINE_SHARED_ADDRESS_SDK5 0x02FFFA0C

#define LOADER_RETURN_LOCATION                     (u32)CARDENGINEI_ARM7_BUFFERED_LOCATION+0x11800
#define LOADER_RETURN_SDK5_LOCATION                (u32)CARDENGINEI_ARM7_BUFFERED_LOCATION+0xF800
#define LOADER_RETURN_DSIWARE_LOCATION             (u32)CARDENGINEI_ARM7_BUFFERED_LOCATION+0x8C00

#define RESET_PARAM      0x27FFC20
#define RESET_PARAM_SDK5 0x2FFFC20

//#define TEMP_MEM 0x02FFE000 // __DSiHeader

#define NDS_HEADER         0x027FFE00
#define NDS_HEADER_SDK5    0x02FFFE00 // __NDSHeader
#define NDS_HEADER_POKEMON 0x027FF000

#define DSI_HEADER         0x027FE000
#define DSI_HEADER_SDK5    0x02FFE000 // __DSiHeader

#define ROM_LOCATION_EXT_SDK2 0x0C3C0000
#define ROM_LOCATION_EXT      0x0C3E2000
#define ROM_LOCATION_EXT_P2   0x03700000
#define ROM_LOCATION          0x0C800000
#define ROM_SDK5_LOCATION     0x0D000000

#define CACHE_ADRESS_START                  0x0C800000
#define CACHE_ADRESS_START_low              0x0C480000
#define retail_CACHE_ADRESS_START_TWLSDK    0x02F00000

#define retail_CACHE_ADRESS_SIZE        0x800000
#define retail_CACHE_ADRESS_SIZE_low    0x274000
#define retail_CACHE_ADRESS_SIZE_SDK5   0x7E0000
#define retail_CACHE_ADRESS_SIZE_TWLSDK 0x26000

#define retail_CACHE_SLOTS_16KB      0x200
#define retail_CACHE_SLOTS_32KB      0x100
#define CACHE_SLOTS_16KB_low         0xA0
#define CACHE_SLOTS_32KB_low         0x50
#define retail_CACHE_SLOTS_16KB_SDK5 0x1C0
#define retail_CACHE_SLOTS_32KB_SDK5 0xE0

#define dev_CACHE_ADRESS_START_SDK5 0x0D000000

#define dev_CACHE_ADRESS_SIZE       0x1800000
#define dev_CACHE_ADRESS_SIZE_SDK5  0x1000000
#define dev_CACHE_ADRESS_SIZE_TWLSDK 0xF80000

#define dev_CACHE_SLOTS_8KB         0xC00
#define dev_CACHE_SLOTS_16KB        0x600
#define dev_CACHE_SLOTS_32KB        0x300
#define dev_CACHE_SLOTS_8KB_SDK5    0x800
#define dev_CACHE_SLOTS_8KB_TWLSDK  0x7C0
#define dev_CACHE_SLOTS_16KB_SDK5   0x400
#define dev_CACHE_SLOTS_16KB_TWLSDK 0x3E0
#define dev_CACHE_SLOTS_32KB_SDK5   0x200
#define dev_CACHE_SLOTS_32KB_TWLSDK 0x1F0

#endif // LOCATIONS_H
