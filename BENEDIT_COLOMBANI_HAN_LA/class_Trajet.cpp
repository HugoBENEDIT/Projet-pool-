#include "_header.h"

std::vector < pair<int,int> > Trajet::AStar( pair<int,int> coo_dep, pair<int,int> coo_arr, int case_x, int case_y)
{

    ///Initialisation d'une porte
    bool teo = true;

    ///Blindage des valeurs : est -il sur le quadrillage ?
    if( coo_dep.first < 0 || coo_dep.first > 62)
    {
        std::cout << "L'avion n'est plus sur le quadrillage" << std::endl;
        teo=false;
    }
    if( coo_dep.second < 0 || coo_dep.second > 27)
    {
        std::cout << "L'avion n'est plus sur le quadrillage" << std::endl;
        teo=false;
    }
    if( coo_arr.first < 0 || coo_arr.first > 62)
    {
        std::cout << "L'avion n'est plus sur le quadrillage" << std::endl;
        teo=false;
    }
    if( coo_arr.second < 0 || coo_arr.second > 27)
    {
        std::cout << "L'avion n'est plus sur le quadrillage" << std::endl;
        teo=false;
    }

    ///On décale tout les valeurs de 1 ( qu'on remettra a la normal a la fin) permettant de ne pas "froller" le mur
    coo_dep.first = coo_dep.first+1;
    coo_dep.second = coo_dep.second+1;
    coo_arr.first = coo_arr.first+1;
    coo_arr.second = coo_arr.second+1;

    ///Initialisation de cases
    Case *Case_dep; //Case départ
    Case *Case_arr; //Case d'arrivé
    Case *Case_actu; //Case actuelle (case actu de Astar)

    ///INITIALISATION =============================================
    std::vector < pair<int,int> > PCC; ///Vecteur des plus court chemin qui seras retourné dans le main

    PCC.push_back(make_pair(coo_dep.first-1,coo_dep.second-1));

    ///Initialisation de chaque cases
    for(int j=0; j<32; j++)
        for(int i=0; i<65; i++)
            m_carte.push_back(new Case(i,j,1,std::numeric_limits<int>::max(),std::numeric_limits<int>::max()));


    ///INITIALISE LES PREDECESSEURS A FALSE
    std::vector < std::vector <bool>> preds;
    std::vector <bool> tmp_bool;
    for(int i=0; i<65; i++)
        tmp_bool.push_back(true);
    for(int i=0; i<32; i++)
        preds.push_back(tmp_bool);

    preds[coo_dep.second][coo_dep.first]=false; ///Initialisation de la case de bases

    ///INITIALISE LA LIMITE DU PLATEAU
    for(int i=0; i<28 ; i++)
        preds[i][0]=false;

    ///METTRE DES MUR ICI (par exemple à 5 20 =>  preds[20+1][5+1]=false;  ///METEO ICI
    preds[case_y+1][case_x+1]=false;
    preds[case_y+1][case_x+2]=false;
    preds[case_y+1][case_x+3]=false;
    preds[case_y+2][case_x+1]=false;
    preds[case_y+2][case_x+2]=false;
    preds[case_y+2][case_x+3]=false;
    preds[case_y+3][case_x+1]=false;
    preds[case_y+3][case_x+2]=false;
    preds[case_y+3][case_x+3]=false;



    for (auto s : m_carte)  ///INITIALISATION DE LA PREMIERE CASE
    {
        if(coo_dep.first == s->getX() && coo_dep.second == s->getY() )
        {
            Case_dep = s;
            Case_actu = s;
        }

        if(coo_arr.first == s->getX() && coo_arr.second == s->getY() )
        {
            Case_arr = s;
        }
    }
    ///FIN INITIALISATION ==========================================

    ///Si la case de départ = case d'arrivé
    if(coo_dep.first == coo_arr.first && coo_dep.second == coo_arr.second)
    {
        std::cout << "L'avion fait du surplace ! " << std::endl;
        teo=false;
    }

bool premiere=true;

    ///PRINCIPALE BOUCLE DE ASTAR
    while(teo)
    {

    Case *CaseNO;
    Case *CaseN;
    Case *CaseNE;
    Case *CaseE;
    Case *CaseSE;
    Case *CaseS;
    Case *CaseSO;
    Case *CaseO;

    double nb_g=0;

        for (auto s : m_carte) ///Boucle for permettant de passer par les cases et trouver les cases voisin de la case actuelle
        {
            ///POUR LA CASE DU NORD OUEST
            if(s->getX() == Case_actu->getX()-1 && s->getY() == Case_actu->getY()-1 && s->getId() == 1)
            {
                s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseNO = s; ///CaseNO Prend cette valeur pour la comparaison plus tard

            }

            ///POUR LA CASE DU NORD
            if(s->getX() == Case_actu->getX() && s->getY() == Case_actu->getY()-1  && s->getId() == 1)
            {
                s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseN = s;
            }

            ///POUR LA CASE DU NORD EST
            if(s->getX() == Case_actu->getX()+1 && s->getY() == Case_actu->getY()-1  && s->getId() == 1)
            {

                s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseNE = s;
            }

            ///POUR LA CASE DE L'EST
            if(s->getX() == Case_actu->getX()+1 && s->getY() == Case_actu->getY()  && s->getId() == 1)
            {


                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseE = s;
            }

            ///POUR LA CASE DU SUD EST
            if(s->getX() == Case_actu->getX()+1 && s->getY() == Case_actu->getY()+1  && s->getId() == 1)
            {

                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseSE = s;
            }

            ///POUR LA CASE DU SUD
            if(s->getX() == Case_actu->getX() && s->getY() == Case_actu->getY()+1  && s->getId() == 1)
            {

                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseS = s;
            }

            ///POUR LA CASE DU SUD OUEST
            if(s->getX() == Case_actu->getX()-1 && s->getY() == Case_actu->getY()+1  && s->getId() == 1)
            {
                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseSO = s;
            }

            ///POUR LA CASE DE L'OUEST
            if(s->getX() == Case_actu->getX()-1 && s->getY() == Case_actu->getY()  && s->getId() == 1)
            {

                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseO = s;
            }
        }

        ///Si cette case a déja été passé dessus, initialise la distance a beaucoup  ================
        if(preds[CaseNO->getY()][CaseNO->getX()]==false)
            CaseNO->setG(std::numeric_limits<int>::max());
        if(preds[CaseN->getY()][CaseN->getX()]==false)
            CaseN->setG(std::numeric_limits<int>::max());
        if(preds[CaseNE->getY()][CaseNE->getX()]==false)
            CaseNE->setG(std::numeric_limits<int>::max());
        if(preds[CaseE->getY()][CaseE->getX()]==false)
            CaseE->setG(std::numeric_limits<int>::max());
        if(preds[CaseSE->getY()][CaseSE->getX()]==false)
            CaseSE->setG(std::numeric_limits<int>::max());
        if(preds[CaseS->getY()][CaseS->getX()]==false)
            CaseS->setG(std::numeric_limits<int>::max());
        if(preds[CaseSO->getY()][CaseSO->getX()]==false)
            CaseSO->setG(std::numeric_limits<int>::max());
        if(preds[CaseO->getY()][CaseO->getX()]==false)
            CaseO->setG(std::numeric_limits<int>::max());



        nb_g = Case_actu->getG();

        if(premiere == true)
        {
         nb_g = 0;
        premiere = false;
        }

        if(CaseNO->getG() < nb_g)
            CaseNO->setG(std::numeric_limits<int>::max());
        if(CaseN->getG() < nb_g)
            CaseN->setG(std::numeric_limits<int>::max());
        if(CaseNE->getG() < nb_g)
            CaseNE->setG(std::numeric_limits<int>::max());
        if(CaseE->getG() < nb_g)
            CaseE->setG(std::numeric_limits<int>::max());
        if(CaseSE->getG() < nb_g)
            CaseSE->setG(std::numeric_limits<int>::max());
        if(CaseS->getG() < nb_g)
            CaseS->setG(std::numeric_limits<int>::max());
        if(CaseSO->getG() < nb_g)
            CaseSO->setG(std::numeric_limits<int>::max());
        if(CaseO->getG() < nb_g)
            CaseO->setG(std::numeric_limits<int>::max());


        ///Initialisation d'un vecteur F_comparaison qui va comparer tout les F ( F= G + H) précédement calculé)
        std::vector<float> F_comparaison;
        F_comparaison.push_back(CaseNO->getF());
        F_comparaison.push_back(CaseN->getF());
        F_comparaison.push_back(CaseNE->getF());
        F_comparaison.push_back(CaseE->getF());
        F_comparaison.push_back(CaseSE->getF());
        F_comparaison.push_back(CaseS->getF());
        F_comparaison.push_back(CaseSO->getF());
        F_comparaison.push_back(CaseO->getF());

        ///Programme trouvant le la plus petite valeur F dans le vecteur F_comparaison
        int petit=-1;
        float num_min = std::numeric_limits<int>::max();
        for(int i=0; i<F_comparaison.size(); i++) //Compare alors toutes les valeurs du tableau afin de récuperer le plus petit F
            if(F_comparaison[i]<num_min)
            {
                num_min=F_comparaison[i];
                petit = i;
            }

        ///La Case actuelle va donc prend la case dont le F est le plus petit
        if(petit == 0)
            Case_actu= CaseNO;
        if(petit == 1)
            Case_actu= CaseN;
        if(petit == 2)
            Case_actu= CaseNE;
        if(petit == 3)
            Case_actu= CaseE;
        if(petit == 4)
            Case_actu= CaseSE;
        if(petit == 5)
            Case_actu= CaseS;
        if(petit == 6)
            Case_actu= CaseSO;
        if(petit == 7)
            Case_actu= CaseO;

           ///Initialise donc la case actuelle a FALSE pour pas qu'on repasse dessus.
        preds[Case_actu->getY()][Case_actu->getX()]=false;




        ///PUSH_BACK les coordonnées X et Y dans le vecteur PCC (Plus court chemin)
        pair<int,int> tmp;
        tmp.first= Case_actu->getX() -1;
        tmp.second = Case_actu->getY() -1;
        PCC.push_back(tmp);

        ///FIN DE LA BOUCLE ?
        if(Case_actu->getX() == coo_arr.first && Case_actu->getY() == coo_arr.second)
            teo = false;
    }

    return PCC;
}

