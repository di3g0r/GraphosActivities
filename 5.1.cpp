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
        int capArray;
        int collisions;
        list<int> *table;
        int *array;
    public:
        HashTable(int V){
            int size = getPrime(V);
            this->collisions = 0;
            this->capacity = size;
            this->capArray = 2 * capacity;
            table = new list<int>[capacity];
            array = new int[capArray]{0};
        }
        ~HashTable(){
            delete []table;
            delete []array;
            std::cout << "\nDestructor: Hash Table Borrada\n";
        }

        bool checkPrime(int);
        int getPrime(int);

        void insertItem(int);
        void insertItemArray(int);

        void deleteItem(int);

        int hashFunction(int);
        void displayHash();
};

/*checkPrime(int n), esta funcion recibe un entero como argumento
y revisa si es un numero primo o no. Complejidad O(1)*/
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

/*getPrime(int n), recibimos un numero como parametro y apoyandonos con
checkPrime(int) verificamos si el numero es o no primo, en caso de no serlo
sumamos 2 al numero hasta que se haga primo. Complejidad O(1)*/
int HashTable::getPrime(int n){
    if(n % 2 == 0){
        n++;
    }

    while(checkPrime(n) == false){
        n += 2;
    }
    return n;
}

/*hashFunction(int key), esta funcion es que nos da nuestro valor
de indice, realiza una operacion matematica con el numero que recibe
y encuentra el indice donde debe de ser guardado dicho valor
Complejidad O(1)*/
int HashTable::hashFunction(int key){
    float knuth = (sqrt(5) - 1) / 2 ;
    float x = capacity * (fmod(key*knuth,1));
    x = floor(x);
    int k = static_cast<int>(x);
    return k;
    //return (key % (capacity));
}

/*insertItem(int data), esta funcion agrega elementos a la hash
table (list de enteros), encuentra el indice llamando 
hashFunction(int key) y agrega el elementos en dicho indice
en caso de que el elemento donde debe de ser agregado 
el elemento ya tenga elementos ahi, sumamos 1 a nuestro
contador de colisiones Complejidad O(1)*/
void HashTable::insertItem(int data){

    int index = hashFunction(data);

    if(table[index].empty() != true){
        collisions++;
    }

    table[index].push_back(data);

}

/*insertItemArray(int data), esta funcion tiene el mismo
objetivo que la anterior, solo que inserta el elemento a un
array de ints y maneja las colisiones usando quadratic probing 
Complejidad O(n)*/
void HashTable::insertItemArray(int data){
    int i = 1;

    int index = hashFunction(data);

    if(array[index] == 0){
        array[index] = data;
    }

    else{
        if(index >= capArray){
            std::cout << "El elemento " << data << " se sale de la tabla\n";
            index--;
            while(array[index] != 0){
                index--;
            }
            array[index] = data;
        }
        else{
            index = index + (i * i);
            if(array[index] == 0){
                array[index] = data;
            }
            else{
                std::cout << "El elemento " << data << " tuvo una colision con " << array[index] << "\n";
                while(array[index] != 0 && index < capArray){
                    i++;
                    index = index + (i * i);
                }
                array[index] = data;
            }
        }
    }
}

/*deleteItem(int key), recibe un elemento el cual queremos 
borrar de la hashTable, y lo busca en su indice correspondiente
para borrarlo, en caso de que no este ahi, recorre el array o lista
a partir de esa posicion para encontrarlo. Complejidad O(n)*/
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

    //Hacemos 0 el elemento en el array
    for(int j = index; index < capArray; index++){
        if(array[index] == key){
            array[index] == 0;
        }
    }

}

/*displayHash(), imprime la HashTable en sus 2 formatos
asi como el num total de colisiones que ocurrieron
Complejidad O(n)*/
void HashTable::displayHash(){
    for(int i = 0; i < capacity; i++){
        std::cout << "Table[" << i << "]";

        for(auto x : table[i]){
            std::cout << "-->" << x;
        }
        std::cout << "\n\n";
    }

    for(int j = 0; j < capArray; j++){
        std::cout << "[" << j << "] = " << array[j] << "\n";
    }

    std::cout << "Hubo un total de " << collisions << " colisiones en la Hash Table\n";

    std::cout << "\n";
}

int main(){
    int data[] = {231,321,212,321,433,262,277,401};

    int size = sizeof(data) / sizeof(data[0]);

    HashTable h(size);

    for(int i = 0; i < size; i++){
        h.insertItem(data[i]);
        h.insertItemArray(data[i]);
    }

    h.displayHash();
}