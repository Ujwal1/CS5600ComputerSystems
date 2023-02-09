/*
 * polybius.h
 *
 *  Created on: Jan 23, 2023
 *      Author: ujwal
 */

#ifndef POLYBIUS_H_
#define POLYBIUS_H_

char* pbEncode(const char *plaintext, const char table[5][5]);
char* pbDecode(const char *ciphertext, const char table[5][5]);

#endif /* POLYBIUS_H_ */
