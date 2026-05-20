#ifndef BAUTURA_HPP
#define BAUTURA_HPP

#include "Produs.hpp"

class Bautura : public Produs {
private:
    int volumMl;
    static int valideazaVolum(int volum);

public:
    // constructori
    Bautura();
    Bautura(const std::string& nume, float pret, int volumMl);
    Bautura(const Bautura& alta); // Constructor de copiere

    // destructor
    ~Bautura() override;

    // operator de atribuire
    Bautura& operator=(const Bautura& alta);

    // suprascrierea metodelor virtuale
    float calculeazaPret() const override;
    Produs* clone() const override;

    void afisare(std::ostream& out) const override;

    // supraincarcare operator de citire
    friend std::istream& operator>>(std::istream& in, Bautura& b);
};

#endif