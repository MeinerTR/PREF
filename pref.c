#include <stdio.h>
#include <stdlib.h>

#define pUI unsigned int
#define pCUI const unsigned int
#define pUC unsigned char
#define pCUC const unsigned char

typedef enum {True, False} Bool;
#define _ERROR(MSG) {perror(#MSG); exit(42);}

static pCUI pLength(pCUC *_STR7) {
    pUI _Output7 = 0;
    while (1) {
        if (_STR7[_Output7] == '\0') {
        break; } else { _Output7++; }
    } return _Output7;
}

pUC *prefGet(pCUC *_Path, pCUC *_Key7) {
    FILE *_File7 = fopen(_Path, "r");
    if (!_File7) { return NULL; }
    Bool _ADD7 = False, _Hope7 = True;
    pUI _CURR7 = 0, _CURR5 = 0;
    pUC *_Output7 = (pUC *) malloc (
        sizeof(pUC) ); char _CHR7;
    pCUI _LEN7 = pLength(_Key7);
    printf("%i\n", _LEN7);
    while (1) { _CHR7 = fgetc(_File7);
        if (_CHR7 == '\n') {
            if (_ADD7 == True) {
                printf("1...\n");
                return _Output7;
            } _Hope7 = True; _CURR7 = 0;
        } else if (_CHR7 == EOF) {
            if (_ADD7 == True) { return _Output7; } break; 
            } else {
                if (_ADD7 == True) {
                    _Output7 = realloc (
                    _Output7, sizeof(pUC) * _CURR5 + 1
                    ); _Output7[_CURR5] = _CHR7; _CURR5++;
                } else if (_Hope7 == True) {
                    if (_CHR7 != _Key7[_CURR7]) {
                        _Hope7 = False;         }
                    if (_CHR7 == ' ' & _CURR7 == _LEN7) {
                        _ADD7 = True; } else {_CURR7++; printf("3...\n");}
                }
        }
    } fclose(_File7);
    free(_Output7); return NULL;
}

int main(void) {
    pUC *Width = prefGet("./general.pref", "HelloWorld");
    if (!Width) _ERROR(Unable to get the variable!)
    printf("%s\n", Width);
    free(Width);
}
