#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <iomanip>
#include <string>
#include <sstream>





#include "Interp4Command.hh"
#include "Wtyczka.hh"
#include "ZarzadcaWtyczek.hh"
#include "GnuplotVisualizer.hh"
//#include "scene.hh"



#define LINE_SIZE 500
using namespace std;


/*!
 * Czyta z pliku opis sceny i zapisuje stan sceny do parametru,
 * który ją reprezentuje.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param Scn - (\b we.) reprezentuje scenę, na której ma działać robot.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
 






   /*!
    * \brief wywoluje menu obslugi polecen dla drona
    * Po wybraniu zadanej opcji realizowane sa zadania zgodnie z opisem
    */
  void menu(); 

  void pokaz_wtyczki();

   /*!
    * \brief pobiera od uzytkownika nazwe pliku 
    * Nastepnie z tego pliku beda czytane polecenia dla drona
    */
  void wczytaj();


   /*!
    * \brief realizuje obbliczanie i pozycji drona oraz jej rysowanie
    * Po każdorazowym wczytaniu jednej linijki danych obliczana, a takze wyrysowywana 
    * aktualna pozycja drona
    */
  void start();

   /*!
    * \brief wypisuje na konsoli zawartosc pliku tekstowego z ktorego pobieramy komendy dla drona
    */
  void pokaz_sekwencje();

   

    /*!
    * \brief zmienna zawiera nazwe pliku z poleceniami dla drona
    * Domyslnie jest to plik data.txt, lecz mozna go zmienic za pomoca funkcji wczytaj()
    */

    std::string nazwa_pliku = "data.txt";
    istringstream preprocesor;


    bool ExecPreprocesor( const char * NazwaPliku, istringstream &IStrm4Cmds )
    {
      string Cmd4Preproc = "cpp -P ";
      char Line[LINE_SIZE];
      ostringstream OTmpStrm;

      Cmd4Preproc += NazwaPliku;
      FILE *pProc = popen(Cmd4Preproc.c_str(),"r");
      if(!pProc)
        return false;
      while(fgets(Line,LINE_SIZE,pProc))
        OTmpStrm<<Line;
      IStrm4Cmds.str(OTmpStrm.str());
      return pclose(pProc) == 0;


    }

    /*bool String2Double(const *char sNumText, double &Val)
    {
      istringstream IStrm (sNumText);
      if(!(IStrm >> Val)) 
        return false;
      char Ch;
      if(Strm >> Ch)
        return false;

      return true;
    }*/



int main()
{

  menu();
   /*!
    * \brief Udostępnia wartości współrzędnych pozy robota
    *\param[in] angle_deg - ustawiana wartość kąta orientacji 
    *  Udostępnia wartości współrzędnych kartezjańskich pozycji
    *  oraz kąt orientacji robota.
    *  \return Bieżące współrzędne położenia drona.
    */

  



  return 0;


}

void menu()
{
  char znak;
  cout<<"Witaj w menu obslugi polecen DRONA\n\
w - wczytanie nazwy pliku sekwencji instrukcji dla drona\n\
p - pokaz sekwencje instrukcji\n\
i - pokaz dostepne instrukcje/wtyczki\n\
s - start wykonywania sekwencji instrukcji\n\
a - dodaj nowa wtyczke\n\
d - usun wtyczke\n\
? - wyswietl ponownie Menu\n\n\
k - koniec dzialania programu\n\n\
Jaki jest Twoj wybor (?-Menu): ";

cin>>znak;
switch(znak)
{
  case 'a':
  //Add_Rotate();
  menu();
  break;

  case 'i':
 // pokaz_wtyczki();
  menu();
  break;

  case 'p':
  pokaz_sekwencje();
  menu();
  break; 

  case 's':
  start();
  menu();
  break;

  case 'w':
  wczytaj();
  menu();
  break;

  case '?':
  menu();
  break;

  case 'k':
  cout<<"Koniec programu\n";
  break;


  default:
  cout<<"Zly wybor, ponow go\n";
  menu();
  break;

}


}
/*
void pokaz_wtyczki()
{
  if(Fly)
    pCmd->PrintSyntax();
  if(Turn)
    pCmd_Turn->PrintSyntax();
  /*if(Rotate)
    pCmd_Rotate->PrintSyntax();

}
*/
void pokaz_sekwencje()
{
  std::ifstream plik;
  plik.open( nazwa_pliku);
  if( !plik.good() )
      cerr<<"Brak pliku o takiej nazwie\n";
    
  std::string wiersz;
  while( std::getline( plik, wiersz ) )
      std::cout << wiersz << std::endl;
    
  plik.close();


}
void wczytaj()
{
  
  cout<<"Podaj nazwe pliku, ktory chcesz otworzyc\n";
  //cin>>nazwa_pliku;
  ExecPreprocesor(nazwa_pliku.c_str(),preprocesor);
  cout<<"Pomyslnie wybrano plik do wczytania.\n";


}

