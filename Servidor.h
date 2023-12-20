#pragma once 
#include<iostream>

using namespace std;

class Servidor{

private:

string id;
string nombre;

public:
Servidor(string id, string nombre){
    this->id = id;
    this->nombre = nombre;
}

string getId(){
    return id;
}
int getIdInt(){
    return stoi(id);
}
string getNombre(){
    return nombre;
}

};