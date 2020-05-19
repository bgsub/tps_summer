#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include "Patient.h"
#include <vector>


class Medecin
{
public:
    enum class Specialite
    {
  
        first_ = -1,
        Generaliste,
        Cardiologue,
        Dermatologue,
        Gynecologue,
        Pediatre,
        Ophtalmologue,
        Autre,
        last_
    };
    
    Medecin() = default;
    Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite);

    // TODO : signature des opérateurs à surcharger.
    friend std::ostream& operator<< (std::ostream& out, const Medecin& patient);
    // opérateur+= qui remplace ajouterPatient 
    bool operator+=(Patient& patient);
    // opérateur-= qui remplace supprimerPatient
    bool operator-=(std::string numAssMal);
    // opérateur== qui compare un string avec le numéro licence du médecin premier sens 
    bool operator==(std::string numLicence);

    // opérateur== qui compare un string avec le numéro licence du médecin deuxieme sens 
    friend bool operator==(std::string numLicence, const Medecin medecin);
    // (par exemple, pour "158795" == medecin)

    
    const std::string& getNom() const;
    const std::string& getNumeroLicence() const;
    bool getEstActif() const;
    const Specialite getSpecialite() const;
    const size_t getCapacitePatientAssocies() const;
    const size_t getNombrePatientsAssocies() const;
    std::vector<std::shared_ptr<Patient>> getPatientsAssocies();

    void setNom(const std::string& nom);
    void setNumeroLicence(const std::string& numeroLicence);
    void setEstActif(bool estActif);
    void setSpecialite(Specialite specialite);

private:
    // Attributs
    std::string nom_;
    std::string numeroLicence_;
    Specialite specialite_;
    bool estActif_ = true;

    // TODO: remplacer le tableau par un vecetur de Patient*
    std::vector<std::shared_ptr<Patient>> patientsAssocies_;                               // pas sur
    size_t nbPatientsAssocies_;
    size_t capacitePatientsAssocies_;

};

#endif // MEDECIN_H