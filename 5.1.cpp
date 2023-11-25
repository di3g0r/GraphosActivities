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
        int collisions;
        list<int> *table;
        int *array;
    public:
        HashTable(int V){
            int size = getPrime(V);
            this->collisions = 0;
            this->capacity = size;
            table = new list<int>[capacity];
            array = new int[capacity]{0};
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

/*checkPrime(int n),Esta función recibe un entero como argumento y revisa si 
es un numero primo o no, regresa un valor booleano. Complejidad O(Raiz de n)*/
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

/*getPrime(int n), Recibimos un numero como parámetro y apoyándonos
 con checkPrime(int) verificamos si el número es o no primo, en caso
  de no serlo, sumamos 2 al número hasta que se haga primo. Complejidad O(n)*/
int HashTable::getPrime(int n){
    if(n % 2 == 0){
        n++;
    }

    while(checkPrime(n) == false){
        n += 2;
    }
    return n;
}

/*hashFunction(int key), Esta función es que nos da nuestro valor de índice,
 realiza una operación matemática con el número que recibe y encuentra el índice
  donde debe de ser guardado dicho valor. En este caso utilice la función
 de Universal Hashing. Complejidad O(1)*/
int HashTable::hashFunction(int key){
    float knuth = (sqrt(5) - 1) / 2 ;
    float x = capacity * (fmod(key*knuth,1));
    x = floor(x);
    int k = static_cast<int>(x);
    return k;
    //return (key % (capacity));
}

/*insertItem(int data), Esta función agrega elementos a la
hash table (list de enteros), encuentra el índice llamando 
hashFunction(int key) y agrega el elementos en dicho índice
en caso de que el elemento donde debe de ser agregado  el elemento
ya tenga elementos ahí, sumamos 1 a nuestro contador de colisiones
 y lo agregamos al final de la lista de este indice. Complejidad O(1)*/
void HashTable::insertItem(int data){

    int index = hashFunction(data);

    if(table[index].empty() != true){
        collisions++;
    }

    table[index].push_back(data);

}

/*insertItemArray(int data), Esta función tiene el mismo objetivo
que la anterior, solo que inserta el elemento a un array de enteros
y maneja las colisiones usando quadratic probing, en caso de que el
índice ya este ocupado empieza a sumar 1 al índice, si ese lugar 
también ya está ocupado, suma el cuadrado de 2, si también está 
ocupado suma el cuadrado de 3, y así sucesivamente hasta encontrar 
un lugar donde guardar dicho valor
Complejidad O(n)*/
void HashTable::insertItemArray(int data){
    int i = 1;

    int index = hashFunction(data);

    if(array[index] == 0){
        array[index] = data;
    }

    else{
        while (index < capacity){
            index = (index + i * i) % capacity;
            i++;

            if (array[index] == 0) {
                array[index] = data;
                break;
            }
        }
        if (index >= capacity) {
            std::cout << "El elemento " << data << " se sale de la tabla\n";
        }
    }
}

/*deleteItem(int key), Recibe un elemento el cual queremos
borrar de la hashTable, y lo busca en su índice correspondiente 
para borrarlo, en caso de que no esté ahí, recorre el array o lista
a partir de esa posición para encontrarlo. Complejidad O(1+(n/m))*/
void HashTable::deleteItem(int key){
    int index = hashFunction(key);

    // Hacemos 0 el elemento en el array
    if (array[index] == key) {
        array[index] = 0;
    } else {
        for (int j = index; j < capacity; j++) {
            if (array[j] == key) {
                array[j] = 0;
                break;
            }
        }
    }

    // También eliminamos el elemento de la lista
    list<int>::iterator i;
    for (i = table[index].begin(); i != table[index].end(); i++) {
        if (*i == key) {
            break;
        }
    }

    if (i != table[index].end()) {
        table[index].erase(i);
    }

    // Libera solo la memoria de array si no es nulo
    
}


/*displayHash(), Imprime la HashTable en sus 2 formatos
así como el número total de colisiones que ocurrieron
Complejidad O(n2)*/
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

    std::cout << "Hubo un total de " << collisions << " colisiones en la Hash Table\n";

    std::cout << "\n";
}

int main(){
    int data[] = {256,300,145,391,228,337};

    int size = sizeof(data) / sizeof(data[0]);

    HashTable h(size);

    for(int i = 0; i < size; i++){
        h.insertItem(data[i]);
        h.insertItemArray(data[i]);
    }

    h.displayHash();

    h.deleteItem(337);

    std::cout << "\nBorramos el 337\n";

    h.displayHash();
}