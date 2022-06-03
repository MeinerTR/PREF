#ifndef INI_H
#define INI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define p_CO const
#define p_UN unsigned

#define p_I int
#define p_UI p_UN p_I
#define p_CUI p_CO p_UI

#define p_C char
#define p_UC p_UN p_C
#define p_CUC p_CO p_UC

#define p_LIST p_UI *
#define p_V void
#define p_STR p_UC *

p_STR INI_Key;
p_STR INI_Path;
FILE *INI_FILE;

#define INI_Free(ED)    \
    if (ED != NULL) {   \
        free(ED);       \
        ED = NULL;      \
    }

typedef enum {p_F, p_T} p_B;

#define INI_NULL_KEY (p_STR) "*[idX]!;.;!-"
// #define INI_NULL_KEYS p_STR *    \
// Pikachu = (p_STR *) calloc (0, 0);      \
//                             return Pikachu
#define INI_NULL_TYPE 0x404
#define INI_NULL_KEY_INT 0x727
// #define INI_NULL_KEYS_INT p_LIST  \ 
// Pikachu = (p_LIST) calloc (0, 0);        \
//                             return Pikachu

#define If_INI_Equals(A, B, L)              \
    for (iDx = 0; iDx < L; iDx++) {         \
        if (A[iDx] != B[iDx]) {             \
            break;                          \
        }                                   \
    } if (iDx == L)

p_B INI_Open(p_UC *Path) {
    INI_FILE = fopen(Path, "r");
    INI_Path = Path;
    if (!INI_FILE) {
        return p_F;
    } else {
        return p_T;
    }
}

p_STR INI_Get_STR(p_UC *Key, p_CUI Length) {
    p_UI Idx = 0, Mode = 1, KLen, iDx;
    p_B GotFirst = p_F; fseek(INI_FILE, 0, SEEK_SET);
    p_C CHR; p_UC *CurrKey, *Output;

    INI_Key = Key;

    CurrKey = (p_STR) calloc (0, 0);
    Output = (p_STR) calloc (0, 0);

    while (CHR != -2) {
        CHR = fgetc(INI_FILE);

        if (CHR == '\n') {
            if (Mode == 2) {
                return Output;
            } else {
                Idx = 0; Mode = 1;
                GotFirst = p_F;
                INI_Free(CurrKey);
            }
        } else if (CHR == EOF) {
            if (Mode == 2) {
                return Output;
            } else {
                return INI_NULL_KEY;
            } CHR = -2;
        } else {
            if (Mode != 0) {
                if (Mode == 1) {
                    if (CHR == ' ')  {
                        CurrKey[Idx] = '\0';
                        If_INI_Equals(CurrKey, Key, Length) {
                            Mode = 2;
                            KLen = Idx;
                        } else {
                            Mode = 0;
                        }
                    } else {
                        CurrKey = (p_STR) realloc ( CurrKey,
                            (Idx + 1) * sizeof(p_UC)
                        ); CurrKey[Idx] = CHR;
                    }
                } else {
                    if (GotFirst == p_F) {
                        if (CHR != ' ') {
                            GotFirst = p_T;
                            KLen++;
                        }
                    } if (GotFirst == p_T) {
                        Output = (p_STR) realloc ( Output,
                            sizeof((Idx - KLen) + 1) * sizeof(p_UC)
                        ); Output[Idx - KLen] = CHR;
                    }
                } Idx++;
            }
        } 
    }
}

p_STR *INI_New_STR_List(p_CUI Length) {
    p_STR *Output = (p_STR *) calloc (Length, sizeof(p_STR));
    return Output;
}

p_LIST INI_New_LEN_List(p_CUI Length) {
    p_LIST Output = (p_LIST) calloc (Length, sizeof(p_UI));
    return Output;
}

