#ifndef CHAT_H
#define CHAT_H

#include "sha1.h"
#include <unordered_map>

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
public:
    Chat();
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

    friend void test(Chat& c);

private:
    struct AuthData {
        AuthData();
        ~AuthData();
        AuthData(char _login[LOGINLENGTH], uint* sh1);
        AuthData& operator=(const AuthData& other);

        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
    };

    std::unordered_map<std::string, AuthData> hashTable;
    int data_count;

    int hashFunction(const std::string& key);
    int quadraticProbing(int index, int attempt);
};

#endif // CHAT_H