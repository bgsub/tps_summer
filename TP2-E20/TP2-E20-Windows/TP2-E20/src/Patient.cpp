// TODO: Faire l'entête de fichier

#include "Patient.h"
#include <iostream>
#include <string>

//! Constructeur par paramètre  de la classe Patient
//! \param nom						Nom du patient
//! \param dateDeNaissance			Date de naissance du patient
//! \param numeroAssuranceMaladie	Le numero d'assurance maladie du patient
Patient::Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie)
	: nom_(nom)
	, numeroAssuranceMaladie_(numeroAssuranceMaladie)
	, dateDeNaissance_(dateDeNaissance)
{
}


// TODO : La methode afficher doit être remplacée par l’opérateur << 
//! Méthode qui affiche les informations d'un patient
//! \param stream Le stream dans lequel afficher.
std::ostream& operator<<(std::ostream& stream, const Patient& patient) 
{
	
	stream << "Patient: " << patient.nom_ << " | Date de naissance: " << patient.dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << patient.numeroAssuranceMaladie_;
	return stream;
}

// TODO : Opérateur == qui compare un string avec le numero d'assurance maladie du patient avec patient comme opérande de gauche
bool Patient:: operator==(std::string numAssMal)
{
	return(numeroAssuranceMaladie_ == numAssMal);
}

// TODO : Opérateur == qui compare le numero d'assurance maladie du patient avec le numero d'assurance comme opérande de gauche.
 bool operator==(std::string numAssMal,   Patient patient)      // pas pareil que la declaration ?
{
	 return(patient == numAssMal);
}

//! Méthode qui retourne le nom du patient
//! \return le nom du patient 
const std::string& Patient::getNom() const
{

	return nom_;
}

//! Méthode qui retourne le numéro d'assurance maladie du patient
//! \return le numéro d'assurance maladie du patient
const std::string& Patient::getNumeroAssuranceMaladie() const
{

	return numeroAssuranceMaladie_;
}

//! Méthode qui retourne la date de naissance du patient
//! \return la date de naissnace du patient 
const std::string& Patient::getDateDeNaissance() const
{

	return dateDeNaissance_;
}

//! Méthode qui permet de mettre à jour le nom du patient
//! \Param nom Le nom du patient
void Patient::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui permet de mettre à jour le nom du numero d'assurance maladie du patient
//! \Param numeroAssuranceMaladie le numero d'assurance maladie
void Patient::setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie)
{
	numeroAssuranceMaladie_ = numeroAssuranceMaladie;
}

//! Méthode qui permet de mettre à jour la date de naissance du patient
//! \Param dateDeNaissance date de naissance du patient
void Patient::setDateDeNaissance(const std::string& dateDeNaissance)
{
	dateDeNaissance_ = dateDeNaissance;
}
