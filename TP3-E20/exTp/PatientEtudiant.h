#ifndef PATIENTETUDIAT_H
#define PATIENTETUDIAT_H



#include "Patient.h"
#include "Etudiant.h"



// Classe qui hérite de la classe Etudiant et la classe Patient
class PatientEtudiant : public Patient, Etudiant           // un patientEtudiant est un patient avant d etre un etudiant. (polymorphisme) 
{
public:
    PatientEtudiant() = default;
    // Constructeur par paramètre. Il utilise le constructeur de la classe Etudiant et la classe Patient
    PatientEtudiant(const std::string& nom, const std::string& dateNaissance, const std::string& numeroAssMal, const std::string& matricule, const std::string& etablissement);
    // Surcharge de la méthode afficher
   void afficher(std::ostream& stream) const  override ;
    // Des getters et des setters si nécessaire.
    double getTauxRabais() const;
   void setTauxRabais(double taux);
    const double TAUX_RABAIS = 0.2;
private:
    double tauxRabais_;
};



#endif // PATIENTETUDIAT_HIAT_H