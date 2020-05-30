//TODO : Entête du fichier
#include <iostream>
#include "Medecin.h"
#include "typesafe_enum.h"

constexpr int PATIENT_INEXSISTANT = -1;

//TODO : Constructeur par paramètre pour intialiser les attributs de la classe. 
// Il utilise le constructeur de la classe Personnel
Medecin::Medecin(const std::string& nom, const std::string& id, Specialite specialite)
	:Personnel(nom, id), specialite_(specialite), nombreConsultations_(0)

{

}
//! Operateur qui ajoute un patient à la liste des patients
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Medecin::operator+=(Patient* patient)
{
	if (patient && !chercherPatient(patient->getNumeroAssuranceMaladie())) {
		patientsAssocies_.push_back(patient);

		return true;
	}

	return false;
}

//! Operateur qui supprime un patient de la liste des patients
//! \param numeroAssuranceMaladiePatient Le patient à ajouter
//! \return      Un bool qui indique si l'opération a bien fonctionnée
bool Medecin::operator-=(const std::string& numeroAssuranceMaladiePatient)
{
	int indexPatient = trouverIndexPatient(numeroAssuranceMaladiePatient);
	if (indexPatient == PATIENT_INEXSISTANT)
	{
		return false;
	}

	patientsAssocies_.erase(patientsAssocies_.begin() + indexPatient);

	return true;
}

//TODO : méthode Afficher
std::ostream& Medecin::afficher(std::ostream& stream) const
{
	static const std::string SPECIALITES[] = { "Generaliste",
												"Cardiologue",
												"Dermatologue",
												"Gynecologue",
												"Pediatre",
												"Ophtalmologue",
												"Autre" };
	auto index = enum_value(specialite_);
	assert(valid_as_enum<Medecin::Specialite>(index));
	std::string specialite = SPECIALITES[index];

	//TODO : Afficher les informations du médecin liées à la classe Personnel
	Personnel::afficher(stream);
	stream << "\n\tSpecialite: " << specialite
		<< (patientsAssocies_.empty() ? "\n\tAucun patient n'est suivi par ce medecin." : "\n\tPatients associes:");

	for (const auto& patient : patientsAssocies_)
	{
		stream << "\n\t\t";
		patient->afficher(stream);
		return stream;
	}
}

//! Méhode qui cherche un patient par numero d'assurance maladie
//! \param numeroAssuranceMaladie Le numero d'assurance maladie Le numero d'assurance maladie du patient à chercher
//! \return Un pointeur vers le patient. Le pointeur est nullptr si le patient n'existe pas dans la liste des patients.
Patient* Medecin::chercherPatient(const std::string& numeroAssuranceMaladie)
{
	for (auto& patientsAssocie : patientsAssocies_)
	{
		if (*patientsAssocie == numeroAssuranceMaladie)
		{
			return patientsAssocie;
		}
	}

	return nullptr;
}

//TODO : Méthode incrementNombreConsultations 
// Incrementer le nombre de consultaions
void Medecin::incrementNombreConsultations()
{
	nombreConsultations_++;
}
//TODO : Méthode getSalaireAnnuel
double Medecin::getSalaireAnnuel() const
{
	return(SALAIRE_DE_BASE_MEDECIN + (nombreConsultations_ * getPrixConsultation()));
}
// le salaire annuel = salaire de base du médecin + nombre de consultations * le prix de consultation

//TODO : Méthode getPrixConsultation
double Medecin::getPrixConsultation() const
{

	switch (specialite_)
	{
	case Medecin::Specialite::Generaliste:return  60;
		break;
	case Medecin::Specialite::Cardiologue:return 120;
		break;
	case Medecin::Specialite::Dermatologue:return 120;
		break;
	case Medecin::Specialite::Gynecologue: return 100;
		break;
	case Medecin::Specialite::Pediatre:return 80;
		break;
	case Medecin::Specialite::Ophtalmologue: return 100;
		break;
	case Medecin::Specialite::Autre:return 60;
		break;
	default:
		throw "La spécialite du médecin n'est pas définie";
	}

}


//Utiliser Switch
//Cette méthode retourne le prix de la consultation qui dépend de la spécialité du médecin.
//prix = 100 pour Gynecologue et Ophtalmologue
//prix = 120 pour Cardiologue et Dermatologue
//prix = 80 pour Pediatre
//prix = 60 pour Generaliste ou Autre
//default : throw "La spécialite du médecin n'est pas définie"






//! Méthode qui retourne le status du medecin
//! \return le status du medecin
bool Medecin::getEstActif() const
{

	return estActif_;
}
size_t Medecin::getNombreConsultations() const
{
	return nombreConsultations_;
}
//! Méthode qui retourne la specialite du medecin
//! \return la specialite des medecins
const Medecin::Specialite Medecin::getSpecialite() const
{

	return specialite_;
}

//! Méthode qui retourne le nombre de patients associés
//! \return le nombre de patients associés
const size_t Medecin::getNombrePatientsAssocies() const
{

	return patientsAssocies_.size();
}


//! Méthode qui retourne la liste des patients associes au medecin
//! \return la liste des patients
const std::vector<Patient*>& Medecin::getPatientsAssocies() const
{
	return patientsAssocies_;
}


//! Méthode qui met a jours le statut  du medecin si il est actif ou non
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


//! Méthode  qui permet de trouver l'index un medecin dans la liste des medecins
//! \param numeroLicence   numero de licence du medecin
//! \return             int bool qui indique l'index du medecin et MEDECIN_INEXSISTANT si le medecin est inexistant
int Medecin::trouverIndexPatient(const std::string& numeroAssuranceMaladie)
{
	for (std::size_t i = 0; i < patientsAssocies_.size(); i++)
	{
		if (*patientsAssocies_[i] == numeroAssuranceMaladie)
		{
			return static_cast<int>(i);
		}
	}
	return PATIENT_INEXSISTANT;
}
