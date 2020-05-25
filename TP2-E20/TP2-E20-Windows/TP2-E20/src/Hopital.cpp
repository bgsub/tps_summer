/* ////////////////////////////////////////////////////////////////////////////
/	TD2 : fichier  Hopital.cpp                                                /
/	travail fait par Bryan junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise : 24 mai 2020 à 23h55                                      /
/   Description: Implementation de la classe Hopital                          /
*//////////////////////////////////////////////////////////////////////////////

#include "Hopital.h"

//! Constructeur par paramètre  de la classe Hopital
//! \param nom      Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse):nom_(nom), adresse_(adresse)
{
}

//! methode	qui charge la base de donnees
//! \parametre string nom du fichier des medecins
//! \paramtre string nom du fichier des patients
//! /return un bool
bool Hopital:: chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients)
{
	return(gestionnaireMedecins_.chargerDepuisFichier(nomFichierMedecins) && gestionnairePatients_.chargerDepuisFichier(nomFichierPatients));
}

//! operater += qui ajoute une consultation dans laliste des consultations
//! \parametre une reference vers la consultation
//! /return un bool
bool Hopital :: operator+=(Consultation& consultation)
{
	if (consultation.getMedecin()->getEstActif()  && gestionnaireMedecins_.chercherMedecin(consultation.getMedecin()->getNumeroLicence())
		&& gestionnairePatients_.chercherPatient(consultation.getPatient()->getNumeroAssuranceMaladie()))
	{
		consultations_.push_back(std::make_shared<Consultation>(consultation));
		return true;
	}
	else return false;
}


//! operater += qui ajoute un médecin au gestionnaire de médecins.
//! \parametre une reference vers le medecin a ajouter
//! /return un bool
bool Hopital:: operator+=( Medecin& medecin)
{
	return(gestionnaireMedecins_ += medecin);
}
//! operater += qui ajoute un patient au gestionnairePatients.
//! \parametre une reference vers le patient a ajouter
//! /return un bool
bool Hopital:: operator+=( Patient& patient)
{

	return(gestionnairePatients_+=patient);
}

//! Méthode qui retourne le nom de l'hopital
//! \return le nom de l'hopital 
const std::string& Hopital::getNom() const
{
	return nom_;
}

//! Méthode qui retourne l'adresse de l'hopital
//! \return l'adresse de l'hopital 
const std::string& Hopital::getAdresse() const
{
	return adresse_;
}

//! Méthode qui retourne le gestionnaire des medecins
//! \return gestionnaire des medecins
GestionnaireMedecins& Hopital::getGesionnaireMedecins()          
{
	return gestionnaireMedecins_;
}

//! Méthode qui retourne le gestionnaire des patients
//! \return gestionnaire des patients
GestionnairePatients& Hopital::getGestionnairePatients()                             
{
	return gestionnairePatients_;
}

// TODO : getConsultations() retourne une reference constante vers le vecteur consultation.
const std::vector <std::shared_ptr<Consultation>>& Hopital::getConsultations() const
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
