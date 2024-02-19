#include "Graf.h"

Graf::Graf(int bc, string* niz, double** matrica) {
    brojCvorova = bc;
    cvorovi = niz;
    grane = matrica;
}

void Graf::kopiraj(const Graf& graf) {
    brojCvorova = graf.brojCvorova;
    grane = new double* [brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        grane[i] = new double[brojCvorova];
        for (int j = 0; j < brojCvorova; j++) {
            grane[i][j] = graf.grane[i][j];
        }
    }

    cvorovi = new string[brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        cvorovi[i] = graf.cvorovi[i];
    }
}

void Graf::premesti(Graf& graf) {
    brojCvorova = graf.brojCvorova;
    grane = graf.grane;
    graf.grane = nullptr;
    cvorovi = graf.cvorovi;
    graf.cvorovi = nullptr;
}

void Graf::brisi() {
    delete[] cvorovi;
    for (int i = 0; i < brojCvorova - 1; i++)
        delete[] grane[i];
    delete[] grane;
}

Graf& Graf::operator=(const Graf& graf) {
    if (this != &graf) {
        brisi();
        kopiraj(graf);
    }
    return *this;
}

Graf& Graf::operator=(Graf&& graf)  noexcept {
    if (this != &graf) {
        brisi();
        premesti(graf);
    }
    return *this;
}

