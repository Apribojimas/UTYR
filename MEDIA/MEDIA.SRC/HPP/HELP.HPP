#ifndef HELP
#define HELP

#include "viewtext.hpp"

class Help : public ViewText
{

public:
 ~Help();
  Help();

// reikalinga Object
  virtual ClassType isA();
protected:
  virtual int Keyboard(MSG &msg);       // klaviaturos
};
#endif
