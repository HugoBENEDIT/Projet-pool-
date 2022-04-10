#include "_header.h"

///---------------------------------------------------------------------------------

///on envoie en parametre le sommet initial et le vecteur des prédécesseurs
void aff(size_t num,size_t fin,const std::vector<int>& graph,const std::vector<int>& p, int &nbr, std::vector<int>& sommets)
{
    size_t i,j,x;
    int poids_tot=0;

    std::vector<int> sommet_tmp;

    ///on parcours notre vector des prédécesseurs
    for(i=0; i<graph.size(); i++)
    {
        ///si l'itérateur est différent du sommet initial
        if(i!=num && i==fin)
        {
            ///et si le prédécesseur a bien été marqué (car -1 il n'est pas marqué)
            if(graph[i]!=-1)
            {
                x=p[i];
                poids_tot+=x;

                std::cout<<"[P:"<<x<<"]";
                std::cout<<i<<" <- ";
                nbr++;
                sommet_tmp.push_back(i);

                j=graph[i];
                sommet_tmp.push_back(j);

                while(j!=num)
                {
                    x=p[j];
                    poids_tot+=x;
                    std::cout<<"[P:"<<x<<"]";
                    std::cout<<j<<" <- ";
                    j=graph[j];
                    nbr++;
                    sommet_tmp.push_back(j);

                }

                std::cout<<j<<std::endl;
                nbr++;
            }
        }
    }
    std::cout<<"Poids total: "<<poids_tot<<std::endl;

    std::cout<<"Il y a : "<< nbr << " Sommets " << std::endl;

    for(int i=sommet_tmp.size()-1; i>=0; i--)
        sommets.push_back(sommet_tmp[i]);

    std::cout<<" Il passera par les sommets: " <<std::endl;
    for(int i=0; i<sommets.size(); i++)
        std::cout <<sommets[i]<< std::endl;

}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int calcul_ang(pair<int,int> case_dep, pair<int,int> case_arr)
{
    double A;
    A = (atan2( (case_arr.second *15 + 368) - (case_dep.second * 15 + 302), (case_arr.first * 15 + 368)  -   (case_dep.first * 15 + 302)   ))*(180.0/(M_PI));  //A = (atan2(y arrivé - y départ , x arrivé - x départ))*(180.0/(M_PI));
    if(A<0)
    {
        A = A+ 360;
    }
    return (A * 256)/360;
}

