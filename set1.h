#ifndef SET1_H
#define SET1_H

#include <string>

/* utils */
int hexToDec(char c);
char decToHex(int n);
int countAlphaNums(const unsigned char *);

/* challenge 1 */
std::string hexToB64(const unsigned char*, unsigned int);

/* challenge 2 */
std::string fxor(const unsigned char *, const unsigned char *, unsigned int);

/* challenge 3 */
std::string sbxor(const unsigned char *, unsigned char, unsigned int);

/* challenge 4 */
// nope

/* challenge 5 */
std::string rkxor(const unsigned char *, const unsigned char *, unsigned int);

#endif