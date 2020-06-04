/*/////////////////////////////////////////////////////////////////////////////
/	TP3 : fichier GestionnairePatients.cpp                                    /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 07 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe GestionnairePatients          /
*//////////////////////////////////////////////////////////////////////////////
#include "GestionnairePatients.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "typesafe_enum.h"

//! Constructeur par defaut de la classe GestionnairePatients
GestionnairePatients::GestionnairePatients() : patients_(std::vector<std::shared_ptr<Patient>>())
{
}

//! Méhode qui cherche un patient par son numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (auto& patient : patients_)
	{
		if (*patient == numeroAssuranceMaladie)
		{
			return patient.get();
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

//! Operateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return        Un bool qui indique si l'opération a bien fonctionnée
bool GestionnairePatients::operator+=(Patient* patient)
{
	if (patient && !chercherPatient(patient->getNumeroAssuranceMaladie())) {

		if (patients_.size() >= NB_PATIENT_MAX)
		{
			return false;
		}
		if (dynamic_cast<PatientEtudiant*>(patient))
		{
			patients_.push_back(std::make_shared<PatientEtudiant>(*dynamic_cast<PatientEtudiant*>(patient)));

		}
		else
		{
			patients_.push_back(std::make_shared<Patient>(*patient)); /// dynamic pas besoin ca c est deja un patient*
		}
		return true;
	}
	return false;
}

//! opérateur qui affiche les patients
//! \param os Le stream dans lequel afficher
//! \param gestionnairePatients le gestionnaire de patient que l'on veut afficher
std::ostream& operator<<(std::ostream& os, const GestionnairePatients& gestionnairePatients)
{
	for (const auto& patient : gestionnairePatients.patients_)
	{
		patient->afficher(os);
		os << '\n';
	}

	return os;
}

//! Méthode qui retourne tous les  patients
//! \return patients_ les patients
const std::vector<std::shared_ptr<Patient>>& GestionnairePatients::getPatients() const
{
	return patients_;
}


//! Méthode qui ajoute un patient au vecteur de patients étudiants si celui-ci est un étudiant
//! return vectTemp le vecteur de PatientEtudiant*

 std::vector<PatientEtudiant*> GestionnairePatients::getPatientsEtudiants()const
{
	std::vector<PatientEtudiant*> vectTemp;
	for ( const auto& patient : patients_) {
		if (dynamic_cast<PatientEtudiant*>(patient.get()))             //on cherche si le type est un patientÉtudiant
		{
			vectTemp.push_back(dynamic_cast<PatientEtudiant*>(patient.get()));   // si c'est le cas, on ajoute le patient dans le vetTemp de patient etudiant
		}
	}
	return vectTemp;
}

//! Méthode qui retourne le nombre des patients dans la liste
//! \return Le nombre de patients dans la liste
size_t GestionnairePatients::getNbPatients() const
{
	return patients_.size();
}

//! Méthode qui donne le nombre de patients étudiants
//! return le nombre de patients étudiants (size_t)

size_t GestionnairePatients::getNbPatientsEtudiants() const
{
	return getPatientsEtudiants().size();
}

//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypePatient; // Indique le type de patient. 0 : Patient , 1 : PatientEtudiant (voir l'enum TypePatient)
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;

	std::string matricule;
	std::string etablissement;

	if (stream >> indexTypePatient >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie))
	{
		TypePatient typePatient = to_enum<GestionnairePatients::TypePatient, int>(indexTypePatient);
		 
		switch (typePatient)
		{

		case GestionnairePatients::TypePatient::Patient:
			return *this += (std::make_shared<Patient>(Patient(nomPatient, anneeDeNaissance, numeroAssuranceMaladie))).get();

			break;
		case GestionnairePatients::TypePatient::PatientEtudiant:
			if (stream >> std::quoted(matricule) >> std::quoted(etablissement))
			{
				return  *this += (std::make_shared<PatientEtudiant>(PatientEtudiant(nomPatient, anneeDeNaissance, numeroAssuranceMaladie, matricule, etablissement))).get();
			}
			break;

		default: assert(false); // ne devrait pas passer avec le fichier fourni

		}
	}
	return false;
}
