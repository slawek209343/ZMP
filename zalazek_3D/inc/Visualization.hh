#ifndef VISUALIZATION_HH
#define VISUALIZATION_HH


#include "DronPose.hh"

/*!
 * \brief
 */
class Visualization {

  public:
  /*!
   * \brief Destruktor wirtualny, aby zapewnić poprawną destrukcję
   *        obiektu klasy pochodnej
   */
   virtual ~Visualization() {}
  /*!
   * \brief Powoduje odrysowanie aktualnej sceny z uwzglęnieniem bieżącej
   *        pozycji drona
   */
  virtual void Draw( const DronPose *pPose ) {}
};






#endif
