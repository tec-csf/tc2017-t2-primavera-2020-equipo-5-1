/**
 * This file is part of {{ tc2017-t2-primavera-2020-equipo-5-1 }}.
 *
 * Developed for Diseño, Análisis de Algoritmos
 * This product includes software developed by the LSST Project
 * (https://www.lsst.org).
 * See the COPYRIGHT file at the top-level directory of this distribution
 * for details of code ownership.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include<iostream> 
#include<string.h>
#include "arbol_b.cpp"
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
 * Menu let's you select whether you will be running AVL Tree or BTree  
 *
 */
class Menu{
    public:

    /**
    * Runs main menu for user selection. 
    *
    */
    void runMenu(){
        int option=0;
        int size =0;
        int max =0;
        int num_busqueda =0;
    

        //get type of tree, size of tree, and range from which to generate random numbers
        cout<<"¿Qué tipo de árbol deseas generar? (responde 1 0 2) \n 1. AVL \n 2. árbol B "<<endl;
        cin>>option;
        cout<<"¿De qué tamaño deseas que sea tu árbol?"<<endl;
        cin>>size;
        cout<<"Escribe el límite máximo: "<<endl;
        cin>>max;

        //generate random numbers
        srand((int)time(0));
        int array[size];
        for(int i=0; i<size; i++){
            array[i]= (rand() % max) + 1;
        }
     

        if(option ==1){
            //here is implemnentation of AVL tree 

        }
        if(option ==2){
            BTree<int> tree;
            auto time_before = high_resolution_clock::now();
            for(int i=0; i<size; i++){
                tree.insert(array[i]);
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
                int result = tree.Buscar(array_busqueda[i]);
            }
            time_after = high_resolution_clock::now();

            cout<<"TIEMPO DE BÚSQUEDA EN NANOSEGUNDOS "<<duration_cast<nanoseconds>(time_after-time_before).count()<<endl;


            time_before = high_resolution_clock::now();
            for(int i=0; i<num_busqueda; i++){
                tree.Borrar(array_busqueda[i]); 
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