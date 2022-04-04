#include "header.h"


int main()
{
    Graphe g{"graphe1_TP2.txt"};
    ///appel de la méthode pour afficher le graphe
    int porte;

    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std::cout << "==================================================" << std::endl;
            std::cout << "Que voulez vous faire ?:" << std::endl;
            std::cout << "1: Afficher les aretes et les poids du graphes" << std::endl;
            std::cout << "2: Afficher les aretes triees en fonction du poids" << std::endl;
            std::cout << "3: Effectuer et afficher l'algorithme de KRUSKAL" << std::endl;
            std::cout << "0: Quitter" << std::endl;
            std::cin >> porte;
        }
        while(porte!=0&&porte!=1&&porte!=2&&porte!=3);

        if(porte==1||porte==2||porte==3)
            g.Kruskal(porte);

    }
    while(porte!=0);

    return 0;
}
