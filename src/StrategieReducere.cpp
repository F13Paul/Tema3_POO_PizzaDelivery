#include "Reducere.hpp"

double FaraReducereStrategy::aplica(double pretInitial) const {
    return pretInitial;
}

void FaraReducereStrategy::afiseaza() const {
    std::cout << "Fara reducere\n";
}

ReducereFixaStrategy::ReducereFixaStrategy(int suma)
    : Reducere<int>("Reducere fixa", suma) {}

double ReducereFixaStrategy::aplica(double pretInitial) const {
    if (pretInitial - valoare < 0) {
        return 0;
    }

    return pretInitial - valoare;
}

ReducereProcentualaStrategy::ReducereProcentualaStrategy(double procent)
    : Reducere<double>("Reducere procentuala", procent) {}

double ReducereProcentualaStrategy::aplica(double pretInitial) const {
    double procentCalcul = valoare / 100.0;
    return pretInitial - pretInitial * procentCalcul;
}