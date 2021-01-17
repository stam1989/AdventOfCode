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


constexpr int STEPS = 1000;

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
    
    
    
    Position p;
    Velocity v;

};


void ApplyGravity(std::shared_ptr<Moon>& m1, std::shared_ptr<Moon>& m2)
{
    if (m1->p.x > m2->p.x)
    {
        m1->v.x--;
        m2->v.x++;
    }
    else if (m1->p.x < m2->p.x)
    {
        m1->v.x++;
        m2->v.x--;
    }
    
    if (m1->p.y > m2->p.y)
    {
        m1->v.y--;
        m2->v.y++;
    }
    else if (m1->p.y < m2->p.y)
    {
        m1->v.y++;
        m2->v.y--;
    }
    
    if (m1->p.z > m2->p.z)
    {
        m1->v.z--;
        m2->v.z++;
    }
    else if (m1->p.z < m2->p.z)
    {
        m1->v.z++;
        m2->v.z--;
    }

}

void UpdateVelocity(std::vector<std::shared_ptr<Moon>>& moons)
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

void ApplyVelocity(std::shared_ptr<Moon>& m)
{
    m->p.x += m->v.x;
    m->p.y += m->v.y;
    m->p.z += m->v.z;
}

void UpdatePosition(std::vector<std::shared_ptr<Moon>>& moons)
{
    for (auto i = 0; i < moons.size(); i++)
    {
        ApplyVelocity(moons[i]);
    }
}


void TimeStep(std::vector<std::shared_ptr<Moon>>& moons)
{    
    UpdateVelocity(moons);
    UpdatePosition(moons);
}

uint64_t CalculatePotentialEnergy(const std::shared_ptr<Moon>& m)
{
    return abs(m->p.x) + abs(m->p.y) + abs(m->p.z);
}

uint64_t CalculateKineticEnergy(const std::shared_ptr<Moon>& m)
{
        return abs(m->v.x) + abs(m->v.y) + abs(m->v.z);
}

uint64_t CalculateTotalEnergy(const std::shared_ptr<Moon>& m)
{
    return CalculatePotentialEnergy(m) * CalculateKineticEnergy(m);
}


int main()
{
    
    std::shared_ptr<Moon> Io(std::make_shared<Moon>(-16, -1, -12));
    std::shared_ptr<Moon> Europa(std::make_shared<Moon>(0, -4, -17));
    std::shared_ptr<Moon> Ganymede(std::make_shared<Moon>(-11, 11, 0));
    std::shared_ptr<Moon> Callisto(std::make_shared<Moon>(2, 2, -6));
    
    std::vector<std::shared_ptr<Moon>> moons{ Io, Europa, Ganymede, Callisto};
    
    for(auto step = 0; step < STEPS; step++)
    {
        TimeStep(moons);
    }
    
    uint64_t system_total_energy = 0;
    for (auto const& moon : moons)
    {
        system_total_energy += CalculateTotalEnergy(moon);
    }
    
    std::cout << "System's total energy is: " << system_total_energy << std::endl;
    
	return 0;
}
