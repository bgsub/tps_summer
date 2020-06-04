#ifndef MEDECINRESIDENT_H
#define MEDECINRESIDENT_H

#include <string>
#include"Medecin.h"
#include"Etudiant.h"
class MedecinResident: public Medecin,Etudiant
{
public:
	MedecinResident(const std::string& nom, const std::string& dateNaissance, const std::string& matricule, const std:: string&ecole, const std:: string& id, Specialite specialite);
     void afficher(std::ostream& stream) const override;
	  
	static constexpr size_t SALAIRE_DE_BASE_MEDECIN_RESIDENT = 50000;

	double getSalaireAnnuel() const override;
};



#endif // MEDECINRESIDENT_H