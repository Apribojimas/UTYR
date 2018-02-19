#ifndef _BAG
#define _BAG

#define DELETE          0x01
#define NO_DELETE       0x02
#include "Object.hpp"
void Delete (Object *Obj);

class Bag : public Object
{
 int Status;
protected:
 int BagSize;
public:
 Object ** Array;

public:
 ~Bag();
  Bag(int status = NO_DELETE);

  int GetBagSize(void);
  void operator + (Object *Obj);
  void operator - (int i);
  Object * operator [](int i);
  Object * GetItem(int i);
  void PutToHead(int i);
  void PutToTail(int i);
  void ChangePlace(int get,int put = 0);
  void Swap(int i,int j);
// reikalinga Object
  virtual ClassType isA();
};
#endif
