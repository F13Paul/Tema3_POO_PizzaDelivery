#include "Desert.hpp"
#include "Exceptii.hpp"

// constructor default
Desert::Desert() : Produs("Desert Generic", 15.0f), kcal(250) {}

// constructor cu parametri
Desert::Desert(const std::string& nume, float pret, int kcal)
    : Produs(nume, pret), kcal(valideazaKcal(kcal)) {}

// constructor de copiere
Desert::Desert(const Desert& altul) : Produs(altul), kcal(altul.kcal) {}

// destructor
Desert::~Desert() {}

// operator=
Desert& Desert::operator=(const Desert& altul) {
    if (this != &altul) {
        Produs::operator=(altul);
        this->kcal = altul.kcal;
    }
    return *this;
}

// setterul a devenit functie statica cu aruncare de exceptie custom
int Desert::valideazaKcal(int kcal) {
    if (kcal < 0) {
        throw CaloriiInvalideException("Eroare: Numarul de calorii nu poate fi negativ!");
    }

    return kcal;
}

Produs* Desert::clone() const {
    return new Desert(*this);
}

// polimorfism: Daca are peste 500 kcal, aplicam "taxa pe zahar" de 3 RON
float Desert::calculeazaPret() const {
    float pretFinal = pretDeBaza;
    if (kcal > 500) {
        pretFinal += 3.0f;
    }
    return pretFinal;
}

// suprascriem afisarea
void Desert::afisare(std::ostream& out) const {
    Produs::afisare(out);
    out << " | Calorii: " << kcal << " kcal | Pret final: " << calculeazaPret() << " RON";
}

// citirea
std::istream& operator>>(std::istream& in, Desert& d) {
    in >> static_cast<Produs&>(d);
    
    int caloriiIntroduse;
    std::cout << "Introduceti numarul de calorii: ";
    in >> caloriiIntroduse;
    
    // folosim setter-ul pentru a declansa exceptia daca e cazul
    d.kcal = Desert::valideazaKcal(caloriiIntroduse);
    
    return in;
}