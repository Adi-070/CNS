#include<stdio.h>
int key1[8],key2[8];
int n,i,j;
void leftshift(int key[10],int num)
{
    int temp1,temp2;
    for(j=0;j<num;j++)
    {
        temp1=key[0];
        for(i=0;i<4;i++)
        {
            key[i]=key[i+1];
        }
        key[4]=temp1;
        temp2=key[5];
        for(i=5;i<9;i++)
        {
            key[i]=key[i+1];
        }
        key[9]=temp2;
    }
}

void keygeneration(int key[10])
{
    int p10[10]={3,5,2,7,4,10,1,9,8,6},p8[8]={6,3,7,4,8,5,10,9};
    int keyp10[10];
    
    for(i=0;i<10;i++)
    {
        keyp10[i]=key[(p10[i]-1)]; 
    }
    leftshift(keyp10,1);
    printf("key1:");
    for(i=0;i<8;i++)
    {
        key1[i]=keyp10[(p8[i]-1)];
        printf("%d",key1[i]);
    }
    leftshift(keyp10,2);
    printf("\nkey2:");
    for(i=0;i<8;i++)
    {
        key2[i]=keyp10[(p8[i]-1)];
        printf("%d",key2[i]);
    }
}

void sboxfunction(int sr[4],int xor[8])
{
    int sbox[2][2]={{0,1},{2,3}};
    int s0[4][4]={{1,0,3,2},{3,2,1,0},{0,2,1,3},{3,1,3,2}};
    int s1[4][4]={{0,1,2,3},{2,0,1,3},{3,0,1,0},{2,1,0,3}}; 
    int sresult[2];
    i=0;
    sresult[0]=s0[sbox[xor[0]][xor[3]]][sbox[xor[1]][xor[2]]];
    sresult[1]=s1[sbox[xor[4]][xor[7]]][sbox[xor[5]][xor[6]]];
    for(j=0;j<2;j++)
    {
        switch (sresult[j])
        {
            case 0:sr[i++]=0;
            sr[i++]=0;
            break;
            case 1:sr[i++]=0;
            sr[i++]=1;
            break;
            case 2:sr[i++]=1;
            sr[i++]=0;
            break;
            case 3:sr[i++]=1;
            sr[i++]=1;
            break;
        }
    }
}

void cryption(int pt[8],int k1[8],int k2[8])
{
    int ip[8]={2,6,3,1,4,8,5,7};
    int sr[4],et[8];
    int inverseip[8]={4,1,3,5,7,2,8,6};
    int ep[8]={4,1,2,3,2,3,4,1};
    int aip[8],aep[8],xor[8],as[8],as1[8];
    int p4[4]={2,4,3,1};
    //intial permutation
    for(i=0;i<8;i++)
    {
        aip[i]=pt[(ip[i]-1)];
    }
    //expansion permutation
    for(i=0;i<8;i++)
    {
        aep[i]=aip[(ep[i]+3)];
    }
    //xor of key1(for encryption)/key2(for decryption) and expamsion permutation
    for(i=0;i<8;i++)
    {
        xor[i]=aep[i]^k1[i];
    }
    
    sboxfunction(sr,xor);//finding sbox values
    
    //creation of array on which expansion permutation is applied
    for(i=0;i<4;i++)
    {
        as[i+4]=sr[p4[i]-1]^aip[i];
        as[i]=aip[i+4];
    }
    
    //expansion permutation
    for(i=0;i<8;i++)
    {
        aep[i]=as[(ep[i]+3)];
    }
    
    //xor of key2(for encryption)/key1(for decryption) and expamsion permutation
    for(i=0;i<8;i++)
    {
        xor[i]=aep[i]^k2[i];
    }
    
    sboxfunction(sr,xor);
    
    //creation of array to which inverse initial permutation is applied
    for(i=0;i<4;i++)
    {
        as1[i]=sr[p4[i]-1]^as[i];
        as1[i+4]=as[i+4];
    }
    
    if(n==1)
    {printf("\nencrypted text:");}
    else
    {printf("\n decrypted text:");}
    
    //inverse initial permutation
    for(i=0;i<8;i++)
    {
        et[i]=as1[(inverseip[i]-1)];
        printf("%d",et[i]);
    }
}

void main()
{
    int key[10],pt[8];
    
    //plain text input
    printf("enter the 8 bit text:\n");
    for(i=0;i<8;i++)
    {
        scanf("%d",&pt[i]);
    }
    //key input
    printf("enter the 10 bit key:\n");
    for(i=0;i<10;i++)
    {
        scanf("%d",&key[i]);
    }
    //printing plaintext and key
    printf("the 8 bit text:");
    for(i=0;i<8;i++)
    {
        printf("%d",pt[i]);
    }
    printf("\nthe 10 bit key:");
    for(i=0;i<10;i++)
    {
        printf("%d",key[i]);
    }
    printf("\nenter 1 for encryption or 2 for decryption:");
    scanf("%d",&n);
    //key generation 
    keygeneration(key);
    
    //encryption and decryption
    switch (n)
    {
        case 1 :cryption(pt,key1,key2);
        break;
        case 2:cryption(pt,key2,key1);
        break;
        default:printf("invalid input");
        break;
    }
}
