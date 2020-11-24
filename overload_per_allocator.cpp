#include <cstddef>
#include <iostream>

using namespace std;

namespace lin3{
    class Screen{
        private:
            int i;
        public :
            Screen(int x):i(x){};
            int get(){
                return i;
            }
            void* operator new(size_t);
            void   operator delete(void*,size_t);
        private:
            Screen* next;
            static Screen* freeStore;
            static const int screenChunk;
    };

    Screen* Screen::freeStore=0;
    const int Screen::screenChunk=24;

    void* Screen::operator new(size_t size){
        Screen *p;
        if(!freeStore){
            cout<<"\n这里调用了一次Screen::operator new()"<<endl;
            size_t chunk=screenChunk *size;
            freeStore=p=reinterpret_cast<Screen*>(new char[chunk]);
            for(;p!=&freeStore[screenChunk-1];++p){
                p->next=p+1;
            }
            p->next=0;
        }
        p=freeStore;
        freeStore=freeStore->next;
        return p;
    }
    
    void Screen::operator delete(void *p,size_t){
        (static_cast<Screen*>(p))->next=freeStore;
        freeStore=static_cast<Screen*>(p);
    }

    void test_per_calss_allocator_1(){
        cout<<"\n test_per_class_allocator_1()"<<endl;
        cout<<sizeof(Screen)<<endl;
        
        size_t const N=100;
        Screen* p[N];

        for(int i=0;i<N;i++){
            p[i]=new Screen(i);
        }

        for(int i=0;i<N;i++){
            cout<<p[i]<<endl;
        }

        for(int i=0;i<N;i++){
            delete p[i];
        }
    }
}

int main(){
    lin3::test_per_calss_allocator_1();
    return 1;
}