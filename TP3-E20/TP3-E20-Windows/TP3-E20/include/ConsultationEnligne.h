#ifndef CONSULTATIONENLIGNE_H
#define CONSULTATIONENLIGNE_H

#include <string>
#include "Consultation.h"

class ConsultationEnligne : public Consultation
{
public:
    ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date);



    //   void afficher(std::ostream& os) const;

       // TODO calculerPrix méthode virtuelle pure qui retourne le prix de la consultation. A ne pas implémenter
    const double calculerPrix() const override;

    const double RABAIS_EN_LIGNE = 0.5;
    const std::string& getDiagnostique() const;
    double getRabaisConsultationEnligne() const;
    void setDiagnostique(const std::string& diagnostique);
    void setRabaisConsultationEnligne(double rabais);
    //TODO : ces attributs doivent être accessibles par les classes dérivées de cette class
private:
    std::string diagnostique_;
    double rabaisConsultationEnligne_;
};

#endif // CONSULTATIONENLIGNE_H


//TODO : Cette classe hérite de la classe Consultaion.
//TODO : Des attributs privées : diagnostique__ (std::string),rabaisConsultationEnLigne__ (double)
//TODO: Le constructeur par paramètres pour initialiser les attributs de la classe. 
//Ce constructeur utilise le constructeur de la classe Consultation.
//TODO : surchager la méthode calculerPrix  const double calculerPrix() const override;
//TODO: des getters e