#include <iostream>
#include "Interp4Turn.hh"

using std::cout;
using std::endl;

#define PI 3.1415926535897

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
  return Interp4Turn::CreateCmd();
}


/*!
 *
 */
Interp4Turn::Interp4Turn(): _Speed(0), _Distance(0), _Radius(0)
{}


/*!
 *
 */
void Interp4Turn::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Speed << " " << _Distance << " " << _Radius << endl;
}


/*!
 *
 */
const char* Interp4Turn::GetCmdName() const
{
  return "Turn";
}


/*!
 *
 */
bool Interp4Turn::ExecCmd( DronPose     *pRobPose,  Visualization *pVis) const
{
  Wektor3D temp;
  double temp_angle;
  temp = pRobPose->GetPos_m();
  temp_angle = pRobPose->GetAngle_deg();
  double rotate_angle = -360/ ((2*PI*_Radius)/_Distance);
  double x,y;


  pRobPose->SetTime(_Distance/_Speed);

  for(int i = 0;i<rotate_angle;i++)
  {
    x = _Radius *cos(-(temp_angle + i) *TO_RAD) + temp.x();
    y = _Radius *sin(-(temp_angle + i) *TO_RAD) + temp.y(); 

    pVis->Draw(pRobPose);
    usleep(100000);  // Pauza 1 sek.
  }
      


  temp.x() += x;
  temp.y() += y;

  pRobPose->SetPos_m(temp);

  pRobPose->SetAngle_deg(temp_angle + rotate_angle);

  cout<<endl<<" x = "<<x<<" y = "<<y<< " z= " <<temp.z() <<" orientacja= "<< temp_angle+rotate_angle<< endl;
  cout<<"Aktualny czas ruchu dla drona wynosi "<<pRobPose->GetTime()<<" s\n";



  return true;
}


/*!
 *
 */
bool Interp4Turn::ReadParams(std::istream& Strm_CmdsList)
{
  
    Strm_CmdsList>> _Speed >> _Distance >> _Radius;
    cout<< _Speed <<" " << _Distance << " " << _Radius<<endl;


  return true;
}


/*!
 *
 */
Interp4Command* Interp4Turn::CreateCmd()
{
  return new Interp4Turn();
}


/*!
 *
 */
void Interp4Turn::PrintSyntax() const
{
  cout << "   Turn  speed[m/s]  distance[m]  radius[m]" << endl;
}
