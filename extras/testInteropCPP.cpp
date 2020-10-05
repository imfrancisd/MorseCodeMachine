//C++ std::string interoperability tests for MorseCodeMachine.h.
//
//    ** TEST PASSES WHEN **
//    ** Program compiles and runs. **
//
//Compile testInteropCPP.cpp and run:
//    g++ -o testInteropCPP.out testInteropCPP.cpp ../src/all/*.cpp ../src/arduino/*.cpp
//    ./testInteropCPP.out

#include "../src/MorseCodeMachine.h"
#include <iostream>
#include <string>

using namespace std;

void dly1()
{
    cout << " ";
}

void dit1()
{
    cout << ".";
}

void dah1()
{
    cout << "_";
}

void dly2(void *)
{
    cout << " ";
}

void dit2(void *)
{
    cout << ".";
}

void dah2(void *)
{
    cout << "_";
}

int dly3()
{
    cout << " ";
    return 0;
}

int dit3()
{
    cout << ".";
    return 0;
}

int dah3()
{
    cout << "_";
    return 0;
}

int dly4(void *)
{
    cout << " ";
    return 0;
}

int dit4(void *)
{
    cout << ".";
    return 0;
}

int dah4(void *)
{
    cout << "_";
    return 0;
}

int main()
{
    int errorCode = 0;
    const size_t bufferSize = 100;
    char buffer[bufferSize];

    string messageEnglish = "Hello World!";
    string messageGreek = "γεια World!";
    string messageHebrew = "שלום World!";
    string messageArabic = "مرحبا World!";
    string messagePersian = "سلام World!";
    string messageRussian = "Здравствуй World!";

    sendMorse(messageEnglish, dly1, dit1, dah1);
    cout << endl;
    sendMorse(&messageEnglish, dly1, dit1, dah1);
    cout << endl;

    sendMorse(messageEnglish, dly2, dit2, dah2, nullptr);
    cout << endl;
    sendMorse(&messageEnglish, dly2, dit2, dah2, nullptr);
    cout << endl;

    errorCode = sendMorse(messageEnglish, dly3, dit3, dah3);
    cout << endl << errorCode << endl;
    errorCode = sendMorse(&messageEnglish, dly3, dit3, dah3);
    cout << endl << errorCode << endl;

    errorCode = sendMorse(messageEnglish, dly4, dit4, dah4, nullptr);
    cout << endl << errorCode << endl;
    errorCode = sendMorse(&messageEnglish, dly4, dit4, dah4, nullptr);
    cout << endl << errorCode << endl;

    errorCode = convertMorseFromGreek(messageGreek, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;
    errorCode = convertMorseFromGreek(&messageGreek, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;

    errorCode = convertMorseFromHebrew(messageHebrew, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;
    errorCode = convertMorseFromHebrew(&messageHebrew, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;

    errorCode = convertMorseFromArabic(messageArabic, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;
    errorCode = convertMorseFromArabic(&messageArabic, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;

    errorCode = convertMorseFromPersian(messagePersian, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;
    errorCode = convertMorseFromPersian(&messagePersian, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;

    errorCode = convertMorseFromRussian(messageRussian, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;
    errorCode = convertMorseFromRussian(&messageRussian, buffer, bufferSize);
    cout << buffer << endl << errorCode << endl;

    return 0;
}

