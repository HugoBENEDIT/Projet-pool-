#include "_header.h"

Carte::Carte(std::string nomFichier, std::string nomFichier2)
{
    if(nomFichier2 == "Aeroport.txt")
    {
        std::ifstream ifsArr{nomFichier2};
        std::ifstream ifsArr2{"Aretes.txt"};
        if (!ifsArr)
            throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier2 );
        if (!ifsArr2)
            throw std::runtime_error( "Impossible d'ouvrir en lecture Aretes.txt");
        ifsArr >> m_ordre1;
        for(int i=0; i<m_ordre1; i++)
        {
            std::string prenom;
            int nom, x, y, pistes, places, delai, temps, anticollision, decat, duree, nb_aretes;
            ifsArr >> nom >> prenom;
            ifsArr >> x >> y >> pistes >> places >> delai >> temps >> anticollision >> decat >> duree >> nb_aretes;
            if ( ifsArr.fail() )
                throw std::runtime_error("Probleme lecture de l'aeroport");
            Aeroport* a= new Aeroport(nom, prenom, x, y, pistes, places, delai, temps, anticollision, decat, duree);
            m_aeroport.push_back(a);
            m_nb_arete.push_back(nb_aretes);
        }
        for(int i=0; i<m_ordre1; i++)
        {
            for(int j=0; j< m_nb_arete[i]; j++)
            {
                int nom2, distance;
                ifsArr2 >> nom2 >> distance;
                if ( ifsArr2.fail() )
                    throw std::runtime_error("Probleme lecture des aretes");
                m_aeroport[i]->ajouterSucc(m_aeroport[nom2], distance);
            }
        }

    }
    if (nomFichier == "avions.txt")
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
        bool vol;
        string type;
        int conso,capacite;
        for (int i=0; i < m_ordre ; ++i)
        {
            ifs>>type>>conso>>capacite;
            if ( ifs.fail() )
                throw std::runtime_error("Probleme lecture arc");
            Avion* a= new Avion(vol,type, conso, capacite);
            m_avions.push_back(a);
        }
    }
}

int Carte::get_ordre()
{
    return m_ordre;
}

int Carte::get_ordre1()
{
    return m_ordre1;
}

std::vector<Avion*> Carte::getAvion()
{
    return m_avions;
}

Avion* Carte::getAvion_i(int i)
{
    return m_avions[i];
}

std::vector<Aeroport*> Carte::getSo()const
{
    return m_aeroport;
}

Aeroport* Carte::getSo_i(int i)const
{
    return m_aeroport[i];
}

void Carte::afficher() const
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
    std::cout<<std::endl <<"Nombre aeroport : "<< m_ordre1<<std::endl;
    std::cout << "Aeroport :" << std::endl;
    for (int i=0; i < m_aeroport.size(); ++i)
    {
        m_aeroport[i]->aff();
    }
}

void Carte::init_allegro()
{
    allegro_init();

    set_color_depth(desktop_color_depth());

    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,ecran_x,ecran_y,0,0))!=0)
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    install_keyboard();
    install_mouse();
    show_mouse(screen);
}

void Carte::add_bitmap(BITMAP* tmp, std::string s)
{
    m_bitmap[s] = tmp;
}

BITMAP* Carte::get_bitmapp(std::string c)
{
    return m_bitmap[c.c_str()];
}

void Carte::ini_bitmap()
{
    BITMAP* buffer = create_bitmap(ecran_x, ecran_y);
    add_bitmap(buffer,"buffer");
    add_bitmap(load_bitmap("Photo/Avion_d.bmp",NULL),"AvionD");
    if (!m_bitmap["AvionD"])
    {
        allegro_message( "AvionD introuvable !" );
        exit( EXIT_FAILURE);
    }
    add_bitmap(load_bitmap("Photo/Map.bmp",NULL),"Map");
    if (!m_bitmap["Map"])
    {
        allegro_message( "Map introuvable !" );
        exit( EXIT_FAILURE);
    }
    BITMAP* Map2 = create_bitmap(ecran_x, ecran_y);
    add_bitmap(Map2,"Map2");

    add_bitmap(load_bitmap("Photo/Meteo.bmp",NULL),"Meteo");
    if (!m_bitmap["Meteo"])
    {
        allegro_message( "Meteo introuvable !" );
        exit( EXIT_FAILURE);
    }
}

