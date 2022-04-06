#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include <time.h>
#include <iostream>
#define SCREEN_H 800
#define SCREEN_W 1500


 void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}


int main()

{
    allegro_init();


    set_color_depth(desktop_color_depth());

    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,SCREEN_W,SCREEN_H,0,0))!=0)
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    install_keyboard();

     BITMAP *buffer = create_bitmap(SCREEN_W, SCREEN_H);

     BITMAP *avion_bd = load_bitmap("Avion_bd.bmp", NULL);
    if (!avion_bd)
    {
        allegro_message( "Avion_bd introuvable !" );
        exit( EXIT_FAILURE);
    }


     BITMAP *avion_b = load_bitmap("Avion_b.bmp", NULL);
    if (!avion_b)
    {
        allegro_message( "Avion_b introuvable !" );
        exit( EXIT_FAILURE);
    }


     BITMAP *avion_bg = load_bitmap("Avion_bg.bmp", NULL);
    if (!avion_bg)
    {
        allegro_message( "Avion_bg introuvable !" );
        exit( EXIT_FAILURE);
    }

     BITMAP *avion_g = load_bitmap("Avion_g.bmp", NULL);
    if (!avion_g)
    {
        allegro_message( "Avion_g introuvable !" );
        exit( EXIT_FAILURE);
    }
     BITMAP *avion_hg = load_bitmap("Avion_hg.bmp", NULL);
    if (!avion_hg)
    {
        allegro_message( "Avion_hg introuvable !" );
        exit( EXIT_FAILURE);
    }
     BITMAP *avion_h = load_bitmap("Avion_h.bmp", NULL);
    if (!avion_h)
    {
        allegro_message( "Avion_h introuvable !" );
        exit( EXIT_FAILURE);
    }
     BITMAP *avion_hd = load_bitmap("Avion_hd.bmp", NULL);
    if (!avion_hd)
    {
        allegro_message( "Avion_hd introuvable !" );
        exit( EXIT_FAILURE);
    }
     BITMAP *avion_d = load_bitmap("Avion_d.bmp", NULL);
    if (!avion_d)
    {
        allegro_message( "Avion_d introuvable !" );
        exit( EXIT_FAILURE);
    }


int coor_x = 750;
int coor_y = 400;
int coor_xa = 0;
int coor_ya = 0;
int vitesse = 5;
int frame = 1000;


     while(!key[KEY_ESC])
    {


        std::cout << "saisir coordonnées d arrivées x :"<< std::endl;
        std::cin>> coor_xa;
        std::cout << "saisir coordonnées d arrivées y :"<< std::endl;
        std::cin>> coor_ya;


        while((coor_x!=coor_xa)&&(coor_y!=coor_ya))
        {


        if((coor_xa < coor_x)&&(coor_ya<coor_y))
        {
           coor_x = coor_x - vitesse;
           coor_x = coor_y - vitesse;
           masked_blit(avion_bg, buffer, 0, 0, coor_x, coor_y, SCREEN_W, SCREEN_H);
          // delay(frame);
           std::cout<<"X : "<< coor_x<<"Y : "<<coor_y<< std::endl;
        }

         if((coor_xa > coor_x)&&(coor_ya<coor_y))
        {
           coor_x = coor_x + vitesse;
           coor_x = coor_y - vitesse;
           masked_blit(avion_bd, buffer, 0, 0, coor_x, coor_y, SCREEN_W, SCREEN_H);
            // delay(frame);
              std::cout<<"X : "<< coor_x<<"Y : "<<coor_y<< std::endl;
        }

         if((coor_xa > coor_x)&&(coor_ya>coor_y))
        {
           coor_x = coor_x + vitesse;
           coor_x = coor_y + vitesse;
           masked_blit(avion_hd, buffer, 0, 0, coor_x, coor_y, SCREEN_W, SCREEN_H);
            // delay(frame);
              std::cout<<"X : "<< coor_x<<"Y : "<<coor_y<< std::endl;
        }

         if((coor_xa < coor_x)&&(coor_ya > coor_y))
        {
           coor_x = coor_x - vitesse;
           coor_x = coor_y + vitesse;
           masked_blit(avion_hg, buffer, 0, 0, coor_x, coor_y, SCREEN_W, SCREEN_H);
             //delay(frame);
              std::cout<<"X : "<< coor_x<<" Y : "<<coor_y<<std::endl;
            }

        blit(buffer, screen, 0,0,0,0,SCREEN_W,SCREEN_H);
        }


    }
}END_OF_MAIN()

