#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib> //rand()
#include "../fibonacci/fib.h" //fibSearch()
#include <algorithm> //swap()
#include <cstring> //menset()

using Rank=int;
using ll=long long;



template<typename T>
class Vector{ //向量模板类
  private:
    T* _elem; //数据区
    Rank _capa; //容量
    Rank _size; //规模

  protected:
    Rank binSearch(T *S,const T& e,Rank lo,Rank hi) const; //二分查找a
    Rank binSearch_b(T *S,const T& e,Rank lo,Rank hi) const; //二分查找b
    Rank binSearch_c(T *S,const T& e,Rank lo,Rank hi) const; //二分查找c
    Rank fibSearch(T *S,const T& e,Rank lo,Rank hi) const; //斐波那契查找
    void bubbleSort(Rank lo,Rank hi); //起泡排序
    void merge(Rank lo,Rank mi,Rank hi); //二路归并
    void mergeSort(Rank lo,Rank hi); //归并排序
    void merge(Rank lo,Rank mi,Rank hi,ll& invCount); 
    void mergeSort(Rank lo,Rank hi,ll& invCount); 

  public:
    Rank search(const T &e) const{
      return search(e,0,_size);
    } //整体查找
    // 等价于 Rank search(const Vector<T>* this, const T& e);
    // 后面const修饰的是隐式参数 this 指针
    // 约束的是：这个成员函数内部，不能修改当前对象的任何成员变量。
    Rank search(const T &e,Rank lo,Rank hi) const; //区间查找
    void sort(Rank lo, Rank hi); void sort() { sort( 0, _size ); } //排序
    ll countInversion(Rank lo,Rank hi); //统计逆序对数量
    ll countInversion() { return countInversion(0,_size); }
};

struct Bitmap{
  unsigned char* M; //8bit
  //unsigned char 范围 0 ~ 255，只有正数。
  // M 是指针，代表连续一长串 unsigned char 盒子的起始地址。
  Rank N,size; //数组M共有8*N个bit，其中size个bit的值是 1，其余为0
  void init(Rank n){
    M=new unsigned char[N = (n+7)/8];
    // (n+7)/8 是向上取整，把 bit 数量换算成字节数
    memset( M, 0, N );
  }

};


#include "Vector.inl"
#endif

