#include <iostream>
template <typename T>
struct Base {
public:
  void Do() {
      T* derived = static_cast<T*>(this);
      derived->Do(); 
      //static_cast<T*>(this)->Do();
  }
private:
    Base() {
        std::cout << "Base()" << std::endl;
    }
    friend T;
};

struct Derived1 : public Base<Derived1> {
//public:
    void Do() {
        std::cout << "Derived1 Do()\n" << std::endl;
    }
};
struct Derived2 : public Base<Derived2> {
//public:
    void Do() {
        std::cout << "Derived2 Do()\n" << std::endl;
    }
};
int main() {
    Derived1 d1;
    d1.Do();
    Derived2 d2;
    d2.Do();
    return 0;
}
