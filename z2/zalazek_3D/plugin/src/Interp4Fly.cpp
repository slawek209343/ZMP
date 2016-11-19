#include <iostream>
#include "Interp4Fly.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Fly::CreateCmd();
}


/*!
 *
 */
Interp4Fly::Interp4Fly(): _SpeedHor(0), _SpeedVer(0), _Distance(0)
{}


/*!
 *
 */
void Interp4Fly::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _SpeedHor  <<" " << _SpeedVer << " " << _Distance <<endl;
}


/*!
 *
 */
const char* Interp4Fly::GetCmdName() const
{
  return "Fly";
}


/*!
 *
 */
bool Interp4Fly::ExecCmd( DronPose     *pRobPose,  Visualization *pVis) const
{
  Wektor3D temp;
  double temp_angle;




  temp = pRobPose->GetPos_m();//pobieram aktualna pozycje drona
  temp_angle = pRobPose->GetAngle_deg();//pobieram aktualna orientacje drona

  double x,y,z,war1,war2,wsp;

  wsp = _SpeedHor / _SpeedVer;
  war1 = sqrt((_Distance*_Distance)/(1+(wsp*wsp)));
  war2 = war1 * wsp;

  cout<<"war1 = "<<war1<< " war2= "<<war2<< " wsp= "<<wsp<<endl;



  x = war2 * cos(-temp_angle*TO_RAD);//zamiana stopni na radiany
  y = war2 * sin(-temp_angle*TO_RAD);
  z = war1;
  double new_x = x/25,new_y = y/25 ,new_z = z/25,t_new = abs(1000000*(war1 / _SpeedVer)/25);
  for(int i=0;i<25;i++)//odswiezanie 25 klatek na sekunde 
  { 
    //wyliczam nowa pozycje drona
    temp.x() = temp.x() + new_x;
    temp.y() = temp.y() + new_y;
    temp.z() = new_z + temp.z();
    pRobPose->SetPos_m(temp);//aktualizuje nowa pozycje drona
    pVis->Draw(pRobPose);
    usleep(t_new);  // Pauza
    //cout<<endl<<t_new<<endl<<"to byl czas\n";

  }



  pRobPose->SetTime(abs(war1 / _SpeedVer));
 // cout<<endl<<war1/_SpeedVer<<endl<<"to byl czas\n";
  //pRobPose->SetPos_m(temp);//aktualizuje nowa pozycje drona

  cout<<"Zmiana pozycji drona, teraz wynosi ona: x= "<<temp.x()<< " y= " << temp.y()<<" z= "<<temp.z()<<endl;
    //pVis->Draw(pRobPose);
    //usleep((war1 / _SpeedVer)* 1000000);  // Pauza 1 sek.
  


  return true;
}


/*!
 *
 */
bool Interp4Fly::ReadParams(std::istream& Strm_CmdsList)
{
  
     Strm_CmdsList>> _SpeedVer >> _SpeedHor >>_Distance;
     cout<<_SpeedHor << " "<<_SpeedVer <<" "<< _Distance<<endl;

  return true;
}


/*!
 *
 */
Interp4Command* Interp4Fly::CreateCmd()
{
  return new Interp4Fly();
}


/*!
 *
 */
void Interp4Fly::PrintSyntax() const
{
  cout << "Fly  hor_speed[m/s]  ver_speed[m/s]  dist[m]" << endl;
}
