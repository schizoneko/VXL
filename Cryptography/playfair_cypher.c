#include <stdio.h>
#include <string.h>
#include <ctype.h>

char table[5][5];

// Check if character is already in key table
int in_table(char c, int len) {
    for (int i = 0; i < len; i++)
        if (table[i / 5][i % 5] == c)
            return 1;
    return 0;
}

// Create key table
void create_table(char *key) {
    int i, k = 0;
    char c, alphabet[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    for (i = 0; key[i]; i++) {
        c = toupper(key[i] == 'J' ? 'I' : key[i]);
        if (!in_table(c, k) && isalpha(c))
            table[k / 5][k++ % 5] = c;
    }

    for (i = 0; alphabet[i]; i++) {
        if (!in_table(alphabet[i], k))
            table[k / 5][k++ % 5] = alphabet[i];
    }
}

// Print key table
void print_table() {
    printf("Key Table:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
}

// Find position of char in table
void find_pos(char c, int *row, int *col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (table[i][j] == c) {
                *row = i;
                *col = j;
            }
}

// Encrypt pair
void encrypt_pair(char a, char b, char *out) {
    int r1, c1, r2, c2;
    find_pos(a, &r1, &c1);
    find_pos(b, &r2, &c2);

    if (r1 == r2) { // same row
        out[0] = table[r1][(c1 + 1) % 5];
        out[1] = table[r2][(c2 + 1) % 5];
    } else if (c1 == c2) { // same column
        out[0] = table[(r1 + 1) % 5][c1];
        out[1] = table[(r2 + 1) % 5][c2];
    } else { // rectangle
        out[0] = table[r1][c2];
        out[1] = table[r2][c1];
    }
}

// Encrypt message
void encrypt(char *msg, char *enc) {
    char a, b;
    int len = strlen(msg), k = 0;

    for (int i = 0; i < len; i++) {
        a = toupper(msg[i] == 'J' ? 'I' : msg[i]);
        if (!isalpha(a)) continue;

        if (i + 1 == len || !isalpha(msg[i+1])) b = 'X';
        else b = toupper(msg[i+1] == 'J' ? 'I' : msg[i+1]);

        if (a == b) {
            encrypt_pair(a, 'X', &enc[k]);
            k += 2;
        } else {
            encrypt_pair(a, b, &enc[k]);
            k += 2;
            i++;
        }
    }
    enc[k] = '\0';
}

int main() {
    char key[] = "YOMAMA";
    char plaintext[] = "NILLKIGGA";
    char ciphertext[100];

    create_table(key);
    print_table();
    encrypt(plaintext, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
