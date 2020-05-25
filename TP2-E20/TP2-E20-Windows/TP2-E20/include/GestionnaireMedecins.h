#ifndef GESTIONNAIREMEDECIN_H
#define GESTIONNAIREMEDECIN_H

#include <memory>
#include "Medecin.h"
#include "GestionnairePatients.h"


class GestionnaireMedecins
{
public:
    GestionnaireMedecins();
    //constructeur de copie.
    GestionnaireMedecins(const GestionnaireMedecins& gestMedecins);
    //operateur d'affectaion.
    GestionnaireMedecins& operator=(const GestionnaireMedecins& gestMedecins);

    Medecin* chercherMedecin(const std::string& numeroLicence);
    bool chargerDepuisFichier(const std::string& nomFichiers);
    // operateur += pour ajouter les medecins.
    bool operator+=(Medecin& medecin);
   // operateur -= pour enlever les medecins.
    bool operator-=(const std::string& numeroLicence);

    // surcharge de l operateur<< d affichage.
    friend std::ostream& operator<<(std::ostream& out, const GestionnaireMedecins& gestMedecins);
    size_t getNbMedecins() const;
    // get medecin.
    const std::vector<std::shared_ptr<Medecin>>& getMedecins() const;

private:
    bool lireLigneMedecin(const std::string& ligne);
    int trouverIndexMedecin(const std::string& numeroLicence);
    //remplacer le tableau par un vecteur de shared_ptr de medecin.
    std::vector<std::shared_ptr<Medecin>> medecins_;
};

#endif // GESTIONNAIREMEDECIN_H