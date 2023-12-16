#ifndef DOMACI_GRAF_H
#define DOMACI_GRAF_H

#include <iomanip>
#include <cmath>
#include "Stek.h"

class Graf {
    int brojCvorova;
    double** grane;
    string* cvorovi;

    void kopiraj(const Graf& graf);
    void premesti(Graf& graf);
    void brisi();

public:
    Graf(int bc, string* niz, double** matrica);
    Graf(const Graf& graf) { kopiraj(graf); }
    Graf(Graf&& graf) noexcept { premesti(graf); }
    ~Graf() { brisi(); }

    Graf& operator=(const Graf& graf);
    Graf& operator=(Graf&& graf) noexcept;

    [[nodiscard]] int dohvatiBrojCvorova() const { return brojCvorova; }
    [[nodiscard]] double** dohvatiGrane() const { return grane; }
    [[nodiscard]] string* dohvatiCvorove() const { return cvorovi; }

    friend ostream& operator<<(ostream& os, const Graf& g);

    void dodavanjeCvora(const string& s);
    void uklanjanjeCvora(const string& s);

    void dodavanjeGrane(const string& s1, const string& s2, double d);
    void uklanjanjeGrane(const string& s1, const string& s2);

    void nalazenjeNajslicnijihReci(const string& rec, int& brojNajslicnijihReci);
    void najkraciPutIzmedjuDveReci(const string& rec1, const string& rec2);
    void nalazenjeJakoPovezanihReci(const string& rec);
};

#endif //DOMACI_GRAF_H
