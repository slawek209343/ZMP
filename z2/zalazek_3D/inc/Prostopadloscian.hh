#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH
#include <string>
#include "Wektor3D.hh"
#include "Cuboid.hh"
#include <string>

using namespace std;


class Prostopadloscian: public Cuboid
{
public:
	string _name;
    Wektor3D _center;
    Wektor3D _size;


public:
    char *nazwa;

const Wektor3D &GetCenter() const{
 return _center;
}
const Wektor3D &GetSize() const{
 return _size;
}

};




#endif