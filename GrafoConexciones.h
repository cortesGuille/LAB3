#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <map>

using namespace std;

struct Nodo { //Estos son los parametros de los vertices 
    string id;
    string tipo; // "usuario" o "servidor"
    int idcliente;    // solo para tipo "usuario" 
    int idservidor;    // solo para tipo "servidor"
                      // se rellena -1 para el tipo que no es
};

struct Arco { // Estos son los parametros de las Aritas son los parametros dados en "conexiones.csv"
    string origen;
    string destino;
    int velocidad;
    int distancia;
};
class GrafoConexiones {
    
    public:
    map<string, Nodo> nodos; //lista de adyacencia
    vector<Arco> arcos; //lista de caminos
    /**
    *Funcion que agregra los todos los vectores al grafo , En la seccion int id se le pone -1 cuando no es el tipo correspondiente
    *@param string id 
    *@param string tipo
    *@param int idCliente
    *@param int idServidor
    */
    void agregarNodo(const string& id, string tipo, int idcliente = -1, int idservidor = -1) {
        nodos[id] = {id, tipo, idcliente, idservidor};
    }
    /**
     * Funcion que agrega los arcos, esta viene dada en conexiones.csv
     * @param string origen
     * @param string destino
     * @param int velocidad
     * @param int distancia
    */
    void agregarArco(const string& origen, const string& destino, int velocidad, int distancia) {
        arcos.push_back({origen, destino, velocidad, distancia});
    }
    /**
     * Imprime el grafo
     * 
    */
    void imprimirGrafo() {
         
      

        cout << "\nArcos o Aristas:\n";
        for (const auto& arco : arcos) {
            cout << "Origen: " << arco.origen << ", Destino: " << arco.destino
                 << ", Velocidad: " << arco.velocidad << ", Distancia: " << arco.distancia
                 << endl;
        }
    }
    
    /**
     * Funcion para encontrar el tiempo minimo entre dos nodos
     * ,devolvera un pair con el camino y el tiempo minimo
     * y dentro de la funcion dira el tiempo que se demora entre arcos
     * @param string origen
     * @param string destino
     * @param int peso
     * 
    */
    void funcionDjstra (const string& origen, const string& destino, int peso){

        map <string, int> distancia; //distancia minima
        map <string, string> anterior; //nodo previo
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq; //pila de prioridad

        for (const auto& par: nodos){ //inicializar las distancias

            const string& idNodo = par.first;
            distancia [idNodo] = numeric_limits<int>::max();
            anterior [idNodo] = "";
        }
        distancia [origen] = 0; 
        pq.push({0, origen}); //origen

        while(!pq.empty()){//encontrar el nodo con el tiempo minimo

            string n = pq.top().second; 
            pq.pop();
            for(const Arco& arco : arcos){

                if(arco.origen==n){
                    string v = arco.destino;
                    //calcular el tiempo minimo
                    // para saber cuanto es el menor se debe calcular (distancia/peso)*(velocidad)
                    // el tiempo minimo se calcula de la siguiente manera
                    int  ntiempo = (peso/arco.distancia)*(arco.velocidad);
                    if(ntiempo==0){
                        ntiempo=arco.velocidad;
                    }
                    int alt = distancia [n] + ntiempo;
                    if(alt<distancia[v]){
                        distancia[v] = alt;
                        anterior[v] = n;
                        pq.push({alt, v});


                    }



                }   
            }


        }
    // muestra por pantalla el camino y el tiempo 
    vector<string > camino;
    string actual = destino;
    int tiempo=0;
    //mientras actual no este vacio
    while(!actual.empty()){
        camino.insert(camino.begin(), actual); //inserta al principio para no generar un bucle infinito 
        for(const Arco& arco : arcos){
                //busca el arco
                if(arco.origen == anterior[actual] && arco.destino == actual){ 
                    int tiempoDelArco= (peso/arco.distancia)*arco.velocidad;
                    if(tiempoDelArco==0){
                        tiempoDelArco=arco.velocidad;
                    }
                    tiempo += tiempoDelArco;
                    cout << "Tramo: " << arco.origen << " -> " << arco.destino
                     << ", Tiempo: " << tiempoDelArco << "(s), Tiempo total: " << tiempo <<"(s)" <<endl;
                    break;
                }

        }
         actual = anterior[actual];
    }
    if(anterior[destino].empty()){//si no hay camino valido 
        cout<<"No hay camino valido desde"<<" "<<origen<<" "<<"hasta ->"<<" "<<destino<<endl;
    }



    }

};