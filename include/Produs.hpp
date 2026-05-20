#ifndef PRODUS_HPP
#define PRODUS_HPP

#include <iostream>
#include <string>

class Produs {
protected:
    const int id;
    std::string nume;
    float pretDeBaza;
    static int contorId; // membru static pentru generarea ID-urilor unice
    static float valideazaPret(float pret);

public:
    // constructori
    Produs(); // default
    Produs(const std::string& nume, float pret); // cu parametri
    Produs(const Produs& altul); // cosntructor de copiere

    // destructor virtual (OBLIGATORIU la moștenire)
    virtual ~Produs();

    // operator atribuire
    Produs& operator=(const Produs& altul);

    // metode polimorfice (virtuale)
    virtual float calculeazaPret() const = 0; // metoda pur virtuala -> clasa devine abstracta
    virtual Produs* clone() const = 0; // pentru copierea polimorfica

    void print(std::ostream& out) const; // fct publica, non-virtuala
    virtual void afisare(std::ostream& out) const; // fct virtuala pentru afisare specifica fiecarui tip de produs

    // Supraincarcare operatori << si >> ca functii prietene
    friend std::ostream& operator<<(std::ostream& out, const Produs& p);
    friend std::istream& operator>>(std::istream& in, Produs& p);
};

#endif