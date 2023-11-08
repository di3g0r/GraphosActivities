//Diego Rodríguez Romero A01741413
//12 de noviembre de 2023
// Grafos: Algoritmos complementarios

#include <list>
#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <time.h>
#include <queue>

using namespace std;

class Graph{
    private:
        int numVertices;

        list<int> *adjLists;
        vector<vector<int>> *adjMatrix;

        bool *visited;
        bool *connected;
    public:
        Graph(int V){
            numVertices = V;

            adjLists = new list<int> [V];

            adjMatrix = new vector<vector<int>> [V];       
            adjMatrix->resize(V, vector<int>(V, 0));

            visited = new bool[V];
            connected = new bool[V];
        }
        ~Graph(){
            delete []adjLists;
            delete []visited;
        }

        void LoadGraph(int);

        void addEdge(int, int);
        void printGraph();

        void DFS(int);
        void BFS(int);

        void MDFS(int);
        void MBFS(int);

        bool isConnected();
        void ResetVisited();
};

void Graph::printGraph(){
    //adjList
    std::cout << "Adjacency List\n"; 
    for(int i = 0; i < this->numVertices; i++){
        std::cout << "\nVertex " << i << ":";

        for (auto x: this->adjLists[i]){
            std::cout << " -> " << x; 
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    //adjMatrix
    std::cout << "Adjacency Matrix\n\n";
    int n = 0;
    for (auto k: this->adjMatrix[n]){
        for(int j = 0; j < this->numVertices; j++){
            std::cout << k[j];
        }
        std::cout << "\n";
        n++;
    }
    std::cout << "\n";
}

/*addEdge(int s, int d), funcion donde le agregamos una nueva arista al grafo
indicamos el par de vertices que queremos conectar. Complejidad O(1)*/
void Graph::addEdge(int s, int d){
    this->adjLists[s].push_back(d);

    this->adjMatrix->at(s)[d] = 1;
}

/*ResetVisited(), recorre todo el array de visited y pone todos sus valores en falso
Complejidad O(n)*/
void Graph::ResetVisited(){
    for(int i = 0; i < numVertices; i++){
        visited[i] = false;
        connected[i] = false;
    }
}

bool Graph::isConnected(){
    for(int i=0; i < numVertices; i++){
        if(connected[i] == false){
            return false;
        }
    }
    return true;
}

void Graph::LoadGraph(int n){
    //Graph(n, m);
    //Lenamos la adjList de forma random
    ResetVisited();

    bool x = false;
    int conexion = rand() % n;
    int vertice = rand() % n;

    if(conexion != vertice){
        visited[vertice] = true;
        addEdge(vertice, conexion);
        connected[vertice] = true;
        connected[conexion] = true;
        std::cout << vertice << "-> " << conexion << "\n";
    }

    while(x != true){
        conexion = rand() % n;
        vertice = rand() % n;
        if(this->adjMatrix->at(vertice)[conexion] == 0 && conexion != vertice && visited[conexion] == false 
        && (connected[vertice] == true || connected[conexion] == true)){
            visited[vertice] = true;
            addEdge(vertice, conexion);
            connected[vertice] = true;
            connected[conexion] = true;
            std::cout << vertice << "-> " << conexion << "\n";
        }
        x = isConnected();
    }
    std::cout << "\n";
}

int main(){
    srand (time(NULL));

    Graph G(6);

    G.LoadGraph(6);

    G.printGraph();

    return 0;
}