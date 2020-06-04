/* ////////////////////////////////////////////////////////////////////////////
/	TP3 : fichier PatientEtudiant.cpp                                         /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 07 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe PatientEtudiant               /
*//////////////////////////////////////////////////////////////////////////////

#include "PatientEtudiant.h"
#include <iostream>
#include <string>


//! Constructeur par paramètre  de la classe PatientEtudiant
//! \param nom Nom du patient etudiant
//! \param dateDeNaissance La date de naissance du patient etudiant
//! \ param numerAssMal Numero d`assurance maladie du patient etudiant
//! \ param matricule Matricule du patient etudiant
//! \ param etablissement Nom de l`etablissement du patient etudiant

PatientEtudiant::PatientEtudiant(const std::string& nom, const std::string& dateNaissance, const std::string& numeroAssMal, const std::string& matricule, const std::string& etablissement)
    : Patient(nom,dateNaissance,numeroAssMal)
    , Etudiant(nom, dateNaissance, matricule,etablissement)
    , tauxRabais_(TAUX_RABAIS) {}   // initialisation de l'attribut tauxRabais_;


//! Méthode qui affiche les informations liées au patient
//! param un ostream stream
void PatientEtudiant::afficher(std::ostream& stream)  const  {



    Patient::afficher(stream);
    stream << " | ";
    Etudiant::afficher(stream);
    stream << " | Taux de rabais: " << getTauxRabais();
    
}



//! Méthode qui permet d'accéder à l'attribut tauxRabais_
//! return tauxRabaix_ le taux de rabais pour un patient étudiant
double PatientEtudiant::getTauxRabais() const { return tauxRabais_; }

//! Méthode qui permet de modifier l'attribut tauxRabais_
//! param taux la valeur du taux qu'on veut attribuer à l'attribut tauxRabais_
void PatientEtudiant::setTauxRabais(double taux) { tauxRabais_ = taux; }