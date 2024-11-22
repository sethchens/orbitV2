//
//  TestShip.h
//  OrbitV2
//
//  Created by Seth on 11/20/24.
//

#pragma once
#include "unitTest.h"
#include "Ship.h"

class TestShip : UnitTest
{
public:
   void run()
   {
      constructor_default();
      move_oneSecond();
      move_tenSeconds();
//      move_noRotation();
      input_downOnce();
      
      report("Ship");
   }
   
private:
   void constructor_default();
   void move_oneSecond();
   void move_tenSeconds();
//   void move_noRotation();
   void input_downOnce();
};
