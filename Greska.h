#ifndef DOMACI_GRESKA_H
#define DOMACI_GRESKA_H

#include <exception>

class nepostojeciGraf : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Uneli ste nepostojeci graf.\n";
    }
};

class nepostojecaDatoteka : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Datoteka ne postoji.\n";
    }
};

class pogresnaOpcija : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Data opcija ne postoji. Unesite broj od 1 do 9.\n";
    }
};

class nepostojeciCvor : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Ne postoji cvor sa datim imenom.\n";
    }
};

class postojeciCvor : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Vec postoji cvor sa datim imenom.\n";
    }
};

class neregularnaTezina : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Tezina grane mora biti broj izmedju 0 i 1.\n";
    }
};

class neregularanBrojReci : public std::exception {
public:
    [[nodiscard]] const char* what() const noexcept override {
        return "Broj reci mora biti ceo pozitivan broj.\n";
    }
};

#endif //DOMACI_GRESKA_H
