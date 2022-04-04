#include "header.h"



    void Graphe::Kruskal(int porte)
    {

        ///Récupère le vecteur arète depuis le sous programme qui TRI par ordre croissant le poids de chaque aretes
        std::vector<Arete*> Arete = TriArete();

        ///Initialisation d'un vecteur indiquant que chaque sommet est isolé
        std::vector<int> verif;
        for(int i=0; i<m_sommets.size(); i++)
            verif.push_back(i);

        ///Initialisation des vecteurs permettant l'affichage du résultat final
        std::vector<int> som1;
        std::vector<int> som2;
        std::vector<int> poids;


        ///AFFICHAGE SANS KRUSKAL===================================
        if(porte==1)
        {
            system("cls");
            std::cout << "... AFFICHAGE BASIC ...\n "<< std::endl;
            std::cout << "Les Aretes sont: "<< std::endl;
            std::cout << std::endl;
            for(auto s: m_aretes)
                s -> afficher();
        }

        if(porte==2)
        {
            system("cls");
            std::cout << "... AFFICHAGE DU TRI ...\n "<< std::endl;
            std::cout << "Les Aretes sont: "<< std::endl;
            std::cout << std::endl;
            for(auto s: Arete)
                s -> afficher();
        }

        ///Principale boucle de KRUSKAL=============================
        for(auto s : Arete)
            if(verif[s-> getSommet_init()]!=verif[s-> getSommet_fin()]) ///Si les composantes connexes sont différents
            {
                int tmp = verif[s-> getSommet_fin()];
                for(int i=0; i<=verif.size(); i++) ///Permet de faire la "mise à jour" de chaque composante connexe
                {
                    if(verif[i]==tmp)
                        verif[i]=verif[s-> getSommet_init()];
                }
                som1.push_back(s->getSommet_init());
                som2.push_back(s->getSommet_fin());
                poids.push_back(s->getPoid());
            }


        ///AFFICHAGE DE KRUSKAL=====================================
        if(porte==3)
        {
            system("cls");
            std::cout << "...Lancement de l'algorithme de Kruskal...\n "<< std::endl;
            std::cout << "Les Aretes utilisees sont: "<< std::endl;
            std::cout << std::endl;
            for(int i=0; i<poids.size(); i++)
            {
                std::cout << "Arete: " ;
                std::cout << "[" << som1[i] << ";" << som2[i] << "] \t De poids: " << poids[i] << std::endl;
            }

            int total=0;
            for(int i=0; i<poids.size(); i++)
                total=total+poids[i];

            std::cout << std::endl << "Le poids total est de : " << total << std::endl;
        }
        ///=============================
    }




