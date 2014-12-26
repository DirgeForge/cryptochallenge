#include "set1.h"

// ------------------------------------------------------------
//	utils
// ------------------------------------------------------------

int hexToDec(char c)
{
	if ('0' <= c && c <= '9')
	{
		return c - '0';
	}
	if ('A' <= c && c <= 'F')
	{
		return c - 'A' + 10;
	}
	return c - 'a' + 10;
}

char decToHex(int n)
{
	if (0 <= n && n <= 9)
	{
		return '0' + n;
	}
	if (10 <= n && n <= 15)
	{
		return 'a' + (n - 10);
	}
}
std::string charToHex(char c)
{
	std::string result = "";
	result += decToHex(c >> 4);
	result += decToHex(c & 0x0f);
	return result;
}

int countAlphaNums(const char * in)
{
	unsigned int count = 0; 
	while (*in != '\0')
	{
		if (('a' <= *in && *in <= 'z') ||
			('A' <= *in && *in <= 'Z') ||
			('0' <= *in && *in <= '9') ||
			(' ' == *in))
		{
			count++;
		}
		in++;
	}
	return count;
}

// ------------------------------------------------------------
//	challenge 1 
//	convert hex to base64
// ------------------------------------------------------------

std::string hexToB64(const char * hex, unsigned int len)
{
	static const std::string b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string result = "";
    char b16Buf[3];
    char b64Quad[4];
    int i = 0;

    // store 6 hexes at a time into the buffer
    while (len > 0)
    {
        // combine two hexes into one index
        if (len > 1)
        {
            b16Buf[i++] = (hexToDec(*hex++) << 4) + hexToDec(*hex++);
            len -= 2;
        }
        else
        {
            b16Buf[i++] = hexToDec(*hex++) << 4;
            len = 0;
        }

        // buffer is full, convert and dump as base64
        if (i == 3)
        {
            b64Quad[0] = (b16Buf[0] & 0xfc) >> 2;
            b64Quad[1] = ((b16Buf[0] & 0x03) << 4) + ((b16Buf[1] & 0xf0) >> 4);
            b64Quad[2] = ((b16Buf[1] & 0x0f) << 2) + ((b16Buf[2] & 0xc0) >> 6);
            b64Quad[3] = b16Buf[2] & 0x3f;

            for (i = 0; i < 4; i++)
            {
                result += b64[b64Quad[i]];
            }
            i = 0;
        }
    }

    // buffer is still partially filled
    if (i > 0)
    {
        for (int j = i; j < 3; j++)
        {
            b16Buf[j] = '\0';
        }

        b64Quad[0] = (b16Buf[0] & 0xfc) >> 2;
        b64Quad[1] = ((b16Buf[0] & 0x03) << 4) + ((b16Buf[1] & 0xf0) >> 4);
        b64Quad[2] = ((b16Buf[1] & 0x0f) << 2) + ((b16Buf[2] & 0xc0) >> 6);
        b64Quad[3] = b16Buf[2] & 0x3f;

        for (int j = 0; j < i + 1; j++)
        {
            result += b64[b64Quad[j]];
        }

        while (i < 3)
        {
            result += '=';
            i++;
        }
    }

    return result;
}

// ------------------------------------------------------------
//	challenge 2 
//	write a function that takes two equal-length buffers and 
//	produces their XOR combination
// ------------------------------------------------------------

std::string fxor(const char * in, const char * key, unsigned int len)
{
	std::string result = "";

	while (len > 0)
	{
		result += decToHex((hexToDec(*in++) ^ hexToDec(*key++)));
		len--;
	}

	return result;
}


// ------------------------------------------------------------
// 	  challenge 3
// 	  single-byte XOR
// ------------------------------------------------------------

std::string sbxor(const char * in, char key, unsigned int len)
{
	std::string decoded = "";
	while (*in != '\0')
	{
		char c = hexToDec(*in++) << 4;
		if (*in != '\0')
		{
			c += hexToDec(*in++);
		}
		decoded += c ^ key;
	}
	return decoded;
}

// ------------------------------------------------------------
// 	  challenge 3
// 	  single-byte XOR
// ------------------------------------------------------------

/* i did it the stupid way in main.cpp */

// ------------------------------------------------------------
//		challenge 5
//		repeating-key XOR
// ------------------------------------------------------------
/*
	@param in character sequence to be encrypted
	@param key hex key sequence
	@param len length of the key sequence
	@return decoded string
*/
std::string rkxor(const char * in, const char * key, unsigned int len)
{
	std::string decoded = "";
	unsigned int count = 0;
	while (*in != '\0')
	{
		decoded += charToHex(*in ^ *(key + count));
		in++, count++;

		if (count >= len)
		{
			count = 0;
		}
	}
	return decoded;
}

// ------------------------------------------------------------
//		challenge 6
//		break repeating-key XOR
// ------------------------------------------------------------
/*
	@param *a character sequence
	@param *b character sequence
	@param n length of the sequences
	@return hammering distance between the two sequences
*/
int hamming(const char * a, const char * b, unsigned int n)
{
	std::string xord = "";
	for (unsigned i = 0; i < n; i++)
	{
		xord += *(a + i) ^ *(b + i);
	}

	int hammingDist = 0;
	for (unsigned i = 0; i < xord.length(); i++)
	{

		for (unsigned j = 1; j <= 128; j*=2)
		{
			if ((xord[i] & j) > 0)
			{
				hammingDist++;
			}

		}
	}
	return hammingDist;
}