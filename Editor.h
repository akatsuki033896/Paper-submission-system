#pragma once
#include <vector>
#include "Author.h"

class Editor
{
private:
    int id;
    pair<unsigned long long int, unsigned long long int> hashed_password;
    vector<int> paperlist;
public:
    Editor()
    {
        paperlist.reserve(4096);
    }
    static unsigned long long int hash1(const string & str, unsigned long long int mod)
    {
        unsigned long long int hash = 0;
        for (char c : str) {
            hash = (hash * 31 + c) % mod;
        }
        return hash;
    }
    static unsigned long long int hash2(const string & str, unsigned long long int mod)
    {
        unsigned long long int hash = 0;
        for (char c : str) {
            hash = (hash * 17 + c) % mod;
        }
        return hash;
    }
    static pair<unsigned long long int, unsigned long long int> HASH(string orgpw)
    {
        unsigned long long int mod1 = 1e9 + 7;
        unsigned long long int mod2 = 1e9 + 9;
        unsigned long long int h1 = hash1(str, mod1);
        unsigned long long int h2 = hash2(str, mod2);
        return make_pair(h1, h2);
    }
    bool Verify(string password)
    {
        if (HASH(password) == hashed_password)
            return 1;
        return 0;
    }
}