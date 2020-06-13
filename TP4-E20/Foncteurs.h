//TODO Ent�te du fichier

#ifndef FONCTEURS_H
#define FONCTEURS_H

#include <memory>
#include <utility>
#include "GestionnairePersonnels.h"
#include "Hopital.h"
#include "utils.h"
#include "GestionnairePatients.h"
//#include "Personnel.h"


// Foncteur (classe generique) predicat binaire comparant les seconds elements de paires pour determiner si elles sont en ordre.
// parametres de l'operateur():	pair1, pair2	deux references constantes vers des paires dont les elements sont de type T1 et T2.
// return de l'operateur():						un booleen qui indique si le second element de la premiere paire est strictement inferieur au second element de la deuxi�me paire
template <typename T1, typename T2>
class  ComparateurSecondElementPaire
{
public:

	bool operator() (const std::pair<T1, T2>& pair1, const  std::pair<T1, T2>& pair2)
	{
		return(pair1.second < pair2.second);
	}
};


// Foncteur (classe generique) predicat unaire servant a comparer un objet(Patient ou Personnel) avec un id de type string.
// parametr de l'operateur(): elem		un pointeur shared_ptr tenant un element de type T.
// return de l'operateur():				un bool qui indique si l'objet est egal a l'id 

template<typename T>
class ComparateurEstEgalAvecId
{
public:
	ComparateurEstEgalAvecId(const std::string& id) : id_(id) {}

	bool operator()(std::shared_ptr<T> elem)
	{
		return(*elem == id_);
	}
private:
	std::string id_;
};
// Foncteur qui se charge de l'ajout de la periode passee par les personnels a l'hopital a une somme.
// parametres de l'operateur(): somme	de type double 
//								pair	de type pair de string et shared_ptr de Personnel
// return de l'operateur()		la somme du parametre somme et  de l'anciennete du personnel passe en parametre.


class AccumulateurPeriodePersonnel {
public:
	//AccumulateurPeriodePersonnel(double somme) : somme_(somme) {}
	double operator()(double somme, std::pair<const std::string, std::shared_ptr<Personnel>> pair) {
		tm temps1 = getDateCourante();
		tm temps2 = pair.second->getDateAdhesion();

		return somme + static_cast<double>(static_cast<double>(getDateCourante().tm_year) - static_cast<double>(pair.second->getDateAdhesion().tm_year));
		
	}
//private:
//	double somme_;
};

//Foncteur (classe generique) predicat unaire servant a comparer un objet de type Patient a n'importe quel autre objet.
// parametres de l'operateur():patient	un pointeur shared_ptr tenant un element de type Patient
// return								un booleen qui indique si l'objet est de type Patient 
template <typename T>
class  ComparateurTypePatient
{
public:
	//ComparateurTypePatient(T objet) : objet_(objet) {}
	bool operator()(std::shared_ptr<Patient> patient)
	{
		return (dynamic_cast<T*>(patient.get()));
	}
private:
	T objet_;

};

// Foncteur EstDansIntervalleDatesConsultation predicat unaire servant a determiner si une consultation est realisee entre deux dates.
// parametres de l'operateur(): cons	une reference constante vers un shared_ptr de Consultation.
// return								un booleen qui indique si la consultation est bien realisee entre les dates donnees. 
class EstDansIntervalleDatesConsultation {
public:
	EstDansIntervalleDatesConsultation(const tm& date1, const tm& date2) : date1_(date1), date2_(date2) {}
	bool operator ()(const std::shared_ptr<Consultation>& cons)
	{
		tm dateConsultation = convertirStringDate(cons->getDate());
		if (comparerDate(dateConsultation, date1_) == true && comparerDate(date2_, dateConsultation) == true)
		{
			return true;
		}
		else return false;
	}
private:
	tm date1_;
	tm date2_;

};




#endif // FONCTEURS_H
