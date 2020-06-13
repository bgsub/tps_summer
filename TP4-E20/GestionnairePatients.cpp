/* ////////////////////////////////////////////////////////////////////////////
/	TP4 : fichier GestionnairePatients.cpp                                    /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 14 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe GestionnairePatients          /
*//////////////////////////////////////////////////////////////////////////////

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"
#include "Foncteurs.h"

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients() : patients_(std::vector<std::shared_ptr<Patient>>())
{
}

// Methode qui permet de chercher le patient dans la liste des patients
// param	reference constante vers le numero d'assurance maladie du patient
//! return	un pointeur de patient
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie) 
{
	auto it = std::find_if(patients_.begin(), patients_.end(), ComparateurEstEgalAvecId<Patient>(numeroAssuranceMaladie));
	if (it != patients_.end())    // patients_.end() correspond  aune case vide je crois
	{
		return  (*it).get();
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
		patients_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLignePatient(ligne))
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

// Méthode générique ajouterPatient 
//!Param: référence vers l'objet à ajouter
//!return un bool

template<typename T>
bool GestionnairePatients::ajouterPatient(const T& patient)
{
	
	if (!chercherPatient(patient.getNumeroAssuranceMaladie())) {  // cette ligne ci me dérange , ahhahaha

		if (patients_.size() >= NB_PATIENT_MAX)
		{
			return false;
		}

		patients_.push_back(std::make_shared<T>(patient));

		return true;
	}

	return false;
}

// La méthode supprimerPatient
//! param : numero d'assurance Maladie de type string patient à supprimer
// Return un booleen

bool GestionnairePatients::supprimerPatient(const std::string& numeroAssuranceMaladie)
{
	/*const auto& it = std::remove_if(patients_.begin(), patients_.end(), ComparateurEstEgalAvecId<Patient>(numeroAssuranceMaladie));
	patients_.erase(it,patients_.end());*/
	size_t size = patients_.size();
	patients_.erase(std::remove_if(patients_.begin(), patients_.end(), ComparateurEstEgalAvecId<Patient>(numeroAssuranceMaladie)), patients_.end());

	if (size > patients_.size())
	{
		return true;
	}
	else {
		return false;
	}
	
}


// Methode qui permet d'afficher les informations d'un patient
//param: os (la stream), une reference constante vers la classe GestionnairePatients
std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatients)
{
	// Code fourni
	if constexpr (false) 

	{
		for (auto it = gestionnairePatients.patients_.cbegin(); it != gestionnairePatients.patients_.cend(); ++it)
		{
			(*it)->afficher(os); //  ici it c est un iterator et non un pointer so on le derefence
			os << '\n';
		}
		return os;
	}
	// TODO
	else
	{
		for (const auto& it : gestionnairePatients.patients_)
		{
			(it)->afficher(os);   
			os << '\n';
		}

		return os;
	}
}

//! Méthode qui retourne tous les  patients
//! \return patients_ les patients
const std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients() const
{
	return patients_;
}

// Methode getPatientsEtudiants
//! Return un vecteur de pointeur shared_ptr vers Patient
std::vector<std::shared_ptr<Patient>> GestionnairePatients::getPatientsEtudiants() const
{
	std::vector<std::shared_ptr<Patient>> patientsEtudiants;
	std::copy_if(patients_.begin(), patients_.end(), back_inserter(patientsEtudiants), ComparateurTypePatient<PatientEtudiant>());
	return patientsEtudiants;
}

//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return patients_.size();
}

//! Méthode qui retourne le nombre des patients étudiants dans la liste
//! \return Le nombre de patients étudiants dans la liste
size_t GestionnairePatients::getNbPatientsEtudiants() const
{
	return getPatientsEtudiants().size();
}

// Methode qui permet de lisre un patient
//!Param : un string qui represente la ligne lue
//!return un bool
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePatient;
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;
	std::string dateAdhesion;
	Patient patient;
	std::string matricule;
	std::string etablissement;
	PatientEtudiant patientEtudiant;

	if (stream >> indexTypePatient >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie))
	{
		switch (to_enum<GestionnairePatients::TypePatient, int>(indexTypePatient)) {
		case TypePatient::Patient:
			return  ajouterPatient(Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, convertirStringDate(dateAdhesion)));
		case TypePatient::PatientEtudiant:
			stream >> std::quoted(matricule) >> std::quoted(etablissement);
			return ajouterPatient(PatientEtudiant(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, convertirStringDate(dateAdhesion), matricule, etablissement));
		default:
			assert(false); // ne devrait pas se passer avec le fichier fourni
		}

		return true;
	}

	return false;
}
