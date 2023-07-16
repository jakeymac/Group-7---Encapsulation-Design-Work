/*************************************************************
 * 1. Name:
 *      Jacob Johnson and Jaden Myers
 * 2. Assignment Name:
 *      Lab 13: Artillery Final Submission
 * 3. Assignment Description:
 *      With this submission, our Artillery simulator should be just about perfect.
 * 4. What was the hardest part? Be as specific as possible.
 *      There was a lot of fine tuning with little graphical details.
 *      Getting the game to reset took a littl bit but not too long.
 *      The ground class would fail an assert once in a while, so we
 *      helped it cope more gracefully. If a value was out of range,
 *      we just set the value to the closest valid number.
 * 5. How long did it take for you to complete the assignment?
 *      2-3 hours.
 *****************************************************************/
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <cassert>      // for ASSERT
#include <list>
#include "uiInteract.hpp" // for INTERFACE
#include "uiDraw.hpp"     // for RANDOM and DRAW*
#include "ground.hpp"     // for GROUND
#include "position.hpp"   // for POSITION
#include "bullet.hpp"
#include "angle.hpp"
using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight),
      ground(ptUpperRight),
      time(3.0),
      angle(0.0)
   {
       int randNum = rand();
       int length = Position(ptUpperRight).getPixelsX();
       double randX = (randNum % length) + 5.0;


       // Set the horizontal position of the howitzer. This should be random.
       ptHowitzer.setPixelsX(randX);

      // Generate the ground and set the vertical position of the howitzer.
      ground.reset(ptHowitzer);
   }

   bool hasLiveBullet() {
       if (!bullets.empty()) {
           for (Bullet bullet : bullets) {
               if (!bullet.hitGround()) {
                   return true;
               }
           }
       }

       return false;
   }

   Ground ground;                 // the ground
   list<Bullet> bullets;
   //Position  projectilePath[20];  // path of the projectile
   Position  ptHowitzer;          // location of the howitzer
   Position  ptUpperRight;        // size of the screen
   double angle;                  // angle of the howitzer
   double time;                   // amount of time since the last firing
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL.
   Demo* pDemo = (Demo*)p;

   //
   // accept input
   //

   // move a large amount
   if (pUI->isRight())
      pDemo->angle += 0.05;
   if (pUI->isLeft())
      pDemo->angle -= 0.05;

   // move by a little
   if (pUI->isUp())
      pDemo->angle += (pDemo->angle >= 0 ? -0.0015 : 0.0015);
   if (pUI->isDown())
      pDemo->angle += (pDemo->angle >= 0 ? 0.0015 : -0.0015);

   // fire that gun
   if (pUI->isSpace()) {
       pDemo->time = 0.0;
       pDemo->bullets.push_back(Bullet(pDemo->ptHowitzer, pDemo->angle, &(pDemo->ground)));
   }

   //
   // perform all the game logic
   //

   // advance time by half a second.
   pDemo->time += 0.5;

   // move the projectiles across the screen
   for (Bullet &bullet : pDemo->bullets) {
       if (bullet.isAlive()) {
           bullet.advance();
       }
   }

   // check if we hit the target
   for (Bullet& bullet : pDemo->bullets) {
       if (bullet.hitGround()) {
           double distance = computeDistance(pDemo->ground.getTarget(), bullet.getImpactPosition());
            
           assert(bullet.getImpactPosition().getPixelsY() <= pDemo->ground.getElevationMeters(bullet.getImpactPosition()));
           // We are only checking the size of the streak because a bullet actually lives for 20 frames after impact.
           // This extra life span gives us time to finish drawing the streak (if we missed the target.)
           // By checking if the size of the streak path is 19, we are basically making it so that we only run this
           // code once: the moment it makes impact.
           if (bullet.getStreakPath().size() == 19) {
               if (distance < 250.0) {
                   Position pt = pDemo->ptUpperRight;
                   *pDemo = Demo(pt);
                   return;
               }
           }
       }
   }

   // remove oldies
   for (auto it = pDemo->bullets.begin(); it != pDemo->bullets.end();)
       if ( !(it->isAlive()) )
       {
           it = pDemo->bullets.erase(it);
       }
       else
           ++it;

   //
   // draw everything
   //

   ogstream gout(Position(10.0, pDemo->ptUpperRight.getPixelsY() - 20.0));

   // draw the ground first
   pDemo->ground.draw(gout);

   // draw the howitzer
   gout.drawHowitzer(pDemo->ptHowitzer, pDemo->angle, pDemo->time);
 
   // draw the projectile
   for (Bullet bullet : pDemo->bullets) {
       double age = 0.0;

       for (Position p : bullet.getStreakPath()) {
           gout.drawProjectile(p, age);
           age += 0.4;
       }
   }

   // draw some text on the screen
   gout.setf(ios::fixed | ios::showpoint);
   gout.precision(1);
   gout.setPosition(Position(21000.0, 19000.0));

   if (pDemo->hasLiveBullet()) {
       Bullet bullet = pDemo->bullets.back();
       gout << "altitude:    " << bullet.getAltitude() << "m\n";
       gout << "speed:      " << bullet.getSpeed() << "m/s\n";
       gout << "distance:   " << bullet.getDistance() << "m\n";
       gout << "hang time: "
           << bullet.getHangTime() << "s\n";
   }
   else {
       Angle current = Angle();
       current.setRadians(pDemo -> angle);
       double angleOutput;
       if (current.getDegrees() > 180.0) {
           angleOutput = 360.0 - current.getDegrees();
       }
       else {
           angleOutput = current.getDegrees();
       }
       
       assert(angleOutput <= 180.0);
       
       gout << "angle: " << angleOutput << " degrees";
       
   }
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setPixelsX(700.0);
   ptUpperRight.setPixelsY(500.0);
   Position().setZoom(40.0 /* 42 meters equals 1 pixel*/);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);

   return 0;
}