///Commande affichage BitMap masked_blit(get_bitmapp("Salle"), buffer, m_x[i-1], m_y[i-1],0, 0, 250, 250);

void Carte::aff_map()
{
    for(int i=0; i<=28 ; i++)
        line(get_bitmapp("Map"),368,302+(i*15),368+(15*63),302+(i*15),makecol(100,100,100));
    for(int i=0; i<=63 ; i++)
        line(get_bitmapp("Map"),368+(i*15),302,368+(i*15),302+(28*15),makecol(100,100,100));
    blit(get_bitmapp("Map"), get_bitmapp("buffer"), 0,0,0,0,ecran_x, ecran_y);
    blit(get_bitmapp("buffer"), screen, 0, 0, 0, 0, ecran_x, ecran_y);
    blit(get_bitmapp("Map"), get_bitmapp("Map2"), 0,0,0,0,ecran_x, ecran_y);
}





std::vector <int> Carte::Dijkstra(int num,int num2,int num3,std::vector<int>&poids,std::vector<Avion*> a,int* condition) const
{

    std::vector<int> c((int)m_aeroport.size(),0);
    std::vector<int> p((int)m_aeroport.size(),1);
    ///avant de commencer on initialise les prédécesseurs a -1 car il n'y en a pas
    std::vector<int> previous((int)m_aeroport.size(),-1);
    int x=num,y=num2;

    int i=0;
    int maxi=0;
    int maxi2=0;
    int nb;
    std::vector<int> nbb;
    nbb.push_back(nb);

    ///le poids du sommet initial on le met à 0
    m_aeroport[num]->setP(0);

    c[num]=1;

    int numP;
    numP=num;

    ///on va initialiser le marquage des sommets sauf le sommet initial a 5
    for(int i=0; i<m_aeroport[num]->getSuccesseurs().size(); i++)
    {

        m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->setMarque(5);
    }


    ///tant que le sommet d'arrivé n'a pas été marqué on continue notre boucle
    while(m_aeroport[num2]->getMarque()!=1)
    {

        ///on marque notre sommet initial dans la Blacklist
        m_aeroport[num]->setMarque(0);
        parcours(poids,previous,num,a,num3,nbb,condition);



        ///on va mtn observez et comparer le chemin avec le poids le plus petit avec un for parcourant tous les sommets sauf sommet initial (size -1)
        for(int i=0; i<m_aeroport.size()-1; i++)
        {
            int cpt=0,cpt2=0;


            if(m_aeroport[i]->getMarque()==1)
            {
                maxi++;

                for(int j=i+1; j<m_aeroport.size(); j++)
                {



                    if(cpt==0)
                    {
                        maxi2++;
                        num=m_aeroport[i]->get_nom();
                    }
                    if(m_aeroport[j]->getMarque()==1)
                    {

                        cpt++;

                        ///si on trouve un sommet avec un poids plus petit alors on récupere le numéro de ce sommet
                        if(m_aeroport[i]->getP() > m_aeroport[j]->getP())
                        {
                            num=m_aeroport[j]->get_nom();
                            cpt2++;

                        }
                        else
                        {
                            num=m_aeroport[i]->get_nom();

                        }
                    }

                }
                if(cpt2==0)
                {
                    i=m_aeroport.size();
                }
            }


        }




    }

    return previous;

}


void Carte::parcours(std::vector<int>&poids,std::vector<int>&previous,int num,std::vector<Avion*> a,int num3,std::vector<int> nbb,int* condition) const
{
    int verif=0;
    int nb=0;

    ///ici on va parcourir tous les successeurs du Carte à partir du sommet initial donné
    for(int i=0; i<m_aeroport[num]->getSuccesseurs().size(); i++)
    {
        ///si un successeur n'a pas été marqué alors on marque ce sommet et on additionne le poids du chemin
        ///Et si on remarque que l'avion n'a pas assez de carburant alors on prend l'autre sommet pour faire une escale
        if(m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->getMarque()!=0)
        {

            m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->setP(m_aeroport[num]->getSuccesseurs()[i].second + m_aeroport[num]->getP());
            m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->setMarque(1);
            previous[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]= m_aeroport[num]->get_nom();
            poids[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]=m_aeroport[num]->getSuccesseurs()[i].second;



        }


    }

}


