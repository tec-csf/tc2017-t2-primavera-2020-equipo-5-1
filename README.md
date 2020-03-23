# Tarea *2*. *Análisis de Algoritmos*

---

##### Integrantes:
1. Carla Pérez Gavilán Del Castillo - *A01023033* - *CSF*
2. Rubén Hernández Rivas - *A01024669* - *CSF*
3. Christian Alberto Dalma Schultz - *A01423166* - *CSF*

---
## 1. Aspectos generales

Las orientaciones de la tarea se encuentran disponibles en la plataforma **Canvas**.

Este documento es una guía sobre qué información debe entregar como parte de la tarea, qué requerimientos técnicos debe cumplir y la estructura que debe seguir para organizar su entrega.


### 1.1 Requerimientos técnicos

A continuación se mencionan los requerimientos técnicos mínimos de la tarea, favor de tenerlos presente para que cumpla con todos.

* El código debe desarrollarse en C++, cumpliendo con el último estándar [C++17](https://isocpp.org/std/the-standard).
* Toda la programación debe realizarse utilizando Programación Genérica.
* Deben utilizarse las [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md).
* Todo el código debe estar correctamente documentado, siguiendo los lineamientos que aparecen en [Documenting C++ Code](https://developer.lsst.io/cpp/api-docs.html).
* Todo el código de la tarea debe alojarse en este repositorio de GitHub.
* Debe configurar su repositorio para que utilice el sistema de Integración Continua [Travis CI](https://travis-ci.org/).

### 1.2 Estructura del repositorio

El proyecto debe seguir la siguiente estructura de carpetas:
```
- / 			        # Raíz del repositorio
    - README.md			# Archivo con la información general de la actividad (este archivo)
    - sources  			# Códigos fuente con la solución
    - examples			# Archivos de ejemplo que pueden utilizarse para verificar que la solución funciona.
```

## 2. Solución

Se crearon dos árboles, un AVL implementado en memoria y un árbol B implementado en disco (por medio de archivos). 

#### Para el árbol B: 
 El ábrol B se implementa a través de un archivo, al cual se le va escribiendo la estructura Nodo. 
 
INSERCIÓN: 

       * se búsca el índice donde se va a insertar el nuevo número
       * si este indice se en un nodo lleno se llama a una función que divide el nodo y sub el nodo central al nodo padre. 
       * si el nodo es la raíz se hace una divisón especial. 
FUNCIÓN QUE BUSCA HIJO TENIENDO PADRE:
* para la función que busca el hijo siendo el padre se utiliza la siguiente fórmula (H(index)= (index/N) + 1 + index)

FUNCIÓN QUE BUSCA PADRE TENIENDO HIJO:
* para la función que busca el hijo siendo el padre se utiliza la siguiente fórmula (P(index)= (index-2)/(N+1))
  
BORRAR: 
  * se utiliza la función de búsqueda y luego se elimina, se utilizan procesos distintos si se está eliminando en un nodo hoja o raíz. 
   * si la eliminación resulta en un desbalance, se vuelve a balancear el árbol.

BUSCAR:
    * se itera sobre el árbol de forma recursiva, si se encuentra el nodo que se está buscando, se regresa la posición. 
    
#### Para el árbol ALV:
 Arbol avl se implementa de memoria se crea y se rota para temrinar de forma balanceada
 
INSERCIÓN:

       * Se busca el punto del arbol donde esta el nodo padre
       * Se inserta el nodo dependiendo la ubicacion del noco padre
       * Si el arbol termina desvalanciado se rotara como es devido para alcanzar su balance
 BUSQUEDA: 
   * Recorre el arbol leyendo cada padre hasta llegar al punto donde este el numero
 
 BORRAR: 
   * La funcion de busqueda es utilizada para encontrar el nodo
   * El nodo es borrado de forma correcta de acuerdo a la base de datos 
   * Si el nodo tiene nodos hijos se hace la rotacion necesaria
   * Si despues de borrar el nodo el arbol resulta desbalanceado se hace la rotacion necesaria
 
 

### 2.1 Pasos a seguir para utilizar la aplicación

Hay dos maneras de correr el código: 
###### a. De forma ineractiva, se deben correr los siguientes comandos en términal: 
    -  g++ Menu.cpp -std=c++17 -o travis_gcc_cpp17
    - ./travis_gcc_cpp17
    
  Se le solicitará seleccionar las siguientes variables:
   - el número máximo: los números aleatorios se generaran del 0 a este número
   - el número de nodos: la cantidad de números que se le insertarán al árbol. 
   - el número de elementos a buscar: como máximo el número de nodos, misma cantidad que se utilizará para la eliminiación . 
   - si desea generar un árbol avl, o un árbol B
  
  NOTA: el código de menu está implementado específicamente para enteros en el main, si desea utilizarlo de forma genérica habrá que cambiar el código main. 
  
###### b. Corriéndolo con parámetros default. Deberá correr los siguientes comandos en terminal:
    -  g++ MenuNoUser.cpp -std=c++17 -o travis_gcc_cpp17
    -   ./travis_gcc_cpp17
    

## 3. Referencias

-  http://c.conclase.net/ficheros/?cap=004
-  https://www.geeksforgeeks.org/fseek-in-c-with-example/
-  http://www.cplusplus.com/reference/cstdio/
