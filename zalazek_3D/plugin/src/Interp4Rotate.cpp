#include <iostream>
#include "Interp4Rotate.hh"

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
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): _Ang_Speed_degS(0), _Ang_Distance_deg(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << _Ang_Speed_degS << " " << _Ang_Distance_deg << endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return "Rotate";
}


/*!
 *
 */
bool Interp4Rotate::ExecCmd( DronPose *pRobPose,  Visualization *pVis) const
{
  
  double temp_angle=0;

  Wektor3D temp;
  temp = pRobPose->GetPos_m();
  int x,y,z;


  temp_angle = pRobPose->GetAngle_deg();
  //cout<<temp_angle<<endl;

  if((_Ang_Distance_deg && _Ang_Speed_degS) !=0)
  {
      pRobPose->SetAngle_deg(temp_angle + _Ang_Distance_deg);
      
  }

  
  pVis->Draw(pRobPose);

  usleep(abs(_Ang_Distance_deg / _Ang_Speed_degS)*1000000);  // Pauza 
  pRobPose->SetTime(abs(_Ang_Distance_deg / _Ang_Speed_degS));

    cout<<"x= "<<temp[0]<<" y= "<<temp[1]<<" z= "<<temp[2]<<"Orientacja wynosi "<<temp_angle + _Ang_Distance_deg<<" stopni"<<endl;
  cout<<"Aktualny czas ruchu dla drona wynosi "<<pRobPose->GetTime()<<" s\n";

  return true;
}


/*!
 *
 */
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  
    Strm_CmdsList >> _Ang_Speed_degS >> _Ang_Distance_deg;
     //cout<<"Elo, patrz co mam!\n";
     cout<< _Ang_Speed_degS << " " << _Ang_Distance_deg<<endl;


  return true;
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  ang_speed[deg/s]  ang[deg]  " << endl;
}
