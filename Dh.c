
#include <stdio.h>
int compute(int a, int m, int n)
{
    int r;
    int y = 1;
    while (m > 0)
    {
        r = m % 2;
        if (r == 1) {
            y = (y*a) % n;
        }
        a = a*a % n;
        m = m / 2;
    }
    return y;
}
int main()
{
    int p,g,A,B;            
    int Xa, Xb;      
    printf("Enter the common prime no.: ");
    scanf("%d",&p);
    printf("Enter the primitive root of %d : ",p);
    scanf("%d",&g);
    printf("Enter the private key of A 'Xa':  ");
    scanf("%d",&Xa);      
    A = compute(g, Xa, p);
    printf("Enter the private key of B 'Xb':  ");
    scanf("%d",&Xb);       
    B = compute(g, Xb, p);
    int keyA = compute(B, Xa, p);
    int keyB = compute(A, Xb, p);
    printf("Public Key of A:%d\n",A);
    printf("Public Key of B:%d\n",B);
    printf("Alice's secret key is %d\nBob's secret key is %d\n", keyA, keyB);
    return 0;
}

