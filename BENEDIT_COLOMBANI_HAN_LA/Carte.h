#ifndef CARTE_H_INCLUDED
#define CARTE_H_INCLUDED

class Carte
{
private :
    ///liste des sommets (vecteur de pointeurs sur Sommet)

    std::vector<Aeroport*> m_aeroport;
    std::vector<Avion*> m_avions;
    std::vector<int> m_nb_arete;
    std::map <string, BITMAP*> m_bitmap;
    Trajet *m_trajet;

    ///nb sommets
    int m_ordre;
    int m_ordre1;
    ///nb arretes
    int m_taille;


public :

    ///Constructeur///
    Carte(std::string nomFichier, std::string nomFichier2);

    /*destructeur*/
    ~Carte()
    {
        for (auto s : m_aeroport)
            delete s;
        for (auto c: m_avions)
            delete c;
    }

    ///Ascesseur///
    int get_ordre();
    int get_ordre1();
    std::vector<Avion*> getAvion();
    Avion* getAvion_i(int i);
    std::vector<Aeroport*> getSo()const;
    Aeroport* getSo_i(int i)const;

    /*méthode d'affichage*/
    void afficher() const;
    void init_allegro();
    void ini_bitmap();
    void add_bitmap(BITMAP* tmp, std::string s);
    BITMAP* get_bitmapp(std::string c);
    void aff_bit(int i,BITMAP*buffer);
    void aff_map();

    std::vector <int> Dijkstra(int num,int num2,int num3,std::vector<int>&poids,std::vector<Avion*> a,int* condition) const;
    void parcours(std::vector<int>&poids,std::vector<int>&previous,int num,std::vector<Avion*> a,int num3,std::vector<int> nbb,int* condition) const;
    void aff_trajet(std::vector<int> nbr_sommet,std::vector<std::vector <int>> sommets,std::vector<int> avion_num);

    std::vector <int> Dijkstra2(int num,int num2,int num3,std::vector<int>&poids,std::vector<Avion*> a,int* condition) const;
    void parcours2(std::vector<int>&poids,std::vector<int>&previous,int num,std::vector<Avion*> a,int num3,std::vector<int> nbb,int* condition) const;
};



#endif // CARTE_H_INCLUDED
