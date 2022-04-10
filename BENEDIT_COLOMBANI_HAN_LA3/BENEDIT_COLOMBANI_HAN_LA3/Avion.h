#ifndef AVION_H_INCLUDED
#define AVION_H_INCLUDED

class Avion
{

private :

    bool m_vol;
    std::string m_type;
    int m_conso;
    int m_capacite;

public :

    /*constructeur*/
    Avion() {}
    Avion(bool vol,std::string type, int conso, int capacite):m_vol(vol), m_type(type),m_conso(conso),m_capacite(capacite) {};

    /*accesseurs*/
    std::string getType()const;
    bool getvol();
    void setvol(bool oui);
    void setType(std::string type);
    void setConso(int conso);
    int getConso() const;
    void setCapacite(int capacite);
    int getCapacite() const;

    ///Méthodes///
    void aff();
};

#endif // AVION_H_INCLUDED
