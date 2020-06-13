/* ////////////////////////////////////////////////////////////////////////////
/	TP4 : fichier GestionnairePersonnels.cpp                                  /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 14 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe GestionnairePersonnels        /
*//////////////////////////////////////////////////////////////////////////////

#include "GestionnairePersonnels.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"
#include "Foncteurs.h"
#include <algorithm>

constexpr int PERSONNEL_INEXSISTANT = -1;

// Méthode qui permet de chercherPersonnel
//! param: un string id du personnel
//! return un Pointeur de personnel
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id) const
{
	auto it = personnels_.find(id);
	if (it != personnels_.end())
	{
		return it->second.get();
	}
	return nullptr;
}

//! Méthode  qui permet de charger les informations des personnels
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succes
bool GestionnairePersonnels::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		personnels_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLignePersonnel(ligne))
			{
				return false;
			}
		}
		return true;
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";

	return false;
}

//  Méthode générique ajouterPatient
//! param une reference constante de personnel personnel
//! return un booleen
template <typename T>
bool GestionnairePersonnels::ajouterPersonnel(const T& personnel)
{
	//dynamic_cast<Personnel*>((std::make_shared<T>(personnel).get())) && !chercherPersonnel(personnel.getId()) ? 	personnels_[personnel.getId()] = std::make_shared<T>(personnel) : return false;
	if (dynamic_cast<Personnel*>((std::make_shared<T>(personnel).get())) && !chercherPersonnel(personnel.getId())) { 
		personnels_[personnel.getId()] = std::make_shared<T>(personnel);
		return true;
	}
	return false;
}

// Méthode supprimerPesonnel
//!param: un string l'id de personnel à supprimer
//!Return un booleen
bool GestionnairePersonnels::supprimerPatient(const std::string& id)
{
	if (chercherPersonnel(id))
	{
		personnels_[id]->setEstActif(false);
		return true;
	}
	return false;
}

//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePersonnels)
{
	// Code fourni
	if constexpr (false)
	{
		for (auto it = gestionnairePersonnels.personnels_.cbegin(); it != gestionnairePersonnels.personnels_.cend(); ++it)
		{
			it->second->afficher(os);
			os << '\n';
		}
		return os;
	}
	else
	{
		//TODO fait : Utiliser une boucle for ranged-based
		for (const auto& it : gestionnairePersonnels.personnels_)
		{
			it.second->afficher(os);
			os << '\n';
		}
		return os;
	}
}

//Methode getPersonnel
//!Return un unordered_map  de shared_ptr de personnel dont string est la clee 
std::unordered_map<std::string, std::shared_ptr<Personnel>> GestionnairePersonnels::getPersonnels() const
{
	return personnels_;
}

//  méthode générique getPersonnelsAvecType() qui retourne la liste de personnels selon le type
//! return un unordered_map de string et un pointeur vers le personnel
template <typename T>
std::unordered_map<std::string, T*> GestionnairePersonnels::getPersonnelsAvecType() const
{
	std::unordered_map<std::string, T*> personnelsAvecTypes;
	for (const auto& it : personnels_)
	{
		if (dynamic_cast<T*>(it.second.get()))
		{
			personnelsAvecTypes.insert(std::make_pair(it.first, dynamic_cast<T*>(it.second.get())));  // est ce que je dois utiliser un const_cast
		}
	}
	return personnelsAvecTypes;
}
// méthode qui trie le personnel de l’hôpital suivant le salaire annuel avec sort
//!Return un vecteur de pair de string est shared_ptr<Pesonnel>
std::vector < std::pair < std::string, std::shared_ptr<Personnel>>> GestionnairePersonnels::getPersonnelsTriesSuivantSalaireAnnuel() const
{
	std::vector < std::pair < std::string, std::shared_ptr<Personnel>>> vectTemp (personnels_.begin(), personnels_.end() );
	std::sort(vectTemp.begin(), vectTemp.end(), ComparateurSecondElementPaire<std::string, std::shared_ptr<Personnel>>());
	return vectTemp;
}


//! Méthode qui retourne le nombre des personnels
//! \return le nombre de tous le pesonnels
size_t GestionnairePersonnels::getNbPersonnels() const
{
	return personnels_.size();
}

//  Méthode qui retourne le nombre de Medecins
//! return le nombre de tous le pesonnel de type 
size_t GestionnairePersonnels::getNbMedecins() const
{
	return getPersonnelsAvecType<Medecin>().size();
}

//  Méthode qui retourne le nombre de Medecins Residents
//! return le nombre de tous les medecins Residents
size_t GestionnairePersonnels::getNbMedecinsResidents() const
{
	return getPersonnelsAvecType<MedecinResident>().size();
}


// Methode qui lit a ligne 
// Utilise la fonction convertirStringDate implémentée dans utils.h  pour convertir dateAdhesion de string à tm
//! return un bool
bool GestionnairePersonnels::lireLignePersonnel(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePersonnel;
	std::string nomPersonnel;
	std::string id;
	std::string dateAdhesion;

	std::string dateDeNaissance;
	std::string matricule;
	std::string etablissement;

	int indexSpecialite;

	if (stream >> indexTypePersonnel >> std::quoted(nomPersonnel) >> std::quoted(id)>>std::quoted(dateAdhesion))
	{
		switch (to_enum<GestionnairePersonnels::TypePersonnel, int>(indexTypePersonnel)) {
		case TypePersonnel::Medecin:
			stream >> indexSpecialite;
			return ajouterPersonnel(Medecin(nomPersonnel, id, to_enum<Medecin::Specialite, int>(indexSpecialite),convertirStringDate(dateAdhesion)));
		case TypePersonnel::MedecinResident:
			stream >> std::quoted(dateDeNaissance) >> std::quoted(matricule) >> std::quoted(etablissement) >> indexSpecialite;
			return ajouterPersonnel(MedecinResident(nomPersonnel, dateDeNaissance, matricule, etablissement, id, to_enum<Medecin::Specialite, int>(indexSpecialite),  convertirStringDate(dateAdhesion)));
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
		}
	}

	return false;
}

