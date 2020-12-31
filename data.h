#pragma once

#include "maths.h"
#include <sstream>

template <class T>
struct Data {

  // raw data

  std::vector<std::string> header_row;
  std::vector<std::vector<T>> raw;
  float train_prop;

  // data stats

  int x_columns;
  int y_columns;
  int rows;
  bool header;

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

  void load_data(std::string & input_data, bool has_header) {

    header_row.resize(0);
    raw.resize(0);

    std::stringstream s(input_data);
    std::string line;
    std::string word;
    T value;
    char a;

    if(has_header == 1) {
      s >> line;
      for(int j = 0; j < line.size(); ++j) {
        if(line[j] == ',') {
          header_row.push_back(word);
          word = "";
        }
        else word += line[j];
      }
      header_row.push_back(word);
    }

    rows = 0;

    for(int i = 0; !s.eof(); ++i) {
      s >> line;
      ++rows;
      std::stringstream l(line);
      raw.push_back({});
      for(int j = 0; !l.eof(); ++j) {
        l >> value;
        raw[i].push_back(value);
        l >> a;
      }
    }

  }

  Data<T>(int x, int y, std::string input_data, bool has_header,
          float train_prop_t) {

    x_columns = x;
    y_columns = y;
    norm_x_a.resize(x);
    norm_x_b.resize(x);
    norm_y_a.resize(y);
    norm_y_b.resize(y);
    out_x.resize(x);
    out_y.resize(y);
    train_prop = train_prop_t;

    load_data(input_data, has_header);
  }

  Data<T>(int x, int y) {

    x_columns = x;
    y_columns = y;
    norm_x_a.resize(x);
    norm_x_b.resize(x);
    norm_y_a.resize(y);
    norm_y_b.resize(y);
    out_x.resize(x);
    out_y.resize(y);
  }

  void find_norms(int type_x, int type_y) {

    if(type_x == 0) {
      for(int j = 0; j < x_columns; ++j) {
        norm_x_a[j] = 0;
        norm_x_b[j] = 1;
      }
    }

    if(type_y == 0) {
      for(int j = 0; j < y_columns; ++j) {
        norm_y_a[j] = 0;
        norm_y_b[j] = 1;
      }
    }

    if(type_x == 1) {

      for(int j = 0; j < x_columns; ++j) {
        norm_x_a[j] = 0;
        norm_x_b[j] = 0;
      }

      for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < x_columns; ++j) {
          norm_x_a[j] += raw[i][j];
          norm_x_b[j] += raw[i][j] * raw[i][j];
          }
      }
      for(int j = 0; j < x_columns; ++j) norm_x_a[j] /= rows;

      for(int j = 0; j < x_columns; ++j) {
        norm_x_b[j] -= rows * norm_x_a[j] * norm_x_a[j];
        norm_x_b[j] /= (rows - 1);
        norm_x_b[j] = sqrt(norm_x_b[j]);
      }
    }

    if(type_y == 1) {

      for(int j = 0; j < y_columns; ++j) {
        norm_y_a[j] = 0;
        norm_y_b[j] = 0;
      }

      for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < y_columns; ++j) {
          norm_y_a[j] += raw[i][x_columns + j];
          norm_y_b[j] += raw[i][x_columns + j] * raw[i][x_columns + j];
          }
      }
      for(int j = 0; j < y_columns; ++j) norm_y_a[j] /= rows;

      for(int j = 0; j < y_columns; ++j) {
        norm_y_b[j] -= rows * norm_y_a[j] * norm_y_a[j];
        norm_y_b[j] /= (rows - 1);
        norm_y_b[j] = sqrt(norm_y_b[j]);
      }
    }

  }

  void norm_raw_data() {

    for(int i = 0; i < rows; ++i) {
      for(int j = 0; j < x_columns; ++j) {
        raw[i][j] -= norm_x_a[j];
        raw[i][j] /= norm_x_b[j];
      }
      for(int j = 0; j < y_columns; ++j) {
        raw[i][j + x_columns] -= norm_y_a[j];
        raw[i][j + x_columns] /= norm_y_b[j];
      }
    }
  }

  void set_order() {

    std::vector<int> p;
    p = permutation_random(rows);

    train_order.resize(0);
    valid_order.resize(rows - (train_prop * rows));

    for(int i = 0; i < train_prop * rows; ++i) {
      train_order.push_back(p[i]);
    }

    for(int i = train_prop * rows + 1; i < rows; ++i) {
      valid_order.push_back(p[i]);
    }

  }
  void get_next_train() {

    out_x = raw[0];

  }
  void get_next_valid() {

  }



};
