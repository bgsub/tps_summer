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
    GestionnairePatients& operator=(const GestionnairePatients& gestPatients);             // avec ou sans ca le test 10 marche.... (operateur d affectation)
   // bool ajouterPatient(const Patient& patient);
    Patient* chercherPatient(const std::string& numeroAssuranceMaladie);
    bool chargerDepuisFichier(const std::string& nomFichier);
    //void afficher(std::ostream& stream) const;

    // TODO fait : signature des opérateurs à surcharger.
    // opérateur<< qui remplace afficher
    friend std::ostream& operator<<(std::ostream& stream,  GestionnairePatients& gestPatients);
    // opérateur+= qui remplace ajouterPatient
    bool operator+=(Patient patient);


    size_t getNbPatients() const;
    // TODO fait : signature de getPatients()  retourne une reference constante vers le vecteur patients_
  const std::vector<std::shared_ptr<Patient>>& getPatients() const;

    static constexpr size_t NB_PATIENT_MAX = 16;

private:
    bool lireLignePatient(const std::string& ligne);

    //TODO fait : remplacer le tableau par un vecteur de shared_ptr de Patient
    std:: vector <std::shared_ptr<Patient>>patients_;
    size_t nbPatients_;
};

#endif // GESTIONNAIREPATIENTS_H