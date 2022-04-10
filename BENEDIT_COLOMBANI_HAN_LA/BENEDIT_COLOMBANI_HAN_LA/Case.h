#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

class Case
{
private:
    /*for(int i=0; i<=28 ; i++)
    line(c.get_bitmapp("Map"),368,302+(i*15),368+(15*63),302+(i*15),makecol(100,100,100));
    for(int i=0; i<=63 ; i++)
    line(c.get_bitmapp("Map"),368+(i*15),302,368+(i*15),302+(28*15),makecol(100,100,100));*/
    int m_x,m_y;
    int m_id;
    float m_G;
    float m_H;

public:

    Case() {}
    Case(int x, int y,int id, float G, float H)
    : m_x(x),m_y(y),m_id(id),m_G(G),m_H(H) {}
    ~Case() {}
    ///====================

    ///LES GETTERS
    int getX()
    {
        return m_x;
    }

    int getY()
    {
        return m_y;
    }

    int getId()
    {
        return m_id;
    }

    float getG()
    {
        return m_G;
    }

    float getH()
    {
        return m_H;
    }

    double getF()
    {
        return m_G + m_H;
    }

    //LES SETTERS
    void setG(float n)
    {
        m_G = n;
    }

    void setH(float n)
    {
        m_H = n;
    }

    void setId(int n)
    {
        m_id = n;
    }
};

#endif // CASE_H_INCLUDED
