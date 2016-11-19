#ifndef  COMMAND4TURN_HH
#define  COMMAND4TURN_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Fly
 *
 * Plik zawiera definicję klasy Interp4Fly ...
 */

/*!
 * \brief Modeluje polecenie dla robota mobilnego, które wymusza jego ruch do przodu
 *
 *  Klasa modeluje ...
 */
class Interp4Turn: public Interp4Command {
  /*!
   * \brief zmienne przechowujace paramtry lotu drona
   * Dla polecenia Turn sa to predkosc [m/s], przebyta droga [m], oraz promien krzywizny [m]
   */
  double  _Speed;
  double  _Distance;
  double  _Radius;
 public:
  /*!
   * \brief konstruktor naszej klasy inicjalizowany za pomoc listy inicjalizacyjnej
   */
  Interp4Turn();  
  /*!
   * \brief wyswietla nazwe polecenia i wartosci jego parametrow
   * przykladowo dla polecenia Fly zostanie wyswietlony poniszczy tekst w postaci:
   * Fly 3 1 20.
   */
  virtual void PrintCmd() const;
  /*!
   * \brief funkcja wyswietla nazwe i skladanie danego polecenia, np.:
   * Fly speed_hor[m/s]  speed_ver[m/s]  dst[m]
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief zwraca wskaznik do napisu w przypadku Fly bedzie to napis "Fly"
   * \return zwraca wskaznik do napisu bedacego nazwa danego polecenia.
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief wykonuje dane polecenie. Parametry metody maja nastepujace znaczenia:
   *pDronPose - wskaznik na obiekt w ktorym zapisane jest polozenie i orientacja drona. 
   * W momencie wywolania struktura zawiera poczatkowa pozycje drona. Po zakonczeniu dane w strukturze sa aktualizowane.
   *\return  true- jesli operacja zakonczyla sie powodzeniem, false w przeciwnym wypadku
   */
  virtual bool ExecCmd( DronPose  *pRobPose,   Visualization *pVis) const;
  /*!
   * \brief funkcja wczytuje z ciagu tekstowego liste parametrow 
   * \param strumien wejsciowy istream zawierajacy polecenia dla drona
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief funkcja wyswietla jakiego typu dane sa uzywane do sterowania dronem oraz wyswietla w jakich jednostkach
   */
  virtual void PrintParams() {}
  /*!
   * \brief
   *
   *  Ta metoda nie musi być zdefiniowna w klasie bazowej.
   */
  static Interp4Command* CreateCmd();
 };

#endif
