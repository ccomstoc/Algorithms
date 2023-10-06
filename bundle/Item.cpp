//-----Item.cpp-----
#include "Item.h"

int Item::autoIdTrack = 0;

Item::Item(){

  weight = 0;
  value = 0;
  id = 0;
  vpw = 0;

}

Item::Item(int w, int v){

  weight = w;
  value = v;
  id = ++autoIdTrack;
  vpw = ((double)value) / ((double)weight);

}
