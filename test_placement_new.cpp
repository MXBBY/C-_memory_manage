#include <iostream>
#include<new>

using namespace std;

namespace lin2{
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

    void test_array_new_and_placement_new(){
        cout<<"\n test_placement_new()"<<endl;
    
        size_t size=3;
{
        //test 1
        A* buf=(A*)(new char[sizeof(A)*size]);
        A* tmp=buf;

        cout<<"buf="<<buf<<"    tmp="<<tmp<<endl;

        for(int i=0;i<size;i++){
            new(tmp++) A(i);
        }
        cout<<"buf="<<buf<<"    tmp="<<tmp<<endl;
        delete buf;
        //!deletet[] buf; 
        cout<<"\n\n";
    }
    {
        //test 2
        A* buf=new A[size];
        A*tmp=buf;
        
        cout<<"buf="<<buf<<"    tmp="<<tmp<<endl;

        for(int i=0;i<size;i++){
            new(tmp++) A(i);
        }
        cout<<"buf="<<buf<<"    tmp="<<tmp<<endl;

        delete[] buf;
    }
    }
}

int main(){
    lin2::test_array_new_and_placement_new();
    return 1;
}