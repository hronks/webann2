#include "web.h"

int main() {

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

  for(int j = 0; j < 1; ++j) {

    std::cout<<"\nTRIAL "<<j+1<<"\n";

    data.get_next_train();

    data.out_x_PULL_SOFT();
    data.out_x_COPY_TO(x);
    data.out_y_PULL_SOFT();
    data.out_y_COPY_TO(y);

    for(int i = 0; i < layer.size(); ++i) {
      layer[i].in_f_COPY_FROM(x);
      layer[i].in_f_PUSH_SOFT();
      std::cout<<"\nLAYER FORWARD "<<i+1<<" (TRIAL "<<j+1<<")\n";
      layer[i].forwards();
      layer[i].out_f_PULL_SOFT();
      layer[i].out_f_COPY_TO(x);
    }

  //  std::cout<<"x vector is: ";
  //  print(x);
  //  std::cout<<"\n";

  //  std::cout<<"y vector is: ";
  //  print(y);
  //  std::cout<<"\n";

    cost.data_y_COPY_FROM(y);
    cost.data_y_PUSH_SOFT();
    cost.in_f_COPY_FROM(x);
    cost.in_f_PUSH_SOFT();

    std::cout<<"\nCOST (TRIAL "<<j+1<<")\n";
    cost.calculate();

    cost.diff_PULL_SOFT();

    for(int i = layer.size() - 1; i >= 0; --i) {
      layer[i].in_b_COPY_FROM(x);
      layer[i].in_b_PUSH_SOFT();
      std::cout<<"\nLAYER BACKWARD "<<i+1<<" (TRIAL "<<j+1<<")\n";
      layer[i].backwards();
      layer[i].out_b_PULL_SOFT();
      layer[i].out_b_COPY_TO(x);
    }

  }


}
