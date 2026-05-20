#ifndef PRODUS_FACTORY_HPP
#define PRODUS_FACTORY_HPP

#include "Pizza.hpp"
#include "Bautura.hpp"
#include "Desert.hpp"

class ProdusFactory {
public:
    static Pizza creeazaPizzaDiavola();
    static Pizza creeazaPizzaPollo();
    static Bautura creeazaCola();
    static Bautura creeazaApa();
    static Desert creeazaClatite();
};

#endif