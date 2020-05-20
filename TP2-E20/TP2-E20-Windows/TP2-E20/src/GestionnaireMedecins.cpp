// TODO: Faire l'entête de fichier

#include "GestionnaireMedecins.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr size_t CAPACITE_MEDECINS_INITIALE = 2;
constexpr int MEDECIN_INEXSISTANT = -1;

//! Constructeur par defaut de la classe GestionnaireMedecins
GestionnaireMedecins::GestionnaireMedecins()
	: nbMedecins_(0)
	, capaciteMedecins_(CAPACITE_MEDECINS_INITIALE)
	, medecins_(std::vector<std::shared_ptr<Medecin>>(CAPACITE_MEDECINS_INITIALE))
{
}

GestionnaireMedecins::  GestionnaireMedecins(const GestionnaireMedecins& gestMedecins):nbMedecins_(gestMedecins.nbMedecins_),capaciteMedecins_(gestMedecins.capaciteMedecins_)
{
	medecins_.clear();
	for (size_t i = 0; i < gestMedecins.getNbMedecins(); i++)
	{
		medecins_.push_back(std::make_shared<Medecin>(*gestMedecins.medecins_[i]));
	}
}
GestionnaireMedecins& GestionnaireMedecins::operator=(const GestionnaireMedecins& gestMedecins)
{
	if (this != &gestMedecins)
	{
		//medecins_.clear();
		nbMedecins_ = gestMedecins.nbMedecins_;
		capaciteMedecins_ = gestMedecins.capaciteMedecins_;
		

		for (size_t i= 0; i < gestMedecins.getNbMedecins(); i++)
		{
			auto medecinTest = std::make_shared<Medecin>(*gestMedecins.medecins_[i]);
			medecins_.push_back(std::move(medecinTest));   
		}
	}
	return *this;
}
//! Méthode qui cherche un medecin par son nom
//! \param nomMedecin Le nom du medecin à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le medecin n'existe pas dans la liste des medecin.
Medecin* GestionnaireMedecins::chercherMedecin(const std::string& numeroLicence)
{
	for (size_t i = 0; i < getNbMedecins(); i++)
	{

		// Adapater la ligne ci-dessous en utilisant l'operateur == pour la comparaison
		if (numeroLicence == medecins_[i]->getNumeroLicence())
		{
			return medecins_[i].get();
		}
		else return nullptr;
	}

	
}


//! Méthode  qui permet de charger les informations des medecins depuis un fichier
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succes
bool GestionnaireMedecins::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		// Doit être adaptée pour vecteur
		nbMedecins_ = 0;
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (lireLigneMedecin(ligne) == false)
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


// TODO: Methode ajouterMedecin doit être remplacée par l'opérteur +=. il prend en paramètre une référence vers le medecin à ajouter
// Retourne true si l'opération d'ajout est réussie, false si non.

//! Méthode qui ajoute un médecin à la liste des patients
//! \param medecin Le medecin à ajouter
bool GestionnaireMedecins:: operator+=(Medecin& medecin)
{
	auto medecinTest = std::make_shared<Medecin>(medecin);
	for (size_t i = 0; i < medecins_.size(); i++)
	{
		if (medecins_[i] != medecinTest)
		{
			medecins_.push_back(std::move(medecinTest));
			return true;
		}
		return false;
	}

}

// TODO: Methode supprimerMedecin doit être remplacée par l'operteur -= Il prend en paramètre le numéro de licence 
// Retourne true si l'opération d'ajout est réussi, false si non.

//! Méthode  qui permet de supprimer un medecin
//! \param numeroLicence   numero de licence du medecin a supprimer
//! \return             Un bool qui indique si le medecin a été supprimé
bool GestionnaireMedecins::operator-=(const std::string& numeroLicence)
{
	int indexMedecin = trouverIndexMedecin(numeroLicence);

	if (indexMedecin != MEDECIN_INEXSISTANT)
	{
		medecins_[indexMedecin]->setEstActif(false);
		return true;
	}

	return false;

}

// TODO : La methode afficher doit être remplacée par l’opérateur << 
//! Méthode pour afficher la liste des medecins
//! \param stream Le stream dans lequel afficher
std:: ostream& operator<<(std::ostream& out, const GestionnaireMedecins& gestMedecins)
{
	for (size_t i = 0; i <gestMedecins.getNbMedecins(); i++)
	{
		out << *(gestMedecins.medecins_[i].get());
		out << '\n';
	}
	return out;
}



//! Méthode qui retourne le nombre des medecins dans la liste
//! \return Le nombre de medecins dans la liste
size_t GestionnaireMedecins::getNbMedecins() const
{
	return nbMedecins_;
}

// TODO : getMedecins() retourne une reference constante vers le vecteur medecins_
const std::vector<std::shared_ptr<Medecin>>& GestionnaireMedecins::getMedecins() const
{
	return medecins_;
}

size_t GestionnaireMedecins::getCapaciteMedecins() const
{
	
	return medecins_.capacity();
}

//! Méthode qui lit les attributs d'un medecin
//! \param ligne  Le string qui contient les attributs
bool GestionnaireMedecins::lireLigneMedecin(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomMedecin;
	std::string numeroLicence;
	int indexSpecialite;


	// Pour extraire ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> quoted(variable)

	if (stream >> std::quoted(nomMedecin) >> std::quoted(numeroLicence) >> indexSpecialite)
	{
		// Adapter cette méthode pour utiliser l'opérateur+=
		Medecin medecin = Medecin(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite));

		
		return operator+=(medecin);
	}

	return false;
}

//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
//! \return             int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
int GestionnaireMedecins::trouverIndexMedecin(const std::string& numeroLicence)
{
	// À Adapter pour vecteur et l'utilisation l'opérateur == 
	for (std::size_t i = 0; i < medecins_.size(); i++)
	{
		if (medecins_[i]->getNumeroLicence() == numeroLicence)
		{
			return static_cast<int>(i);
		}
	}
	return MEDECIN_INEXSISTANT;
}
