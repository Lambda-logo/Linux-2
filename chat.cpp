#include "chat.h"
#include <cstring>

Chat::Chat() : data_count(0) {}

int Chat::hashFunction(const std::string& key) {
    // Implement hash function here
}

int Chat::quadraticProbing(int index, int attempt) {
    // Implement quadratic probing logic here
}

void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    uint* pass_hash = sha1(_pass, pass_length);

    std::string loginStr(_login);
    AuthData newUserData(_login, pass_hash);

    int index = hashFunction(loginStr);
    int attempt = 0;
    while (hashTable.find(loginStr) != hashTable.end()) {
        index = quadraticProbing(index, ++attempt);
    }

    hashTable[loginStr] = newUserData;
    data_count++;
}

bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Implement login logic here
}

void test(Chat& c) {
    // Implement test cases here
}