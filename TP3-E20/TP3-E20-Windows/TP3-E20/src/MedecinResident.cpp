// TODO: Faire l'entête de fichier

#include <iostream>
#include <string>
#include"medecinResident.h"

// TODO: //Un constructeur par paramètre pour intialiser les attributs en faisant appel au constructeur des classes Etudiant et Medecin
MedecinResident::MedecinResident(const std::string& nom, const std::string& dateNaissance, const std::string& matricule, const std::string& ecole, const std::string& id, Specialite specialite)

	:Etudiant(nom, dateNaissance, matricule, ecole), Medecin(nom, id, specialite)
{

}
void MedecinResident::afficher(std::ostream& stream) const {
	Medecin::afficher(stream);
	stream << "\n\t";
	Etudiant::afficher(stream);

}
// TODO : Méthode afficher
// 1- Afficher les informations liées à la classe Medecin
// 2- Afficher "\n\t"
// 3- // 1- Afficher les informations liées à la classe Etudiant


// TODO : Méthode getSalaireAnnuel
// Retourner le Salaire annuel qui est:  salaire de base du médecin résidant + nombre de consultations * le prix de consultation du médecin

double MedecinResident::getSalaireAnnuel() const
{
	return(SALAIRE_DE_BASE_MEDECIN_RESIDENT + (nombreConsultations_ * getPrixConsultation()));
}