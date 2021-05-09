#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <SFML/Graphics.hpp>
#include "CApp.h"


int main()
{
    CApp app;
    app.run();

    return 0;
}

/* 
   buying delay

   death screen, IEntity, dealdamage




  more weapons, placeable walls and healthkit

    -sound
    ^^ damage, walking, shooting, background, grab money

    -menues

    -restartable
*/