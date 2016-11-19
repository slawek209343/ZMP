#ifndef  ZARZADCAWTYCZEK_HH
#define  ZARZADCAWTYCZEK_HH
#include <map>
#include "Wtyczka.hh"


/*!
 * \file
 * \brief Definicja klasy ZarzadcaWtyczek.hh
 *
 * Plik zawiera definicję klasy WZarzadcaWtyczek.hh
 */
class ZarzadcaWtyczek
{
/*!
 * \brief mapa posiadajaca jako klucz string wskazujacy jak nazywa sie wtyczka
 *
 * na podstawie klucza otrzymujemy wskaznik na wlasciwy obiekt
 */
	map <string,Wtyczka> para;

public:

/*!
 * \brief dodaje do naszej mapy kolejne wtyczki
 *
 *\param referencja z utworzonej wczesniej wtyczki
 *\param string bedacy kluczem
 */	
	void dodaj(Wtyczka &wtyczka, std::string nazwa);
	~ZarzadcaWtyczek(){
		cout<<"Destruktor ZarzadcaWtyczek\n";
	};
/*!
 * \brief dodaje do naszej mapy kolejne wtyczki
 *
 *\param string bedacy kluczem, po ktorym szukamy
 *\return wskaznik na obiekt bedacy wtyczka
 */	
	Wtyczka & znajdz_wtyczke(std::string nazwa);


};

void ZarzadcaWtyczek::dodaj(Wtyczka &wtyczka, std::string nazwa)
{
	para[nazwa] = wtyczka;
	cout<<"Dodano do mapy wtyczke o nazwie "<<nazwa<<endl<<endl;

}
Wtyczka & ZarzadcaWtyczek::znajdz_wtyczke(std::string nazwa)
{
	return para[nazwa];

}

#endif