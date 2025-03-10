#ifndef GESTIONNAIREPERSONNELS_H
#define GESTIONNAIREPERSONNELS_H

#include <memory>
#include "Medecin.h"
#include "MedecinResident.h"
//! Ne pas inclure la Classe Personnel dans cette classe

class GestionnairePersonnels
{
public:
	enum class TypePersonnel
	{
		first_ = -1,
		Medecin,
		MedecinResident,
		last_
	};

	GestionnairePersonnels() = default;

	Personnel* chercherPersonnel(const std::string& id);
	bool chargerDepuisFichier(const std::string& nomFichiers);

	bool operator+=(Personnel* personnel);
	bool operator-=(const std::string& id);
	friend std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePesonnel);

	const std::vector<std::shared_ptr<Personnel>>& getPersonnels() const;

	// Méthode constante getMedecins retourne un vecteur de Medecin*
	std::vector<Medecin*> getMedecins() const;
	// Méthode constante getMedecinsResidents retourne un vecteur de MedecinResidant*
	std::vector<MedecinResident*> getMedecinsResidents() const;
	size_t getNbPersonnels() const;
	size_t getNbMedecins() const;
	size_t getNbMedecinsResidents() const;

private:
	bool lireLignePersonnel(const std::string& ligne);
	int trouverIndexPersonnel(const std::string& id);

	std::vector<std::shared_ptr<Personnel>> personnels_;
};

#endif // GESTIONNAIREPERSONNELS_H