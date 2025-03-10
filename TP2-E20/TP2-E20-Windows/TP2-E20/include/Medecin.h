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

    // opérateur+= qui remplace ajouterPatient 
    bool operator+=( Patient& patient);
    // opérateur-= qui remplace supprimerPatient
    bool operator-=(std::string numAssMal);
    //operateur<< d affichage.
    friend std::ostream& operator<< (std::ostream& out, const Medecin& patient);
    // opérateur== qui compare un string avec le numéro licence du médecin premier sens 
    bool operator==(std::string numLicence);

    // opérateur== qui compare un string avec le numéro licence du médecin deuxieme sens 
    friend bool operator==(const std::string& numLicence, const Medecin medecin);
    // (par exemple, pour "158795" == medecin)
    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    
    const std::string& getNom() const;
    const std::string& getNumeroLicence() const;
    bool getEstActif() const;
    const Specialite getSpecialite() const;
    const size_t getNombrePatientsAssocies() const;
    std::vector<Patient*> getPatientsAssocies() const;

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

    std::vector<Patient*> patientsAssocies_;                               
   
   

};

#endif // MEDECIN_H