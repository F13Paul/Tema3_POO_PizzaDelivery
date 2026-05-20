#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "Comanda.hpp"
#include "Pizza.hpp"
#include "Bautura.hpp"
#include "Desert.hpp"
#include "Exceptii.hpp"
#include "Reducere.hpp"
#include "ProdusFactory.hpp"
#include "StrategieReducere.hpp"

void curataBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int citesteOptiune() {
    int optiune;
    std::cout << "Alege optiunea: ";
    std::cin >> optiune;

    if (std::cin.fail()) {
        curataBuffer();
        return -1;
    }

    curataBuffer();
    return optiune;
}

float citestePret() {
    float pret;
    std::cout << "Pret de baza: ";
    std::cin >> pret;

    if (std::cin.fail()) {
        curataBuffer();
        throw PretInvalidException("Pretul introdus nu este valid.");
    }

    curataBuffer();
    return pret;
}

int citesteIntregPozitiv(const std::string& mesaj) {
    int valoare;
    std::cout << mesaj;
    std::cin >> valoare;

    if (std::cin.fail()) {
        curataBuffer();
        throw PizzaDeliveryException("Valoarea introdusa nu este un numar valid.");
    }

    curataBuffer();
    return valoare;
}

Pizza creeazaPizzaCustom() {
    std::string nume;
    std::cout << "Nume pizza: ";
    std::getline(std::cin, nume);

    float pret = citestePret();

    int nrIngrediente = citesteIntregPozitiv("Cate ingrediente vrei? ");

    if (nrIngrediente < 0) {
        throw IngredientInvalidException("Numarul de ingrediente nu poate fi negativ.");
    }

    std::vector<std::string> ingrediente;
    for (int i = 0; i < nrIngrediente; ++i) {
        std::string ingredient;
        std::cout << "Ingredient " << i + 1 << ": ";
        std::getline(std::cin, ingredient);
        ingrediente.push_back(ingredient);
    }

    return Pizza(nume, pret, ingrediente);
}

Bautura creeazaBauturaCustom() {
    std::string nume;
    std::cout << "Nume bautura: ";
    std::getline(std::cin, nume);

    float pret = citestePret();
    int volum = citesteIntregPozitiv("Volum ml: ");

    return Bautura(nume, pret, volum);
}

Desert creeazaDesertCustom() {
    std::string nume;
    std::cout << "Nume desert: ";
    std::getline(std::cin, nume);

    float pret = citestePret();
    int kcal = citesteIntregPozitiv("Numar calorii: ");

    return Desert(nume, pret, kcal);
}

void afiseazaMeniuPrincipal() {
    std::cout << "\n=== Sistem PizzaDelivery ===\n";
    std::cout << "1. Adauga pizza custom\n";
    std::cout << "2. Adauga Pizza Diavola\n";
    std::cout << "3. Adauga Pizza Pollo\n";
    std::cout << "4. Adauga Cola\n";
    std::cout << "5. Adauga Apa minerala\n";
    std::cout << "6. Adauga Clatite cu Finetti\n";
    std::cout << "7. Adauga bautura custom\n";
    std::cout << "8. Adauga desert custom\n";
    std::cout << "9. Afiseaza comanda\n";
    std::cout << "10. Alege reducere pentru intreaga comanda\n";
    std::cout << "0. Finalizeaza comanda\n";
}

std::unique_ptr<StrategieReducere> alegeReducere() {
    std::cout << "\n=== Reduceri disponibile ===\n";
    std::cout << "1. Fara reducere\n";
    std::cout << "2. Reducere fixa\n";
    std::cout << "3. Reducere procentuala\n";

    int optiune = citesteOptiune();

    switch (optiune) {
        case 1: {
            auto reducere = std::make_unique<FaraReducereStrategy>();
            reducere->afiseaza();

            return reducere;
        }

        case 2: {
            int suma;
            std::cout << "Introdu suma reducerii: ";
            std::cin >> suma;

            if (std::cin.fail()) {
                curataBuffer();
                throw PizzaDeliveryException("Suma introdusa nu este valida.");
            }

            curataBuffer();

            if (suma < 0) {
                throw PizzaDeliveryException("Reducerea fixa nu poate fi negativa.");
            }

            auto reducere = std::make_unique<ReducereFixaStrategy>(suma);
            afiseazaReducere<int>(*reducere);

            return reducere;
        }

        case 3: {
            double procent;
            std::cout << "Introdu procentul reducerii. Exemplu: 10 pentru 10%: ";
            std::cin >> procent;

            if (std::cin.fail()) {
                curataBuffer();
                throw PizzaDeliveryException("Procentul introdus nu este valid.");
            }

            curataBuffer();

            if (procent < 0 || procent > 100) {
                throw PizzaDeliveryException("Procentul reducerii trebuie sa fie intre 0 si 100.");
            }

            auto reducere = std::make_unique<ReducereProcentualaStrategy>(procent);
            afiseazaReducere<double>(*reducere);

            return reducere;
        }

        default:
            std::cout << "Optiune invalida. Se pastreaza reducerea anterioara.\n";
            return nullptr;
    }
}

