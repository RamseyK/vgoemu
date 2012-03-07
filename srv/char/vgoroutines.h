#ifndef VGOROUTINES_H
#define VGOROUTINES_H

class VGORoutines
{
public:
       void cryptASCII(char *text, unsigned short length); //encrypt ascii to vgo text
       void decryptASCII(char *text, unsigned short length); //decrypt vgo text to ascii
       void tospecialNum(unsigned char *num); //converts an int to vgo's population numbering
};

#endif
