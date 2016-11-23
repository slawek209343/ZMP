#include <xercesc/util/PlatformUtils.hpp>
#include "xmlparser4scene.hh"
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include "Prostopadloscian.hh"
#ifndef XMLSize_t
# define XMLSize_t unsigned int
#endif


using namespace std;
using namespace xercesc;

/*!
 * Konstruktor klasy. Tutaj należy zainicjalizować wszystkie
 * dodatkowe pola.
 * (Ten opis należy odpowiednio uzupełnić)
 */
XMLParser4Scene::XMLParser4Scene(Scene &Scn)
{
  _pScn = &Scn;
}


/*!
 * Metoda wywoływana jest bezpośrednio przed rozpoczęciem
 * przetwarzana dokumentu XML.
 */
void XMLParser4Scene::startDocument()
{
  cout << "*** Rozpoczecie przetwarzania dokumentu XML." << endl;
}


/*!
 * Metoda wywoływana jest bezpośrednio po zakończeniu
 * przetwarzana dokumentu XML.
 */
void XMLParser4Scene::endDocument()
{
  cout << "=== Koniec przetwarzania dokumentu XML." << endl;
}



/*!
 * Wykonuje operacje związane z wystąpieniem danego elementu XML.
 * W przypadku elementu \p "Action" będzie to utworzenie obiektu
 * reprezentującego odpowiednią działanie robota.
 * W przypadku elementu \p "Parameter" będzie to zapisanie parametrów
 * związanych z danym działaniem.
 * \param[in] ElemName -
 * \param[in] Attrs - (\b we,) atrybuty napotkanego elementu XML.
 */
void XMLParser4Scene::WhenStartElement( const std::string       &ElemName,
		                      const xercesc::Attributes   &Attrs
                                    )
{

  if (ElemName == "Obstacle"){ //operacja wczytywania przeszkody
 
    if (Attrs.getLength() != 1){
      cerr << "Zla ilosc atrybutow dla \"Obstacle\"" << endl; throw 1;
    }
    char* sAttrName = xercesc::XMLString::transcode(Attrs.getQName(0));
    
    if( strcmp(sAttrName,"Name")){
      cerr << "Zla nazwa atrybutu obstacle" << endl; throw 2;
    }
    int zero = 0;
    char* sObstacleName = xercesc::XMLString::transcode(Attrs.getValue(static_cast<XMLSize_t>(zero)));
    string name(sObstacleName);
    Prostopadloscian p;
    p._name = name;
    _pScn->Przeszkody.push_back(p);
    
    xercesc::XMLString::release(&sObstacleName);
    xercesc::XMLString::release(&sAttrName);

    return;
  }

  if (ElemName == "Parameter"){ //proces pobierajacy parametr

    if (Attrs.getLength() != 2){
    cerr << "Zla ilosc atrybutow dla \"Parameter\"" << endl; throw 1;
    }
    char* sAttrName = xercesc::XMLString::transcode(Attrs.getQName(0));
    
    if( strcmp(sAttrName,"Name")){
      cerr << "Zla nazwa atrybutu parameter" << endl; throw 2;
    }
    static int idx = 0;
    int zero = 0;
    char* sParamName = xercesc::XMLString::transcode(Attrs.getValue(static_cast<XMLSize_t>(zero)));
    std::string param =std::string( xercesc::XMLString::transcode(Attrs.getValue(static_cast<XMLSize_t>(1))));
    //coordinates of Wektor3D _center
    if(idx < WYMIAR3D){
      std::string::size_type sz; //alias of size_t
      _pScn->Przeszkody.back()._center[idx] = stod(param, &sz);
      cout << _pScn->Przeszkody.back()._center[idx];
      ++idx;
    }
    //coordinates of Wektor3D _size
    else if( idx < 2 * WYMIAR3D){
      std::string::size_type sz; //alias of size_t
      _pScn->Przeszkody.back()._size[idx-WYMIAR3D] = stod(param, &sz);
      cout << _pScn->Przeszkody.back()._size[idx-WYMIAR3D];
      ++idx;
      if(idx == 6) idx = 0;
    }

    xercesc::XMLString::release(&sParamName);
    xercesc::XMLString::release(&sAttrName);


    return;
  }
}




/*
   *  Tu moge rozpoznac element i przetworzyc jego atrybuty
   */
/*
  if(ElemName == "Obstacle")
  {
    if(Attrs.getLength() != 1){
      cerr<<"Zla ilosc atrybutow dla \"Obstacle\"" << endl; throw 1;     
    }

    char *sAttrName = xercesc::XMLString::transcode(Attrs.getQName(0));

    if(strcmp(sAttrName,"Name")){
      cerr <<"Zla nazwa atrybutu dla Obstacle" << endl; throw 2;

    }
    int zero=0;
    char *sObstacleName = xercesc::XMLString::transcode(Attrs.getValue(static_cast < XMLSize_t >(zero)));

    Prostopadloscian bryla;
    cout<<sObstacleName<<endl;

  bryla.nazwa = sObstacleName;
    _pScn->przeszkody.push_back(bryla);
  xercesc::XMLString::release(&sObstacleName);
  xercesc::XMLString::release(&sAttrName);
    return;
  } */
