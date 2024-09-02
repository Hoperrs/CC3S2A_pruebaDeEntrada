#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct arista{
    int datoDestino;
    int peso;
    arista *sgteArista;
};
typedef arista *parista;

struct vertice{
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
    int visit;
};
typedef vertice *pvertice;

class grafo{
    private:
        pvertice pGrafo;
        int cont=0;
        vector<parista> pAristas; 
    public:
        grafo();
        ~grafo();
        
        void insertarVertice(int);
        void insertarArista(int,int,int);

        pvertice buscarPvertice(int);
        void dijkstra(int);
        int contarVertices();
};

grafo::grafo(){
    pGrafo=NULL;
}

grafo::~grafo(){
    pvertice p,rp;
    parista r,ra;
    p=pGrafo;
    while(p!=NULL){
        r=p->adyacente;
        while(r!=NULL){
            ra=r;
            r=r->sgteArista;
            delete ra;
        }
        rp=p;
        p=p->sgteVertice;
        delete rp;
    }
}

pvertice grafo::buscarPvertice(int n){
    pvertice p=pGrafo;
    if(p!=NULL)
        while(p->datoOrigen!=n && p!=NULL)
            p=p->sgteVertice;
    return p;
}

int grafo::contarVertices(){
    int ve=0;
    pvertice p=pGrafo;
    while(p!=NULL){
        ve++;
        p=p->sgteVertice;
    }
    return ve;
}

void grafo::insertarVertice(int x){
    pvertice p;
    p=new vertice;
    p->datoOrigen=x;
    p->adyacente=NULL;
    p->sgteVertice=pGrafo;
    pGrafo=p;
    p->visit=-1;
}

void grafo::insertarArista(int x, int y, int z){
    pvertice p=buscarPvertice(x);
    parista a;
    if(p!=NULL){
        a=new arista;
        a->datoDestino=y;
        a->peso=z;
        a->sgteArista=p->adyacente;
        p->adyacente=a;
    }
}

void grafo::dijkstra(int origen) {
    int nroVertices = contarVertices();
    vector<int> T(nroVertices, 0); // Vector para almacenar los vértices visitados
    vector<vector<int>> cam(nroVertices); // Vector de vectores para almacenar el camino hacia cada vértice
    vector<int> dist(nroVertices, INF); // Vector para almacenar las distancias mínimas

    T[origen] = 1; // Se marca el vértice de origen como visitado
    dist[origen] = 0; // La distancia al vértice de origen es 0
    cam[origen].push_back(origen); // Agregar el vértice origen al camino

    // Inicializar las distancias iniciales para los vértices adyacentes al vértice de origen
    pvertice pOrigen = buscarPvertice(origen);
    if (pOrigen != NULL) {
        parista qOrigen = pOrigen->adyacente;
        while (qOrigen != NULL) {
            int destino = qOrigen->datoDestino;
            int peso = qOrigen->peso;
            if (dist[origen] != INF && peso < dist[destino]) {
                dist[destino] = peso;
                cam[destino] = {origen, destino}; // Actualizar el camino con el vértice origen y destino
            }
            qOrigen = qOrigen->sgteArista;
        }
    }
    
    while (true) {
        // Buscar el vértice no visitado con la distancia mínima
        int minDistancia = INF;
        int minVertice = -1;

        for (int i = 0; i < nroVertices; i++) {
            if (T[i] == 0 && dist[i] < minDistancia) {
                minDistancia = dist[i];
                minVertice = i;
            }
        }

        if (minVertice == -1) {
            // No se encontró un vértice no visitado con distancia mínima
            // se termina el algoritmo
            break;
        }

        T[minVertice] = 1; // Marcar el vértice como visitado

        // Actualizar las distancias de los vértices adyacentes
        pvertice p = buscarPvertice(minVertice);
				if (p != NULL) {
            parista q = p->adyacente;
            while (q != NULL) {
                int destino = q->datoDestino;
                int peso = q->peso;
                if (dist[minVertice] != INF && dist[minVertice] + peso < dist[destino]) {
                    dist[destino] = dist[minVertice] + peso;
                    cam[destino] = cam[minVertice]; // Copiar el camino hasta el vértice anterior
                    cam[destino].push_back(destino); // Agregar el vértice destino al camino
                }
                q = q->sgteArista;
            }
        }
        // // Imprimir el camino de s -> final
        // cout << " -> " << minVertice<<"["<<cam[minVertice]<<"]";
    }

    // Imprimir el camino desde el origen hasta cada vértice
    for (int i = 0; i < nroVertices; i++) {
        cout << "Camino desde " << origen << " hasta " << i << ": ";
        for (int v : cam[i]) {
            cout << v << "[" << dist[v] << "] ";
        }
        cout << endl;
    }
}


int main(){
    grafo g;
    g.insertarVertice(5);
    g.insertarVertice(4);
    g.insertarVertice(3);
    g.insertarVertice(2);
    g.insertarVertice(1);
    g.insertarVertice(0);
    g.insertarArista(5,4,21);
    g.insertarArista(0,5,29);
    g.insertarArista(0,1,41);
    g.insertarArista(1,2,51);
    g.insertarArista(2,3,50);
    g.insertarArista(4,3,36);
    g.insertarArista(3,5,38);
    g.insertarArista(3,0,45);
    g.insertarArista(1,4,32);
    g.insertarArista(4,2,32);
    g.insertarArista(5,1,24);  
    int inicio = 0;
    int final = 1;
    g.dijkstra(inicio);

    return 0;
}