// TODO : Entête du fichier
#include "PatientEtudiant.h"
#include <iostream>
#include <string>



//TODO : Constructeur par paramètre pour intialiser tous les attributs. Utiliser la liste d'initialisation
//Il utilise le constructeur de la classe Etudiant et la classe Patient
PatientEtudiant::PatientEtudiant(const std::string& nom, const std::string& dateNaissance, const std::string& numeroAssMal, const std::string& matricule, const std::string& etablissement)
    : Patient(nom, dateNaissance, numeroAssMal)
    , Etudiant(nom, dateNaissance, matricule, etablissement)
    , tauxRabais_(TAUX_RABAIS) {}
//TODO : surcharge de la méthode afficher
//Afficher les informations liées au patient
//Puis affichier " | "
//Puis afficher les informations liées à l'étudiant
//Puis afficher " | Taux de rabais: " suivi du tauxRabais_
std::ostream& PatientEtudiant::afficher(std::ostream& stream)  const {



    Patient::afficher(stream);
    stream << " | ";
    Etudiant::afficher(stream);
    stream << " | Taux de rabais: " << getTauxRabais();
    return stream;
}



//TODO : les getters et les setters si nécessaire
double PatientEtudiant::getTauxRabais() const { return tauxRabais_; }
void PatientEtudiant::setTauxRabais(double taux) { tauxRabais_ = taux; }