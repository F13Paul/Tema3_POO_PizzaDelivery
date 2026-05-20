#ifndef STRATEGIE_REDUCERE_HPP
#define STRATEGIE_REDUCERE_HPP

class StrategieReducere {
public:
    virtual double aplica(double pretInitial) const = 0;
    virtual void afiseaza() const = 0;
    virtual ~StrategieReducere() = default;
};

#endif