#include "web.h"

int main() {

  Data_web data("double", 3, 1, "");
  Layer_web layer("dense", "double", 3, 5, "relu");

  std::vector<std::vector<double>> d;

  d.push_back({-1.2223423, 22.2, 0.0221, 102});
  d.push_back({-1.1123423, 32.2, -0.022, 112});
  d.push_back({-1.01223423, 12.2, 0.001, 132});

  std::cout<<"raw data is:\n";
  print(d);
  std::cout<<"\n";

  // load the raw data

  data.raw_resize(3, 4);
  data.raw_copy_from(d);
  data.raw_push_hard();

  data.find_norms();
  data.set_order();
  data.get_next_train();

  data.out_x_pull();
  data.out_y_pull();

  std::vector<double> x = {-0.0023423, -2.2, 0.0021};
  std::vector<double> y = {0, 0, 0, 0, 0};

  std::cout<<"x vector is: ";
  for(int i = 0; i < x.size(); ++i)
    std::cout<<x[i]<<" ";
  std::cout<<"\n\n";

  layer.in_f_copy_from(x);
  layer.in_f_push();
  layer.forwards();
  layer.out_f_pull();
  layer.out_f_copy_to(y);

  std::cout<<"y vector is: ";
  for(int i = 0; i < y.size(); ++i)
    std::cout<<y[i]<<" ";
  std::cout<<"\n\n";


  layer.backwards();

}
