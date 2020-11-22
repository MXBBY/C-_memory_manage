#include <iostream>
#include <vector>

using namespace std;

namespace lin5{
    class Bad{};
    class Foo{
        public:
            Foo(){
                cout<<"Foo::Foo()"<<endl;
            }
            Foo(int){
                cout<<"Foo::Foo()"<<endl;
                throw Bad();
            }

            void* operator new(size_t size){
                cout<<"operator new(size_t size),size="<<size<<endl;
                return malloc(size);
            }

            void* operator new(size_t size,void* start){
                cout<<"operator new(size_t,size,void* start),size="<<size<<endl;
                return start;
            }

            void* operator new(size_t size,long extra){
                cout<<"operator new(size_t size,long extra),size="<<size<<"    extra="<<extra<<endl;
                return malloc(size+extra);
            }

            void* operator new(size_t size,long extra,char init){
                cout<<"operator new(size_t size,long extra,char init),size="<<size<<"    extra="<<extra<<"    init="<<init<<endl;
                return malloc(size+extra); 
            }

        private:
            int m_i;
        };

        void test_overload_placement_new(){
            cout<<"\n\n test_overload_placement_new()......\n";

            Foo start;

            Foo* p1=new Foo;
            Foo* p2=new(&start)Foo;
            Foo* p3=new(100) Foo;
            Foo* p4=new(100,'a') Foo;

            Foo* p5=new(100)Foo(1);
        }
}

int main(){
    lin5::test_overload_placement_new();
    return 1;
}