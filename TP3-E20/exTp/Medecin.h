
#ifndef MEDECIN_H
#define MEDECIN_H

#include <memory>
#include <string>
#include "Patient.h"
#include <vector>
#include "Personnel.h"

// Cette classe hérite de la classe Personnel
class Medecin : public Personnel
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
    Medecin(const std::string& nom, const std::string& id, Specialite specialite);

    bool operator+=(Patient* patient);
    bool operator-=(const std::string& numeroAssuranceMaladiePatient);

    //Surchage de la méthode afficher. Elle doit être déclarée virtuelle ici aussi.
    virtual void afficher(std::ostream& stream) const override;

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    void incrementNombreConsultations();

    //Surchage de la méthode getSalaireAnnuel. Elle doit être déclarée virtuelle ici aussi.
    double getSalaireAnnuel() const;

    double getPrixConsultation() const;

    // Des getters et des setters peuvent être ajoutés ou enlevés si nécessaire

    bool getEstActif() const;
    const Specialite getSpecialite() const;
    const size_t getNombrePatientsAssocies() const;

    const std::vector<Patient*>& getPatientsAssocies() const;

    void setEstActif(bool estActif);
    void setSpecialite(Specialite specialite);
    size_t getNombreConsultations() const;

    static constexpr size_t SALAIRE_DE_BASE_MEDECIN = 100000;
protected:
    // Attributs
    size_t nombreConsultations_;
    Specialite specialite_;
    std::vector<Patient*> patientsAssocies_;

    //La méthode trouverIndexPatient est une méthode privée
private:
    int trouverIndexPatient(const std::string& numeroAssuranceMaladie);
 };

#endif // MEDECIN_H