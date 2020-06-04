#ifndef PATIENT_H
#define PATIENT_H

#include <string>


class Patient
{
public:
    Patient() = default;
    Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie);

    bool operator==(const std::string& numeroAssuranceMaladie) const;
    friend bool operator==(const std::string& nom, const Patient& patient);

    //Méthode virtuelle
    virtual void afficher(std::ostream& stream) const ;

    const std::string& getNom() const;
    const std::string& getNumeroAssuranceMaladie() const;
    const std::string& getDateDeNaissance() const;
   
    void setNom(const std::string& nom);
    void setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie);
    void setDateDeNaissance(const std::string& dateDeNaissance);

    // Ces attributs doivent être accessibles par les classes dérivées de cette classe
protected:
    std::string nom_;
    std::string numeroAssuranceMaladie_;
    std::string dateDeNaissance_;
};

#endif // PATIENT_H