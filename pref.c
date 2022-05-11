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

pUC *prefGet(pCUC *_Path7, pCUC *_Key7) {
    FILE *_File7 = fopen(_Path7, "r");
    if (!_File7) { return NULL; }
    Bool _ADD7 = False, _Hope7 = True;
    pUI _CURR7 = 0, _CURR5 = 0;
    pUC *_Output7 = (pUC *) malloc (
        sizeof(pUC) ); char _CHR7;
    // pCUI _LEN7 = pLength(_Key7);
    while (1) { _CHR7 = fgetc(_File7);
        if (_CHR7 == '\n') {
            if (_ADD7 == True) {
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
                    if (_CHR7 == ' ') { //  & _CURR7 == _LEN7
                        _ADD7 = True; } else {_CURR7++; }
                }
        }
    } fclose(_File7);
    free(_Output7); return NULL;
}

void prefChange(pCUC *_Path7, pCUC *_Key7, pCUC *_NewVar7, pCUC *_SaveAS7) {
    FILE *_File7 = fopen(_Path7, "r"), *_File5 = fopen("OOPSIE.VIRUS", "w");
    fclose(_File5); _File5 = fopen("OOPSIE.VIRUS", "a");
    pUI _Length7 = 0, _LEN7 = pLength(_Key7); char _CHR7 = 0; Bool _Search7 = True;
    pUC *_Line7 = (pUC *) malloc ( sizeof(pUC) * 5 ); Bool _Write7 = True;
    while (_CHR7 != -2) { _CHR7 = fgetc(_File7);
        if (_CHR7 == '\n' | _CHR7 == EOF) { // :( --- ); BUGGY ;( --- ):
            if (_Line7[4] != 5) {
                if (_Write7 == True) { 
                    fputs(_Line7, _File5); fputc('\n', _File5);
                } else {
                    _Write7 = True;
                    fprintf(_File5, "%s %s\n", _Key7, _NewVar7);
                }  } free(_Line7); 
            _Line7 = (pUC *) malloc (
                    sizeof(pUC) * 5);
            _Length7 = 0; _Search7 = True;
            if (_CHR7 == EOF) {_CHR7 = -2;}
        } else {
            if (_Length7 > 4) {
                _Line7 = realloc(
                _Line7, _Length7 + 1);
            } _Line7[_Length7] = _CHR7;
            if (_Search7 == True) {
                if (_CHR7 != _Key7[_Length7]) {
                    _Search7 = False;
                } if (_Length7 == _LEN7) {
                if (_CHR7 == ' ') { _Write7 = False;
                } } } _Length7++; }
    } fclose(_File7); fclose(_File5); free(_Line7);
    remove(_Path7); rename("OOPSIE.VIRUS", _SaveAS7);
}

int main(void) {
    pUC *PreStar = prefGet("./General.pref", "STAR"),
        *PrePlanet = prefGet("./General.pref", "PLANET");
    printf("Before changed!\n");
    printf("STAR: %s\nPLANET: %s\n", PreStar, PrePlanet);
    prefChange("./General.pref", "STAR", "Sun", "General.pref");
    prefChange("./General.pref", "PLANET", "Mars", "General.pref");
    free(PreStar); free(PrePlanet);
    pUC *NewStar = prefGet("./General.pref", "STAR"),
        *NewPlanet = prefGet("./General.pref", "PLANET");
    printf("After changed!\n");
    printf("STAR: %s\nPLANET: %s\n", NewStar, NewPlanet);
    free(NewStar); free(NewPlanet);
}
