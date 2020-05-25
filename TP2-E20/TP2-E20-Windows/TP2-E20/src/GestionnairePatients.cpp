/* ////////////////////////////////////////////////////////////////////////////
/	TD2 : fichier GestionnairePatients.cpp                                    /
/	travail fait par Bryan junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise : 24 mai 2020 à 23h55                                      /
/   Description: Implementation de la classe GestionnairePatients             /
*//////////////////////////////////////////////////////////////////////////////

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients()
{}


//! Constructeur par copie de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients(const GestionnairePatients& gestPatients)
{
	patients_.clear();
	for (std::shared_ptr<Patient> patient : gestPatients.patients_)                     // utilisation of for range-based loop
	{
		patients_.push_back(std::make_shared<Patient>(*patient));
	}
	
}



//! Méhode qui cherche un patient par son numero d assurance Maladie
//! \param numeroAssuranceMaladie  du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (std::shared_ptr<Patient> patient : patients_) //  patient a pour type std:: shared_ptr<Patient>
	
	{
	                                                       
		if (patient->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			return patient.get() ;
		}
	}

	return nullptr;
}

//! Méthode  qui permet de charger les informations des patients depuis un fichier
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succès
bool GestionnairePatients::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		patients_.clear();               // on supprime les elements nullptr initialisé lors de la constrution je crois
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (lireLignePatient(ligne) == false)
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


//! Méthode qui ajoute un patient à la liste des patients
//! grace  à une surcharge de l'opérateur+=
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePatients:: operator+=( const Patient&  patient)
{
	std::shared_ptr<Patient> patientTest = std::make_shared<Patient>(patient);
	
	if (patients_.size() < NB_PATIENT_MAX && !chercherPatient(patient.getNumeroAssuranceMaladie()))
	{
		patients_.push_back(patientTest);
		return true;

	}
	else return false;
}


//! Méthode pour afficher la liste des patients
//! grace  à une surcharge de l'opérateur<<
//! \param stream Le stream dans lequel afficher
//! / return le stream
std::ostream& operator<<(std::ostream& stream,const GestionnairePatients& gestPatients)
{
	for(std::shared_ptr<Patient> patient : gestPatients.patients_) // patient est de type shared_ptr<Patient>
	{ 
		stream << *(patient);  // on affiche les patients grace  a l operateur<< surcharger
		stream << '\n';   

	}
	return stream;
}

//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return patients_.size();                         // return nbPatients_ fonctionne pas.
}

// TODO : getPatients()  retourne une reference constante vers le vecteur patients_
const std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients() const
{
	return patients_;
}

//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;


	// Pour extraire ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> quoted(variable)

	if (stream >> quoted(nomPatient) >> quoted(anneeDeNaissance) >> quoted(numeroAssuranceMaladie))
	{
	
		return operator+=(Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie));
	}
	
}
