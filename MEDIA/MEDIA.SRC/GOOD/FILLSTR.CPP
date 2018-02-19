#include <conio.h>
#include <ctype.h>
#include <alloc.h>
#include <string.h>
#include "keys.h"

int FillStr(int key,char *Str,int &CurrentPlace,int StrSize)
{
 int i;
 switch(key)
  {
   case CR:
        return 1;
   case BS:
        if (CurrentPlace == 0)
         return 1;
        memcpy(Str+CurrentPlace - 1,Str + CurrentPlace,strlen(Str + CurrentPlace));
        Str[StrSize - 1] = ' ';
        CurrentPlace --;
        return 1;
   case DEL:
        if (CurrentPlace != StrSize - 1)
         memcpy(Str + CurrentPlace,Str + CurrentPlace + 1,strlen(Str + CurrentPlace));
        Str[StrSize - 1] = ' ';
        return 1;
   case LEFT:
        if (CurrentPlace != 0)
         CurrentPlace --;
        return 2;
   case RIGHT:
        if (CurrentPlace < StrSize - 1)
         CurrentPlace ++;
        return 2;
   case END:
        CurrentPlace = StrSize - 1;
        return 2;
   case HOME:
        CurrentPlace = 0;
        return 2;
   case CTRL_LEFT:
        if(isalpha(Str[CurrentPlace]) || isdigit(Str[CurrentPlace]))
         {
          while(isalpha(Str[CurrentPlace]) || isdigit(Str[CurrentPlace]))
           if (CurrentPlace != 0)
            CurrentPlace --;
           else
            return 2;
         }
        else
         {
          while(!(isalpha(Str[CurrentPlace]) || isdigit(Str[CurrentPlace])))
           if (CurrentPlace != 0)
            CurrentPlace --;
           else
            return 2;
         }
        return 2;
   case CTRL_RIGHT:
        if(isalpha(Str[CurrentPlace]) || isdigit(Str[CurrentPlace]))
         {
          while(isalpha(Str[CurrentPlace]) || isdigit(Str[CurrentPlace]))
           if (CurrentPlace < StrSize - 1)
            CurrentPlace ++;
           else
            return 2;
         }
        else

         {
          while(!(isalpha(Str[CurrentPlace]) || isdigit(Str[CurrentPlace])))
           if (CurrentPlace < StrSize - 1)
            CurrentPlace ++;
           else
            return 2;
         }
        return 2;
   default :
        if (key > 255)
         break;
        for(i = StrSize - 1;i > CurrentPlace;i --)
         Str[i] = Str[i - 1];
        Str[CurrentPlace] = (char)key;
        if (CurrentPlace < StrSize - 1)
          CurrentPlace ++;
        return 1;
  }
 Str[StrSize] = 0;

return 0;
}

