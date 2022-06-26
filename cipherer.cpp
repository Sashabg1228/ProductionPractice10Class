#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<cctype>

using namespace std;

// Class handler for ciphering the deck
class Cipherer
{
public:
    void cipherDeck(const string filename, const string key, const char initialVector)
    {
        string result;
        
        //variables for reading the file
        string line; 
        string helperString;
        vector<char> plaintext;

        // opening the file
        fstream file(filename);

        //reading the file
        getline(file, line);
        
        //parse line
        stringstream parsingLine(line);
        
        while (getline(parsingLine, helperString, ' ')) 
        {
            plaintext.push_back(helperString[0]);
        }

        //actualy cyphering the deck
        for (int i = 0; i < 52; i++)
        {
            if (i == 0) 
            {
                result = cipherChar(plaintext[0], key, initialVector);
            } 
            else
            {
                result += cipherChar(plaintext[i], key, result[i - 1]);
            }
        }

        //writing the file
        for (int i = 0; i < 52; i++)
        {
            file << result[i] << " ";
        }

        //closing the file
        file.close();
    }
private:
    string cipherChar(char plaintext, const string key, const char initialVector)
    {
        string result;

        // exoring the initial vectr and the plaintext
        result = plaintext ^ initialVector;

        //actualy ciphering the char
        if (isalpha(plaintext))
        {
            (plaintext - 'A' + makeToNum(key)) % 26 + 'A';
        }
        else
        {
            (plaintext - '0' + makeToNum(key)) % 10 + '1';
        }
    }

    int makeToNum(const string key)
    {   
        int result = 0;

        int len = key.length();
        for (int i = 0; i < len; i++)
        {
            result += key[i];
        }

        return result;
    }
};