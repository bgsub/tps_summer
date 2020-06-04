/* ////////////////////////////////////////////////////////////////////////////
/	TP3 : fichier ConsultationPhysique.cpp                                    /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 07 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe ConsultationPhysique          /
*//////////////////////////////////////////////////////////////////////////////

#include "ConsultationPhysique.h"
#include"PatientEtudiant.h"

//! Constructeur par paramètres de la classe ConsultationPhysique
//! \param medecin Le medecin responsable de la consultation
//! \param patient Le patient qui demande une consultation
//! \param date    La date de la consultation
ConsultationPhysique::ConsultationPhysique(Medecin& medecin, Patient& patient, const std::string& date) :
    Consultation(medecin, patient, date)
    , prescription_(" ")
{}

//! Méthode qui permet de calculer le prix de la consultation physique du patient
//! return rabais prix de la consultation physique du patient
const double ConsultationPhysique::calculerPrix() const
{
    double rabais = medecin_->getPrixConsultation();   
    // car ecrire ceci est un peu trop long et difficile a comprendre :
       // return medecin_->getPrixConsultation() * (1 - getRabaisConsultationEnLigne()) * 1 - (dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais());

    if (dynamic_cast<PatientEtudiant*>(patient_))
    {
        auto PatientEtudiantTest = dynamic_cast<PatientEtudiant*>(patient_);
        //--on appplique son rabais
        rabais *= (1 - PatientEtudiantTest->getTauxRabais());
    }
    return rabais;
}

//! Méthode qui permet d'obtenir la prescription de la consultation physique du patient
//! return prescription_ prescription d'une consultation physique

const std::string& ConsultationPhysique::getPrescription() const
{
    return prescription_;
}

//! Méthode qui permet de modifier la prescription de la consultation physique du patient
//! param prescription nouvelle prescription de la consultation 
void ConsultationPhysique::setPrescription(const std::string& prescription)
{
    prescription_ = prescription;
}

