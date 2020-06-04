/*/////////////////////////////////////////////////////////////////////////////
/	TP3 : fichier Hopital.cpp                                                 /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 07 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe Hopital                       /
*//////////////////////////////////////////////////////////////////////////////
#include "Hopital.h"

//! Constructeur par paramètre  de la classe Hopital
//! \param nom      Nom de l'hopital
//! \param adresse  Adresse de l'hopital
Hopital::Hopital(const std::string& nom, const std::string& adresse) :nom_(nom), adresse_(adresse)
{
}

//! Methode pour charger la base de donnees de l'hopital
//! \param nomFichierMedecins  le nom du fichier qui contient les informations des medecins
//! \param adresse  nomFichierPatients le nom du fichier qui contient les informations des patients
bool Hopital::chargerBaseDeDonnees(const std::string& nomFichierMedecins, const std::string& nomFichierPatients)
{
	return gestionnairePersonnels_.chargerDepuisFichier(nomFichierMedecins)
		&& gestionnairePatients_.chargerDepuisFichier(nomFichierPatients);
}

//! Operateur qui ajoute une consultation à un hopital
//! \param consultation à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Consultation& consultation)
{
	
	Medecin* medecin = dynamic_cast<Medecin*>( gestionnairePersonnels_.chercherPersonnel(consultation.getMedecin()->getId()));
	if (medecin && medecin->getEstActif())  // si le medecin existe et il est actif
	{
		if (!gestionnairePatients_.chercherPatient(consultation.getPatient()->getNumeroAssuranceMaladie())) // retourne un pointeur de patient*
			return false;  // si le patient n'existe pas
		else {
			if (dynamic_cast<ConsultationEnligne*>(const_cast<Consultation*>(&consultation)))  //  si le patient existe et que la consultation est en ligne
				consultations_.push_back(std::make_shared<ConsultationEnligne>(*dynamic_cast<ConsultationEnligne*>(const_cast<Consultation*>(&consultation))));
			
			if (dynamic_cast<ConsultationPhysique*>(const_cast<Consultation*>(&consultation))) // si le patient existe et que la consultation est physique
				consultations_.push_back(std::make_shared<ConsultationPhysique>(*dynamic_cast<ConsultationPhysique*>(const_cast<Consultation*>(&consultation))));

		}
		
		*medecin += consultation.getPatient();    // pas bien compris pk le fait d ajouter l etoile a enleve l erreure.
		medecin->incrementNombreConsultations(); 
	}
}

//! Operateur qui ajoute un médecin à un hopital
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Medecin& medecin)
{
	auto medecinTest = std::make_shared<Medecin>(medecin);
	return gestionnairePersonnels_ +=medecinTest.get();
}

//! Operateur qui ajoute un patient à un hopital
//! \param patient Le patient à ajouter
//! \return       Un bool qui indique si l'opération a bien fonctionnée
bool Hopital::operator+=(const Patient& patient)
{
	auto patientTest = std::make_shared<Patient>(patient);
	return gestionnairePatients_ += patientTest.get();
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
//! \return consultations_
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

