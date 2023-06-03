#pragma once
#include "position.h"
#include "trigonometry.h"

class Physics {
public:
    Physics(double v, double radians)
    {
        
        t = 1.0;
        gravity = 0;
        dv = 0.0;
        ddx = 0.0;
        ddy = 0.0;
        this->v = v;
        dx = Trigonometry::computeHorizontalComponent(radians, v);
        dy = Trigonometry::computeVerticalComponent(radians, v);
    }

    void compute_physics(double force, double mass, double radians) 
    { 
        compute_acceleration(force, mass, radians);
        compute_velocity();
    }

    double getGravity() { return gravity * t; }
    void applyGravity() { dy = dy - getGravity(); }

    void compute_acceleration(double force, double mass, double radians) 
    {
        dv = force / mass;
        ddx = Trigonometry::computeHorizontalComponent(radians, dv);
        ddy = Trigonometry::computeVerticalComponent(radians, dv);
    }

    void compute_velocity() 
    {
        dx = dx - (ddx * t);
        dy = dy + (ddy * t);

        applyGravity();

        v = Trigonometry::computeTotalComponent(dx, dy);
    }

    Position compute_location(Position pt)
    {
        pt.addMetersX(dx * t);
        pt.addMetersY(dy * t);
        return pt;
    }

    double get_velocity() { return v; }

private:
    double t;
    double gravity;
    double dv;          // Delta Velocity a.k.a. Total Acceleration
    double ddx;         // Horizontal Acceleration
    double ddy;         // Vertical Acceleration
    double v;           // Total Velocity
    double dx;          // Horizontal Velocity
    double dy;          // Vertical Velocity
};
