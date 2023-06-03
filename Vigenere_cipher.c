#include<stdio.h>
#include<string.h>
 
int main(){
    char msg[30],key[30];
    printf("Enter the plaintext:");
    scanf("%s",msg);
    printf("Enter the key:");
    scanf("%s",key);
    int msgLen = strlen(msg), keyLen = strlen(key), i, j;
    char A[27][27];
    for(i=0;i<26;i++){
    for(j=0;j<26;j++){
    A[i][j]='A'+((j+i)%26);}}
    for(i=0;i<26;i++){
    for(j=0;j<26;j++){
    printf("%c",A[i][j]);}
    printf("\n");}
    char newKey[msgLen], encryptedMsg[msgLen], decryptedMsg[msgLen];
    for(i = 0, j = 0; i < msgLen; ++i, ++j){
        if(j == keyLen)
            j = 0;
 
        newKey[i] = key[j];
    }
    newKey[i] = '\0';
            for(i = 0; i < msgLen; ++i)
        encryptedMsg[i] = ((msg[i] + newKey[i]) % 26) + 'A';
    encryptedMsg[i] = '\0';
    for(i = 0; i < msgLen; ++i)
        decryptedMsg[i] = (((encryptedMsg[i] - newKey[i]) + 26) % 26) + 'A';
    decryptedMsg[i] = '\0';
    printf("Original Message: %s", msg);
    printf("\nKey: %s", key);
    printf("\nNew Generated Key: %s", newKey);
    printf("\nEncrypted Message: %s", encryptedMsg);
    printf("\nDecrypted Message: %s", decryptedMsg);
 
return 0;
}
