template<typename T>struct ListNode;
template<typename T>using LNP=ListNode<T>*;//list Node Position
template<typename T>struct ListNode
{
  T data;
  LNP<T> pred,succ; //数值、前驱、后继
  ListNode():data(),pred(nullptr),succ(nullptr){}
  ListNode(const T& e, p)
};
