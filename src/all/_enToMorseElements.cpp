#include "_countUtf8Bytes.h"
#include "_enToMorseElements.h"
#include "_isDiacritic.h"
#include "_skipDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
unsigned int _enToMorseElements(char c)
{
    //ASCII characters are Unicode code points U+0000 - U+007F.
    unsigned char unicode = 0xff & c;

    //Convert lowercase (a-z) to uppercase (A-Z).
    //Uppercase (U+0041 - U+005A)
    //Lowercase (U+0061 - U+007A)
    if ((0x61 <= unicode) && (unicode <= 0x7a))
    {
        unicode -= 0x20;
    }

    switch (unicode)
    {
        //Digits 0-9.

        case 0x30:
            //0 -> DAH DAH DAH DAH DAH
            return 0b1111100011111000;

        case 0x31:
            //1 -> DIT DAH DAH DAH DAH
            return 0b1111100001111000;

        case 0x32:
            //2 -> DIT DIT DAH DAH DAH
            return 0b1111100000111000;

        case 0x33:
            //3 -> DIT DIT DIT DAH DAH
            return 0b1111100000011000;

        case 0x34:
            //4 -> DIT DIT DIT DIT DAH
            return 0b1111100000001000;

        case 0x35:
            //5 -> DIT DIT DIT DIT DIT
            return 0b1111100000000000;

        case 0x36:
            //6 -> DAH DIT DIT DIT DIT
            return 0b1111100010000000;

        case 0x37:
            //7 -> DAH DAH DIT DIT DIT
            return 0b1111100011000000;

        case 0x38:
            //8 -> DAH DAH DAH DIT DIT
            return 0b1111100011100000;

        case 0x39:
            //9 -> DAH DAH DAH DAH DIT
            return 0b1111100011110000;

        //Letters A-Z.

        case 0x41:
            //A -> DIT DAH
            return 0b1100000001000000;

        case 0x42:
            //B -> DAH DIT DIT DIT
            return 0b1111000010000000;

        case 0x43:
            //C -> DAH DIT DAH DIT
            return 0b1111000010100000;

        case 0x44:
            //D -> DAH DIT DIT
            return 0b1110000010000000;

        case 0x45:
            //E -> DIT
            return 0b1000000000000000;

        case 0x46:
            //F -> DIT DIT DAH DIT
            return 0b1111000000100000;

        case 0x47:
            //G -> DAH DAH DIT
            return 0b1110000011000000;

        case 0x48:
            //H -> DIT DIT DIT DIT
            return 0b1111000000000000;

        case 0x49:
            //I -> DIT DIT
            return 0b1100000000000000;

        case 0x4a:
            //J -> DIT DAH DAH DAH
            return 0b1111000001110000;

        case 0x4b:
            //K -> DAH DIT DAH
            return 0b1110000010100000;

        case 0x4c:
            //L -> DIT DAH DIT DIT
            return 0b1111000001000000;

        case 0x4d:
            //M -> DAH DAH
            return 0b1100000011000000;

        case 0x4e:
            //N -> DAH DIT
            return 0b1100000010000000;

        case 0x4f:
            //O -> DAH DAH DAH
            return 0b1110000011100000;

        case 0x50:
            //P -> DIT DAH DAH DIT
            return 0b1111000001100000;

        case 0x51:
            //Q -> DAH DAH DIT DAH
            return 0b1111000011010000;

        case 0x52:
            //R -> DIT DAH DIT
            return 0b1110000001000000;

        case 0x53:
            //S -> DIT DIT DIT
            return 0b1110000000000000;

        case 0x54:
            //T -> DAH
            return 0b1000000010000000;

        case 0x55:
            //U -> DIT DIT DAH
            return 0b1110000000100000;

        case 0x56:
            //V -> DIT DIT DIT DAH
            return 0b1111000000010000;

        case 0x57:
            //W -> DIT DAH DAH
            return 0b1110000001100000;

        case 0x58:
            //X -> DAH DIT DIT DAH
            return 0b1111000010010000;

        case 0x59:
            //Y -> DAH DIT DAH DAH
            return 0b1111000010110000;

        case 0x5a:
            //Z -> DAH DAH DIT DIT
            return 0b1111000011000000;

        //Symbols.

        case 0x22:
            //" -> DIT DAH DIT DIT DAH DIT
            return 0b1111110001001000;

        case 0x26:
            //& -> DIT DAH DIT DIT DIT
            return 0b1111100001000000;

        case 0x27:
            //' -> DIT DAH DAH DAH DAH DIT
            return 0b1111110001111000;

        case 0x28:
            //( -> DAH DIT DAH DAH DIT
            return 0b1111100010110000;

        case 0x29:
            //) -> DAH DIT DAH DAH DIT DAH
            return 0b1111110010110100;

        case 0x2b:
            //+ -> DIT DAH DIT DAH DIT
            return 0b1111100001010000;

        case 0x2c:
            //, -> DAH DAH DIT DIT DAH DAH
            return 0b1111110011001100;

        case 0x2d:
            //- -> DAH DIT DIT DIT DIT DAH
            return 0b1111110010000100;

        case 0x2e:
            //. -> DIT DAH DIT DAH DIT DAH
            return 0b1111110001010100;

        case 0x2f:
            /// -> DAH DIT DIT DAH DIT
            return 0b1111100010010000;

        case 0x3a:
            //: -> DAH DAH DAH DIT DIT DIT
            return 0b1111110011100000;

        case 0x3d:
            //= -> DAH DIT DIT DIT DAH
            return 0b1111100010001000;

        case 0x3f:
            //? -> DIT DIT DAH DAH DIT DIT
            return 0b1111110000110000;

        case 0x40:
            //@ -> DIT DAH DAH DIT DAH DIT
            return 0b1111110001101000;

        //Recognized characters that do not have Morse elements.

        case 0x20: // 
        case 0x3c: //<
        case 0x3e: //>
            return unicode;

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
                 (((*bytes)[0] == '\x45') || ((*bytes)[0] == '\x65')))
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
}

