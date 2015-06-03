#include "StarNearEarth.h"
#include <math.h>

#define PI 3.14159265
 
class SNE_Analyzer : public StarNearEarth
{
private:
   double x, y, z;

public:
   void calcCartCoords();
   double getX() { return x; }
   double getY() { return y; }
   double getZ() { return z; }
   string coordToString();
   SNE_Analyzer & operator=(const StarNearEarth &sne);
};

string SNE_Analyzer::coordToString(){
   return "X: " + to_string(x) + "Y: " + to_string(y) + "Z: " + to_string(z);
}

void SNE_Analyzer::calcCartCoords(){
   double LY = 3.262 / this->getParallaxMean();
   double RA = this->getRAsc() * PI / 180;
   double DEC = this->getDec() * PI / 180;

   x = LY * cos(DEC) * cos(RA);
   y = LY * cos(DEC) * sin(RA);
   z = LY * sin(DEC);
}

SNE_Analyzer & SNE_Analyzer::operator=(const StarNearEarth &sne)
{

   setRank(sne.getRank());
   setNameCns(sne.getNameCns());
   setNumComponents(sne.getNumComponents());
   setNameLhs(sne.getNameLhs());
   setRAsc(sne.getRAsc());
   setDec(sne.getDec());
   setPropMotionMag(sne.getPropMotionMag());
   setPropMotionDir(sne.getPropMotionDir());
   setParallaxMean(sne.getParallaxMean());
   setParallaxVariance(sne.getParallaxVariance());
   setWhiteDwarfFlag(sne.getWhiteDwarfFlag());
   setSpectralType(sne.getSpectralType());
   setMagApparent(sne.getMagApparent());
   setMagAbsolute(sne.getMagAbsolute());
   setMass(sne.getMass());
   setNotes(sne.getNotes());
   setNameCommon(sne.getNameCommon());
   calcCartCoords();

   return *this;
}

