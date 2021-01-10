#pragma once

#include "ann.h"
#include "web_macros.h"

struct Layer_web {

  std::string layer_type;
  std::string value_type;

// only one of these will point anywhere

  Layer<float>* l_f;
  Layer<double>* l_d;
  Layer<long double>* l_ld;

// these define X, X_copy_from, X_copy_to, X_push, X_pull, X_resize

  DEFINE_1D_VECTOR(in_f, l)
  DEFINE_1D_VECTOR(out_f, l)
  DEFINE_1D_VECTOR(in_b, l)
  DEFINE_1D_VECTOR(out_b, l)

// these define X()

  DEFINE_0ARG_FUNCTION(void, forwards, l)
  DEFINE_0ARG_FUNCTION(void, backwards, l)
  DEFINE_0ARG_FUNCTION(void, learn, l)

  Layer_web();
  Layer_web(std::string layer_type_t, std::string value_type_t,
            int inputs, int outputs,
            std::string activation_function) {

    layer_type = layer_type_t;
    value_type = value_type_t;

    in_f_RESIZE(inputs);
    out_f_RESIZE(outputs);

    in_b_RESIZE(outputs);
    out_b_RESIZE(inputs);

    float (*af_f)(float, int);
    double (*af_d)(double, int);
    long double (*af_ld)(long double, int);

    if(activation_function == "relu") {
      if(value_type == "float") af_f = ReLU<float>;
      if(value_type == "double") af_d = ReLU<double>;
      if(value_type == "long double") af_ld = ReLU<long double>;
    }

    if(activation_function == "sigmoid") {
      if(value_type == "float") af_f = Sigmoid<float>;
      if(value_type == "double") af_d = Sigmoid<double>;
      if(value_type == "long double") af_ld = Sigmoid<long double>;
    }

    if(layer_type == "dense") {
      if(value_type == "float")
        l_f = new DenseLayer<float>(inputs, outputs, af_f);
      if(value_type == "double")
        l_d = new DenseLayer<double>(inputs, outputs, af_d);
      if(value_type == "long double")
        l_ld = new DenseLayer<long double>(inputs, outputs, af_ld);
    }

  }

  ~Layer_web() {
    if(layer_type == "dense") {
      if(value_type == "float") delete l_f;
      if(value_type == "double") delete l_d;
      if(value_type == "long double") delete l_ld;
    }
  }

};
