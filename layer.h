#pragma once

template <class T>
struct Layer {

  std::vector<T> in;
  std::vector<T> out;

  virtual void forwards() { };
  virtual void backwards() { };

};

template <class T>
struct DenseLayer: Layer<T> {

  std::vector<std::vector<T>> w;
  std::vector<T> b;


  void forwards();
  void backwards();



};

template <class T>
void DenseLayer<T>::forwards() {
  std::cout<<"hello";
}

template <class T>
void DenseLayer<T>::backwards() {
  std::cout<<"hello2";
}
