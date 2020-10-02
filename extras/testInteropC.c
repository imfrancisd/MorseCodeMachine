//C interoperability tests for MorseCodeMachine.h.
//
//    ** TEST PASSES WHEN **
//    ** Program compiles and runs. **
//
//Compile ../src/all/
//    g++ -c ../src/all/*.cpp
//    mkdir all/
//    mv *.o all/
//
//Compile ../src/arduino/
//    g++ -c ../src/arduino/*.cpp
//    mkdir arduino/
//    mv *.o arduino/
//
//Compile testInteropC.c
//    # telling the compiler and linker to remove unused functions.
//    gcc -fdata-sections -ffunction-sections -o testInteropC.out testInteropC.c all/*.o arduino/*.o -Wl,--gc-sections

#include "../src/MorseCodeMachine.h"
#include <stdio.h>

int dly(void *context)
{
    (void)(context);
    printf(" ");
    return 0;
}

int dit(void *context)
{
    (void)(context);
    printf(".");
    return 0;
}

int dah(void *context)
{
    (void)(context);
    printf("_");
    return 0;
}

int main()
{
    int errorCode = 0;
    size_t bufferSize = 100;
    char buffer[bufferSize];

    errorCode = sendMorse("Hello World!", dly, dit, dah, NULL);
    printf("\n%d\n", errorCode);
    errorCode = convertMorseFromGreek("γεια World!", buffer, bufferSize);
    printf("%s\n%d\n", buffer, errorCode);
    errorCode = convertMorseFromHebrew("שלום World!", buffer, bufferSize);
    printf("%s\n%d\n", buffer, errorCode);
    errorCode = convertMorseFromArabic("مرحبا World!", buffer, bufferSize);
    printf("%s\n%d\n", buffer, errorCode);
    errorCode = convertMorseFromPersian("سلام World!", buffer, bufferSize);
    printf("%s\n%d\n", buffer, errorCode);
    errorCode = convertMorseFromRussian("Здравствуй World!", buffer, bufferSize);
    printf("%s\n%d\n", buffer, errorCode);

    return 0;
}

