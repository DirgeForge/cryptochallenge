#include "set1.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#define TEST 6

using namespace std;
int main()
{
    #if TEST == 1
    const string hex = 
    "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    string encoded = hexToB64(hex.c_str(), hex.length());

    cout << encoded << endl;
    const string check = 
    "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    for (unsigned i = 0; i < check.length() && i < hex.length(); i++)
    {
        if (check[i] != encoded[i])
        {
            cout << "Mismatch found at index " << i 
            << "(found " << hex[i] << "; expected " << encoded[i] << ")" << endl;
        }
    }

    #elif TEST == 2
    const string hex = "1c0111001f010100061a024b53535009181c";
    const string key = "686974207468652062756c6c277320657965";
    const string check = "746865206b696420646f6e277420706c6179";

    string fxord = fxor(hex.c_str(), key.c_str(), key.length());
    cout << fxord << endl << check << endl;
    for (unsigned i = 0; i < check.length() && i < hex.length(); i++)
    {
        if (check[i] != fxord[i])
        {
            cout << "Mismatch found at index " << i 
            << "(found " << fxord[i] << "; expected " << check[i] << ")" << endl;
        }
    }

    #elif TEST == 3
    // spoiler alert: the key is 'X'
    const string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    const string hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    string decoded;
    int alphanums = 0, keyIdx = 0;
    for (unsigned i = 0; i < key.length(); i++)
    {
        string s = sbxor(hex.c_str(), key[i], hex.length());
        if (alphanums < countAlphaNums(s.c_str()))
        {
            decoded = s;
            alphanums = countAlphaNums(s.c_str());
            keyIdx = i;
        }
    }
    cout << "key[" << key[keyIdx] << "]: " << decoded << endl;

    #elif TEST == 4
    const string key = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    string decoded;
    int alphanums = 0, keyIdx = 0, row = 0;

    ifstream f("4.txt");
    string * hex = new string[400];
    int len = 0;
    while (f.good() && len < 400)
    {
        f >> hex[len];
        len++;
    }

    // i shouldn't be bruteforcing this, but :meh:
    for (unsigned i = 0; i < key.length(); i++)
    {
        for (unsigned j = 0; j < len; j++)
        {
            string s = sbxor(hex[j].c_str(), key[i], hex[j].length());
            if (alphanums < countAlphaNums(s.c_str()))
            {
                decoded = s;
                alphanums = countAlphaNums(s.c_str());
                keyIdx = i;
                row = j;
            }
        }
    }
    cout << "row[" << row << "], key[" << key[keyIdx] << "]: " << decoded << endl;


    #elif TEST == 5
    const string message[] = 
    {"Burning 'em, if you ain't quick and nimble", "I go crazy when I hear a cymbal"};
    const string key = "ICE";
    
    for (unsigned int i = 0; i < 2; i++)
    {
        string enc = rkxor(message[i].c_str(), key.c_str(), 3);
        cout << enc << endl;
    }


    #elif TEST == 6
    /* // this should pass
    string a = "this is a test";
    string b = "wokka wokka!!!";
    cout << "got: " << hamming(a.c_str(), b.c_str(), 14) << ", expected: " << 37;
    */

    fstream f("6.txt");
    string txt = "";
    while (f.good())
    {
        string s; 
        f >> s;
        txt += b64ToHex(s.c_str());
    }
    double dist = 320;
    int keysize;
    for (int i = 2; i <= 40; i++)
    {
        double ham = 
        hamming(txt.substr(0, i).c_str(), txt.substr(i, i).c_str(), i) / static_cast<double>(i);
        if (ham < dist)
        {
            dist = ham;
            keysize = i;
        }

    }
    cout << showpoint << dist << " " << keysize;

    #endif
    return 0;
}
