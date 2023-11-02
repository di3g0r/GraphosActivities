//Diego Rodríguez Romero A01741413
//5 de noviembre de 2023
// Graph: Representations and traversals

#include <list>
#include <iostream>

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
        list<int> *adjLists;
        bool *visited;
    public:
        Graph(int V){
            numVertices = V;
            adjLists = new list<int> [V];
            visited = new bool[V];
        }
        ~Graph(){
            delete []adjLists;
            delete []visited;
        }
        void addEdge(int, int);
        void printGraph();

        void DFS(int);
        void BFS(int);

        void ResetVisited();
};

void Graph::printGraph(){
    for(int i = 0; i < this->numVertices; i++){
        std::cout << "\nVertex " << i << ":";

        for (auto x: this->adjLists[i]){
            std::cout << " -> " << x; 
        }
        std::cout << "\n";
    }
}

void Graph::addEdge(int s, int d){
    this->adjLists[s].push_back(d);
    this->adjLists[d].push_back(s);
}

void Graph::ResetVisited(){
    for(int i = 0; i < numVertices; i++){
        visited[i] = false;
    }
}

void Graph::DFS(int vertex){
    ResetVisited();

    this->visited[vertex] = true;
    list<int> adjVertex = this->adjLists[vertex];

    std::cout << vertex << " ";

    for(auto i: adjVertex)
        if(!this->visited[i])
            DFS(i);
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
}

int main(){
    Graph G(5);

    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(0, 3);
    G.addEdge(1, 2);
    G.addEdge(0, 4);

    G.printGraph();

    return 0;
}



