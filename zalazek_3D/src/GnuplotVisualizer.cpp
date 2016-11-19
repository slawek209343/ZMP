#include "GnuplotVisualizer.hh"
#include <fstream>
#include <iostream>
#include "Wektor3D.hh"

using namespace std;

/*!
 * Konstruktor inicjalizuje pracę z programem gnuplot.
 * Na potrzeby tej inicjalizacji wykonane są następujące operacje:
 * 
 * \li Kasowanie zawartości plików, których nazwy zdefiniowane są poprzez stałe
 *   \link GnuplotVisualizer.hh::FILE_NAME__TRAJECTORY FILE_NAME__TRAJECTORY\endlink
 *   oraz 
 *   \link GnuplotVisualizer.hh::FILE_NAME__DRON_BODY_VIEW FILE_NAME__DRON_BODY_VIEW\endlink.
 *   W pierwszym z plików zapisywane są współrzędne wierzchołków łamanej modelującej
 *   ścieżkę przelotu drona. W drugim natomiast są zapisywane współrzędne aktualnego
 *   widoku bryły reprezentującej korpus drona.
 *
 * \li Inicjacja pracy programu gnuplot.
 *
 * \li Dodanie nazw plików, z których będą czytane dane przy każdorazowym odrysowaniu
 *     rysunku.
 *
 * \li Ustawienie trybu rysowania jako rysowanie przestrzenne 3D.
 *
 * \li Wstępne ustawienie zakresu współrzędnych rysowanej sceny.
 *     Te zakresy należy dostosować do potrzeb własnego programu.
 *
 * \li Wstępne ustawienie kierunku, z którego widziana jest scena.
 *     W trakcie pracy aplikacji kierunek ten można modyfikować
 *     wykorzystując kursor myszki.
 */
GnuplotVisualizer::GnuplotVisualizer()
{
  ofstream  Strm;
  Strm.open(FILE_NAME__TRAJECTORY);      Strm.close();  // Kasujemy poprzednia
  Strm.open(FILE_NAME__DRON_BODY_VIEW);  Strm.close();  // zawartość

  Plotter.Inicjalizuj(); 
  Plotter.DodajNazwePliku(FILE_NAME__TRAJECTORY);
  Plotter.DodajNazwePliku(FILE_NAME__DRON_BODY_VIEW);

  Plotter.ZmienTrybRys(PzG::TR_3D);
  Plotter.UstawZakresX(-100, 250);
  Plotter.UstawZakresY(-100, 250);
  Plotter.UstawZakresZ(-100, 200);
  Plotter.UstawRotacjeXZ(40,60); 
}

/*!
 * Dodaje do pliku, którego nazwa jest zdefinowana
 * przez stałą 
 * \link Visualization.hh::FILE_NAME__DRON_BODY_VIEW
 *                                     FILE_NAME__DRON_BODY_VIEW\endlik,
 * współrzędne następnego punktu ścieżki ruchu drona.
 */
bool AddTrajectoryPoint( const DronPose *pPose )
{
  ofstream  OuStrm(FILE_NAME__TRAJECTORY,ios::app);
  if (!OuStrm.is_open()) {
    cerr << " Blad otwarcia do zapisu pliku \"" FILE_NAME__TRAJECTORY "\""
	 << endl;
    return false;
  }
  OuStrm << pPose->GetPos_m() << endl;
  return true;
}


/*!
 * Zapisanie pliku z zaktualnymi współrzędnymi wierzchołków bryły
 * opisującej drona.
 * Ze względu na specyfikę sposobu rysowania powierzchni przez program gnuplot,
 * format wejściowy i wyjściowy pliku musi zostać zachowany, tzn. muszą być
 * zachwane przerwy w postaci wolnych linii między kolejnymi zbiorami wierzchołków,
 * które stanowią tworzącą rysowanej siatki danej powierzchni.
 * Ta funkcja to zapewnia.
 * \param[in] pPose - wskaźnik na obiekt zawierający dane dotyczące aktualnej pozy
 *                    drona.
 *
 * \warning W tej funkcji brakuje uwzględnienia rotacji, która pozwoli odzwierciedlić
 *          aktualną orientację drona. W kodzie funkcji jest zaznaczone miejsce,
 *          w którym należy wpisać odpowiedni kod.
 *
 */
bool WriteCurrDonPose( const DronPose *pPose )
{
  ofstream  OuStrm(FILE_NAME__DRON_BODY_VIEW);
  ifstream  InStrm(FILE_NAME__DRON_BODY_TEMPLATE);
  Wektor3D  Pos;
  //DronPose Dron;

  

  if (!OuStrm.is_open()) {
    cerr << " Blad otwarcia do zapisu pliku \"" FILE_NAME__DRON_BODY_VIEW "\""
	 << endl;
    return false;
  }
  if (!InStrm.is_open()) {
    cerr << " Blad otwarcia do odczytu pliku \"" FILE_NAME__DRON_BODY_TEMPLATE "\""
	 << endl;
    return false;
  }

  char      Separator;
 
  while (!InStrm.eof()) {
    if (InStrm >> Pos) {
      // 
      // Przed translacją trzeba dokonać właściwej rotacji, aby uwzględnić aktualną
      // orientację drona. Dla ułatwienia przyjmujemy, że uwzględniamy tylko orientację
      // w płaszczyźnie 0XY.
      // 
      // Tutaj więc należy dopisać kod rotacji
      //
      //Dron.SetAngle_deg( pPose->GetAngle_deg());
      //Pos += pPose->GetPos_m();
      OuStrm << Pos << endl;
      continue;
    }
    InStrm.clear();
    if (!(InStrm >> Separator)) break;
    if (Separator != '#') {
      cerr << " Blad w pliku \"" FILE_NAME__DRON_BODY_TEMPLATE "\"" << endl
           << " oczekiwano znaku #. Zamiast tego odebrano znak " << Separator
	   << endl;
      return false;
    }
    OuStrm << "#\n\n";
  }
  return true;
}



/*!
 * Powoduje dopisanie aktualnej współrzędnej drona do pliku,
 * w którym zawarta jest sekwencja wcześniejszych położeń.
 * W ten sposób otrzymana łamana reprentuje trajektorię ścieżkę
 * lotu drona.
 * Ponadto na podstawie pliku wzorcowego opisującego korpus drona,
 * utworzony zostaje plik ze współrzędnymi wierzchołków w jego
 * nowej pozycji. Po tej pozycji następuje odrysowanie drona
 * w jego aktulanej pozycji.
 *
 * \param[in] pPose - wskaźnik na obiekt zawierający dane dotyczące aktualnej pozy
 *                    drona.
 */
void GnuplotVisualizer::Draw( const DronPose *pPose )
{
  AddTrajectoryPoint(pPose);
  WriteCurrDonPose(pPose);
  Plotter.Rysuj();
}
