#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <string>

class Etudiant
{
public:
    Etudiant() = default;
    Etudiant(const std::string& nom, const std::string& dateDeNaissance, const std::string& matricule, const std::string& etablissement);

    //TODO : méthode virtuelle pure.
    void afficher(std::ostream& stream) const;

    const std::string& getNom() const;
    const std::string& getMatricule() const;
    const std::string& getDateDeNaissance() const;
    const std::string& getEtablissement() const;

    void setNom(const std::string& nom);
    void setMatricule(const std::string& numeroAssuranceMaladie);
    void setDateDeNaissance(const std::string& dateDeNaissance);
    void setEtablissement(const std::string& etablissement);


   
//TODO : les classes dérivées de cette classe ne doivent avoir accès qu'à l'attribut etablissement_.
private:
    std::string etablissement_;
    std::string nom_;
    std::string matricule_;
    std::string dateDeNaissance_;
};

#endif // ETUDIANT_H