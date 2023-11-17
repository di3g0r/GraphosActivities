//Act 5.1: Implmentacion de operaciones en sets
//Diego Rodríguez Romero A01741413
// de noviembre de 2023

 #include <iostream>
#include <list>
#include <math.h>

using namespace::std;

class HashTable
{
    private:
        int capacity;
        list<int> *table;
        int *array;
    public:
        HashTable(int V){
            int size = getPrime(V);
            this->capacity = size,
            table = new list<int>[capacity];
            array = new int[capacity]{NULL};
        }
        ~HashTable(){
            delete []table;
            std::cout << "\nDestructor: Hash Table Borrada\n";
        }

        bool checkPrime(int);
        int getPrime(int);

        void insertItem(int);
        void deleteItem(int);

        int hashFunction(int);
        void displayHash();
};

bool HashTable::checkPrime(int n){
    if(n == 1 || n == 0){
        return false;
    }

    int raiz = sqrt(n);
    for(int i = 2; i <= raiz; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

int HashTable::getPrime(int n){
    if(n % 2 == 0){
        n++;
    }

    while(checkPrime(n) == false){
        n += 2;
    }
    return n;
}

int HashTable::hashFunction(int key){
    return (key % capacity);
}

void HashTable::insertItem(int data){
    int i = 1;

    int index = hashFunction(data);

    table[index].push_back(data);

    while(index < capacity){
        if(array[index] == NULL){
            array[index] = data;
        }
        else{
            index = index + pow(i, 2);
            i++;
            if(index > capacity){
                index = capacity;
                while(array[index] != NULL){
                    if(array[index] != NULL){
                        index--;
                    }
                    else if(array[index] == NULL){
                        array[index] = data;
                    }
                }
            }
            if(index < capacity){
                array[index] = data;
            }
        }
    }
}

void HashTable::deleteItem(int key){
    int index = hashFunction(key);

    list<int>::iterator i;
    for(i = table[index].begin(); i != table[index].end(); i++){
        if(*i == key){
            break;
        }
    }

    if (i != table[index].end()){
        table[index].erase(i);
    }
}

void HashTable::displayHash(){
    for(int i = 0; i < capacity; i++){
        std::cout << "Table[" << i << "]";

        for(auto x : table[i]){
            std::cout << "-->" << x;
        }
        std::cout << "\n\n";
    }

    for(int j = 0; j < capacity; j++){
        std::cout << "[" << j << "] = " << array[j] << "\n";
    }

    std::cout << "\n";
}

int main(){
    int data[] = {231,321,212,321,433,262};

    int size = sizeof(data) / sizeof(data[0]);

    HashTable h(size);

    for(int i = 0; i < size; i++){
        h.insertItem(data[i]);
    }

    h.displayHash();
}

