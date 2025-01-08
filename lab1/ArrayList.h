#include <string>

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

class ArrayList
{
    public: 
        ArrayList();
        ~ArrayList();

        void insert(std::string item);
        bool remove(std::string item);
        int find(std::string item);

        void print(std::ostream &out);
        int size();

    private: 
        std::string *arr; 
        int numItems;
        int capacity; 

        // Helper function for remove()
        void shift();

        // You write these functions
        void expand();
        void shrink();
        void resize(int);
};

#endif 
