#include "MorseCodeMachine.h"

void sendMorse(const char message[], void (*dotDelayFunction)(), void (*dotFunction)(), void (*dashFunction)())
{
    #define DIT dotFunction(); dotDelayFunction();
    #define DAH dashFunction(); dotDelayFunction();

    bool hasLetterSpacing = true;

    while (1)
    {
        switch (*message)
        {
            case '0':
                DAH DAH DAH DAH DAH;
                break;

            case '1':
                DIT DAH DAH DAH DAH;
                break;

            case '2':
                DIT DIT DAH DAH DAH;
                break;

            case '3':
                DIT DIT DIT DAH DAH;
                break;

            case '4':
                DIT DIT DIT DIT DAH;
                break;

            case '5':
                DIT DIT DIT DIT DIT;
                break;

            case '6':
                DAH DIT DIT DIT DIT;
                break;

            case '7':
                DAH DAH DIT DIT DIT;
                break;

            case '8':
                DAH DAH DAH DIT DIT;
                break;

            case '9':
                DAH DAH DAH DAH DIT;
                break;

            case 'A':
            case 'a':
                DIT DAH;
                break;

            case 'B':
            case 'b':
                DAH DIT DIT DIT;
                break;

            case 'C':
            case 'c':
                DAH DIT DAH DIT;
                break;

            case 'D':
            case 'd':
                DAH DIT DIT;
                break;

            case 'E':
            case 'e':
                DIT;
                break;

            case 'F':
            case 'f':
                DIT DIT DAH DIT;
                break;

            case 'G':
            case 'g':
                DAH DAH DIT;
                break;

            case 'H':
            case 'h':
                DIT DIT DIT DIT;
                break;

            case 'I':
            case 'i':
                DIT DIT;
                break;

            case 'J':
            case 'j':
                DIT DAH DAH DAH;
                break;

            case 'K':
            case 'k':
                DAH DIT DAH;
                break;

            case 'L':
            case 'l':
                DIT DAH DIT DIT;
                break;

            case 'M':
            case 'm':
                DAH DAH;
                break;

            case 'N':
            case 'n':
                DAH DIT;
                break;

            case 'O':
            case 'o':
                DAH DAH DAH;
                break;

            case 'P':
            case 'p':
                DIT DAH DAH DIT;
                break;

            case 'Q':
            case 'q':
                DAH DAH DIT DAH;
                break;

            case 'R':
            case 'r':
                DIT DAH DIT;
                break;

            case 'S':
            case 's':
                DIT DIT DIT;
                break;

            case 'T':
            case 't':
                DAH;
                break;

            case 'U':
            case 'u':
                DIT DIT DAH;
                break;

            case 'V':
            case 'v':
                DIT DIT DIT DAH;
                break;

            case 'W':
            case 'w':
                DIT DAH DAH;
                break;

            case 'X':
            case 'x':
                DAH DIT DIT DAH;
                break;

            case 'Y':
            case 'y':
                DAH DIT DAH DAH;
                break;

            case 'Z':
            case 'z':
                DAH DAH DIT DIT;
                break;

            case '<':
                hasLetterSpacing = false;
                break;

            case '>':
                hasLetterSpacing = true;
                break;

            default:
                //Make everything else a delay between words, including the '\0'.
                //7 delays total. 3 from previous letter, 2 from here, 2 at end of loop.
                dotDelayFunction();
                dotDelayFunction();
                break;
        }

        if (hasLetterSpacing)
        {
            //Delay between digits and letters.
            //3 delays total. 1 from end of digit/letter, 2 from here.
            dotDelayFunction();
            dotDelayFunction();
        }

        if (*message == '\0')
        {
            break;
        }
        
        message++;
    }
}
