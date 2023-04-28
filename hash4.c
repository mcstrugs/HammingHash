#include <stdio.h>
#include <stdlib.h>

static int G[11] =
    {(0b1100<<11) + (1<<10),
    (0b0110<<11) + (1<<9),
    (0b0011<<11) + (1<<8),
    (0b1010<<11) + (1<<7),
    (0b0101<<11) + (1<<6),
    (0b1001<<11) + (1<<5),
    (0b1110<<11) + (1<<4),
    (0b1101<<11) + (1<<3),
    (0b1011<<11) + (1<<2),
    (0b0111<<11) + (1<<1),
    (0b1111<<11) + (1)};

static int minWeights[35] =
{3,5,9,17,32,
36,40,50,64,66,
72,84,128,132,138,
144,193,256,258,260,
280,416,512,514,524,
528,545,832,1024,1030,
1032,1040,1120,1281,1664};

int countBits(int n)
{
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int left_multiplyG(int a)
{
    int code = 0;
    int n = 11;
    for (int i = 0; i < n; i++)
    {
        code = code^((a & 1<<i)>>i)*G[11 - i - 1];
    }
    return code;
}

int isAdjacent(int a, int b)
{
    int a_code = left_multiplyG(a);
    int b_code = left_multiplyG(b);
    int diff = a_code ^ b_code;
    int weight = countBits(diff);

    return weight == 3;
}

int main() {
    // compute minimum weight words
    int c;
    int hash = 0;
    int index = 0;
    while((c = getchar()) != EOF)
    {
        while(c > 0) {
            if (c % 2 == 1)
            {
                index += 1;
                index %= 35;
                hash ^= minWeights[index];
            } else {
                index -= 1;
                index %= 35;
                hash ^= minWeights[index];
            }
            hash %= 2048;
            c >>= 1;
        }
        //hash ^= minWeights[c % 35];
        //hash %= 2048;
    }
    printf("%d\n",hash);

    return 0;
}
