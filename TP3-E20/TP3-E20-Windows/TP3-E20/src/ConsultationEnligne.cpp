//TODO : Entête du ficher



#include"consultationEnligne.h"
#include"patientEtudiant.h"
// TODO : Constructeur par paramètre



ConsultationEnligne::ConsultationEnligne(Medecin& medecin, Patient& patient, const std::string& date) :
    Consultation(medecin, patient, date)
    , diagnostique_(" ")
    , rabaisConsultationEnligne_(RABAIS_EN_LIGNE)
{}

//   void afficher(std::ostream& os) const;

   // TODO calculerPrix méthode virtuelle pure qui retourne le prix de la consultation. A ne pas implémenter

const double ConsultationEnligne::calculerPrix() const
{
    double rabais = medecin_->getPrixConsultation();    // car ecrire ceci est un peu trop long et difficile a comprendre :
   // return medecin_->getPrixConsultation() * (1 - getRabaisConsultationEnLigne()) * 1 - (dynamic_cast<PatientEtudiant*>(patient_)->getTauxRabais());
    if (dynamic_cast<PatientEtudiant*>(patient_))
    {
        // si le patient est un patient etudiant :
           //-- on cree un patientEtudiant* par dynamic-cast
        auto PatientEtudiantTest = dynamic_cast<PatientEtudiant*>(patient_);
        //--on appplique son rabais
        rabais *= (1 - PatientEtudiantTest->getTauxRabais());
        //--on applique le rabis de la consultation en ligne
        rabais *= (1 - getRabaisConsultationEnligne());
    }
    else {
        rabais *= (1 - getRabaisConsultationEnligne()); // on applique juste le rabais de la consultation en ligne;
    }
    return rabais;
}


const std::string& ConsultationEnligne::getDiagnostique() const
{
    return diagnostique_;
}
double ConsultationEnligne::getRabaisConsultationEnligne() const
{
    return rabaisConsultationEnligne_;
}

void ConsultationEnligne::setDiagnostique(const std::string& diagnostique)
{
    diagnostique_ = diagnostique;
}
void ConsultationEnligne::setRabaisConsultationEnligne(double rabais)
{
    rabaisConsultationEnligne_ = rabais;
}

//TODO : const double calculerPrix() const
// Chercher le prix de la consultation du médecin
// Vérifier si le patient est un patient étudiant (Convesion dynamique)
// Si le patient est patient étudiant, appliquer  le rabais étudiant
// Appliquer encore le rabais de la consultation enligne
// retourner le prix de la consultaion


// TODO : des getters et des setters si nécessaire
