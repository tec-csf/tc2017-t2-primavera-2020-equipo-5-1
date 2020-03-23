# Tarea *2*. *Análisis de Algoritmos*

---

##### Integrantes:
1. Carla Pérez Gavilán Del Castillo - *A01023033* - *CSF*
2. Rubén Hernández Rivas - *A01024669* - *CSF*
3. Christian Alberto Dalma Schultz - *A01423166* - *CSF*
4. *[Poner aquí Nombre y Apellidos del integrante 4]* - *[Poner aquí su Matrícula]* - *[Poner aquí su campus]*
5. *[Poner aquí Nombre y Apellidos del integrante 5]* - *[Poner aquí su Matrícula]* - *[Poner aquí su campus]*

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
   INSERCIÓN: 
    - se búsca el índice donde se va a insertar el nuevo número
    - se busca si este indice tiene hijos 
    
    FUNCIÓN QUE BUSCA HIJO TENIENDO PADRE:
       - para la función que busca el hijo siendo el padre se utiliza la siguiente fórmula: 
    FUNCIÓN QUE BUSCA PADRE TENIENDO HIJO:
    
    BORRAR: 
    
    BUSCAR:


### 2.1 Pasos a seguir para utilizar la aplicación

Hay dos maneras de correr el código: 
a. De forma ineractiva, se deben correr los siguientes comandos en términal: 
    - g++ Menu.cpp -std=c++17 -o travis_gcc_cpp17
    - ./travis_gcc_cpp17
  Se le solicitará seleccionar las siguientes variables:
   - el número máximo: los números aleatorios se generaran del 0 a este número
   - el número de nodos: la cantidad de números que se le insertarán al árbol. 
   - el número de elementos a buscar: como máximo el número de nodos, misma cantidad que se utilizará para la eliminiación . 
   - si desea generar un árbol avl, o un árbol B
  
   - si desea generar un 
  NOTA: el código de menu está implementado específicamente para enteros en el main, si desea utilizarlo de forma genérica habrá que cambiar el código main. 
  
b. Corriéndolo con parámetros default. Deberá correr los siguientes comandos en terminal:
    - g++ MenuNoUser.cpp -std=c++17 -o travis_gcc_cpp17
    - ./travis_gcc_cpp17
    

## 3. Referencias

    -  http://c.conclase.net/ficheros/?cap=004
