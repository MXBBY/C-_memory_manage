#include <cstddef>
#include<iostream>
#include<string>

using namespace std;

namespace lin4{
    class Foo{
        public:
            int _id;
            long _data;
            string _str;
        public:
            static void* operator new(size_t size);
            static void   operator delete(void* deadObject,size_t size);
            static void* operator new[](size_t size);
            static void   operator delete[](void* deadObject,size_t size);

            Foo():_id(0){
                cout<<"default ctor.this="<<this<<"    _id="<<_id<<endl;
            } 
            Foo(int i):_id(i){
                cout<<"ctor.this="<<this<<"    _id="<<_id<<endl;
            }
            ~Foo(){
                cout<<"dtor.this="<<this<<"    _id="<<_id<<endl;
            }
    };

    void* Foo::operator new(size_t size){
        Foo* p=(Foo*)malloc(size);
        cout<<"Foo::operator new(),size="<<size<<"\t  return:"<<p<<endl;

        return p;
    }

    void Foo::operator delete(void* pdead,size_t size){
        cout<<"Foo::operator delete(),pdead="<<pdead<<"    size="<<size<<endl;
        free(pdead);
    }
    void* Foo::operator new[](size_t size)
    {
        Foo* p = (Foo*)malloc(size);   
        cout << "Foo::operator new[](), size=" << size << "\t  return: " << p << endl;  
  
        return p;
    }

    void Foo::operator delete[](void* pdead, size_t size)
    {
        cout << "Foo::operator delete[](), pdead= " << pdead << "  size= " << size << endl;
  
        free(pdead);
    }


    void test_overload_operator_new_and_array_new(){
        cout<<"\n test_overload_operator_new_and_array_new()....."<<endl;
        cout<<"sizeof(Foo)="<<sizeof(Foo)<<endl;
        {
            Foo* p=new Foo(7);
            delete p;

            cout<<"\n"<<endl;

            Foo* pArray=new Foo[5];
            delete[] pArray;
        }
        {
            cout<<"\n test global expression ::new and ::new[]"<<endl;

            Foo* p=::new Foo(7);
            ::delete p;

            Foo* pArray=::new Foo[5];
            ::delete[] pArray;
        }
    }
}

int main(){
    lin4::test_overload_operator_new_and_array_new();
    return 1;
}
