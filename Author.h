#pragma once
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

using namespace std;

class Author {
  string ORCID;
  string name;
  string workplace;
  string email;
  vector<int> paperlist;
  pair<unsigned long long int, unsigned long long int> hashed_password;

public:
  Author() {
    ORCID.reserve(32);
    name.reserve(256);
    workplace.reserve(256);
    email.reserve(256);
    paperlist.reserve(512);
  }
  string getORCID() { return ORCID; }
  string getWorkplace() { return workplace; }
  string getName() { return name; }
  string getEmail() { return email; }
  vector<int> *getPaperList() { return &paperlist; }
  void modify_Name(string new_name) { name = new_name; }
  void modify_Email(string new_email) { email = new_email; }
  void modify_workplace(string new_workplace) { workplace = new_workplace; }
  static unsigned long long int hash1(const string &str,
                                      unsigned long long int mod) {
    unsigned long long int hash = 0;
    for (char c : str) {
      hash = (hash * 31 + c) % mod;
    }
    return hash;
  }
  static unsigned long long int hash2(const string &str,
                                      unsigned long long int mod) {
    unsigned long long int hash = 0;
    for (char c : str) {
      hash = (hash * 17 + c) % mod;
    }
    return hash;
  }
  static pair<unsigned long long int, unsigned long long int>
  HASH(string orgpw) {
    unsigned long long int mod1 = 1e9 + 7;
    unsigned long long int mod2 = 1e9 + 9;
    unsigned long long int h1 = hash1(str, mod1);
    unsigned long long int h2 = hash2(str, mod2);
    return make_pair(h1, h2);
  }
  bool Verify(string password) {
    if (HASH(password) == hashed_password)
      return 1;
    return 0;
  }
};