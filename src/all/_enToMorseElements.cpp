#include "_countUtf8Bytes.h"
#include "_enToMorseElements.h"
#include "_isDiacritic.h"
#include "_skipDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



unsigned int _enToMorseElements(char c)
{
    switch (c)
    {
        //Digits 0-9.

        case '0':
            //DAH DAH DAH DAH DAH
            return 0b1111100011111000;

        case '1':
            //DIT DAH DAH DAH DAH
            return 0b1111100001111000;

        case '2':
            //DIT DIT DAH DAH DAH
            return 0b1111100000111000;

        case '3':
            //DIT DIT DIT DAH DAH
            return 0b1111100000011000;

        case '4':
            //DIT DIT DIT DIT DAH
            return 0b1111100000001000;

        case '5':
            //DIT DIT DIT DIT DIT
            return 0b1111100000000000;

        case '6':
            //DAH DIT DIT DIT DIT
            return 0b1111100010000000;

        case '7':
            //DAH DAH DIT DIT DIT
            return 0b1111100011000000;

        case '8':
            //DAH DAH DAH DIT DIT
            return 0b1111100011100000;

        case '9':
            //DAH DAH DAH DAH DIT
            return 0b1111100011110000;

        //Letters A-z and a-z.

        case 'A':
        case 'a':
            //DIT DAH
            return 0b1100000001000000;

        case 'B':
        case 'b':
            //DAH DIT DIT DIT
            return 0b1111000010000000;

        case 'C':
        case 'c':
            //DAH DIT DAH DIT
            return 0b1111000010100000;

        case 'D':
        case 'd':
            //DAH DIT DIT
            return 0b1110000010000000;

        case 'E':
        case 'e':
            //DIT
            return 0b1000000000000000;

        case 'F':
        case 'f':
            //DIT DIT DAH DIT
            return 0b1111000000100000;

        case 'G':
        case 'g':
            //DAH DAH DIT
            return 0b1110000011000000;

        case 'H':
        case 'h':
            //DIT DIT DIT DIT
            return 0b1111000000000000;

        case 'I':
        case 'i':
            //DIT DIT
            return 0b1100000000000000;

        case 'J':
        case 'j':
            //DIT DAH DAH DAH
            return 0b1111000001110000;

        case 'K':
        case 'k':
            //DAH DIT DAH
            return 0b1110000010100000;

        case 'L':
        case 'l':
            //DIT DAH DIT DIT
            return 0b1111000001000000;

        case 'M':
        case 'm':
            //DAH DAH
            return 0b1100000011000000;

        case 'N':
        case 'n':
            //DAH DIT
            return 0b1100000010000000;

        case 'O':
        case 'o':
            //DAH DAH DAH
            return 0b1110000011100000;

        case 'P':
        case 'p':
            //DIT DAH DAH DIT
            return 0b1111000001100000;

        case 'Q':
        case 'q':
            //DAH DAH DIT DAH
            return 0b1111000011010000;

        case 'R':
        case 'r':
            //DIT DAH DIT
            return 0b1110000001000000;

        case 'S':
        case 's':
            //DIT DIT DIT
            return 0b1110000000000000;

        case 'T':
        case 't':
            //DAH
            return 0b1000000010000000;

        case 'U':
        case 'u':
            //DIT DIT DAH
            return 0b1110000000100000;

        case 'V':
        case 'v':
            //DIT DIT DIT DAH
            return 0b1111000000010000;

        case 'W':
        case 'w':
            //DIT DAH DAH
            return 0b1110000001100000;

        case 'X':
        case 'x':
            //DAH DIT DIT DAH
            return 0b1111000010010000;

        case 'Y':
        case 'y':
            //DAH DIT DAH DAH
            return 0b1111000010110000;

        case 'Z':
        case 'z':
            //DAH DAH DIT DIT
            return 0b1111000011000000;

        //Symbols.

        case '"':
            //DIT DAH DIT DIT DAH DIT
            return 0b1111110001001000;

        case '&':
            //DIT DAH DIT DIT DIT
            return 0b1111100001000000;

        case '\'':
            //DIT DAH DAH DAH DAH DIT
            return 0b1111110001111000;

        case '(':
            //DAH DIT DAH DAH DIT
            return 0b1111100010110000;

        case ')':
            //DAH DIT DAH DAH DIT DAH
            return 0b1111110010110100;

        case '+':
            //DIT DAH DIT DAH DIT
            return 0b1111100001010000;

        case ',':
            //DAH DAH DIT DIT DAH DAH
            return 0b1111110011001100;

        case '-':
            //DAH DIT DIT DIT DIT DAH
            return 0b1111110010000100;

        case '.':
            //DIT DAH DIT DAH DIT DAH
            return 0b1111110001010100;

        case '/':
            //DAH DIT DIT DAH DIT
            return 0b1111100010010000;

        case ':':
            //DAH DAH DAH DIT DIT DIT
            return 0b1111110011100000;

        case '=':
            //DAH DIT DIT DIT DAH
            return 0b1111100010001000;

        case '?':
            //DIT DIT DAH DAH DIT DIT
            return 0b1111110000110000;

        case '@':
            //DIT DAH DAH DIT DAH DIT
            return 0b1111110001101000;

        //Recognized characters that do not have Morse elements.

        case ' ':
            return 0x0020;

        case '<':
            return 0x003c;

        case '>':
            return 0x003e;

        //Unrecognized characters.

        default:
            return 0x0000;
    }
}

unsigned int _enToMorseElements(const char **bytes)
{
    unsigned int morseElements = 0;
    unsigned char countUtf8Bytes = _countUtf8Bytes(*bytes);

    if (countUtf8Bytes == 1)
    {
        if (!_isDiacritic((*bytes) + 1))
        {
            //Found ascii character followed by 0 diacritics.
            morseElements = _enToMorseElements((*bytes)[0]);
        }
        else if ((!_isDiacritic((*bytes) + 3)) &&
                 ((*bytes)[1] == '\xcc') &&
                 ((*bytes)[2] == '\x81') &&
                 (((*bytes)[0] == 'E') || ((*bytes)[0] == 'e')))
        {
            //Found E or e (U+0045 or U+0065) followed by acute (U+0301) and no other diacritics.
            morseElements = 0b1111100000100000;
        }
        else
        {
            //Found ascii character followed by 1 or more diacritics.
            morseElements = 0x0000;
        }
    }
    else if ((countUtf8Bytes == 2) &&
             (!_isDiacritic((*bytes) + 2)) &&
             ((*bytes)[0] == '\xc3') &&
             (((*bytes)[1] == '\x89') || ((*bytes)[1] == '\xa9')))
    {
        //Found E acute (U+00C9 or U+00E9) followed by 0 diacritics.
        morseElements = 0b1111100000100000;
    }
    else
    {
        //Found extended ascii character or error in UTF-8 encoding.
        //Found 2 byte, 3 byte, or 4 byte UTF-8 character which may be followed by diacritics.
        morseElements = 0x0000;
    }

    //Go to next UTF-8 character.
    (*bytes) += (countUtf8Bytes > 0) ? countUtf8Bytes : 1;

    //Skip diacritics only if valid UTF-8 character found.
    if (countUtf8Bytes > 0)
    {
        while (_skipDiacritic(bytes))
            ;
    }

    return morseElements;
}

