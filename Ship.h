/***********************************************************************
 * Header File:
 *    SHIP
 * Author:
 *    <your name here>
 * Summary:
 *    The ship class
 ************************************************************************/


#pragma once
#include "acceleration.h"
#include "Satellite.h"
#include "uiInteract.h"
#include "uiDraw.h"

class TestShip;

class Ship : public Satellite
{
public:
   friend TestShip;
   
   // constructor
   Ship() : Satellite(0, 10.0, 0.0002)
   {
      pos.setPixelsX(-450.0);
      pos.setPixelsY(450.0);
      velocity.setDX(0.0);
      velocity.setDY(-2000.0);
      angle.setDown();
   }
   
  void draw(ogstream &gout) override
   {
      gout.drawShip(pos, angle.getRadians(), false);
   }
   
   void input(const Interface& ui) override
   {
       if (ui.isRight())
           this->angle.add(0.1);
       if (ui.isLeft())
           this->angle.add(-0.1);
       
       if (ui.isDown())
       {
           // Calculate thrust effect based on the direction the ship is pointing
          Acceleration thrust;
          thrust.setDDX(2.0 * cos(angle.getRadians()));
          thrust.setDDY(2.0 * sin(angle.getRadians()));
          
          // udpate velocity
          velocity.add(thrust, 1.0);
          
           // Update the position using the current velocity
          pos.add(thrust, velocity, 48.0);
       }
   }
   
   void move(double time) override
   {
      Satellite::move(48.0);
      
      // Reset angle change to remove time dilation effect on rotation
      angle.add(-angularVelocity * (48.0 - 1.0));
   }
};

class FakeShip : Ship
{
public:
   FakeShip() : Ship() {}
   void input(bool isRight, bool isLeft, bool isDown, bool isSpace)
   {
      if (isRight)
          this->angle.add(0.1);
      if (isLeft)
          this->angle.add(-0.1);
      
      if (isDown)
      {
          // Calculate thrust effect based on the direction the ship is pointing
         Acceleration thrust;
         thrust.setDDX(2.0 * cos(angle.getRadians()));
         thrust.setDDY(2.0 * sin(angle.getRadians()));
         
         // udpate velocity
         velocity.add(thrust, 1.0);
         
          // Update the position using the current velocity
         pos.add(thrust, velocity, 48.0);
      }
   }
};