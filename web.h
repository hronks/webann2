#pragma once

#include "ann.h"
#include "web_macros.h"


  union data_type {
    float f;
    double d;
    long double ld;
  };

  union LayerUnion {
    DenseLayer<float> *df;
    DenseLayer<double> *dd;
    DenseLayer<long double> *dld;
  };

struct Layer_web {

  std::string type;
  LayerUnion l;

  std::vector<data_type> in;
  std::vector<data_type> out;

  Layer_web(std::string type_t, int inputs, int outputs) {

    type = type_t;

    if(type == NAME_DF) l.df = new DenseLayer<float>;
    if(type == NAME_DD) l.dd = new DenseLayer<double>;
    if(type == NAME_DLD) l.dld = new DenseLayer<long double>;

    DEFINE_VECTOR_TYPE(in, inputs)
    DEFINE_VECTOR_TYPE(out, outputs)

  }

  ~Layer_web() {
    if(type == NAME_DF) delete l.df;
    if(type == NAME_DD) delete l.dd;
    if(type == NAME_DLD) delete l.dld;
  }

  PULL_OBJECT(void, forwards())
  PULL_OBJECT(void, backwards())

  void in_set(std::vector<float> x) {
    in.resize(x.size());
    for(int i = 0; i < x.size(); ++i) {
      if(type == NAME_DF) in[i].f = x[i];
      if(type == NAME_DD) in[i].d = x[i];
      if(type == NAME_DLD) in[i].ld = x[i];
    }
  }

  void in_set(std::vector<double> x) {
    in.resize(x.size());
    for(int i = 0; i < x.size(); ++i) {
      if(type == NAME_DF) in[i].f = x[i];
      if(type == NAME_DD) in[i].d = x[i];
      if(type == NAME_DLD) in[i].ld = x[i];
    }
  }

  void in_set(std::vector<long double> x) {
    in.resize(x.size());
    for(int i = 0; i < x.size(); ++i) {
      if(type == NAME_DF) in[i].f = x[i];
      if(type == NAME_DD) in[i].d = x[i];
      if(type == NAME_DLD) in[i].ld = x[i];
    }
  }

  void in_push() {

    if(type == NAME_DD) {
      

    }


  }
  void in_pull();

};
