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
  switch(rand()%6){
    case 1:bubbleSort(lo,hi); break; //起泡排序
    case 2:selectionSort(lo,hi); break; //选择排序（习题）
    case 3:mergeSort(lo,hi); break; //归并排序
    case 4:heapSort(lo,hi); break; //堆排序（第12章）
    case 5:quickSort(lo,hi); break; //快速排序（第14章）
    default:shellSort(lo,hi); break; //希尔排序（第14章）
  }
}

// template<typename T>
// void Vector<T>::bubbleSort(Rank lo,Rank hi){
//   while(lo<--hi){
//     for(Rank i=lo;i<hi;i++){
//       if(_elem[i]>_elem[i+1]) swap(_elem[i],_elem[i+1]);
//     }
//   }
// }

template<typename T>
void Vector<T>::bubbleSort(Rank lo,Rank hi){
  for(Rank last;lo<hi;hi=last){
    last=lo;
    for(Rank i=lo+1;i<hi;i++)
      if(_elem[i-1]>_elem[i])
        swap(_elem[i-1],_elem[i]),last=i;
  }
} //时间复杂度最优O(n)、最坏O(n^2)、平均O(n^2)

template<typename T>
void Vector<T>::mergeSort(Rank lo,Rank hi){
  if(hi-lo<2) return;
  Rank mi=(lo+hi)/2;
  mergeSort(lo,mi);mergeSort(mi,hi);
  merge(lo,mi,hi); //O(n)
} //最好、最坏、平均的时间复杂度均为O(nlogn)

template<typename T>
void Vector<T>::merge(Rank lo,Rank mi,Rank hi){
  T* S=_elem+lo;
  Rank la=mi-lo; T* A=new T[la]; //A[0,la)是S的前缀
  for(Rank i=0;i<la;i++) A[i]=S[i];
  Rank lb=hi-mi; T* B=S+la; //B[0,lb)是S的后缀
  Rank a,b,s=0;//a：A的读取指针；b：B的读取指针；s：S的写入指针
  while((a<la)&&(b<lb)){
    S[s++]=(A[a]<=B[b])?A[a++]:B[b++];
  }
  while(a<la) S[s++]=A[a++]; //若B先耗尽
  delete[] A;
}