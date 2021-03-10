#include <iostream>
#include "AutomotaGrid.h"

int main()
{
    AutomotaGrid *grid = new AutomotaGrid();

    bool* b = grid->GetCellNeighbours(1, 1, 1);
}
