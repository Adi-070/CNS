#include <stdio.h>
#include <ctype.h>
#include<string.h>


// Function to perform Caesar cipher encryption
void caesarEncrypt(char *message, int key) {
    int i = 0;
    char ch;

    while (message[i]) {
        ch = message[i];

        if (isalpha(ch)) {
            if (isupper(ch)) {
                ch = (ch - 'A' + key) % 26 + 'A';
            } else {
                ch = (ch - 'a' + key) % 26 + 'a';
            }
        }

        message[i] = ch;
        i++;
    }
}

// Function to perform Caesar cipher decryption
void caesarDecrypt(char *encryptedMessage, int key) {
    int i = 0;
    char ch;

    while (encryptedMessage[i]) {
        ch = encryptedMessage[i];

        if (isalpha(ch)) {
            if (isupper(ch)) {
                ch = (ch - 'A' - key + 26) % 26 + 'A';
            } else {
                ch = (ch - 'a' - key + 26) % 26 + 'a';
            }
        }

        encryptedMessage[i] = ch;
        i++;
    }
}

int main() {
    char message[100];
    int key;

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the key (a positive integer): ");
    scanf("%d", &key);

    // Remove trailing newline from the message
    message[strcspn(message, "\n")] = '\0';

    printf("Original message: %s\n", message);

    // Encrypt the message
    caesarEncrypt(message, key);
    printf("Encrypted message: %s\n", message);

    // Decrypt the encrypted message
    caesarDecrypt(message, key);
    printf("Decrypted message: %s\n", message);

    return 0;
}
