#include <iostream>
#include "Renderer.h"

int main()
{
    AutomotaGrid* automota = new AutomotaGrid();
    Renderer renderer(automota);

    automota->SetState(4, 4, 4, true);

    renderer.RenderFrame();

    renderer.OntoConsole();

    while(true){}
}
