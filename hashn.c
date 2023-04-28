#include <stdio.h>
#include <stdlib.h>

static int G[(1<<5) - 5 - 1];
static int N = (1<<5) - 5 - 1;

int fillG()
{
    int index = 0;
    for (int i = 0; i < 32; i++)
    {
        if (countBits(i) > 1)
        {
            //printf("%b\n",index);
            //printf("%b\n",i<<N);
            G[index] = i<<(N) ^ (1<<(N - index - 1));
            index++;
        }
    }
}

int countBits(int n)
{
    int count = 0;
    while (n) {
        n &= (n-1);
        count++;
    }
    return count;
}

int left_multiplyG(int a)
{
    int code = 0;
    int n = N;
    for (int i = 0; i < n; i++)
    {
        code = code^((a & 1<<i)>>i)*G[n - i - 1];
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

int main()
{
    fillG();

    //for (int i = 0; i < 26; i++)
    //{
    //    printf("%.31b\n",G[i]);
    //}
    for (unsigned int i = 0; i < (1<<26); i++)
    {
        if (isAdjacent(i,0))
        {
            printf("%d\n",i);
        }
    }
    return 0;
}
