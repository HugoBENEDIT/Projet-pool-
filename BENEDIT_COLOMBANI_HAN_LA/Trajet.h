#ifndef TRAJET_H_INCLUDED
#define TRAJET_H_INCLUDED

class Trajet
{
private:


    std::vector <Case*> m_carte;


public:

    Trajet() {};
    ~Trajet() {};

    ///Sous programme Astar qui va retourner un vecteur de pair ( les coo que l'avion fera)
    std::vector < pair<int,int> > AStar( pair<int,int> coo_dep, pair<int,int> coo_arr, int case_x, int case_y);
    std::vector < pair<int,int> > AStar2( pair<int,int> coo_dep, pair<int,int> coo_arr);
    float GetDistance(Case* Coo_dep, Case* Coo_arr);
    void afficher_al();



};















#endif // TRAJET_H_INCLUDED
