// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée

#include <iostream>
#include "typesafe_enum.h"
#include"Medecin.h"

constexpr std::size_t CAPACITE_PATIENTS_INITIALE = 2;

// TODO compléter le Constructeur par paramètre  de la classe Medecin avec une liste d'initialisation
// Utilisez CAPACIT_PATIENTS_INITIALE pour la taille initiale de patientsAssocies_ (tableau de taille dynamique)
Medecin::Medecin(const std::string& nom, const std::string& numeroLicence, Specialite specialite) : nom_(nom), numeroLicence_(numeroLicence), specialite_(specialite), estActif_(true),
nbPatientsAssocies_(0),capacitePatientsAssocies_(CAPACITE_PATIENTS_INITIALE),
patientsAssocies_(std:: make_unique<std::shared_ptr<Patient>[]>(CAPACITE_PATIENTS_INITIALE)) {}

//! Méthode qui ajoute un patien à liste des patients associes au medecin.
//! \param Patient patient à ajouter
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

// TODO
bool Medecin::supprimerPatient(const std::string& numeroAssuranceMaladie)
{
	
	for (size_t i(0); i < nbPatientsAssocies_; i++)
	{
		if(patientsAssocies_[i].get()->getNumeroAssuranceMaladie() == numeroAssuranceMaladie)
		{
			patientsAssocies_[i] = std::move(patientsAssocies_[nbPatientsAssocies_ - 1]);
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
		patientsAssocies_[i].get()->afficher(stream);
		stream << '\n';
	}
    stream << '\n';
}

// TODO 
const std::string& Medecin::getNom() const
{
	return  nom_;
}

// TODO 
const std::string& Medecin::getNumeroLicence() const
{
	return numeroLicence_;
}

// TODO
bool Medecin::getEstActif() const
{
	return estActif_;
}


// TODO
const size_t Medecin::getCapacitePatientAssocies() const
{
	return capacitePatientsAssocies_;
 }

// TODO getNombrePatientsAssocies() : retourner le nombre de patients dans le tableau patientsAssocies_
const size_t Medecin:: getNombrePatientsAssocies () const
{
	return nbPatientsAssocies_;
}
// TODO getPatientsAssocies() : retourner le tableau des patients associés au médecin (attribut patientsAssocies_)
std::unique_ptr<std::shared_ptr<Patient>[]> Medecin::getPatientsAssocies() 
{
	return std::move(patientsAssocies_);
}
const Medecin :: Specialite Medecin::getSpecialite() const
{
	return specialite_;
}
// TODO 
void Medecin :: setNom(const std::string& nom)
{
	nom_ = nom;
}
// TODO 
void Medecin::setNumeroLicence(const std::string& numeroLicence)
{
	numeroLicence_ = numeroLicence;
}

// TODO
void Medecin::setEstActif(bool estActif)
{
	estActif_ = estActif;
}


// TODO
void Medecin::setSpecialite(Specialite specialite)
{
	specialite_ = specialite;
}
