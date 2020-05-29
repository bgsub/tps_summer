//TODO Entête du fichier
#include "Etudiant.h"
#include <iostream>
#include <string>



//TODO le constructeur par paramètres. Utiliser la liste d'initialisation
Etudiant::Etudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablissement)
    : nom_(nom), dateDeNaissance_(dateDeNaissance), matricule_(matricule), etablissement_(etablissement) {}



//! Méthode qui affiche les informations de l'étudiant
//! \param os Le stream dans lequel afficher
std::ostream& Etudiant::afficher(std::ostream& stream) const
{
    stream << "Matricule: " << matricule_ << "\n\tEtablissement: " << etablissement_; //// je vois pas ce que je dois ajouter; est ce que je dois remplacer stream par cout??////
    return stream;
}



//TODO : getNom
const std::string& Etudiant::getNom() const { return nom_; }



//TODO : getMatricule
const std::string& Etudiant::getMatricule() const { return matricule_; }



//TODO : getEtablissement
const std::string& Etudiant::getEtablissement() const { return etablissement_; } ////// je me demande si c'est necessaire vu que c'est un attribut protege////



//TODO : getDateDeNaissance
const std::string& Etudiant::getDateDeNaissance() const { return dateDeNaissance_; }



//TODO : setNom
void Etudiant::setNom(const std::string& nom) { nom_ = nom; }



//TODO : setMatricule
void Etudiant::setMatricule(const std::string& numeroAssuranceMaladie) { matricule_ = numeroAssuranceMaladie; }



//TODO : setDateDeNaissance
void Etudiant::setDateDeNaissance(const std::string& dateDeNaissance) { dateDeNaissance_ = dateDeNaissance; }



//TODO : setEtablissement
void Etudiant::setEtablissement(const std::string& etablissement) { etablissement_ = etablissement; } ////// je me demande si c'est necessaire vu que c'est un attribut protege////
