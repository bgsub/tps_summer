#ifndef GESTIONNAIREPATIENTS_H
#define GESTIONNAIREPATIENTS_H

#include <string>
#include "Patient.h"
#include <memory>
#include <vector>

class GestionnairePatients
{
public:
    GestionnairePatients();
    GestionnairePatients(const GestionnairePatients& gestPatients);                       // contructeur par copie;

    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);
    // surcharge de l opérateur<< 
    friend std::ostream& operator<<(std::ostream& stream, const  GestionnairePatients& gestPatients);
    // surcharge de l operateur  +-
    bool operator+=(const Patient& patient);
    size_t getNbPatients() const;
    const std::vector<std::shared_ptr<Patient>>& getPatients() const;

    static constexpr size_t NB_PATIENT_MAX = 16;

private:
    bool lireLignePatient(const std::string& ligne);
    std:: vector <std::shared_ptr<Patient>>patients_;

};

#endif // GESTIONNAIREPATIENTS_H