#include "web.h"

int main() {

  Data_web data("double", 10, 1, start_data, 1, 0.8);
  Layer_web layer("dense", "double", 3, 5, "relu");

//  pull data to web wrapper and copy to a variable

  std::vector<std::vector<double>> d;
  data.raw_PULL_HARD();
  data.raw_COPY_TO(d);

  std::cout<<"raw data is :\n";
  print(d);
  std::cout<<"\n";

  // normalse the data

  data.find_norms(1, 0);
  data.norm_raw_data();
  data.raw_PULL_SOFT();

  data.raw_COPY_TO(d);
  std::cout<<"normalised raw data is :\n";
  print(d);
  std::cout<<"\n";

  // divide up training and validation data

  data.set_order();
  data.get_next_train();

  data.out_x_PULL_SOFT();
  data.out_y_PULL_SOFT();





  std::vector<double> x = {-0.0023423, -2.2, 0.0021};
  std::vector<double> y = {0, 0, 0, 0, 0};

  std::cout<<"x vector is: ";
  for(int i = 0; i < x.size(); ++i)
    std::cout<<x[i]<<" ";
  std::cout<<"\n\n";

  layer.in_f_COPY_FROM(x);
  layer.in_f_PUSH_SOFT();
  layer.forwards();
  layer.out_f_PULL_SOFT();
  layer.out_f_COPY_TO(y);

  std::cout<<"y vector is: ";
  for(int i = 0; i < y.size(); ++i)
    std::cout<<y[i]<<" ";
  std::cout<<"\n\n";


  layer.backwards();

}
