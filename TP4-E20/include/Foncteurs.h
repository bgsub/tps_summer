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


// TODO : Foncteur ComparateurSecondElementPaire
// Foncteur pr�dicat binaire comparant les seconds �l�ments de paires pour d�terminer si elles sont en ordre.
// Le foncteur est une classe g�n�rique.
// Le template de classe prend deux param�tres, soit les types T1 et T2 tenus par une paire std::pair<T1, T2>.
// L�op�rateur() doit prendre en param�tre deux r�f�rences constantes vers des paires dont les �l�ments sont de type T1 et T2.
// Il retourne true si le second �l�ment de la premi�re paire est strictement inf�rieur au second �l�ment de la deuxi�me paire, false sinon.
template <typename T1, typename T2>
class  ComparateurSecondElementPaire
{
public:

	/*dois je faire un constructeur ou pas ?
	ils le font dans le moodle mais pas dans les exemples sur internet */
	//rep : ca dpend des parametres.


	////// souvent il y a un constructeur par copie souvent non, je vais t explique quand il faut ou pas en mettre en appel video quand on va en faire

	//ComparateurSecondElementPaire(std::pair<T1, T2> pair1, std::pair<T1, T2> pair2);
	bool operator() (const std::pair<T1, T2>& pair1, const  std::pair<T1, T2>& pair2)
	{
		return(pair1.second < pair2.second);
	}
	/// ici c est le coeur du foncteur , je vais aussi t explique si t as pas compris comment ca fonctionne en appel video,




	/// t as des questions ? 
};

   /////// ici c est un foncteur qui compare qlq chose 





// TODO : Foncteur ComparateurEstEgalAvecId
// Foncteur pr�dicat unaire servant � comparer un objet(Patient ou Personnel) avec un id de type string.
// Le foncteur est une classe g�n�rique.
// Le template de classe prend un seul param�tre de type T.
// L�op�rateur() doit prendre en param�tre un pointeur shared_ptr tenant un �l�ment de type T.Il retourne true si l�objet �gale � l�id et false si non.


template<typename T> 
class ComparateurEstEgalAvecId
{
public :
	ComparateurEstEgalAvecId(const std::string& id) : id_(id) {}

	bool operator()(std::shared_ptr<T> elem)
	{
		return(elem == id_);
	}
private:
	std::string id_;



////    Les foncteurs ne sont pas des classe et n appartiennent pas au sens propre à une classe : c est juste des fonction qui agissent comme des operations







};
// TODO : Foncteur AccumulateurPeriodePersonnel
// Foncteur qui se charge de l'ajout de la p�riode pass�e par les personnels � l'h�pital � une somme.
// L�op�rateur() prend 3  param�tres :        //////  je crois qu ici ils voulaient dire 2
//      somme de type double 
//      pair de type pair de string et shared_ptr de Personnel
//      Il retourne la somme du param�tre somme et  de l�anciennet� du personnel pass� en param�tre.
// Indice : utiliser les fonctions getDateCourante et getDateAdhesion pour calculer l�anciennet� en prenant en compte juste les ann�es.

class  AccumulateurPeriodePersonnel
{
public:
	AccumulateurPeriodePersonnel(double sum, std::shared_ptr<Personnel> pers) : sum_(sum), pers_(pers) {}
	double  operator()(double somme, const std::shared_ptr<Personnel>& pers)
	{
		//je vais continuer apres avoir fait Personnel
		//double anciennete =  pers->
	}

private:
	double sum_;
	std::shared_ptr<Personnel> pers_;
};

// TODO : Foncteur ComparateurTypePatient
// Foncteur pr�dicat unaire servant � comparer un objet de type Patient � n�importe quel autre objet.
// Le foncteur est une classe g�n�rique.
// Le template de classe prend un seul param�tre de type T.
// L�op�rateur() doit prendre en param�tre un pointeur shared_ptr tenant un �l�ment de type Patient
// Il retourne true si l�objet est de type Patient et false si non. Hint : conversion dynamique
template <typename T>
class  ComparateurTypePatient
{
public:
	//ComparateurTypePatient(T objet) : objet_(objet) {}
	bool operator()(std::shared_ptr<Patient> patient)
	{
		return (dynamic_cast<T*>( patient.get()));
	}
private :
	T objet_;

};

// TODO : EstDansIntervalleDatesConsultation
// Foncteur pr�dicat unaire servant � d�terminer si une consultation est r�alis�e entre deux dates.
// Constructeur par param�tres initalisant l'intervalle de dates. Il prend deux r�f�rences constantes vers deux objets de type tm.
// L�op�rateur() une r�f�rence constante vers un shared_ptr de Consultation.
// Utiliser les deux fonctions d�finis dans utils.h convertirStringDate pour convertir une date de sting vers tm et comparerDate pour comparer deux dates.
class EstDansIntervalleDatesConsultation {
	EstDansIntervalleDatesConsultation(const tm& date1, const tm& date2) : date1_(date1), date2_(date2) {}
	bool operator ()(const std::shared_ptr<Consultation>& cons)
	{
		tm dateConsultation = convertirStringDate(cons->getDate());
		if (comparerDate(dateConsultation, date1_) == true && comparerDate(date2_, dateConsultation) == true)
		{
			return true;
		}
		else return false;

		       //! juste pour savoir si cette ligne de code passe pareil
	//	return (comparerDate(dateConsultation, date1_) && comparerDate(date2_, dateConsultation));;
	}
private:
	tm date1_;
	tm date2_;

};




#endif // FONCTEURS_H
