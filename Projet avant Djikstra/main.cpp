#include "header.h"

int main()
{
    int fin=0;
    Carte g{"avions.txt"};
    Carte c("Aeroport.txt");
    std::vector<Avion*> a;
    c.afficher1();
    g.afficher();
    a=g.getAvion();

    while(fin!=1)
    {
        int m;
        string m2;
        std::cout << std::endl;
        std::cout << "Sur quel avion voulez-vous modifier ? Tapez 1/2/3..."<<std::endl;
        int p;
        std::cin>>p;
        std::cout << "Modifier le type (1) la conso (2) ou la capacite (3)?"<<std::endl;
        int k;
        std::cin>>k;

        ///on peut modifier un attribut d'un avion
        if(k==1)
        {
            std::cout << "Saisir-> ";
            std::cin>>m2;
            a[p-1]->setType(m2);
        }
        else if(k==2)
        {
            std::cout << "Saisir-> ";
            std::cin>>m;
            a[p-1]->setConso(m);
        }
        else if(k==3)
        {
            std::cout << "Saisir-> ";
            std::cin>>m;
            a[p-1]->setCapacite(m);
        }


        std::cout << std::endl;
        for (int i=0; i < a.size(); ++i)
        {
            a[i]->aff();
        }

    }
    return 0;
}