void menu(Carte *carte)
{
    int choix;
    std::cout << " \t \t \t \t BIENVENUE DANS LA SIMULATION DU CONTROLE AERIEN ! " << std::endl << std::endl;
    std::cout << " \t \t 1. Voir les informations des aeroports et des avions " << std::endl;
    std::cout << " \t \t 2. Faire une simulation Dijkstra " << std::endl;
    std::cout << " \t \t 3. Faire une simulation avec graphisme " << std::endl;
    std::cout << " \t \t 4. Quittez le programme " << std::endl;
    std::cout << " Veuillez faire un choix : ";
    std::cin >> choix;
    switch(choix)
    {
    case 1:
    {
        /// appel de la méthode pour afficher le graphe
        carte->afficher();
        break;
    }
    case 2:
    {
        int sommet_ini, sommet_fin, avion_num;
        int condition=0;
        std::vector<int> previous;
        std::vector<Avion*> a;
        a=carte->getAvion();

        std::vector<int> poids((int)carte->getSo().size(),-1);
        poids= {NULL};

        ///saisie du numéro du sommet initial pour lancer un Dijkstra
        std::cout<<std::endl<<"numero du sommet initial : ";
        std::cin >> sommet_ini;

        ///Blindage
        while (sommet_ini < 0 || sommet_ini > carte->get_ordre1()-1 )
        {
            std::cout << "Erreur lors de la saisis !" << std::endl;
            std::cin >> sommet_ini;
        }

        std::cout<<std::endl<<"numero du sommet final : ";
        std::cin >>sommet_fin;

        ///Blindage
        while (sommet_fin < 0 || sommet_fin > carte->get_ordre1()-1 )
        {
            std::cout << "Erreur lors de la saisis !" << std::endl;
            std::cin >> sommet_fin;
        }

        std::cout<< "Saisir un avion :" <<std::endl;
        std::cin >> avion_num;

        while (avion_num < 1 || avion_num > carte->get_ordre() )
        {
            std::cout<<std::endl<<"Erreur lors de la saisis !" << std::endl;
            std::cin>>avion_num;
        }

        ///Pour Astar
        int nbr_sommet=0;
        std::vector<int> sommets;

        ///Dijkstra + affichage
        std::cout<<std::endl;

        previous=carte->Dijkstra(sommet_ini,sommet_fin,avion_num,poids, a, &condition);
        std::cout <<std::endl;
        aff(sommet_ini,sommet_fin,previous,poids,nbr_sommet,sommets);

        if(condition==1)
        {
            std::cout << "L'avion ne peut decoller car pas assez de carburant" << std::endl;
        }
        break;
    }
    case 3:
    {
        ///Initialisation allegro
        carte->init_allegro();
        carte->ini_bitmap();
        carte->aff_map();

        std::vector <int> sommet_ini;
        std::vector <int> sommet_fin;
        std::vector <int> avion_num;
        int sommet_ini_tmp;
        int sommet_fin_tmp;
        int avion_num_tmp;

        int tmp;

        int condition=0;
        std::vector<int> previous ;
        std::vector<Avion*> a ;
        a=carte->getAvion();

        std::vector<int> poids((int)carte->getSo().size(),-1);
        poids= {NULL};

        ///saisie du numéro du sommet initial pour lancer un Dijkstra==================
        std::cout<<std::endl<<"numero du sommet initial : ";
        std::cin >> tmp;
        while (tmp < 0 || tmp > carte->get_ordre1()-1 )
        {
            std::cout << "Erreur lors de la saisis !" << std::endl;
            std::cin >> tmp;
        }
        sommet_ini.push_back(tmp);

        ///SAISIE DU SOMMET FINAL==================================================
        std::cout<<std::endl<<"numero du sommet final : ";
        std::cin >>tmp;
        while (tmp < 0 || tmp > carte->get_ordre1()-1 )
        {
            std::cout << "Erreur lors de la saisis !" << std::endl;
            std::cin >> tmp;
        }
        sommet_fin.push_back(tmp);

        ///SAISIE DU TYPE D'AVION==================================================
        std::cout<< "Saisir un avion :" <<std::endl;
        std::cin >> tmp;
        while (tmp < 1 || tmp > carte->get_ordre() )
        {
            std::cout<<std::endl<<"Erreur lors de la saisis !" << std::endl;
            std::cin>>tmp;
        }
        avion_num.push_back(tmp);

        ///Pour Astar
        std::vector<int> nbr_sommet;
        std::vector<std::vector<int>> sommets;


        ///Ajout d'un avion  (LECTURE DE FICHIER)
        sommet_ini.push_back(1);
        sommet_fin.push_back(5);
        avion_num.push_back(3);

        ///Ajout d'un deuxieme avion
        sommet_ini.push_back(3);
        sommet_fin.push_back(6);
        avion_num.push_back(2);


        for(int i=0;i < 3 ; i++)
        {
        int nbr_sommet_tmp=0;
        std::vector<int> sommets_tmp;

        sommet_ini_tmp = sommet_ini[i];
        sommet_fin_tmp = sommet_fin[i];
        avion_num_tmp = avion_num[i];

            ///Dijkstra + affichage
        std::cout<<std::endl;
        previous=carte->Dijkstra(sommet_ini_tmp,sommet_fin_tmp,avion_num_tmp,poids,a,&condition);
        std::cout <<std::endl;
        aff(sommet_ini_tmp,sommet_fin_tmp,previous,poids,nbr_sommet_tmp,sommets_tmp);


        nbr_sommet.push_back(nbr_sommet_tmp);
        sommets.push_back(sommets_tmp);
        }


        ///CALCUL DU TRAJET ET AFFICHAGE POUR 1 AVION =================================================================
        carte->aff_trajet(nbr_sommet,sommets,avion_num);
        std::cout << std::endl <<"Veuillez cliquer sur l'onglet d'allegro ! " << std::endl;
        allegro_exit();
        break;
    }
    case 4:
    {
        break;
    }
    default:
    {
        std::cout << "Erreur de saisis veuillez resaisir un choix : ";
        std::cin >> choix;
    }
    }
}



