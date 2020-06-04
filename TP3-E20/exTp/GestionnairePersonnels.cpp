/*/////////////////////////////////////////////////////////////////////////////
/	TP3 : fichier GestionnairePersonnels                                      /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 07 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe GestionnairePersonnels        /
*//////////////////////////////////////////////////////////////////////////////
#include "GestionnairePersonnels.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

constexpr int PERSONNEL_INEXSISTANT = -1;

//! Méthode qui cherche un personnel par son id
//! \param id L'identifiant du personnel à chercher
//! \return Un pointeur vers le personnel. Le pointeur est nullptr si le personnel n'existe pas dans la liste des personnels.
Personnel* GestionnairePersonnels::chercherPersonnel(const std::string& id)
{
	for (const auto& personnel : personnels_)
	{
		if (*personnel == id)
		{
			return personnel.get();
		}
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

//! Operateur qui ajoute un personnel à la liste des personnels
//! \param personnel Le personnel à ajouter
//! \return          Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePersonnels::operator+=(Personnel* personnel)
{
	if (personnel && !chercherPersonnel(personnel->getId()))
	{
		if (dynamic_cast<MedecinResident*>(personnel)) {
			personnels_.push_back(std::make_shared<MedecinResident>(*dynamic_cast<MedecinResident*>(personnel)));
		}
		else if (dynamic_cast<Medecin*>(personnel)) {
			personnels_.push_back(std::make_shared<Medecin>(*dynamic_cast<Medecin*>(personnel)));
		}
		else {
			assert(false);
		}
		return true;
	}
	return false;
}

//! Operateur qui supprime un personnel de la liste des personnels en rendant son statut estActif à false
//! \param id	  L'identifiant du personnel à supprimer
//! \return       Un bool qui indique si l'opération a bien fonctionné
bool GestionnairePersonnels::operator-=(const std::string& id)
{
	int indexPersonnel = trouverIndexPersonnel(id);
	if (indexPersonnel != PERSONNEL_INEXSISTANT)
	{
		personnels_[indexPersonnel]->setEstActif(false);
		return true;
	}

	return false;
}

//! Operateur qui permet d'afficher les informations des personnels 
//! \param os					   Le stream dans lequel afficher
//! \param gestionnairePersonnels  Le gestionnaire personnels à afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePersonnels& gestionnairePersonnels)
{
	for (const auto& personnel : gestionnairePersonnels.personnels_)
	{
		personnel->afficher(os);
		os << '\n';
	}
	return os;
}

//! Méthode qui retourne la liste de tout le personnel de l'hôpital
//! \return personnels_ la liste du personnel
const std::vector<std::shared_ptr<Personnel>>& GestionnairePersonnels::getPersonnels() const
{
	return personnels_;
}


//! Méthode qui ajoute un personnel au vecteur de medecins si celui-ci est un médecin
//! return vectTemp un vecteur de Medecin*

std::vector<Medecin*> GestionnairePersonnels::getMedecins() const
{
	std::vector<Medecin*> vectTemp;
	for (const auto& personnel : personnels_)
	{
		if (dynamic_cast<Medecin*>(personnel.get()))
		{
			vectTemp.push_back(dynamic_cast<Medecin*>(personnel.get()));
		}
	}
	return vectTemp;
}


//! Méthode qui ajoute un personnel au vecteur de médecins résidents si celui-ci est un médecin résident
//! return vectTemp vecteur de MedecinResident*
std::vector<MedecinResident*> GestionnairePersonnels::getMedecinsResidents() const
{
	std::vector<MedecinResident*> vectTemp;
	for (const auto& personnel : personnels_)
	{
		if (dynamic_cast<MedecinResident*>(personnel.get()))
		{
			vectTemp.push_back(dynamic_cast<MedecinResident*>(personnel.get()));
		}
	}
	return vectTemp;
}



//! Méthode qui donne le nombre de personnels
//! return le nombre de personnels (size_t)
size_t GestionnairePersonnels:: getNbPersonnels() const
{
	return personnels_.size();
}

//! Méthode qui donne le nombre de médecins
//! return le nombre de médecins (size_t)
size_t GestionnairePersonnels::getNbMedecins() const
{
	return getMedecins().size();
}
//! Méthode qui donne le nombre de médecins résidents
//! return le nombre de médecins résidents (size_t)
size_t GestionnairePersonnels:: getNbMedecinsResidents() const
{
	return getMedecinsResidents().size();
}

//! Méthode qui lit les attributs d'un personnel
//! \param ligne  Le string qui contient les attributs
bool GestionnairePersonnels::lireLignePersonnel(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePersonnel;
	std::string nomPersonnel;
	std::string id;

	std::string dateDeNaissance;
	std::string matricule;
	std::string etablissement;

	int indexSpecialite;

	if (stream >> indexTypePersonnel >> std::quoted(nomPersonnel) >> std::quoted(id))
	{
		
		 TypePersonnel typepPersonnel=  to_enum<GestionnairePersonnels::TypePersonnel, int>(indexTypePersonnel);

		 switch (typepPersonnel)
		 {
		 case GestionnairePersonnels::TypePersonnel::Medecin:
			 if (stream >> indexSpecialite)
			 {
				Medecin::Specialite specialite= to_enum<Medecin::Specialite, int>(indexSpecialite);
				auto medecinTest = std::make_shared<Medecin>(Medecin(nomPersonnel, id, specialite));
				return *this += (medecinTest.get());

			 }
			 break;
		 case GestionnairePersonnels::TypePersonnel::MedecinResident:
			 if (stream >> std::quoted(dateDeNaissance)>> std::quoted(matricule)>>std::quoted(etablissement)>>indexSpecialite)
			 {
				 Medecin::Specialite specialite = to_enum<Medecin::Specialite, int>(indexSpecialite);
				 auto medecinResTest = std::make_shared<MedecinResident>(MedecinResident(nomPersonnel, dateDeNaissance, matricule, etablissement, id, specialite));
				 return *this += (medecinResTest.get());

			 }
			 break;
	
		 default:
			 assert(false);
		 }


	}

	return false;
}

//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
//! \return             int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
int GestionnairePersonnels::trouverIndexPersonnel(const std::string& id)
{
	for (std::size_t i = 0; i < personnels_.size(); i++)
	{
		if (*personnels_[i] == id)
		{
			return static_cast<int>(i);
		}
	}
	return PERSONNEL_INEXSISTANT;
}