void afiseazaTotalFinal(const Comanda& comanda, const StrategieReducere& strategieReducere) {
    float totalInitial = comanda.calculeazaTotal();
    double totalFinal = strategieReducere.aplica(totalInitial);

    std::cout << "\n=== Total comanda ===\n";
    std::cout << "Total initial: " << totalInitial << " lei\n";
    std::cout << "Total dupa reducere: " << totalFinal << " lei\n";
}

int main() {
    Comanda comandaCurenta;
    std::unique_ptr<StrategieReducere> strategieReducere = std::make_unique<FaraReducereStrategy>();

    bool ruleaza = true;

    while (ruleaza) {
        try {
            afiseazaMeniuPrincipal();
            int optiune = citesteOptiune();

            switch (optiune) {
                case 1: {
                    Pizza pizzaCustom = creeazaPizzaCustom();
                    comandaCurenta.adaugaProdus(pizzaCustom);
                    std::cout << "Pizza custom a fost adaugata in comanda.\n";
                    break;
                }

                case 2: {
                    Pizza pizza = ProdusFactory::creeazaPizzaDiavola();
                    comandaCurenta.adaugaProdus(pizza);
                    std::cout << "Pizza Diavola a fost adaugata in comanda.\n";
                    break;
                }

                case 3: {
                    Pizza pizza = ProdusFactory::creeazaPizzaPollo();
                    comandaCurenta.adaugaProdus(pizza);
                    std::cout << "Pizza Pollo a fost adaugata in comanda.\n";
                    break;
                }

                case 4: {
                    Bautura cola = ProdusFactory::creeazaCola();
                    comandaCurenta.adaugaProdus(cola);
                    std::cout << "Cola a fost adaugata in comanda.\n";
                    break;
                }

                case 5: {
                    Bautura apa = ProdusFactory::creeazaApa();
                    comandaCurenta.adaugaProdus(apa);
                    std::cout << "Apa minerala a fost adaugata in comanda.\n";
                    break;
                }

                case 6: {
                    Desert clatite = ProdusFactory::creeazaClatite();
                    comandaCurenta.adaugaProdus(clatite);
                    std::cout << "Clatitele au fost adaugate in comanda.\n";
                    break;
                }

                case 7: {
                    Bautura bauturaCustom = creeazaBauturaCustom();
                    comandaCurenta.adaugaProdus(bauturaCustom);
                    std::cout << "Bautura custom a fost adaugata in comanda.\n";
                    break;
                }

                case 8: {
                    Desert desertCustom = creeazaDesertCustom();
                    comandaCurenta.adaugaProdus(desertCustom);
                    std::cout << "Desertul custom a fost adaugat in comanda.\n";
                    break;
                }

                case 9: {
                    std::cout << "\n" << comandaCurenta;
                    afiseazaTotalFinal(comandaCurenta, *strategieReducere);
                    break;
                }

                case 10: {
                    std::unique_ptr<StrategieReducere> strategieNoua = alegeReducere();

                    if (strategieNoua != nullptr) {
                        strategieReducere = std::move(strategieNoua);
                        std::cout << "Reducerea a fost actualizata.\n";
                    }

                    break;
                }

                case 0: {
                    std::cout << "\n=== Comanda finala ===\n";
                    std::cout << comandaCurenta;
                    afiseazaTotalFinal(comandaCurenta, *strategieReducere);
                    std::cout << "Multumim pentru comanda!\n";
                    ruleaza = false;
                    break;
                }

                default:
                    std::cout << "Optiune invalida. Incearca din nou.\n";
                    break;
            }

        } catch (const PizzaDeliveryException& e) {
            std::cerr << "Eroare PizzaDelivery: " << e.what() << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Eroare standard: " << e.what() << "\n";
        }
    }

    return 0;
}