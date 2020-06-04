/* ////////////////////////////////////////////////////////////////////////////
/	TP3 : fichier MedecinResident.cpp                                         /
/	travail fait par Bryan Junior Ngatshou                     : 1956611      /
/	                 Alexandra Johanne Bifona Africa		   : 1955711      /
/                                                                             /
/	Date de remise: 07 juin 2020 à 23h55                                      /
/   Description   : Implementation de la classe MedecinResident               /
*//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include"MedecinResident.h"

//! Constructeur par paramètre  de la classe MedecinResident
//! \ param nom Nom du patient
//! \ param dateDeNaissance La date de naissance de l etudiant 
//! \ param matricule Matricule de l etudiant 
//! \ param ecole Nom de l etablissement de l etudiant
//! \ param id L id du medecin 
//! \ param specialite La specialite du medecin

MedecinResident::MedecinResident(const std::string& nom, const std::string& dateNaissance, const std::string& matricule, const std::string& ecole, const std::string& id, Specialite specialite)

	:Etudiant(nom,dateNaissance,matricule,ecole),Medecin(nom,id,specialite)
{

}
//! Méthode qui affiche les informations d'un médécin résident
//! param une  ostream stream

void MedecinResident:: afficher(std::ostream& stream) const {
	Medecin::afficher(stream);
	stream << "\n\t";
	Etudiant::afficher(stream);
	
}


//! Méthode qui donne le salaire annuel d'un médécin résident
//! return le salaire annuel du médecin résident (un double)

double MedecinResident:: getSalaireAnnuel() const
{
	return(SALAIRE_DE_BASE_MEDECIN_RESIDENT + (nombreConsultations_ * getPrixConsultation()));
}