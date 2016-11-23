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
/**************************************************************************************/
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

    if(idx < WYMIAR3D){    //elementy  do Wektor3D _center
      std::string::size_type sz; //alias of size_t
      _pScn->Przeszkody.back()._center[idx] = stod(param, &sz);//string to double
      cout << _pScn->Przeszkody.back()._center[idx];
      ++idx;
    }

    else if( idx < 2 * WYMIAR3D){    //elementy do Wektor3D _size
      std::string::size_type sz; //alias of size_t
      _pScn->Przeszkody.back()._size[idx-WYMIAR3D] = stod(param, &sz);//string to double
      cout << _pScn->Przeszkody.back()._size[idx-WYMIAR3D];
      ++idx;
      if(idx == 6) idx = 0;
    }

    xercesc::XMLString::release(&sParamName);
    xercesc::XMLString::release(&sAttrName);


    return;
  }
}

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