std::vector <int> Carte::Dijkstra2(int num,int num2,int num3,std::vector<int>&poids,std::vector<Avion*> a,int* condition) const
{

    std::vector<int> c((int)m_aeroport.size(),0);
    std::vector<int> p((int)m_aeroport.size(),1);
    ///avant de commencer on initialise les prédécesseurs a -1 car il n'y en a pas
    std::vector<int> previous((int)m_aeroport.size(),-1);
    int x=num,y=num2;

    int i=0;
    int maxi=0;
    int maxi2=0;
    int nb;
    std::vector<int> nbb;
    nbb.push_back(nb);

    ///le poids du sommet initial on le met à 0
    m_aeroport[num]->setP(0);

    c[num]=1;

    int numP;
    numP=num;

    ///on va initialiser le marquage des sommets sauf le sommet initial a 5
    for(int i=0; i<m_aeroport[num]->getSuccesseurs().size(); i++)
    {

        m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->setMarque(5);
    }


    ///tant que le sommet d'arrivé n'a pas été marqué on continue notre boucle
    while(m_aeroport[num2]->getMarque()!=1)
    {

        ///on marque notre sommet initial dans la Blacklist
        m_aeroport[num]->setMarque(0);
        parcours2(poids,previous,num,a,num3,nbb,condition);


        ///Si un avion n'a pas assez de carburant pour un chemin et ne peut pas faire d'escale
        if(*condition==1)
        {
            m_aeroport[num2]->setMarque(1);
        }

        ///on va mtn observez et comparer le chemin avec le poids le plus petit avec un for parcourant tous les sommets sauf sommet initial (size -1)
        for(int i=0; i<m_aeroport.size()-1; i++)
        {
            int cpt=0,cpt2=0;

            if(m_aeroport[i]->getMarque()==1)
            {
                maxi++;

                for(int j=i+1; j<m_aeroport.size(); j++)
                {
                    if(cpt==0)
                    {
                        maxi2++;
                        num=m_aeroport[i]->get_nom();
                    }
                    if(m_aeroport[j]->getMarque()==1)
                    {

                        cpt++;
                        ///si on trouve un sommet avec un poids plus petit alors on récupere le numéro de ce sommet
                        if(m_aeroport[i]->getP() > m_aeroport[j]->getP())
                        {
                            num=m_aeroport[j]->get_nom();
                            cpt2++;
                        }
                        else
                        {
                            num=m_aeroport[i]->get_nom();
                        }
                    }

                }
                if(cpt2==0)
                {
                    i=m_aeroport.size();
                }
            }


        }
        if(maxi==0)
        {
            *condition=1;
        }
        if(num3-1==0)
        {

            if(numP==0 && num2==6 || numP==0 && num2==5 || numP==0 && num2==4 || numP==1 && num2==6 || numP==1 && num2==5 || numP==1 && num2==4
                    || numP==2 && num2==6 || numP==2 && num2==5 || numP==2 && num2==4 || numP==3 && num2==4 || numP==3 && num2==5 || numP==3 && num2==6)
            {
                *condition=1;
            }

        }
        else if(num3-1==1)
        {
            if(numP==0 && num2==6 || numP==1 && num2==6 || numP==2 && num2==6 || numP==4 && num2==6 || numP==5 && num2==6 || numP==3 && num2==6)
            {
                *condition=1;
            }
        }
    }

    if(*condition!=1)
        std::cout<<"Voici le meilleur chemin pour aller de "<<m_aeroport[x]->get_prenom()<<" a "<<m_aeroport[y]->get_prenom()<<" avec un Poids total de: "<<m_aeroport[num2]->getP()<<std::endl;

    else std::cout<<"L'avion n'a pas assez de carburant pour aller de "<<m_aeroport[x]->get_prenom() <<" a "<<m_aeroport[y]->get_prenom()<<". Il lui faut au moins "<<m_aeroport[num2]->getP()<<" L"<<std::endl;

    return previous;
}


