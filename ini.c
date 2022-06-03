#include "ini.h"

int main(void) {
    p_B Success = INI_Open("./WhereAreWe.ini");
    if (Success == p_F) {
        printf("FAILED!\n");
    } else {
        INI_Change("STAR", "Finally!");

        p_STR *Keys = INI_New_STR_List(2);
        Keys[0] = "STAR"; Keys[1] = "PLANET";
        p_LIST Sizes = INI_New_LEN_List(2);
        Sizes[0] = 4; Sizes[1] = 6; 
        p_STR *Values_STR = INI_Get_STRS(Keys, Sizes, 2);
        if (Values_STR != NULL) {
            printf("%s::%s\n", Values_STR[0], Values_STR[1]);
        } else {
            printf("GOT NULL!\n");
        }
        free(Keys); free(Values_STR); free(Sizes);
        Keys = INI_New_STR_List(2);
        Keys[0] = "STAR_SIZE"; Keys[1] = "PLANET_SIZE";
        Sizes = INI_New_LEN_List(2);
        Sizes[0] = 9; Sizes[1] = 11;
        p_LIST Values_INT = INI_Get_INTS(Keys, Sizes, 2);
        if (Values_INT != NULL) {
            if (Values_INT[0] == INI_NULL_KEY_INT) {
                printf("\"%s\" variable in \"%s\" must be an integer!\n", Keys[0], INI_Path);
            } else if (Values_INT[1] == INI_NULL_KEY_INT) {
                printf("\"%s\" variable in \"%s\" must be an integer!\n", Keys[1], INI_Path);
            } else {
                printf("%i::%i\n", Values_INT[0], Values_INT[1]);
            }
        } else {
            printf("GOT NULL!\n");
        }
        free(Keys); free(Values_INT); free(Sizes);
        // p_I Size = INI_Get_INT("STAR_SIZE", 9);
        // if (Size != INI_NULL_KEY_INT) {
        //     if (Size != INI_NULL_TYPE) {
        //         printf("%i\n", Size);
        //     } else {
        //         printf("Cannot transform \"%s\" to a number in \"%s\"!\n", INI_Key, INI_Path);
        //     }
        // } else {
        //     printf("Cannot find \"%s\" in \"%s\"!\n", INI_Key, INI_Path);
        // } p_I Size2 = INI_Get_INT("PLANET_SIZE", 9);
        // if (Size2 != INI_NULL_KEY_INT) {
        //     if (Size2 != INI_NULL_TYPE) {
        //         printf("%i\n", Size2);
        //     } else {
        //         printf("Cannot transform \"%s\" to a number in \"%s\"!\n", INI_Key, INI_Path);
        //     }
        // } else {
        //     printf("Cannot find \"%s\" in \"%s\"!\n", INI_Key, INI_Path);
        // } 
        INI_Close();
    }
}