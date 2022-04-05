#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <map>
#include <vector>
#include <fstream>


using namespace std;

class Avion
{
private :
    string m_type;
    int m_conso;
    int m_capacite;

public :
    /*constructeur*/
    Avion(string type, int conso, int capacite):m_type(type),m_conso(conso),m_capacite(capacite) {};
    /*accesseurs*/
    string getType()const
    {
        return m_type;
    }
    void setType(string type)
    {
        m_type=type;
    }

    void setConso(int conso)
    {
        m_conso=conso;
    }
    int getConso() const
    {
        return m_conso;
    }

    void setCapacite(int capacite)
    {
        m_capacite=capacite;
    }
    int getCapacite() const
    {
        return m_capacite;
    }
    void aff()
    {
        std::cout << "Type d'avion: " << getType() << " courrier" << "  |  consommation: "<< getConso() <<" L/100km"<< "  |  capacite carburant: " << getCapacite() <<" L" << std::endl;
    }
};

class Aeroport
{
private:
    int m_nom;
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
    Aeroport(int nom, int x, int y, int pistes, int places, int delai, int temps, int anticollision, int decat, int duree):m_nom(nom), m_x(x), m_y(y), m_nb_piste(pistes), m_nb_places_sol(places), m_delai_attente_sol(delai), m_temps_acces_pistes(temps), m_delai_anticollision(anticollision), m_temps_DECAT(decat), m_duree_boucle(duree){};
    ///Getter
    int get_nom() const
    {
        return m_nom;
    }
    int get_x () const
    {
        return m_x;
    }
    int get_y () const
    {
        return m_y;
    }
    int get_pistes() const
    {
        return m_nb_piste;
    }
    int get_places() const
    {
        return m_nb_places_sol;
    }
    int get_delai() const
    {
        return m_delai_attente_sol;
    }
    int get_temps() const
    {
        return m_temps_acces_pistes;
    }
    int get_anticollision() const
    {
        return m_delai_anticollision;
    }
    int get_decat() const
    {
        return m_temps_DECAT;
    }
    int get_duree() const
    {
        return m_duree_boucle;
    }
    const std::vector<std::pair<const Aeroport*, int>>& getSuccesseurs()const {return m_distance;}
    void ajouterSucc(const Aeroport*s, int m_p)
    {
        std::pair<const Aeroport*, int> Suc;
        Suc.first=s;
        Suc.second=m_p;
        m_distance.push_back(Suc);
        m_distance1[s]=m_p;
    }

    void setMarque(int marque){m_marque=marque;}
    int getMarque() const{return m_marque;}
    void setP(int p)
    {
        if(m_p>p || m_p==-1) m_p=p;
    }
    int getP() const{return m_p;}
    void aff()
    {
        std::cout << "Nom de l'aeroport : " << m_nom << std::endl;
        std::cout << "Position de l'aeroport : [" << m_x << "] [" << m_y << "]" << std::endl;
        std::cout << "Nombre de pistes : " << m_nb_piste << std::endl;
        std::cout << "Nombre de places au sol : " << m_nb_places_sol << std::endl;
        std::cout << "Delai attente au sol : " << m_delai_attente_sol << std::endl;
        std::cout << "Temps d'acces aux pistes : " << m_temps_acces_pistes << std::endl;
        std::cout << "Delai anticollision : " << m_delai_anticollision << std::endl;
        std::cout << "Temps Decollage/Atterissage : " << m_temps_DECAT << std::endl;
        std::cout << "Duree boucle d'attente : " << m_duree_boucle << std::endl;
        for (std::map<const Aeroport*, int>::iterator it=m_distance1.begin(); it!=m_distance1.end(); ++it)
                std::cout<< "Aeroport : " << m_nom << " vers " <<it->first->get_nom() <<" distance ==> " << it->second<< std::endl;
        std::cout << std::endl << std::endl;
    }
};

