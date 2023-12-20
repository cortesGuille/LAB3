#pragma once
#include <iostream>

using namespace std;

class Cliente{

private:

string id;
string nombre;

public:
Cliente(string id, string nombre){
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
