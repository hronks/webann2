#pragma once

#include "maths.h"

template <class T>
struct Data {

  // raw data

  std::vector<std::vector<T>> raw;
  float train_prop;

  // normalization parameters

  std::vector<T> norm_x_a;    // x -> (x-norm_a)/norm_b
  std::vector<T> norm_x_b;    // x -> (x-norm_a)/norm_b
  std::vector<T> norm_y_a;    // x -> (x-norm_a)/norm_b
  std::vector<T> norm_y_b;    // x -> (x-norm_a)/norm_b

  // live output data rows

  std::vector<T> out_x;
  std::vector<T> out_y;

  std::vector<int> train_order;
  std::vector<int> valid_order;
  int current_train;
  int current_valid;

  Data<T>(int x, int y) {

    norm_x_a.resize(x);
    norm_x_b.resize(x);
    norm_y_a.resize(y);
    norm_y_b.resize(y);
    out_x.resize(x);
    out_y.resize(y);
  }

  void find_norms() {

  }
  void set_order() {


  }
  void get_next_train() {

    out_x = raw[0];

  }
  void get_next_valid() {

  }



};
