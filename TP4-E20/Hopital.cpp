/* ////////////////////////////////////////////////////////////////////////////
/	TP4 : fichier Hopital.cpp                                                 /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 14 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe Hopital                       /
*//////////////////////////////////////////////////////////////////////////////

#include "Hopital.h"
#include "ConsultationEnligne.h"
#include "ConsultationPhysique.h"
#include "typesafe_enum.h"
#include "assert.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include<algorithm>
#include"Foncteurs.h"


//! Constructeur par paramètre  de la classe Hopital
//! \param nom      Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse) :nom_(nom), adresse_(adresse)
{
}


// Methode qui charge les consultations en faisant appel à la fonction chargerDepuisFichierConsultation 
//! param , les noms de fichier de patients, de consultations et de perssonnels
//! return un bool
bool Hopital::chargerBaseDeDonnees(const std::string& nomFichierPersonnels, const std::string& nomFichierPatients, const std::string& nomFichierConsultations)
{
	return gestionnairePersonnels_.chargerDepuisFichier(nomFichierPersonnels)
		&& gestionnairePatients_.chargerDepuisFichier(nomFichierPatients) && chargerDepuisFichierConsultation(nomFichierConsultations);
}

//! Méthode  qui permet de charger les informations des consultations
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succes
bool Hopital::chargerDepuisFichierConsultation(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		consultations_.clear();
		std::string ligne;
		while (getline(fichier, ligne))
		{
			if (!lireLigneConsultation(ligne))
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

// Méthode qui retourne la moyenne de l'ancienneté des personnels de type double
// return la moyenne de l'ancienneté des personnels 
double Hopital::getAncienneteMoyenneDesPersonnels() const
{
	double somme = std::accumulate((gestionnairePersonnels_.getPersonnels()).cbegin(), (gestionnairePersonnels_.getPersonnels()).cend(), 0.0, AccumulateurPeriodePersonnel());
	return somme / (static_cast<double>(gestionnairePersonnels_.getNbPersonnels()));
	
}


// Methode getCosultationsEntreDates
//!param : date1 et date2 des références constantes vers des objets de type tm
//!return un vecteur de shared_ptr vers Consultation
std::vector <std::shared_ptr<Consultation>> Hopital::getConsultationsEntreDates(const  tm& date1, const tm& date2) const
{
	std::vector <std::shared_ptr<Consultation>> temp;
	std::copy_if(consultations_.begin(), consultations_.end(), back_inserter(temp),  EstDansIntervalleDatesConsultation(date1, date2));
	return temp;
}

//  Methode ajouterConsultation qui permet d'ajouter une consultattion et retourne un bool qui indique si elle a ete ajoutee 
//! param:  une référence vers l'objet à ajouter
//! return un bool
template<typename T>
bool Hopital::ajouterConsultation( T& consultation)
{
	Medecin* medecin = dynamic_cast<Medecin*>(gestionnairePersonnels_.chercherPersonnel(consultation.getMedecin()->getId()));
	if (medecin && medecin->getEstActif())
	{
		Patient* patient = gestionnairePatients_.chercherPatient(consultation.getPatient()->getNumeroAssuranceMaladie());
		if (!patient)
			
		{
			return false;
		}

		
			consultations_.push_back(std::make_shared<T>(consultation));
		
		

		Patient* patientDuMedecin = medecin->chercherPatient(patient->getNumeroAssuranceMaladie());
		if (!patientDuMedecin)
		{
			*medecin += patient;
		}
		medecin->incrementNombreConsultations();

		return true;
	}

	return false;
}

//! Méthode qui retourne le nom de l'hopital
//! return nom_ le nom de l'hopital 
const std::string& Hopital::getNom() const
{
	return nom_;
}

//! Méthode qui retourne l'adresse de l'hopital
//! \return adresse_ l'adresse de l'hopital 
const std::string& Hopital::getAdresse() const
{
	return adresse_;
}

//! Méthode qui retourne le gestionnaire du personnels
//! \return gestionnairePersonnels_ gestionnaire du personnels
GestionnairePersonnels& Hopital::getGestionnairePersonnels()
{
	return gestionnairePersonnels_;
}

//! Méthode qui retourne le gestionnaire des patients
//! \return gestionnaire des patients
GestionnairePatients& Hopital::getGestionnairePatients()
{
	return gestionnairePatients_;
}

//! Méthode qui retourne les consultaions de l'hopital
//! \return consultations_ les consultations
const std::vector<std::shared_ptr<Consultation>>& Hopital::getConsultations() const
{
	return consultations_;
}

//! Méthode qui permet de mettre à jour le nom de l'hopital
//! \Param nom Le nom de l'hopital
void Hopital::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour l'adresse de l'hopital
//! \Param adresse  l'adresse de l'hopital
void Hopital::setAdresse(const std::string& adresse)
{
	adresse_ = adresse;
}

//! Méthode qui lit les attributs d'une consulation
//! \param ligne  Le string qui contient les attributs
//! \return le status de l'opération si elle s'est bien passée
bool Hopital::lireLigneConsultation(const std::string& ligne)
{
	std::istringstream stream(ligne);
	int indexTypeConsultation;
	std::string idMedecin;
	std::string idPatient;
	std::string dateConsultation;

	if (stream >> indexTypeConsultation >> std::quoted(idMedecin) >> std::quoted(idPatient) >> std::quoted(dateConsultation))
	{
		Medecin* medecin = dynamic_cast<Medecin*>(gestionnairePersonnels_.chercherPersonnel(idMedecin));
		Patient* patient = gestionnairePatients_.chercherPatient(idPatient);

		if (medecin && patient) {
			TypeConsultation typeConsultation = to_enum<Hopital::TypeConsultation, int>(indexTypeConsultation);
			if (typeConsultation == TypeConsultation::ConsultationEnLigne)
			{
				ConsultationEnligne consultation = ConsultationEnligne(*medecin, *patient, dateConsultation);

				return ajouterConsultation(consultation);
			}
			else if (typeConsultation == TypeConsultation::ConsultationPhysique)
			{
				ConsultationPhysique consultation = ConsultationPhysique(*medecin, *patient, dateConsultation);

				return ajouterConsultation(consultation);
			}
			else
			{
				assert(false); // ne devrait pas se passer avec le fichier fourni
			}
		}
		else {
			return false;
		}
	}

	return false;
}
