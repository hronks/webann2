#include "web.h"

int main() {

  Network_web network({Layer("dense", "double", 10, 32, "relu")});


  Data_web data("double", 10, 1, start_data, 1, 0.8);
  std::vector<Layer_web> layer;
  layer.reserve(3);
  layer.emplace_back("dense", "double", 10, 32, "relu");
  layer.emplace_back("dense", "double", 32, 32, "relu");
  layer.emplace_back("dense", "double", 32, 1, "sigmoid");
  Cost_web cost("binary_crossentropy", "double", 1);


//  pull data to web wrapper and copy to a variable

  std::vector<std::vector<double>> d;
  std::vector<double> x, y, temp;

  data.raw_PULL_HARD();
  data.raw_COPY_TO(d);

  data.find_norms(1, 0);
  data.norm_raw_data();
  data.total_train_PULL();

  double error;

  for(int j = 0; j < 30; ++j) {

    error = 0;

    data.get_next_train();

    data.out_x_PULL_SOFT();
    data.out_x_COPY_TO(x);
    data.out_y_PULL_SOFT();
    data.out_y_COPY_TO(y);

    for(int i = 0; i < layer.size(); ++i) {
      layer[i].in_f_COPY_FROM(x);
      layer[i].in_f_PUSH_SOFT();
      layer[i].forwards();
      layer[i].out_f_PULL_SOFT();
      layer[i].out_f_COPY_TO(x);
    }

    cost.data_y_COPY_FROM(y);
    cost.data_y_PUSH_SOFT();
    cost.in_f_COPY_FROM(x);
    cost.in_f_PUSH_SOFT();

    cost.calculate();
    std::cout<<cost.c_d->cost<<" -> ";

    cost.diff_PULL_SOFT();
    cost.diff_COPY_TO(x);

    for(int i = layer.size() - 1; i >= 0; --i) {
      layer[i].in_b_COPY_FROM(x);
      layer[i].in_b_PUSH_SOFT();
      layer[i].backwards();
      layer[i].out_b_PULL_SOFT();
      layer[i].out_b_COPY_TO(x);
      layer[i].learn();

    }



    data.out_x_PULL_SOFT();
    data.out_x_COPY_TO(x);
    data.out_y_PULL_SOFT();
    data.out_y_COPY_TO(y);

    for(int i = 0; i < layer.size(); ++i) {
      layer[i].in_f_COPY_FROM(x);
      layer[i].in_f_PUSH_SOFT();
      layer[i].forwards();
      layer[i].out_f_PULL_SOFT();
      layer[i].out_f_COPY_TO(x);
    }

    cost.data_y_COPY_FROM(y);
    cost.data_y_PUSH_SOFT();
    cost.in_f_COPY_FROM(x);
    cost.in_f_PUSH_SOFT();

    cost.calculate();
    std::cout<<cost.c_d->cost<<"\n";

  }


}
