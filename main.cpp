#include <fstream>
#include "Graf.h"
#include "Greska.h"

Graf* citanjeGrafa() {
    int brojGrafa;
    cout << "Izaberite graf (1, 2): ";
    cin >> brojGrafa;
    cout << endl;
    if (brojGrafa != 1 && brojGrafa != 2) throw nepostojeciGraf();

    ifstream fajl;
    if (brojGrafa == 1) fajl.open("graf1.txt");
    else fajl.open("graf2.txt");

    if (!fajl.is_open()) throw nepostojecaDatoteka();

    int brojCvorova, brojGrana;
    fajl >> brojCvorova >> brojGrana;

    auto* cvorovi = new string[brojCvorova];
    for (int i = 0; i < brojCvorova; i++) fajl >> cvorovi[i];

    auto** grane = new double* [brojCvorova];
    for (int i = 0; i < brojCvorova; i++) {
        grane[i] = new double[brojCvorova];
        for (int j = 0; j < brojCvorova; j++) {
            if (i == j) grane[i][j] = 0;
            else grane[i][j] = INFINITY;
        }
    }

    int m, n;
    string s1, s2;
    double d;
    for (int i = 0; i < brojGrana; i++) {
        fajl >> s1 >> s2 >> d;

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

        grane[m][n] = d;
    }

    fajl.close();

    return new Graf(brojCvorova, cvorovi, grane);
}

bool proveraCvor(Graf* graf, const string& ime) {
    bool postoji = false;
    for (int i = 0; i < graf->dohvatiBrojCvorova(); i++) {
        if (ime == graf->dohvatiCvorove()[i]) postoji = true;
    }
    return postoji;
}

int main() {
    while (true) {
        try {
            Graf* graf = citanjeGrafa();
            while (true) {
                try {
                    cout << "Izaberite opciju:" << endl;
                    cout << "1. Dodavanje cvora" << endl;
                    cout << "2. Uklanjanje cvora" << endl;
                    cout << "3. Dodavanje grane" << endl;
                    cout << "4. Uklanjanje grane" << endl;
                    cout << "5. Nalazenje najslicnijih reci" << endl;
                    cout << "6. Nalazenje najkraceg puta izmedju dve reci" << endl;
                    cout << "7. Nalazenje jako povezanih reci" << endl;
                    cout << "8. Ispis grafa" << endl;
                    cout << "9. Kraj programa" << endl;

                    int opcija;
                    cin >> opcija;
                    cout << endl;
                    if (opcija < 1 || opcija > 9) throw pogresnaOpcija();

                    string imeCvora1, imeCvora2;
                    double tezinaGrane;
                    int brojNajslicnijihReci;
                    switch (opcija) {
                        case 1:
                            cout << "Unesite ime cvora: ";
                            cin >> imeCvora1;
                            cout << endl;
                            if (proveraCvor(graf, imeCvora1)) throw postojeciCvor();
                            graf->dodavanjeCvora(imeCvora1);
                            continue;

                        case 2:
                            cout << "Unesite ime cvora: ";
                            cin >> imeCvora1;
                            cout << endl;
                            if (!proveraCvor(graf, imeCvora1)) throw nepostojeciCvor();
                            graf->uklanjanjeCvora(imeCvora1);
                            continue;

                        case 3:
                            cout << "Unesite ime dva cvora i tezinu grane izmedju njih: ";
                            cin >> imeCvora1 >> imeCvora2 >> tezinaGrane;
                            cout << endl;
                            if (!proveraCvor(graf, imeCvora1) || !proveraCvor(graf, imeCvora2)) throw nepostojeciCvor();
                            if (tezinaGrane > 1 || tezinaGrane <= 0) throw neregularnaTezina();
                            graf->dodavanjeGrane(imeCvora1, imeCvora2, tezinaGrane);
                            continue;

                        case 4:
                            cout << "Unesite ime dva cvora: ";
                            cin >> imeCvora1 >> imeCvora2;
                            cout << endl;
                            if (!proveraCvor(graf, imeCvora1) || !proveraCvor(graf, imeCvora2)) throw nepostojeciCvor();
                            graf->uklanjanjeGrane(imeCvora1, imeCvora2);
                            continue;

                        case 5:
                            cout << "Unesite rec i broj najslicnijih reci: ";
                            cin >> imeCvora1 >> brojNajslicnijihReci;
                            cout << endl;
                            if (!proveraCvor(graf, imeCvora1)) throw nepostojeciCvor();
                            if (brojNajslicnijihReci <= 0) throw neregularanBrojReci();
                            graf->nalazenjeNajslicnijihReci(imeCvora1, brojNajslicnijihReci);
                            cout << endl;
                            continue;

                        case 6:
                            cout << "Unesite ime dva cvora: ";
                            cin >> imeCvora1 >> imeCvora2;
                            cout << endl;
                            if (!proveraCvor(graf, imeCvora1) || !proveraCvor(graf, imeCvora2)) throw nepostojeciCvor();
                            graf->najkraciPutIzmedjuDveReci(imeCvora1, imeCvora2);
                            cout << endl;
                            continue;

                        case 7:
                            cout << "Unesite ime cvora: ";
                            cin >> imeCvora1;
                            cout << endl;
                            if (!proveraCvor(graf, imeCvora1)) throw nepostojeciCvor();
                            graf->nalazenjeJakoPovezanihReci(imeCvora1);
                            cout << endl;
                            continue;

                        case 8:
                            cout << *graf << endl;
                            continue;

                        case 9:
                            delete graf;
                            break;

                        default:
                            continue;
                    }
                    break;
                }
                catch (exception& e) {
                    cout << e.what() << endl;
                }

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            }

            break;

        }
        catch (exception& e) {
            cout << e.what() << endl;
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }




    return 0;
}
