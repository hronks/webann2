#pragma once

#define DEFINE_1D_VECTOR(NAME, STRUCT) \
  std::vector<float> NAME##_f; \
  std::vector<double> NAME##_d; \
  std::vector<long double> NAME##_ld; \
 \
    void NAME##_copy_from(std::vector<float> x) { \
      for(int i = 0; i < NAME##_f.size(); ++i) NAME##_f[i] = x[i];} \
    void NAME##_copy_from(std::vector<double> x) { \
      for(int i = 0; i < NAME##_d.size(); ++i) NAME##_d[i] = x[i];} \
    void NAME##_copy_from(std::vector<long double> x){ \
      for(int i = 0; i < NAME##_ld.size(); ++i) NAME##_ld[i] = x[i];} \
 \
    void NAME##_copy_to(std::vector<float> &x) {x = NAME##_f;} \
    void NAME##_copy_to(std::vector<double> &x) {x = NAME##_d;} \
    void NAME##_copy_to(std::vector<long double> &x) {x = NAME##_ld;} \
 \
  void NAME##_push() { \
    if(value_type == "float") \
      for(int i = 0; i < STRUCT##_f->NAME.size(); ++i) STRUCT##_f->NAME[i] = NAME##_f[i]; \
    if(value_type == "double") \
      for(int i = 0; i < STRUCT##_d->NAME.size(); ++i) STRUCT##_d->NAME[i] = NAME##_d[i]; \
    if(value_type == "long double") \
      for(int i = 0; i < STRUCT##_ld->NAME.size(); ++i) STRUCT##_ld->NAME[i] = NAME##_ld[i]; \
  } \
 \
  void NAME##_pull() { \
    if(value_type == "float") \
      for(int i = 0; i < STRUCT##_f->NAME.size(); ++i) NAME##_f[i] = STRUCT##_f->NAME[i]; \
    if(value_type == "double") \
      for(int i = 0; i < STRUCT##_d->NAME.size(); ++i) NAME##_d[i] = STRUCT##_d->NAME[i]; \
    if(value_type == "long double") \
      for(int i = 0; i < STRUCT##_ld->NAME.size(); ++i) NAME##_ld[i] = STRUCT##_ld->NAME[i]; \
  } \
  \
  void NAME##_resize(int x) { \
    if(value_type == "float") NAME##_f.resize(x); \
    if(value_type == "double") NAME##_d.resize(x); \
    if(value_type == "long double") NAME##_ld.resize(x); \
  }

  #define DEFINE_2D_VECTOR(NAME, STRUCT) \
    std::vector<std::vector<float>> NAME##_f; \
    std::vector<std::vector<double>> NAME##_d; \
    std::vector<std::vector<long double>> NAME##_ld; \
   \
      void NAME##_copy_from(std::vector<std::vector<float>> x) { \
        for(int i = 0; i < NAME##_f.size(); ++i) \
          for(int j = 0; j < NAME##_f[i].size(); ++j) \
            NAME##_f[i][j] = x[i][j];} \
      void NAME##_copy_from(std::vector<std::vector<double>> x) { \
        for(int i = 0; i < NAME##_d.size(); ++i) \
          for(int j = 0; j < NAME##_d[i].size(); ++j) \
            NAME##_d[i][j] = x[i][j];} \
      void NAME##_copy_from(std::vector<std::vector<long double>> x) { \
        for(int i = 0; i < NAME##_ld.size(); ++i) \
          for(int j = 0; j < NAME##_ld[i].size(); ++j) \
            NAME##_ld[i][j] = x[i][j];} \
   \
      void NAME##_copy_to(std::vector<std::vector<float>> &x) \
        {x = NAME##_f;} \
      void NAME##_copy_to(std::vector<std::vector<double>> &x) \
        {x = NAME##_d;} \
      void NAME##_copy_to(std::vector<std::vector<long double>> &x) \
        {x = NAME##_ld;} \
   \
    void NAME##_push() { \
      if(value_type == "float") \
        for(int i = 0; i < STRUCT##_f->NAME.size(); ++i) \
          for(int j = 0; j < STRUCT##_f->NAME[i].size(); ++j) \
            STRUCT##_f->NAME[i][j] = NAME##_f[i][j]; \
      if(value_type == "double") \
        for(int i = 0; i < STRUCT##_d->NAME.size(); ++i) \
          for(int j = 0; j < STRUCT##_d->NAME[i].size(); ++j) \
            STRUCT##_d->NAME[i][j] = NAME##_d[i][j]; \
      if(value_type == "long double") \
        for(int i = 0; i < STRUCT##_ld->NAME.size(); ++i) \
          for(int j = 0; j < STRUCT##_ld->NAME[i].size(); ++j) \
            STRUCT##_ld->NAME[i][j] = NAME##_ld[i][j]; \
    } \
    \
    void NAME##_push_hard() { \
      if(value_type == "float") \
        STRUCT##_f->NAME = NAME##_f; \
      if(value_type == "double") \
        STRUCT##_d->NAME = NAME##_d; \
      if(value_type == "long double") \
        STRUCT##_ld->NAME = NAME##_ld; \
    } \
   \
    void NAME##_pull() { \
      if(value_type == "float") \
        for(int i = 0; i < STRUCT##_f->NAME.size(); ++i) \
          for(int j = 0; j < STRUCT##_f->NAME[i].size(); ++j) \
            NAME##_f[i][j] = STRUCT##_f->NAME[i][j]; \
      if(value_type == "double") \
        for(int i = 0; i < STRUCT##_d->NAME.size(); ++i) \
          for(int j = 0; j < STRUCT##_d->NAME[i].size(); ++j) \
            NAME##_d[i][j] = STRUCT##_d->NAME[i][j]; \
      if(value_type == "long double") \
        for(int i = 0; i < STRUCT##_ld->NAME.size(); ++i) \
          for(int j = 0; j < STRUCT##_ld->NAME[i].size(); ++j) \
            NAME##_ld[i][j] = STRUCT##_ld->NAME[i][j]; \
    } \
    \
    void NAME##_resize(int x, int y) { \
      if(value_type == "float") { \
        NAME##_f.resize(x); \
        for(int i = 0; i < x; ++i) \
          NAME##_f[i].resize(y); \
      } \
      if(value_type == "double") { \
        NAME##_d.resize(x); \
        for(int i = 0; i < x; ++i) \
          NAME##_d[i].resize(y); \
      } \
      if(value_type == "long double") { \
        NAME##_ld.resize(x); \
        for(int i = 0; i < x; ++i) \
          NAME##_ld[i].resize(y); \
      } \
    }

#define DEFINE_0ARG_FUNCTION(TYPE, NAME, STRUCT) \
  TYPE NAME { \
    if(value_type == "float") STRUCT##_f->NAME; \
    if(value_type == "double") STRUCT##_d->NAME; \
    if(value_type == "long double") STRUCT##_ld->NAME; \
  }
