/* ////////////////////////////////////////////////////////////////////////////
/	TP3 : fichier ConsultationEnligne.cpp                                     /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 07 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe ConsultationEnligne           /
*//////////////////////////////////////////////////////////////////////////////
#include"ConsultationEnligne.h"
#include"PatientEtudiant.h"


//! Constructeur par paramètres de la classe ConsultationEnligne
//! \param medecin Le medecin responsable de la consultation
//! \param patient Le patient qui demande une consultation
//! \param date    La date de la consultation

ConsultationEnligne::ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date) :
    Consultation(medecin, patient, date)
    , diagnostique_(" ")
    , rabaisConsultationEnligne_(RABAIS_EN_LIGNE)
{}

//! Méthode qui permet de modifier la prescription de la consultation en ligne du patient
//! return rabais le prix de la consultation en ligne
const double ConsultationEnligne::calculerPrix() const
{
    double PrixConsultation = medecin_->getPrixConsultation();    // car ecrire ceci est un peu trop long et difficile a comprendre :
   // return medecin_->getPrixConsultation() * (1 - getRabaisConsultationEnLigne()) * 1 - (dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais());
    if (dynamic_cast<PatientEtudiant*>(patient_))
    {
        // si le patient est un patient etudiant :
           //-- on cree un patientEtudiant* par dynamic-cast
        auto PatientEtudiantTest = dynamic_cast<PatientEtudiant*>(patient_);
        //--on appplique son rabais
        PrixConsultation *= (1 - PatientEtudiantTest->getTauxRabais());
        //--on applique le rabis de la consultation en ligne
        PrixConsultation *= (1 - getRabaisConsultationEnligne());
    }
    else {
        PrixConsultation *= (1 - getRabaisConsultationEnligne()); // on applique juste le rabais de la consultation en ligne;
    }
    return PrixConsultation;
}

//! Méthode qui permet d'obtenir le diagnostique de la consultation en ligne du patient
//! return diagnostique_ diagnostique de la consultation 

const std::string& ConsultationEnligne::getDiagnostique() const
{
    return diagnostique_;
}

//! Méthode qui permet d'obtenir le rabais de la consultation en ligne du patient
//! return rabaisConsultationEnligne_ le rabais de la consultation en ligne 

double ConsultationEnligne::getRabaisConsultationEnligne() const
{
    return rabaisConsultationEnligne_;
}
//! Méthode qui permet de modifier la prescription de la consultation en ligne du patient
//! param disgnostique le nouveau diagnostique à attribuer à diagnostique_
void ConsultationEnligne::setDiagnostique(const std::string& diagnostique)
{
    diagnostique_ = diagnostique;
}
//! Méthode qui permet de modifier le rabais de la consultation en ligne du patient
//! param rabais le nouveau rabais à attribuer à rabaisConsultationEnligne_
void ConsultationEnligne::setRabaisConsultationEnligne(double rabais)
{
    rabaisConsultationEnligne_ = rabais;
}

