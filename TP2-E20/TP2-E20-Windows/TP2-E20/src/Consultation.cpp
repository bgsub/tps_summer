/* ////////////////////////////////////////////////////////////////////////////
/	TD2 : fichier Consultation.cpp                                            /
/	travail fait par Bryan junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise : 24 mai 2020 à 23h55                                      /
/   Description: Implementation de la classe Consultation                     /
*//////////////////////////////////////////////////////////////////////////////

#include "Consultation.h"
#include <iostream>
#include <string>

//! constructeur de la classe Consultations
//! ajoute un patient dans la liste de patients associes au medecin
Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date):medecin_(new Medecin (medecin)), patient_(new Patient(patient)),date_(date)

{
	if (medecin.chercherPatient(patient.getNumeroAssuranceMaladie()));
	{
		medecin += patient;
	}
}



//! methode d affichage des consultations 
//! grace a la surcharge de l operatuer <<
// \return un stream
std::ostream& operator<<(std::ostream& stream, const Consultation& consultation)
{
	stream << "Consultation:" << "\n\tMedecin: " << consultation.medecin_->getNom()  << "\n\t" <<*consultation.patient_ << "\n\tDate de consultation: " << consultation.date_;
	stream << '\n';
	return stream;
}

//! Méthode qui retourne le médecin de la consultation
//! \return Medecin*
Medecin* Consultation::getMedecin() const
{
	return medecin_;
}

//! Méthode qui retourne le patient de la consultation
//! \return Patient*
Patient* Consultation::getPatient() const
{
	return patient_;
}

//! Méthode qui retourne lea date de la consultation
//! \return const std::string
const std::string& Consultation::getDate() const
{
	return date_;
}
