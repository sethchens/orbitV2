/***********************************************************************
 * Source File:
 *    SIMULATOR
 * Author:
 *    <your name here>
 * Summary:
 *    The main simulator class that handles the orbital simulation
 ************************************************************************/
#include "uiInteract.h"
#include "uiDraw.h"
#include "position.h"
#include "sputnik.h"
#include "test.h"
#include "hubble.h"
#include "starlink.h"
#include "crewDragon.h"
#include "GPS.h"
#include "Ship.h"
using namespace std;

/*********************************************
 * SIMULATOR
 * The main simulator class
 *********************************************/
class Simulator
{
public:
    // Constructor initializes the simulation
    Simulator(Position ptUpperRight) :
        ptUpperRight(ptUpperRight),
        pSputnik(new Sputnik()),
        pHubble(new Hubble()),
        pStarlink(new Starlink()),
        pCrewDragon(new CrewDragon()),
        pGPS(new GPS()),
        pShip(new Ship())
    {
        // Initialize the random stars
        for (int i = 0; i < NUM_STARS; i++)
        {
            Position pt;
            pt.setPixelsX(random(-ptUpperRight.getPixelsX(), ptUpperRight.getPixelsX()));
            pt.setPixelsY(random(-ptUpperRight.getPixelsY(), ptUpperRight.getPixelsY()));
            stars[i] = pt;
            phases[i] = random(0, 255);  // Random initial phase for twinkling
        }
    }

    // Destructor cleans up any allocated memory
    ~Simulator()
    {
        delete pSputnik;
        delete pHubble;
        delete pStarlink;
        delete pCrewDragon;
        delete pGPS;
       delete pShip;
    }

    // Move everything forward one time unit
    void update(const Interface & pUI)
    {
        // Move Sputnik according to physics (includes orbital motion)
        if (pSputnik && !pSputnik->isDead())
            pSputnik->move(1.0);

        // Move Hubble according to physics
        if (pHubble && !pHubble->isDead())
            pHubble->move(1.0);

        // Move Starlink according to physics
        if (pStarlink && !pStarlink->isDead())
            pStarlink->move(1.0);

        // Move CrewDragon according to physics
        if (pCrewDragon && !pCrewDragon->isDead())
            pCrewDragon->move(1.0);

        if (pGPS && !pGPS->isDead())
            pGPS->move(1.0);
       
       if (pShip && !pShip->isDead())
       {
//          pShip->input(pUI);
//          pShip->move(10.0);
       }

        // Update star phases for twinkling
        for (int i = 0; i < NUM_STARS; i++)
            phases[i] = (phases[i] + 1) % 256;
    }

    // Draw everything on the screen
    void draw(ogstream& gout)
    {
        // Draw the stars first (background)
        for (int i = 0; i < NUM_STARS; i++)
            gout.drawStar(stars[i], phases[i]);

        // Draw stationary Earth
        Position posEarth;
        gout.drawEarth(posEarth, 0.0);

        // Draw Sputnik last (foreground)
        if (pSputnik && !pSputnik->isDead())
            pSputnik->draw(gout);

        if (pHubble && !pHubble->isDead())
            pHubble->draw(gout);

        if (pStarlink && !pStarlink->isDead())
            pStarlink->draw(gout);

        if (pCrewDragon && !pCrewDragon->isDead())
            pCrewDragon->draw(gout);

        if (pGPS && !pGPS->isDead())
            pGPS->draw(gout);
       
       if (pShip && !pShip->isDead())
          pShip->draw(gout);

    }

private:
    Position ptUpperRight;         // Size of the screen
    Sputnik* pSputnik;            // The Sputnik satellite
    Hubble* pHubble;
    CrewDragon* pCrewDragon;
    Starlink* pStarlink;
    GPS* pGPS;
    Ship* pShip;
    static const int NUM_STARS = 100;
    Position stars[NUM_STARS];     // Array of star positions
    uint8_t phases[NUM_STARS];     // Array of star phases
};

/*************************************
 * CALLBACK
 * Handle all the frames by moving everything and drawing
 **************************************/
void callBack(const Interface* pUI, void* p)
{
    // Cast the void pointer to a simulator object
    Simulator* pSim = (Simulator*)p;

    // Update the simulation
    pSim->update(*pUI);

    // Draw everything
    Position pos;  // Center of the screen
    ogstream gout(pos);
    pSim->draw(gout);
}

/*********************************
 * Main handles command line parameters and creates the game
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
    // Run unit tests first
    testRunner();

    // Initialize OpenGL
    Position ptUpperRight;
    ptUpperRight.setZoom(128000.0);
    ptUpperRight.setPixelsX(1000.0);
    ptUpperRight.setPixelsY(1000.0);

    // Initialize the game
    Interface ui(argc, argv, "Orbital Simulator", ptUpperRight);
    Simulator sim(ptUpperRight);

    // Play the game
    ui.run(callBack, &sim);

    return 0;
}
