#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

 void Kruskal(int porte);


class Sommet
{
private :
    int m_num;
    ///chaque sommet possède la liste de ses successeurs (un vecteur de pointeurs sur Sommet)
    std::vector<const Sommet*> m_successeurs;

public :
    /*constructeur*/
    Sommet(int num):m_num{num} {};
    /*accesseurs*/
    int getNum()const
    {
        return m_num;
    }
    ///accesseur : pour la liste des successeurs
    const std::vector<const Sommet*>& getSuccesseurs()const
    {
        return m_successeurs;
    }
    /* pour ajouter un successeur à la liste*/
    void ajouterSucc(const Sommet*s)
    {
        m_successeurs.push_back(s);
    }

};

///============================================================================
class Arete
{
private :
    Sommet* m_sommet_init;
    Sommet* m_sommet_fin;
    int m_poid;

public :

    Arete(Sommet* sommet_init, Sommet* sommet_fin, int poid)
        :m_sommet_init(sommet_init),m_sommet_fin(sommet_fin),m_poid(poid) {};

///Arete(int poid):m_poid{poid} {};

    ~Arete();

    //accesseurs
    int getPoid()const
    {
        return m_poid;
    }

    int getSommet_init ()
    {
        return m_sommet_init->getNum();
    }
    Sommet *getSommet_init_p ()
    {
        return m_sommet_init;
    }

    int getSommet_fin ()
    {
        return m_sommet_fin->getNum();
    }
    Sommet *getSommet_fin_p ()
    {
        return m_sommet_fin;
    }

    ///AFFICHAGE
    void afficher() const
    {
        std::cout << "Arete: " ;
        std::cout << "[" << m_sommet_init->getNum() << ";" << m_sommet_fin->getNum() << "] \t De poids: " << m_poid << std::endl;
    }
};

///===================================================================================
class Graphe
{
private :
    ///liste des sommets (vecteur de pointeurs sur Sommet)
    std::vector<Sommet*> m_sommets;
    std::vector<Arete*> m_aretes;

public :
    /* La construction du réseau peut se faire à partir d'un fichier
     dont le nom est passé en paramètre
    Le fichier contient : orientation (0 ou 1), ordre, taille, liste des arcs */
    Graphe(std::string nomFichier)
    {
        std::ifstream ifs{nomFichier};
        if (!ifs)
            throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
        ///====================================
        int ordre;
        ifs >> ordre;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture ordre du graphe");
        ///====================================

        ///====================================
        int taille;
        ifs >> taille;
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture taille du graphe");
        ///====================================
        for (int i=0; i<=ordre; i++)
            m_sommets.push_back( new Sommet{i} );
        ///====================================
        int num1,num2,poids;
        for (int i=1; i<=taille; i++)
        {
            ifs>>num1>>num2>>poids;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture arc");
            //On crée l'arete
            Arete *a= new Arete(m_sommets[num1],m_sommets[num2],poids);
            //On l'ajoute
            m_aretes.push_back(a);
        }
    }
    /*destructeur*/
    ~Graphe()
    {
        for (auto s : m_sommets)
            delete s;
    }
    /*méthode d'affichage*/
    void afficher() const
    {
        std::cout<<std::endl<<"graphe ";
        std::cout<<"ordre = "<<m_sommets.size()<<std::endl<<"  ";
        std::cout<<"listes d'adjacence :"<<std::endl;
        //for(auto s : m_aretes)
        //   s -> afficher();

    }


    std::vector<Arete*> TriArete() ///sous-programme triant le poids des aretes dans l'ordre croissant
    {

        std::vector<Arete*> AreteTrie;
        ///Initialise les aretes de base dans un autre vecteur
        for(auto s : m_aretes)
        {
            Arete *a=new Arete(s->getSommet_init_p(),s->getSommet_fin_p(),s->getPoid());
            AreteTrie.push_back(a);
        }


        ///TRI A BULLE PERMETTANT DE TRIER LE POIDS DES ARETES DANS L'ORDRE CROISSANT
        for (int i=0 ; i < AreteTrie.size()-1; i++)
        {
            for (int j=0 ; j < AreteTrie.size()-i-1; j++)
            {
                if (AreteTrie[j]->getPoid() > AreteTrie[j+1]->getPoid())
                {
                    Arete *tmp=new Arete(AreteTrie[j]->getSommet_init_p(),AreteTrie[j]->getSommet_fin_p(),AreteTrie[j]->getPoid());
                    AreteTrie[j] = AreteTrie[j+1];
                    AreteTrie[j+1] = tmp;
                }
            }
        }
        ///==========================================================================

        return AreteTrie;

    }

    void Kruskal(int porte);

};



#endif // HEADER_H_INCLUDED
