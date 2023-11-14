//Act 4.3 Actividad Integradora Grafos
//Diego Rodríguez Romero
//18 de noviembre de 2023

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> 

using namespace std;

class Graph
{
private:
  int numVertices;
  int adjMatrix[1000][1000];
  
  bool *visited;
  int *inDegree;
  int *outDegree;
public:
  Graph(int V)
  {
    numVertices = V;
    visited = new bool[V];
    inDegree = new int[1000]();  
    outDegree = new int[1000](); 
  }
  ~Graph()
  {
    delete []visited;
  }
  void addEdge(int, int);
  void printGraph();
  void loadGraph();

  void updInDegree(int);
  void updOutDegree(int);

  int top10Ips();
};



void Graph::addEdge(int s, int d)
{
  if(adjMatrix[s][d] != 1)
    this->adjMatrix[s][d] = 1;
}


void Graph::loadGraph(){


}

vector<int> splitStrings(string &s) {
    vector<int> intSplit;

    string mes, dia, hora, direccionIP;
    char ch1, ch2, ch3;
    int ipPart1, ipPart2, ipPart3, ipPart4;

    stringstream SS(s);
    SS.clear();
    SS >> mes >> dia >> hora >> direccionIP;

    SS.clear();
    SS.str(direccionIP);

    SS >> ipPart1 >> ch1 >> ipPart2 >> ch2 >> ipPart3 >> ch3 >> ipPart4;

    intSplit.push_back(ipPart1);
    intSplit.push_back(ipPart2);
    intSplit.push_back(ipPart3);
    intSplit.push_back(ipPart4);

    return intSplit;
}

void Graph::updInDegree(int vector){
    this->inDegree[vector] += 1;
}

void Graph::updOutDegree(int vector){
    this->outDegree[vector] += 1;
}

void readFile(Graph& gr) {
    system("clear");

    ifstream InputFile("bitacora.txt");
    if(!InputFile){
        cerr << "Error opening the input file." << endl;
        return;
    }

    // Read and store each entry in the vector
    string entry;
    while (getline(InputFile, entry)) {
        vector<int> ipParts = splitStrings(entry);

        gr.addEdge(ipParts[0],ipParts[1]);
        //Actualizamos los valores de inDegree y outDegrees
        gr.updOutDegree(ipParts[0]);
        gr.updInDegree(ipParts[1]);

        gr.addEdge(ipParts[1],ipParts[2]);
        gr.updOutDegree(ipParts[1]);
        gr.updInDegree(ipParts[2]);

        gr.addEdge(ipParts[2],ipParts[3]);
        gr.updOutDegree(ipParts[2]);
        gr.updInDegree(ipParts[3]);
    }

    // Closes the file currently associated
    InputFile.close();
}

int Graph::top10Ips(){
    int top10values[10] = {0};
    int top10index[10] = {0};

    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (outDegree[i] > top10values[j]) {
                for (int k = 9; k > j; --k) {
                    top10values[k] = top10values[k - 1];
                    top10index[k] = top10index[k - 1];
                }
                top10values[j] = outDegree[i];
                top10index[j] = i;
                break;
            }
        }
    }

    for (int i = 0; i < 10; ++i) {
        std::cout << top10values[i] << " " << top10index[i] << std::endl;
    }

    return 0;
}
int main(){
  Graph grafo(1000);
  readFile(grafo);
  grafo.top10Ips();
}