class Carte
{
private :
    ///liste des sommets (vecteur de pointeurs sur Sommet)
    //std::vector<Avion*> m_avions;
    std::vector<Aeroport*> m_aeroport;
    std::vector<Avion*> m_avions;
    std::vector<int> m_nb_arete;

    ///nb sommets
    int m_ordre;
    int m_ordre1;
    ///nb arretes
    int m_taille;

public :

    Carte(std::string nomFichier)
    {
        if(nomFichier == "Aeroport.txt")
        {
            std::ifstream ifs{nomFichier};
            std::ifstream ifs2{"Aretes.txt"};
            if (!ifs)
                throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
            if (!ifs2)
                throw std::runtime_error( "Impossible d'ouvrir en lecture Aretes.txt");
            ifs >> m_ordre1;
            for(int i=0; i<m_ordre1; i++)
            {
                int nom, x, y, pistes, places, delai, temps, anticollision, decat, duree, nb_aretes;
                ifs >> nom;
                ifs >> x >> y >> pistes >> places >> delai >> temps >> anticollision >> decat >> duree >> nb_aretes;
                if ( ifs.fail() )
                    throw std::runtime_error("Probleme lecture de l'aeroport");
                Aeroport* a= new Aeroport(nom, x, y, pistes, places, delai, temps, anticollision, decat, duree);
                m_aeroport.push_back(a);
                m_nb_arete.push_back(nb_aretes);
            }
            for(int i=0; i<m_ordre1; i++)
            {
                for(int j=0; j< m_nb_arete[i]; j++)
                {
                    int nom2, distance;
                    ifs2 >> nom2 >> distance;
                    if ( ifs2.fail() )
                        throw std::runtime_error("Probleme lecture des aretes");
                    m_aeroport[i]->ajouterSucc(m_aeroport[nom2], distance);
                }
            }

        }
        else if (nomFichier == "avions.txt")
        {

            std::ifstream ifs{nomFichier};
            if (!ifs)
                throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

            ifs >> m_ordre;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture ordre du graphe");

            ifs >> m_taille;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture taille du graphe");

            // for (int i=0; i< get_ordre()+1 ; ++i)
            //m_sommets.push_back( new Sommet{i, i} );
            string type;
            int conso,capacite;
            for (int i=0; i < m_ordre ; ++i)
            {
                ifs>>type>>conso>>capacite;
                if ( ifs.fail() )
                    throw std::runtime_error("Probleme lecture arc");
                Avion* a= new Avion(type, conso, capacite);
                m_avions.push_back(a);
            }
        }
    }
    /*destructeur*/
    ~Carte()
    {
        for (auto s : m_aeroport)
            delete s;
        for (auto c: m_avions)
            delete c;
    }
    /*méthode d'affichage*/
    void afficher1() const
    {
        std::cout<<std::endl<<"Carte ";
        std::cout<<std::endl <<"Nombre aeroport : "<< m_ordre1<<std::endl;
        std::cout << "Aeroport :" << std::endl;
        for (int i=0; i < m_aeroport.size(); ++i)
        {
            m_aeroport[i]->aff();
        }
    }
    /*méthode d'affichage*/
    void afficher() const
    {
        std::cout<<std::endl<<"Carte ";
        std::cout << std::endl <<"Sommets du graph: " << std::endl;
        for (int i=1; i<m_ordre+1; i++)
        {
            std::cout << i << "\t";
        }
        std::cout<<std::endl <<"ordre = "<< m_ordre<<std::endl;
        std::cout<<"taille = "<<m_taille<<std::endl;
        std::cout << "Avions :" << std::endl;
        for (int i=0; i < m_avions.size(); ++i)
        {
            m_avions[i]->aff();
        }
    }

    int get_ordre()
    {
        return m_ordre;
    }
    int get_ordre1()
    {
        return m_ordre1;
    }

    std::vector<Avion*> getAvion()
    {
        return m_avions;
    }
};

#endif // HEADER_H_INCLUDED