/*teraz dla parametrow rozmieszczenia i dlugosci*/
 /* if(ElemName == "Parameter")
  {
    if(Attrs.getLength() != 2){
      cerr<<"Zla ilosc atrybutow dla \"Parameter\"" << endl; throw 1;     
    }

    char *sAttrName = xercesc::XMLString::transcode(Attrs.getQName(0));

    if(strcmp(sAttrName,"Name")){
      cerr <<"Zla nazwa atrybutu dla Parameter" << endl; throw 2;

    }
    int zero=0;
    char *sObstacleName = xercesc::XMLString::transcode(Attrs.getValue(static_cast < XMLSize_t >(1))); //dla zerowego nie musimy brac bo to nazwa 
    Prostopadloscian bryla;


  bryla.nazwa = sObstacleName;
    _pScn->przeszkody.push_back(bryla);
  xercesc::XMLString::release(&sObstacleName);
  xercesc::XMLString::release(&sAttrName);
    return;
  } 


  cout << "       ---> Tu moge przetwarzyc element: " << ElemName << endl;
  
}
*/



/*!
 * Metoda jest wywoływana po napotkaniu nowego elementu XML, np.
 * gdy zostanie napotkany element:
   \verbatim
     <Action Name="Rotate">
   \endverbatim
 *  to poprzez parametr \e xscElemName jest dostęp do nazwy elementu
 *  tzn. \p Action, 
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 *  \param[in] Attrs -  lista atrybutów danego symbolu XML.
 *                 W przykładzie pokazanym powyżej listę atrybutów
 *                 będą stanowiły napisy:
 */
/*
 * Te metode nalezy odpowiednio zdekomponowac!!!
 */
void XMLParser4Scene::startElement(  const   XMLCh* const    pURI,
                                       const   XMLCh* const    pLocalName,
                                       const   XMLCh* const    pQNname,
				       const   xercesc::Attributes&     Attrs
                                    )
{
  char* sElemName = xercesc::XMLString::transcode(pLocalName);
  cout << "+++ Poczatek elementu: "<< sElemName << endl;

  WhenStartElement(sElemName, Attrs);

  xercesc::XMLString::release(&sElemName);
}




/*!
 * Metoda zostaje wywołana w momencie zakończenia danego elementu
 * XML, np. jeżeli w pliku jest wpis:
   \verbatim
     <Action Name="Rotate">
     </Action>
   \endverbatim
 * to metoda ta zostanie wywołana po napotkaniu znacznika
 * \p </Action>. Jeżeli element XML ma formę skróconą, tzn.
   \verbatim
     <Parametr Name="Rotate"/>
   \endverbatim
 * to wówczas wywołana metoda wywołana zostanie w momencie
 * napotkania sekwencji "/>"
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 */
void XMLParser4Scene::endElement(  const   XMLCh* const    pURI,
                                     const   XMLCh* const    pLocalName,
                                     const   XMLCh* const    pQName
                                  )
{
   char* sElemName = xercesc::XMLString::transcode(pLocalName);
   cout << "--- Koniec elementu: "<< sElemName << endl;

   WhenEndElement(sElemName);

   xercesc::XMLString::release(&sElemName);
}



/*!
 * Wykonuje końcowe operacje związane z danym elementem XML. 
 * W przypadku \p "Action" jest to dodanie utworzonego wcześniej
 * obiektu do listy poleceń robota.
 * Metoda wywoływana jest w momencie napotkania znacznika końca
 * danego elementu XML.
 * \param[in] ElemName -  nazwa elementu XML
 */
void XMLParser4Scene::WhenEndElement(const std::string& ElemName)
{
  cout << "       ---> Tu na koniec moge wykonac jakies dzialanie (o ile jest potrzebne)"
       << endl << endl;
}



/*!
 * Metoda wywoływana jest, gdy napotkany zostanie błąd fatalny,
 * np.
  \verbatim
    <Action Name="Rotate">
    </Parametr>
  \endverbatim
 */
void XMLParser4Scene::fatalError(const xercesc::SAXParseException&  Exception)
{
   char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

   cerr << "Blad fatalny! " << endl
        << "    Plik:  " << sSystemId << endl
        << "   Linia: " << Exception.getLineNumber() << endl
        << " Kolumna: " << Exception.getColumnNumber() << endl
        << " Informacja: " << sMessage 
        << endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
}

/*!
 * Metoda jest wywoływana, gdy napotkany zostanie błąd, który nie
 * jest traktowany jako fatalny. W ten sposób traktowane są błędy
 * występujące w opisie gramatyki dokumentu.
 * \param[in] Except - zawiera informacje dotyczące błędu. Informacje
 *                     te to opis błędu oraz numer linii, w której
 *                     wystąpił błąd.
 */
void XMLParser4Scene::error(const xercesc::SAXParseException&  Exception)
{
  cerr << "Blad ..." << endl;


   char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

   cerr << "Blad fatalny! " << endl
        << "    Plik:  " << sSystemId << endl
        << "   Linia: " << Exception.getLineNumber() << endl
        << " Kolumna: " << Exception.getColumnNumber() << endl
        << " Informacja: " << sMessage 
        << endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
   //TMP
  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}


/*!
 *
 */
void XMLParser4Scene::warning(const xercesc::SAXParseException&  Exception)  
{
  cerr << "Ostrzezenie ..." << endl;

  /*
   * Tutaj należy wstawić odpowiedni kod. Tekst wyświetlany powyżej
   * jest tylko "atrapą".
   */
}



/*
bool XMLParser4Scene::ReadFile(const char* sFileName,  Scene& Scn)
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

*/