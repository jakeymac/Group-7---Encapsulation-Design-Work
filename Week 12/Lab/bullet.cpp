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

Bullet::Bullet(Position p, double radians, Ground * ground) : physics(radians, p, ground) {
    streakPath.push_front(p);
    impactPos = Position(-1.0, -1.0);
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
