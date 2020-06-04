#ifndef CONSULTATION_H
#define CONSULTATION_H

#include <string>
#include "Medecin.h"
#include "Patient.h"

class Consultation
{
public:
    Consultation() = default;
    Consultation(Medecin& medecin, Patient& patient, const std::string& date);

    Medecin* getMedecin() const;
    Patient* getPatient() const;
    const std::string& getDate() const;
    double getPrix() const;
    void afficher(std::ostream& os) const;

  //calculerPrix méthode virtuelle pure qui retourne le prix de la consultation
    virtual const double calculerPrix() const = 0;            // méthode virtuelle pure

    const double PRIX_DE_BASE = 50;

    // ces attributs doivent être accessibles par les classes dérivées de cette class
protected:
    Medecin* medecin_;
    Patient* patient_;
    std::string date_;
    double prix_;
};

#endif // CONSULTATION_H