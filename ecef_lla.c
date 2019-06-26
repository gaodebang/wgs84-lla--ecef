#include "stdafx.h"

#include <math.h>



#define  PI  3.141592653

/*

该程序根据GPS.G1-X-00006.pdf文档，实现了WGS84和ECEF坐标的转换

*/



void LLAtoECEF(double latitude, double longitude, double height, double &X, double &Y, double &Z)

{

  double a = 6378137;

  double b = 6356752.314245;// b=(1-f)

  double E = (a*a - b*b)/(a*a);



  double COSLAT = cos(latitude*PI/180);

  double SINLAT = sin(latitude*PI/180);

  double COSLONG = cos(longitude*PI/180);

  double SINLONG = sin(longitude*PI/180);



  double N = a /(sqrt(1 - E*SINLAT*SINLAT));

  double NH = N + height;



  X = NH * COSLAT * COSLONG;

  Y = NH * COSLAT * SINLONG;

  Z = (b*b*N/(a*a) + height) * SINLAT;

}



void ECEFtoLLA(int lx, int ly, int lz)

{ 

  double      x, y, z;

  double      a, b, f, e, e1;

  double      Longitude;

  double      Latitude;

  double      Altitude;

  double      p, q;

  double      N;

  x = (double)lx ;

  y = (double)ly ;

  z = (double)lz ;

  a = (double)6378137.0;

  b = (double)6356752.31424518;

  f = 1.0 / (double)298.257223563;

  e = sqrtl(((a * a) - (b * b)) / (a * a));

  e1 = sqrtl(((a * a) - (b * b)) / (b * b));

  p = sqrtl((x * x) + (y * y));

  q = atan2l((z * a), (p * b));

  Longitude = atan2l(y, x);

  Latitude = atan2l((z + (e1 * e1) * b * powl(sinl(q), 3)), (p - (e * e) * a * powl(cosl(q), 3)));

  N = a / sqrtl(1 - ((e * e) * powl(sinl(Latitude), 2)));

  Altitude = (p / cosl(Latitude)) - N;

  Longitude = Longitude * 180.0 / PI;

  Latitude = Latitude  * 180.0 / PI;

  Latitude = (double)Latitude;

  Longitude = (double)Longitude;

  Altitude = (double)Altitude;

}





int _tmain(int argc, _TCHAR* argv[])

{

  double latitude = 22.21555549969;

  double longitude = 113.367229848;

  double h = 0.5;

  double XX = 0.0;

  double YY = 0.0;

  double ZZ = 0.0;

  LLAtoECEF(latitude, longitude, h, XX, YY, ZZ);

  ECEFtoLLA(XX, YY, ZZ);

return 0;

}