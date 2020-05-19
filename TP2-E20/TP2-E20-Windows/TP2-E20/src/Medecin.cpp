// TODO: Faire l'entête de fichier

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
	, nbPatientsAssocies_(0)
	, capacitePatientsAssocies_(CAPACITE_PATIENTS_INITIALE)
	, patientsAssocies_(std::vector<std::shared_ptr<Patient>>(CAPACITE_PATIENTS_INITIALE))
{
}

// TODO: Methode ajouterPatient doit être remplacée par l'operateur +=. il prend en paramètre le patient à ajouter
// Retourne true si l'opération d'ajout est réussi, false si non.

//! Méthode qui ajoute un patient à liste des patients associes au médecin.
//! \param Patient patient à ajouter
bool Medecin:: operator+=(Patient& patient)
{
	/*if (patientsAssocies_.size() < CAPACITE_PATIENTS_INITIALE)
	{
		auto patientTest = std::make_shared<Patient>(patient);
		patientsAssocies_.push_back(std::move(patientTest));
		return true;
	}
	else return false;*/
	auto patientTest = std::make_shared<Patient>(patient);
	for (size_t i = 0;  i<patientsAssocies_.size();i++)
	{
		if ( patientsAssocies_[i] != patientTest)
		{
			patientsAssocies_.push_back(std::move(patientTest));
			return true;
		}
		return false;
	}
	
}


// TODO: Methode supprimerPatient doit être remplacée par l'operateur -= Il prend en paramètre le numero d'assurance maladie du patient 
// Retourne true si l'opération d'ajout est réussi, false si non.

//! Méthode pour supprimer un patient de la liste des patients
//! \param le nom du patient a supprimer
bool Medecin::operator-=(std::string numAssMal)
{
	for (size_t i = 0; i < nbPatientsAssocies_; i++)
	{
		if (patientsAssocies_[i]->getNumeroAssuranceMaladie() == numAssMal)
		{
			patientsAssocies_[i].reset();

			for (size_t j = i; j < nbPatientsAssocies_ - 1; j++)
			{
				patientsAssocies_[j] = patientsAssocies_[j + 1];
			}

			patientsAssocies_.pop_back();
			nbPatientsAssocies_--;

			return true;
		}
	}

	return false;
}
// TODO : La methode afficher doit être remplacée par l’opérateur << 
//! Méthode pour afficher les informations du medecin
//! \param stream dans lequel on ecrit les informations du medecin
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
		<< (medecin.nbPatientsAssocies_ == 0 ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");

	for (std::size_t i = 0; i < medecin.nbPatientsAssocies_; i++)
	{
		out << "\n\t\t";
		out << medecin.patientsAssocies_[i];
	}
	out << '\n';
	return out;
}

// TODO : Opérateur == qui compare un string avec le numéro de la  licence du médecin avec medécin comme opérande de gauche
bool Medecin:: operator==(std::string numLicence)
{
	return(numeroLicence_ == numLicence);
}

// TODO :  Opérateur ==  qui compare le numéro de la  licence du médecin avec un le numéro de la  licence. Le numéro de licence comme opérande de gauche.
bool operator==(std::string numLicence,  Medecin medecin)
{
	return (medecin==numLicence);
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

	return nbPatientsAssocies_;
}

//! Méthode qui retourne la capacité du tableau patientsAssocies_
//! \return la capacité du tableau patientsAssocies_
const size_t Medecin::getCapacitePatientAssocies() const
{

	return capacitePatientsAssocies_;
}

//! Méthode qui retourne la liste des patients associes au medecin
//! \return la liste des patients
std::vector<std::shared_ptr<Patient>> Medecin::getPatientsAssocies()
{
	return move(patientsAssocies_);
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
