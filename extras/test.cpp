//Basic tests for MorseCodeMachine.h.
//
//Compile with g++ and run:
//    g++ -o test.out test.cpp ../src/all/*.cpp ../src/arduino/*.cpp
//    ./test.out
//    ./test.out "hello world"
//
//Compile with cl.exe and run:
//    cl.exe /nologo /EHsc /Fetest.exe test.cpp ..\src\all\*.cpp ..\src\arduino\*.cpp
//    test.exe
//    test.exe "hello world"
//
//Compile with clang++ and run:
//    clang++ -o test.out test.cpp ../src/all/*.cpp ../src/arduino/*.cpp
//    ./test.out
//    ./test.out "hello world"

#include "../src/MorseCodeMachine.h"
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
        memset(out, '?', outSize);
        out[0] = '\0';
        out[outSize - 1] = '\0';
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
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "\xc3\x89\xcc\x81\xc3\xa9\xcc\x81 "\
        "E\xcc\x81""e\xcc\x81 "\
        "E\xcc\x81\xcc\xad""e\xcc\x81\xcc\xad "\
        "< \xc3\x89  \xc3\xA9 ><\xc3\x89\xc3\xa9> "\
        "< E\xcc\x81  e\xcc\x81 >""<E\xcc\x81""e\xcc\x81> "\
        "A\xcc\x81""a\xcc\x81 "\
        "A\xcc\x81\xcc\xad""a\xcc\x81\xcc\xad "\
        "\xce\xb1\xcc\x81""\xce\xb1\xcc\x81\xcc\xad "\
        "e\xc6\x8et e\xe2\x99\x9et e\xf0\x9f\x98\x80t "\
        "\xef\xbf\xbd "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
/*
*/
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
        "*,*,*,-,-,-,*,*,*,,,*,*,*,-,-,-,*,*,*,,,*,*,*,-,-,-,*,*,*,,,,,,,"\
        "*,*,-,*,*,,,*,*,-,*,*,,,,,,,"\
        ",,,,,,,,,,,,,,,,,,,,,"\
        "*,*,-,*,*,,,*,*,-,*,*,,,,,,,"\
        ",,,,,,,,,,,,,,,,,,,,,"\
        "*,*,-,*,*,*,*,-,*,*,,,*,*,-,*,*,*,*,-,*,*,,,,,,,"\
        "*,*,-,*,*,*,*,-,*,*,,,*,*,-,*,*,*,*,-,*,*,,,,,,,"\
        ",,,,,,,,,,,,,,,,,,,,,"\
        ",,,,,,,,,,,,,,,,,,,,,"\
        ",,,,,,,,,,,,,,,,,,,,,"\
        "*,,,,,,,-,,,,,,,*,,,,,,,-,,,,,,,*,,,,,,,-,,,,,,,"\
        ",,,,,,,,,,,,,,"\
        "*,-,-,*,-,,,*,-,-,*,-,,,*,-,-,*,-,,,*,-,-,*,-,,,,,,,"\
        "*,-,*,-,,,*,-,*,-,,,*,-,*,-,,,*,-,*,-,,,,,,,"\
        "*,-,-,*,-,,,*,-,-,*,-,,,*,-,-,*,-,,,*,-,-,*,-,,,,,,,"\
        "*,-,*,-,,,*,-,*,-,,,*,-,*,-,,,*,-,*,-,,,,,,,"\
        "*,-,*,-,,,*,-,*,-,,,,,,,"\
        "-,*,-,*,*,,,-,*,-,*,*,,,-,*,-,*,*,,,-,*,-,*,*,,,,,,,"\
        "-,*,-,*,*,,,-,*,-,*,*,,,-,*,-,*,*,,,-,*,-,*,*,,,,,,,"\
        "-,*,-,*,*,,,-,*,-,*,*,,,-,*,-,*,*,,,-,*,-,*,*,,,,,,,"\
        "*,*,-,*,*,,,*,*,-,*,*,,,,,,,"\
        "*,*,-,-,*,,,*,*,-,-,*,,,,,,,"\
        "*,*,-,*,*,,,*,*,-,*,*,,,*,*,-,*,*,,,*,*,-,*,*,,,,,,,"\
        "*,-,*,*,-,,,*,-,*,*,-,,,*,-,*,*,-,,,*,-,*,*,-,,,,,,,"\
        "*,*,-,*,*,,,*,*,-,*,*,,,*,*,-,*,*,,,*,*,-,*,*,,,,,,,"\
        "-,-,*,-,*,,,-,-,*,-,*,,,-,-,*,-,*,,,-,-,*,-,*,,,,,,,"\
        "-,-,-,-,,,-,-,-,-,,,-,-,-,-,,,-,-,-,-,,,,,,,"\
        "*,-,-,-,*,,,*,-,-,-,*,,,*,-,-,-,*,,,*,-,-,-,*,,,,,,,"\
        "*,-,*,*,-,,,*,-,*,*,-,,,,,,,"\
        "-,-,*,-,-,,,-,-,*,-,-,,,-,-,*,-,-,,,-,-,*,-,-,,,,,,,"\
        "-,-,*,-,-,,,-,-,*,-,-,,,-,-,*,-,-,,,-,-,*,-,-,,,,,,,"\
        "-,-,-,*,,,-,-,-,*,,,-,-,-,*,,,-,-,-,*,,,,,,,"\
        "-,-,-,*,,,-,-,-,*,,,-,-,-,*,,,-,-,-,*,,,,,,,"\
        "-,-,-,*,,,-,-,-,*,,,,,,,"\
        "*,*,*,-,*,*,*,,,*,*,*,-,*,*,*,,,*,*,*,-,*,*,*,,,*,*,*,-,*,*,*,,,,,,,"\
        "*,*,*,-,*,,,*,*,*,-,*,,,*,*,*,-,*,,,*,*,*,-,*,,,,,,,"\
        "-,-,-,-,,,-,-,-,-,,,-,-,-,-,,,-,-,-,-,,,,,,,"\
        "*,-,-,*,*,,,*,-,-,*,*,,,,,,,"\
        "*,*,-,-,,,*,*,-,-,,,*,*,-,-,,,*,*,-,-,,,,,,,"\
        "*,*,-,-,,,*,*,-,-,,,*,*,-,-,,,*,*,-,-,,,,,,,"\
        "-,-,*,*,-,*,,,-,-,*,*,-,*,,,-,-,*,*,-,*,,,-,-,*,*,-,*,,,,,,,"\
        "-,-,*,*,-,,,-,-,*,*,-,,,-,-,*,*,-,,,-,-,*,*,-,,,,,,,"\
