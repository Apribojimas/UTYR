#ifndef _MSGFILTER
#define _MSGFILTER

#include "bag.hpp"
#include "grec.hpp"
#include "struct.hpp"


class MSGFilter : public GRectangle
{
 Bag MouseBag;
 Bag KeyboardBag;
 Bag CommandBag;

 int MouseBagFlag;
 int KeyboardBagFlag;
 int CommandBagFlag;

public:
 ~MSGFilter();
  MSGFilter(int x = 0,int y = 0,int dx = 0,int dy = 0);

  void ClearAllMSG(void);
  void ClearMouseMSG(void);
  void ClearKeyboardMSG(void);
  void ClearCommandMSG(void);
  void SetMSGFilter(int i = 1);
  void SetMouseMSGFilter(int i = 1);
  void SetKeyboardMSGFilter(int i = 1);
  void SetCommandMSGFilter(int i = 1);
  void SetMouseMSG(int i,...);
  void SetKeyboardMSG(int i,...);
  void SetCommandMSG(int i,...);
  int isMyMSG(MSG &msg);
  int isMyMouseMSG(MSG &msg);
  int isMyKeyboardMSG(MSG &msg);
  int isMyCommandMSG(MSG &msg);

  virtual ClassType isA();
};
#endif
