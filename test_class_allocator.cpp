#include <iostream>
#include <cstddef>

using namespace std;

namespace lin7{
    class allocator{
        private:
            struct obj{
                struct obj* next;
            };
        public:
            void* allocate(size_t);
            void   deallocate(void*,size_t);
            void check();
        private:
            obj* freeStore=nullptr;
            const int CHUNK=5;    
    };

    void* allocator::allocate(size_t size){
        obj* p;
        if(!freeStore){
            size_t chunk=size*CHUNK;
            freeStore=p=(obj*)malloc(chunk);
            for(int i=0;i<(CHUNK-1);i++){
                p->next=(obj*)((char*)p+size);
                p=p->next;
            }
            p->next=nullptr;
        }
        p=freeStore;
        freeStore=freeStore->next;
        return p;
    }

    void allocator::deallocate(void* p,size_t size){
        ((obj*)p)->next=freeStore;
        freeStore=(obj*)p;
    }

    #define DECLARE_POOL_() \
    public:\
        static void* operator new(size_t size){ \
            return myAlloc.allocate(size); \
        } \
        static void operator delete(void* pdead,size_t size){ \
            return myAlloc.deallocate(pdead,size); \
        } \
    protected: \
        static allocator myAlloc;

    #define IMPLEMNT_POOL_ALLOC(class_name) \
        allocator class_name::myAlloc;

    class Foo{
        public:
            long L;
            string str;
           
        public:
            Foo():L(0){}
            Foo(long l):L(l){}
        DECLARE_POOL_();
    };
    IMPLEMNT_POOL_ALLOC(Foo);
    void test_Foo(){
        int N=100;
        Foo* test[N];
        for(int i=0;i<N;i++){
            test[i]=new Foo;
            cout<<"test[i]="<<test[i]<<endl;
        }
        for(int i=0;i<N;i++){
            delete test[i];
        }
    }
}

int main(){
    lin7::test_Foo();
    return 1;
}