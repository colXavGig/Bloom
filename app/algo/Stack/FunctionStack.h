#pragma once
#include <stdio.h>
#include <stdlib.h>


class Juxtapose;

struct task{
    Juxtapose* instance;
    const char *type;
    const char *signature1;
    const char *signature2;

    task(Juxtapose *inst,const char * type, const char *signature1, const char *signature2)
        :instance(inst), type(type), signature1(signature1), signature2(signature2){} 
};
/**
 * class pour comparer deux FileTrees dans le garden
 */
class FunctionStack{
    private:
        task **list;
        size_t size;
        size_t capacity;

    public:
        FunctionStack():list(nullptr),size(0),capacity(1){}
        /**
         * @param task enqueue une tache
         */
        void push(task *);
        /**
         * si size < 0 retourn false
         * @param out dequeue une tache
         */
        bool Trypop(task *&out);

};