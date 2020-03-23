#include <stdio.h>
#include<iostream> 
#include<string.h>
#include "arbol_b.cpp"
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;


class Menu{
    public:

    void runMenu(){
        int option=0;
        int size =0;
        int max =0;
        int num_busqueda =0;
    
        cout<<"¿Qué tipo de árbol deseas generar? (responde 1 0 2)\n 1. AVL \n 2. árbol B "<<endl;
        cin>>option;
        cout<<"¿De qué tamaño deseas que sea tu árbol?"<<endl;
        cin>>size;
        cout<<"Escribe el límite máximo: "<<endl;
        cin>>max;

        //generar números aleatorios 
        srand((int)time(0));
        int array[size];
        for(int i=0; i<size; i++){
            array[i]= (rand() % max) + 1;
        }
     

        if(option ==1){
            
        }
        if(option ==2){
            BTree<int> tree;
            auto time_before = high_resolution_clock::now();
            for(int i=0; i<size; i++){
                tree.Insert(array[i]);
            }
            auto time_after = high_resolution_clock::now();
             cout<<"TIEMPO DE INSERCIÓN EN NANOSEGUNDOS "<<duration_cast<nanoseconds>(time_after-time_before).count()<<endl;
            
            cout<<"Cuántos números desesa buscar"<<endl;
            cin>>num_busqueda;
            int array_busqueda[num_busqueda];
            
            for(int i=0; i<num_busqueda; i++){
                int index = (rand() % size) + 1;
                int result =array[index];
                array_busqueda[i]=result;
            }
            
            time_before = high_resolution_clock::now();
            for(int i=0; i<num_busqueda; i++){
                
            }
            time_after = high_resolution_clock::now();

            cout<<"TIEMPO DE BÚSQUEDA EN NANOSEGUNDOS "<<duration_cast<nanoseconds>(time_after-time_before).count()<<endl;


            time_before = high_resolution_clock::now();
            for(int i=0; i<num_busqueda; i++){
                
            }
            time_after = high_resolution_clock::now();

            cout<<"TIEMPO DE ELIMINACIÓN EN NANOSEGUNDOS "<<duration_cast<nanoseconds>(time_after-time_before).count()<<endl;



        }
    }
    
};

int main(){
    Menu m;
    m.runMenu();

    return 0;
}