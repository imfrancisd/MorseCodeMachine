#include "_countUtf8Bytes.h"
#include "_enToMorseElements.h"
#include "_isDiacritic.h"
#include "_skipDiacritic.h"
#include "_utf8ToUnicode.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
static unsigned char _toUpperAscii(unsigned char ascii)
{
    //ASCII characters are Unicode code points U+0000 - U+007F.
    //Convert lowercase (a-z) to uppercase (A-Z).
    //Uppercase (U+0041 - U+005A)
    //Lowercase (U+0061 - U+007A)
    if ((0x61 <= ascii) && (ascii <= 0x7a))
    {
        ascii -= 0x20;
    }
    return ascii;
}

static unsigned char _enToMorseElements(unsigned char ascii)
{
    switch (_toUpperAscii(ascii))
    {
        //Digits 0-9.

        case 0x30:
            //0 -> DAH DAH DAH DAH DAH
            return 0b11111100;

        case 0x31:
            //1 -> DIT DAH DAH DAH DAH
            return 0b01111100;

        case 0x32:
            //2 -> DIT DIT DAH DAH DAH
            return 0b00111100;

        case 0x33:
            //3 -> DIT DIT DIT DAH DAH
            return 0b00011100;

        case 0x34:
            //4 -> DIT DIT DIT DIT DAH
            return 0b00001100;

        case 0x35:
            //5 -> DIT DIT DIT DIT DIT
            return 0b00000100;

        case 0x36:
            //6 -> DAH DIT DIT DIT DIT
            return 0b10000100;

        case 0x37:
            //7 -> DAH DAH DIT DIT DIT
            return 0b11000100;

        case 0x38:
            //8 -> DAH DAH DAH DIT DIT
            return 0b11100100;

        case 0x39:
            //9 -> DAH DAH DAH DAH DIT
            return 0b11110100;

        //Letters A-Z.

        case 0x41:
            //A -> DIT DAH
            return 0b01100000;

        case 0x42:
            //B -> DAH DIT DIT DIT
            return 0b10001000;

        case 0x43:
            //C -> DAH DIT DAH DIT
            return 0b10101000;

        case 0x44:
            //D -> DAH DIT DIT
            return 0b10010000;

        case 0x45:
            //E -> DIT
            return 0b01000000;

        case 0x46:
            //F -> DIT DIT DAH DIT
            return 0b00101000;

        case 0x47:
            //G -> DAH DAH DIT
            return 0b11010000;

        case 0x48:
            //H -> DIT DIT DIT DIT
            return 0b00001000;

        case 0x49:
            //I -> DIT DIT
            return 0b00100000;

        case 0x4a:
            //J -> DIT DAH DAH DAH
            return 0b01111000;

        case 0x4b:
            //K -> DAH DIT DAH
            return 0b10110000;

        case 0x4c:
            //L -> DIT DAH DIT DIT
            return 0b01001000;

        case 0x4d:
            //M -> DAH DAH
            return 0b11100000;

        case 0x4e:
            //N -> DAH DIT
            return 0b10100000;

        case 0x4f:
            //O -> DAH DAH DAH
            return 0b11110000;

        case 0x50:
            //P -> DIT DAH DAH DIT
            return 0b01101000;

        case 0x51:
            //Q -> DAH DAH DIT DAH
            return 0b11011000;

        case 0x52:
            //R -> DIT DAH DIT
            return 0b01010000;

        case 0x53:
            //S -> DIT DIT DIT
            return 0b00010000;

        case 0x54:
            //T -> DAH
            return 0b11000000;

        case 0x55:
            //U -> DIT DIT DAH
            return 0b00110000;

        case 0x56:
            //V -> DIT DIT DIT DAH
            return 0b00011000;

        case 0x57:
            //W -> DIT DAH DAH
            return 0b01110000;

        case 0x58:
            //X -> DAH DIT DIT DAH
            return 0b10011000;

        case 0x59:
            //Y -> DAH DIT DAH DAH
            return 0b10111000;

        case 0x5a:
            //Z -> DAH DAH DIT DIT
            return 0b11001000;

        //Symbols.

        case 0x22:
            //" -> DIT DAH DIT DIT DAH DIT
            return 0b01001010;

        case 0x26:
            //& -> DIT DAH DIT DIT DIT
            return 0b01000100;

        case 0x27:
            //' -> DIT DAH DAH DAH DAH DIT
            return 0b01111010;

        case 0x28:
            //( -> DAH DIT DAH DAH DIT
            return 0b10110100;

        case 0x29:
            //) -> DAH DIT DAH DAH DIT DAH
            return 0b10110110;

        case 0x2b:
            //+ -> DIT DAH DIT DAH DIT
            return 0b01010100;

        case 0x2c:
            //, -> DAH DAH DIT DIT DAH DAH
            return 0b11001110;

        case 0x2d:
            //- -> DAH DIT DIT DIT DIT DAH
            return 0b10000110;

        case 0x2e:
            //. -> DIT DAH DIT DAH DIT DAH
            return 0b01010110;

        case 0x2f:
            /// -> DAH DIT DIT DAH DIT
            return 0b10010100;

        case 0x3a:
            //: -> DAH DAH DAH DIT DIT DIT
            return 0b11100010;

        case 0x3d:
            //= -> DAH DIT DIT DIT DAH
            return 0b10001100;

        case 0x3f:
            //? -> DIT DIT DAH DAH DIT DIT
            return 0b00110010;

        case 0x40:
            //@ -> DIT DAH DAH DIT DAH DIT
            return 0b01101010;

        //Recognized characters that do not have Morse elements.

        case 0x20: // 
        case 0x3c: //<
        case 0x3e: //>
            return 0b10000000;

        //Unrecognized characters.

        default:
            return 0x00;
    }
}

