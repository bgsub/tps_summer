#ifndef PATIENTETUDIAT_H
#define PATIENTETUDIAT_H

#include "Patient.h"
#include "Etudiant.h"

//TODO : Classe qui hérite de la classe Etudiant et la classe Patient
class PatientEtudiant :
{
public:
	PatientEtudiant() = default;
	
	//TODO : Constructeur par paramètre. Il utilise le constructeur de la classe Etudiant et la classe Patient

	//TODO : surcharge de la méthode afficher

	//TODO : des getters et des setters si nécessaire.

	const double TAUX_RABAIS = 0.2;

private:
	double tauxRabais_;
};

#endif // PATIENTETUDIAT_H