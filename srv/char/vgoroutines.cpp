#include "vgoroutines.h"


//CONVERT ASCII: WORKING
//encrypt text: hex ascii code (in hex) * 4 (IN DEC) then back to hex = crypted
//decrypt: cryptd (in hex) / 4 (in dec) then back to hex = original ascii code


void cryptASCII(char *text, unsigned short length)
{
int i;
do {
*(unsigned short*)text = *(unsigned short*)text * 4; //ENCRYPT
//hex_print(pData, 2);
//cout<<pData<<"\n";
text+=2;
i++;
} while (i < (length/2));
}


void decryptASCII(char *text, unsigned short length)
{
int i;
do {
*(unsigned short*)text = *(unsigned short*)text / 4; //DECRYPT
//hex_print(pData, 2);
//cout<<pData<<"\n";
text+=2;
i++;
} while (i < (length/2));
}