unsigned char _enToMorseElements(const unsigned char **bytes)
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

        //Convert 2 byte UTF-8 diacritic to Unicode code point.
        unsigned char unicodeHi = (*bytes)[1];
        unsigned char unicodeLo = (*bytes)[2];
        _utf8ToUnicode(&unicodeHi, &unicodeLo);

        //Diacritics needed are between U+0300 - U+036F
        if (unicodeHi != 0x03)
        {
            goto MatchNothing;
        }

        switch (_toUpperAscii((*bytes)[0]))
        {
            case 0x41: //A
                switch (unicodeLo)
                {
                    case 0x00: //grave
                        goto MatchAWithGrave;

                    case 0x08: //diaeresis
                        goto MatchAWithDiaeresis;

                    case 0x0a: //ring above
                        goto MatchAWithRing;

                    case 0x28: //ogonek
                        goto MatchAWithOgonek;

                    default:
                        goto MatchNothing;
                }

            case 0x43: //C
                switch (unicodeLo)
                {
                    case 0x01: //acute
                        goto MatchCWithAcute;

                    case 0x02: //circumflex
                        goto MatchCWithCircumflex;

                    case 0x27: //cedilla
                        goto MatchCWithCedilla;

                    default:
                        goto MatchNothing;
                }

            case 0x45: //E
                switch (unicodeLo)
                {
                    case 0x00: //grave
                        goto MatchEWithGrave;

                    case 0x01: //acute
                        goto MatchEWithAcute;

                    case 0x28: //ogonek
                        goto MatchEWithOgonek;

                    default:
                        goto MatchNothing;
                }

            case 0x47: //G
                switch (unicodeLo)
                {
                    case 0x02: //circumflex
                        goto MatchGWithCircumflex;

                    default:
                        goto MatchNothing;
                }

            case 0x48: //H
                switch (unicodeLo)
                {
                    case 0x02: //circumflex
                        goto MatchHWithCircumflex;

                    default:
                        goto MatchNothing;
                }

            case 0x4a: //J
                switch (unicodeLo)
                {
                    case 0x02: //circumflex
                        goto MatchJWithCircumflex;

                    default:
                        goto MatchNothing;
                }

            case 0x4e: //N
                switch (unicodeLo)
                {
                    case 0x01: //acute
                        goto MatchNWithAcute;

                    case 0x03: //tilde
                        goto MatchNWithTilde;

                    default:
                        goto MatchNothing;
                }

            case 0x4f: //O
                switch (unicodeLo)
                {
                    case 0x01: //acute
                        goto MatchOWithAcute;

                    case 0x08: //diaeresis
                        goto MatchOWithDiaeresis;

                    default:
                        goto MatchNothing;
                }

            case 0x53: //S
                switch (unicodeLo)
                {
                    case 0x01: //acute
                        goto MatchSWithAcute;

                    case 0x02: //circumflex
                        goto MatchSWithCircumflex;

                    case 0x0c: //caron
                        goto MatchSWithCaron;

                    default:
                        goto MatchNothing;
                }

            case 0x55: //U
                switch (unicodeLo)
                {
                    case 0x06: //breve
                        goto MatchUWithBreve;

                    case 0x08: //diaeresis
                        goto MatchUWithDiaeresis;

                    default:
                        goto MatchNothing;
                }

            case 0x5a: //Z
                switch (unicodeLo)
                {
                    case 0x01: //acute
                        goto MatchZWithAcute;

                    case 0x07: //dot above
                        goto MatchZWithDotAbove;

                    default:
                        goto MatchNothing;
                }

            default:
                goto MatchNothing;
        }

        goto MatchNothing;
    }

    //2 byte UTF-8 character followed by 0 diacritics.
    if ((countUtf8Bytes == 2) && (!_isDiacritic((*bytes) + 2)))
    {
        //Convert 2 byte UTF-8 character to Unicode code point.
        unsigned char unicodeHi = (*bytes)[0];
        unsigned char unicodeLo = (*bytes)[1];
        _utf8ToUnicode(&unicodeHi, &unicodeLo);

        switch (unicodeHi)
        {
            case 0x00:
                //Latin-1 Supplement Unicode block.
                //Convert lowercase to uppercase.
                //Uppercase (U+00C0 - U+00D6, U+00D8 - U+00DE).
                //Lowercase (U+00E0 - U+00F6, U+00F8 - U+00FE).
                //Note: U+00D7 is multiplication sign and
                //      U+00F7 is division sign.
                if ((0xe0 <= unicodeLo) && (unicodeLo <= 0xfe))
                {
                    unicodeLo -= 0x20;
                }
                
                switch (unicodeLo)
                {
                    case 0xc0:
                        goto MatchAWithGrave;

                    case 0xc4:
                        goto MatchAWithDiaeresis;

                    case 0xc5:
                        goto MatchAWithRing;

                    case 0xc6:
                        goto MatchAE;

                    case 0xc7:
                        goto MatchCWithCedilla;

                    case 0xc8:
                        goto MatchEWithGrave;

                    case 0xc9:
                        goto MatchEWithAcute;

                    case 0xd0:
                        goto MatchEth;

                    case 0xd1:
                        goto MatchNWithTilde;

                    case 0xd3:
                        goto MatchOWithAcute;

                    case 0xd6:
                        goto MatchOWithDiaeresis;

                    case 0xd8:
                        goto MatchOWithStroke;

                    case 0xdc:
                        goto MatchUWithDiaeresis;

                    case 0xde:
                        goto MatchThorn;

                    default:
                        goto MatchNothing;
                }

            case 0x01:
                //Latin Extended-A Unicode block.
                //Note: Converting lowercase to uppercase or
                //      converting uppercase to lowercase
                //      just makes the compiled program bigger.
                switch (unicodeLo)
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
    morseElements = 0x00;
    goto Done;

MatchAscii:
    morseElements = _enToMorseElements((*bytes)[0]);
    goto Done;

MatchAE:
MatchAWithDiaeresis:
MatchAWithOgonek:
    //Æ, æ (AE)               -> DIT DAH DIT DAH
    //Ä, ä (A WITH DIAERESIS) -> DIT DAH DIT DAH
    //Ą, ą (A WITH OGONEK)    -> DIT DAH DIT DAH
    morseElements = 0b01011000;
    goto Done;

MatchAWithGrave:
MatchAWithRing:
    //À, à (A WITH GRAVE) -> DIT DAH DAH DIT DAH
    //Å, å (A WITH RING)  -> DIT DAH DAH DIT DAH
    morseElements = 0b01101100;
    goto Done;

MatchCWithAcute:
MatchCWithCedilla:
MatchCWithCircumflex:
    //Ć, ć (C WITH ACUTE)      -> DAH DIT DAH DIT DIT
    //Ç, ç (C WITH CEDILLA)    -> DAH DIT DAH DIT DIT
    //Ĉ, ĉ (C WITH CIRCUMFLEX) -> DAH DIT DAH DIT DIT
    morseElements = 0b10100100;
    goto Done;

MatchDWithStroke:
MatchEWithAcute:
MatchEWithOgonek:
    //Đ, đ (D WITH STROKE) -> DIT DIT DAH DIT DIT
    //É, é (E WITH ACUTE)  -> DIT DIT DAH DIT DIT
    //Ę, ę (E WITH OGONEK) -> DIT DIT DAH DIT DIT
    morseElements = 0b00100100;
    goto Done;

MatchEth:
    //Ð, ð (ETH) -> DIT DIT DAH DAH DIT
    morseElements = 0b00110100;
    goto Done;

MatchEWithGrave:
MatchLWithStroke:
    //È, è (E WITH GRAVE)  -> DIT DAH DIT DIT DAH
    //Ł, ł (L WITH STROKE) -> DIT DAH DIT DIT DAH
    morseElements = 0b01001100;
    goto Done;

MatchGWithCircumflex:
    //Ĝ, ĝ (G WITH CIRCUMFLEX) -> DAH DAH DIT DAH DIT
    morseElements = 0b11010100;
    goto Done;

MatchHWithCircumflex:
MatchSWithCaron:
    //Ĥ, ĥ (H WITH CIRCUMFLEX) -> DAH DAH DAH DAH
    //Š, š (S WITH CARON)      -> DAH DAH DAH DAH
    morseElements = 0b11111000;
    goto Done;

MatchJWithCircumflex:
    //Ĵ, ĵ (J WITH CIRCUMFLEX) -> DIT DAH DAH DAH DIT
    morseElements = 0b01110100;
    goto Done;

MatchNWithAcute:
MatchNWithTilde:
    //Ń, ń (N WITH ACUTE) -> DAH DAH DIT DAH DAH
    //Ñ, ñ (N WITH TILDE) -> DAH DAH DIT DAH DAH
    morseElements = 0b11011100;
    goto Done;

MatchOWithAcute:
MatchOWithDiaeresis:
MatchOWithStroke:
    //Ó, ó (O WITH ACUTE)     -> DAH DAH DAH DIT
    //Ö, ö (O WITH DIAERESIS) -> DAH DAH DAH DIT
    //Ø, ø (O WITH STROKE)    -> DAH DAH DAH DIT
    morseElements = 0b11101000;
    goto Done;

MatchSWithAcute:
    //Ś, ś (S WITH ACUTE) -> DIT DIT DIT DAH DIT DIT DIT
    morseElements = 0b00010001;
    goto Done;

MatchSWithCircumflex:
    //Ŝ, ŝ (S WITH CIRCUMFLEX) -> DIT DIT DIT DAH DIT
    morseElements = 0b00010100;
    goto Done;

MatchThorn:
    //Þ, þ (THORN) -> DIT DAH DAH DIT DIT
    morseElements = 0b01100100;
    goto Done;

MatchUWithBreve:
MatchUWithDiaeresis:
    //Ŭ, ŭ (U WITH BREVE)     -> DIT DIT DAH DAH
    //Ü, ü (U WITH DIAERESIS) -> DIT DIT DAH DAH
    morseElements = 0b00111000;
    goto Done;

MatchZWithAcute:
    //Ź, ź (Z WITH ACUTE) -> DAH DAH DIT DIT DAH DIT
    morseElements = 0b11001010;
    goto Done;

MatchZWithDotAbove:
    //Ż, ż (Z WITH DOT ABOVE) -> DAH DAH DIT DIT DAH
    morseElements = 0b11001100;
    goto Done;

Done:
    //Go to next UTF-8 character.
    //Skip diacritics only if valid UTF-8 character found.
    if (countUtf8Bytes == 0)
    {
        (*bytes)++;
    }
    else
    {
        (*bytes) += countUtf8Bytes;
        while (_skipDiacritic(bytes))
            ;
    }
    return morseElements;
}
}

