#include <stdio.h>
#include <stdlib.h>

#define UI unsigned int
#define CUI const unsigned int
#define UC unsigned char
#define CUC const unsigned char

typedef enum {True, False} Bool;
#define ERROR(MSG) {perror(#MSG); exit(-1);}

CUI Length(CUC *STR) {
    UI Output = 0;
    while (1) {
        if (STR[Output] == '\0') {
            break; } Output++;
} return Output;                 }

static Bool ClassHere(CUC *Line, CUC *Class) {
    CUI _Length = Length(Class);
    for (UI Idx = 0; Idx < _Length; Idx++) {
        if (Line[Idx + 1] != Class[Idx])   {
            return False;                  }
    } if (Line[_Length + 1] == ']')        {
        return True;} else {return False;  }
                                           }

static Bool VariableHere(CUC *Line, CUC *Variable) {
    CUI _Length = Length(Variable);
    for (UI Idx = 0; Idx < _Length; Idx++) {
        if (Line[Idx] != Variable[Idx])    {
            return False;                  }
    } if (Line[_Length] == ':')            {
        return True;} else {return False;  }
                                           }

static UC *GetLine(FILE *File, CUC *Class, CUC *Variable) {
    char CHR; UI LLen = 0, VLen = 0, _Line = 3;
    UC *Line = (UC *) malloc (sizeof(UC) * _Line);
    Bool CorrectOne = False; while (CHR != -2) {
        CHR = fgetc(File);
        if (CHR == '\n' | CHR == EOF) {
            if (Line[0] == '[') {
                if (ClassHere(Line, Class) == True) {
                    CorrectOne = True; 
                } else {
                    CorrectOne = False;
                } if (CHR == EOF) {CHR = -2;}
            } else if (CorrectOne == True) {
                if (VariableHere(Line, Variable) == True) {
                    return Line;
                }  } free(Line);
            LLen = 0; VLen = 0; _Line = 3;
            Line = (UC *) malloc (sizeof(UC) * _Line);
        } else {
            if (CHR == ':') {
                VLen = LLen;
            } else if (LLen == _Line) {
                Line = (UC *) realloc (
                Line, sizeof(UC) * LLen + 1);
                _Line = LLen + 1; } 
                Line[LLen] = CHR; LLen++;
        }
    } return NULL;
}

UC *GetVariable(CUC *Path, CUC *Class, CUC *Variable) {
    FILE *File = fopen(Path, "r");
    if (!File) ERROR(Unable to open file!)
    UC *Line = GetLine(File, Class, Variable);
    if (Line == NULL) { fclose(File); return NULL; }
    CUI _Length = (Length(Line) - (Length(Variable) + 3));
    UC *Output = (UC *) malloc (sizeof(UC) * _Length);
    printf("%s::%i\n", Line, _Length);
    fclose(File);
    free(Line); return Output;
}

int main(void) {
    UC *WIDTH = GetVariable("./general.pref", "SCREEN", "HEIGHT");
    printf("%s\n", WIDTH);
    free(WIDTH);
}