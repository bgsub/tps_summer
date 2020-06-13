#ifndef HOPITAL_H
#define HOPITAL_H

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include "Consultation.h"
#include "ConsultationPhysique.h"
#include "ConsultationEnligne.h"
#include "GestionnairePersonnels.h"
#include "GestionnairePatients.h"
#include "Foncteurs.h"
#include "utils.h"

class Hopital
{
public:
    enum class TypeConsultation
    {
        first_ = -1,
        ConsultationEnLigne,
        ConsultationPhysique,
        last_
    };

    Hopital() = default;
    Hopital(const std::string& nom, const std::string& adresse);

    bool chargerBaseDeDonnees(const std::string& nomFichierPersonnels, const std::string& nomFichierPatients, const std::string& nomFichierConsultations);
    bool chargerDepuisFichierConsultation(const std::string& nomFichiers);
    double getAncienneteMoyenneDesPersonnels() const;
    std::vector <std::shared_ptr<Consultation>>getConsultationsEntreDates(const tm& date1, const tm& date2) const;

    template <typename T>
    bool ajouterConsultation (T& consultation);

    //  Methode ajouterPersonnel
    //! param: personnel     une référence vers l'objet à ajouter
    //! return               un bool qui indique si l'objet a ete ajoute
    template <typename T>
    bool ajouterPersonnel(T& personnel)
    {
        return gestionnairePersonnels_.ajouterPersonnel<T>(personnel);
    }
    //  Methode ajouterPatient
    //! param: patient      une référence vers l'objet à ajouter
    //! return              un bool qui indique si l'objet a ete ajoute
    template <typename T>
    bool ajouterPatient( T& patient)
    {
        return gestionnairePatients_.ajouterPatient<T>(patient);
    }

    const std::string& getNom() const;
    const std::string& getAdresse() const;
    GestionnairePersonnels& getGestionnairePersonnels();
    GestionnairePatients& getGestionnairePatients();
    const std::vector<std::shared_ptr<Consultation>>& getConsultations() const;

    void setNom(const std::string& nom);
    void setAdresse(const std::string& adresse);

private:
    bool lireLigneConsultation(const std::string& ligne);

    std::string nom_;
    std::string adresse_;

    GestionnairePersonnels gestionnairePersonnels_;
    GestionnairePatients gestionnairePatients_;
    std::vector<std::shared_ptr<Consultation>> consultations_;
};

#endif // HOPITAL_H
