// TODO: Faire l'entête de fichier
/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier GestionnaireMedecins.cpp                        /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Félix Moreau		   : 1846157              /
/                                                                 /
/	Date de remise : 17 mai 2020 à 23h55                          /
/   Description: Implementation de la classe GestionnairesMedecins/
*//////////////////////////////////////////////////////////////////

//   Nous pensons ne pas avoir besoin de destructeurs car les smarts pointeurs gerent leur  propre memoire

#include <fstream>
#include <iomanip>
#include "typesafe_enum.h"
#include <iostream>
#include <sstream>
#include"GestionnaireMedecins.h"
constexpr size_t CAPACITE_MEDECINS_INITIALE = 2;
constexpr int MEDECIN_INEXSISTANT = -1;

//! Constructeur de la GestionnaireMedecins
//! Aucun parametre            
GestionnaireMedecins:: GestionnaireMedecins():nbMedecins_(0),capaciteMedecins_(CAPACITE_MEDECINS_INITIALE),
medecins_(std::make_unique<std::shared_ptr<Medecin>[]> (CAPACITE_MEDECINS_INITIALE)){}




//! Méthode qui ajoute un médecin à la liste des patients
//! \param medecin Le medecin à ajouter
void GestionnaireMedecins::ajouterMedecin(std::shared_ptr<Medecin> medecin)
{
	constexpr unsigned int AUGMENTATION_NOMBRE_MEDECINS = 2;
	
	if (capaciteMedecins_ < (nbMedecins_ + 1))
	{
		capaciteMedecins_ *= AUGMENTATION_NOMBRE_MEDECINS;

		auto tableauTest = std::make_unique<std::shared_ptr<Medecin>[]>(capaciteMedecins_);
		// copier les anciens medecins avant de faire le move
		for (size_t i = 0; i < capaciteMedecins_ / AUGMENTATION_NOMBRE_MEDECINS; i++) // puisqu on a double la capacite 
		{
			tableauTest[i] = medecins_[i];
		}
		medecins_ = std::move(tableauTest);
	}
	medecins_[nbMedecins_] = medecin; //on ajoute un medecin;
	nbMedecins_++;                     // on incremente

}
	

//! Methode qui permet de chercher un medecin grace a son numero de license
//! \param string numero de license du medecin         
//! / return un std::shared_ptr<Medecin> qui represente un medecin    
//! / return un nullptr si pas trouve

std::shared_ptr<Medecin> GestionnaireMedecins::chercherMedecin(const std::string& numeroLicence)
{
	for (size_t i = 0; i < nbMedecins_; i++)
	{
		if (medecins_[i].get()->getNumeroLicence()== numeroLicence) return medecins_[i];
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
		nbMedecins_ = 0;
		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			if (!lireLigneMedecin(ligne))return false;

		}
		return true;
		std::cerr << "Le fichier " << nomFichier
			<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
		return false;
	}
}

//! Methode qui permet de suprrimer un medecin grace a son numero de license
//! \param string numero de license du medecin         
//! / return un booleen qui nous donne l etat actif ou non du medecin   

bool GestionnaireMedecins::supprimerMedecin(const std::string& numeroLicence)
{

	bool estActif = false;
	size_t i = trouverIndexMedecin(numeroLicence);
	if (i!=MEDECIN_INEXSISTANT)
	{
		medecins_[i].get()->setEstActif(estActif);
		return true;
	}
	else return false;
	
}

//! Methode qui permet d afficher les medecins du tableau de medecin
//! \param ostream stream         
 
void GestionnaireMedecins::afficher(std::ostream& stream) const
{
	for (size_t i = 0; i < nbMedecins_; i++) {
		medecins_[i].get()->afficher(stream);
	}
	stream << '\n';
}



//! Methode qui  retourne le  nb de Medecins
size_t GestionnaireMedecins::getNbMedecins() const
{
	return nbMedecins_;
}
//! Methode qui  retourne la capacite de Medecins
size_t GestionnaireMedecins:: getCapaciteMedecins() const
{
	return capaciteMedecins_;
}


//! Méthode qui lit les attributs d'un medecin
//! \param ligne  Le string qui contient les attributs
//! /retourne un booleen qui nous dit si la lecture fut ou non un succes
bool GestionnaireMedecins::lireLigneMedecin(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomMedecin;
	std::string numeroLicence;
	int indexSpecialite;
	if (nbMedecins_ < capaciteMedecins_)
	{
		stream >> std::quoted(nomMedecin) >> std::quoted(numeroLicence) >> indexSpecialite;
		//Medecin medecin = Medecin(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite));          // nous ne comprenons pas pk cette forme n a pas fonctionne
		auto medecinTest = std::make_shared<Medecin>(Medecin(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite)));
		ajouterMedecin(medecinTest);
		return true;
	}

	else return false;

	
	
}

//! Methode qui trouve un medecin 
//! \param numero de licence du medecin
//! /retourne un int qui represente la position du medecin dans le tableau
int GestionnaireMedecins::trouverIndexMedecin(const std::string& numeroLicence) const
{
	for (size_t i = 0; i < nbMedecins_; i++)
	{
		if (medecins_[i].get()->getNumeroLicence() == numeroLicence) return i;
		else return MEDECIN_INEXSISTANT;
	}

}



