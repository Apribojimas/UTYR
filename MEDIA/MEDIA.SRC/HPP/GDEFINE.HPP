#include <dir.h>
// gbutton

#define RELEASE    0            // isButtonPressed
#define PRESSED    1

//gvideomode

#define WND_GRAPH         0x01      // defined WndType
#define WND_TEXT          0x02

// gsmallwindow

#define WND_CLOSE_BUTTON  0x04      // defined WndType
#define WND_MIN_BUTTON    0x08
#define WND_MAX_BUTTON    0x10

#define WND_ICON      0             // defined WndStatus
#define WND_NORMAL    1
#define WND_BIG       2

#define WND_MOVE       1            // WndEvent
#define WND_MOUSE_MOVE 2
#define WND_BUTTON     3

#define WND_PASIVE     0             // WndActive
#define WND_ACTIVE     1

// gwindow

#define  DTW_MENU    1                  //  WndMenu

#define WND_HSCROLL  0x01               // WndScroll
#define WND_VSCROLL  0x02

// gmenu

#define MENU_FILL   0                   // MenuType
#define MENU_FRAME  1
#define MENU_EMPTY  2

//gscroll

#define HORIZANTAL   0x01            // ScrollType
#define VERTICAL     0x02

#define SCROLL_BUTTON   2             // return event handler
#define SCROLL_MOVE     3

// gfile

#define MAX_PATH (MAXPATH + 1)        // path length
#define READ     0                    // GFileType (nuskaitymo)
#define WRITE    1                    //           (rasymo)

// button + shape
#define BUTTON_UP          0          // ButtonEvent
#define BUTTON_DOWN        1
#define BUTTON_ACTIVE      2
#define BUTTON_PASIVE      3
#define BUTTON_UNAVAILABLE 4

#define JUSTIFY_LEFT       0           // Justify
#define JUSTIFY_RIGHT      1
#define JUSTIFY_CENTER     2

// MSGFilter

#define DISABLE_ALL_MSG    0   // praleidziam tik tuos kuriuos uzsakem
#define ENABLE_ALL_MSG     1   // praleidziam visus pranesimus

// GReadBMP

#define WINDOW_SIZE_DX  450   // nustatom pradini lango dydi
#define WINDOW_SIZE_DY  400

// fragmentai e,l,r,c,n
#define FRAGMENT_STATUS_FILL_BEGIN 1
#define FRAGMENT_STATUS_FILL_FIRST 2
#define FRAGMENT_STATUS_FILL_MOVE  3
#define FRAGMENT_STATUS_FILL_END   4
