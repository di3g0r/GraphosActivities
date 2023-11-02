//Diego Rodríguez Romero A01741413
//5 de noviembre de 2023
// Graph: Representations and traversals

#include <list>
#include <iostream>
#include <stdlib.h> 
#include <vector>
#include <time.h>

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
            adjMatrix->resize(V,vector<int>(V, 0));
            
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

void Graph::addEdge(int s, int d){
    this->adjLists[s].push_back(d);
    this->adjLists[d].push_back(s);

    this->adjMatrix->at(s)[d] = 1;
    this->adjMatrix->at(d)[s] = 1;

}

void Graph::ResetVisited(){
    for(int i = 0; i < numVertices; i++){
        visited[i] = false;
    }
}

void Graph::DFS(int vertex){

    this->visited[vertex] = true;
    list<int> adjVertex = this->adjLists[vertex];

    std::cout << vertex << " ";

    for(auto i: adjVertex)
        if(!this->visited[i])
            DFS(i);

    std::cout << "\n";
}

void Graph::BFS(int startVertex){
    ResetVisited();
    
    visited[startVertex] = true;
    
    list<int> queue;
    queue.push_back(startVertex);

    while(!queue.empty()){
        int currentVertex = queue.front();

        std::cout << currentVertex << " ";

        queue.pop_front();

        for(auto i:adjLists[currentVertex]){
            if(!visited[i]){
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
    std::cout << "\n";
}

void Graph::LoadGraph(int n, int m){
    srand (time(NULL));
    //Graph(n, m);
    //Lenamos la adjList de forma random
    int cont = 0;
    while(cont < m){
        int conexion = rand() % n + 1;
        int vertice = rand() % n + 1;
        if(this->adjMatrix->at(vertice)[conexion] == 0 && conexion != vertice){
            addEdge(vertice, conexion);
            cont += 1;
        }
    }
}

int main(){
    /*
    Graph G(5, 3);

    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(0, 3);
    G.addEdge(1, 2);
    G.addEdge(0, 4);
    
    G.printGraph();
    */

    //G.DFS(0);

    //G.BFS(0);

    Graph G(6, 5);
    G.LoadGraph(6, 5);
    G.printGraph();

    return 0;
}



