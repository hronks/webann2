#pragma once

#include "ann.h"
#include "web_macros.h"

struct Cost_web {

  std::string value_type;

  Cost<float>* c_f;
  Cost<double>* c_d;
  Cost<long double>* c_ld;

  DEFINE_1D_VECTOR(data_y, c)
  DEFINE_1D_VECTOR(in_f, c)
  DEFINE_1D_VECTOR(diff, c)

  DEFINE_0ARG_FUNCTION(void, calculate, c)

  Cost_web() {};
  Cost_web(std::string function, std::string value_type_t, int variables) {

    value_type = value_type_t;

    data_y_RESIZE(variables);
    in_f_RESIZE(variables);
    diff_RESIZE(variables);

    void (*cf_f)(   const std::vector <float> &,
                    const std::vector <float> &,
                          float &,
                          std::vector <float> &);
    void (*cf_d)(   const std::vector <double> &,
                    const std::vector <double> &,
                          double &,
                          std::vector <double> &);
    void (*cf_ld)(  const std::vector <long double> &,
                    const std::vector <long double> &,
                          long double &,
                          std::vector <long double> &);

    if(function == "binary_crossentropy") {
      if(value_type == "float") cf_f = Binary_crossentropy<float>;
      if(value_type == "double") cf_d = Binary_crossentropy<double>;
      if(value_type == "long double") cf_ld = Binary_crossentropy<long double>;
    }

    if(value_type == "float")
      c_f = new Cost<float>(cf_f, variables);
    if(value_type == "double")
      c_d = new Cost<double>(cf_d, variables);
    if(value_type == "long double")
      c_ld = new Cost<long double>(cf_ld, variables);

  }

};
