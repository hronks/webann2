#pragma once
#include "maths.h"

#define DEBUG_LAYER_H 0

template <class T>
struct Layer {

  int a;

  std::vector<T> in_f;
  std::vector<T> out_f;

  std::vector<T> in_b;
  std::vector<T> out_b;

  virtual void forwards() { };
  virtual void backwards() { };
  virtual void learn() { };
};

template <class T>
struct DenseLayer: Layer<T> {

  std::vector<std::vector<T>> w;
  std::vector<T> b;
  std::vector<T (*)(T, int)> af;

  std::vector<T> df;
  std::vector<T> delta;
  std::vector<std::vector<T>> epsilon;

  DenseLayer<T>(int inputs, int outputs, T (*f)(T, int)) {
    this->in_f.resize(inputs);
    this->out_b.resize(inputs);
    this->out_f.resize(outputs);
    this->in_b.resize(outputs);
    this->df.resize(outputs);
    this->delta.resize(outputs);

    w.resize(outputs);
    epsilon.resize(outputs);
    for(int i = 0; i < outputs; ++i) {
      epsilon[i].resize(inputs);
      af.push_back(f);
      b.push_back(random<T>(-1, 1));
      for(int j = 0; j < inputs; ++j)
        w[i].push_back(random<T>(-1, 1) / (T) outputs);
    }
  }

  void forwards();
  void backwards();
  void learn();
};

template <class T>
void DenseLayer<T>::forwards() {

  if(DEBUG_LAYER_H == 1) {

    std::cout<<"\ninput vector:\n";
    print(this->in_f);
    std::cout<<"\n";

    std::cout<<"\nweight matrix:\n";
    print(w);
    std::cout<<"\n";

    std::cout<<"\nbias vector:\n";
    print(b);
    std::cout<<"\n";
  }

  multiply(w, this->in_f, this->out_f);

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\noutput before bias addition:\n";
    print(this->out_f);
    std::cout<<"\n";
  }

  add(b, this->out_f);

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\noutput before activation function:\n";
    print(this->out_f);
    std::cout<<"\n";
  }

  apply(this->out_f, af, 1, this->df);
  apply(af, 0, this->out_f);

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\noutput:\n";
    print(this->out_f);
    std::cout<<"\n";
  }

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\ndf/dx:\n";
    print(df);
    std::cout<<"\n";
  }

}

template <class T>
void DenseLayer<T>::backwards() {

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\nbackwards input:\n";
    print(this->in_b);
    std::cout<<"\n";
  }

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\ndf/dx:\n";
    print(df);
    std::cout<<"\n";
  }

  hadamard(df, this->in_b, delta);
  multiply_transpose(w, delta, this->out_b);
  outer(this->in_f, delta, epsilon);

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\ndelta (dC/db):\n";
    print(delta);
    std::cout<<"\n";
  }

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\nepsilon (dC/dw):\n";
    print(epsilon);
    std::cout<<"\n";
  }

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\nbackwards out:\n";
    print(this->out_b);
    std::cout<<"\n";
  }

}

template <class T>
void DenseLayer<T>::learn() {

  T h = 0.001;

  perturb(delta, -h, b);
  perturb(epsilon, -h, w);

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\nupdated bias vector:\n";
    print(b);
    std::cout<<"\n";
  }

  if(DEBUG_LAYER_H == 1) {
    std::cout<<"\nupdated weight vector:\n";
    print(w);
    std::cout<<"\n";
  }

}
