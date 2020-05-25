/* ////////////////////////////////////////////////////////////////////////////
/	TD2 : fichier Medecin.cpp                                                 /
/	travail fait par Bryan junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise : 24 mai 2020 à 23h55                                      /
/   Description: Implementation de la classe Medecin                          /
*//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "Medecin.h"
#include "typesafe_enum.h"

constexpr std::size_t CAPACITE_PATIENTS_INITIALE = 2;

//! Constructeur par paramètre  de la classe Medecin
//! \param nom              Nom du medecin
//! \param numeroLicence    Numero de licence du medecin
//! \param specialite       Specialite du medecin
Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite)
	: nom_(nom)
	, numeroLicence_(numeroLicence)
	, specialite_(specialite)

{}


//! Méthode qui ajoute un patient à liste des patients associes au médecin.
//! grace a une surcharge de l operateur+=
//! \param Patient patient à ajouter
//! /return un booleen
bool Medecin:: operator+=( Patient& patient)
{
	if (chercherPatient(patient.getNumeroAssuranceMaladie()) == nullptr)
	{
		patientsAssocies_.push_back(&patient);
		return true;
	}
	else return false;
}



//! Méthode qui supprime un patient à liste des patients associes au médecin.
//! grace a une surcharge de l operateur-=
//! \param le numero d assurance maladie du patient
//! /return un booleen
bool Medecin::operator-=(std::string numAssMal)
{
	for (size_t i = 0; i < patientsAssocies_.size(); i++)
	{
		if (chercherPatient(numAssMal))
		{
			for (size_t j = i; j < patientsAssocies_.size() - 1; j++)
			{
				patientsAssocies_[j] = patientsAssocies_[j + 1];
			}
			patientsAssocies_.pop_back();
			

			return true;
		}
	}
	return false;
}

//! Méthode pour afficher les informations du medecin
//! grace a une surcharge de  l’opérateur << 
//! \param stream dans lequel on ecrit les informations du medecin
//! \param Medecin  le medecin qui doit etre afficher
std::ostream& operator<<(std::ostream& out, const Medecin& medecin) 
{
	static const std::string SPECIALITES[] = { "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre" };
	auto index = enum_value(medecin.specialite_);
	assert(valid_as_enum<Medecin::Specialite>(index));                   // assert(valid_as_enum<Specialite>(index)) ne fonctionne pas
	
	std::string specialite = SPECIALITES[index];

	std::string statut = medecin.estActif_ ? "Actif" : "Inactif";

	out << "\nMedecin: " << medecin.nom_
		<< "\n\tNumero de licence: " << medecin.numeroLicence_
		<< "\n\tSpecialite: " << specialite
		<< "\n\tStatut: " << statut
		<< (medecin.patientsAssocies_.size() == 0 ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");

	for (std::size_t i = 0; i < medecin.patientsAssocies_.size(); i++)
	{
		out << "\n\t\t";
		out << *medecin.patientsAssocies_[i];
	}
	out << '\n';
	return out;
}



//! Methode qui compare un medecin avec un string
//! \param le numero de licence(string) du patient qui doit etre comparé
//! / return un booleen
bool Medecin:: operator==(std::string numLicence)
{
	return(numeroLicence_ == numLicence);
}

//! Methode qui compare un medecin avec un string
//! \param le numero de license(string) du medecin qui doit etre comparé
//! \param le medecin (Medecin) qui doit etre comparé
//! /return un booleen
bool operator==(const std::string& numLicence,  Medecin medecin)
{
	return (medecin==numLicence);
}


//! Methode qui compare un medecin avec un string
//! \param le numero de license(string) du medecin qui doit etre comparé
//! \param le medecin (Medecin) qui doit etre comparé
//! /return un booleen
Patient* Medecin:: chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (size_t i = 0; i<patientsAssocies_.size(); i++)
	{
		if (patientsAssocies_[i]->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			return patientsAssocies_[i];
		}
	
	}

	return nullptr;
}
//! Méthode qui retourne le nom du medecin
//! \return le nom du medecin 
const std::string& Medecin::getNom() const
{

	return nom_;
}


//! Méthode qui retourne le numero de licence du medecin
//! \return le numero de licence
const std::string& Medecin::getNumeroLicence() const
{

	return numeroLicence_;
}

//! Méthode qui retourne le status du medecin
//! \return le status du medecin
bool Medecin::getEstActif() const
{

	return estActif_;
}

//! Méthode qui retourne la specialite du medecin
//! \return la specialite des medecins
const Medecin::Specialite Medecin::getSpecialite() const
{

	return specialite_;
}

//! Méthode qui retourne le nombre de patients associés au  médecin
//! \return le nombre patient associes
const size_t Medecin::getNombrePatientsAssocies() const
{
	return patientsAssocies_.size();
}

//! Méthode qui retourne la capacité du tableau patientsAssocies_
//! \return la capacité du tableau patientsAssocies_
//const size_t Medecin::getCapacitePatientAssocies() const
//{
//
//	return capacitePatientsAssocies_;
//}

//! Méthode qui retourne la liste des patients associes au medecin
//! \return la liste des patients
 std::vector<Patient*> Medecin::getPatientsAssocies() const
{
	return patientsAssocies_;
}

//! Méthode qui met a jours le nom  du medecin
//! \pararm  nom  Le nom du médecin
void Medecin::setNom(const std::string& nom)
{
	nom_ = nom;
}

//! Méthode qui met a jours le numero de licence du medecin
//! \pararm  numeroLicence  le numero de licence du medecin
void Medecin::setNumeroLicence(const std::string& numeroLicence)
{
	numeroLicence_ = numeroLicence;
}

//! Méthode qui met a jours le statut du medecin si il est actif ou non
//! \pararm  boolean indiquant le  nouveau status du medecin
void Medecin::setEstActif(bool estActif)
{

	estActif_ = estActif;
}

//! Méthode qui met a jours la specialité du medecin
//! \pararm  specialite  specialité du medecin
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}
