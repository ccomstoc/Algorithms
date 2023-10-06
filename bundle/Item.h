//-----Item.h-----
#include <iostream>

#ifndef ITEM_H
#define ITEM_H

class Item {

  public:

    static int autoIdTrack;
    int id;
    int weight;
    int value;
    double vpw;//value per weight
    Item();
    Item(int w, int v);



};

#endif
