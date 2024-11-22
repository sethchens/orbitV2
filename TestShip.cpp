//
//  TestShip.cpp
//  OrbitV2
//
//  Created by Seth on 11/20/24.
//

#include "TestShip.h"

/*********************************************
 * CONSTRUCTOR: default
 * Input:
 * Output:
 *********************************************/
void TestShip::constructor_default()
{
   // setup
   // exercise
   Ship s;
   
   // verify
   assertEquals(s.radius, 10.0);
   assertEquals(s.pos.x, -22500.0);
   assertEquals(s.pos.y, 22500.0);
   assertEquals(s.velocity.dx, 0.0);
   assertEquals(s.velocity.dy, -2000.0);
   assertEquals(s.angle.radians, 3.141592653589);
} // teardown

/*********************************************
 * MOVE: 1 second
 * Input:
 * Output:
 *********************************************/
void TestShip::move_oneSecond()
{
    // Setup
   Ship s;

    // Exercise
    s.move(1.0);
   
    // Verify position has changed
   assertEquals(s.pos.x, 641869776.95774639);
   assertEquals(s.pos.y, -641965776.95774639);
   assertEquals(s.age, 1);
}

/*********************************************
 * MOVE: 10 seconds
 * Input:
 * Output:
 *********************************************/
void TestShip::move_tenSeconds()
{
    // Setup
   Ship s;

    // Exercise
   for (int i = 0; i < 10; i++)
      s.move(1.0);
   
    // Verify position has changed
   assertEquals(s.pos.x, 6418900259.6663752);
   assertEquals(s.pos.y, -6419860259.6648922);
   assertEquals(s.age, 10);
}

/*********************************************
 * INPUT: down once
 * Input:
 * Output:
 *********************************************/
void TestShip::input_downOnce()
{
    // Setup
    FakeShip s;

    // Exercise
   
   
    // Verify position has changed
//   assertEquals(s.pos.x, 6418900259.6663752);
//   assertEquals(s.pos.y, -6419860259.6648922);
//   assertEquals(s.age, 10);
}