std::vector < pair<int,int> > Trajet::AStar2( pair<int,int> coo_dep, pair<int,int> coo_arr)
{

    ///Initialisation d'une porte
    bool teo = true;

    ///Blindage des valeurs : est -il sur le quadrillage ?
    if( coo_dep.first < 0 || coo_dep.first > 62)
    {
        std::cout << "L'avion n'est plus sur le quadrillage" << std::endl;
        teo=false;
    }
    if( coo_dep.second < 0 || coo_dep.second > 27)
    {
        std::cout << "L'avion n'est plus sur le quadrillage" << std::endl;
        teo=false;
    }
    if( coo_arr.first < 0 || coo_arr.first > 62)
    {
        std::cout << "L'avion n'est plus sur le quadrillage" << std::endl;
        teo=false;
    }
    if( coo_arr.second < 0 || coo_arr.second > 27)
    {
        std::cout << "L'avion n'est plus sur le quadrillage" << std::endl;
        teo=false;
    }

    ///On décale tout les valeurs de 1 ( qu'on remettra a la normal a la fin) permettant de ne pas "froller" le mur
    coo_dep.first = coo_dep.first+1;
    coo_dep.second = coo_dep.second+1;
    coo_arr.first = coo_arr.first+1;
    coo_arr.second = coo_arr.second+1;

    ///Initialisation de cases
    Case *Case_dep; //Case départ
    Case *Case_arr; //Case d'arrivé
    Case *Case_actu; //Case actuelle (case actu de Astar)

    ///INITIALISATION =============================================
    std::vector < pair<int,int> > PCC; ///Vecteur des plus court chemin qui seras retourné dans le main

    PCC.push_back(make_pair(coo_dep.first-1,coo_dep.second-1));

    ///Initialisation de chaque cases
    for(int j=0; j<32; j++)
        for(int i=0; i<65; i++)
            m_carte.push_back(new Case(i,j,1,std::numeric_limits<int>::max(),std::numeric_limits<int>::max()));


    ///INITIALISE LES PREDECESSEURS A FALSE
    std::vector < std::vector <bool>> preds;
    std::vector <bool> tmp_bool;
    for(int i=0; i<65; i++)
        tmp_bool.push_back(true);
    for(int i=0; i<32; i++)
        preds.push_back(tmp_bool);

    preds[coo_dep.second][coo_dep.first]=false; ///Initialisation de la case de bases

    ///INITIALISE LA LIMITE DU PLATEAU
    for(int i=0; i<28 ; i++)
        preds[i][0]=false;

    ///METTRE DES MUR ICI (par exemple à 5 20 =>  preds[20+1][5+1]=false;
    preds[5+1][0+2]=false;
    preds[5+1][0+1]=false;
    for (auto s : m_carte)  ///INITIALISATION DE LA PREMIERE CASE
    {
        if(coo_dep.first == s->getX() && coo_dep.second == s->getY() )
        {
            Case_dep = s;
            Case_actu = s;
        }

        if(coo_arr.first == s->getX() && coo_arr.second == s->getY() )
        {
            Case_arr = s;
        }
    }
    ///FIN INITIALISATION ==========================================

    ///Si la case de départ = case d'arrivé
    if(coo_dep.first == coo_arr.first && coo_dep.second == coo_arr.second)
    {
        std::cout << "L'avion fait du surplace ! " << std::endl;
        teo=false;
    }

bool premiere=true;

    ///PRINCIPALE BOUCLE DE ASTAR
    while(teo)
    {

    Case *CaseNO;
    Case *CaseN;
    Case *CaseNE;
    Case *CaseE;
    Case *CaseSE;
    Case *CaseS;
    Case *CaseSO;
    Case *CaseO;

    double nb_g=0;

        for (auto s : m_carte) ///Boucle for permettant de passer par les cases et trouver les cases voisin de la case actuelle
        {
            ///POUR LA CASE DU NORD OUEST
            if(s->getX() == Case_actu->getX()-1 && s->getY() == Case_actu->getY()-1 && s->getId() == 1)
            {
                s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseNO = s; ///CaseNO Prend cette valeur pour la comparaison plus tard

            }

            ///POUR LA CASE DU NORD
            if(s->getX() == Case_actu->getX() && s->getY() == Case_actu->getY()-1  && s->getId() == 1)
            {
                s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseN = s;
            }

            ///POUR LA CASE DU NORD EST
            if(s->getX() == Case_actu->getX()+1 && s->getY() == Case_actu->getY()-1  && s->getId() == 1)
            {

                s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseNE = s;
            }

            ///POUR LA CASE DE L'EST
            if(s->getX() == Case_actu->getX()+1 && s->getY() == Case_actu->getY()  && s->getId() == 1)
            {


                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseE = s;
            }

            ///POUR LA CASE DU SUD EST
            if(s->getX() == Case_actu->getX()+1 && s->getY() == Case_actu->getY()+1  && s->getId() == 1)
            {

                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseSE = s;
            }

            ///POUR LA CASE DU SUD
            if(s->getX() == Case_actu->getX() && s->getY() == Case_actu->getY()+1  && s->getId() == 1)
            {

                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseS = s;
            }

            ///POUR LA CASE DU SUD OUEST
            if(s->getX() == Case_actu->getX()-1 && s->getY() == Case_actu->getY()+1  && s->getId() == 1)
            {
                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseSO = s;
            }

            ///POUR LA CASE DE L'OUEST
            if(s->getX() == Case_actu->getX()-1 && s->getY() == Case_actu->getY()  && s->getId() == 1)
            {

                    s->setG(GetDistance(s,Case_dep)); //Calcul de la distance de G (G c'est la distance entre la cette case ci et la case de départ)
                s->setH(GetDistance(s,Case_arr)); //Calcul de la distance de H (G c'est la distance entre la cette case ci et la case d'Arrivé)
                ///s->setId(0); ///Bloque ce chemin
                CaseO = s;
            }
        }

        std::cout << "CASE G N " << CaseN->getG() << std::endl;


        ///Si cette case a déja été passé dessus, initialise la distance a beaucoup  ================
        if(preds[CaseNO->getY()][CaseNO->getX()]==false)
            CaseNO->setG(std::numeric_limits<int>::max());
        if(preds[CaseN->getY()][CaseN->getX()]==false)
            CaseN->setG(std::numeric_limits<int>::max());
        if(preds[CaseNE->getY()][CaseNE->getX()]==false)
            CaseNE->setG(std::numeric_limits<int>::max());
        if(preds[CaseE->getY()][CaseE->getX()]==false)
            CaseE->setG(std::numeric_limits<int>::max());
        if(preds[CaseSE->getY()][CaseSE->getX()]==false)
            CaseSE->setG(std::numeric_limits<int>::max());
        if(preds[CaseS->getY()][CaseS->getX()]==false)
            CaseS->setG(std::numeric_limits<int>::max());
        if(preds[CaseSO->getY()][CaseSO->getX()]==false)
            CaseSO->setG(std::numeric_limits<int>::max());
        if(preds[CaseO->getY()][CaseO->getX()]==false)
            CaseO->setG(std::numeric_limits<int>::max());



        nb_g = Case_actu->getG();
        std::cout <<"LOL " << nb_g << std::endl;

        if(premiere == true)
        {
         nb_g = 0;
        premiere = false;
        }

        if(CaseNO->getG() < nb_g)
            CaseNO->setG(std::numeric_limits<int>::max());
        if(CaseN->getG() < nb_g)
            CaseN->setG(std::numeric_limits<int>::max());
        if(CaseNE->getG() < nb_g)
            CaseNE->setG(std::numeric_limits<int>::max());
        if(CaseE->getG() < nb_g)
            CaseE->setG(std::numeric_limits<int>::max());
        if(CaseSE->getG() < nb_g)
            CaseSE->setG(std::numeric_limits<int>::max());
        if(CaseS->getG() < nb_g)
            CaseS->setG(std::numeric_limits<int>::max());
        if(CaseSO->getG() < nb_g)
            CaseSO->setG(std::numeric_limits<int>::max());
        if(CaseO->getG() < nb_g)
            CaseO->setG(std::numeric_limits<int>::max());



        ///Initialisation d'un vecteur F_comparaison qui va comparer tout les F ( F= G + H) précédement calculé)
        std::vector<float> F_comparaison;
        F_comparaison.push_back(CaseNO->getF());
        F_comparaison.push_back(CaseN->getF());
        F_comparaison.push_back(CaseNE->getF());
        F_comparaison.push_back(CaseE->getF());
        F_comparaison.push_back(CaseSE->getF());
        F_comparaison.push_back(CaseS->getF());
        F_comparaison.push_back(CaseSO->getF());
        F_comparaison.push_back(CaseO->getF());

        ///Programme trouvant le la plus petite valeur F dans le vecteur F_comparaison
        int petit=-1;
        float num_min = std::numeric_limits<int>::max();
        for(int i=0; i<F_comparaison.size(); i++) //Compare alors toutes les valeurs du tableau afin de récuperer le plus petit F
            if(F_comparaison[i]<num_min)
            {
                num_min=F_comparaison[i];
                petit = i;
            }

        ///La Case actuelle va donc prend la case dont le F est le plus petit
        if(petit == 0)
            Case_actu= CaseNO;
        if(petit == 1)
            Case_actu= CaseN;
        if(petit == 2)
            Case_actu= CaseNE;
        if(petit == 3)
            Case_actu= CaseE;
        if(petit == 4)
            Case_actu= CaseSE;
        if(petit == 5)
            Case_actu= CaseS;
        if(petit == 6)
            Case_actu= CaseSO;
        if(petit == 7)
            Case_actu= CaseO;

           ///Initialise donc la case actuelle a FALSE pour pas qu'on repasse dessus.
        preds[Case_actu->getY()][Case_actu->getX()]=false;




        ///PUSH_BACK les coordonnées X et Y dans le vecteur PCC (Plus court chemin)
        pair<int,int> tmp;
        tmp.first= Case_actu->getX() -1;
        tmp.second = Case_actu->getY() -1;
        PCC.push_back(tmp);

        ///FIN DE LA BOUCLE ?
        if(Case_actu->getX() == coo_arr.first && Case_actu->getY() == coo_arr.second)
            teo = false;
    }

    return PCC;
}

void Trajet::afficher_al()
{
    while(!key[KEY_ESC])
    {

    }
}


///POUR L'ALGORITHME DE A STAR
float Trajet::GetDistance(Case* Coo_dep, Case* Coo_arr)
{
    float a = Coo_arr->getX() - Coo_dep->getX();
    float b = Coo_arr->getY() - Coo_dep->getY();

    float a2 = pow(a,2);
    float b2 = pow(b,2);

    float c = sqrt (a2 + b2);

    return c;
}
