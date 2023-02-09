/*
 * cipher.c
 *
 *  Created on: Jan 23, 2023
 *      Author: ujwal
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "polybius.h"

int main(int argc, char *argv[]) {

	const char table[5][5] = {
			{'A', 'B', 'C', 'D', 'E'},
			{'F', 'G', 'H', 'I', 'K'},
			{'L', 'M', 'N', 'O', 'P'},
			{'Q', 'R', 'S', 'T', 'U'},
			{'V', 'W', 'X', 'Y', 'Z'}
	};

	char *operation = argv[1];
	char *text = argv[2];

	if (strcmp(operation, "-e") == 0) {
		char *ciphertext = pbEncode(text, table);
		printf("Ciphertext: %s\n", ciphertext);
	}
	else if(strcmp(operation, "-d") == 0) {
		char *decodedText = pbDecode(text, table);
		printf("Decoded plaintext: %s\n", decodedText);
	}
	else {
		printf("Invalid Operation. Use -e for encryption and -d for decryption");
		return 1;
	}
	return 0;
}

