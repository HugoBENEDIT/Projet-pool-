#include "_header.h"

int main()
{
    ///Variables
    int sommet_ini, sommet_fin, menu2=1;
    int avion_num;
    int x=0;
    int condition=0;
    std::vector<int> previous;
    std::vector<Avion*> a;

    while (menu2 == 1)
    {
        Carte carte("avions.txt", "Aeroport.txt");
        menu(&carte);

        ///FIN DU CALCUL DU TRAJET ET AFFICHAGE POUR 1 AVION =================================================================
        std::cout <<std::endl;
        std::cout << "Voulez vous quitter le programme: 1. NON  2. OUI" << std::endl;
        std::cin >> menu2;

        ///Blindage
        while(menu2 > 2 || menu2 <1)
        {
            std::cout << "Erreur lors de la saisis !" << std::endl;
            std::cin >> menu2;
        }

        ///Arret pgrm
        if (menu2 == 2)
        {
            return 0;
        }
        std::cout << std::endl;
        system("cls");
    }
}
END_OF_MAIN()
