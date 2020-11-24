#include <cstddef>
#include <iostream>

using namespace std;

namespace lin6{
    class Airplane{
        private:
            struct AirplaneRep{
                unsigned long miles;
                char type;
            };
        private:
            union{
                AirplaneRep rep;
                Airplane* next;
            };
        public:
            Airplane(){
                cout<<"ctor.Airplane()"<<endl;
            }
            unsigned long getMiles(){
                return rep.miles;
            }
            char getType(){
                return rep.type;
            }
            Airplane*  getNext(){
                return next;
            }
            void set(unsigned long m,char t){
                rep.miles=m;
                rep.type=t;
            }
        public:
            static void* operator new(size_t size);
            static void operator delete(void* deadObject,size_t size);
        private:
            static const int BLOCK_SIZE;
            static Airplane* headOfFreeList;
    };

    Airplane* Airplane::headOfFreeList ;
    const int Airplane::BLOCK_SIZE =512;

    void* Airplane::operator new(size_t size){
        if(size!=sizeof(Airplane)){
            return ::operator new(size);
        }
        Airplane* p=headOfFreeList;
        if(p){
            cout<<"take one block."<<endl;
            headOfFreeList=p->next;
        }
        else{
            cout<<"malloc(512block)"<<endl;
            Airplane* newBlock=static_cast<Airplane*>(::operator new(BLOCK_SIZE*sizeof(Airplane)));
            for(int i=1;i<BLOCK_SIZE-1;i++){
                newBlock[i].next=&newBlock[i+1];            
            }
            newBlock[BLOCK_SIZE-1].next=0;
            p=newBlock;
            headOfFreeList=&newBlock[1];
        }
        return p;
    }

    void Airplane::operator delete(void* deadObjext,size_t size){
        if(deadObjext==0) return;
        if(size!=sizeof(Airplane)){
            ::operator delete(deadObjext);
            return;
        }
        Airplane *carcass=static_cast<Airplane*>(deadObjext);

        carcass->next=headOfFreeList;
        headOfFreeList=carcass;
    }

    void test_per_class_allocator_2(){
        cout<<sizeof(Airplane)<<endl;
        size_t const N=100;
        Airplane* p[N];
        for(int i=0;i<N;i++){
            p[i]=new Airplane;
        }
        p[1]->set(1000,'A');
        p[5]->set(2000,'B');
        p[9]->set(500000,'C');
        cout<<p[1]<<"    "<<p[1]->getType()<<"    "<<p[1]->getMiles()<<endl;
        cout<<p[5]<<"    "<<p[5]->getType()<<"    "<<p[5]->getMiles()<<endl;

        for(int i=0;i<10;i++){
            cout<<p[i]<<endl;
        }
        for(int i=0;i<N;i++){
            delete p[i];
        }
    }
}

int main(){
    lin6::test_per_class_allocator_2();
    return 1;
}