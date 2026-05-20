#include "ProdusFactory.hpp"

Pizza ProdusFactory::creeazaPizzaDiavola() {
    return Pizza("Pizza Diavola", 25.0f, {"Sos Rosii", "Mozzarella", "Salam"});
}

Pizza ProdusFactory::creeazaPizzaPollo() {
    return Pizza("Pizza Pollo", 28.0f, {"Sos de usturoi", "Pui", "Porumb", "Masline"});
}

Bautura ProdusFactory::creeazaCola() {
    return Bautura("Cola la Sticla", 6.5f, 500);
}

Bautura ProdusFactory::creeazaApa() {
    return Bautura("Apa Minerala Mare", 4.0f, 1000);
}

Desert ProdusFactory::creeazaClatite() {
    return Desert("Clatite cu Finetti", 15.0f, 600);
}