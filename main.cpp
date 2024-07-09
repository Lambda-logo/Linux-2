#include "chat.h"

int main() {
    Chat chat;

    // Test registration and login procedures
    char login1[LOGINLENGTH] = "user1";
    char pass1[] = "password1";

    chat.reg(login1, pass1, strlen(pass1));
    bool success = chat.login(login1, pass1, strlen(pass1));

    class AuthManager {
    public:
        AuthManager() {}

        void reg(const std::string& login, const std::string& pass) {
            uint* pass_hash = sha1((char*)pass.c_str(), pass.length());
            chat.reg((char*)login.c_str(), pass_hash, SHA1HASHLENGTHBYTES);
            delete[] pass_hash;
        }

        bool login(const std::string& login, const std::string& pass) {
            uint* pass_hash = sha1((char*)pass.c_str(), pass.length());
            bool success = chat.login((char*)login.c_str(), pass_hash, SHA1HASHLENGTHBYTES);
            delete[] pass_hash;
            return success;
        }
        int AuthMan() {
            // Создаем объект класса AuthManager
            AuthManager authManager;

            // Регистрация пользователя
            std::string login1 = "user1";
            std::string pass1 = "password1";
            authManager.reg(login1, pass1);

            // Аутентификация пользователя
            bool success = authManager.login(login1, pass1);

            return 0;
        }
    return 0;
}