void start()
{

  DronPose DPose;
  GnuplotVisualizer PlotVis;
  //Scene Scena;

  DPose.SetPos_m(0,0,0);
  PlotVis.ReadScene("scene.xml"); // Ta metoda w tej chwili tylko udaje, że czyta
  PlotVis.Draw(&DPose);




  cout<<"Tworzenie wtyczki ROTATE, powtarzam ROTATE\n\n";
  Wtyczka Rotate;
  Rotate._pLibHandler = dlopen("Interp4Rotate.so",RTLD_LAZY);
  Rotate.dodaj_wtyczke();

  cout<<"Tworzenie wtyczki TURN, powtarzam TURN\n\n";
  Wtyczka Turn;
  Turn._pLibHandler = dlopen("Interp4Turn.so",RTLD_LAZY);
  Turn.dodaj_wtyczke();

  cout<<"Tworzenie wtyczki FLY, powtarzam FLY\n\n";    
  Wtyczka Fly;
  Fly._pLibHandler = dlopen("Interp4Fly.so",RTLD_LAZY);
  Fly.dodaj_wtyczke();


  ZarzadcaWtyczek Menedzer;

  Menedzer.dodaj(Rotate,"ROTATE");

  Menedzer.dodaj(Turn,"TURN");

  Menedzer.dodaj(Fly,"FLY");


  cout << "Aby rozpoczac lot, nacisniecie klawisza ENTER" << endl;
  cin >> skipws;
  cin.ignore(100000,'\n');

  std::ifstream plik;

  /*plik.open(nazwa_pliku);

  if( !plik.good() )
    cerr<<"Brak pliku o takiej nazwie\n";
    */
  std::string wiersz;
    

  while(!preprocesor.eof())
  {
    
    
    preprocesor>>wiersz;
    //plik>>wiersz;

    //if(preprocesor.eof())
    //  break;

    Menedzer.znajdz_wtyczke(wiersz).zwroc_pInterp()->PrintSyntax();
    Menedzer.znajdz_wtyczke(wiersz).zwroc_pInterp()->ReadParams(preprocesor);
    Menedzer.znajdz_wtyczke(wiersz).zwroc_pInterp()->ExecCmd(&DPose,&PlotVis); // Wykonanie polecenia wraz z jego wizualizacją

  }

  cout << "Aby zakonczyc, nacisniecie klawisza ENTER" << endl;
  cin.ignore(100000,'\n');
    
  preprocesor.clear();
//  plik.close();


}


/*

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

#include <iostream>
#include <list>
#include "scene.hh"
#include "xmlparser4scene.hh"

using namespace std;
using namespace xercesc;





/*!
 * Czyta z pliku opis sceny i zapisuje stan sceny do parametru,
 * który ją reprezentuje.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param Scn - (\b we.) reprezentuje scenę, na której ma działać robot.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
 /*
bool ReadFile(const char* sFileName, Scene& Scn)
{
   try {
            XMLPlatformUtils::Initialize(); //inicjalizacja biblioteki Xerces
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader(); // Tworzenie obiektu parsera, i ustawieie własności

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);

   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

   DefaultHandler* pHandler = new XMLParser4Scene(Scn); // Tworzenia handlera zdarzeń
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {
    // Wczytanie gramatyki
     if (!pParser->loadGrammar("grammar/scene.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/scene.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName); //ustawienie parsera
   }
   catch (const XMLException& Exception) {  //Przechwytywanie wyjątków
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;// Usunięcie pomocniczych obiektów
   delete pHandler;
   return true;
}




int main (int argc, char* args[]) 
{
   Scene  Scn;

   if (!ReadFile("scene.xml",Scn)) return 1;

   cout << endl;
}

*/