#include "_header.h"

int Aeroport::get_nom() const
{
    return m_nom;
}

std::string Aeroport::get_prenom() const
{
    return m_prenom;
}

int Aeroport::get_x () const
{
    return m_x;
}

int Aeroport::get_y () const
{
    return m_y;
}

int Aeroport::get_pistes() const
{
    return m_nb_piste;
}

int Aeroport::get_places() const
{
    return m_nb_places_sol;
}

int Aeroport::get_delai() const
{
    return m_delai_attente_sol;
}

int Aeroport::get_temps() const
{
    return m_temps_acces_pistes;
}

int Aeroport::get_anticollision() const
{
    return m_delai_anticollision;
}

int Aeroport::get_decat() const
{
    return m_temps_DECAT;
}

int Aeroport::get_duree() const
{
    return m_duree_boucle;
}

const std::vector<std::pair<const Aeroport*, int>>& Aeroport::getSuccesseurs()const
{
    return m_distance;
}

int Aeroport::getSuccesseurs_nom(int nom)
{
    for(std::map<const Aeroport*, int>::iterator it = m_distance1.begin(); it!=m_distance1.end(); ++it)
    {
        if(it->first->get_nom() == nom)
        {
            return it->second;
        }
    }
}

void Aeroport::ajouterSucc(const Aeroport*s, int m_p)
{
    std::pair<const Aeroport*, int> Suc;
    Suc.first=s;
    Suc.second=m_p;
    m_distance.push_back(Suc);
    m_distance1[s]=m_p;
}

void Aeroport::setMarque(int marque)
{
    m_marque=marque;
}

int Aeroport::getMarque() const
{
    return m_marque;
}

void Aeroport::setP(int p)
{
    if(m_p>p || m_p==-1) m_p=p;
    //std::cout << "TEST" << std::endl;
}

int Aeroport::getP() const
{
    return m_p;
}

void Aeroport::aff()
{
    std::cout << "Numero de l'aeroport : " << m_nom << std::endl;
    std::cout << "Nom de l'aeroport : " << m_prenom << std::endl;
    std::cout << "Position de l'aeroport : [" << m_x << "] [" << m_y << "]" << std::endl;
    std::cout << "Nombre de pistes : " << m_nb_piste << std::endl;
    std::cout << "Nombre de places au sol : " << m_nb_places_sol << std::endl;
    std::cout << "Delai attente au sol : " << m_delai_attente_sol << std::endl;
    std::cout << "Temps d'acces aux pistes : " << m_temps_acces_pistes << std::endl;
    std::cout << "Delai anticollision : " << m_delai_anticollision << std::endl;
    std::cout << "Temps Decollage/Atterissage : " << m_temps_DECAT << std::endl;
    std::cout << "Duree boucle d'attente : " << m_duree_boucle << std::endl;
    for (std::map<const Aeroport*, int>::iterator it=m_distance1.begin(); it!=m_distance1.end(); ++it)
        std::cout<< "Aeroport : " << m_prenom << " vers " <<it->first->get_prenom() <<" distance ==> " << it->second << std::endl;
    std::cout << std::endl << std::endl;
}
