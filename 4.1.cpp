//Diego Rodríguez Romero A01741413
//5 de noviembre de 2023
// Graph: Representations and traversals

#include <list>
#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <time.h>
#include <queue>

using namespace std;
/*
struct Node{
    int vertex;
    struct node* next;
};

struct Graph{
    int numVertices;
    struct node** adjLists;
};*/

class Graph{
    private:
        int numVertices;
        int numEdges;

        list<int> *adjLists;
        vector<vector<int>> *adjMatrix;

        bool *visited;
    public:
        Graph(int V, int E){

            numVertices = V;
            numEdges = E;

            adjLists = new list<int> [V];

            adjMatrix = new vector<vector<int>> [V]; 
            adjMatrix->resize(V, vector<int>(V, 0));
            
            visited = new bool[V];
        }
        ~Graph(){
            delete []adjLists;
            delete []visited;
        }

        void LoadGraph(int, int);

        void addEdge(int, int);
        void printGraph();

        void DFS(int);
        void BFS(int);

        void MDFS(int);
        void MBFS(int);

        void ResetVisited();
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
    this->adjLists[d].push_back(s);

    this->adjMatrix->at(s)[d] = 1;
    this->adjMatrix->at(d)[s] = 1;

}

/*ResetVisited(), recorre todo el array de visited y pone todos sus valores en falso
Complejidad O(n)*/
void Graph::ResetVisited(){
    for(int i = 0; i < numVertices; i++){
        visited[i] = false;
    }
}

/*DFS(int vertex), ejecuta el recorrido del grafo por el metodo  Depth First Search
en la lista de adyacencia, empieza en el vertice indicado
el cual marca como visitado y se agregan a un stack sus adyacentes, luego toma
el primer elemento del stack y repite los 2 pasos anteriores hasta terminar
Complejidad O(V + E)*/
void Graph::DFS(int vertex){
    this->visited[vertex] = true;
    list<int> adjVertex = this->adjLists[vertex];

    std::cout << vertex << " ";

    for(auto i: adjVertex)
        if(!this->visited[i])
            DFS(i);

    for(int i = 0; i < numVertices; i++){
        if(visited[i] == false){
            DFS(i);
        }
    }
}

/*MDFS(int vertex), ejecuta el recorrido del arbol Depth First Search
en la matriz de adyacencia, empieza con el elemento dado, lo marca como visitado, y se pasa a 
su primer elemento adyacente, y hace lo mismo, repite el proceso hasta visitar todos los elementos
Complejidad O(V + E)*/
void Graph::MDFS(int vertex){
    this->visited[vertex] = true;

    vector<int> adjVertex(numVertices);
    adjVertex = this->adjMatrix->at(vertex);

    std::cout << vertex << " ";

    for(int i = 0; i < adjVertex.size();i++){
        if(adjVertex[i] == 1){
            if(this->visited[i] == false){
                MDFS(i);
            }
        }         
    }
    for(int i = 0; i < numVertices; i++){
        if(visited[i] == false){
            MDFS(i);
        }
    }
}

/*BFS(int startVertex), empieza su busqueda en un vertice, crea una lista
de los nodos adyacentes de dicho vertice que no han sido vsitados
 y los agrega a una queue, toma el elemento mas alto de la queue y repite
 el proceso O(V + E)*/
void Graph::BFS(int startVertex){ 
    visited[startVertex] = true;
    
    list<int> queue;
    queue.push_back(startVertex);

    while(!queue.empty()){
        int currentVertex = queue.front();

        std::cout << currentVertex << " ";

        queue.pop_front();

        for(auto i: adjLists[currentVertex]){
            if(!visited[i]){
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }

    for(int i = 0; i < numVertices; i++){
        if(visited[i] == false){
            BFS(i);
        }
    }

    std::cout << "\n";
}

/*MBFS(int startVertex), metodo de busqueda Breadth First Search, tiena la misma logica que
BFS solo que utiliza las filas de la matriz para realizar la busqueda en vez de las listas
Complejidad O(V + E)*/
void Graph::MBFS(int startVertex){
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

    for(int i = 0; i < numVertices; i++){
        if(visited[i] == false){
            MBFS(i);
        }
    }
    std::cout << "\n";

}

/*LoadGraph(int n, int m), funcion que nos permite crear un Grafo de froma random
indicando cuantas vertices y cuantas aristas se quiere que se tengan, Crea tanto la lista de 
aycencia como la matriz. Complejidad O(m)*/
void Graph::LoadGraph(int n, int m){
    //Graph(n, m);
    //Lenamos la adjList de forma random
    int cont = 0;

    while(cont < m){
        int conexion = rand() % n ;
        int vertice = rand() % n ;
        if(this->adjMatrix->at(vertice)[conexion] == 0 && conexion != vertice){
            addEdge(vertice, conexion);
            cont++;
        }
    }
}

int main(){
    
    srand (time(NULL));

    int ver, aristas;

    std::cout << "Cuantos vertices quieres que tenga tu grafo?\n";
    std::cin >> ver;

    std::cout << "Cuantas aristas quieres que tenga tu grafo?\n";
    std::cin >> aristas;

    while(aristas > (ver * (ver - 1)) / 2){
        std::cout << "Tu grafo no puede tener esa cantidad de aristas\n";
        std::cout << "Cuantas aristas quieres que tenga tu grafo?\n";
        std::cin >> aristas;
    }

    Graph G(ver, aristas);
    G.LoadGraph(ver, aristas);

    std::cout << "Este es tu grafo\n\n";
    G.printGraph();

    G.ResetVisited();
    
    std::cout << "DFS para AdjList\n";
    G.DFS(0);
    std::cout << "\n";

    G.ResetVisited();

    std::cout << "BFS para AdjList\n";
    G.BFS(0);
    std::cout << "\n";

    G.ResetVisited();

    std::cout << "DFS para AdjMatrix\n";
    G.MDFS(0);
    std::cout << "\n";

    G.ResetVisited();

    std::cout << "BFS para AdjMatrix\n";
    G.MBFS(0);

    return 0;
}



