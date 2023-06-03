#include<stdio.h>
#include<string.h>
#include<ctype.h>
int N;
char et[30];
char dt[30];

void hillcipheren(int keymatrix[N][N],char plaintext[],int l)
{
    int ptmatrix[l][1],result[l][1];
    int x=0;
    while(x<strlen(plaintext)){
    
    for(int i=0;i<l;i++){
        if((x+i)<strlen(plaintext)){
            ptmatrix[i][0]=(int)tolower(plaintext[x+i])-97;
        }
        else{
            ptmatrix[i][0]=((int)'z')-97;
        }
    }
    
    for (int i = 0; i < l; ++i)
    {
          for (int j = 0; j < 1; ++j) 
          {
              result[i][j]=0;
                 for (int k = 0; k < l; ++k) {
                    result[i][j] += keymatrix[i][k] * ptmatrix[k][j];
                    }
                 et[x+i]=(result[i][j]%26)+97;
          }
    }
    
    x=x+l;
    }
}

void hillcipherde(int invkeymatrix[N][N],char enctext[],int l)
{
    int etmatrix[l][1],result1[l][1];
    int x=0;
    while(x<strlen(enctext)){
    
        for(int i=0;i<l;i++){
            if((x+i)<strlen(enctext)){
            etmatrix[i][0]=(int)tolower(enctext[x+i])-97;
            }
        }
        for (int i = 0; i < l; ++i) {
              for (int j = 0; j < 1; ++j) {
              result1[i][j]=0;
                 for (int k = 0; k < l; ++k) {
                 result1[i][j] += invkeymatrix[i][k] * etmatrix[k][j];
                         }
                 dt[x+i]=(result1[i][j]%26)+97;
                 }
        }
        x=x+l;
    }
}
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n)
{
	int i = 0, j = 0;
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{

			if (row != p && col != q)
			{
				temp[i][j++] = A[row][col];

				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}


int determinant(int A[N][N], int n)
{
	int D = 0;
	if (n == 1)
		return A[0][0];
	int temp[N][N];
	int sign = 1;

	for (int f = 0; f < n; f++)
	{

		getCofactor(A, temp, 0, f, n);
		D += sign * A[0][f] * determinant(temp, n - 1);


		sign = -sign;
	}
	return D;
}


void adjoint(int A[N][N],int adj[N][N])
{
	if (N == 1)
	{
		adj[0][0] = 1;
		return;
	}

	int sign = 1, temp[N][N];
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{

			getCofactor(A,temp, i, j, N);


			sign = ((i+j)%2==0)? 1: -1;


			adj[j][i] = (sign)*(determinant(temp, N-1));
		}
	}
}


int inverse(int A[N][N])
{

	int det = determinant(A, N);
	if (det == 0)
	{
		printf("Singular matrix, can't find its inverse");
		return 0;
	}
	printf("\ndeterminant=%d\n",det);
	return det;
}


 int multipleinverse(int r2){
     int t1=0,t2=1,q=0;
     int t,r1=26,r;
     while(r2!=0){
         q=r1/r2;
         r=r1%r2;
         t=(t1-(t2*q));
         r1=r2;
         r2=r;
         t1=t2;
         t2=t;
     }
     return t1;
 }


void main()
{
    int z;
    int det,mi;
    char plaintext[30],key[30];
    float s;
    printf("enter the plain text:\n");
    scanf("%s",plaintext);
    printf("\nenter n\n");
    scanf("%d",&N);
    int A[N][N];
    int adj[N][N];
    printf("\nenter input matrix\n");
    for (int i=0; i<N; i++){
    		for (int j=0; j<N; j++){
    			scanf( "%d",&A[i][j]);
    	}
    }
    	printf( "\nInput matrix is :\n");
    	for (int i=0; i<N; i++){
    		for (int j=0; j<N; j++){
    			printf( "%d \t",A[i][j]);
    	}
    printf("\n");
    }
    hillcipheren(A,plaintext,N);
    printf("\nencrypted text:\n");
    printf("%s \n\n",et);
    printf("adjoint matrix:\n");
    adjoint(A, adj);
    for (int i=0; i<N; i++){
    for (int j=0; j<N; j++){
    printf( "%d \t",adj[i][j]);
    	}
    printf("\n");
    }
    det=inverse(A);
    if(det==0){
    printf("inverse does not exist\n");
    return;
    }
    else
    {
    	mi=multipleinverse(det%26);
    	printf("\nmultiple inverse is :%d\n",mi);
    	if(det<0){
    	z=-1;
    }
    else{
    	z=1;
    }
    for (int i=0; i<N; i++){
    		for (int j=0; j<N; j++){
    			adj[i][j]=(z*mi*adj[i][j])%26;
    			if(adj[i][j]<0){
    			adj[i][j]=26+adj[i][j];
    			}
    	}
    }
    printf("\ninverse matrix:\n");
    for (int i=0; i<N; i++){
    		for (int j=0; j<N; j++){
    			printf( "%d \t",adj[i][j]);
    	}
    printf("\n");
    }
    	}
    hillcipherde(adj,et,N);
    printf("\ndecrypted text:\n");
    printf("%s \n",dt);
}