void Carte::parcours2(std::vector<int>&poids,std::vector<int>&previous,int num,std::vector<Avion*> a,int num3,std::vector<int> nbb,int* condition) const
{
    int verif=0;
    int nb=0;

    ///ici on va parcourir tous les successeurs du Carte à partir du sommet initial donné
    for(int i=0; i<m_aeroport[num]->getSuccesseurs().size(); i++)
    {
        ///si un successeur n'a pas été marqué alors on marque ce sommet et on additionne le poids du chemin
        ///Et si on remarque que l'avion n'a pas assez de carburant alors on prend l'autre sommet pour faire une escale
        if(m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->getMarque()!=0 && a[num3-1]->getConso()*(m_aeroport[num]->getSuccesseurs()[i].second/100)<(a[num3-1]->getCapacite()))
        {
            m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->setP(m_aeroport[num]->getSuccesseurs()[i].second + m_aeroport[num]->getP());
            m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->setMarque(1);
            previous[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]= m_aeroport[num]->get_nom();
            poids[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]=m_aeroport[num]->getSuccesseurs()[i].second;
        }
        else if(m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->getMarque()==0 && a[num3-1]->getConso()*(m_aeroport[num]->getSuccesseurs()[i].second/100)>a[num3-1]->getCapacite())
        {
            m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->setP(m_aeroport[num]->getSuccesseurs()[i].second + m_aeroport[num]->getP());
        }
        else if(m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->getMarque()!=0 && a[num3-1]->getConso()*(m_aeroport[num]->getSuccesseurs()[i].second/100)>a[num3-1]->getCapacite())
        {
            m_aeroport[m_aeroport[num]->getSuccesseurs()[i].first->get_nom()]->setP(m_aeroport[num]->getSuccesseurs()[i].second + m_aeroport[num]->getP());
        }
    }
}


