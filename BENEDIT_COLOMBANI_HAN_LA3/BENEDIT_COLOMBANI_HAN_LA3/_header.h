#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <allegro.h>
#include <cmath>
#include <fstream>
#include <utility>
#include <limits>   // Mettre la valeur "infinie"         std::numeric_limits<int>::max()



using namespace std;

#include "Aeroport.h"
#include "Case.h"
#include "Trajet.h"
#include "Avion.h"
#include "Carte.h"


#define ecran_x 1600
#define ecran_y 900
#define M_PI 3.14159265358979323846


///======================================================
void aff(size_t num,size_t fin,const std::vector<int>& graph,const std::vector<int>& p, int &nbr, std::vector<int>& sommets);
void delay(unsigned int mseconds);
int calcul_ang(pair<int,int> case_dep, pair<int,int> case_arr);
void menu(Carte *carte);
///======================================================



#endif // _HEADER_H_INCLUDED
