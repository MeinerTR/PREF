#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define pUI unsigned int
#define pCUI const unsigned int
#define pUC unsigned char
#define pCUC const unsigned char

pUC *prefGet(pCUC *_Path7, pCUC *_Key7) {
    FILE *_File7 = fopen(_Path7, "r");
    if (!_File7) { return NULL; }
    pUI _ADD7 = 0; bool _Hope7 = true;
    pUI _CURR7 = 0, _CURR5 = 0;
    pUC *_Output7 = (pUC *) calloc (
        1, sizeof(pUC) ); char _CHR7;
    while (1) { _CHR7 = fgetc(_File7);
        if (_CHR7 == '\n') {
            if (_ADD7 == true) {
                return _Output7;
            } _Hope7 = true; _CURR7 = 0;
        } else if (_CHR7 == EOF) {
            if (_ADD7 == true) { return _Output7; } break; 
        } else {
                if (_ADD7 == true) {
                    _Output7 = realloc (
                    _Output7, sizeof(pUC) * _CURR5 + 1
                    ); _Output7[_CURR5] = _CHR7; _CURR5++;
                } else if (_Hope7 == true) {
                    if (_CHR7 != _Key7[_CURR7]) {
                        _Hope7 = false;         }
                    if (_CHR7 == ' ') {
                        _ADD7 = true; } else {_CURR7++; }
                }
        }
    } fclose(_File7);
    free(_Output7); return NULL;
}

void prefChange(pCUC *_Path7, pCUC *_Key7, pCUC *_NewVar7, pCUC *_SaveAS7) {
    FILE *_File7 = fopen(_Path7, "r"), *_File5 = fopen("OOPSIE.VIRUS", "w");
    fclose(_File5); _File5 = fopen("OOPSIE.VIRUS", "a");
    pUI _Length7 = 0; char _CHR7 = 0; bool _Search7 = true;
    pUC *_Line7 = (pUC *) malloc ( sizeof(pUC) * 5 ); bool _Write7 = true;
    while (_CHR7 != -2) { _CHR7 = fgetc(_File7);
        if (_CHR7 == '\n' | _CHR7 == EOF) {
            if (_Line7[4] != 5) {
                if (_Write7 == 1) { 
                    fputs(_Line7, _File5); fputc('\n', _File5);
                } else {
                    _Write7 = 1;
                    fprintf(_File5, "%s %s\n", _Key7, _NewVar7);
                }  }
            if (_CHR7 == EOF) {_CHR7 = -2;} else {
                free(_Line7);  _Line7 = (pUC *) malloc (
                                        sizeof(pUC) * 5);
                _Length7 = 0; _Search7 = 1;
            }
        } else {
            if (_Length7 > 4) {
                _Line7 = realloc(
                _Line7, _Length7 + 1);
            } _Line7[_Length7] = _CHR7;
            if (_Search7 == true) {
                if (_CHR7 != _Key7[_Length7]) {
                    _Search7 = false;
                }
                if (_CHR7 == ' ') { _Write7 = false;
                } } _Length7++; }
    } fclose(_File7); fclose(_File5); free(_Line7);
    remove(_Path7); rename("OOPSIE.VIRUS", _SaveAS7);
}

int main(void) {
    pUC *Star = prefGet("./WhereAreWe.pref", "STAR"),
    *Planet = prefGet("./WhereAreWe.pref", "PLANET");
    printf("\nBefore changed!\n");
    printf("STAR: %s\nPLANET: %s\n", Star, Planet);
    prefChange("./WhereAreWe.pref", "STAR", "Son", "WhereAreWe.pref");
    prefChange("./WhereAreWe.pref", "PLANET", "Mars", "WhereAreWe.pref");
    Star = prefGet("./WhereAreWe.pref", "STAR");
    Planet = prefGet("./WhereAreWe.pref", "PLANET");
    printf("\nAfter changed!\n");
    printf("STAR: %s\nPLANET: %s\n\n", Star, Planet);
    free(Star); free(Planet);
}
