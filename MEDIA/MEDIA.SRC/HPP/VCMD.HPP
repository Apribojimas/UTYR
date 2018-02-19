#ifndef _VASIA_DEFINE
#define _VASIA_DEFINE

enum VasiaCommand
{
 VASIA_COMMAND = 10000,
 GRABER,                   // mouse matuoklis
 VAIZDA_12,                // 12 vaizdu
 VIDEO_MODE,               // ijungti video rezimus
 VAIZDO_APDOR,             // apdorosime vaizdus
 BMP_READ,                 // pranesam, kad reikes uzsikrauti vaizda
 BMP_WRITE,
 FRAGMENT_SWITCH,          // pakeisime menu i koks fragmentas bus iskirptas
 FRAGMENT_RECTANGLE,       //  - staciakampis
 FRAGMENT_CIRCLE,          //  - apskritimas
 FRAGMENT_ELLIPSE,         //  - elipse
 FRAGMENT_FRAGMENT,        //  - nereguliarus
 FRAGMENT_FILL,            // pranesam fragmentui (...), kad jis uzsipildytu duomenimis
 FRAGMENT_FILL_ABORT,      // pranesam fragmentui (class), kad buvo atsisakyta fragmento
 FRAGMENT_COPY,            // pranesam kad mes norime gauti fragmenta
 FRAGMENT_HANDLER,         // po fragment_copy komandos ivykdom fragmento copy i atm. manager ir atsiunciam jo handler
 FRAGMENT_SHOW,            // aktyvus fragmentas nori persipiesti
 LUPA,                     // didinsim paveiksla
 LUPA_PICTURE_HANDLER,     // paveiksliuko kuri reikia didinti handleris
 DESTROY_HISTO,            // pranesam kad histograma turi susinaikinti
 HISTOGRAMA,               // suskaiciuoti histograma
 DROP_ICON,                // ismesti ikona
 FR_FILTRAI,               // pakeiciam meniu i filtru meniu
 MEDIAN,
 LAPLASS,
 ROBERTS,
 HIGH_PASS,
 AVERAGE,
 GRADIENT,
 ROBERTS_SQRT,
 ROBERTS_MAX,
 ROBERTS_ABS,
 AVERAGE_1,
 AVERAGE_2,
 AVERAGE_3,
 AVERAGE_4,
 AVERAGE_5,
 AVERAGE_6,
 HIGH_PASS_1,
 HIGH_PASS_2,
 HIGH_PASS_3,
 EDGE_DETECTION,
 DETECT_MAX,
 DETECT_MIN,
 WBOUNDARY,
 EWRONGS,
 GRADIENT_1,
 GRADIENT_2,
 GRADIENT_3,
 GRADIENT_4,
 GRADIENT_5,
 GRADIENT_6,
 GRADIENT_7,
 GRADIENT_8,
 LAPLAS1,                  // laplaso filtrai
 LAPLAS2,
 LAPLAS3,
 LAPLAS4,
 MEDIAN1x3,                // medianiniai filtrai
 MEDIAN3x1,
 MEDIAN3x3,
 MEDIAN5x5,
 MEDIANCROSS,
 HISTO_REDUCE,
 HISTO_REDUCE_OK,
 HISTO_PL,                 // histograminis prapletimas
 HISTO_PL1,
 HISTO_PL2,
 HISTO_PL3,
 HISTO_PL_OK,
 HISTO_PL_OK1,
 HISTO_PL_OK2,
 BIN,
 BIN_OK,
 EAT_MEM,                  // suvalgyti atminti.
 TAIP_NE_OK,               // Taip_Ne objekto vidines komandos
 TAIP_NE_CANCEL,
 DESKTOP_END,              // pabaiga !!!
 KALKULIATORIUS,           // issaukiam kalkuliatoriu
 KALKUL_STRUCT,            // perduodam kalkuliatoriaus struct CalStruct
 KALIBRAVIMAS,             //
 KALIBRAVIMAS_OK,          //
 KALIBRAVIMAS_CANCEL,      //
 D1,                       // atstumai
 D2,
 D3,
 D4,
 D5,
 D6,
 V1,                       // turiai
 V2,
 FILL_GROUP,                // pranesam kad pasikeite grupes sudetis
 V_SANTYKIS,                // turiu santykis
 D_SANTYKIS,                // atstumu santykis
 TURIS,                     // turis
 GRID,                      // tinklelis
 GRID_END,                  // pabaiga
 KOORD_ASYS,                // koordinaciu asys
 PLOTAS,                    // plotas
 PLOTAS_FILL,               // pranesa, kad suskaiciavom plota
 NUSKANUOTI,                // skanuojam
 CHANGE_FILE_MASK,          // pakeitem FileNameMask
 CLOSE_PICTURE,             // naikinu 12 vaizdu
 VM_640,                    // ijungti video rezima
 VM_800,
 VM_1024,
 DESKTOP_WND_DRAW,          // persipiesti Desktop Windows
 PACIENTAS,                 // infornacija apie pacienta
 CHANGE_HISTO_NAME,         // pakeisti histogramos varda
 FRONTOGRAMA,
 VIENA_LINIJA,              // prie frontogramos
 TRYS_LINIJOS,
 PENKIOS_LINIJOS,
 SEPTYNIOS_LINIJOS,
 DEVYNIOS_LINIJOS,
 VIENUOLIKA_LINIJU,
 DESTROY_FRONTO,            // sunaikinti frontograma
 DESTROY_FRAGMENT_LINE,     // sunaikinam frontogramos linija
 TASK_CHANGE_FILTER,
};

enum FilterEnum
{
 CROSS,
 DIAGONAL,
 WEIGHT,
 CLASIC,
 MIN,
 MAX,
 SQRT,
 ABS,
 BOUNDARY,
 WRONGS,
 FON,
};

#endif
