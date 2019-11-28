//Basic tests for ../src/all/sendMorse.h.
//
//Compile with g++ and run:
//    g++ -o test.out test.cpp ../src/all/*.cpp
//    ./test.out
//    ./test.out "hello world"
//
//Compile with cl.exe and run:
//    cl.exe /nologo /EHsc /Fetest.exe test.cpp ..\src\all\*.cpp
//    test.exe
//    test.exe "hello world"
//
//Compile with clang++ and run:
//    clang++ -o test.out test.cpp ../src/all/*.cpp
//    ./test.out
//    ./test.out "hello world"

#include "../src/all/sendMorse.h"
#include "../src/all/convertMorseFromGreek.h"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>

namespace Machine1
{
    std::string out = "";
    void dly() {out.append(",");}
    void dit() {out.append("*");}
    void dah() {out.append("-");}
    void reset() {out = "";}
}

namespace Machine2
{
    std::string out = "";
    std::string outDefault = "";
    void dly(void *context)
    {
        std::string *s = context ? (std::string *)context : &outDefault;
        s->append(",");
    }
    void dit(void *context)
    {
        std::string *s = context ? (std::string *)context : &outDefault;
        s->append("*");
    }
    void dah(void *context)
    {
        std::string *s = context ? (std::string *)context : &outDefault;
        s->append("-");
    }
    void reset()
    {
        out = "";
        outDefault = "";
    }
}

namespace Machine3
{
    std::string out = "";
    int errorCode = -123;
    int dly() {out.append(","); return 0;}
    int dit() {out.append("*"); return 0;}
    int dah() {out.append("-"); return 0;}
    int dlyWithError() {out.append(","); return 1;}
    int ditWithError() {out.append("*"); return 2;}
    int dahWithError() {out.append("-"); return 3;}
    void reset()
    {
        out = "";
        errorCode = -123;
    }
}

namespace Machine4
{
    std::string out = "";
    std::string outDefault = "";
    int errorCode = -123;
    int dly(void *context)
    {
        std::string *s = context ? (std::string *)context : &outDefault;
        s->append(",");
        return 0;
    }
    int dit(void *context)
    {
        std::string *s = context ? (std::string *)context : &outDefault;
        s->append("*");
        return 0;
    }
    int dah(void *context)
    {
        std::string *s = context ? (std::string *)context : &outDefault;
        s->append("-");
        return 0;
    }
    int dlyWithError(void *context)
    {
        std::string *s = context ? (std::string *)context : &outDefault;
        s->append(",");
        return 1;
    }
    int ditWithError(void *context)
    {
        std::string *s = context ? (std::string *)context : &outDefault;
        s->append("*");
        return 2;
    }
    int dahWithError(void *context)
    {
        std::string *s = context ? (std::string *)context : &outDefault;
        s->append("-");
        return 3;
    }
    void reset()
    {
        out = "";
        outDefault = "";
        errorCode = -123;
    }
}

namespace Machine5
{
    const size_t outSize = 1024;
    char out[outSize];
    int errorCode = -123;
    void reset()
    {
        memset(out, '\0', outSize);
        errorCode = -123;
    }
}

namespace Test
{
    int countPass = 0;
    int countFail = 0;

    void printResult(int testId, bool pass)
    {
        if (pass)
        {
            std::cout << "Result : Pass" << std::endl;
            countPass++;
        }
        else
        {
            std::cout << "Result : Fail" << std::endl;
            std::cerr << "-------- Fail Test " << testId << " --------" << std::endl;
            countFail++;
        }
    }

