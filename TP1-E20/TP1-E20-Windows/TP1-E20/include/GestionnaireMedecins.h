#ifndef GESTIONNAIREMEDECIN_H
#define GESTIONNAIREMEDECIN_H

#include <memory>
#include "Medecin.h"
#include "GestionnairePatients.h"


class GestionnaireMedecins
{
public:

    GestionnaireMedecins();

    void ajouterMedecin(std::shared_ptr<Medecin> medecin);
    std::shared_ptr<Medecin> chercherMedecin(const std::string& numeroLicence);
	bool chargerDepuisFichier(const std::string& nomFichiers);
    bool supprimerMedecin(const std::string& numeroLicence);

    void afficher(std::ostream& stream);

    size_t getNbMedecins();
    size_t getCapaciteMedecins();

private:
    bool lireLigneMedecin(const std::string& ligne);
    int trouverIndexMedecin(const std::string& numeroLicence);

    size_t nbMedecins_;
    size_t capaciteMedecins_;
    std::unique_ptr<std::shared_ptr<Medecin>[]> medecins_;
};

#endif // GESTIONNAIREMEDECIN_H