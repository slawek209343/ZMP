#ifndef PROSTOPADLOSCIAN_HH
#define PROSTOPADLOSCIAN_HH

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

const Wektor3D &GetCenter() const;
const Wektor3D &GetSize() const;

};
const Wektor3D & Prostopadloscian::GetSize() const
{

	return _size;
}
const Wektor3D & Prostopadloscian::GetCenter() const
{
	return _center;
}


#endif