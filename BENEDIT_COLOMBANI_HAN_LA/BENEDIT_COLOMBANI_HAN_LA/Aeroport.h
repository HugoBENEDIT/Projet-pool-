#ifndef AEROPORT_H_INCLUDED
#define AEROPORT_H_INCLUDED

class Aeroport
{
private:
    int m_nom;
    std::string m_prenom;
    int m_x;
    int m_y;
    int m_nb_piste;
    int m_nb_places_sol;
    int m_delai_attente_sol;
    int m_temps_acces_pistes;
    int m_delai_anticollision;
    int m_temps_DECAT;
    int m_duree_boucle;
    int m_marque = -1;
    int m_p = -1;
    std::map<const Aeroport*, int> m_distance1;
    std::vector<std::pair<const Aeroport*, int>>m_distance;

public:
    ///Constructeur
    Aeroport(int nom, std::string prenom, int x, int y, int pistes, int places, int delai, int temps, int anticollision, int decat, int duree):m_nom(nom),m_prenom(prenom), m_x(x), m_y(y), m_nb_piste(pistes), m_nb_places_sol(places), m_delai_attente_sol(delai), m_temps_acces_pistes(temps), m_delai_anticollision(anticollision), m_temps_DECAT(decat), m_duree_boucle(duree) {};

    ///Accesseur///
    int get_nom() const;
    std::string get_prenom() const;
    int get_x () const;
    int get_y () const;
    int get_pistes() const;
    int get_places() const;
    int get_delai() const;
    int get_temps() const;
    int get_anticollision() const;
    int get_decat() const;
    int get_duree() const;
    const std::vector<std::pair<const Aeroport*, int>>& getSuccesseurs()const;
    int getSuccesseurs_nom(int nom);
    void ajouterSucc(const Aeroport*s, int m_p);
    void setMarque(int marque);
    int getMarque() const;
    void setP(int p);
    int getP() const;

    ///Méthodes///
    void aff();
};


#endif // AEROPORT_H_INCLUDED

