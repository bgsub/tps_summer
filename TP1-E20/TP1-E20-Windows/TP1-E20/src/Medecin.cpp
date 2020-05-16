// TODO: Faire l'entête de fichier
/* ////////////////////////////////////////////////////////////////
/	TD1 : fichier Medecin.cpp                                     /
/	travail fait par Bryan junior Ngatshou : 1956611              /
/					 Félix Moreau		   : 1846157              /
/                                                                 /
/	Date de remise : 17 mai 2020 à 23h55                          /
/   Description: Implementation de la classe Medecin              /
*//////////////////////////////////////////////////////////////////


// TODO: Inclure la définition de la classe appropriée

//   Nous pensons ne pas avoir besoin de destructeurs car les smarts pointeurs gerent leur  propre memoire ( y sont smarts ahahah... ok , j arrete)

#include <iostream>
#include "typesafe_enum.h"
#include"Medecin.h"

constexpr std::size_t CAPACITE_PATIENTS_INITIALE = 2;

//! Constructeur de la classe Medecin
//! \param nom du medecin         
//! \param numero du medecin     
//! \param specialite du medecin     
Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite) : nom_(nom), numeroLicence_(numeroLicence), specialite_(specialite), estActif_(true),
nbPatientsAssocies_(0),capacitePatientsAssocies_(CAPACITE_PATIENTS_INITIALE),
patientsAssocies_(std:: make_unique<std::shared_ptr<Patient>[]>(CAPACITE_PATIENTS_INITIALE)) {}

//! Méthode qui ajoute un patient à liste des patients associes au medecin.
//! \param Patient patient à ajouter
//! \aucun parametre de retour 

void Medecin::ajouterPatient(Patient patient)
{
	static constexpr unsigned int AUGMENTATION_NOMBRE_PATIENTS = 2;
	
	if (capacitePatientsAssocies_ < (nbPatientsAssocies_ + 1))
	{capacitePatientsAssocies_ *= AUGMENTATION_NOMBRE_PATIENTS; // double la capacite
	auto test = std::make_unique<std::shared_ptr<Patient>[]>(capacitePatientsAssocies_); // utilisation d auto car type long
	for (size_t i = 0; i < capacitePatientsAssocies_ / AUGMENTATION_NOMBRE_PATIENTS;i++ ) {
		test[i] = patientsAssocies_[i];

	}
	patientsAssocies_ = std::move(test);
	}
	auto test2 = std::make_shared<Patient>(patient); // on transforme patient en smart ptr
	patientsAssocies_[nbPatientsAssocies_] = test2; // ajout du patient
	nbPatientsAssocies_++; //maj du nbre de patients

}
//! Méthode qui supprime un patient à liste des patients associes au medecin.
//! \param string numeroAssuranceMaladie du patient a ajouter
//! \aucun parametre de retour 

bool Medecin::supprimerPatient(const std::string& numeroAssuranceMaladie)
{
	
	for (size_t i(0); i < nbPatientsAssocies_; i++)
	{
		if(patientsAssocies_[i].get()->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			patientsAssocies_[i] = std::move(patientsAssocies_[nbPatientsAssocies_ - 1]);  // move deplace aussi chaque element dans le tableau car il s'agit de smarts pointers(wow)
			patientsAssocies_[nbPatientsAssocies_ - 1].reset();
			nbPatientsAssocies_-=1;
			return true;
		}
	}
	return false;
}


//! Méthode pour afficher les informations du medecin
//! \param stream dans lequel on ecrit les informations du medecin
void Medecin::afficher(std::ostream& stream) const
{
	static const std::string SPECIALITES[] = {  "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre"};
	auto index = enum_value(specialite_);
	assert(valid_as_enum<Specialite>(index));
	std::string specialite = SPECIALITES[index];

	std::string statut = estActif_ ? "Actif" : "Inactif";

    stream << "\nMedecin: " << nom_
           << "\n\tNumero de licence: " << numeroLicence_ 
		   << "\n\tSpecialite: " << specialite
		   << "\n\tStatut: " << statut
           << (nbPatientsAssocies_ == 0 ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");


	// TODO : afficher les patients associés au medecin
	stream << '\n';
	for (size_t i = 0; i < nbPatientsAssocies_; i++)
	{
		stream << "\t\t";
		patientsAssocies_[i].get()->afficher(stream);     // fonction afficher de chaque patient grace au stream 
		stream << '\n';
	}
    stream << '\n';
}

//! Méthode qui retourne le nom du medecin
const std::string& Medecin::getNom() const
{
	return  nom_;
}

//! Méthode qui retourne le numero de licence du medecin
const std::string& Medecin::getNumeroLicence() const
{
	return numeroLicence_;
}

//! Méthode qui retourne si le medecin est actif ou pas 
bool Medecin::getEstActif() const
{
	return estActif_;
}


//! Méthode qui retourne  la capacite du tableau de patients associes
const size_t Medecin::getCapacitePatientAssocies() const
{
	return capacitePatientsAssocies_;
 }

//! Méthode qui retournele nombre de patients associes au medecin
const size_t Medecin:: getNombrePatientsAssocies () const
{
	return nbPatientsAssocies_;
}
//! Méthode qui retourne le tableau de patients associes 
std::unique_ptr<std::shared_ptr<Patient>[]> Medecin::getPatientsAssocies() 
{
	return std::move(patientsAssocies_);
}
//! Méthode qui retourne la specialite 
const Medecin :: Specialite Medecin::getSpecialite() const
{
	return specialite_;
}
//! Méthode qui set le nom 
void Medecin :: setNom(const std::string& nom)
{
	nom_ = nom;
}
//! Méthode qui set le numero de licence
void Medecin::setNumeroLicence(const std::string& numeroLicence)
{
	numeroLicence_ = numeroLicence;
}

//! Méthode qui set si le medecin est actif ou pas
void Medecin::setEstActif(bool estActif)
{
	estActif_ = estActif;
}

//! Méthode qui set la specialite du medecin
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}
