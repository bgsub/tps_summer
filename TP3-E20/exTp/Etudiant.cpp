/*/////////////////////////////////////////////////////////////////////////////
/	TP3 : fichier Consultation.cpp                                            /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 07 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe Etudiant                      /
*//////////////////////////////////////////////////////////////////////////////
#include "Etudiant.h"
#include <iostream>
#include <string>


//! Constructeur par paramètre  de la classe MedecinResident
//! \ param nom Nom de l etudiant
//! \ param dateDeNaissance La date de naissance de l etudiant 
//! \ param matricule Matricule de l etudiant 
//! \ param etablissement Nom de l etablissement de l etudiant

Etudiant::Etudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablissement)
    : nom_(nom), dateDeNaissance_(dateDeNaissance), matricule_(matricule), etablissement_(etablissement) {}



//! Méthode qui affiche les informations de l'étudiant
//! \param os Le stream dans lequel afficher
void Etudiant::afficher(std::ostream& stream) const
{
    stream << "Matricule: " << matricule_ << "\n\tEtablissement: " << etablissement_; //// je vois pas ce que je dois ajouter; est ce que je dois remplacer stream par cout??////

}



//! Méthode qui permet d'obtenir le nom de l'étudiant
//! return nom_ le nom de l'tudiant (string)
const std::string& Etudiant::getNom() const { return nom_; }



//! Méthode qui permet d'obtenir le matricule de l'étudiant
//! return matricule_ le matricule de l'étudiant (string)
const std::string& Etudiant::getMatricule() const { return matricule_; }



//! Méthode qui permet d'obtenir le nom de l'établissement de l'étudiant
//! return etablissement_ nom de l'établissement de l'étudiant (string)
const std::string& Etudiant::getEtablissement() const { return etablissement_; } 



//! Méthode qui permet d'obtenir la date de naissance de l'étudiant
//! return dateDeNaissance_ la date de naissance de l'étudiant (string)
const std::string& Etudiant::getDateDeNaissance() const { return dateDeNaissance_; }



//! Méthode qui permet de modifier le nom de l'étudiant
//! param nom le nom de l'étudiant qu'on attribuer à l'attribut nom_
void Etudiant::setNom(const std::string& nom) { nom_ = nom; }



//! Méthode qui permet de modifier le matricule de l'étudiant
//! param numeroAssuranceMaladie le matricule de l'étudiant qu'on attribuer à l'attribut matricule_
void Etudiant::setMatricule(const std::string& numeroAssuranceMaladie) { matricule_ = numeroAssuranceMaladie; }



//! Méthode qui permet de modifier la date de naissance de l'étudiant
//! param dateDeNaissance la date de naissance de l'étudiant qu'on attribuer à l'attribut dateDeNaissance_
void Etudiant::setDateDeNaissance(const std::string& dateDeNaissance) { dateDeNaissance_ = dateDeNaissance; }



//! Méthode qui permet de modifier le nom de l'établissement de l'étudiant
//! param établissement le nom de l'établissement de l'étudiant qu'on attribuer à l'attribut etablissement_
void Etudiant::setEtablissement(const std::string& etablissement) { etablissement_ = etablissement; } ////// je me demande si c'est necessaire vu que c'est un attribut protege////
