//TODO Entête du fichier
#include "Etudiant.h"
#include <iostream>
#include <string>

//TODO le constructeur par paramètres. Utiliser la liste d'initialisation

//! Méthode qui affiche les informations de l'étudiant
//! \param os Le stream dans lequel afficher
void Etudiant::afficher(std::ostream& stream) const
{
	stream << "Matricule: " << matricule_ << "\n\tEtablissement: " << etablissement_;
}

//TODO : getNom

//TODO : getMatricule

//TODO : getEtablissement

//TODO : getDateDeNaissance

//TODO : setNom

//TODO : setMatricule

//TODO : setDateDeNaissance

//TODO : setEtablissement