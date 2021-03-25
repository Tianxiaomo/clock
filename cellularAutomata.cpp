//The Game of Life, also known simply as Life, is a cellular automaton
//devised by the British mathematician John Horton Conway in 1970.
// https://en.wikipedia.org/wiki/Conway's_Game_of_Life

#include "cellularAutomata.h"

AUTOMATA::AUTOMATA(/* args */ TFT_eSPI &t) : UI(t)
{
}

AUTOMATA::~AUTOMATA()
{
}

void AUTOMATA::start()
{

    //Set up the display
    // tft.init();
    // tft.setRotation(3);
    // tft.fillScreen(TFT_BLACK);
    // tft.setTextSize(1);
    // tft.setTextColor(TFT_WHITE);
    // tft.setCursor(0, 0);

    //Display a simple splash screen
    // tft.fillScreen(TFT_BLACK);
    // tft.setTextSize(2);
    // tft.setTextColor(TFT_WHITE);
    // tft.setCursor(40, 5);
    // tft.println(F("Arduino"));
    // tft.setCursor(35, 25);
    // tft.println(F("Cellular"));
    // tft.setCursor(35, 45);
    // tft.println(F("Automata"));

    tft.fillScreen(TFT_BLACK);
    initGrid();
    drawGrid();
}

void AUTOMATA::render()
{
    computeCA();
    drawGrid();
    for (int16_t x = 1; x < GRIDX - 1; x++)
    {
        for (int16_t y = 1; y < GRIDY - 1; y++)
        {
            grid[x][y] = newgrid[x][y];
        }
    }
}

void AUTOMATA::restart()
{
    tft.fillScreen(TFT_BLACK);
    initGrid();
    drawGrid();
}

//Draws the grid on the display
void AUTOMATA::drawGrid(void)
{
    uint16_t color = TFT_WHITE;
    for (int16_t x = 1; x < GRIDX - 1; x++)
    {
        for (int16_t y = 1; y < GRIDY - 1; y++)
        {
            if ((grid[x][y]) != (newgrid[x][y]))
            {
                if (newgrid[x][y] == 1)
                    color = 0xFFFF; //random(0xFFFF);
                else
                    color = 0;
                tft.fillRect(CELLXY * x, CELLXY * y, CELLXY, CELLXY, color);
            }
        }
    }
}

//Initialise Grid
void AUTOMATA::initGrid(void)
{
    for (int16_t x = 0; x < GRIDX; x++)
    {
        for (int16_t y = 0; y < GRIDY; y++)
        {
            newgrid[x][y] = 0;

            if (x == 0 || x == GRIDX - 1 || y == 0 || y == GRIDY - 1)
            {
                grid[x][y] = 0;
            }
            else
            {
                if (random(3) == 1)
                    grid[x][y] = 1;
                else
                    grid[x][y] = 0;
            }
        }
    }
}

//Compute the CA. Basically everything related to CA starts here
void AUTOMATA::computeCA()
{
    for (int16_t x = 1; x < GRIDX; x++)
    {
        for (int16_t y = 1; y < GRIDY; y++)
        {
            int neighbors = getNumberOfNeighbors(x, y);
            if (grid[x][y] == 1 && (neighbors == 2 || neighbors == 3))
            {
                newgrid[x][y] = 1;
            }
            else if (grid[x][y] == 1)
                newgrid[x][y] = 0;
            if (grid[x][y] == 0 && (neighbors == 3))
            {
                newgrid[x][y] = 1;
            }
            else if (grid[x][y] == 0)
                newgrid[x][y] = 0;
        }
    }
}

// Check the Moore neighborhood
int AUTOMATA::getNumberOfNeighbors(int x, int y)
{
    return grid[x - 1][y] + grid[x - 1][y - 1] + grid[x][y - 1] + grid[x + 1][y - 1] + grid[x + 1][y] + grid[x + 1][y + 1] + grid[x][y + 1] + grid[x - 1][y + 1];
}
