// TODO: Faire l'entête de fichier

#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients()
	: nbPatients_(0)
{
}

GestionnairePatients::GestionnairePatients(const GestionnairePatients& gestPatients): nbPatients_(gestPatients.nbPatients_)
{
	for (size_t i = 0; i < gestPatients.getNbPatients(); i++)
	{
		patients_.push_back(std::make_shared<Patient>(*gestPatients.patients_[i]));
	}
}

GestionnairePatients& GestionnairePatients::operator=(const GestionnairePatients& gestPatients)
{
	if (this != &gestPatients)
	{
		patients_.clear();

		for (size_t i = 0; i < gestPatients.patients_.size(); i++)
		{
			auto patientTest = std::make_shared<Patient>(*gestPatients.patients_[i]);
			patients_.push_back(std::move(patientTest));
		}

	}

	return *this;
}

//! Méhode qui cherche un patient par son nom
//! \param nomPatient Le nom du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	//for (auto patient : patients_)
	for(size_t i = 0; i<patients_.size();i++)
	{
		// À adapter au vecteur et pour l'opérateur==
	                                                          // vu sur gfg but no idea if it works
		if (patients_[i].get()->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			return patients_[i].get() ;
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
		// À adapter au vecteur
		patients_.clear();
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

// TODO: Methode ajouterPatientdoit être remplacée par l'operteur +=. il prend en paramètre une référence vers le patient à ajouter
// Retourne true si l'opération d'ajout est réussi, false si non.

//! Méthode qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePatients:: operator+=( Patient  patient)
{
	auto patientTest = std::make_shared<Patient>(patient);
	for (size_t i = 0; i < patients_.size(); i++)
	{
		if (patients_[i] == std::move(patientTest)) return false;
	}
	if (patients_.size() < NB_PATIENT_MAX)
	{
		patients_.push_back(patientTest);
		return true;
		
	}
	else return false;
}

// TODO : La methode afficher  doit être remplacée L’opérateur << 
//! Méthode pour afficher la liste des patients
//! \param stream Le stream dans lequel afficher
std::ostream& operator<<(std::ostream& stream, GestionnairePatients& gestPatients)
{
	for (size_t i = 0; i < gestPatients.getPatients().size(); i++)
	{
		stream << *(gestPatients.patients_[i].get());
		stream << '\n';
	}
	stream << gestPatients.getNbPatients();  // juste pour verifier, doit etre enlever
	return stream;
}

//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return nbPatients_;
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
		// Adapter cette méthode pour utiliser l'opérateur+=
		Patient patient = Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie);
		bool succes = operator+=(patient);
		return succes;
	}
	else return false;
}
