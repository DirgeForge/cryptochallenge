#ifndef SET1_H
#define SET1_H

#include <string>

/* utils */
int hexToDec(char c);
char decToHex(int n);
int countAlphaNums(const char *);

/* challenge 1 */
std::string hexToB64(const char*, unsigned int);

/* challenge 2 */
std::string fxor(const char *, const char *, unsigned int);

/* challenge 3 */
std::string sbxor(const char *, char, unsigned int);

/* challenge 4 */
// nope

/* challenge 5 */
std::string rkxor(const char *, const char *, unsigned int);

/* challenge 6 */
int hamming(const char *, const char *, unsigned int);

#endif