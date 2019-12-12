#include "_countUtf8Bytes.h"
#include "_enFromGreekMorse.h"
#include "_isDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



namespace b1ccef0c36f5537eb1a608b20bb25eb318bbf795
{
int _enFromGreekMorse(const char **greek, char **english, const char *englishEnd)
{
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
    unsigned char unicode[2];
    unicode[0] = 0x3f & (*greek)[0];
    unicode[1] = 0x3f & (*greek)[1];
    unicode[1] = unicode[1] | (0xc0 & (unicode[0] << 6));
    unicode[0] = unicode[0] >> 2;

    //Greek characters are Unicode code points U+0391 - U+03c9.
    if (unicode[0] != 0x03)
    {
        goto ErrorNoMatch;
    }

    //Convert uppercase (Α-Ω) to lowercase (α-ω).
    //Uppercase (U+0391 - U+03A9)
    //Lowercase (U+03B1 - U+03C9)
    if ((0x91 <= unicode[1]) && (unicode[1] <= 0xa9))
    {
        unicode[1] += 0x20;
    }

    switch (unicode[1])
    {
        case 0xb1:
            //α (alpha) -> A
            *(*english)++ = '\x41';
            goto Success;

        case 0xb2:
            //β (beta) -> B
            *(*english)++ = '\x42';
            goto Success;

        case 0xb3:
            //γ (gamma) -> G
            *(*english)++ = '\x47';
            goto Success;

        case 0xb4:
            //δ (delta) -> D
            *(*english)++ = '\x44';
            goto Success;

        case 0xb5:
            //ε (epsilon) -> E
            *(*english)++ = '\x45';
            goto Success;

        case 0xb6:
            //ζ (zeta) -> Z
            *(*english)++ = '\x5a';
            goto Success;

        case 0xb7:
            //η (eta) -> H
            *(*english)++ = '\x48';
            goto Success;

        case 0xb8:
            //θ (theta) -> C
            *(*english)++ = '\x43';
            goto Success;

        case 0xb9:
            //ι (iota) -> I
            *(*english)++ = '\x49';
            goto Success;

        case 0xba:
            //κ (kappa) -> K
            *(*english)++ = '\x4b';
            goto Success;

        case 0xbb:
            //λ (lambda) -> L
            *(*english)++ = '\x4c';
            goto Success;

        case 0xbc:
            //μ (mu) -> M
            *(*english)++ = '\x4d';
            goto Success;

        case 0xbd:
            //ν (nu) -> N
            *(*english)++ = '\x4e';
            goto Success;

        case 0xbe:
            //ξ (xi) -> X
            *(*english)++ = '\x58';
            goto Success;

        case 0xbf:
            //ο (omicron) -> O
            *(*english)++ = '\x4f';
            goto Success;

        case 0xc0:
            //π (pi) -> P
            *(*english)++ = '\x50';
            goto Success;

        case 0xc1:
            //ρ (rho) -> R
            *(*english)++ = '\x52';
            goto Success;

        case 0xc2:
        case 0xc3:
            //ς or σ (sigma) -> S
            *(*english)++ = '\x53';
            goto Success;

        case 0xc4:
            //τ (tau) -> T
            *(*english)++ = '\x54';
            goto Success;

        case 0xc5:
            //υ (upsilon) -> Y
            *(*english)++ = '\x59';
            goto Success;

        case 0xc6:
            //φ (phi) -> F
            *(*english)++ = '\x46';
            goto Success;

        case 0xc7:
            //χ (chi) -> <MM>
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '\x3c';
            *(*english)++ = '\x4d';
            *(*english)++ = '\x4d';
            *(*english)++ = '\x3e';
            goto Success;

        case 0xc8:
            //ψ (psi) -> Q
            *(*english)++ = '\x51';
            goto Success;

        case 0xc9:
            //ω (omega) -> W
            *(*english)++ = '\x57';
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

