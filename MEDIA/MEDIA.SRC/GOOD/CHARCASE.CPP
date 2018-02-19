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
   case 'Ð':
        return 'µ';
   case 'Ñ':
        return '¶';
   case 'Ò':
        return '·';
   case 'Ó':
        return '¸';
   case 'Ô':
        return '½';
   case 'Õ':
        return '¾';
   case 'Ö':
        return 'Æ';
   case '×':
        return 'Ç';
   case 'Ø':
        return 'Ï';
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
   case 'µ':
        return 'Ð';
   case '¶':
        return 'Ñ';
   case '·':
        return 'Ò';
   case '¸':
        return 'Ó';
   case '½':
        return 'Ô';
   case '¾':
        return 'Õ';
   case 'Æ':
        return 'Ö';
   case 'Ç':
        return '×';
   case 'Ï':
        return 'Ø';
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