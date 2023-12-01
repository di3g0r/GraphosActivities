//Act 5.2 - Actividad Integral sobre el uso de códigos hash
//Diego Rodríguez Romero A01741413
//30 de noviembre de 2023

#include <iostream>
#include <fstream>
#include <sstream> 
#include <list>
#include <math.h>
#include <vector>
#include <queue>
#include <bits/stdc++.h>

using namespace::std;

class HashTable
{
    private:
        int capacity;
        int collisions;
        int rango = contarPuertos();
        list<string> *table;
        vector<int> portEntries;
    public:
        HashTable(int V){
            int size = getPrime(V);
            this->collisions = 0;
            this->capacity = size;
            table = new list<string>[capacity];
            portEntries[rango];
        }
        ~HashTable(){
            delete []table;
            std::cout << "\nDestructor: Hash Table Borrada\n";
        }

        bool checkPrime(int);
        int getPrime(int);

        void insertItem(string);

        int hashFunction(int);
        void displayHash();

};

/*SplitStrings, regresa un vector de enteros con todos los puertos*/
int splitStrings(string &s) {
    string mes, dia, hora, direccionIP;
    char ch1, ch2, ch3, ch4;
    int ipPart1, ipPart2, ipPart3, ipPart4, puerto;

    stringstream SS(s);
    SS.clear();
    SS >> mes >> dia >> hora >> direccionIP;

    SS.clear();
    SS.str(direccionIP);

    SS >> ipPart1 >> ch1 >> ipPart2 >> ch2 >> ipPart3 >> ch3 >> ipPart4  >> ch4 >> puerto;

    return puerto;
}


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
void HashTable::insertItem(string line){

    int data = splitStrings(line);

    int index = hashFunction(data);

    portEntries[data-rango] = 0;

    if(table[index].empty() != true){
        portEntries[data-rango]++;
    }
    else{
        portEntries[data-rango] = 0;
    }

    table[index].push_back(line);

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

    std::cout << "\n";

    std::cout << "Hubo un total de " << collisions << " colisiones en la Hash Table (Chaining)\n";

    std::cout << "\n";
}

void readFile(HashTable ht) {

    ifstream InputFile("bitacora.txt");
    if(!InputFile){
        cerr << "Error opening the input file." << endl;
        return;
    }

    // Read and store each entry in the vector
    string entry;
    while (getline(InputFile, entry)) {
        ht.insertItem(entry);

    }
    // Closes the file currently associated
    InputFile.close();
}

vector<string> abrirArchivo(){
    vector<string> lineas;
    ifstream InputFile("bitacora.txt");
    if(!InputFile){
        cerr << "Error opening the input file." << endl;
        return;
    }

    string entry;
    while (getline(InputFile, entry)) {
        lineas.push_back(entry);

    }
    // Closes the file currently associated
    InputFile.close();

    return lineas;
}


int contarPuertos(){
    vector<string> lineas = abrirArchivo();
    priority_queue<int> ports;

    for(int i = 0; i < lineas.size(); i++){
        int port = splitStrings(lineas[i]);
        ports.push(port);
    }

    int max = ports.top();

    while(ports.size() != 1) {
        cout << "Port: " << ports.top() << endl;
        ports.pop();
    }

    int min = ports.top();

    int rango = max - min;

    return rango;
}

void top5(vector<int> puertos){
    int tops[5];
    for(int i = 0; i < 5; i++){
        tops[i] = *max_element(puertos.begin(),puertos.end());
        puertos.erase(tops[i]);
    }
    
    
}

int main(){

    return 0;
}