#ifndef  WTYCZKA_HH
#define  WTYCZKA_HH
#include <iostream>
#include <dlfcn.h>
#include "Interp4Command.hh"
using namespace std;

/*!
 * \file
 * \brief Definicja klasy Wtyczka.hh
 *
 * Plik zawiera definicję klasy Wtyczka.hh
 */


/*!
 * \brief Przechowuje 2 wskazniki, jeden to uchwyt do pliku .so 
 *
 *  Klasa pelni rolę przechowalni wskaznikow dla bibliotek dynamicznych
 */
class Wtyczka
{
  
  /*!
 * \brief wskaznik typu Interp4Command
 *
 *  poprzez niego odnosimy sie do konkretnego obiektu
 */
  Interp4Command *_pInterp;

public:
  /*!
 * \brief wskaznik typu void, jako uchwyt pliku
 *
 */
  void * _pLibHandler;

	 /*!
 * \brief konstruktor bezparametryczny
 *
 *  wyswietla tekst kiedy jest wywolywany
 */

   Wtyczka(){
    cout<<"Wywolany konstruktor Wtyczek\n";
   }


  /*!
 * \brief destruktor klasy
 *
 *  wyswietla tekst kiedy jest wywolywany oraz zwalnia pamiec
 */
	~Wtyczka(){
    cout<<"dziala destruktor wtyczek\n";
  
    _pInterp = NULL;
    //delete _pInterp;
		dlclose(_pLibHandler);

		
  }
 /*!
 * \brief aktualizuje wskazniki klasy o konkretne wartosci z zadanej wtyczki
 *
 *  dodawanie dynamiczne biblioteki
 */
	void dodaj_wtyczke();

 /*!
 * \brief zwraca wskaznik do konkretnej wtyczki, jako ze jest on zmienna prywatna
 *
 *  /return wskaznik na obiekt bedacy jedna z wtyczek
 */
  Interp4Command* zwroc_pInterp()
  {
    return _pInterp;
  }

};



void Wtyczka::dodaj_wtyczke()
{

  Interp4Command *(*pCreateCmd)(void);
  void *pFun;

  if (!_pLibHandler) {
    cerr << "!!! Brak biblioteki: Tylko ktora to" << endl;

  }
  pFun = dlsym(_pLibHandler,"CreateCmd");
  if (!pFun) {
    cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;

  }

  pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);


  _pInterp = pCreateCmd();
}


#endif