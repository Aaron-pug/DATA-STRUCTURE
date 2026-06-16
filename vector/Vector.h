#ifndef VECTOR_H
#define VECTOR_H

#include <cstdlib>

using Rank=int;

template<typename T>
class Vector{ //向量模板类
  private:
    T* _elem; //数据区
    Rank _capa; //容量
    Rank _size; //规模

  protected:
    
    Rank binSearch(T *S,const T &e,Rank lo,Rank hi) const;
    Rank fibSearch(T *S,const T &e,Rank lo,Rank hi) const;
    Rank binSearch_b(T *S,const T &e,Rank lo,Rank hi) const;
    Rank binSearch_c(T *S,const T &e,Rank lo,Rank hi) const;
  public:
    Rank search(const T &e) const{
      return search(e,0,_size)
    } //整体查找
    // 等价于 Rank search(const Vector<T>* this, const T& e);
    // 后面const修饰的是隐式参数 this 指针
    // 约束的是：这个成员函数内部，不能修改当前对象的任何成员变量。
    Rank search(const T &e,Rank lo,Rank hi) const; //区间查找

};



#include "Vector.inl"
#endif


