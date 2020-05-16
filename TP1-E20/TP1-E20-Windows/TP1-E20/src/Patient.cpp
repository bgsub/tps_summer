// TODO: Faire l'entête de fichier
/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier Patient.cpp                                     /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Félix Moreau		   : 1846157              /
/                                                                 /
/	Date de remise : 17 mai 2020 à 23h55                          /
/   Description: Implementation de la classe Patient              /
*//////////////////////////////////////////////////////////////////

// pas besoin de destructeur 

// TODO fait : Inclure la définition de la classe appropriée
#include <iostream>
#include <string>
#include"Patient.h"

//! Constructeur de la classe Patient
//! \param nom du patient          
//! \param date de naissance du patient      
//! \param numeroAssuranceMaladie du patient             
Patient::Patient(const std::string& nom, const std::string& dateDeNaissance, const std::string& numeroAssuranceMaladie) :nom_(nom),dateDeNaissance_(dateDeNaissance),numeroAssuranceMaladie_(numeroAssuranceMaladie)
{}

//! Méthode qui affiche les informations d'un patient
//! \param stream Le stream dans lequel afficher.
void Patient::afficher(std::ostream& stream) const
{
	// Ne modifiez pas cette fonction
	stream << "Patient: " << nom_ << " | Date de naissance: " << dateDeNaissance_
		<< " | Numero d\'assurance maladie: " << numeroAssuranceMaladie_;
}

//! Méthode qui retourne le nom du patient 
const std::string& Patient::getNom() const
{
	return nom_;
}

//! Méthode qui retourne le numero d assurance maladie  
const std::string& Patient::getNumeroAssuranceMaladie() const{
	return numeroAssuranceMaladie_;
}
//! Méthode qui retourne la date  de naissance du patient
const std::string& Patient::getDateDeNaissance() const
{
	return dateDeNaissance_;
}

//! methode qui set le nom
void Patient:: setNom(const std::string& nom)
{
	nom_ = nom;
}
//! methode qui set le numero d'assurance maladie
void Patient::setNumeroAssuranceMaladie(const std::string& numeroAssuranceMaladie)
{
	numeroAssuranceMaladie_ = numeroAssuranceMaladie;
}
//! methode qui set la date de naissance du patient
void Patient::setDateDeNaissance(const std::string& dateDeNaissance)
{
	dateDeNaissance_ = dateDeNaissance;
}