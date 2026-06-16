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

template<typename T>
Rank Vector<T>::binSearch_b(T *S,const T &e,Rank lo,Rank hi) const{
  while(hi-lo>1){
    Rank mi=(lo+hi)/2;
    (e<S[mi])?hi=mi:lo=mi;
  }
  return (e==S[lo])?lo:-1;
  // 查找成功时返回对应的秩，如果有多个元素命中则返回秩的最大者
  // 查找失败时，简单返回-1，而不能指示失败的位置 
}

template<typename T>
Rank Vector<T>::fibSearch(T *S,const T &e,Rank lo,Rank hi) const{
  for(Fib fib(hi-lo);lo<hi;){
    while(hi-lo<fib.get()) fib.prev();//保证fib.get()为不大于向量长度的最大fib数
    Rank mi=lo+fib.get()-1;//确定形如Fib(k)-1的轴点
    if(e<S[mi]) hi=mi;
    else if(e>S[mi]) lo=mi+1;
    else return mi;
  }
  return -1;
}

template<typename T>
Rank Vector<T>::binSearch_c(T *S,const T &e,Rank lo,Rank hi) const{
  while(lo<hi){
    Rank mi=(lo+hi)/2;
    e<S[mi]?hi=mi:lo=mi+1;
  }
  return lo-1;//查找成功时返回对应的秩，如果有多个元素命中则返回秩的最大者
  //只有当返回值等价-1（无符号下为UINT32_MAX）时，才是完全查找失败，数组全部元素都比目标值大；
  //其余返回合法下标的情况，哪怕没有相等元素，也只是没有精准匹配，不属于完全失败。
}

template<typename T>
void Vector<T>::sort(Rank lo, Rank hi){
  if(hi-lo<2) return;
  
}
