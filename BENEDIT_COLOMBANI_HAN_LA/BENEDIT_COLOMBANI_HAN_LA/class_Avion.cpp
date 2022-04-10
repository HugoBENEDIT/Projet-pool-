#include "_header.h"

std::string Avion::getType()const
{
    return m_type;
}

bool Avion::getvol()
{
    return m_vol;
}

void Avion::setvol(bool oui)
{
    m_vol = oui;
}

void Avion::setType(std::string type)
{
    m_type=type;
}

void Avion::setConso(int conso)
{
    m_conso=conso;
}

int Avion::getConso() const
{
    return m_conso;
}

void Avion::setCapacite(int capacite)
{
    m_capacite=capacite;
}

int Avion::getCapacite() const
{
    return m_capacite;
}

void Avion::aff()
{
    std::cout << "Type d'avion: " << getType() << " courrier" << "  |  consommation: "<< getConso() <<" L/100km"<< "  |  capacite carburant: " << getCapacite() <<" L" << std::endl;
}