void Carte::aff_trajet(std::vector<int> nbr_sommet,std::vector<std::vector <int>> sommets,std::vector<int> avion_num)
{
    std::vector<bool> changement;
    pair<int,int> case_dep;
    pair<int,int> case_arr;
    int case_x=0;
    int case_y=0;

    std::vector <int> sommet_get_x;
    std::vector <int> sommet_get_y;

    /// CALCUL DU NOMBRE DE SOMMET MAXIMAL ET METTRE DANS LA BOUCLE FOR
    int num_max=0;
    int grand;
    for(int i=0; i<nbr_sommet.size(); i++) //Compare alors toutes les valeurs du tableau afin de récuperer le plus petit F
        if(nbr_sommet[i] > num_max)
        {
            num_max=nbr_sommet[i];
            grand=i;
        }

    std::vector<int> boucle_dij;

    for(int j=0; j<3 ; j++)
    {
        changement.push_back(false);
        getAvion_i(avion_num[j]-1)->setvol(true);   //Faire décoller l'avion
        boucle_dij.push_back(0);
        sommet_get_x.push_back(NULL);
        sommet_get_y.push_back(NULL);
    }

    std::vector<pair<int,int>> initaliser;

    int temps_1=0;

    int tmp1 = 0;

    int B1;
    int B2;
    int B3;

    ///CALCUL DU TRAJET ET AFFICHAGE POUR 1 AVION =================================================================
    while(temps_1==0)  /// Pour 4 sommet, il va faire 3 trajet
    {
        std::vector <std::vector < pair<int,int> > > PCC;
        for(int pcctmp=0; pcctmp < 3; pcctmp++)
            PCC.push_back(initaliser) ;

        ///L'avion ne pourra plus décoller du tout

        bool terminer_1 = false;
        bool terminer_2 = false;
        bool terminer_3 = false;

        if(boucle_dij[0] == nbr_sommet[0]-1)
        {
            getAvion_i(avion_num[0]-1)->setvol(false);
            terminer_1 = true;
        }

        if(boucle_dij[1] == nbr_sommet[1]-1)
        {
            getAvion_i(avion_num[1]-1)->setvol(false);
            terminer_2 = true;
        }
        if(boucle_dij[2] == nbr_sommet[2]-1)
        {
            getAvion_i(avion_num[2]-1)->setvol(false);
            terminer_3 = true;
        }



        ///CALCUL AVEC A STAR=========================================================================
        for(int j=0; j<3 ; j++) ///calcul avec A Star pour tout les avions
        {
            if(getAvion_i(avion_num[j]-1)->getvol()==true)
            {
                if(changement[j] == false)   ///SI LE VECTEUR EST FINI FAUT PAR CALCULER CA .............
                {
                    sommet_get_x[j] = getSo_i(sommets[j][boucle_dij[j]])->get_x();
                    sommet_get_y[j] = getSo_i(sommets[j][boucle_dij[j]])->get_y();
                }
                case_dep.first = sommet_get_x[j];
                case_dep.second = sommet_get_y[j];

                //RECUP LES COO DANS CASE ARRIVE
                case_arr.first = getSo_i(sommets[j][boucle_dij[j]+1])->get_x();
                case_arr.second = getSo_i(sommets[j][boucle_dij[j]+1])->get_y();


                ///Calcul angle
                double A;
                A = (atan2( (case_arr.second *15 + 368) - (case_dep.second * 15 + 302), (case_arr.first * 15 + 368)  -   (case_dep.first * 15 + 302)   ))*(180.0/(M_PI));  //A = (atan2(y arrivé - y départ , x arrivé - x départ))*(180.0/(M_PI));
                if(A<0)
                {
                    A = A+ 360;
                }
                if(j==0)
                B1 = (A * 256)/360;
                if(j==1)
                B2 = (A * 256)/360;
                if(j==2)
                B3 = (A * 256)/360;

                Trajet trajet;
                PCC[j]=  trajet.AStar(case_dep,case_arr,case_x,case_y);
            }
        }


        ///CALCUL AVEC A STAR=========================================================================




        ///METTRE BOUCLE WHILE ICI POUR LAFFICHAGE ALLEGRO
        int popo=0;
        int porte=1;
        int porte2=1;
        int porte3=1;

        while(porte==1 && porte2==1 && porte3==1)
        {
            blit(get_bitmapp("Map2"), get_bitmapp("buffer"), 0,0,0,0,ecran_x, ecran_y);
            if(getAvion_i(avion_num[0]-1)->getvol() == true)
            {
                    rotate_sprite(get_bitmapp("buffer"),get_bitmapp("AvionD"), PCC[0][popo].first * 15 + 368 - 7, PCC[0][popo].second *15 + 302    -  7, itofix(B1));
                    textprintf_ex(get_bitmapp("buffer"), font, 1371, 43, makecol(255,255,255), -1, "Information de l'Avion :");
                    textprintf_ex(get_bitmapp("buffer"), font, 1371, 53, makecol(255,255,255), -1, "Type :");
                    textprintf_ex(get_bitmapp("buffer"), font, 1371, 63, makecol(255,255,255), -1, "Carburant :");
                    textprintf_ex(get_bitmapp("buffer"), font, 1371, 73, makecol(255,255,255),-1,  "Position [x] : %d", PCC[0][popo].first * 15 + 368 - 7);
                    textprintf_ex(get_bitmapp("buffer"), font, 1371, 83, makecol(255,255,255), -1, "Position [y] : %d", PCC[0][popo].second * 15 + 302 - 7);
                    if(avion_num[0] == 1)
                    {
                        textprintf_ex(get_bitmapp("buffer"), font, 1430, 53, makecol(255,255,255), -1, "court");
                        textprintf_ex(get_bitmapp("buffer"), font, 1465, 63, makecol(255,255,255), -1, "4500");
                    }
                    else if(avion_num[0] == 2)
                    {
                        textprintf_ex(get_bitmapp("buffer"), font, 1430, 53, makecol(255,255,255), -1, "moyen");
                        textprintf_ex(get_bitmapp("buffer"), font, 1465, 63, makecol(255,255,255), -1, "10000");
                    }
                    else if(avion_num[0] == 3)
                    {
                        textprintf_ex(get_bitmapp("buffer"), font, 1430, 53, makecol(255,255,255), -1, "long");
                        textprintf_ex(get_bitmapp("buffer"), font, 1465, 63, makecol(255,255,255), -1, "20000");
                    }

            }
            if(getAvion_i(avion_num[1]-1)->getvol() == true)
            {
                rotate_sprite(get_bitmapp("buffer"),get_bitmapp("AvionD"), PCC[1][popo].first * 15 + 368 - 7, PCC[1][popo].second *15 + 302    -  7, itofix(B2));
            }
            if(getAvion_i(avion_num[2]-1)->getvol() == true)
            {

                rotate_sprite(get_bitmapp("buffer"),get_bitmapp("AvionD"), PCC[2][popo].first * 15 + 368 - 7, PCC[2][popo].second *15 + 302    -  7, itofix(B3));
            }
            blit(get_bitmapp("buffer"), screen, 0, 0, 0, 0, ecran_x, ecran_y);

            delay(2000);

            ///PLAER UNE PERTURBATION METEO
            if(key[KEY_T])
            {
                case_x = (mouse_x - 368) / 15;
                case_y = (mouse_y - 302) / 15;

                blit(get_bitmapp("Map"), get_bitmapp("Map2"), 0,0,0,0,ecran_x, ecran_y);
                blit(get_bitmapp("Meteo"), get_bitmapp("Map2"), 46,0, case_x*15 + 368, case_y*15 + 302 + 3,45+46,45);

                porte =0;

                for(int change; change< changement.size(); change++)
                    changement[change] = true;

                sommet_get_x[0] = PCC[0][popo].first;
                sommet_get_y[0] = PCC[0][popo].second;

                sommet_get_x[1] = PCC[1][popo].first;
                sommet_get_y[1] = PCC[1][popo].second;

                sommet_get_x[2] = PCC[2][popo].first;
                sommet_get_y[2] = PCC[2][popo].second;
            }

            popo=popo+1;

            if(popo == PCC[0].size() && getAvion_i(avion_num[0]-1)->getvol() == false)
            {
                std::cout << "JE RENTRE LA 0 " << std::endl;
                getAvion_i(avion_num[0]-1)->setvol(false); ///L'avion atteri
                changement[0] = false;

                ///LES AUTRES NE CHANGE PAS
                changement[1] = true;
                sommet_get_x[1] = PCC[1][popo].first;
                sommet_get_y[1] = PCC[1][popo].second;

                changement[2] = true;
                sommet_get_x[2] = PCC[2][popo].first;
                sommet_get_y[2] = PCC[2][popo].second;
                ///////////////////////////////////

                porte=0;
                boucle_dij[0]++;
            }

            if(popo == PCC[1].size() && getAvion_i(avion_num[1]-1)->getvol() == false)
            {
                std::cout << "JE RENTRE LA 1 " << std::endl;
                getAvion_i(avion_num[1]-1)->setvol(false); ///L'avion atteri
                changement[1] = false;

                changement[0] = true;
                sommet_get_x[0] = PCC[0][popo].first;
                sommet_get_y[0] = PCC[0][popo].second;

                changement[2] = true;
                sommet_get_x[2] = PCC[2][popo].first;
                sommet_get_y[2] = PCC[2][popo].second;

                porte3=0;
                boucle_dij[1]++;
            }

            if(popo == PCC[2].size() && getAvion_i(avion_num[2]-1)->getvol() == false)
            {
                std::cout << "JE RENTRE LA 1 " << std::endl;
                getAvion_i(avion_num[2]-1)->setvol(false); ///L'avion atteri
                changement[2] = false;

                changement[0] = true;
                sommet_get_x[0] = PCC[0][popo].first;
                sommet_get_y[0] = PCC[0][popo].second;

                changement[1] = true;
                sommet_get_x[1] = PCC[1][popo].first;
                sommet_get_y[1] = PCC[1][popo].second;

                porte2=0;
                boucle_dij[2]++;
            }
            getAvion_i(avion_num[0]-1)->setvol(true); ///L'avion redécolle
            getAvion_i(avion_num[1]-1)->setvol(true); ///L'avion redécolle
            getAvion_i(avion_num[2]-1)->setvol(true); ///L'avion redécolle

        }
        ///FIN DE LA BOUCLE WHILE
        return;
    }

}

