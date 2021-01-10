#pragma once

#include "maths.h"

#define DEBUG_COST_H 0

template <class T>
struct Cost {


  void (*cost_function)(  const std::vector <T> &,
                          const std::vector <T> &,
                                T &,
                                std::vector <T> &);

  T cost;
  std::vector<T> data_y;
  std::vector<T> in_f;
  std::vector<T> diff;

  Cost<T> (void (*f)( const std::vector <T> &,
                      const std::vector <T> &,
                            T &,
                            std::vector <T> &),
           int variables) {

    cost_function = f;
    data_y.resize(variables);
    in_f.resize(variables);
    diff.resize(variables);

  }

  void calculate() {

    cost_function(in_f, data_y, cost, diff);

    if(DEBUG_COST_H == 1) {
      std::cout<<"\n";
      std::cout<<"var: ";
      print(in_f);
      std::cout<<" act: ";
      print(data_y);
      std::cout<<" -> cost: "<<cost;
      std::cout<<" diff: ";
      print(diff);
      std::cout<<"\n";
    }
  }




};
