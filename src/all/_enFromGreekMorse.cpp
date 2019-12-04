#include "_countUtf8Bytes.h"
#include "_enFromGreekMorse.h"
#include "_isDiacritic.h"



// ---------------- PRIVATE FUNCTIONS ---------------- //
// Anything in here, can and will, change at any time. //



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
    unicode[1] |= (unicode[0] << 6);
    unicode[0] >>= 2;

    //Greek characters are Unicode code points U+0391 - U+03c9.
    if (unicode[0] != 0x03)
    {
        goto ErrorNoMatch;
    }

    //Convert uppercase Greek characters to lowercase Greek characters.
    //Uppercase (U+0391 - U+03A9)
    //Lowercase (U+03B1 - U+03C9)
    if ((0x91 <= unicode[1]) && (unicode[1] <= 0xa9))
    {
        unicode[1] += 0x20;
    }

    switch (unicode[1])
    {
        case 0xb1:
            //α (alpha)
            *(*english)++ = 'A';
            goto Success;

        case 0xb2:
            //β (beta)
            *(*english)++ = 'B';
            goto Success;

        case 0xb3:
            //γ (gamma)
            *(*english)++ = 'G';
            goto Success;

        case 0xb4:
            //δ (delta)
            *(*english)++ = 'D';
            goto Success;

        case 0xb5:
            //ε (epsilon)
            *(*english)++ = 'E';
            goto Success;

        case 0xb6:
            //ζ (zeta)
            *(*english)++ = 'Z';
            goto Success;

        case 0xb7:
            //η (eta)
            *(*english)++ = 'H';
            goto Success;

        case 0xb8:
            //θ (theta)
            *(*english)++ = 'C';
            goto Success;

        case 0xb9:
            //ι (iota)
            *(*english)++ = 'I';
            goto Success;

        case 0xba:
            //κ (kappa)
            *(*english)++ = 'K';
            goto Success;

        case 0xbb:
            //λ (lambda)
            *(*english)++ = 'L';
            goto Success;

        case 0xbc:
            //μ (mu)
            *(*english)++ = 'M';
            goto Success;

        case 0xbd:
            //ν (nu)
            *(*english)++ = 'N';
            goto Success;

        case 0xbe:
            //ξ (xi)
            *(*english)++ = 'X';
            goto Success;

        case 0xbf:
            //ο (omicron)
            *(*english)++ = 'O';
            goto Success;

        case 0xc0:
            //π (pi)
            *(*english)++ = 'P';
            goto Success;

        case 0xc1:
            //ρ (rho)
            *(*english)++ = 'R';
            goto Success;

        case 0xc2:
        case 0xc3:
            //ςσ (sigma)
            *(*english)++ = 'S';
            goto Success;

        case 0xc4:
            //τ (tau)
            *(*english)++ = 'T';
            goto Success;

        case 0xc5:
            //υ (upsilon)
            *(*english)++ = 'Y';
            goto Success;

        case 0xc6:
            //φ (phi)
            *(*english)++ = 'F';
            goto Success;

        case 0xc7:
            //χ (chi)
            if (englishEnd <= (*english) + 4)
            {
                goto ErrorNoSpace;
            }
            *(*english)++ = '<';
            *(*english)++ = 'M';
            *(*english)++ = 'M';
            *(*english)++ = '>';
            goto Success;

        case 0xc8:
            //ψ (psi)
            *(*english)++ = 'Q';
            goto Success;

        case 0xc9:
            //ω (omega)
            *(*english)++ = 'W';
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

