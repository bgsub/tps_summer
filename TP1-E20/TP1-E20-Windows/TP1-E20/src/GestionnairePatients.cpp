// TODO: Faire l'entête de fichier
/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier GestionnairePatient.cpp                         /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Félix Moreau		   : 1846157              /
/                                                                 /
/	Date de remise : 17 mai 2020 à 23h55                          /
/   Description: Implementation de la classe GestionnairePatients /
*//////////////////////////////////////////////////////////////////

//   Nous pensons ne pas avoir besoin de destructeurs car les smarts pointeurs gerent leur  propre memoire

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "GestionnairePatients.h"
//! Constructeur de la GestionnairePatient
//! Aucun parametre 
GestionnairePatients::GestionnairePatients() : nbPatients_(0)
{}

//! Méthode qui ajoute un patient à la liste des patients
//! \param Patient patient le  patient à ajouter
bool GestionnairePatients::ajouterPatient(const Patient& patient)
{
	if (nbPatients_ < NB_PATIENT_MAX)
	{
		patients_[nbPatients_] = patient;
		nbPatients_++;
		return true;
	}
	else return false;
}


//! Methode qui permet de chercher un patient grace a son numero d' assurance maladie
//! \param string numero d assurance maladie du patient         
//! / return un std::shared_ptr<Patient> qui represente un patient   
//! / return un nullptr si pas trouve
std::shared_ptr<Patient> GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)

{
	for (size_t i = 0; i < nbPatients_; i++)
	{
		if (patients_[i].getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			auto patientTest = std::make_shared<Patient>(patients_[i]);
			return patientTest;
		}
		else return nullptr;
	}
}


//! Méthode  qui permet de charger les informations des patients depuis un fichier
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succès
bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		std::string ligne;
		nbPatients_ = 0;
		while (std::getline(fichier, ligne))
		{
			if (!lireLignePatient(ligne))return false;

		}
		return true;
	}
	std::cerr << "Le fichier " << nomFichier
		<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";

	return false;
}

//! Methode qui permet d afficher les patients du tableau de patients
//! \param ostream stream    
void GestionnairePatients::afficher(std::ostream& stream) const
{
	for (size_t i = 0; i < nbPatients_; i++)
	{
		patients_[i].afficher(stream);
		stream << '\n';
	}
}


//! Methode qui retourne le nbre de patients
size_t GestionnairePatients::getNbPatients() const { return nbPatients_; }

//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
//! /bool si la patien a ete ajoute 
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;

	stream >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie);
	Patient test(nomPatient, anneeDeNaissance, numeroAssuranceMaladie);
	
	return ajouterPatient(test);
	
}