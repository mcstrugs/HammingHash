#include <stdio.h>

static int G[4] = {0b1101000, 0b1010100, 0b0110010, 0b1110001};

int countBits(int n)
{
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int isAdjacent(int a, int b)
{
    int a_code = 0^((a & 0b1000)>>3)*G[0] ^ ((a & 0b0100)>>2)*G[1] ^ ((a & 0b0010)>>1)*G[2] ^ (a & 0b0001)*G[3];
    int b_code = 0^((b & 0b1000)>>3)*G[0] ^ ((b & 0b0100)>>2)*G[1] ^ ((b & 0b0010)>>1)*G[2] ^ (b & 0b0001)*G[3];
    int diff = a_code ^ b_code;
    int weight = countBits(diff);

    return weight == 3;
}

int main() {
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            printf("%d",isAdjacent(i,j));
        }
        printf("\n");
    }
    return 0;
}
