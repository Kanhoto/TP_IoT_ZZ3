#include <iostream>
#include <cstring>
#include <openssl/aes.h>

unsigned char cypheringCpt = 0;

const unsigned char key[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char iv[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

// Fonction de chiffrement AES
void encrypt_aes(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &aes_key, iv, AES_ENCRYPT);
}

// Fonction de déchiffrement AES
void decrypt_aes(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);
    AES_cbc_encrypt(ciphertext, plaintext, ciphertext_len, &aes_key, iv, AES_DECRYPT);
}

/*
int main() {
    unsigned char plaintext[] = "Bonjour le monde !";
    unsigned char key[] = "0123456789abcdef";
    unsigned char iv[] = "0123456789abcdef";
    unsigned char ciphertext[strlen((char*) plaintext)];
    unsigned char decryptedtext[strlen((char*) plaintext)];

    // Chiffrement AES
    encrypt_aes(plaintext, strlen((char*) plaintext), key, iv, ciphertext);
    cout << "Texte chiffré : ";
    for(int i = 0; i < strlen((char*) plaintext); i++) {
        cout << hex << (int) ciphertext[i];
    }
    cout << endl;

    // Déchiffrement AES
    decrypt_aes(ciphertext, strlen((char*) plaintext), key, iv, decryptedtext);
    cout << "Texte déchiffré : " << decryptedtext << endl;

    return 0;
}*/