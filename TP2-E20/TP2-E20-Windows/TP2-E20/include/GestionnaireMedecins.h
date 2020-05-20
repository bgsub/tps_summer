#ifndef GESTIONNAIREMEDECIN_H
#define GESTIONNAIREMEDECIN_H

#include <memory>
#include "Medecin.h"
#include "GestionnairePatients.h"


class GestionnaireMedecins
{
public:
    GestionnaireMedecins();
    //TODO : signature de constructeur de copie
    GestionnaireMedecins(const GestionnaireMedecins& gestMedecins);
    //TODO : signature d'operateur d'affectaion
    GestionnaireMedecins& operator=(const GestionnaireMedecins& gestMedecins);

    Medecin* chercherMedecin(const std::string& numeroLicence);
    bool chargerDepuisFichier(const std::string& nomFichiers);

    bool operator+=(Medecin& medecin);
    bool operator-=(const std::string& numeroLicence);


    friend std::ostream& operator<<(std::ostream& out, const GestionnaireMedecins& gestMedecins);
    
 


    size_t getNbMedecins() const;
    size_t getCapaciteMedecins() const;
    // TODO : signature de getMedecins() retourne une reference constante vers le vecteur medecins_
    const std::vector<std::shared_ptr<Medecin>>& getMedecins() const;

private:
    bool lireLigneMedecin(const std::string& ligne);
    int trouverIndexMedecin(const std::string& numeroLicence);

    // TODO: remplacer le tableau par un vecteur de shared_ptr de medecin
    size_t nbMedecins_;
    size_t capaciteMedecins_;
    std::vector<std::shared_ptr<Medecin>> medecins_;
};

#endif // GESTIONNAIREMEDECIN_H