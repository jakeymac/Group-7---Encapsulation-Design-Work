/***********************************************************************
 * Source File:
 *    Class : brief discription
 * Author:
 *    add author
 * Summary:
 *    add summary
 ************************************************************************/

#include "bullet.h"
#include "physics.h"
#include "ground.h"

Bullet::Bullet(Position p, double radians, Ground * ground) : physics(radians, p, ground), startPos(p) {
    streakPath.push_front(p);
    impactPos = Position(-1.0, -1.0);
    startAngle = radians;
}

 bool Bullet::isAlive() const 
 {
    return physics.distanceToAltitude.size() > 0 || streakPath.size() > 0;
 }

void Bullet::advance() {
    if (!physics.hitGround()) {
        physics.advance();
    }
    else {
        impactPos = physics.getPosition();
    }

    if (physics.distanceToAltitude.size() > 0) {
        streakPath.push_front(physics.distanceToAltitude.front());
        physics.distanceToAltitude.pop_front();
    }

    if (streakPath.size() > 20 || physics.distanceToAltitude.size() == 0) {
        streakPath.pop_back();
    }
}

list<Position> Bullet::getStreakPath() const
{
    return streakPath;
}

double Bullet::getAltitude()
{
    return streakPath.front().getMetersY();
}

double Bullet::getSpeed()
{
    return physics.getSpeed();
}

double Bullet::getDistance()
{
    return abs(streakPath.front().getMetersX() - startPos.getMetersX());
}

double Bullet::getHangTime()
{
    return physics.getHangTime();
}

bool Bullet::hitGround()
{
    if (physics.hitGround()) {
        impactPos = physics.getPosition();
        return true;
    }
    else {
        return false;
    }
}
