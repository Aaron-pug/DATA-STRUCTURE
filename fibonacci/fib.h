using Rank=int;

class Fib{
  private:
    int f,g;// f = fib(k - 1), g = fib(k)

  public:
    Fib(Rank n){ //初始化为不小于n的最小Fibonacci项
      f=1;
      g=0;
      while(g<n) next();
    }//fib(-1), fib(0)，O(log_phi(n))时间

    int get(){return g;}

    int next(){ //转至下一Fibonacci项
      g+=f;
      f=g-f;
      return g;
    }
    int prev(){
      f=g-f;
      g=g-f;
      return g;
    }
};