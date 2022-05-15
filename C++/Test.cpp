#include <iostream>
#include <string.h>

#include "Prefs.h"

int main(void) {
    Prefs User; User.Path = "User.pref";
    unsigned int WIDTH;
    std::string UserName;
    try {
        User.Change("PLAYER.NAME", "MeinerTR", User.Path);
    } catch (int ERRCODE) {
        switch (ERRCODE) {
            case (prefNULL): {
                std::cout << "Prefs.Path is NULL!\n";
                return -1;
            } case (prefPATH): {
                std::cout << "Unable to open " << User.Path << "!\n";
                return -1;
            } case (prefFIND): {
                std::cout << "Unable to find " << User.CurrKey << " in " << User.Path << "!\n";
                return -1;
            }
        }
    }
    try {
        UserName = User.STR("PLAYER.NAME");
    } catch (int ERRCODE) {
        switch (ERRCODE) {
            case (prefNULL): {
                std::cout << "Prefs.Path is NULL!\n";
                return -1;
            } case (prefPATH): {
                std::cout << "Unable to open " << User.Path << "!\n";
                return -1;
            } case (prefFIND): {
                std::cout << "Unable to find " << User.CurrKey << " in " << User.Path << "!\n";
                return -1;
            }
        }
    } std::cout << UserName << std::endl;
    try {
        WIDTH = User.INT("SCREEN.WIDTH");
    } catch (int ERRCODE) {
        switch (ERRCODE) {
            case (prefNULL): {
                std::cout << "Prefs.Path is NULL!\n";
                return -1;
            } case (prefPATH): {
                std::cout << "Unable to open " << User.Path << "!\n";
                return -1;
            } case (prefFIND): {
                std::cout << "Unable to find " << User.CurrKey << " in " << User.Path << "!\n";
                return -1;
            } case (prefTYPE): {
                std::cout << "Unable to convert " << User.CurrKey << "'s value to int!\n";
                return -1;
            }
        }
    } std::cout << WIDTH << std::endl;
    return 0;
}