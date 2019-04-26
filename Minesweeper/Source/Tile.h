#ifndef TILE_H
#define TILE_H

/*
//  Value:
//  0 - 8 ~ number of mines surround
//  -1 ~ mine
//
//  Priority
//  flagged > covered
*/
class Tile
{
private:
    int value;
    bool covered;
    bool flagged;

public:
    //constructor
    Tile();
    ~Tile();

    //getter
    int getValue();
    bool isCovered();
    bool isFlagged();
    bool isMine();

    //setter
    void setValue(int _value);
    void setCovered(bool _covered);
    void setFlagged(bool _flagged);

    //function
    void setMine();         // turn this tile to mine ~ set value = -1
    void increaseValue();   // value += 1 if tile is not mine
    void resetAll();        // set tile to default
    void reset();           // set covered and flagged to default
};

#endif // TILE_H
