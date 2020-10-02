#include "_countUtf8Bytes.h"
#include "_enFromGreekMorse.h"
#include "_isDiacritic.h"
#include "_utf8ToUnicode.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
int _enFromGreekMorse(const unsigned char **greek, unsigned char **english, const unsigned char *englishEnd)
{
    unsigned char unicodeHi;
    unsigned char unicodeLo;

    //Check if there is space to write in *english.
    if (englishEnd <= (*english) + 1)
    {
        goto ErrorNoSpace;
    }

    //Check if *greek is 2 byte UTF-8 character without diacritics following it.
    if ((_countUtf8Bytes(*greek) != 2) || _isDiacritic((*greek) + 2))
    {
        goto ErrorNoMatch;
    }

    //Convert 2 byte UTF-8 character to Unicode code point.
    unicodeHi = (*greek)[0];
    unicodeLo = (*greek)[1];
    _utf8ToUnicode(&unicodeHi, &unicodeLo);

    //Greek characters are Unicode code points U+0391 - U+03c9.
    if (unicodeHi != 0x03)
    {
        goto ErrorNoMatch;
    }

    //Convert uppercase (Α-Ω) to lowercase (α-ω).
    //Uppercase (U+0391 - U+03A9)
    //Lowercase (U+03B1 - U+03C9)
    if ((0x91 <= unicodeLo) && (unicodeLo <= 0xa9))
    {
        unicodeLo += 0x20;
    }

    switch (unicodeLo)
    {
        case 0xb1:
            //α (alpha) -> A
            *(*english)++ = 0x41;
            goto Success;

        case 0xb2:
            //β (beta) -> B
            *(*english)++ = 0x42;
            goto Success;

        case 0xb3:
            //γ (gamma) -> G
            *(*english)++ = 0x47;
            goto Success;

        case 0xb4:
            //δ (delta) -> D
            *(*english)++ = 0x44;
            goto Success;

        case 0xb5:
            //ε (epsilon) -> E
            *(*english)++ = 0x45;
            goto Success;

        case 0xb6:
            //ζ (zeta) -> Z
            *(*english)++ = 0x5a;
            goto Success;

        case 0xb7:
            //η (eta) -> H
            *(*english)++ = 0x48;
            goto Success;

        case 0xb8:
            //θ (theta) -> C
            *(*english)++ = 0x43;
            goto Success;

        case 0xb9:
            //ι (iota) -> I
            *(*english)++ = 0x49;
            goto Success;

        case 0xba:
            //κ (kappa) -> K
            *(*english)++ = 0x4b;
            goto Success;

        case 0xbb:
            //λ (lambda) -> L
            *(*english)++ = 0x4c;
            goto Success;

        case 0xbc:
            //μ (mu) -> M
            *(*english)++ = 0x4d;
            goto Success;

        case 0xbd:
            //ν (nu) -> N
            *(*english)++ = 0x4e;
            goto Success;

        case 0xbe:
            //ξ (xi) -> X
            *(*english)++ = 0x58;
            goto Success;

        case 0xbf:
            //ο (omicron) -> O
            *(*english)++ = 0x4f;
            goto Success;

        case 0xc0:
            //π (pi) -> P
            *(*english)++ = 0x50;
            goto Success;

        case 0xc1:
            //ρ (rho) -> R
            *(*english)++ = 0x52;
            goto Success;

        case 0xc2:
        case 0xc3:
            //ς or σ (sigma) -> S
            *(*english)++ = 0x53;
            goto Success;

        case 0xc4:
            //τ (tau) -> T
            *(*english)++ = 0x54;
            goto Success;

        case 0xc5:
            //υ (upsilon) -> Y
            *(*english)++ = 0x59;
            goto Success;

        case 0xc6:
            //φ (phi) -> F
            *(*english)++ = 0x46;
            goto Success;

        case 0xc7:
            //χ (chi) -> <MM>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = 0x3c;
            *(*english)++ = 0x4d;
            *(*english)++ = 0x4d;
            *(*english)++ = 0x3e;
            goto Success;

        case 0xc8:
            //ψ (psi) -> Q
            *(*english)++ = 0x51;
            goto Success;

        case 0xc9:
            //ω (omega) -> W
            *(*english)++ = 0x57;
            goto Success;

        default:
            goto ErrorNoMatch;
    }

Success:
    (*greek) += 2;
    return 0;

ErrorNoSpace:
    return 1;

ErrorNoMatch:
    return 2;
}
}

