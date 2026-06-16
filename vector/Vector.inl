#ifndef VECTOR_H
#include "Vector.h"
#endif

template<typename T>
Rank Vector<T>::search(const T &e,Rank lo,Rank hi) const{
  return(rand()%2)?
  binSearch( _elem, e, lo, hi ):fibSearch( _elem, e, lo, hi );
}

template<typename T>
Rank Vector<T>::binSearch(T *S,const T &e,Rank lo,Rank hi) const{
  while(lo<hi){
    Rank mi=(lo+hi)/2;
    if(e<S[mi]) hi=mi;
    else if(e>S[mi]) lo=mi+1;
    else return mi;
  }
  return -1;
}