p_STR *INI_Get_STRS(p_STR *Keys, p_LIST Lengths, p_UI Length) {
    p_UI Idx = 0, Mode = 1, KLen, iDx, idX = 0;
    p_B GotFirst = p_F; fseek(INI_FILE, 0, SEEK_SET);
    p_C CHR; p_UC *CurrKey, *Value, **Output;

    INI_Key = Keys[idX];

    CurrKey = (p_STR) calloc (0, 0);
    Value = (p_STR) calloc (0, 0);
    Output = (p_STR *) calloc (Length, 0);

    while (CHR != -2) {
        CHR = fgetc(INI_FILE);

        if (CHR == '\n') {
            if (Mode == 2) { 
                Output[idX] = (p_STR) malloc ((Idx - KLen + 1) * sizeof(p_UC));
                strcpy(Output[idX], Value);
                INI_Key = Keys[idX];
                INI_Free(Value);
                if (idX == Length - 1) {
                    INI_Free(CurrKey);
                    return Output;
                } idX++;
            } Idx = 0; Mode = 1;
            GotFirst = p_F;
            INI_Free(CurrKey);
        } else if (CHR == EOF) {
            INI_Free(CurrKey);
            if (Mode == 2) {
                Output[idX] = (p_STR) malloc ((Idx - KLen + 1) * sizeof(p_UC));
                strcpy(Output[idX], Value);
                INI_Free(Value); idX++;
                if (idX < Length + 1) {
                    return NULL;
                } else {
                    printf("HOW\n");
                    return Output;
                }
            } INI_Free(Value); CHR = -2;
        } else {
            if (Mode != 0) {
                if (Mode == 1) {
                    if (CHR == ' ')  {
                        for (p_UI idx = 0; idx < Length; idx++) {
                            If_INI_Equals(CurrKey, Keys[idx], Lengths[idx]) {
                                if (Lengths[idx] == Idx) {
                                    Mode = 2;
                                    KLen = Idx;
                                    break;
                                } else {
                                    if (Mode != 2) {
                                        Mode = 0;
                                    }
                                }
                            } else {
                                Mode = 0;
                            }
                        }
                    } else {
                        CurrKey = (p_STR) realloc ( CurrKey,
                            (Idx + 1) * sizeof(p_UC)
                        ); CurrKey[Idx] = CHR;
                    }
                } else {
                    if (GotFirst == p_F) {
                        if (CHR != ' ') {
                            GotFirst = p_T;
                            KLen++;
                        }
                    } if (GotFirst == p_T) {
                        Value = (p_STR) realloc (
                            Value, (Idx - KLen + 1) * sizeof(p_UC)
                        ); Value[Idx - KLen] = CHR;
                    }
                } Idx++;
            }
        } 
    }
}

p_I INI_Get_INT(p_UC *Key, p_CUI Length) {
    p_UI Idx = 0, Mode = 1, KLen, iDx;
    p_B GotFirst = p_F; fseek(INI_FILE, 0, SEEK_SET);
    p_C CHR; p_UC *CurrKey, *Output;

    INI_Key = Key;

    CurrKey = (p_STR) calloc (0, 0);
    Output = (p_STR) calloc (0, 0);

    while (CHR != -2) {
        CHR = fgetc(INI_FILE);

        if (CHR == '\n') {
            if (Mode == 2) {
                p_I CopyCat = atoi(Output);
                if (!CopyCat) {
                    return INI_NULL_TYPE;
                } else {
                    return CopyCat;
                }
            } else {
                Idx = 0; Mode = 1;
                GotFirst = p_F;
                INI_Free(CurrKey)
            }
        } else if (CHR == EOF) {
            if (Mode == 2) {
                p_I CopyCat = atoi(Output);
                if (!CopyCat) {
                    return INI_NULL_TYPE;
                } else {
                    return CopyCat;
                }
            } else {
                return INI_NULL_KEY_INT;
            } CHR = -2;
        } else {
            if (Mode != 0) {
                if (Mode == 1) {
                    if (CHR == ' ')  {
                        CurrKey[Idx] = '\0';
                        If_INI_Equals(CurrKey, Key, Length) {
                            Mode = 2;
                            KLen = Idx;
                        } else {
                            Mode = 0;
                        }
                    } else {
                        CurrKey = (p_STR) realloc ( CurrKey,
                            (Idx + 1) * sizeof(p_UC)
                        ); CurrKey[Idx] = CHR;
                    }
                } else {
                    if (GotFirst == p_F) {
                        if (CHR != ' ') {
                            GotFirst = p_T;
                            KLen++;
                        }
                    } if (GotFirst == p_T) {
                        Output = (p_STR) realloc ( Output,
                            sizeof((Idx - KLen) + 1) * sizeof(p_UC)
                        ); Output[Idx - KLen] = CHR;
                    }
                } Idx++;
            }
        } 
    }
}

