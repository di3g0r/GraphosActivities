#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

struct node{
    int vertex;
    struct node* next;
};

class Graph{
private:
    int numVertices;
    int numEdges;
    bool *visited;
    vector<list<int>> adjLists;
    vector<vector<bool>> adjMatrix;
public:
    Graph(int V){
        numVertices = V;
        //adjLists = new list<int> [V];
        adjMatrix = vector<vector<bool>>(V, vector<bool>(V, false));
        visited = new bool[V];
    }
    ~Graph(){
        //delete []adjLists;
        delete []visited;
    }
    void addEdge(int, int);
    void loadGraph();
    void printMatrix();
    void printOutDegree();
};

//We declare a pair of integers in order to use a priority queue with a value for port and other for priority
typedef pair<int, int> Pair;

void Graph::addEdge(int s, int d){
    // We set the indicated values for our adjacency matrix to true.
    if (s < numVertices && d < numVertices) {
        adjMatrix[s][d] = true;
    }
}

vector<string> readFile() {
    system("cls");
    vector<string> v;

    ifstream InputFile("bitacora.txt");
    if(!InputFile){
        cerr << "Error opening the input file." << endl;
        return v;
    }
    // Read and store each entry in the vector
    string entry;
    while(InputFile){
        getline(InputFile, entry);
        v.push_back(entry);
    }

    // Closes the file currently associated
    InputFile.close();

    return v;
}


void Graph::printMatrix(){
    // We traverse all the matrix with two for loops.
    for(int i = 0; i < numVertices; i++){
        for (int j = 0; j < numVertices; j++){
            bool value = adjMatrix[i][j];
            cout << value << " ";
        }
        cout << endl;
    }
}

vector<string> splitLine(string &s) {
    vector<string> splittedv;
    string temp, ip, segment;
    stringstream SS(s), ipStream;
    // Ignoramos los primeros tres elementos en la lista
    for (int i = 0; i < 3; i++)
        SS >> temp;
    // Leemos la IP hasta encontrar un ':'
    getline(SS, ip, ':');
    ipStream.str(ip);
    for (int i = 0; i < 4; i++) {
        // Dividimos los componentes de la IP separados por '.'
        getline(ipStream, segment, '.');
        // Agregamos cada elemento al vector de resultados
        splittedv.push_back(segment);
    }
    return splittedv;
}

void Graph::loadGraph() {
    vector<string> v = readFile();
    for (int i = 0; i < v.size(); i++) {
        vector<string> splitted = splitLine(v[i]);
        for (int j = 0; j < splitted.size() - 1; j++) {
            addEdge(stoi(splitted[j]), stoi(splitted[j + 1]));
        }
    }
}


void Graph::printOutDegree() {
    priority_queue<pair<int, int>> counters;
    int counter;
    for (int i = 0; i < numVertices; i++) {
        counter = 0;
        for (int j = 0; j < numVertices; j++) {
            if (adjMatrix[i][j])
                counter++;
        }
        counters.push(make_pair(counter, i));
    }
    while (!counters.empty()) {
        pair<int, int> top = counters.top();
        cout << "IP Segment: " << top.second << ", Out-Degree value: " << top.first << endl;
        counters.pop();
    }
}

int main(){
    Graph G(999);
    G.loadGraph();
    G.printOutDegree();
    return 0;
}