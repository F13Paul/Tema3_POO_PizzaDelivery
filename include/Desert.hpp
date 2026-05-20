#ifndef DESERT_HPP
#define DESERT_HPP

#include "Produs.hpp"

class Desert : public Produs {
private:
    int kcal;
    static int valideazaKcal(int kcal);

public:
    // constructori
    Desert();
    Desert(const std::string& nume, float pret, int kcal);
    Desert(const Desert& altul); //

    // destructor
    ~Desert() override;

    // operator de atribuire
    Desert& operator=(const Desert& altul);

    // suprascrierea metodelor virtuale
    float calculeazaPret() const override;
    Produs* clone() const override;
    
    void afisare(std::ostream& out) const override;

    friend std::istream& operator>>(std::istream& in, Desert& d);
};

#endif