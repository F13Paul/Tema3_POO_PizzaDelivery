#include "Produs.hpp"
#include "Exceptii.hpp"

// initializare contor static
int Produs::contorId = 1;

// constructor default
Produs::Produs() : id(contorId++), nume("Produs Necunoscut"), pretDeBaza(0.0f) {}

// constructor cu parametri
Produs::Produs(const std::string& nume, float pret)
    : id(contorId++), nume(nume), pretDeBaza(valideazaPret(pret)) {}

// constructor de copiere
Produs::Produs(const Produs& altul) : id(contorId++), nume(altul.nume), pretDeBaza(altul.pretDeBaza) {}

// destructor
Produs::~Produs() {}

// operator=
Produs& Produs::operator=(const Produs& altul) {
    if (this != &altul) {
        this->nume = altul.nume;
        this->pretDeBaza = altul.pretDeBaza;
    }
    return *this;
}

float Produs::valideazaPret(float pret) {
    if (pret < 0) {
        throw PretInvalidException("Pretul de baza nu poate fi negativ.");
    }
    return pret;
}

void Produs::print(std::ostream& out) const {
    afisare(out);
}

void Produs::afisare(std::ostream& out) const {
    out << "ID: " << id << " | Nume: " << nume << " | Pret Baza: " << pretDeBaza << " RON";
}

std::ostream& operator<<(std::ostream& out, const Produs& p) {
    p.print(out);
    return out;
}

std::istream& operator>>(std::istream& in, Produs& p) {
    std::cout << "Introduceti nume produs: ";
    in >> p.nume;

    float pret;
    std::cout << "Introduceti pret de baza: ";
    in >> pret;

    p.pretDeBaza = Produs::valideazaPret(pret);

    return in;
}