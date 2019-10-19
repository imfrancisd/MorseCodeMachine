#include "MorseCodeMachine.h"

void sendMorse(const char message[], void (*dotDelayFunction)(), void (*dotFunction)(), void (*dashFunction)())
{
    #define DIT dotFunction(); dotDelayFunction();
    #define DAH dashFunction(); dotDelayFunction();

    while (*message != '\0')
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

            default:
                //Make everything else a delay between words.
                //7 delays total. 3 from previous letter, 2 from here, 2 at end of loop.
                dotDelayFunction();
                dotDelayFunction();
                break;
        }

        //Delay between digits and letters.
        //3 delays total. 1 from end of digit/letter, 2 from here.
        dotDelayFunction();
        dotDelayFunction();
        
        message++;
    }
}
