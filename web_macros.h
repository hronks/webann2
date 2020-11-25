#pragma once

#define NAME_DF "dense_float"
#define NAME_DD "dense_double"
#define NAME_DLD "dense_float"

#define DEFINE_VECTOR_TYPE( VECTOR, SIZE) \
  if(type == NAME_DF) { \
    data_type temp; \
    temp.f = 0; \
    VECTOR.resize(SIZE, temp); \
  } \
  if(type == NAME_DD) { \
    data_type temp; \
    temp.d = 0; \
    VECTOR.resize(SIZE, temp); \
  } \
  if(type == NAME_DLD) { \
    data_type temp; \
    temp.ld = 0; \
    VECTOR.resize(SIZE, temp); \
  }

  #define PULL_OBJECT( TYPE, NAME ) \
    TYPE NAME { \
      if(type == NAME_DF) l.df->NAME; \
      if(type == NAME_DD) l.dd->NAME; \
      if(type == NAME_DLD) l.dld->NAME; \
  }
