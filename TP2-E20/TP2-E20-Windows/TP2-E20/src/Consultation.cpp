// TODO: Faire l'entête de fichier

#include "Consultation.h"
#include <iostream>
#include <string>

// TODO : compléter Constructeur par paramètre de la classe Consulation en utilisant la liste d'initialisation
// Assurer d'ajouter le patient à la liste des patients assoicés au medecin s'il n'y existe pas.
Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date):medecin_(new Medecin(medecin)),patient_(new Patient (patient)),date_(date)

{
	
	 Patient* patientTest = medecin.chercherPatient(patient.getNumeroAssuranceMaladie());
	if (patientTest == nullptr)
	{
		
	}
	
}
//Consultation::Consultation(Medecin& medecin, Patient& patient, const std::string& date)
//    :date_(date) {
//    medecin_ = new Medecin(medecin);
//    patient_=new Patient(patient)
//    for (size_t i = 0; i < medecin.getPatientsAssocies().size(); i++) {
//        if (medecin.getPatientsAssocies()[i] == patient_)
//            break;
//
//    }
//         
//      medecin.getPatientsAssocies()[medecin.getPatientsAssocies().size()] = patient_;
//        
//}


// TODO : operateur<< pour afficher les informations d'une consultation.
// Voir l'enoncé pour avoir un exemple d'affichage d'une consultation. 
// Si l'affichage n'est pas respecté, le test de l'affichage de consultation ne passera pas.

std::ostream& operator<<(std::ostream& out, const Consultation& consultation)
{
	out << "Consultation:" << "\n\tMedecin: " << consultation.medecin_->getNom()  << *consultation.patient_ << "\n\tDate de consultation: " << consultation.date_;
	out << '\n';
	return out;
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
