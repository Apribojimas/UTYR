#include <string.h>
#include <ctype.h>

int Toupper(int i)
{
 if(i > 255)
  return i;
 if(isalpha(i))
  return toupper(i);
 switch((char)i)
  {
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
  }
 return i;
}

int Tolower(int i)
{
 if(i > 255)
  return i;
 if(isalpha(i))
  return tolower(i);
 switch((char)i)
  {
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
   case '�':
        return '�';
  }
 return i;
}

void Strupr(char *string)
{
 int i;

 for(i = strlen(string) - 1;i >= 0;i --)
  string[i] = Toupper(string[i]);
}

void Strlwr(char *string)
{
 int i;

 for(i = strlen(string) - 1;i >= 0;i --)
  string[i] = Tolower(string[i]);
}