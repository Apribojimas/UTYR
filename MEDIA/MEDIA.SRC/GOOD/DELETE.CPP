#include "msgfdata.hpp"
#include "grollerd.hpp"
#include "gcbutton.hpp"
#include "desktopw.hpp"
#include "ginput.hpp"
#include "gfile.hpp"
#include "greadbmp.hpp"
#include "fragment.hpp"
#include "bpoint.hpp"
#include "mousemer.hpp"
#include "mminfo.hpp"
#include "calculate.hpp"
#include "histo.hpp"
#include "laplas.hpp"
#include "median.hpp"
#include "warning.hpp"
#include "viewtext.hpp"
#include "help.hpp"
#include "taipne.hpp"
#include "kalibrav.hpp"
#include "grid.hpp"
#include "skaner.hpp"
#include "vaizda12.hpp"
#include "histopl.hpp"
#include "magnify.hpp"
#include "frag_r.hpp"
#include "frag_c.hpp"
#include "frag_e.hpp"
#include "frag_f.hpp"
#include "frag_l.hpp"
#include "lupa.hpp"
#include "pacient.hpp"
#include "getline.hpp"
#include "fronto.hpp"
#include "gpal.hpp"

void Delete (Object *Obj)
{
 switch(Obj->isA())
  {
   case _Bag:
	delete (Bag *)Obj;
	break;
   case _GPoint:
	delete (GPoint *)Obj;
	break;
   case _GRectangle:
	delete (GRectangle *)Obj;
	break;
   case _GEventHandler:
	delete (GEventHandler *)Obj;
	break;
   case _GVideoMode:
	delete (GVideoMode *)Obj;
	break;
   case _GFrame:
	delete (GFrame *)Obj;
	break;
   case _GSmallWindow:
	delete (GSmallWindow *)Obj;
	break;
   case _GWindow:
	delete (GWindow *)Obj;
	break;
   case _GButton:
	delete (GButton*)Obj;
	break;
   case _GRadioButton:
	delete (GRadioButton*)Obj;
	break;
   case _GCheckButton:
	delete (GCheckButton*)Obj;
	break;
   case _GMenu:
	delete (GMenu *)Obj;
	break;
   case _DeskTopWindow:
	delete (DeskTopWindow *)Obj;
	break;
   case _GScroll:
	delete (GScroll *)Obj;
	break;
   case _GRoller:
	delete (GRoller *)Obj;
	break;
   case _GRollerData:
	delete (GRollerData *)Obj;
	break;
   case _GFile:
	delete (GFile *)Obj;
	break;
   case _Group:
	delete (Group *)Obj;
	break;
   case _GInput:
	delete (GInput *)Obj;
	break;
   case _MSGFilter:
        delete (MSGFilter *)Obj;
        break;
   case _MSGFilterData:
        delete (MSGFilterData *)Obj;
        break;
   case _GReadBMP:
	delete (GReadBMP *)Obj;
	break;
   case _FragmentRectangle:
	delete (FragmentRectangle *)Obj;
	break;
   case _FragmentLine:
	delete (FragmentLine *)Obj;
	break;
   case _FragmentEllipse:
	delete (FragmentEllipse *)Obj;
	break;
   case _FragmentCircle:
	delete (FragmentCircle *)Obj;
	break;
   case _FragmentFragment:
	delete (FragmentFragment*)Obj;
	break;
   case _Fragment:
	delete (Fragment *)Obj;
	break;
   case _FragmentGroup:
	delete (FragmentGroup *)Obj;
	break;
   case _BPoint:
	delete (BPoint*)Obj;
	break;
   case _Lupa:
	delete (Lupa*)Obj;
	break;
   case _MouseMer:
        delete (MouseMer *)Obj;
        break;
   case _MemManInfo:
        delete (MemManInfo *)Obj;
        break;
   case _Calculate:
        delete (Calculate *)Obj;
        break;
   case _Histo:
        delete (Histo *)Obj;
        break;
   case _Warning:
        delete (Warning *)Obj;
        break;
   case _Laplas:
        delete (Laplas *)Obj;
        break;
   case _FMedian1x3:
        delete (Median1x3 *)Obj;
        break;
   case _FMedian3x1:
        delete (Median3x1 *)Obj;
        break;
   case _FMedian3x3:
        delete (Median3x3 *)Obj;
        break;
   case _FMedian5x5:
        delete (Median5x5 *)Obj;
        break;
   case _FMedianCross:
        delete (MedianCross *)Obj;
        break;
   case _ViewText:
        delete (ViewText *)Obj;
        break;
   case _Help:
        delete (Help *)Obj;
        break;
   case _Taip_Ne:
        delete (Taip_Ne *)Obj;
        break;
   case _Kalibravimas:
        delete (Kalibravimas *)Obj;
        break;
   case _Grid:
        delete (Grid *)Obj;
        break;
   case _Skaner:
        delete (Skaner *)Obj;
        break;
   case _PictureHandler:
        delete (PictureHandler *)Obj;
        break;
   case _Vaizda12:
        delete (Vaizda12 *)Obj;
        break;
   case _Magnify:
        delete (Magnify *)Obj;
        break;
   case _HistoPl:
        delete (HistoPl *)Obj;
        break;
   case _Pacient:
        delete (Pacient *)Obj;
        break;
   case _GetLineFromMemory:
        delete (GetLineFromMemory *)Obj;
        break;
   case _FrontoGrama:
        delete (FrontoGrama *)Obj;
        break;
   case _GPalette:
        delete (GPalette *)Obj;
        break;
   default:
        delete Obj;
        break;
  }
}