#include <stdio.h>
#include <string.h>

#define SBOX_SIZE 256

void swap(unsigned char *a, unsigned char *b) {
    unsigned char temp = *a;
    *a = *b;
    *b = temp;
}

void ksa(unsigned char *key, int key_length, unsigned char *S) {
    int i, j = 0;
    for (i = 0; i < SBOX_SIZE; i++) {
        S[i] = i;
    }
    for (i = 0; i < SBOX_SIZE; i++) {
        j = (j + S[i] + key[i % key_length]) % SBOX_SIZE;
        swap(&S[i], &S[j]);
    }
}

void prga(unsigned char *S, unsigned char *plaintext, unsigned char *ciphertext, int length, unsigned char *keystream) {
    int i = 0, j = 0, k;
    for (k = 0; k < length; k++) {
        i = (i + 1) % SBOX_SIZE;
        j = (j + S[i]) % SBOX_SIZE;
        swap(&S[i], &S[j]);
        unsigned char K = S[(S[i] + S[j]) % SBOX_SIZE];
        keystream[k] = K; // Lưu dòng khóa
        ciphertext[k] = plaintext[k] ^ K;
    }
}

void print_hex(unsigned char *data, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char key[] = "NillKigger";
    int key_length = strlen((char *)key);
    
    unsigned char plaintext[] = "Hanoi University of Science and Technology";
    int text_length = strlen((char *)plaintext);
    
    unsigned char S[SBOX_SIZE];
    unsigned char ciphertext[text_length];
    unsigned char keystream[text_length];
    
    ksa(key, key_length, S);
    prga(S, plaintext, ciphertext, text_length, keystream);
    
    printf("Keystream: ");
    print_hex(keystream, text_length);
    
    printf("Ciphertext: ");
    print_hex(ciphertext, text_length);
    
    return 0;
}
