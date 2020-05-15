// TODO: Faire l'entête de fichier

// TODO: Inclure la définition de la classe appropriée
#include <fstream>
#include <iomanip>
#include "typesafe_enum.h"
#include <iostream>
#include <sstream>
#include"GestionnaireMedecins.h"
constexpr size_t CAPACITE_MEDECINS_INITIALE = 2;
constexpr int MEDECIN_INEXSISTANT = -1;

// TODO : Constructeur par défaut en utilisant la liste d'initialisation
// Utilisez CAPACITE_MEDECINS_INITIALE pour la taille initiale de medecins_ (tableau de taille dynamique)
GestionnaireMedecins:: GestionnaireMedecins():nbMedecins_(0),capaciteMedecins_(CAPACITE_MEDECINS_INITIALE),
medecins_(std::make_unique<std::shared_ptr<Medecin>[]> (CAPACITE_MEDECINS_INITIALE)){}




//! Méthode qui ajoute un médecin à la liste des patients
//! \param medecin Le medecin à ajouter
void GestionnaireMedecins::ajouterMedecin(std::shared_ptr<Medecin> medecin)
{
	constexpr unsigned int AUGMENTATION_NOMBRE_MEDECINS = 2;
	// TODO
	// Verifier si assez de mémoire est allouée
	// Si pas assez de mémoire, doubler la taille du tableau (AUGMENTATION_NOMBRE_MEDECINS)
	// Ajouter le medecin au tableau
	// Utiliser std::unique_ptr<std::shared_ptr<Medecin>[]> ainsi que std::move pour transférer le ownership
	// du tableau temporaire vers le tableau membre medecins_;
	if (capaciteMedecins_ < (nbMedecins_ + 1))
	{
		capaciteMedecins_ *= AUGMENTATION_NOMBRE_MEDECINS;

		auto test = std::make_unique<std::shared_ptr<Medecin>[]>(capaciteMedecins_);
		// copier les anciens medecins avant de faire le move
		for (size_t i = 0; i < capaciteMedecins_ / AUGMENTATION_NOMBRE_MEDECINS; i++)
		{
			test[i] = medecins_[i];
		}
		medecins_ = std::move(test);
	}
	//auto test2 = std::make_shared<Medecin>(medecin);
	medecins_[nbMedecins_] = medecin;
	nbMedecins_++;

}
	

// TODO : compléter chercherMedecin(const std::string& numeroLicence)
// Chercher un medecin dans la liste medecins par son numéro de licence
// Retourner le pointeur vers le medecin si trouvé, sinon retourner nullptr

std::shared_ptr<Medecin> GestionnaireMedecins::chercherMedecin(const std::string& numeroLicence)
{
	for (size_t i = 0; i < nbMedecins_; i++)
	{
		if (medecins_[i].get()->getNumeroLicence()== numeroLicence) return medecins_[i];
		else return nullptr;
	}

}

//! Méthode  qui permet de charger les informations des medecins depuis un fichier
//! \param nomFichier   Le nom du fichier à charger
//! \return             Un bool qui indique si le fichier a été chargé avec succes
bool GestionnaireMedecins::chargerDepuisFichier(const std::string& nomFichier)
{
	std::ifstream fichier(nomFichier);
	if (fichier)
	{
		nbMedecins_ = 0;
		std::string ligne;
		while (std::getline(fichier, ligne))
		{
			if (!lireLigneMedecin(ligne))return false;

		}
		return true;
		std::cerr << "Le fichier " << nomFichier
			<< " n'existe pas. Assurez vous de le mettre au bon endroit.\n";
		return false;
	}
}

// TODO : compléter 
bool GestionnaireMedecins::supprimerMedecin(const std::string& numeroLicence)
{

	bool estActif = false;
	size_t i = trouverIndexMedecin(numeroLicence);
	if (i!=MEDECIN_INEXSISTANT)
	{
		medecins_[i].get()->setEstActif(estActif);
		return true;
	}
	else return false;
	
}

// Chercher l'index du medecin dans le tableau medecins_ en faisant appel à la fonction trouverIndexMedecin
// Rendez le medecin inactif. Attention : il ne fait pas retirer le medecin du tableau medecins_
// Retourner true si le medein est trouvé et rendu inactif, sinon retourné false

// TODO : afficher(std::ostream& stream)
void GestionnaireMedecins::afficher(std::ostream& stream)
{
	for (size_t i = 0; i < nbMedecins_; i++) {
		medecins_[i].get()->afficher(stream);
	}
	stream << '\n';
}

// Afficher tous les medecins contenus dans le tableau medecins_ en utilisant le stream

// TODO : getNbMedecins() : retourner nbMedecins_
size_t GestionnaireMedecins::getNbMedecins()
{
	return nbMedecins_;
}
// TODO : getCapaciteMedecins() : retourner capaciteMedecins_
size_t GestionnaireMedecins:: getCapaciteMedecins()
{
	return capaciteMedecins_;
}
//! Méthode qui lit les attributs d'un medecin
//! \param ligne  Le string qui contient les attributs
bool GestionnaireMedecins::lireLigneMedecin(const std::string& ligne)
{
	std::istringstream stream(ligne);
	std::string nomMedecin;
	std::string numeroLicence;
	int indexSpecialite;
	if (nbMedecins_ < capaciteMedecins_)
	{
		stream >> std::quoted(nomMedecin) >> std::quoted(numeroLicence) >> indexSpecialite;
		//Medecin medecin = Medecin(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite));
		auto test = std::make_shared<Medecin>(Medecin(nomMedecin, numeroLicence, to_enum<Medecin::Specialite, int>(indexSpecialite)));
		ajouterMedecin(test);
		return true;
	}

	else return false;

	
	
}

// TODO : 

int GestionnaireMedecins::trouverIndexMedecin(const std::string& numeroLicence)
{
	for (size_t i = 0; i < nbMedecins_; i++)
	{
		if (medecins_[i].get()->getNumeroLicence() == numeroLicence) return i;
		else return MEDECIN_INEXSISTANT;
	}

}

// Retourner l'indexe du medecin comportant le numéro de licence envoyé en paramètre
// Si le medecin n'existe pas, retourner -1 (MEDECIN_INEXSISTANT)

