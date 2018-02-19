#ifndef _DEFINE
#define _DEFINE

enum ClassType
 {
  _Object = 0,
  _Bag,
  _GPoint,
  _GRectangle,
  _GEventHandler,
  _GVideoMode,
  _GFrame,
  _GSmallWindow,
  _GWindow,
  _GButton,
  _GRadioButton,
  _GCheckButton,
  _GMenu,
  _DeskTopWindow,
  _GScroll,
  _GRoller,
  _GRollerData,
  _GFile,
  _Group,
  _GInput,
  _MSGFilter,
  _MSGFilterData,
  _GReadBMP,
  _FragmentRectangle,
  _FragmentEllipse,
  _FragmentCircle,
  _FragmentLine,
  _FragmentFragment,
  _Fragment,
  _FragmentGroup,
  _BPoint,
  _Lupa,
  _MouseMer,
  _MemManInfo,
  _Calculate,
  _Histo,
  _Warning,
  _Laplas,
  _FMedian3x3,
  _FMedian3x1,
  _FMedian1x3,
  _FMedianCross,
  _FMedian5x5,
  _ViewText,
  _Help,
  _Taip_Ne,
  _Kalibravimas,
  _Grid,          // tinklelis
  _Skaner,
  _PictureHandler,
  _Vaizda12,
  _Magnify,
  _HistoPl,
  _Pacient,
  _GetLineFromMemory,
  _FrontoGrama,
  _GPalette,
  _Average,
  _HighPass,
  _Gradient,
  _Roberts,
  _HistoReduce,
  _HistoScroller,
  _Edge,
  _HistoMod,
};

enum SystemCommand
 {
  EMPTY = 0,          // tuscia komanda
  REDRAW,             // perpiesti ekrana
  DESKTOP_EXIT,       // pranesimas, kad pasibaige programa
  OUT_OF_MEMORY,      // truksta atm.
  HEAPCORRUPT,        // pranesam kad blogai su heap
  ITEM_ACTIVE,        // aktivuojam langa kuris gavo si pranesima
  ITEM_PASIVE,        // langas tampa neaktyvus
  ITEM_UNAVAILABLE,   // langas neapsikiamas
  ITEM_SHOW,          // visiems langams reikia persipiesti
  ITEM_HIDE,
  ITEM_DESTROY,       // komanda reiskia kad sunaikinamas item su adr.
  ITEM_CLOSE,         // komanda skirta window
  ITEM_MIN,           // pranesam kad reikia si langa padaryti icon
  ITEM_ICON,          // pranesam kad reikia sio lango icon ideti i desktop
  ITEM_NORMAL,        // pranesam kad langas turi persipiesti ir jau nera icon busenoje
  ITEM_MAX,           // komanda skirta window
  ITEM_STATUS,        // komanda skirta kad suzinoti ar langas nera icon
  ITEM_OK,            // patvirtinimo komanda naudojama taip/ne sistemoje
  ITEM_CANCEL,        // atsisakymo komanda naudojama taip/ne sistemoje
  ITEM_REGISTER,      // iregistruojam langa
  MENU_ACTIVE,        // komanda kuri nurodo, kad aktivizuojamas menu
  MENU_PASIVE,        //          - || -          pasive menu
  FILE_READ_OK,       // pranesam kad yra jau parinktas kelias
  FILE_WRITE_OK,      // pranesam kad yra jau parinktas kelias
  FILE_CANCEL,        // pranesam kad vartotojas atsisake
  FILE_DIRECTORY,     // pranesam gfile kad pakeistu direktorija
  FILE_DISK,          //               - || -        diska
  FILE_MASK,          //      - || -        pasikeite file mask
  ROLLER_OK,          // vidinis groller pranesimas kuris reiskia kad jis turi pasiusti cmd savo uzsakovui
  TERMINATE_FILTER,   // sunaikinti filtra
  FILTER_LOCK_OUT,    // filtras pasibaige
  VIDEO_MODE_640,     // pranesam, kad keiciam video rezimus
  VIDEO_MODE_800,
  VIDEO_MODE_1024,
  INVERSE_PALETTE,    // invertuojam gray palete
 };
#endif
