//Diego Rodríguez Romero A01741413
//12 de noviembre de 2023
// Grafos: Algoritmos complementarios

#include <list>
#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <time.h>
#include <queue>
#include <stack>

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
        bool isAllVisited();

        void ResetVisited();

        bool isTree();

        void TopologicalSort() ;
        void auxTopological(int, stack<int>&);

        bool isBipartite();
        int inDegree();
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

bool Graph::isAllVisited(){
    for(int i=0; i < numVertices; i++){
        if(visited[i] == false){
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

bool Graph::isTree(){
    for(int i=0; i < numVertices; i++){
        int cont = 0;
        for(int j=0; j < numVertices; j++){
            if(this->adjMatrix->at(j)[i] == 1){
                cont++;
            }
            if(cont > 1){
                return false;
            }
        }
    }
    return true;
}

void Graph::TopologicalSort() {
    ResetVisited();
    stack<int> stack;

    for (int i = 0; i < numVertices; i++) {
        if (visited[i] == false) {
            auxTopological(i, stack);
        }
    }

    while (stack.empty() == false) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
}

void Graph::auxTopological(int v, stack<int> &stack) {
    visited[v] = true;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && (*adjMatrix)[v][i] == 1) {
            auxTopological(i, stack);
        }
    }

    stack.push(v);
}

int Graph::inDegree(){
    for (int i = 0; i < numVertices; i++){
        for(int j = 0; j < numVertices;j++){
            if(adjMatrix->at(j)[i] == 1){

            }
        }
    }
}

bool Graph::isBipartite(){
    for(int i = 0;i < numVertices; i++){

    }
    visited[startVertex] = true;
    vector<int> adjVertex(numVertices);

    list<int> queue;
    queue.push_back(startVertex);

    while(!queue.empty()){
        int currentVertex = queue.front();
    
        adjVertex = this->adjMatrix->at(startVertex);

        std::cout << currentVertex << " ";

        queue.pop_front();

        for(int i = 0; i < adjVertex.size();i++){
            if(!visited[i] && adjVertex[i] == 1){
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}

int main(){
    srand (time(NULL));

    Graph G(6);

    /*G.addEdge(0,1);
    G.addEdge(0,2);
    G.addEdge(2,3);
    G.addEdge(1,2);*/

    G.LoadGraph(6);

    G.printGraph();

    if(G.isTree() == false){
        std::cout << "el grafo no es un arbol\n";
    }
    else{
        std::cout << "el grafo si es un arbol\n";
    }

    G.TopologicalSort();

    if(G.isBipartite(0) == false){
        std::cout << "el grafo no es bipartita\n";
    }
    else{
        std::cout << "el grafo si es bipartita\n";
    }
    
    return 0;
}