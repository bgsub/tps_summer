/* ////////////////////////////////////////////////////////////////////////////
/	TD2 : fichier Patient.cpp                                                 /
/	travail fait par Bryan junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise : 24 mai 2020 à 23h55                                      /
/   Description: Implementation de la classe Patient                          /
*//////////////////////////////////////////////////////////////////////////////

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



//! Méthode qui affiche les informations d'un patient
//! \param stream Le stream dans lequel afficher.
//! /return le stream.
std::ostream& operator<<(std::ostream& stream, const Patient& patient) 
{
	
	stream << "Patient: " << patient.nom_ << " | Date de naissance: " << patient.dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << patient.numeroAssuranceMaladie_;
	return stream;
}

//! Methode qui compare un patient avec un string
//! \param le nom du patient string qui doit etre comparé
// return un booleen
bool Patient:: operator==(std::string numAssMal)
{
	return(numeroAssuranceMaladie_ == numAssMal);
}

//! Methode qui compare un patient avec un string
//! \param le nom  du patient string qui doit etre comparé
//! \param le le Patient qui doit etre comparé
// return un booleen
 bool operator==(const std::string& numAssMal,  Patient patient)      // pas pareil que la declaration ?
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
