#ifndef  INTERP4COMMAND_HH
#define  INTERP4COMMAND_HH

#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <unistd.h>

#include "DronPose.hh"
#include "Visualization.hh"

/*!
 * \brief Stala sluzaca do zamiany stopni na radiany
 *
 *  Jest uzywana, gdy uzywa sie funkcji sin() oraz cos()
 */
#define TO_RAD  0.01745329252
/*!
 * \file
 * \brief Definicja klasy Interp4Command
 *
 * Plik zawiera definicję klasy Interp4Command ...
 */

/*!
 * \brief Modeluje abstrakcyjne polecenie dla robota mobilnego
 *
 *  Klasa modeluje ...
 */
 class Interp4Command {
  public:
   /*!
    * \brief Destruktor wirtualny ze wzgledu na klasy pochodne
    *
    *  
    */
   virtual ~Interp4Command() {}
   /*!
    * \brief
    */
   virtual void PrintCmd() const = 0;
   /*!
    * \brief
    */
   virtual void PrintSyntax() const = 0;
   /*!
    * \brief
    */
   virtual const char* GetCmdName() const = 0;
   /*!
    * \brief
    */
   virtual bool ExecCmd(  DronPose  *pRobPose,  Visualization *pVis  ) const = 0;
   /*!
    * \brief
    */
   virtual bool ReadParams(std::istream& Strm_CmdsList) = 0;
 };

#endif
