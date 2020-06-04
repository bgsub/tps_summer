#ifndef CONSULTATIONENLIGNE_H
#define CONSULTATIONENLIGNE_H

#include <string>
#include"Consulation.h"

class ConsultationEnligne : public Consultation
{
public:
    ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date);

 
    const double calculerPrix() const override;

    const double RABAIS_EN_LIGNE = 0.5;
    const std::string& getDiagnostique() const;
    double getRabaisConsultationEnligne() const;
    void setDiagnostique(const std::string& diagnostique);
    void setRabaisConsultationEnligne(double rabais);
   // ces attributs doivent être accessibles par les classes dérivées de cette class
private:
    std::string diagnostique_;
    double rabaisConsultationEnligne_;
};

#endif // CONSULTATIONENLIGNE_H


