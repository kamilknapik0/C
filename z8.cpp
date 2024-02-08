#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;


char szyfrujDeszyfruj(char znak, char klucz) {
    return znak ^ klucz;
}

void szyfrujDeszyfrujPlik(const string& plikWejsciowy, const string& plikWyjsciowy, char klucz, bool szyfruj) {
    ifstream plikWe(plikWejsciowy.c_str(), ios::binary);
    ofstream plikWy(plikWyjsciowy.c_str(), ios::binary);
    if (!plikWe) {
        cout << "Nie mozna otworzyc pliku wejsciowego: " << plikWejsciowy << endl;
        return;
    }
    if (!plikWy) {
        cout << "Nie mozna otworzyc pliku wyjsciowego: " << plikWyjsciowy << endl;
        return;
    }
    char znak;
    while (plikWe.get(znak)) {
        if (szyfruj)
            znak = szyfrujDeszyfruj(znak, klucz);
        else
            znak = szyfrujDeszyfruj(znak, klucz);
        plikWy.put(znak);
    }
    plikWe.close();
    plikWy.close();
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Nieprawidlowe uzycie programu." << endl;
        cout << "Poprawne wywolanie: " << argv[0] << " [s|d] <plik_wejsciowy> <plik_wyjsciowy> <klucz>" << endl;
        return 1;
    }
    char operacja = argv[1][0];
    string plikWejsciowy = argv[2];
    string plikWyjsciowy = argv[3];
    char klucz = argv[4][0];
    bool szyfruj = (operacja == 's');
    szyfrujDeszyfrujPlik(plikWejsciowy, plikWyjsciowy, klucz, szyfruj);
    cout << "Operacja zakonczona pomyslnie." << endl;
    return 0;
}

