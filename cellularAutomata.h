#ifndef _cellularAutomata_H_
#define _cellularAutomata_H_

#include "ui.h"

#define GRIDX 160
#define GRIDY 120
#define CELLXY 2

class AUTOMATA : public UI
{
private:
    /* data */
    //Current grid
    uint8_t grid[GRIDX][GRIDY];

    //The new grid for the next generation
    uint8_t newgrid[GRIDX][GRIDY];

    void drawGrid(void);
    void initGrid(void);
    void computeCA();
    int getNumberOfNeighbors(int x, int y);

public:
    AUTOMATA(/* args */ TFT_eSPI &t);
    ~AUTOMATA();

    void start();
    void render();
    void restart();
};

#endif