//Basic tests for ../src/all/sendMorse.h.
//
//Compile with g++ and run:
//    g++ -o test.out test.cpp ../src/all/*.cpp
//    ./test.out
//
//Compile with cl.exe and run:
//    cl.exe /nologo /Ehsc /Fetest.exe test.cpp ..\src\all\*.cpp
//    test.exe

#include "../src/all/sendMorse.h"
#include <iostream>
#include <string>

namespace Machine1
{
    std::string out;
    void dly() {out.append(" ");}
    void dit() {out.append("*");}
    void dah() {out.append("-");}
}

namespace Machine2
{
    std::string out;
    void dly(void *context)
    {
        std::string *s = context ? (std::string *)context : &out;
        s->append(" ");
    }
    void dit(void *context)
    {
        std::string *s = context ? (std::string *)context : &out;
        s->append("*");
    }
    void dah(void *context)
    {
        std::string *s = context ? (std::string *)context : &out;
        s->append("-");
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
            std::cout << "Result : Pass" << std::endl << std::endl;
            countPass++;
        }
        else
        {
            std::cout << "Result : Fail" << std::endl;
            std::cerr << "-------- Fail Test " << testId << " --------" << std::endl;
            std::cout << std::endl;
            countFail++;
        }
    }

    const std::string ascii =
        "0123456789 "\
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ "\
        "abcdefghijklmnopqrstuvwxyz "\
        "<sos><3b><eeettteee> "\
        "<SOS> <3B> "\
        "Sos 3B "\
        "\"&'()+,-./:=?@";

    const std::string morse =
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
        "- - - * * *   - * * * -   * * - - * *   * - - * - *       ";
}

int main(int argc, char **argv)
{
    int testId = 0;

    std::cout << "Testing: void sendMorse(const char *, void (*)(), void (*)(), void (*)())" << std::endl;
    std::cout << std::endl;

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine1::out = "";
    sendMorse(NULL, Machine1::dly, Machine1::dit, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine1::out = "";
    sendMorse(nullptr, Machine1::dly, Machine1::dit, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine1::out = "";
    sendMorse("<sos>", nullptr, Machine1::dit, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 3: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine1::out = "";
    sendMorse("<sos>", Machine1::dly, nullptr, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 4: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine1::out = "";
    sendMorse("<sos>", Machine1::dly, Machine1::dit, nullptr);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::ascii << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    Machine1::out = "";
    sendMorse(Test::ascii.c_str(), Machine1::dly, Machine1::dit, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Test::morse == Machine1::out);

    std::cout << "Testing: void sendMorse(const char *, void (*)(void *), void (*)(void *), void (*)(void *), void *)" << std::endl;

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine2::out = "";
    sendMorse(NULL, Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine2::out = "";
    sendMorse(nullptr, Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine2::out = "";
    sendMorse("<sos>", nullptr, Machine2::dit, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 3: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine2::out = "";
    sendMorse("<sos>", Machine2::dly, nullptr, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 4: nullptr" << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine2::out = "";
    sendMorse("<sos>", Machine2::dly, Machine2::dit, nullptr, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: NULL" << std::endl;
    std::cout << "Expect : * * * - - - * * *       " << std::endl;
    Machine2::out = "";
    sendMorse("<sos>", Machine2::dly, Machine2::dit, Machine2::dah, NULL);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "* * * - - - * * *       ");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: nullptr" << std::endl;
    std::cout << "Expect : * * * - - - * * *       " << std::endl;
    Machine2::out = "";
    sendMorse("<sos>", Machine2::dly, Machine2::dit, Machine2::dah, nullptr);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "* * * - - - * * *       ");

    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::ascii << std::endl;
    std::cout << "Expect : " << Test::morse << std::endl;
    Machine2::out = "";
    sendMorse(Test::ascii.c_str(), Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Test::morse == Machine2::out);

    std::cout << "Pass : " << Test::countPass << std::endl;
    std::cout << "Fail : " << Test::countFail << std::endl;

    return Test::countFail;
}
