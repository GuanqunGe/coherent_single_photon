//SpacePoint class generate 3D space point within a volume
#ifndef SPACE_POINT_H
#define SPACE_POINT_H

#include <iostream>
#include <vector>
#include "TRandom3.h"

class SpacePoint{
private:
    TRandom3* rand;
    double x_low, x_up;  //x, y, z orientation are the same as uboone detector: 
    double y_low, y_up;  //x: horizontal, y: vertical, z: beam direction
    double z_low, z_up;
    double time_low=0, time_up=0;
    std::vector<double> UniformRectangle() const;
public:
    //default constructor
    SpacePoint():x_low(0), x_up(0), y_low(0), y_up(0), z_low(0), z_up(0), rand(new TRandom3()){}
    SpacePoint(double xlow, double xup, double ylow, double yup, double zlow, double zup):x_low(xlow), x_up(xup), y_low(ylow), y_up(yup), z_low(zlow), z_up(zup), rand(new TRandom3()){}


    std::vector<double> Sample3D() const;
    double SampleTime() const { return rand->Uniform(time_low, time_up); }
    void SetX(double low, double up);
    void SetY(double low, double up);
    void SetZ(double low, double up);
    void SetTime(double low, double up);
};


// ======================== Start of the source code  ==========================================
std::vector<double> SpacePoint::Sample3D() const{
    return this->UniformRectangle();
}

std::vector<double> SpacePoint::UniformRectangle() const{
    double x_val = rand->Uniform(x_low, x_up);
    double y_val = rand->Uniform(y_low, y_up);
    double z_val = rand->Uniform(z_low, z_up);
    return {x_val, y_val, z_val};
}

void SpacePoint::SetX(double low, double up){
    x_low = low;
    x_up = up;
    return;
}
void SpacePoint::SetY(double low, double up){
    y_low = low;
    y_up = up;
    return;
}
void SpacePoint::SetZ(double low, double up){
    z_low = low;
    z_up = up;
    return;
}
void SpacePoint::SetTime(double low, double up){
    time_low = low;
    time_up = up;
    return;
}
#endif
