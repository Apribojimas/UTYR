#ifndef _OBJECT_H
#define _OBJECT_H

#include "define.hpp"

class Object
{
public:
 unsigned int RegisterNumber;

public:
  Object();
  virtual ~Object();

  virtual ClassType isA() = 0;
};

#endif
