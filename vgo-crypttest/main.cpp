#include <iostream>

using namespace std;



void hex_print(char* data, int length)
{
for(int i = 0; i < length; i++)
{
printf("0x%02x ",(unsigned char)*(data+i));
}
printf("\n");
}

void ascii_print(char* data, int length)
{
     for(int i = 0; i <length; i++)
     {
             printf("%c ",(unsigned char)*(data+i));
     }
     printf("\n");
}

//CONVERT ASCII: WORKING
//encrypt text: hex ascii code (in hex) * 4 (IN DEC) then back to hex = crypted
//decrypt: cryptd (in hex) / 4 (in dec) then back to hex = original ascii code


void encrypt(char *pData, unsigned short nLength) 
{
//INCOMPLETE, need to put spacing. like 01 01 -> 01 00 01 00
int i;
do {
*(unsigned short*)pData = *(unsigned short*)pData * 4; //ENCRYPT
hex_print(pData, 2);
ascii_print(pData, 1);
pData+=2;
i++;
} while (i < (nLength/2));
pData-=nLength;
hex_print(pData, nLength);
}


void decrypt(char *pData, unsigned short nLength) 
{
int i;
do {
*(unsigned short*)pData = *(unsigned short*)pData / 4; //DECRYPT
hex_print(pData, 2);
ascii_print(pData, 1);
pData+=2;
i++;
} while (i < (nLength/2));
pData-=nLength;
ascii_print(pData, nLength);
}

char crypted[] = {

};

char taf[] = {
0xD8, 0x00, 0xD0, 0x00, 0xB8, 
0x00, 0xCC, 0x00, 0xDC, 0x00, 0xB8, 0x00, 0xC4, 0x00, 0xDC, 0x00, 0xD8, 0x00, 0xB8, 0x00, 0xCC, 
0x00, 0xC8, 0x00, 
};

char test[] = "71.245.108.153";

int main() {
printf("crypt:\n");
decrypt(taf, sizeof(taf));
//encrypt(test, sizeof(test)); 
system("pause");
}


