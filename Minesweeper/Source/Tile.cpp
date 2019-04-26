#include "Tile.h"

//constructor
Tile::Tile()
{
    value = 0;
    covered = true;
    flagged = false;
}

Tile::~Tile()
{

}

//getter
int Tile::getValue() {return value;}
bool Tile::isCovered() {return covered;}
bool Tile::isFlagged() {return flagged;}
bool Tile::isMine() {return value == -1;}

//setter
void Tile::setValue(int _value) {value = _value;}
void Tile::setCovered(bool _covered) {covered = _covered;}
void Tile::setFlagged(bool _flagged) {flagged = _flagged;}

//function
void Tile::setMine()
{
    value = -1;
}

void Tile::increaseValue()
{
    if (value != -1)
    {
        value++;
    }
}

void Tile::resetAll()
{
    value = 0;
    covered = true;
    flagged = false;
}

void Tile::reset()
{
    covered = true;
    flagged = false;
}