/*
*/
        ",,,,,,,";

    const std::string greek =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        "\"&'()+,-./:=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "ΑαΒβΓγΔδΕεΖζΗηΘθΙιΚκΛλΜμΝνΞξΟοΠπΡρΣςσΤτΥυΦφΧχΨψΩω "\
        "Χχ<Χχ> "\
        "\xe1\xbc\x87 \xcf\xaf \xce\xb1\xcc\x81 "\
        "\xce\x90 \xce\xaa "\
        "\xce\xb0 \xcf\x8a "\
        "e\xc4\x80t "\
        "e\xdf\x99t "\
        "e\xc6\x8et "\
        "e\xe2\x99\x9et "\
        "e\xf0\x9f\x98\x80t "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
        "";

    const std::string greekToEnglish =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        "\"&'()+,-./:=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "AABBGGDDEEZZHHCCIIKKLLMMNNXXOOPPRRSSSTTYYFF<MM><MM>QQWW "\
        "<MM><MM><<MM><MM>> "\
        "\xef\xbf\xbd \xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
        "";

    const std::string hebrew =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        "\"&'()+,-./:=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "אבגדהוזחטיכלמנסעפצקרשת "\
        "ךכ םמ ןנ ףפ ץצ "\
        "<שהש> < ש ה ש > <ש<הש>> "\
        "\xe1\xbc\x87 \xcf\xaf \xce\xb1\xcc\x81 "\
        "\xce\x90 \xce\xaa "\
        "\xce\xb0 \xcf\x8a "\
        "e\xc4\x80t "\
        "e\xdf\x99t "\
        "e\xc6\x8et "\
        "e\xe2\x99\x9et "\
        "e\xf0\x9f\x98\x80t "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
        "";

    const std::string hebrewToEnglish =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        "\"&'()+,-./:=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "ABGDOEZHUIKLMNCJPWQRST "\
        "KK MM NN PP WW "\
        "<SOS> < S O S > <S<OS>> "\
        "\xef\xbf\xbd \xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
        "";

    const std::string arabic =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        "\"&'()+,-./:=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "ا ب ت ث ج ح خ د ذ ر ز س ش ص ض ط ظ ع غ ف ق ك ل م ن ه و ي ﺀ "\
        "<زشعه> <سخس> <س<خس>> "\
        "\xe1\xbc\x87 \xcf\xaf \xce\xb1\xcc\x81 "\
        "\xce\x90 \xce\xaa "\
        "\xce\xb0 \xcf\x8a "\
        "e\xc4\x80t "\
        "e\xdf\x99t "\
        "e\xc6\x8et "\
        "e\xe2\x99\x9et "\
        "e\xf0\x9f\x98\x80t "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
        "";

    const std::string arabicToEnglish =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        "\"&'()+,-./:=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "A B T C J H O D Z R <OE> S <MM> X V U Y <AA> G F Q K L M N <FE> W I E "
        "<<OE><MM><AA><FE>> <SOS> <S<OS>> "\
        "\xef\xbf\xbd \xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
        "";

    const std::string persian =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        "\"&'()+,-./:=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "ا ب پ ت ث ج چ ح خ د ذ ر ز ژ س ش ص ض ط ظ ع غ ف ق ک گ ل م ن و ه ی "\
        "<سعس> <س <عس>> <چ ش ص ض غ ق> "\
        "\xe1\xbc\x87 \xcf\xaf \xce\xb1\xcc\x81 "\
        "\xce\x90 \xce\xaa "\
        "\xce\xb0 \xcf\x8a "\
        "e\xc4\x80t "\
        "e\xdf\x99t "\
        "e\xc6\x8et "\
        "e\xe2\x99\x9et "\
        "e\xf0\x9f\x98\x80t "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
        "";

    const std::string persianToEnglish =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        "\"&'()+,-./:=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "A B P T C J <OE> H X D V R Z G S <MM> <AA> <FE> U Y O <IM> F <OS> K Q L M N W E I "\
        "<SOS> <S <OS>> <<OE> <MM> <AA> <FE> <IM> <OS>> "\
        "\xef\xbf\xbd \xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
        "";

    const std::string russian =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        "!\"&'()+,-./:;=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "АаБбВвГгДдЕеЖжЗзИиЙйКкЛлМмНнОоПп "\
        "РрСсТтУуФфХхЦцЧчШшЩщЬьЫыЭэЮюЯя "\
        "<СОС> <С<ОС>> <ЧШЭЮЯ> "\
        "\xe1\xbc\x87 \xcf\xaf \xce\xb1\xcc\x81 "\
        "\xce\x90 \xce\xaa "\
        "\xce\xb0 \xcf\x8a "\
        "e\xc4\x80t "\
        "e\xdf\x99t "\
        "e\xc6\x8et "\
        "e\xe2\x99\x9et "\
        "e\xf0\x9f\x98\x80t "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
        "";

    const std::string russianToEnglish =
        "  "\
        "01234 56789 "\
        "ABCDEFG HIJKLMN OPQRSTU VWXYZ "\
        "abcdefg hijklmn opqrstu vwxyz "\
        "<sos><3b><eeettteee> <SOS> <3B> Sos 3B "\
        ",\"&'))+.=<5E>/:<CT>=?@ "\
        "01 2  1 e ee  eee   e "\
        "< s o s ><  s  o  s  > < 3  b >  < 3  b > "\
        "<<3b>><s<os>><e<e e<t> t t  >e e e> "\
        "\xc3\x89\xc3\xa9 "\
        "E\xcc\x81""e\xcc\x81 "\
        "AABBWWGGDDEEVVZZIIJJKKLLMMNNOOPP "\
        "RRSSTTUUFFHHCC<OE><OE><MM><MM>QQXXYY<FE><FE><IM><IM><AA><AA> "\
        "<SOS> <S<OS>> <<OE><MM><FE><IM><AA>> "\
        "\xef\xbf\xbd \xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "\xef\xbf\xbd \xef\xbf\xbd "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "e\xef\xbf\xbdt "\
        "Àà""A\xcc\x80""a\xcc\x80 "\
        "Ää""A\xcc\x88""a\xcc\x88 "\
        "Åå""A\xcc\x8a""a\xcc\x8a "\
        "Ąą""A\xcc\xa8""a\xcc\xa8 "\
        "Ææ "\
        "Ćć""C\xcc\x81""c\xcc\x81 "\
        "Ĉĉ""C\xcc\x82""c\xcc\x82 "\
        "Çç""C\xcc\xa7""c\xcc\xa7 "\
        "Đđ "\
        "Ðð "\
        "Éé""E\xcc\x81""e\xcc\x81 "\
        "Èè""E\xcc\x80""e\xcc\x80 "\
        "Ęę""E\xcc\xa8""e\xcc\xa8 "\
        "Ĝĝ""G\xcc\x82""g\xcc\x82 "\
        "Ĥĥ""H\xcc\x82""h\xcc\x82 "\
        "Ĵĵ""J\xcc\x82""j\xcc\x82 "\
        "Łł "\
        "Ńń""N\xcc\x81""n\xcc\x81 "\
        "Ññ""N\xcc\x83""n\xcc\x83 "\
        "Óó""O\xcc\x81""o\xcc\x81 "\
        "Öö""O\xcc\x88""o\xcc\x88 "\
        "Øø "\
        "Śś""S\xcc\x81""s\xcc\x81 "\
        "Ŝŝ""S\xcc\x82""s\xcc\x82 "\
        "Šš""S\xcc\x8c""s\xcc\x8c "\
        "Þþ "\
        "Üü""U\xcc\x88""u\xcc\x88 "\
        "Ŭŭ""U\xcc\x86""u\xcc\x86 "\
        "Źź""Z\xcc\x81""z\xcc\x81 "\
        "Żż""Z\xcc\x87""z\xcc\x87 "\
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

            std::cout << "=================================================================" << std::endl;
            std::cout << "Testing: int convertMorseFromHebrew(const char *, char *, size_t)" << std::endl;
            std::cout << "=================================================================" << std::endl;
            std::cout << std::endl;
            Machine5::reset();
            Machine5::errorCode = convertMorseFromHebrew(argv[i], Machine5::out, Machine5::outSize);
            std::cout << Machine5::out << std::endl;
            std::cout << Machine5::errorCode << std::endl;
            std::cout << std::endl;

            std::cout << "=================================================================" << std::endl;
            std::cout << "Testing: int convertMorseFromArabic(const char *, char *, size_t)" << std::endl;
            std::cout << "=================================================================" << std::endl;
            std::cout << std::endl;
            Machine5::reset();
            Machine5::errorCode = convertMorseFromArabic(argv[i], Machine5::out, Machine5::outSize);
            std::cout << Machine5::out << std::endl;
            std::cout << Machine5::errorCode << std::endl;
            std::cout << std::endl;

            std::cout << "==================================================================" << std::endl;
            std::cout << "Testing: int convertMorseFromPersian(const char *, char *, size_t)" << std::endl;
            std::cout << "==================================================================" << std::endl;
            std::cout << std::endl;
            Machine5::reset();
            Machine5::errorCode = convertMorseFromPersian(argv[i], Machine5::out, Machine5::outSize);
            std::cout << Machine5::out << std::endl;
            std::cout << Machine5::errorCode << std::endl;
            std::cout << std::endl;

            std::cout << "==================================================================" << std::endl;
            std::cout << "Testing: int convertMorseFromRussian(const char *, char *, size_t)" << std::endl;
            std::cout << "==================================================================" << std::endl;
            std::cout << std::endl;
            Machine5::reset();
            Machine5::errorCode = convertMorseFromRussian(argv[i], Machine5::out, Machine5::outSize);
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
    std::cout << "Argmt 1: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse((char *)NULL, Machine1::dly, Machine1::dit, Machine1::dah);
    std::cout << "Output : " << Machine1::out << std::endl;
    Test::printResult(testId, Machine1::out == "");
    std::cout << std::endl;

    Machine1::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse((char *)nullptr, Machine1::dly, Machine1::dit, Machine1::dah);
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
    std::cout << "Argmt 1: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse((char *)NULL, Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
    std::cout << "Output : " << Machine2::out << std::endl;
    Test::printResult(testId, Machine2::out == "");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    sendMorse((char *)nullptr, Machine2::dly, Machine2::dit, Machine2::dah, &Machine2::out);
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
    std::cout << "Argmt 5: (void *)NULL" << std::endl;
    std::cout << "Expect : *,*,*,-,-,-,*,*,*,,,,,,," << std::endl;
    sendMorse("<sos>", Machine2::dly, Machine2::dit, Machine2::dah, (void *)NULL);
    std::cout << "Output : " << Machine2::outDefault << std::endl;
    Test::printResult(testId, Machine2::outDefault == "*,*,*,-,-,-,*,*,*,,,,,,,");
    std::cout << std::endl;

    Machine2::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: (void *)nullptr" << std::endl;
    std::cout << "Expect : *,*,*,-,-,-,*,*,*,,,,,,," << std::endl;
    sendMorse("<sos>", Machine2::dly, Machine2::dit, Machine2::dah, (void *)nullptr);
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
    std::cout << "Argmt 1: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine3::errorCode = sendMorse((char *)NULL, Machine3::dly, Machine3::dit, Machine3::dah);
    std::cout << "Output : " << Machine3::out << std::endl;
    Test::printResult(testId, Machine3::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine3::errorCode << std::endl;
    Test::printResult(testId, Machine3::errorCode == -1);
    std::cout << std::endl;

    Machine3::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine3::errorCode = sendMorse((char *)nullptr, Machine3::dly, Machine3::dit, Machine3::dah);
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
    std::cout << "Argmt 1: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine4::errorCode = sendMorse((char *)NULL, Machine4::dly, Machine4::dit, Machine4::dah, &Machine4::out);
    std::cout << "Output : " << Machine4::out << std::endl;
    Test::printResult(testId, Machine4::out == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == -1);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine4::errorCode = sendMorse((char *)nullptr, Machine4::dly, Machine4::dit, Machine4::dah, &Machine4::out);
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
    std::cout << "Argmt 5: (void *)NULL" << std::endl;
    std::cout << "Expect : *,*,*,-,-,-,*,*,*,,,,,,," << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::dit, Machine4::dah, (void *)NULL);
    std::cout << "Output : " << Machine4::outDefault << std::endl;
    Test::printResult(testId, Machine4::outDefault == "*,*,*,-,-,-,*,*,*,,,,,,,");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine4::errorCode << std::endl;
    Test::printResult(testId, Machine4::errorCode == 0);
    std::cout << std::endl;

    Machine4::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 5: (void *)nullptr" << std::endl;
    std::cout << "Expect : *,*,*,-,-,-,*,*,*,,,,,,," << std::endl;
    Machine4::errorCode = sendMorse("<sos>", Machine4::dly, Machine4::dit, Machine4::dah, (void *)nullptr);
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
    std::cout << "Argmt 1: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek((char *)NULL, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek((char *)nullptr, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek("", (char *)NULL, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek("", (char *)nullptr, Machine5::outSize);
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
    std::cout << "Argmt 1: "  << std::endl;
    std::cout << "Argmt 3: 1"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek("", Machine5::out, 1);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: Χ"  << std::endl;
    std::cout << "Argmt 3: 4"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek("Χ", Machine5::out, 4);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: Χ"  << std::endl;
    std::cout << "Argmt 3: 5"  << std::endl;
    std::cout << "Expect : <MM>" << std::endl;
    Machine5::errorCode = convertMorseFromGreek("Χ", Machine5::out, 5);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "<MM>");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: χ"  << std::endl;
    std::cout << "Argmt 3: 4"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromGreek("χ", Machine5::out, 4);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: χ"  << std::endl;
    std::cout << "Argmt 3: 5"  << std::endl;
    std::cout << "Expect : <MM>" << std::endl;
    Machine5::errorCode = convertMorseFromGreek("χ", Machine5::out, 5);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "<MM>");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: aα"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : a" << std::endl;
    Machine5::errorCode = convertMorseFromGreek("aα", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "a");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: aα"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : aA" << std::endl;
    Machine5::errorCode = convertMorseFromGreek("aα", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "aA");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: αΩ"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : A" << std::endl;
    Machine5::errorCode = convertMorseFromGreek("αΩ", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: αΩ"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : AW" << std::endl;
    Machine5::errorCode = convertMorseFromGreek("αΩ", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "AW");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : hi" << std::endl;
    Machine5::errorCode = convertMorseFromGreek("hip", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hi");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 4"  << std::endl;
    std::cout << "Expect : hip" << std::endl;
    Machine5::errorCode = convertMorseFromGreek("hip", Machine5::out, 4);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hip");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
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

    std::cout << "=================================================================" << std::endl;
    std::cout << "Testing: int convertMorseFromHebrew(const char *, char *, size_t)" << std::endl;
    std::cout << "=================================================================" << std::endl;
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromHebrew((char *)NULL, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromHebrew((char *)nullptr, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("", (char *)NULL, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("", (char *)nullptr, Machine5::outSize);
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
    Machine5::errorCode = convertMorseFromHebrew("", Machine5::out, 0);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: "  << std::endl;
    std::cout << "Argmt 3: 1"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("", Machine5::out, 1);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: א"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : A" << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("א", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: aא"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : a" << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("aא", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "a");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: aא"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : aA" << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("aא", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "aA");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: את"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : A" << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("את", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: את"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : AT" << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("את", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "AT");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : hi" << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("hip", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hi");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 4"  << std::endl;
    std::cout << "Expect : hip" << std::endl;
    Machine5::errorCode = convertMorseFromHebrew("hip", Machine5::out, 4);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hip");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::hebrew << std::endl;
    std::cout << "Expect : " << Test::hebrewToEnglish << std::endl;
    Machine5::errorCode = convertMorseFromHebrew(Test::hebrew.c_str(), Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == Test::hebrewToEnglish);
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    std::cout << "=================================================================" << std::endl;
    std::cout << "Testing: int convertMorseFromArabic(const char *, char *, size_t)" << std::endl;
    std::cout << "=================================================================" << std::endl;
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromArabic((char *)NULL, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromArabic((char *)nullptr, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromArabic("", (char *)NULL, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromArabic("", (char *)nullptr, Machine5::outSize);
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
    Machine5::errorCode = convertMorseFromArabic("", Machine5::out, 0);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: "  << std::endl;
    std::cout << "Argmt 3: 1"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromArabic("", Machine5::out, 1);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: ا"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : A" << std::endl;
    Machine5::errorCode = convertMorseFromArabic("ا", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: aا"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : a" << std::endl;
    Machine5::errorCode = convertMorseFromArabic("aا", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "a");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: aا"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : aA" << std::endl;
    Machine5::errorCode = convertMorseFromArabic("aا", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "aA");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: اﺀ"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : A" << std::endl;
    Machine5::errorCode = convertMorseFromArabic("اﺀ", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: اﺀ"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : AE" << std::endl;
    Machine5::errorCode = convertMorseFromArabic("اﺀ", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "AE");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: ﺀا"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : E" << std::endl;
    Machine5::errorCode = convertMorseFromArabic("ﺀا", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "E");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: ﺀا"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : EA" << std::endl;
    Machine5::errorCode = convertMorseFromArabic("ﺀا", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "EA");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : hi" << std::endl;
    Machine5::errorCode = convertMorseFromArabic("hip", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hi");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 4"  << std::endl;
    std::cout << "Expect : hip" << std::endl;
    Machine5::errorCode = convertMorseFromArabic("hip", Machine5::out, 4);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hip");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::arabic << std::endl;
    std::cout << "Expect : " << Test::arabicToEnglish << std::endl;
    Machine5::errorCode = convertMorseFromArabic(Test::arabic.c_str(), Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == Test::arabicToEnglish);
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    std::cout << "=================================================================" << std::endl;
    std::cout << "Testing: int convertMorseFromPersian(const char *, char *, size_t)" << std::endl;
    std::cout << "=================================================================" << std::endl;
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromPersian((char *)NULL, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromPersian((char *)nullptr, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromPersian("", (char *)NULL, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromPersian("", (char *)nullptr, Machine5::outSize);
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
    Machine5::errorCode = convertMorseFromPersian("", Machine5::out, 0);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: "  << std::endl;
    std::cout << "Argmt 3: 1"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromPersian("", Machine5::out, 1);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: ا"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : A" << std::endl;
    Machine5::errorCode = convertMorseFromPersian("ا", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: aا"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : a" << std::endl;
    Machine5::errorCode = convertMorseFromPersian("aا", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "a");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: aا"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : aA" << std::endl;
    Machine5::errorCode = convertMorseFromPersian("aا", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "aA");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: اش"  << std::endl;
    std::cout << "Argmt 3: 5"  << std::endl;
    std::cout << "Expect : A" << std::endl;
    Machine5::errorCode = convertMorseFromPersian("اش", Machine5::out, 5);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: اش"  << std::endl;
    std::cout << "Argmt 3: 6"  << std::endl;
    std::cout << "Expect : A<MM>" << std::endl;
    Machine5::errorCode = convertMorseFromPersian("اش", Machine5::out, 6);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A<MM>");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : hi" << std::endl;
    Machine5::errorCode = convertMorseFromPersian("hip", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hi");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 4"  << std::endl;
    std::cout << "Expect : hip" << std::endl;
    Machine5::errorCode = convertMorseFromPersian("hip", Machine5::out, 4);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hip");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::persian << std::endl;
    std::cout << "Expect : " << Test::persianToEnglish << std::endl;
    Machine5::errorCode = convertMorseFromPersian(Test::persian.c_str(), Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == Test::persianToEnglish);
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    std::cout << "==================================================================" << std::endl;
    std::cout << "Testing: int convertMorseFromRussian(const char *, char *, size_t)" << std::endl;
    std::cout << "==================================================================" << std::endl;
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromRussian((char *)NULL, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromRussian((char *)nullptr, Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)NULL"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromRussian("", (char *)NULL, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 2: (char *)nullptr"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromRussian("", (char *)nullptr, Machine5::outSize);
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
    Machine5::errorCode = convertMorseFromRussian("", Machine5::out, 0);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : -1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == -1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: "  << std::endl;
    std::cout << "Argmt 3: 1"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromRussian("", Machine5::out, 1);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: Ы"  << std::endl;
    std::cout << "Argmt 3: 1"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromRussian("Ы", Machine5::out, 1);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: Ы"  << std::endl;
    std::cout << "Argmt 3: 1"  << std::endl;
    std::cout << "Expect : Y" << std::endl;
    Machine5::errorCode = convertMorseFromRussian("Ы", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "Y");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: ы"  << std::endl;
    std::cout << "Argmt 3: 1"  << std::endl;
    std::cout << "Expect : " << std::endl;
    Machine5::errorCode = convertMorseFromRussian("ы", Machine5::out, 1);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: ы"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : Y" << std::endl;
    Machine5::errorCode = convertMorseFromRussian("ы", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "Y");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: bы"  << std::endl;
    std::cout << "Argmt 3: 2"  << std::endl;
    std::cout << "Expect : b" << std::endl;
    Machine5::errorCode = convertMorseFromRussian("bы", Machine5::out, 2);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "b");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: bы"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : bY" << std::endl;
    Machine5::errorCode = convertMorseFromRussian("bы", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "bY");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: ая"  << std::endl;
    std::cout << "Argmt 3: 5"  << std::endl;
    std::cout << "Expect : A" << std::endl;
    Machine5::errorCode = convertMorseFromRussian("ая", Machine5::out, 5);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: ая"  << std::endl;
    std::cout << "Argmt 3: 6"  << std::endl;
    std::cout << "Expect : A<AA>" << std::endl;
    Machine5::errorCode = convertMorseFromRussian("ая", Machine5::out, 6);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "A<AA>");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 3"  << std::endl;
    std::cout << "Expect : hi" << std::endl;
    Machine5::errorCode = convertMorseFromRussian("hip", Machine5::out, 3);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hi");
    std::cout << "Expect : 1" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 1);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: hip"  << std::endl;
    std::cout << "Argmt 3: 4"  << std::endl;
    std::cout << "Expect : hip" << std::endl;
    Machine5::errorCode = convertMorseFromRussian("hip", Machine5::out, 4);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == "hip");
    std::cout << "Expect : 0" << std::endl;
    std::cout << "Return : " << Machine5::errorCode << std::endl;
    Test::printResult(testId, Machine5::errorCode == 0);
    std::cout << std::endl;

    Machine5::reset();
    std::cout << "Test ID: " << ++testId << std::endl;
    std::cout << "Argmt 1: " << Test::russian << std::endl;
    std::cout << "Expect : " << Test::russianToEnglish << std::endl;
    Machine5::errorCode = convertMorseFromRussian(Test::russian.c_str(), Machine5::out, Machine5::outSize);
    std::cout << "Output : " << Machine5::out << std::endl;
    Test::printResult(testId, std::string(Machine5::out) == Test::russianToEnglish);
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

