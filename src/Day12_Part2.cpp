//============================================================================
// Name        : Adventofcode.cpp
// Author      : Stamatis Chiotis
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <exception>
#include <memory>
#include <algorithm>

#include <csignal>


struct Position
{
public:
    Position()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    
    Position(int px, int py, int pz)
    {
        x = px;
        y = py;
        z = pz;
    }
    
    Position(Position const& p)
    {
        x = p.x;
        y = p.y;
        z = p.z;
    }
    
    ~Position() = default;

    Position &operator=(Position const& other) 
    {
        // Use copy and swap idiom to implement assignment.
        Position copy(other);
        std::swap(*this, copy);
        return *this;
    }
    
    bool operator==(Position& p)
    {
        if (x == p.x && y == p.y && z == p.z)
        {
            return true;
        }
        return false;
    }
    
    Position operator()(Position& p)
    {
        Position p_temp;
        p_temp.x = p.x;
        p_temp.y = p.y;
        p_temp.z = p.z;
        
        return p_temp;
    }

    int x, y, z;
    
};

struct Velocity
{
public:
    Velocity()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    
    Velocity(int vx, int vy, int vz)
    {
        x = vx;
        y = vy;
        z = vz;
    }
    
    Velocity(Velocity const& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    
    ~Velocity() = default;
        
    Velocity &operator=(Velocity const& other) 
    {
        // Use copy and swap idiom to implement assignment.
        Velocity copy(other);
        std::swap(*this, copy);
        return *this;
    }
    
    bool operator==(Velocity& v)
    {
        if (x == v.x && y == v.y && z == v.z)
        {
            return true;
        }
        return false;
    }
    
    Velocity operator()(Velocity& v)
    {
        Velocity v_temp;
        v_temp.x = v.x;
        v_temp.y = v.y;
        v_temp.z = v.z;
        
        return v_temp;
    }
    
    int x, y, z;
};

class Moon
{
public:
    Moon() : p(0, 0, 0), v(0, 0, 0) {}
    Moon(int x, int y, int z) : p(x, y, z), v(0, 0, 0) {}
    Moon(const Moon& m) : p(m.p), v(m.v) {}
    ~Moon(){}
    Moon &operator=(Moon const& other) 
    {
        // Use copy and swap idiom to implement assignment.
        Moon copy(other);
        std::swap(*this, copy);
        return *this;
    }
    
    bool operator==(Moon& m1)
    {
        if (m1.p == this->p && m1.v == this->v)
        {
            return true;
        }
        return false;
    }
    
    Position p;
    Velocity v;

};


void ApplyGravity(Moon& m1, Moon& m2)
{
    if (m1.p.x > m2.p.x)
    {
        m1.v.x--;
        m2.v.x++;
    }
    else if (m1.p.x < m2.p.x)
    {
        m1.v.x++;
        m2.v.x--;
    }
    
    if (m1.p.y > m2.p.y)
    {
        m1.v.y--;
        m2.v.y++;
    }
    else if (m1.p.y < m2.p.y)
    {
        m1.v.y++;
        m2.v.y--;
    }
    
    if (m1.p.z > m2.p.z)
    {
        m1.v.z--;
        m2.v.z++;
    }
    else if (m1.p.z < m2.p.z)
    {
        m1.v.z++;
        m2.v.z--;
    }

}

void UpdateVelocity(std::vector<Moon>& moons)
{
    for (auto i = 0; i < moons.size() - 1; i++)
    {
        for (auto j = 1; j < moons.size(); j++)
        {
            if(j > i)
            {
                ApplyGravity(moons[i], moons[j]);
            }
        }
    }
}

void ApplyVelocity(Moon& m)
{
    m.p.x += m.v.x;
    m.p.y += m.v.y;
    m.p.z += m.v.z;
}

void UpdatePosition(std::vector<Moon>& moons)
{
    for (auto i = 0; i < moons.size(); i++)
    {
        ApplyVelocity(moons[i]);
    }
}


void TimeStep(std::vector<Moon>& moons)
{    
    UpdateVelocity(moons);
    UpdatePosition(moons);

//     return moons;
}

uint64_t CalculatePotentialEnergy(const Moon& m)
{
    return abs(m.p.x) + abs(m.p.y) + abs(m.p.z);
}

uint64_t CalculateKineticEnergy(const Moon& m)
{
        return abs(m.v.x) + abs(m.v.y) + abs(m.v.z);
}

uint64_t CalculateTotalEnergy(const Moon& m)
{
    return CalculatePotentialEnergy(m) * CalculateKineticEnergy(m);
}


int main()
{
    Moon Io(-16, -1, -12);
    Moon Europa(0, -4, -17);
    Moon Ganymede(-11, 11, 0);
    Moon Callisto(2, 2, -6);
    

//     <x=-1, y=0, z=2>
//     <x=2, y=-10, z=-7>
//     <x=4, y=-8, z=8>
//     <x=3, y=5, z=-1>


//     Moon Io(-1, 0, 2);
//     Moon Europa(2, -10, -7);
//     Moon Ganymede(4, -8, 8);
//     Moon Callisto(3, 5, -1);

    std::vector<Moon> moons{ Io, Europa, Ganymede, Callisto};
    std::vector<Moon> moons_first(moons);
//     std::vector<std::vector<Moon>> v_moons{ moons };

    uint64_t step = 0;
    while(1)
    {
//         if (step == 4686774923)
//         {
//             std::raise(SIGINT);
//         }
//         v_moons.emplace_back(TimeStep(moons));
        TimeStep(moons);
        step++;
//         std::cout<< "step: " << step << std::endl;
//         for (uint64_t i = 0; i < v_moons.size() - 1; i++)
//         {
//             if (v_moons[i][0] == v_moons.back()[0] && v_moons[i][1] == v_moons.back()[1] &&
//                 v_moons[i][2] == v_moons.back()[2] && v_moons[i][3] == v_moons.back()[3])
        if (moons[0] == moons_first[0] && moons[1] == moons_first[1] &&
            moons[2] == moons_first[2] && moons[3] == moons_first[3])
        {
            std::cout << "final step: " << step << std::endl;
            return 0;
        }
//         }
    }
    
    
}

