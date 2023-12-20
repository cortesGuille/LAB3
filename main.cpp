#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <algorithm> 
#include <cctype>    
#include "Servidor.h"
#include "Cliente.h"
#include "GrafoConexciones.h"

using namespace std;
/**
 * Funcion split simple para simplificar la lectura en la optenciones de los datos
 * @param string dato
 * @param char delimitador
 * @return vector<string>
*/
vector<string> split(const string& s, char delimiter);
/**
 * Funcion para cargar el grafo
 * @param GrafoConexiones& grafo
 * @param vector<Cliente*> clientes
 * @param vector<Servidor*> servidores
*/
void cargarGrafo(GrafoConexiones& grafo, vector<Cliente*>& clientes, vector<Servidor*>& servidores);
/**
 * Funcion para saber si el usuario esta en la base de datos
 * @param vector<Cliente*> clientes
 * @param string id
 * @return bool
*/
bool inicioDeSesion(vector<Cliente*> clientes, string id);
/**
 * Funcion para saber si el destino existe en la base de datos
 * @param string id
 * @param vector<Cliente*> clientes
 * @param vector<Servidor*> servidores
 * @return bool
*/
bool existe(string id, vector<Cliente*> clientes, vector<Servidor*> servidores);
/**
 * Desplega las opciones del menu
 * 
*/
void menu();
/**
 * Muestra los clientes
 * @param vector<Cliente*> clientes
*/
void mostrarClientes(vector<Cliente*> clientes);
/**
 * Muestra los servidores
 * @param vector<Servidor*> servidores
*/
void mostrarServidores(vector<Servidor*> servidores);
/**
 * Funcion para enviar un paquete
 * @param string id
 * @param vector<Cliente*> clientes
 * @param vector<Servidor*> servidores
 * @param GrafoConexiones& grafo
 * 
*/
void enviarPaquete(string id, vector<Cliente*> clientes, vector<Servidor*> servidores, GrafoConexiones& grafo);
int main() {

    srand(time(NULL));
    ofstream archivo;
    ofstream archivo2;
    archivo2.open("conexiones.csv");
    archivo.open("servidores.csv");
    archivo<<"id,nombre,tipo"<<endl;
    archivo2<<"idCliente,idServidor,velocidad,distancia"<<endl;
    vector<string> cliente;
    vector<string> servidor;
    for (int i = 0; i < 300; i++) {
        int num = i;
        string nombre = "Servidor" + to_string(i);
        int random = rand()%5+1;
        cout<<random<<endl;
        string tipo;
        if(random == 5){
            tipo = "router";
            servidor.push_back(to_string(i));
            for(string client:cliente){
                int random2 = rand()%10+1;
                int velocidadrand = (rand()%3+1)*300;
                archivo2<<client<<","<<i<<","<<velocidadrand<<","<<random2<<endl;
            }
            cliente.clear();
        }else{
            tipo="cliente";
            cliente.push_back(to_string(i));
        }
        archivo << num << "," << nombre << "," << tipo << endl;
    }
    archivo.close();
    for(int i = 0; i< servidor.size(); i++){
        for(int j = i+1; j< servidor.size(); j++){
            if(i!=j){
                int moneda = rand()%4+1;
                if(moneda == 1){
                    int random = rand()%1000+1;
                    int velocidad = (rand()%3+1)*1000;
                    archivo2<<servidor[i]<<","<<servidor[j]<<","<<velocidad<<","<<random<<endl;
                }
            }
        }
        
    }
    archivo2.close();        

    //Objetos
    GrafoConexiones grafo;
    vector<Cliente*> clientes;
    vector<Servidor*> servidores;

    //lectura del archivo de servidores
    ifstream file("servidores.csv");
    if(file.is_open()){
        string line;
        getline(file,line);
        while (getline(file,line))
        {
            vector<string> tokens = split(line, ',');
                string id= tokens[0];
                string nombre = tokens[1];
                string tipo = tokens[2];
                if(tipo=="cliente"){
                  clientes.push_back(new Cliente(id,nombre));
                }
                
                if(tipo=="router"){
                    servidores.push_back(new Servidor(id,nombre));
                
                }
        }
         
    }     
    file.close();

    cargarGrafo(grafo, clientes, servidores);

    //se agregar los nodos(servidores y clientes) al grafo que llegaran a 
    for (auto cliente : clientes) {
        grafo.agregarNodo(cliente->getId(), "usuario", cliente->getIdInt(), -1);
    }

    for (auto servidor : servidores) {
        grafo.agregarNodo(servidor->getId(), "servidor", -1, servidor->getIdInt());
    }
    string id;
    while(true){

        cout<<"ingrese su id: ";
        cin>>id;
        if(inicioDeSesion(clientes, id)){
            break;
        }else{
            cout<<"id incorrecto"<<endl;
        }
    }
    bool finBucle=true;
    int op;
    while(finBucle){
        menu();
        cin>>op;
        switch (op)
        {
        case 1:
            cout<<"Clientes: \n"<<endl;
            mostrarClientes(clientes);
           
            break;
        
        case 2:
            cout<<"Servidores: \n"<<endl;
            mostrarServidores(servidores);
            
            break;

        case 3:
            grafo.imprimirGrafo();
            
            break;

        case 4:
            enviarPaquete(id, clientes, servidores, grafo);

            break;
        case 5:
            finBucle=false;    
            break;    
        default:
            cout<<"Opcion incorrecta"<<endl;
            break;
        }
    }
    
   cout<<"Cierre del programa"<<endl;


    return 0;
}
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    istringstream tokenStream(s);
    string token;
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}
void cargarGrafo(GrafoConexiones& grafo, vector<Cliente*>& clientes, vector<Servidor*>& servidores){
    ifstream archivo("conexiones.csv");
    string linea;
    getline(archivo,linea);
    while(getline(archivo,linea)){
        vector<string> tokens = split(linea, ',');
        string id1 = tokens[0];
        string id2 = tokens[1];
        int velocidad = stoi(tokens[2]);
        int distancia = stoi(tokens[3]);
        
        if (grafo.nodos.find(id1) == grafo.nodos.end()) {
                grafo.agregarNodo(id1, (id1.find("cliente") != string::npos) ? "usuario" : "servidor", -1, -1);
            }
        if (grafo.nodos.find(id2) == grafo.nodos.end()) {
                grafo.agregarNodo(id2, (id2.find("cliente") != string::npos) ? "usuario" : "servidor", -1, -1);
        }
        grafo.agregarArco(id1, id2, velocidad, distancia);
       
    }    

}
bool inicioDeSesion(vector<Cliente*> clientes, string id){
    for(const auto& cliente : clientes){
        if(cliente->getId()==id){
            return true;
        }
    }
    return false;
}
bool existe(string id, vector<Cliente*> clientes, vector<Servidor*> servidores){
    for(const auto& cliente : clientes){
        if(cliente->getId()==id){
            return true;
        }
    }
    for(const auto& servidor : servidores){
        if(servidor->getId()==id){
            return true;
        }
    }
    return false;
}
void menu(){
    cout<<"===========Menu============\n"<<endl;
    cout<<"1. Mostrar Clientes\n";
    cout<<"2. Mostrar Servidores\n";
    cout<<"3. Mostrar Grafo\n";
    cout<<"4. Enviar paquete\n";
    cout<<"5. salir\n";
    cout<<endl;
}

void mostrarClientes(vector<Cliente*> clientes){

    for(const auto& cliente : clientes){
        cout<<cliente->getId()<<" "<<cliente->getNombre()<<endl;
    }
}   

void mostrarServidores(vector<Servidor*> servidores){

    for(const auto& servidor : servidores){
        cout<<servidor->getId()<<" "<<servidor->getNombre()<<endl;
    }
}

void enviarPaquete(string id, vector<Cliente*> clientes, vector<Servidor*> servidores, GrafoConexiones& grafo){
    int tamano = 0;
    string destino;

    cout<<"Ingrese el tamano del paquete: "<<endl;
    cin>>tamano;
    cout<<"Ingrese el destino: "<<endl;
    cin>>destino;
    while(!existe(destino, clientes, servidores)){
        cout<<"El destino no existe"<<endl;
        cout<<"Ingrese el destino: "<<endl;
        cin>>destino;
    }
    //obteniendo el mejor camino
    grafo.funcionDjstra(id, destino, tamano);
}