p_LIST INI_Get_INTS(p_STR *Keys, p_LIST Lengths, p_UI Length) {
    p_UI Idx = 0, Mode = 1, KLen, iDx, idX = 0;
    p_B GotFirst = p_F; fseek(INI_FILE, 0, SEEK_SET);
    p_C CHR; p_UC *CurrKey, *Value; p_LIST Output;

    INI_Key = Keys[idX];

    CurrKey = (p_STR) calloc (0, 0);
    Value = (p_STR) calloc (0, 0);
    Output = (p_LIST) calloc (Length, 0);

    while (CHR != -2) {
        CHR = fgetc(INI_FILE);

        if (CHR == '\n') {
            if (Mode == 2) { 
                p_UI CopyCat = atoi(Value);
                INI_Key = Keys[idX];
                if (!CopyCat) {
                    Output[idX] = INI_NULL_KEY_INT;
                } else {
                    Output[idX] = CopyCat;  
                } INI_Free(Value);
                if (idX == Length - 1) {
                    INI_Free(CurrKey);
                    return Output;
                } idX++;
            } Idx = 0; Mode = 1;
            GotFirst = p_F;
            INI_Free(CurrKey);
        } else if (CHR == EOF) {
            INI_Free(CurrKey);
            if (Mode == 2) {
                p_UI CopyCat = atoi(Value);
                INI_Key = Keys[idX];
                if (!CopyCat) {
                    Output[idX] = INI_NULL_KEY_INT;
                } else {
                    Output[idX] = CopyCat;  
                } INI_Free(Value); idX++;
                if (idX < Length + 1) {
                    return NULL;
                } else {
                    printf("HOW\n");
                    return Output;
                }
            } INI_Free(Value); CHR = -2;
        } else {
            if (Mode != 0) {
                if (Mode == 1) {
                    if (CHR == ' ')  {
                        for (p_UI idx = 0; idx < Length; idx++) {
                            If_INI_Equals(CurrKey, Keys[idx], Lengths[idx]) {
                                if (Lengths[idx] == Idx) {
                                    Mode = 2;
                                    KLen = Idx;
                                    break;
                                } else {
                                    if (Mode != 2) {
                                        Mode = 0;
                                    }
                                }
                            } else {
                                Mode = 0;
                            }
                        }
                    } else {
                        CurrKey = (p_STR) realloc ( CurrKey,
                            (Idx + 1) * sizeof(p_UC)
                        ); CurrKey[Idx] = CHR;
                    }
                } else {
                    if (GotFirst == p_F) {
                        if (CHR != ' ') {
                            GotFirst = p_T;
                            KLen++;
                        }
                    } if (GotFirst == p_T) {
                        Value = (p_STR) realloc (
                            Value, (Idx - KLen + 1) * sizeof(p_UC)
                        ); Value[Idx - KLen] = CHR;
                    }
                } Idx++;
            }
        } 
    }
}

p_V INI_Change(p_STR Key, p_STR Value) {
    FILE *VIRUS = fopen("OOPSIE.VIRUS", "w");
    fclose(VIRUS); p_C CHR; p_STR _Key;
    p_UI Mode = 1, Idx = 0, iDx; 
    VIRUS = fopen("OOPSIE.VIRUS", "a");

    _Key = (p_STR) calloc (0, 0);
    fseek(INI_FILE, 0, SEEK_SET);

    while (CHR != -2) {
        CHR = fgetc(INI_FILE);

        if (CHR == '\n') {
            if (Mode == 2) {
                fputs(Value, VIRUS);
            } Mode = 1; Idx = 0;
            INI_Free(_Key); fputc('\n', VIRUS);
            _Key = (p_STR) calloc (0, 0);
        } else if (CHR == EOF) {
            if (Mode == 2) {
                fputc(' ', VIRUS);
                fputs(_Key, VIRUS);
            } CHR = -2;
        } else {
            if (Mode == 1) {
                if (CHR == ' ') {
                    fputc(' ', VIRUS);
                    If_INI_Equals(_Key, Key, Idx) {
                        Mode = 2;
                    } else {
                        Mode = 0;
                    }
                } else {
                    _Key = (p_STR) realloc (
                        _Key, (Idx + 1) * sizeof(p_UC)
                    ); _Key[Idx] = CHR; fputc(CHR, VIRUS);
                }
            } else if (Mode == 0) {
                fputc(CHR, VIRUS);
            }
        } Idx++;
    } fclose(VIRUS); rename(INI_Path, "RainbowCat.exe");
    rename("OOPSIE.VIRUS", INI_Path); remove("RainbowCat.exe");
}

p_V INI_Close(p_V) {
    if (INI_FILE) {
        fclose(INI_FILE);
    }
}

#endif // INI_H