/*
void Carte::aff_trajet(std::vector<int> nbr_sommet,std::vector<std::vector <int>> sommets,std::vector<int> avion_num)
{

    for(int k=0; k<sommets.size() ; k++)
        {
            std::cout << " ===========  Pour le sommet " << k << std::endl;
            for(int i=0; i<sommets[k].size(); i++)
                std::cout<< "(" << sommets[k][i] << ")" << std::endl;
        }

    std::vector<bool> changement;
    pair<int,int> case_dep;
    pair<int,int> case_arr;
    int case_x=0;
    int case_y=0;



    /// CALCUL DU NOMBRE DE SOMMET MAXIMAL ET METTRE DANS LA BOUCLE FOR
    int num_max=0;
    int grand;
    for(int i=0; i<nbr_sommet.size(); i++) //Compare alors toutes les valeurs du tableau afin de récuperer le plus petit F
        if(nbr_sommet[i] > num_max)
        {
            num_max=nbr_sommet[i];
            grand=i;
        }

    std::vector<int> boucle_dij;

    for(int j=0; j<2 ; j++)
    {
    changement.push_back(false);
    getAvion_i(avion_num[j]-1)->setvol(true);   //Faire décoller l'avion
    boucle_dij.push_back(0);
    }

    std::vector<pair<int,int>> initaliser;

    ///CALCUL DU TRAJET ET AFFICHAGE POUR 1 AVION =================================================================
    while(boucle_dij[grand] < num_max-1)  /// Pour 4 sommet, il va faire 3 trajet
    {
        std::vector <std::vector < pair<int,int> > > PCC;
        for(int pcctmp=0; pcctmp < 2;pcctmp++)
            PCC.push_back(initaliser) ;

            ///L'avion ne pourra plus décoller du tout
    std::cout << "La boucle de dij 0 est: "<< boucle_dij[0] <<" le nbr de sommet 0 - 1 est " << nbr_sommet[0]-1 << std::endl;
    std::cout << "La boucle de dij 1 est: "<< boucle_dij[1] <<" le nbr de sommet 1 - 1 est " << nbr_sommet[1]-1 << std::endl;
    if(boucle_dij[0] == nbr_sommet[0]-1)
         getAvion_i(avion_num[0]-1)->setvol(false);
    if(boucle_dij[1] == nbr_sommet[1]-1)
         getAvion_i(avion_num[1]-1)->setvol(false);

         std::vector <int> sommet_get_x;
    std::vector <int> sommet_get_y;

        ///CALCUL AVEC A STAR=========================================================================
        for(int j=0; j<2 ; j++) ///calcul avec A Star pour tout les avions
        {
            std::cout << "POUR J = "<< j << std::endl;
            if(getAvion_i(avion_num[j]-1)->getvol()==true)
            {
                std::cout << "changement est " << changement[j] << std::endl;
                if(changement[j] == false)   ///SI LE VECTEUR EST FINI FAUT PAR CALCULER CA .............
                {
                    sommet_get_x.push_back (getSo_i(sommets[j][boucle_dij[j]])->get_x());
                    sommet_get_y.push_back (getSo_i(sommets[j][boucle_dij[j]])->get_y());
                }
                case_dep.first = sommet_get_x[j];
                case_dep.second = sommet_get_y[j];

                //RECUP LES COO DANS CASE ARRIVE
                case_arr.first = getSo_i(sommets[j][boucle_dij[j]]+1)->get_x();
                case_arr.second = getSo_i(sommets[j][boucle_dij[j]]+1)->get_y();


                Trajet trajet;
                ///LE QUADRILLAGE EST DE <0,0> à <61,29>

                std::cout <<  " case_dep.first : " << case_dep.first << std::endl;
                std::cout <<  " case_dep.second : " << case_dep.second << std::endl;
                std::cout <<  " case_arr.first : " << case_arr.first << std::endl;
                std::cout <<  " case_arr.second : " << case_arr.second << std::endl;

                PCC[j]=  trajet.AStar(case_dep,case_arr,case_x,case_y);
            }
        }




        for(int k=0; k<PCC.size() ; k++)
        {
            std::cout << " ===========  Pour l'avion " << k << std::endl;
            for(int i=0; i<PCC[k].size(); i++)
                std::cout<< "(" << PCC[k][i].first << "," << PCC[k][i].second << ")" << std::endl;
        }

        ///CALCUL AVEC A STAR=========================================================================




        ///METTRE BOUCLE WHILE ICI POUR LAFFICHAGE ALLEGRO
        ///Calcul angle
        double A;
        A = (atan2( (case_arr.second *15 + 368) - (case_dep.second * 15 + 302), (case_arr.first * 15 + 368)  -   (case_dep.first * 15 + 302)   ))*(180.0/(M_PI));  //A = (atan2(y arrivé - y départ , x arrivé - x départ))*(180.0/(M_PI));
        if(A<0)
        {
            A = A+ 360;
        }
        int B = (A * 256)/360;

        int popo=0;
        int porte=1;

        while(porte==1)
        {
            blit(get_bitmapp("Map2"), get_bitmapp("buffer"), 0,0,0,0,ecran_x, ecran_y);
            if(getAvion_i(avion_num[0]-1)->getvol() == true)
            {
                rotate_sprite(get_bitmapp("buffer"),get_bitmapp("AvionD"), PCC[0][popo].first * 15 + 368 - 7, PCC[0][popo].second *15 + 302    -  7, itofix(B));
            }
            if(getAvion_i(avion_num[1]-1)->getvol() == true)
            {
                std::cout << "PCC[1][popo].first  " << PCC[1][popo].first << " PCC[1][popo].second " << PCC[1][popo].second << std::endl;

                rotate_sprite(get_bitmapp("buffer"),get_bitmapp("AvionD"), PCC[1][popo].first * 15 + 368 - 7, PCC[1][popo].second *15 + 302    -  7, itofix(B));
            }
            blit(get_bitmapp("buffer"), screen, 0, 0, 0, 0, ecran_x, ecran_y);

            delay(500);

            ///PLAER UNE PERTURBATION METEO
            if(key[KEY_T])
            {
                case_x = (mouse_x - 368) / 15;
                case_y = (mouse_y - 302) / 15;

                blit(get_bitmapp("Map"), get_bitmapp("Map2"), 0,0,0,0,ecran_x, ecran_y);
                blit(get_bitmapp("Meteo"), get_bitmapp("Map2"), 46,0, case_x*15 + 368, case_y*15 + 302 + 3,45+46,45);

                porte =0;

                for(int change; change< changement.size();change++)
                changement[change] = true;

                sommet_get_x[0] = PCC[0][popo].first;
                sommet_get_y[0] = PCC[0][popo].second;

                sommet_get_x[1] = PCC[1][popo].first;
                sommet_get_y[1] = PCC[1][popo].second;
            }

            popo=popo+1;

            std::cout << "PCC[0].size()   " << PCC[0].size() << std::endl;
            if(popo == PCC[0].size())
            {
                std::cout << "JE RENTRE LA 0 " << std::endl;
                getAvion_i(avion_num[0]-1)->setvol(false); ///L'avion atteri
                changement[0] = false;

                changement[1] = true;
                sommet_get_x[1] = PCC[1][popo].first;
                sommet_get_y[1] = PCC[1][popo].second;

                porte=0;
                boucle_dij[0]++;
            }

            std::cout << "PCC[1].size()   " << PCC[1].size() << std::endl;
            if(popo == PCC[1].size())
            {
                std::cout << "JE RENTRE LA 1 " << std::endl;
                getAvion_i(avion_num[1]-1)->setvol(false); ///L'avion atteri
                changement[1] = false;

                changement[0] = true;
                sommet_get_x[0] = PCC[0][popo].first;
                sommet_get_y[0] = PCC[0][popo].second;

                porte=0;
                boucle_dij[1]++;
            }
        }

        getAvion_i(avion_num[0]-1)->setvol(true); ///L'avion redécolle
        getAvion_i(avion_num[1]-1)->setvol(true); ///L'avion redécolle

        std::cout << "JE RENTRE LA HIHI " << std::endl;



        ///FIN DE LA BOUCLE WHILE
    }
}
*/
