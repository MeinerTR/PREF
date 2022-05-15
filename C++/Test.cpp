#include <iostream>

#include "Prefs.h"

int main(void) {
    Prefs User; User.Path = "User.pref";
    unsigned int WIDTH;
    std::string UserName;
    try {
        UserName = User.STR("PLAYER.NAME");
    } catch (int ERRCODE) {
        if (ERRCODE == 0) {
            std::cout << "Prefs.Path is NULL!\n";
            return -1;
        } else if (ERRCODE == 1) {
            std::cout << "Unable to open " << User.Path << "!\n";
            return -1;
        } else if (ERRCODE == 2) {
            std::cout << "Unable to find " << User.CurrKey << " in " << User.Path << "!\n";
            return -1;
        }
    } std::cout << UserName << std::endl;
    try {
        WIDTH = User.INT("SCREEN.WIDTH");
    } catch (int ERRCODE) {
        if (ERRCODE == 0) {
            std::cout << "Prefs.Path is NULL!\n";
            return -1;
        } else if (ERRCODE == 1) {
            std::cout << "Unable to open " << User.Path << "!\n";
            return -1;
        } else if (ERRCODE == 2) {
            std::cout << "Unable to find " << User.CurrKey << " in " << User.Path << "!\n";
            return -1;
        } else if (ERRCODE == 3) {
            std::cout << "Unable to convert " << User.CurrKey << "'s value to int!\n";
            return -1;
        }
    } std::cout << WIDTH << std::endl;
    return 0;
}