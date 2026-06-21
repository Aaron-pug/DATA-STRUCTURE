#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib> //rand()
#include "../fibonacci/fib.h" //fibSearch()

using Rank=int;

template<typename T>
void swap(T& a,T& b){
  T temp=a;
  a=b;
  b=temp;
}

template<typename T>
class Vector{ //向量模板类
  private:
    T* _elem; //数据区
    Rank _capa; //容量
    Rank _size; //规模

  protected:
    Rank binSearch(T *S,const T &e,Rank lo,Rank hi) const; //二分查找a
    Rank fibSearch(T *S,const T &e,Rank lo,Rank hi) const; //斐波那契查找
    Rank binSearch_b(T *S,const T &e,Rank lo,Rank hi) const; //二分查找b
    Rank binSearch_c(T *S,const T &e,Rank lo,Rank hi) const; //二分查找c
    void bubbleSort(Rank lo,Rank hi); //起泡排序
    void merge(Rank lo,Rank mi,Rank hi); //二路归并
    void mergeSort(Rank lo,Rank hi); //归并排序

  public:
    Rank search(const T &e) const{
      return search(e,0,_size)
    } //整体查找
    // 等价于 Rank search(const Vector<T>* this, const T& e);
    // 后面const修饰的是隐式参数 this 指针
    // 约束的是：这个成员函数内部，不能修改当前对象的任何成员变量。
    Rank search(const T &e,Rank lo,Rank hi) const; //区间查找
    void sort(Rank lo, Rank hi); void sort() { sort( 0, _size ); } //排序
     
};



#include "Vector.inl"
#endif


