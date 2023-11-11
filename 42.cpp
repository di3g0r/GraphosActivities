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
};

/*printGraph(), imprime el grafo en sus 2 representaciones como lista de
adyacencia o como matriz de adyacencia. Complejidad O(n2)*/
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

/*isConnected(), recorre todo el array de connected para checar si todos
los nodos estan conectados, ya sea que un nodo se dirija a ellos o que ellos
a otro nodo.Complejidad O(n)*/
bool Graph::isConnected(){
    for(int i=0; i < numVertices; i++){
        if(connected[i] == false){
            return false;
        }
    }
    return true;
}

/*isAllVisited(), recorre todo el array de visited para checar si todos
los nodos han sido visitados. Complejidad O(n)*/
bool Graph::isAllVisited(){
    for(int i=0; i < numVertices; i++){
        if(visited[i] == false){
            return false;
        }
    }
    return true;
}

/*LoadGraph(int n), funcion que nos permite crear un Grafo Dirigido
Aciclico (DAG) de froma random
indicando cuantas vertices se quiere que se tenga, Crea tanto la lista de 
aycencia como la matriz. Complejidad O(n2)*/
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

/*isTree(), funcion para verificar si nuestro DAG es una rbol o no,
recorre la matriz en cada indice, checando si dicho indice tiene mas de un padre
, si un solo nodo tiene mas de un padre regresa falso, si todos los nodos tienen un
solo padre regresa true, Complejidad O(n2)*/
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

/*TopologicalSort(), realiza un ordenamiento de modo que cada nodo aparezaca siempre
antes de todos los nodos a los cuales apunta. Como si fueran pasos que se tienen que
realizar y cada uno es dependiente de uno o mas antes que el. Complejidad(n2)*/
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

/*auxTopological(int v, stack<int> &stack), es la funcion auxiliar del topological
sort, mientras TopologicalSort recorre cada uno de los indices para ver si ya fueron visitados.
Si no es asi, itera sobre ese nodo buscando a todos aquellos elementos a los que apunta
, si encuentra un elemento que no ha sido visitado se llama asi misma y al completar el ciclo agrega
 a un elemento a un stack. Complejidad O(n)*/
void Graph::auxTopological(int v, stack<int> &stack) {
    visited[v] = true;

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i] && (*adjMatrix)[v][i] == 1) {
            auxTopological(i, stack);
        }
    }
    stack.push(v);
}

/*isBipartite(), esta funcion lo que hace es checar si un grafo es bipartita, lo hace
atravesando el grafo por BFS y agregando a una priority queue el nodo y su prioridad
la cual es en base a su numero de nodos. ComplejidadO(n3)*/
bool Graph::isBipartite(){
    vector<bool> color(numVertices);
    vector<bool> isColored(numVertices, false);
    vector<int> inDegree(numVertices, 0);

    // Calculate in-degrees
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if ((*adjMatrix)[i][j] == 1) {
                inDegree[j]++;
            }
        }
    }

    priority_queue<pair<int, int>> pq; 

    for (int i = 0; i < numVertices; ++i) {
        pq.push({-inDegree[i], i}); 
    }

    while (!pq.empty()) {
        int currentVertex = pq.top().second;
        pq.pop();

        if (!isColored[currentVertex]) {
            color[currentVertex] = false;
            isColored[currentVertex] = true;

            for (int i = 0; i < numVertices; ++i) {
                if ((*adjMatrix)[currentVertex][i] == 1) {
                    if (!isColored[i]) {
                        color[i] = !color[currentVertex];
                        isColored[i] = true;
                        pq.push({-inDegree[i], i});
                    } else if (color[i] == color[currentVertex]) {
                        return false;
                }
            }
        }
    }

    return true;
    }
}

int main() {
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

    if(G.isBipartite() == false){
        std::cout << "el grafo no es bipartita\n";
    }
    else{
        std::cout << "el grafo si es bipartita\n";
    }
    
    return 0;
}