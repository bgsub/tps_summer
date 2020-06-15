#ifndef GESTIONNAIREPERSONNELS_H
#define GESTIONNAIREPERSONNELS_H

#include <memory>
#include "Medecin.h"
#include "MedecinResident.h"
#include<unordered_map>
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

	Personnel* chercherPersonnel(const std::string& id) const;
	bool chargerDepuisFichier(const std::string& nomFichiers);

	// TODO: Remplacer l'opérateur par la méthode générique ajouterPatient
	// La méthode prend une référence vers l'objet à ajouter
	template <typename T>
	bool ajouterPersonnel(const T& personnel);

	// TODO: Remplacer l'opérateur par la méthode supprimerPesonnel
	// La méthode prend un string qui est l'id de personnel à supprimer
	bool supprimerPatient(const std::string& id);

	friend std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePesonnel);

	//TODO : à adapter au changement du type de l'attribut personnels_
	const std::unordered_map<std::string, std::shared_ptr<Personnel>>& getPersonnels() const;

	// TODO : Ajouter la méthode générique getPersonnelsAvecType()
	// Elle retourne unordered_map de string et un pointeur vers le personnel
	template <typename T>
	std::unordered_map<std::string, T*> getPersonnelsAvecType() const;

	// TODO : Ajouter la méthode getPersonnelsTriesSuivantSalaireAnnuel
	// Elle retourne un vecteur de pair de string est shared_ptr<Pesonnel>

	std::vector <std::pair<std::string, std::shared_ptr<Personnel>>> getPersonnelsTriesSuivantSalaireAnnuel() const;

	size_t getNbPersonnels() const;
	size_t getNbMedecins() const;
	size_t getNbMedecinsResidents() const;

private:
	bool lireLignePersonnel(const std::string& ligne);

	// TODO : Changer le type de l'attribut pesonnel.
	// Il doit être unordered_map : std::string, std::shared_ptr<Personnel>
	std::unordered_map<std::string, std::shared_ptr<Personnel>>personnels_;
};

#endif // GESTIONNAIREPERSONNELS_H