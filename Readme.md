# Laboratorio 3
> La explicacion que de que hace cada funcion esta en el codigo.

## Como Funciona el Grafo
Primero con el Archivo "Servidores.csv" se le asignan los vertices que tiene el grafo, el en el vertice esta designado si es pertenecente a un cliente o servidor. Luego se pasa a leer el "conexciones.csv" que es el que va a establecer las aristas y por tanto las relaciones que tienen cada una de ellas. 

<img src= https://upload.wikimedia.org/wikipedia/commons/6/6f/Listas_de_adyacencia.jpg alt="Imagen como se guardan los datos del grafo">

#### En el Vertice tienen las siguientes variables :

   - string id  
   - string tipo 
   - int idcliente   
   - int idservidor

Como un vertice solo puede ser cliente o servidor se le asigna -1 al id del tipo que no pertenece.

#### Para las Aristas se le aignaron los siguientes variables:

 - string origen
 - string destino
 - int velidad 
 - int distancia 

 Que vienen siendo todas las variables que contiene "conexiones.csv".

 
 ## Funcionamiento del  Menú 

 #### Mostrar Clientes:
   Cuando se leeyo el archivo "sevidores.csv" se guardaron los clientes en un array apartado para poder acceder a ellos de una manera mas sencilla.
 #### Mostrar Sevidores:
   Mismo caso que en mostrar clientes, se guardaron en una array apartado para poder manejarlos de una manera mas sencilla.
 #### Mostrar Grafo:
   Aqui muestras las Aristas que tiene el grafo.
 #### Enviar Paquete:
   Aqui se nos pide el tamaño del paquete y el id de destino que tiene que existir dentro del grafo. Se mostrara por pantalla el camino mas corto con su tiempo que se demora en cada tramo mas el tiempo total, en caso de que no exista un camino de id de Oriden a id de Destino se mostrará por pantalla que no existe un camino.