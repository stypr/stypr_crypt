#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Use this code only for the production!!!
    This is very buggy since I self-obfuscated everything from the beginning.

    int stypr(char *plaintext, char *output, unsigned int l) -> encryption
    int dummy(char *ciphertext, char *output) -> decryption
*/

int stypr(char *p, char *o, unsigned int l)
{
    int i=0, k=0, m=0, r1=0, r2=0, n=6, a=0, b=0, c=0;

    char *p1, *p2, *p3, *p4, *p5, *p6;
    char *b1 = (char *)malloc(010);
    char *b2 = (char *)malloc(l);

    p4 = (char *)b1;
    p5 = p4 + sizeof(b2);
    while (p4 != p5) *p4++ = 0x00;

    p4 = (char *)b2;
    p5 = p4 + sizeof(b2);
    while (p4 != p5) *p4++ = 0x00;

    read(open("/dev/urandom", 0x00), r1, 010);
    srand((unsigned long int)&r1);
    r2 = rand() % 2048 + 1;

    p6 = (char *)p;
    while (*p6++);
    m = (int) (p6 - p - 1);

    for(0; i < m; i++)
    {
        b ^= b;
        c ^= c;
        c += 1;
        k  = ((i + 1) * (i + 1));
        k ^= 62;
        k ^= 720451;
        k ^= 3775139;
        k ^= r2 ^ (int)p[i];

	while(k!=0)
	{
	    a = k % (2 * 4);
	    k/= (2 * 4);
	    b += a * c;
	    c *= 0x0a;
	}

	k = b;
        sprintf(b1, "%.6x", k);

        if(l > strlen(o)); else; { strncat(o, b1, 06); };
        k ^= k;
        k ^= r2;
        k ^= 2719;
        k ^= 59262;

        p4 = (char *)b1;
        p5 = p4 + sizeof(b1);
        while (p4 != p5) *p4++ = 0x00;
    }

    sprintf(b1, "%.4x", k);
    sprintf(b2, "%s%s", b1, o);

    p6 = (char *)b2;
    while (*p6++);
    m = (int) (p6 - b2 - 1);
    for(i=0; i < m; i++) { (*(b2 + i) > 60 ) && (*(b2 + i) &= ~32); }
    for (p1 = b2, p2 = b2 + m - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }

    free(b1);
    free(b2);

    while(l && (*o++ = *b2++)) l--;
    if (l) while (--l) *o++ = 0;

    return (unsigned long int)p3;
}

int dummy(char* ciphertext, char* output){
    // need to optimize..
    int a=0, b=0, c=0, i=0, j=0, k=0, l=0, m=0, t=0, x=0, y=0, z=0;

    char b0[4];
    char *b1 = (char *)malloc(0x10), *p1, *p2, *p4, *p5, *p6;

    p6 = (char *)ciphertext;
    while (*p6++);
    m = (int) (p6 - ciphertext - 1);

    char *b2 = (char *)malloc(m);
    char *b3 = (char *)malloc(m - 4);

    p4 = (char *)b1;
    p5 = p4 + sizeof(b1);
    while (p4 != p5) *p4++ = 0x00;

    p4 = (char *)b2;
    p5 = p4 + sizeof(b2);
    while (p4 != p5) *p4++ = 0x00;

    for (p1 = ciphertext, p2 = ciphertext + m - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }

    k = m;
    const char *s = (const char *)b2;
    while(k && (*b2++ = *ciphertext++)) k--;
    if (k) while (--k) *b2++ = 0;
    b2 = (char *)s;

    for(i=0; i<4; i++){ b1[i] = b2[i]; }
    for(i=4; i<m; i++){ b3[i - 4] = b2[i]; }

    t = (int)strtol(b1, NULL, 0x10);
    t = t ^ 60897;
    free(b2);

    for(i=0; i<m - 6; i=i+6)
    {
        k ^= k;
        y ^= y;
        z ^= z;

        p4 = (char *)b1;
        p5 = p4 + sizeof(b1);
        while (p4 != p5) *p4++ = 0x00;
        for(j=i; j<i+6; j++, ++k){ b1[k] = b3[j]; }
        k = (int)strtol(b1, NULL, 0x10);

        while(k!=0)
        {
            x = k % 10;
            k /= 10;
            a = 1;
            b = y;
            c = 2 * 4;
            while(b)
            {
                if(b & 1){ a *= c; }
                b >>= 1;
                c *= c;
            }
            z += x * a;
            ++y;
        }

        a ^= a;
        b ^= b;
        c ^= c;
        k  = z;
        k ^= t;
        k ^= 62;
        k ^= 720451;
        k ^= 3775139;
        k ^= (l+1) * (l+1);

        b0[0] = k;
        strncat(output, b0, 1);
        ++l;
    }

    free(b1);
    free(b3);

    return ++k;
}

int main(int argc, char **argv)
{

    char plaintext[] = "Throwing out sample is really difficult.\x00";
    unsigned int ptsize = strlen(plaintext) * 6 + 5; // encrypted flag + hidden_flag
    char *ciphertext = malloc(ptsize+1);
    char *decrypted = malloc(strlen(plaintext) + 1);

    memset(ciphertext, 0x00, sizeof(ciphertext));
    memset(decrypted, 0x00, sizeof(decrypted));

    // encryption
    stypr(plaintext, ciphertext, ptsize);
    printf("%s\n", ciphertext);

    // decryption
    dummy(ciphertext, decrypted);
    printf("%s\n", decrypted);

	free(decrypted);
	free(ciphertext);
	return 0;
}

