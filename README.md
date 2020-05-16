## An example of showing c++_crtp usage
奇异值递归模板模式crtp(curiously recurring template pattern)是静态分发，区别于c++多态虚函数调用使用的动态分发，好处是减少了类实例存储虚函数表指针的和虚函数表的存储空间以及传统调用虚函数时由于查表操作效率较慢的问题，具体使用形式是基类定义时使用模板参数Derive,并在各个派生类中实现的公共接口函数里面把this*指针用static_cast转换Derive*指针，各个派生类在定义时采用统一形式:
class Derive1 : public Base<Derive1>
class Derive2 : public Base<Derive2>
为了防止class Derive2 : public Base<Derive1>这种误写操作，在基类中把构造函数声明在private或者protected中，并把模板参数Derive声明为友元，这样派生类必然会调用基类的构造函数，且class Derive2 : public Base<Derive1>这种误写在编译时编译器会报错；
singleton例子里面主要使用crtp实现了子类的单例模式实现，单例模式的getInstance()放在基类里面实现:
template<typename Derived>
class Singleton{
......
static Derived& get_instance(){
        static Derived instance;
        return instance;
......
};
在子类中必须有友元类声明:
class DerivedSingle:public Singleton<DerivedSingle>{
friend class Singleton<DerivedSingle>;
......
};
crtp在使用时把公共的部分放在基类中实现（使用派生类类型T）,子类中单独实现的部分使用static_cast转换成派生类指针，然后调用派生类接口，派生类中实现同名的接口函数，效果上类似于多态.
crtp的缺点是没有了多态的动态绑定，在多层次继承关系中不太建议使用，继承关系会容易混乱.
