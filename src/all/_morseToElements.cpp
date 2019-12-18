#include "_countUtf8Bytes.h"
#include "_morseToElements.h"
#include "_isDiacritic.h"
#include "_skipDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
unsigned int _morseToElements(char c)
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

unsigned int _morseToElements(const char **bytes)
{
    unsigned int morseElements = 0;
    unsigned char countUtf8Bytes = _countUtf8Bytes(*bytes);

    if (countUtf8Bytes == 1)
    {
        //Ascii followed by 0 diacritics.
        if (!_isDiacritic((*bytes) + 1))
        {
            goto MatchAscii;
        }

        //Ascii followed by 2 or more diacritics.
        if (_isDiacritic((*bytes) + 3))
        {
            goto MatchNothing;
        }

        //Convert uppercase (A-Z) to lowercase (a-z).
        //Uppercase (U+0041 - U+005A)
        //Lowercase (U+0061 - U+007A)
        unsigned char ascii = 0xff & (*bytes)[0];
        if ((0x41 <= ascii) && (ascii <= 0x5a))
        {
            ascii += 0x20;
        }

        //Convert 2 byte UTF-8 diacritic to Unicode code point.
        unsigned char diacritic[2];
        diacritic[0] = 0x3f & (*bytes)[1];
        diacritic[1] = 0x3f & (*bytes)[2];
        diacritic[1] = diacritic[1] | (0xc0 & (diacritic[0] << 6));
        diacritic[0] = diacritic[0] >> 2;

        //Diacritics needed are between U+0300 - U+036F
        if (diacritic[0] != 0x03)
        {
            goto MatchNothing;
        }

        switch (diacritic[1])
        {
            //Ascii followed by grave.
            case 0x00:
                switch (ascii)
                {
                    case 0x61: //a
                        goto MatchAWithGrave;

                    case 0x65: //e
                        goto MatchEWithGrave;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by acute.
            case 0x01:
                switch (ascii)
                {
                    case 0x65: //e
                        goto MatchEWithAcute;

                    case 0x63: //c
                        goto MatchCWithAcute;

                    case 0x6e: //n
                        goto MatchNWithAcute;

                    case 0x6f: //o
                        goto MatchOWithAcute;

                    case 0x73: //s
                        goto MatchSWithAcute;

                    case 0x7a: //z
                        goto MatchZWithAcute;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by circumflex.
            case 0x02:
                switch (ascii)
                {
                    case 0x63: //c
                        goto MatchCWithCircumflex;

                    case 0x67: //g
                        goto MatchGWithCircumflex;

                    case 0x68: //h
                        goto MatchHWithCircumflex;

                    case 0x6a: //j
                        goto MatchJWithCircumflex;

                    case 0x73: //s
                        goto MatchSWithCircumflex;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by tilde.
            case 0x03:
                switch (ascii)
                {
                    case 0x6e: //n
                        goto MatchNWithTilde;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by breve.
            case 0x06:
                switch (ascii)
                {
                    case 0x75: //u
                        goto MatchUWithBreve;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by dot above.
            case 0x07:
                switch (ascii)
                {
                    case 0x7a: //z
                        goto MatchZWithDotAbove;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by diaeresis.
            case 0x08:
                switch (ascii)
                {
                    case 0x61: //a
                        goto MatchAWithDiaeresis;

                    case 0x6f: //o
                        goto MatchOWithDiaeresis;

                    case 0x75: //u
                        goto MatchUWithDiaeresis;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by ring above.
            case 0x0a:
                switch (ascii)
                {
                    case 0x61: //a
                        goto MatchAWithRing;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by caron.
            case 0x0c:
                switch (ascii)
                {
                    case 0x73: //s
                        goto MatchSWithCaron;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by cedilla.
            case 0x27:
                switch (ascii)
                {
                    case 0x63: //c
                        goto MatchCWithCedilla;

                    default:
                        goto MatchNothing;
                }

            //Ascii followed by ogonek.
            case 0x28:
                switch (ascii)
                {
                    case 0x61: //a
                        goto MatchAWithOgonek;

                    case 0x65: //e
                        goto MatchEWithOgonek;

                    default:
                        goto MatchNothing;
                }
        }

        goto MatchNothing;
    }

    //2 byte UTF-8 character followed by 0 diacritics.
    if ((countUtf8Bytes == 2) && (!_isDiacritic((*bytes) + 2)))
    {
        //Convert 2 byte UTF-8 character to Unicode code point.
        unsigned char unicode[2];
        unicode[0] = 0x3f & (*bytes)[0];
        unicode[1] = 0x3f & (*bytes)[1];
        unicode[1] = unicode[1] | (0xc0 & (unicode[0] << 6));
        unicode[0] = unicode[0] >> 2;

        switch (unicode[0])
        {
            case 0x00:
                //Latin-1 Supplement Unicode block.
                //Convert uppercase to lowercase.
                //Uppercase (U+00C0 - U+00D6, U+00D8 - U+00DE).
                //Lowercase (U+00E0 - U+00F6, U+00F8 - U+00FE).
                if ((0xc0 <= unicode[1]) && (unicode[1] <= 0xde))
                {
                    unicode[1] += 0x20;
                }
                
                switch (unicode[1])
                {
                    case 0xe0:
                        goto MatchAWithGrave;

                    case 0xe4:
                        goto MatchAWithDiaeresis;

                    case 0xe5:
                        goto MatchAWithRing;

                    case 0xe6:
                        goto MatchAE;

                    case 0xe7:
                        goto MatchCWithCedilla;

                    case 0xe8:
                        goto MatchEWithGrave;

                    case 0xe9:
                        goto MatchEWithAcute;

                    case 0xf0:
                        goto MatchEth;

                    case 0xf1:
                        goto MatchNWithTilde;

                    case 0xf3:
                        goto MatchOWithAcute;

                    case 0xf6:
                        goto MatchOWithDiaeresis;

                    case 0xf8:
                        goto MatchOWithStroke;

                    case 0xfc:
                        goto MatchUWithDiaeresis;

                    case 0xfe:
                        goto MatchThorn;

                    default:
                        goto MatchNothing;
                }

            case 0x01:
                //Latin Extended-A Unicode block.
                switch (unicode[1])
                {
                    case 0x04:
                    case 0x05:
                        goto MatchAWithOgonek;

                    case 0x06:
                    case 0x07:
                        goto MatchCWithAcute;

                    case 0x08:
                    case 0x09:
                        goto MatchCWithCircumflex;

                    case 0x10:
                    case 0x11:
                        goto MatchDWithStroke;

                    case 0x18:
                    case 0x19:
                        goto MatchEWithOgonek;

                    case 0x1c:
                    case 0x1d:
                        goto MatchGWithCircumflex;

                    case 0x24:
                    case 0x25:
                        goto MatchHWithCircumflex;

                    case 0x34:
                    case 0x35:
                        goto MatchJWithCircumflex;

                    case 0x41:
                    case 0x42:
                        goto MatchLWithStroke;

                    case 0x43:
                    case 0x44:
                        goto MatchNWithAcute;

                    case 0x5a:
                    case 0x5b:
                        goto MatchSWithAcute;

                    case 0x5c:
                    case 0x5d:
                        goto MatchSWithCircumflex;

                    case 0x60:
                    case 0x61:
                        goto MatchSWithCaron;

                    case 0x6c:
                    case 0x6d:
                        goto MatchUWithBreve;

                    case 0x79:
                    case 0x7a:
                        goto MatchZWithAcute;

                    case 0x7b:
                    case 0x7c:
                        goto MatchZWithDotAbove;

                    default:
                        goto MatchNothing;
                }

            default:
                goto MatchNothing;
        }

        goto MatchNothing;
    }

    goto MatchNothing;

MatchNothing:
    morseElements = 0x0000;
    goto Done;

MatchAscii:
    morseElements = _morseToElements((*bytes)[0]);
    goto Done;

MatchAE:
MatchAWithDiaeresis:
MatchAWithOgonek:
    //Æ, æ (AE)               -> DIT DAH DIT DAH
    //Ä, ä (A WITH DIAERESIS) -> DIT DAH DIT DAH
    //Ą, ą (A WITH OGONEK)    -> DIT DAH DIT DAH
    morseElements = 0b1111000001010000;
    goto Done;

MatchAWithGrave:
MatchAWithRing:
    //À, à (A WITH GRAVE) -> DIT DAH DAH DIT DAH
    //Å, å (A WITH RING)  -> DIT DAH DAH DIT DAH
    morseElements = 0b1111100001101000;
    goto Done;

MatchCWithAcute:
MatchCWithCedilla:
MatchCWithCircumflex:
    //Ć, ć (C WITH ACUTE)      -> DAH DIT DAH DIT DIT
    //Ç, ç (C WITH CEDILLA)    -> DAH DIT DAH DIT DIT
    //Ĉ, ĉ (C WITH CIRCUMFLEX) -> DAH DIT DAH DIT DIT
    morseElements = 0b1111100010100000;
    goto Done;

MatchDWithStroke:
MatchEWithAcute:
MatchEWithOgonek:
    //Đ, đ (D WITH STROKE) -> DIT DIT DAH DIT DIT
    //É, é (E WITH ACUTE)  -> DIT DIT DAH DIT DIT
    //Ę, ę (E WITH OGONEK) -> DIT DIT DAH DIT DIT
    morseElements = 0b1111100000100000;
    goto Done;

MatchEth:
    //Ð, ð (ETH) -> DIT DIT DAH DAH DIT
    morseElements = 0b1111100000110000;
    goto Done;

MatchEWithGrave:
MatchLWithStroke:
    //È, è (E WITH GRAVE)  -> DIT DAH DIT DIT DAH
    //Ł, ł (L WITH STROKE) -> DIT DAH DIT DIT DAH
    morseElements = 0b1111100001001000;
    goto Done;

MatchGWithCircumflex:
    //Ĝ, ĝ (G WITH CIRCUMFLEX) -> DAH DAH DIT DAH DIT
    morseElements = 0b1111100011010000;
    goto Done;

MatchHWithCircumflex:
MatchSWithCaron:
    //Ĥ, ĥ (H WITH CIRCUMFLEX) -> DAH DAH DAH DAH
    //Š, š (S WITH CARON)      -> DAH DAH DAH DAH
    morseElements = 0b1111000011110000;
    goto Done;

MatchJWithCircumflex:
    //Ĵ, ĵ (J WITH CIRCUMFLEX) -> DIT DAH DAH DAH DIT
    morseElements = 0b1111100001110000;
    goto Done;

MatchNWithAcute:
MatchNWithTilde:
    //Ń, ń (N WITH ACUTE) -> DAH DAH DIT DAH DAH
    //Ñ, ñ (N WITH TILDE) -> DAH DAH DIT DAH DAH
    morseElements = 0b1111100011011000;
    goto Done;

MatchOWithAcute:
MatchOWithDiaeresis:
MatchOWithStroke:
    //Ó, ó (O WITH ACUTE)     -> DAH DAH DAH DIT
    //Ö, ö (O WITH DIAERESIS) -> DAH DAH DAH DIT
    //Ø, ø (O WITH STROKE)    -> DAH DAH DAH DIT
    morseElements = 0b1111000011100000;
    goto Done;

MatchSWithAcute:
    //Ś, ś (S WITH ACUTE) -> DIT DIT DIT DAH DIT DIT DIT
    morseElements = 0b1111111000010000;
    goto Done;

MatchSWithCircumflex:
    //Ŝ, ŝ (S WITH CIRCUMFLEX) -> DIT DIT DIT DAH DIT
    morseElements = 0b1111100000010000;
    goto Done;

MatchThorn:
    //Þ, þ (THORN) -> DIT DAH DAH DIT DIT
    morseElements = 0b1111100001100000;
    goto Done;

MatchUWithBreve:
MatchUWithDiaeresis:
    //Ŭ, ŭ (U WITH BREVE)     -> DIT DIT DAH DAH
    //Ü, ü (U WITH DIAERESIS) -> DIT DIT DAH DAH
    morseElements = 0b1111000000110000;
    goto Done;

MatchZWithAcute:
    //Ź, ź (Z WITH ACUTE) -> DAH DAH DIT DIT DAH DIT
    morseElements = 0b1111110011001000;
    goto Done;

MatchZWithDotAbove:
    //Ż, ż (Z WITH DOT ABOVE) -> DAH DAH DIT DIT DAH
    morseElements = 0b1111100011001000;
    goto Done;

Done:
    //Go to next UTF-8 character.
    //Skip diacritics only if valid UTF-8 character found.
    (*bytes) += (countUtf8Bytes > 0) ? countUtf8Bytes : 1;
    if (countUtf8Bytes > 0)
    {
        while (_skipDiacritic(bytes))
            ;
    }
    return morseElements;
}
}

