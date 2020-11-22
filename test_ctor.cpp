#include <iostream>
#include<string>

using namespace std;

namespace lin1{
    class A{
        public:
            int id;

            A():id(0){
                cout<<"default ctor.this="<<this<<"    id="<<id<<endl;
            }
            A(int i):id(i){
                cout<<"ctor.this="<<this<<"    id="<<id<<endl;
            }
            ~A(){
                cout<<"dtor.this="<< this<<"    id="<<id<<endl;
            }
    };

    void test_call_ctor_directly(){
        cout<<"\n test_call_ctor_directly().........";
        string* pstr=new string;
        cout<<"str.addr= "<<pstr<<endl;
        cout<<"str= "<<*pstr<<endl;

        A* pA=new A(1);
        cout<<pA->id<<endl;
        delete pA;

        void* p=::operator new(sizeof(A));
        cout << "p="<<p<<endl;
        pA=static_cast<A*>(p);
        cout<<pA->id<<endl;

        pA->~A();
        ::operator delete(pA);
    }
}
int main(){
        lin1::test_call_ctor_directly();
        return 1;
    }