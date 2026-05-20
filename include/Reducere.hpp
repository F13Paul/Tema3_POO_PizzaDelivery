#ifndef REDUCERE_HPP
#define REDUCERE_HPP

#include <iostream>
#include <string>
#include "StrategieReducere.hpp"

template <typename T>
class Reducere : public StrategieReducere {
protected:
    std::string descriere;
    T valoare; // aici T poate deveni int sau double

public:
    Reducere(const std::string& descriere, T valoare)
        : descriere(descriere), valoare(valoare) {}

    void afiseaza() const override {
        std::cout << descriere << " - valoare: " << valoare << "\n";
    }
};

template <typename T>
void afiseazaReducere(const Reducere<T>& reducere) {
    reducere.afiseaza();
}

class FaraReducereStrategy : public StrategieReducere {
public:
    double aplica(double pretInitial) const override;
    void afiseaza() const override;
};

class ReducereFixaStrategy : public Reducere<int> {
public:
    explicit ReducereFixaStrategy(int suma);
    double aplica(double pretInitial) const override;
};

class ReducereProcentualaStrategy : public Reducere<double> {
public:
    explicit ReducereProcentualaStrategy(double procent);
    double aplica(double pretInitial) const override;
};

#endif