    const std::string utf8 =
        "  "\
        "01234 "\
        "56789 "\
        "ABCDEFG "\
        "HIJKLMN "\
        "OPQRSTU "\
        "VWXYZ "\
        "abcdefg "\
        "hijklmn "\
        "opqrstu "\
        "vwxyz "\
        "<sos><3b><eeettteee> "\
        "<SOS> <3B> "\
        "Sos 3B "\
        "\"&'( "\
        ")+,- "\
        "./:= "\
        "?@ "\
        "01 2  1 "\
        "e ee  eee   e "\
        "< s o s ><  s  o  s  > "
        "< 3  b >  < 3  b > "\
        "\xc3\x89\xc3\xa9 "\
        "\xc3\x89\xcc\x81\xc3\xa9\xcc\x81 "\
        "E\xcc\x81""e\xcc\x81 "\
        "E\xcc\x81\xcc\xad""e\xcc\x81\xcc\xad "\
        "< \xc3\x89  \xc3\xA9 ><\xc3\x89\xc3\xa9> "\
        "< E\xcc\x81  e\xcc\x81 >""<E\xcc\x81""e\xcc\x81> "\
        "e\xc6\x8et e\xe2\x99\x9et e\xf0\x9f\x98\x80t "\
        "";

    const std::string morse =
        ",,,,,,,,,,,,,,"\
        "-,-,-,-,-,,,*,-,-,-,-,,,*,*,-,-,-,,,*,*,*,-,-,,,*,*,*,*,-,,,,,,,"\
        "*,*,*,*,*,,,-,*,*,*,*,,,-,-,*,*,*,,,-,-,-,*,*,,,-,-,-,-,*,,,,,,,"\
        "*,-,,,-,*,*,*,,,-,*,-,*,,,-,*,*,,,*,,,*,*,-,*,,,-,-,*,,,,,,,"\
        "*,*,*,*,,,*,*,,,*,-,-,-,,,-,*,-,,,*,-,*,*,,,-,-,,,-,*,,,,,,,"\
        "-,-,-,,,*,-,-,*,,,-,-,*,-,,,*,-,*,,,*,*,*,,,-,,,*,*,-,,,,,,,"\
        "*,*,*,-,,,*,-,-,,,-,*,*,-,,,-,*,-,-,,,-,-,*,*,,,,,,,"\
        "*,-,,,-,*,*,*,,,-,*,-,*,,,-,*,*,,,*,,,*,*,-,*,,,-,-,*,,,,,,,"\
        "*,*,*,*,,,*,*,,,*,-,-,-,,,-,*,-,,,*,-,*,*,,,-,-,,,-,*,,,,,,,"\
        "-,-,-,,,*,-,-,*,,,-,-,*,-,,,*,-,*,,,*,*,*,,,-,,,*,*,-,,,,,,,"\
        "*,*,*,-,,,*,-,-,,,-,*,*,-,,,-,*,-,-,,,-,-,*,*,,,,,,,"\
        "*,*,*,-,-,-,*,*,*,,,*,*,*,-,-,-,*,*,*,,,*,*,*,-,-,-,*,*,*,,,,,,,"\
        "*,*,*,-,-,-,*,*,*,,,,,,,*,*,*,-,-,-,*,*,*,,,,,,,"\
        "*,*,*,,,-,-,-,,,*,*,*,,,,,,,*,*,*,-,-,,,-,*,*,*,,,,,,,"\
        "*,-,*,*,-,*,,,*,-,*,*,*,,,*,-,-,-,-,*,,,-,*,-,-,*,,,,,,,"\
        "-,*,-,-,*,-,,,*,-,*,-,*,,,-,-,*,*,-,-,,,-,*,*,*,*,-,,,,,,,"\
        "*,-,*,-,*,-,,,-,*,*,-,*,,,-,-,-,*,*,*,,,-,*,*,*,-,,,,,,,"\
        "*,*,-,-,*,*,,,*,-,-,*,-,*,,,,,,,"\
        "-,-,-,-,-,,,*,-,-,-,-,,,,,,,*,*,-,-,-,,,,,,,,,,,,,,*,-,-,-,-,,,,,,,"\
        "*,,,,,,,*,,,*,,,,,,,,,,,,,,*,,,*,,,*,,,,,,,,,,,,,,,,,,,,,*,,,,,,,"\
        "*,*,*,-,-,-,*,*,*,,,*,*,*,-,-,-,*,*,*,,,,,,,"\
        "*,*,*,-,-,-,*,*,*,,,,,,,,,,,,,,*,*,*,-,-,-,*,*,*,,,,,,,"\
        "*,*,-,*,*,,,*,*,-,*,*,,,,,,,"\
        ",,,,,,,,,,,,,,,,,,,,,"\
        "*,*,-,*,*,,,*,*,-,*,*,,,,,,,"\
        ",,,,,,,,,,,,,,,,,,,,,"\
        "*,*,-,*,*,*,*,-,*,*,,,*,*,-,*,*,*,*,-,*,*,,,,,,,"\
        "*,*,-,*,*,*,*,-,*,*,,,*,*,-,*,*,*,*,-,*,*,,,,,,,"\
        "*,,,,,,,-,,,,,,,*,,,,,,,-,,,,,,,*,,,,,,,-,,,,,,,"\
        ",,,,,,,";

