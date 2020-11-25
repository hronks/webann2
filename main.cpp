#include "web.h"

int main() {

  Layer_web layer("dense_double", 2, 5);

  std::vector<double> x = {212.12, -23};
  layer.in_set(x);


  layer.forwards();
  layer.backwards();

}
