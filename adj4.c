#include <stdio.h>

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
    for (int i = 0; i < 2048; i++)
    {
        for (int j = 0; j < 2048; j++)
        {
            printf("%d",isAdjacent(i,j));
        }
        printf("\n");
    }
    return 0;
}
