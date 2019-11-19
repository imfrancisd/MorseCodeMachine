//Basic tests for ../src/all/sendMorse.h.
//
//Compile with g++ and run:
//    g++ -o test.out test.cpp ../src/all/*.cpp
//    ./test.out
//
//Compile with cl.exe and run:
//    cl.exe /nologo /EHsc /Fetest.exe test.cpp ..\src\all\*.cpp
//    test.exe
//
//Compile with clang++ and run:
//    clang++ -o test.out test.cpp ../src/all/*.cpp
//    ./test.out

#include "../src/all/sendMorse.h"
#include <iostream>
#include <string>

namespace Machine1
{
    std::string out = "";
    void dly() {out.append(" ");}
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
        s->append(" ");
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
    int dly() {out.append(" "); return 0;}
    int dit() {out.append("*"); return 0;}
    int dah() {out.append("-"); return 0;}
    int dlyWithError() {out.append(" "); return 1;}
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
        s->append(" ");
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
        s->append(" ");
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

    const std::string ascii =
        "  "\
        "0123456789 "\
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ "\
        "abcdefghijklmnopqrstuvwxyz "\
        "<sos><3b><eeettteee> "\
        "<SOS> <3B> "\
        "Sos 3B "\
        "\"&'()+,-./:=?@ "\
        "01 2  1 "\
        "e ee  eee   e "\
        "< s o s ><  s  o  s  > "
        "< 3  b >  < 3  b > "\
        "Éé";

    const std::string morse =
        "              "\
        "- - - - -   * - - - -   * * - - -   * * * - -   * * * * -   "\
        "* * * * *   - * * * *   - - * * *   - - - * *   - - - - *       "\
        "* -   - * * *   - * - *   - * *   *   * * - *   - - *   * * * *   "\
        "* *   * - - -   - * -   * - * *   - -   - *   - - -   * - - *   "\
        "- - * -   * - *   * * *   -   * * -   * * * -   * - -   - * * -   "\
        "- * - -   - - * *       "\
        "* -   - * * *   - * - *   - * *   *   * * - *   - - *   * * * *   "\
        "* *   * - - -   - * -   * - * *   - -   - *   - - -   * - - *   "\
        "- - * -   * - *   * * *   -   * * -   * * * -   * - -   - * * -   "\
        "- * - -   - - * *       "\
        "* * * - - - * * *   * * * - - - * * *   * * * - - - * * *       "\
        "* * * - - - * * *       * * * - - - * * *       "\
        "* * *   - - -   * * *       * * * - -   - * * *       "\
        "* - * * - *   * - * * *   * - - - - *   - * - - *   - * - - * -   "\
        "* - * - *   - - * * - -   - * * * * -   * - * - * -   - * * - *   "\
        "- - - * * *   - * * * -   * * - - * *   * - - * - *       "\
        "- - - - -   * - - - -       * * - - -              * - - - -       "\
        "*       *   *              *   *   *                     *       "\
        "* * * - - - * * *   * * * - - - * * *       "\
        "* * * - - - * * *              * * * - - - * * *       "\
        "* * - * *   * * - * *       ";
}

int main(int, char **)
{
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
    std::cout << "Argmt 1: " << Test::ascii << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    sendMorse(Test::ascii.c_str(), Machine1::dly, Machine1::dit, Machine1::dah);
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
    std::cout << "Expect : * * * - - - * * *       " << std::endl;
    sendMorse("<sos>", Machine2::dly, Machine2::dit, Machine2::dah, NULL);
    std::cout << "Output : " << Machine2::outDefault << std::endl;
    Test::printResult(testId, Machine2::outDefault == "* * * - - - * * *       ");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: nullptr" << std::endl;
    std::cout << "Expect : * * * - - - * * *       " << std::endl;
    sendMorse("<sos>", Machine2::dly, Machine2::dit, Machine2::dah, nullptr);
    std::cout << "Output : " << Machine2::outDefault << std::endl;
    Test::printResult(testId, Machine2::outDefault == "* * * - - - * * *       ");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::ascii << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    sendMorse(Test::ascii.c_str(), Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
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
    std::cout << "Expect : * " << std::endl;
    Machine3::errorCode = sendMorse("s", Machine3::dlyWithError, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "* ");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == 1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: o" << std::endl;
    std::cout << "Expect : - " << std::endl;
    Machine3::errorCode = sendMorse("o", Machine3::dlyWithError, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "- ");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == 1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << std::endl;
    std::cout << "Expect :  " << std::endl;
    Machine3::errorCode = sendMorse(" ", Machine3::dlyWithError, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == " ");
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
    std::cout << "Expect : * * * -" << std::endl;
    Machine3::errorCode = sendMorse("<sos>", Machine3::dly, Machine3::dit, Machine3::dahWithError);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "* * * -");
    std::cout << "Expect : 3" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == 3);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::ascii << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    Machine3::errorCode = sendMorse(Test::ascii.c_str(), Machine3::dly, Machine3::dit, Machine3::dah);
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
    std::cout << "Expect : * * * - - - * * *       " << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::dit, Machine4::dah, NULL);
    std::cout << "Output : " << Machine4::outDefault << std::endl;
    Test::printResult(testId, Machine4::outDefault == "* * * - - - * * *       ");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 0);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: nullptr" << std::endl;
    std::cout << "Expect : * * * - - - * * *       " << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::dit, Machine4::dah, nullptr);
    std::cout << "Output : " << Machine4::outDefault << std::endl;
    Test::printResult(testId, Machine4::outDefault == "* * * - - - * * *       ");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 0);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: s" << std::endl;
    std::cout << "Expect : * " << std::endl;
    Machine4::errorCode = sendMorse("s", Machine4::dlyWithError, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "* ");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: o" << std::endl;
    std::cout << "Expect : - " << std::endl;
    Machine4::errorCode = sendMorse("o", Machine4::dlyWithError, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "- ");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << std::endl;
    std::cout << "Expect :  " << std::endl;
    Machine4::errorCode = sendMorse(" ", Machine4::dlyWithError, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == " ");
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
    std::cout << "Expect : * * * -" << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::dit, Machine4::dahWithError, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "* * * -");
    std::cout << "Expect : 3" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 3);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::ascii << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    Machine4::errorCode = sendMorse(Test::ascii.c_str(), Machine4::dly, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Test::morse == Machine4::out);
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 0);
    std::cout << std::endl;

    std::cout << "=======================" << std::endl;
    std::cout << "Summary of Test Results" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "Total Pass : " << Test::countPass << std::endl;
    std::cout << "Total Fail : " << Test::countFail << std::endl;
    std::cout << "=======================" << std::endl;

    return Test::countFail;
}

