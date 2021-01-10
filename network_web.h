#pragma once

#include "ann.h"
#include "layer_web.h"
#include "data_web.h"
#include "cost_web.h"

struct Network_web {

  Data_web data;
  std::vector<Layer_web> layer;
  Cost_web cost;

  Network_web(std::vector<Layer_web>);



};

Network_web::Network_web(std::vector<Layer_web> l) {

  layer = l;


};
