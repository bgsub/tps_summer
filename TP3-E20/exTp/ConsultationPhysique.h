#ifndef CONSULTATIONPHYSIQUE_H
#define CONSULTATIONPHYSIQUE_H

#include <string>
#include"Consulation.h"

class ConsultationPhysique : public Consultation
{
public:
    ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date);



       // calculerPrix méthode virtuelle pure qui retourne le prix de la consultation. A ne pas implémenter
    const double calculerPrix() const override;
    const std::string& getPrescription() const;
   
    void setPrescription(const std::string& prescription);
   
    // ces attributs doivent être accessibles par les classes dérivées de cette class
private:
    std::string prescription_;
   
};

#endif // CONSULTATIONPHYSIQUE_H
