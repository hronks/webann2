#pragma once

#include "maths.h"

template <class T>
struct Layer {

  int a;

  std::vector<T> in_f;
  std::vector<T> out_f;

  std::vector<T> in_b;
  std::vector<T> out_b;

  virtual void forwards() { };
  virtual void backwards() { };
};

template <class T>
struct DenseLayer: Layer<T> {

  std::vector<std::vector<T>> w;
  std::vector<T> b;
  std::vector<T (*)(T, int)> af;

  DenseLayer<T>(int inputs, int outputs, T (*f)(T, int)) {
    this->in_f.resize(inputs);
    this->out_f.resize(outputs);

    w.resize(outputs);
    for(int i = 0; i < outputs; ++i) {
      af.push_back(f);
      b.push_back(random<T>(0, 1) / (T) outputs);
      for(int j = 0; j < inputs; ++j)
        w[i].push_back(random<T>(0, 1));
    }
  }

  void forwards();
  void backwards();
};

template <class T>
void DenseLayer<T>::forwards() {

  std::cout<<"input vector:\n";
  print(this->in_f);
  std::cout<<"\n";

  std::cout<<"weight matrix:\n";
  print(w);
  std::cout<<"\n";

  std::cout<<"bias vector:\n";
  print(b);
  std::cout<<"\n";

  multiply(w, this->in_f, this->out_f);

  std::cout<<"output before bias addition:\n";
  print(this->out_f);
  std::cout<<"\n";

  add(b, this->out_f);

  std::cout<<"output before activation function:\n";
  print(this->out_f);
  std::cout<<"\n";

  apply(af, 0, this->out_f);

  std::cout<<"output:\n";
  print(this->out_f);
  std::cout<<"\n";

}

template <class T>
void DenseLayer<T>::backwards() {
  std::cout<<"hello2";
}
