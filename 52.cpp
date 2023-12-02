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
        int rango;
        list<string> *table;
        vector<int> portEntries;
    public:
        HashTable(int V){
            int rango = contarPuertos();
            int size = getPrime(V);
            this->capacity = size;
            table = new list<string>[capacity];
            portEntries = vector<int>(3000);
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

        void top5(vector<int>);
        vector<int> getPortEntries();

        vector<string> abrirArchivo();
        int contarPuertos();

        int minimo();
};

/*SplitStrings, regresa un vector de enteros con todos los puertos*/
int splitStrings(string &s) {
    string token;
    istringstream tokenStream(s);

    while (getline(tokenStream, token, ':')) {
    }
    istringstream portStream(token);

    int port;
    portStream >> port;
    return port;
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
    int sum = 0;
    while (key != 0) {
        sum += key % 10;
        key /= 10;
    }
    return sum % capacity;
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

    if(table[index].empty() != true){
        portEntries[data-4001]++;
    }
    /*else{
        portEntries[data-3000] = 0;
    }*/

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

    std::cout << "\n";
}

vector<int> HashTable::getPortEntries(){
        return portEntries;
}

void readFile(HashTable &ht) {

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

vector<string> HashTable::abrirArchivo(){
    vector<string> lineas;
    ifstream InputFile("bitacora.txt");
    if(!InputFile){
        cerr << "Error opening the input file." << endl;
    }

    string entry;
    while (getline(InputFile, entry)) {
        lineas.push_back(entry);

    }
    // Closes the file currently associated
    InputFile.close();

    return lineas;
}


int HashTable::contarPuertos(){
    vector<string> lineas = abrirArchivo();
    priority_queue<int> ports;

    for(int i = 0; i < lineas.size(); i++){
        int port = splitStrings(lineas[i]);
        ports.push(port);
    }

    int max = ports.top();

    while(ports.size() != 1) {
        ports.pop();
    }

    int min = ports.top();

    int rango = max - min;

    return rango;
}

int HashTable::minimo(){
    vector<string> lineas = abrirArchivo();
    priority_queue<int> ports;

    while(ports.size() != 1) {
        ports.pop();
    }

    int min = ports.top();

    return min;
}

void HashTable::top5(vector<int> puertos){
    cout << "Top 5 puertos con sus accesos:\n";

    vector<int> indices(portEntries.size());
    iota(indices.begin(), indices.end(), rango);

    for (int i = 0; i < min(5, static_cast<int>(indices.size())); ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < indices.size(); ++j) {
            if (portEntries[indices[j] - rango] > portEntries[indices[maxIndex] - rango]) {
                maxIndex = j;
            }
        }

        swap(indices[i], indices[maxIndex]);

        cout << "Puerto: " << indices[i] + 4001 << ", Accesos: " << portEntries[indices[i] - rango] << "\n";
    }
}

int main(){

    HashTable ht(3000);

    readFile(ht);

    vector<int> puertos = ht.getPortEntries();
    
    ht.top5(puertos);

    return 0;
}