    const std::string greek =
        "0123456789 "\
        "\"&'()+,-./:=?@ "\
        "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz "\
        "<SOS> < S O  S> "\
        "E\xcc\x81""e\xcc\x81 "\
        "E\xcc\x81\xcc\xad""e\xcc\x81\xcc\xad "\
/*
        "ΑαΒβΓγΔδΕεΖζΗηΘθΙιΚκΛλΜμΝνΞξΟοΠπΡρΣςσΤτΥυΦφΧχΨψΩω "\
        "Χχ<Χχ> "\
*/
        "";

    const std::string greekToEnglish =
        "0123456789 "\
        "\"&'()+,-./:=?@ "\
        "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz "\
        "<SOS> < S O  S> "\
        "E\xcc\x81""E\xcc\x81 "\
        "   "\
/*
        "AABBGGDDEEZZHHCCIIKKLLMMNNXXOOPPRRSSSTTYYFF<MM><MM>QQWW "\
        "<MM><MM><MMMM> "\
*/
        "";
}

int main(int argc, char **argv)
{
    //Exploratory tests: input from command line.

    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            std::cout << "=======" << std::endl;
            std::cout << "Message" << std::endl;
            std::cout << "=======" << std::endl;
            std::cout << argv[i] << std::endl;
            std::cout << std::endl;

            std::cout << "=========================================================================" << std::endl;
            std::cout << "Testing: void sendMorse(const char *, void (*)(), void (*)(), void (*)())" << std::endl;
            std::cout << "=========================================================================" << std::endl;
            std::cout << std::endl;
            Machine1::reset();
            sendMorse(argv[i], Machine1::dly, Machine1::dit, Machine1::dah);
            std::cout << Machine1::out << std::endl;
            std::cout << std::endl;

            std::cout << "===================================================================================================" << std::endl;
            std::cout << "Testing: void sendMorse(const char *, void (*)(void *), void (*)(void *), void (*)(void *), void *)" << std::endl;
            std::cout << "===================================================================================================" << std::endl;
            std::cout << std::endl;
            Machine2::reset();
            sendMorse(argv[i], Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
            std::cout << Machine2::out << std::endl;
            std::cout << std::endl;

            std::cout << "=====================================================================" << std::endl;
            std::cout << "Testing: int sendMorse(const char *, int (*)(), int (*)(), int (*)())" << std::endl;
            std::cout << "=====================================================================" << std::endl;
            std::cout << std::endl;
            Machine3::reset();
            Machine3::errorCode = sendMorse(argv[i], Machine3::dly, Machine3::dit, Machine3::dah);
            std::cout << Machine3::out << std::endl;
            std::cout << Machine3::errorCode << std::endl;
            std::cout << std::endl;

            std::cout << "===============================================================================================" << std::endl;
            std::cout << "Testing: int sendMorse(const char *, int (*)(void *), int (*)(void *), int (*)(void *), void *)" << std::endl;
            std::cout << "===============================================================================================" << std::endl;
            std::cout << std::endl;
            Machine4::reset();
            Machine4::errorCode = sendMorse(argv[i], Machine4::dly, Machine4::dit, Machine4::dah, &Machine4::out);
            std::cout << Machine4::out << std::endl;
            std::cout << Machine4::errorCode << std::endl;
            std::cout << std::endl;

            std::cout << "================================================================" << std::endl;
            std::cout << "Testing: int convertMorseFromGreek(const char *, char *, size_t)" << std::endl;
            std::cout << "================================================================" << std::endl;
            std::cout << std::endl;
            Machine5::reset();
            Machine5::errorCode = convertMorseFromGreek(argv[i], Machine5::out, Machine5::outSize);
            std::cout << Machine5::out << std::endl;
            std::cout << Machine5::errorCode << std::endl;
            std::cout << std::endl;
        }

        return -1;
    }

    //Automated tests: no input from command line.

    int testId = 0;

    std::cout << "=========================================================================" << std::endl;
    std::cout << "Testing: void sendMorse(const char *, void (*)(), void (*)(), void (*)())" << std::endl;
    std::cout << "=========================================================================" << std::endl;
    std::cout << std::endl;

    Machine1::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse(NULL, Machine1::dly, Machine1::dit, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");
    std::cout << std::endl;

    Machine1::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse(nullptr, Machine1::dly, Machine1::dit, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");
    std::cout << std::endl;

    Machine1::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse("<sos>", nullptr, Machine1::dit, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");
    std::cout << std::endl;

    Machine1::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 3: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse("<sos>", Machine1::dly, nullptr, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");
    std::cout << std::endl;

    Machine1::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 4: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse("<sos>", Machine1::dly, Machine1::dit, nullptr);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");
    std::cout << std::endl;

    Machine1::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::utf8 << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    sendMorse(Test::utf8.c_str(), Machine1::dly, Machine1::dit, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Test::morse == Machine1::out);
    std::cout << std::endl;

    std::cout << "===================================================================================================" << std::endl;
    std::cout << "Testing: void sendMorse(const char *, void (*)(void *), void (*)(void *), void (*)(void *), void *)" << std::endl;
    std::cout << "===================================================================================================" << std::endl;
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse(NULL, Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse(nullptr, Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse("<sos>", nullptr, Machine2::dit, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 3: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse("<sos>", Machine2::dly, nullptr, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 4: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse("<sos>", Machine2::dly, Machine2::dit, nullptr, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: NULL" << std::endl;
    std::cout << "Expect : *,*,*,-,-,-,*,*,*,,,,,,," << std::endl;
    sendMorse("<sos>", Machine2::dly, Machine2::dit, Machine2::dah, NULL);
    std::cout << "Output : " << Machine2::outDefault << std::endl;
    Test::printResult(testId, Machine2::outDefault == "*,*,*,-,-,-,*,*,*,,,,,,,");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: nullptr" << std::endl;
    std::cout << "Expect : *,*,*,-,-,-,*,*,*,,,,,,," << std::endl;
    sendMorse("<sos>", Machine2::dly, Machine2::dit, Machine2::dah, nullptr);
    std::cout << "Output : " << Machine2::outDefault << std::endl;
    Test::printResult(testId, Machine2::outDefault == "*,*,*,-,-,-,*,*,*,,,,,,,");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::utf8 << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    sendMorse(Test::utf8.c_str(), Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Test::morse == Machine2::out);
    std::cout << std::endl;

    std::cout << "=====================================================================" << std::endl;
    std::cout << "Testing: int sendMorse(const char *, int (*)(), int (*)(), int (*)())" << std::endl;
    std::cout << "=====================================================================" << std::endl;
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine3::errorCode = sendMorse(NULL, Machine3::dly, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == -1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine3::errorCode = sendMorse(nullptr, Machine3::dly, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == -1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine3::errorCode = sendMorse("<sos>", nullptr, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == -1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 3: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine3::errorCode = sendMorse("<sos>", Machine3::dly, nullptr, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == -1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 4: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine3::errorCode = sendMorse("<sos>", Machine3::dly, Machine3::dit, nullptr);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == -1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: s" << std::endl;
    std::cout << "Expect : *," << std::endl;
    Machine3::errorCode = sendMorse("s", Machine3::dlyWithError, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "*,");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == 1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: o" << std::endl;
    std::cout << "Expect : -," << std::endl;
    Machine3::errorCode = sendMorse("o", Machine3::dlyWithError, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "-,");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == 1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << std::endl;
    std::cout << "Expect : ," << std::endl;
    Machine3::errorCode = sendMorse(" ", Machine3::dlyWithError, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == ",");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == 1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: <sos>" << std::endl;
    std::cout << "Expect : *" << std::endl;
    Machine3::errorCode = sendMorse("<sos>", Machine3::dly, Machine3::ditWithError, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "*");
    std::cout << "Expect : 2" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == 2);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: <sos>" << std::endl;
    std::cout << "Expect : *,*,*,-" << std::endl;
    Machine3::errorCode = sendMorse("<sos>", Machine3::dly, Machine3::dit, Machine3::dahWithError);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "*,*,*,-");
    std::cout << "Expect : 3" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == 3);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::utf8 << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    Machine3::errorCode = sendMorse(Test::utf8.c_str(), Machine3::dly, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Test::morse == Machine3::out);
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == 0);
    std::cout << std::endl;

    std::cout << "===============================================================================================" << std::endl;
    std::cout << "Testing: int sendMorse(const char *, int (*)(void *), int (*)(void *), int (*)(void *), void *)" << std::endl;
    std::cout << "===============================================================================================" << std::endl;
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine4::errorCode = sendMorse(NULL, Machine4::dly, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == -1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine4::errorCode = sendMorse(nullptr, Machine4::dly, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == -1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine4::errorCode = sendMorse("<sos>", nullptr, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == -1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 3: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, nullptr, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == -1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 4: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::dit, nullptr, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == -1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: NULL" << std::endl;
    std::cout << "Expect : *,*,*,-,-,-,*,*,*,,,,,,," << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::dit, Machine4::dah, NULL);
    std::cout << "Output : " << Machine4::outDefault << std::endl;
    Test::printResult(testId, Machine4::outDefault == "*,*,*,-,-,-,*,*,*,,,,,,,");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 0);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: nullptr" << std::endl;
    std::cout << "Expect : *,*,*,-,-,-,*,*,*,,,,,,," << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::dit, Machine4::dah, nullptr);
    std::cout << "Output : " << Machine4::outDefault << std::endl;
    Test::printResult(testId, Machine4::outDefault == "*,*,*,-,-,-,*,*,*,,,,,,,");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 0);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: s" << std::endl;
    std::cout << "Expect : *," << std::endl;
    Machine4::errorCode = sendMorse("s", Machine4::dlyWithError, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "*,");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: o" << std::endl;
    std::cout << "Expect : -," << std::endl;
    Machine4::errorCode = sendMorse("o", Machine4::dlyWithError, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "-,");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << std::endl;
    std::cout << "Expect : ," << std::endl;
    Machine4::errorCode = sendMorse(" ", Machine4::dlyWithError, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == ",");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: <sos>" << std::endl;
    std::cout << "Expect : *" << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::ditWithError, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "*");
    std::cout << "Expect : 2" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 2);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: <sos>" << std::endl;
    std::cout << "Expect : *,*,*,-" << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::dit, Machine4::dahWithError, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "*,*,*,-");
    std::cout << "Expect : 3" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 3);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::utf8 << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    Machine4::errorCode = sendMorse(Test::utf8.c_str(), Machine4::dly, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Test::morse == Machine4::out);
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 0);
    std::cout << std::endl;

    std::cout << "================================================================" << std::endl;
    std::cout << "Testing: int convertMorseFromGreek(const char *, char *, size_t)" << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek(NULL, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek(nullptr, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek("", NULL, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek("", nullptr, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 3: 0"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek("", Machine5::out, 0);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::greek << std::endl;
    std::cout << "Expect : " << Test::greekToEnglish << std::endl;
    Machine5::errorCode = convertMorseFromGreek(Test::greek.c_str(), Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == Test::greekToEnglish);
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    std::cout << "=======================" << std::endl;
    std::cout << "Summary of Test Results" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "Total Pass : " << Test::countPass << std::endl;
    std::cout << "Total Fail : " << Test::countFail << std::endl;
    std::cout << "=======================" << std::endl;

    return Test::countFail;
}

