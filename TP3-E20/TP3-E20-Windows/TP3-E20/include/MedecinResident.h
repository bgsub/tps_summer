#ifndef MEDECINRESIDENT_H
#define MEDECINRESIDENT_H

#include <string>
#include"medecin.h"
#include"etudiant.h"
class MedecinResident : public Medecin, Etudiant
{
public:
	MedecinResident(const std::string& nom, const std::string& dateNaissance, const std::string& matricule, const std::string& ecole, const std::string& id, Specialite specialite);
	void afficher(std::ostream& stream) const override;

	static constexpr size_t SALAIRE_DE_BASE_MEDECIN_RESIDENT = 50000;

	double getSalaireAnnuel() const override;
};

//TODO: 
//Cette classe hérite de la classe Etudiant et la classe Medecin
//Pas d'attributs spéciaux pour cette classe
//Un constructeur par paramètre pour intialiser les attributs en faisant appel au constructeur des classes Etudiant et Medecin
//Surchage de la méthode afficher
//Surchage de la méthode getSalaireAnnuel
//Un salaire de base comme constante static :   



#endif // MEDECINRESIDENT_H