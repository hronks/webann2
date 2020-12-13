#pragma once

#include "ann.h"
#include "web_macros.h"

struct Data_web {

  std::string value_type;

  // only one of these will point anywhere

  Data<float>* d_f;
  Data<double>* d_d;
  Data<long double>* d_ld;

  // these define X, X_copy_from, X_copy_to,
  ///             X_push, X_push_hard, X_pull, X_resize


  DEFINE_2D_VECTOR(raw, d)

  DEFINE_1D_VECTOR(norm_x_a, d)
  DEFINE_1D_VECTOR(norm_x_b, d)
  DEFINE_1D_VECTOR(norm_y_a, d)
  DEFINE_1D_VECTOR(norm_y_b, d)

  DEFINE_1D_VECTOR(out_x, d)
  DEFINE_1D_VECTOR(out_y, d)

  DEFINE_0ARG_FUNCTION(void, find_norms(), d)
  DEFINE_0ARG_FUNCTION(void, set_order(), d)
  DEFINE_0ARG_FUNCTION(void, get_next_train(), d)
  DEFINE_0ARG_FUNCTION(void, get_next_valid(), d)

  Data_web( std::string value_type_t, int x_columns, int y_columns,
            std::string norm_type) {

    value_type = value_type_t;
    out_x_resize(x_columns);
    out_y_resize(y_columns);

    if(value_type == "float")
      d_f = new Data<float>(x_columns, y_columns);
    if(value_type == "double")
      d_d = new Data<double>(x_columns, y_columns);
    if(value_type == "long double")
      d_ld = new Data<long double>(x_columns, y_columns);

  }

};