ostream& operator<<(ostream& os, const Graf& g) {
    for (int i = 0; i < g.brojCvorova; i++) os << g.cvorovi[i] << " ";
    os << endl;
    for (int i = 0; i < g.brojCvorova; i++) {
        for (int j = 0; j < g.brojCvorova; j++) {
            os << fixed << setw(4) << setprecision(2) << g.grane[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

void Graf::dodavanjeCvora(const string& s) {
    brojCvorova++;

    auto noviCvorovi = new string[brojCvorova];
    for (int i = 0; i < brojCvorova - 1; i++) {
        noviCvorovi[i] = cvorovi[i];
    }
    noviCvorovi[brojCvorova - 1] = s;

    auto noveGrane = new double* [brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        noveGrane[i] = new double[brojCvorova];
        for (int j = 0; j < brojCvorova; j++) {
            if (i == brojCvorova - 1 && j == brojCvorova - 1) noveGrane[i][j] = 0;
            else if (i == brojCvorova - 1 || j == brojCvorova - 1) noveGrane[i][j] = INFINITY;
            else noveGrane[i][j] = grane[i][j];
        }
    }

    brisi();
    cvorovi = noviCvorovi;
    grane = noveGrane;
}

void Graf::uklanjanjeCvora(const string& s) {
    int indeksZaIzbacivanje;
    for (int i = 0; i < brojCvorova; i++) {
        if (cvorovi[i] == s) {
            indeksZaIzbacivanje = i;
            break;
        }
    }

    brojCvorova--;

    auto noviCvorovi = new string[brojCvorova];
    int k = 0;
    for (int i = 0; i < brojCvorova + 1; i++) {
        if (i != indeksZaIzbacivanje) {
            noviCvorovi[k++] = cvorovi[i];
        }
    }

    auto noveGrane = new double* [brojCvorova];
    int m = 0, n;
    for (int i = 0; i < brojCvorova + 1; i++) {
        n = 0;
        if (i != indeksZaIzbacivanje) {
            noveGrane[m] = new double[brojCvorova];
            for (int j = 0; j < brojCvorova + 1; j++) {
                if (j != indeksZaIzbacivanje) {
                    noveGrane[m][n++] = grane[i][j];
                }
            }
            m++;
        }
    }

    brisi();
    cvorovi = noviCvorovi;
    grane = noveGrane;
}

void Graf::dodavanjeGrane(const string& s1, const string& s2, double d) {
    int m = -1, n = -1;
    for (int j = 0; j < brojCvorova; j++) {
        if (cvorovi[j] == s1) {
            m = j;
            break;
        }
    }

    for (int j = 0; j < brojCvorova; j++) {
        if (cvorovi[j] == s2) {
            n = j;
            break;
        }
    }

    if (m != -1 && n != -1) {
        grane[m][n] = d;
    }
}

void Graf::uklanjanjeGrane(const string& s1, const string& s2) {
    int m = -1, n = -1;
    for (int j = 0; j < brojCvorova; j++) {
        if (cvorovi[j] == s1) {
            m = j;
            break;
        }
    }

    for (int j = 0; j < brojCvorova; j++) {
        if (cvorovi[j] == s2) {
            n = j;
            break;
        }
    }
    if (m != -1 && n != -1) {
        grane[m][n] = INFINITY;
    }
}

void Graf::nalazenjeNajslicnijihReci(const string& rec, int& brojNajslicnijihReci) {
    //Dijkstra
    int pozicijaReci;
    for (int i = 0; i < brojCvorova; i++) {
        if (cvorovi[i] == rec) {
            pozicijaReci = i;
            break;
        }
    }

    auto slicnostSaOstalimRecima = new double[brojCvorova];
    auto poseceniCvorovi = new bool[brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        slicnostSaOstalimRecima[i] = grane[pozicijaReci][i];
        poseceniCvorovi[i] = false;
    }

    poseceniCvorovi[pozicijaReci] = true;
    int pozicijaMaksSlicnosti = 0;
    for (int i = 0; i < brojCvorova - 1; i++) {
        if (i != pozicijaReci) {
            double maksSlicnost = 0;

            for (int j = 0; j < brojCvorova; j++) {
                if (slicnostSaOstalimRecima[j] > maksSlicnost && slicnostSaOstalimRecima[j] != INFINITY && !poseceniCvorovi[j] && j != pozicijaReci) {
                    maksSlicnost = slicnostSaOstalimRecima[j];
                    pozicijaMaksSlicnosti = j;
                }
            }

            poseceniCvorovi[pozicijaMaksSlicnosti] = true;

            for (int j = 0; j < brojCvorova; j++) {
                if (!poseceniCvorovi[j] && slicnostSaOstalimRecima[pozicijaMaksSlicnosti] * grane[pozicijaMaksSlicnosti][j] != INFINITY && ((slicnostSaOstalimRecima[j] != INFINITY &&
                                                                                                                                             slicnostSaOstalimRecima[pozicijaMaksSlicnosti] * grane[pozicijaMaksSlicnosti][j] > slicnostSaOstalimRecima[j]) || slicnostSaOstalimRecima[j] == INFINITY)) {
                    slicnostSaOstalimRecima[j] = slicnostSaOstalimRecima[pozicijaMaksSlicnosti] * grane[pozicijaMaksSlicnosti][j];
                }
            }
        }
    }

    int brojCvorovaDoKojihPostojiPut = 0;
    for (int i = 0; i < brojCvorova; i++) if (slicnostSaOstalimRecima[i] != INFINITY && slicnostSaOstalimRecima[i] != 0) brojCvorovaDoKojihPostojiPut++;
    if (brojCvorovaDoKojihPostojiPut < brojNajslicnijihReci) brojNajslicnijihReci = brojCvorovaDoKojihPostojiPut;

    auto najslicnijeReci = new string[brojNajslicnijihReci];

    for (int i = 0; i < brojNajslicnijihReci; i++) {
        int maksIndeks = -1;
        for (int j = 0; j < brojCvorova; j++) {
            if (slicnostSaOstalimRecima[j] != INFINITY && j != pozicijaReci) {
                if (maksIndeks == -1) maksIndeks = j;
                else if (slicnostSaOstalimRecima[j] > slicnostSaOstalimRecima[maksIndeks]) maksIndeks = j;
            }
        }
        slicnostSaOstalimRecima[maksIndeks] = INFINITY;
        najslicnijeReci[i] = cvorovi[maksIndeks];
    }


    if (!brojNajslicnijihReci) cout << "Zadata rec nema slicne reci." << endl;
    else for (int i = 0; i < brojNajslicnijihReci; i++) cout << najslicnijeReci[i] << endl;
    delete[] slicnostSaOstalimRecima;
    delete[] poseceniCvorovi;
    delete[] najslicnijeReci;
}

void Graf::najkraciPutIzmedjuDveReci(const string& rec1, const string& rec2) {
    //Dijkstra
    int pozicijaReci1;
    for (int i = 0; i < brojCvorova; i++) {
        if (cvorovi[i] == rec1) {
            pozicijaReci1 = i;
            break;
        }
    }

    int pozicijaReci2;
    for (int i = 0; i < brojCvorova; i++) {
        if (cvorovi[i] == rec2) {
            pozicijaReci2 = i;
            break;
        }
    }

    auto slicnostSaOstalimRecima = new double[brojCvorova];
    auto poseceniCvorovi = new bool[brojCvorova];
    auto rekonstrukcijaPuta = new int[brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        if (i != pozicijaReci1) {
            slicnostSaOstalimRecima[i] = grane[pozicijaReci1][i];
            poseceniCvorovi[i] = false;
            if (slicnostSaOstalimRecima[i] != INFINITY) rekonstrukcijaPuta[i] = pozicijaReci1;
            else rekonstrukcijaPuta[i] = -1;
        }
    }

    poseceniCvorovi[pozicijaReci1] = true;
    int pozicijaMaksSlicnosti = 0;
    for (int i = 0; i < brojCvorova; i++) {
        if (i != pozicijaReci1) {
            double maksSlicnost = 0;

            for (int j = 0; j < brojCvorova; j++) {
                if (slicnostSaOstalimRecima[j] > maksSlicnost && slicnostSaOstalimRecima[j] != INFINITY && !poseceniCvorovi[j] && j != pozicijaReci1) {
                    maksSlicnost = slicnostSaOstalimRecima[j];
                    pozicijaMaksSlicnosti = j;
                }
            }

            poseceniCvorovi[pozicijaMaksSlicnosti] = true;

            for (int j = 0; j < brojCvorova; j++) {
                if (!poseceniCvorovi[j] && slicnostSaOstalimRecima[pozicijaMaksSlicnosti] * grane[pozicijaMaksSlicnosti][j] != INFINITY && ((slicnostSaOstalimRecima[j] != INFINITY &&
                                                                                                                                             slicnostSaOstalimRecima[pozicijaMaksSlicnosti] * grane[pozicijaMaksSlicnosti][j] > slicnostSaOstalimRecima[j]) || slicnostSaOstalimRecima[j] == INFINITY)) {
                    slicnostSaOstalimRecima[j] = slicnostSaOstalimRecima[pozicijaMaksSlicnosti] * grane[pozicijaMaksSlicnosti][j];
                    rekonstrukcijaPuta[j] = pozicijaMaksSlicnosti;
                }
            }
        }
    }

    Stek<int> s(brojCvorova);
    bool nemaPuta = false;
    while (true) {
        if (pozicijaReci2 == pozicijaReci1) {
            s.push(pozicijaReci1);
            break;
        }
        else {
            if (rekonstrukcijaPuta[pozicijaReci2] == -1) {
                cout << "Nema puta izmedju ove dve reci." << endl;
                nemaPuta = true;
                break;
            }
            else {
                s.push(pozicijaReci2);
                pozicijaReci2 = rekonstrukcijaPuta[pozicijaReci2];
            }
        }
    }

    if (!nemaPuta) {
        int p1, p2;
        while (s.dohvatiTop() != 0) {
            s.pop(p1);
            s.pop(p2);
            cout << cvorovi[p1] << "-(" << grane[p1][p2] << ")->";
            s.push(p2);
        }
        s.pop(p1);
        cout << cvorovi[p1] << endl;
    }

    delete[] slicnostSaOstalimRecima;
    delete[] poseceniCvorovi;
    delete[] rekonstrukcijaPuta;
}

void Graf::nalazenjeJakoPovezanihReci(const string& rec) {
    auto brojPosecivanja = new int[brojCvorova];
    auto poseceniCvorovi = new bool[brojCvorova];

    int pozicijaReci = 0;
    for (int i = 0; i < brojCvorova; i++) {
        if (cvorovi[i] == rec) {
            pozicijaReci = i;
            break;
        }
    }

    for (int i = 0; i < brojCvorova; i++) {
        brojPosecivanja[i] = 0;
        poseceniCvorovi[i] = false;
    }
    Stek<int> stek(brojCvorova);
    int k = pozicijaReci;
    stek.push(k);
    while (stek.dohvatiTop() != -1) {
        stek.pop(k);
        if (!poseceniCvorovi[k]) {
            poseceniCvorovi[k] = true;
            brojPosecivanja[k]++;
            for (int j = 0; j < brojCvorova; j++) {
                if (grane[k][j] != INFINITY && !poseceniCvorovi[j]) {
                    stek.push(j);
                }
            }
        }
    }

    for (int i = 0; i < brojCvorova; i++) poseceniCvorovi[i] = false;
    k = pozicijaReci;
    stek.push(k);
    while (stek.dohvatiTop() != -1) {
        stek.pop(k);
        if (!poseceniCvorovi[k]) {
            poseceniCvorovi[k] = true;
            brojPosecivanja[k]++;
            for (int j = 0; j < brojCvorova; j++) {
                if (grane[j][k] != INFINITY && !poseceniCvorovi[j]) {
                    stek.push(j);
                }
            }
        }
    }

    int m = 0;
    for (int i = 0; i < brojCvorova; i++) {
        if (brojPosecivanja[i] == 2 && i != pozicijaReci) m++;
    }

    if (!m) cout << "Zadata rec nema jako povezane reci." << endl;
    else {
        cout << "Jako povezane reci sa zadatom recju su: " << endl;
        for (int i = 0; i < brojCvorova; i++) {
            if (brojPosecivanja[i] == 2 && i != pozicijaReci) cout << cvorovi[i] << endl;
        }
    }

    delete[] brojPosecivanja;
    delete[] poseceniCvorovi;
}

