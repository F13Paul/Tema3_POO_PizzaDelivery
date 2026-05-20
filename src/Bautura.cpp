#include "Bautura.hpp"
#include "Exceptii.hpp"

// constructor default
Bautura::Bautura() : Produs("Bautura Generica", 5.0f), volumMl(330) {}

// constructor cu parametri
Bautura::Bautura(const std::string& nume, float pret, int volumMl)
    : Produs(nume, pret), volumMl(valideazaVolum(volumMl)) {}

// constructor de copiere
Bautura::Bautura(const Bautura& alta) : Produs(alta), volumMl(alta.volumMl) {}

// destructor
Bautura::~Bautura() {}

// operator=
Bautura& Bautura::operator=(const Bautura& alta) {
    if (this != &alta) {
        Produs::operator=(alta); // copiem partea de baza
        this->volumMl = alta.volumMl;
    }
    return *this;
}

// setter cu validare minima
int Bautura::valideazaVolum(int volum) {
    if (volum <= 0) {
        throw VolumInvalidException("Volumul bauturii trebuie sa fie pozitiv.");
    }

    return volum;
}

Produs* Bautura::clone() const {
    return new Bautura(*this);
}

// polimorfism: pretul de baza + 2 RON taxa pentru sticle mari (> 500ml)
float Bautura::calculeazaPret() const {
    float pretFinal = pretDeBaza;
    if (volumMl >= 500) {
        pretFinal += 2.0f;
    }
    return pretFinal;
}

// suprascriem afisarea
void Bautura::afisare(std::ostream& out) const {
    Produs::afisare(out); // partea din clasa de baza
    out << " | Volum: " << volumMl << " ml | Pret final: " << calculeazaPret() << " RON";
}

// citirea
std::istream& operator>>(std::istream& in, Bautura& b) {
    in >> static_cast<Produs&>(b);

    int volum;
    std::cout << "Introduceti volumul (ml): ";
    in >> volum;

    b.volumMl = Bautura::valideazaVolum(volum);

    return in;
}