// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "GestionnairePatients.h"
// TODO : compléter le Constructeur par defaut de la classe GestionnairePatients en utilisant une liste d'initialisation
GestionnairePatients::GestionnairePatients() : nbPatients_(0)
{}

// TODO ajouterPatient(const Patient& patient)
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


// TODO 
// Chercher un patient dans la liste patients_ par son numéro d'assurance maladie
// Retourner le pointeur vers le patient si trouvé, sinon retourner nullptr
std::shared_ptr<Patient> GestionnairePatients::chercherPatient(const std::string& numeroAssuranceMaladie)

{
	
	for (size_t i = 0; i < nbPatients_; i++)
	{
		if (patients_[i].getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			auto test = std::make_shared<Patient>(patients_[i]);
			return test;
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
		// TODO : Envoyer chaque ligne à lireLignePatient()
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

// TODO 
void GestionnairePatients::afficher(std::ostream& stream)
{
	for (size_t i = 0; i < nbPatients_; i++)
	{
		patients_[i].afficher(stream);
		stream << '\n';
	}
}
// Afficher tous les patients contenus dans le tableau patients_ en utilisant le stream

// TODO 
size_t GestionnairePatients::getNbPatients() { return nbPatients_; }

//! Méthode qui lit les attributs d'un patient
//! \param ligne  Le string qui contient les attributs
bool GestionnairePatients::lireLignePatient(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomPatient;
	std::string numeroAssuranceMaladie;
	std::string anneeDeNaissance;
	// TODO
	// Utiliser l'opérateur d'extraction (>>) depuis le stream
	// Pour extraire tout ce qui se trouve entre "" dans un stream,
	// il faut faire stream >> std::quoted(variable)
	stream >> std::quoted(nomPatient) >> std::quoted(anneeDeNaissance) >> std::quoted(numeroAssuranceMaladie);
	Patient test(nomPatient, anneeDeNaissance, numeroAssuranceMaladie);
	// retourner true si l'opération a réussi, sinon false
	return ajouterPatient(test);
	//return false;
}