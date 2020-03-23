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
#include <time.h>
#include<string.h>
#include<vector>
#include<tuple>
#include <math.h>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define N 4

template <class T>
struct Node
{
    T key[N];
};


/**
 * File Manager stores all functions related to writting, reading and eliminated in file. 
 *
 */

template <class T>
class FileManager{
    public:
    Node<T> temp;
    FILE* archivo;

FileManager()
{
      archivo = fopen("datos.dat", "w+b");
}
~FileManager()
{
     fclose(archivo);
}

/**
 * Reads all nodes in file 
 *
 */

        void leerArchivo()
        {
            fseek(archivo, 0, SEEK_SET);
            int counter =0;
            if(!archivo) 
                printf("no existe archivo a leer"); 
            if(archivo != NULL)
            {
                while(fread (&temp, sizeof(temp), 1, archivo)== 1)
                {
                cout<<"-----------"<<counter<<endl;

                    for(int i=0; i<N; i++)
                    {
                    printf ("nodo = %d\n", temp.key[i]);
                    }
                counter++;
                }
                
            }else
            {
                perror("No se puede abrir datos.dat");
            }
        }


/**
 * Writes a node in a specific position within file
 *
 * @param[in] the index where to insert the node 
* @param[in] The node that will be inserted 
 */

            void escribirRegistro(int i, Node<int> m)
            {   
                fseek(archivo, (i)*sizeof(temp), SEEK_SET);
                fwrite (&m, sizeof(temp), 1, archivo);
            }

/**
 * Adds a node by the end of the file 
 *
 * @param[in] Node to write
 */

            void agregarRegistro(Node<int> m)
            {   
                fseek(archivo, 0, SEEK_END);
                fwrite (&m, sizeof(temp), 1, archivo);
            }

/**
 * Tells us the position of the last node in file
 *
 * @param[out] integer telling us position of end of file 
 */
            int finalIndice()
            {
                fseek(archivo, 0, SEEK_END);
                return ftell(archivo)/sizeof(temp);
            }

/**
 * Reads the node at index i 
 *
 * @param[in] index where node will be read 
 * @param[out] Node that has just been read 
 */

            Node<T> leerConIndice(int i)
            {   
                fseek(archivo, (i)*sizeof(temp), SEEK_SET);
                fread (&temp, sizeof(temp), 1, archivo);
                return temp;
            }
};

template <class I>
class BTree{
    public:
    FileManager<I> f;
    Node<I> current_node;
    int current_index;
    int nivel;
    int depth;
BTree(){
    nivel=0;
    depth=0;
    current_index=0;
}

/**
 * Checks if node is full 
 *
 * @param[in] index of node to check 
 * @param[out] boolean that states 0 it is not full or 1 it is full
 */

bool NodeFull(int index){
    Node<I> root = f.leerConIndice(index);
    for(int i=0; i<N; i++){
        if(root.key[i]==0){
            return false;
        }
    }
    return true;
}


/**
 * Auxiliary funtion for insert that checks whether Node is already in tree so that no two nodes are equal
 *
 */

void insert(I in){
    if(Buscar(in)==-1){
        Insert(in);
    }
}


/**
 * Main insert function, inserts node into B tree
 *
 * @param[in] number to be inserted in b tree 
 */
void Insert(I in) 
{ 

    current_node= f.leerConIndice(current_index);
    //cuando no hay raiz 
    if(f.finalIndice()==0){
        current_node= initialize(current_node);
        current_node.key[0]=in;
        f.escribirRegistro(0, current_node);
    }else{

   for(int i=0; i<N; i++){
      
       if(current_node.key[i]> in || current_node.key[i]==0 || N-1==i)
       {
           if(nivel!=depth){
            int child = 0;
            if(current_node.key[i]<in  && current_node.key[i]!=0){
                child= getChildRight(current_index+i);
            }else{
                child =getChildLeft(current_index+i);
            }

               current_index = child;
               nivel++;
               Insert(in);
               break;
               
           }else{
               if(NodeFull(current_index)){
                   splitChild(current_index, in);
                   
               }else{
                   insertNode(in, current_index);
               }
                current_index=0;
                nivel=0;
               break;
               
           }
        }

    
        } 
    }
      
    
}


/**
 * Inserts number once we already know the index where it should be inserted 
 *
 * @param[in] number to be inserted 
 * @param[in] index of where the number should be inserted 
 */

void insertNode(I in, int where_insert){
    Node<I> n= f.leerConIndice(where_insert);
    vector<I> vec = nodeToArray(n);
    vec.push_back(in);
    sort(vec.begin(), vec.end());
    n = arrayToNode(vec); 
   
    f.escribirRegistro(where_insert, n);
    
}   

/**
 * Converts a Node into a Vector 
 *
 * @param[in] Node that must be converted to vector
 * @param[out] Vector of length N+1 
 */

vector<I> nodeToArray(Node<I> node){
    vector<I> temporal;
    for(int i=0; i<N; i++)
    {
        if(node.key[i]!=0){
            temporal.push_back(node.key[i]);
        }
    }
    return temporal;
}

/**
 * Converts a Vector into Node
 *
 * @param[in] Vector that will be converted to node 
 * @param[out] Node with all elements in vector form parameter 
 */

Node<I> arrayToNode(vector<I> vec){
    Node<I> temporal;
    for(int i=0; i<N; i++)
    {
        if(i<vec.size()){
        temporal.key[i]= vec.at(i);
        }else{
        temporal.key[i]= 0;
        }
    }
    return temporal;
}

/**
 * Splits a full node where a new node needs to be inserted 
 *
 * @param[in] Index of node that needs to be splitted, and number to be inserted 
 */


void splitChild(int index_to_split, I to_insert)
{
    Node<I> childFul = f.leerConIndice(index_to_split);
    vector<I> vector_temp = nodeToArray(childFul);
    vector_temp.push_back(to_insert);
    sort(vector_temp.begin(), vector_temp.end());
    childFul= initialize(childFul);
    Node<I> *bigger = new Node<I>();
    for(int i=0; i<N/2; i++){
        childFul.key[i]=vector_temp.at(i);
    }
    int counter = 0;
    for(int j= N/2+1; j<=N; j++){
        bigger->key[counter++]= vector_temp.at(j);
    }

     int p =0;
    if(index_to_split%(N+1)==0){
        p = getParentLeft(index_to_split);
    }else{
        p = getParentRight(index_to_split);
    }

   if(Occupied(p)==-1 && p%N != N-1){
        f.escribirRegistro(index_to_split, childFul);
        moveAll(1,index_to_split+1);
        f.escribirRegistro(index_to_split+1, *bigger);
   }
    
    

    if(p!=-1){
        
        if(NodeFull(p/N)){
            splitChild(p/N, vector_temp.at(N/2));
        }else{
           if(Occupied(p)!=-1 || p%N == N-1){
               if(p%N==N-1){
                   p--;
               }
            int child =0;
            if(p%N == 0){
                child= getChildRight(p);
            }  else{
                child= getChildLeft(p);
            }
            
            if(NodeFull(child)==0){
                int get_down = specialSplit(vector_temp, p, index_to_split, Occupied(p));
               Node<I> temporal= f.leerConIndice(p/N);
               temporal.key[p%N]=0;
               f.escribirRegistro(p/N, temporal);
               insertNode(get_down, p/N);
            }else{
                
                insertNode(vector_temp.at(N/2), p/N);
           
                f.escribirRegistro(index_to_split, childFul);
              
                moveAll(1,index_to_split+1);
                f.escribirRegistro(index_to_split+1, *bigger);

            } 
               
           }else{
                insertNode(vector_temp.at(N/2), p/N);
           }     
        }
    }else{
        
        depth++;
        fillInOthers();
        nivel--;
        Node<I> *root_new = new Node<I>();
        root_new->key[0] = vector_temp.at(N/2);
        moveAll(1, index_to_split);
       
        f.escribirRegistro(index_to_split, *root_new);          
    }
}

/**
 * When there is a possibility of filling the leaves before filling the root
 *
 * @param[in] numbers of filled out node
 * @param[in] parent node of filled out node 
 * @param[in] index of filled out node 
 * @param[in] index of node where parent node is stored.
 * @param[out] number that should be reinserted in parent node 
 */

int specialSplit(vector<I> vector_temp, int p, int index_to_split, int parent_index){
    int return_value=0;
     Node<I> node_insertion;

    if(p%N==0){
        for(int i=0; i<N; i++){
        node_insertion.key[i]=vector_temp.at(i);
        }   
        
        insertNode(parent_index, getChildRight(p));
        return_value=vector_temp.at(N);
    }else{
        for(int i=1; i<=N; i++){
        node_insertion.key[i-1]=vector_temp.at(i);
        }   
        insertNode(parent_index, getChildLeft(p)) ;
        return_value=vector_temp.at(0);
    }   
    f.escribirRegistro(index_to_split, node_insertion);
    return return_value;
}

/**
 * Fills all nodes that aren't being used with 0's
 *
 */
void fillInOthers(){
    Node<I> fill; 
    fill= initialize(fill);
    for(int i=getLast(depth); i>f.finalIndice(); i--){
        f.escribirRegistro(i, fill);
    }
}

/**
 * checks if a specific node si occupied 
 * 
 * @param[in] node to check whether it is occupierd
 * @param[out] if it is occupied returns number in node, if not returns -1
 *
 */
int Occupied(int p){
    int index = p%N;
    int i = p/N;
    Node<I> n= f.leerConIndice(i);
    if(n.key[index]==0 || p==-1){
        return -1;
    }else{
        return n.key[index];
    }
}

/**
 * checks if a specific node si occupied 
 * 
 * @param[in] node to check whether it is occupierd
 * @param[out] if it is occupied returns number in node, if not returns -1
 *
 */
void moveAll(int no_move, int initial){
    Node<I> n;
    for(int i= getLast(depth)-no_move; i>=initial; i--){
        n = f.leerConIndice(i);
        f.escribirRegistro(i+no_move, n);
    }
    n= initialize(n);
    for(int i=initial; i<initial+no_move; i++){
        f.escribirRegistro(i, n);
    }
}

/**
 * Gets the last node of a specific level
 * 
 * @param[in] the level or depth 
 * @param[out] the index of the last node in that level 
 *
 */

int getLast(int d){
    int acum=0;
    for(int i=0; i<=d; i++){
        acum+=pow(N+1, i);
    }
    return acum-1;
}


/**
 * Gets the last furst of a specific level
 * 
 * @param[in] the level or depth 
 * @param[out] the index of the first node in that level 
 *
 */

int getFirst(int d){
    return getLast(d-1)+1;
}


/**
 * Sets all node to zeros 
 * 
 * @param[in] node that we wan't to initialize 
 * @param[out] node with all numbers set to zeros
 *
 */

Node<I> initialize(Node<I> node){
    for(int i=0; i<N; i++){
        node.key[i]=0;
    }
    return node;
}

/**
 * Gets parent to the right of index 
 * 
 * @param[in] index to which we want to retrieve parent 
 * @param[out] the index of parent node 
 *
 */

int getParentRight(int index)
{
if(index==0){
    return -1;
}
 if(index%(N+1)==0){
        return -1;
 }else{
     return ((N*index)-1)/(N+1);

 }
}

/**
 * Gets parent to the left of index 
 * 
 * @param[in] index of child from which we will retrieve parent
 * @param[out] the index of parent node 
 *
 */

int getParentLeft(int index){
    if(index==0){
    return -1;
    }
    if(index%(N+1)==1){
     return -1;
    }else{
     return ((N*index)-2)/(N+1);
 }
}

/**
 * Gets child node to the left of index 
 * 
 * @param[in] index of parent from which we will retrieve child
 * @param[out] the index of parent node 
 *
 */


int getChildLeft(int index){
    int result=0;
    result= (index/N)+index+1;
    if(result>getLast(depth)){
        return -1;
    }
    return result;
}

/**
 * Gets child node to the right of index 
 * 
 * @param[in] index of parent from which we will retrieve child
 * @param[out] the index of parent node 
 *
 */

int getChildRight(int index){
    int left = getChildLeft(index);
    if(left == -1){
        return left;
    }
    return left+1;
}

/**
 * Search function, that returns the index of number being searched in tree 
 * 
 * @param[in] number to search for in tree 
 * @param[out] the index of where the number was found 
 *
 */

int Buscar(int number_to_search){
    int resultado=0;
    if(f.finalIndice()==0){
        return -1;
    }
    current_node= f.leerConIndice(current_index);
    for(int i=0; i<N; i++){

        if(current_node.key[i]==number_to_search){
            return (N*current_index)+i;
        }else if((current_node.key[i]>number_to_search || current_node.key[i]==0) && depth!=nivel){
            current_index= getChildLeft(current_index+i);
            nivel++;
            return Buscar(number_to_search);
        }
    }
    nivel=0;
    current_index=0;
    current_node= f.leerConIndice(current_index);
    return -1;
}

/**
 * function that erases particular node from tree 
 * 
 * @param[in] number to erase from tree
 *
 */
void Borrar(int no_erase){
    int general_index = Buscar(no_erase);
    if(general_index != -1)
    {
        current_index = general_index/N;
        current_node = f.leerConIndice(current_index);
        current_node.key[general_index%N]=0;
        f.escribirRegistro(current_index, current_node);
        if(getLast(depth-1)< current_index){
            //when it is leaf node
            
            if(nodeSize(current_node)==1){
            
                int parent_index = getParentRight(current_index);
                Node<I> replace = f.leerConIndice(getChildRight(parent_index));
                

                if(nodeSize(replace)==2){
                    
                    insertNode(Occupied(parent_index), current_index);
                   

                    Node<I> parent_node = f.leerConIndice(parent_index);
                    parent_node.key[parent_index%N]=0;
                    f.escribirRegistro(parent_index/N, parent_node);

                    current_node = f.leerConIndice(current_index);
                    for(int i=0; i<N/2; i++){
                        current_node.key[N/2+i]=replace.key[i];
                    }
                    f.escribirRegistro(current_index, current_node);
                  
                    replace = initialize(replace);
                    f.escribirRegistro(getChildRight(parent_index), replace);
                    sortNode(parent_node, parent_index/N);
                }else if(nodeSize(replace)==0){
                    //doesn't have node from right try left, if it doesn't have from left 
                }
                else{//borrowing form right 
                    insertNode(Occupied(parent_index), current_index);
                    Node<I> parent_node = f.leerConIndice(parent_index/N);
                    parent_node.key[parent_index%N]=0;
                    f.escribirRegistro(parent_index/N, parent_node);
                    

                    insertNode(replace.key[0], parent_index/N);
                    
                    replace.key[0]=0;
                    f.escribirRegistro(getChildRight(parent_index), replace);
                   
                    sortNode(replace, getChildRight(parent_index));

                    sortNode(parent_node, parent_index);
                   

                }

            }
             current_node= f.leerConIndice(current_index);
            sortNode(current_node, current_index);
           
        }else{
            //when it is non leaf

        }   
    }
    current_index=0;
    current_node= f.leerConIndice(current_index);
}


/**
 * Function that sorts elements within node 
 * 
 * @param[in] node that needs to be sorted
 * @param[in] index where node to be sorted is found 
 *
 */
void sortNode(Node<I> nod, int index_node)
{
    vector<I> vec_sort= nodeToArray(nod);
    sort(vec_sort.begin(), vec_sort.end());
    Node<I> node_sorted= arrayToNode(vec_sort);
    f.escribirRegistro(index_node, node_sorted);
}

/**
 * Function that returns the size of node 
 * 
 * @param[in] node from which we want to retrieve size 
 * @param[out] size of node 
 *
 */
int nodeSize(Node<I> n){
    int size=0;
    for(int i=0; i<N; i++){
        if(n.key[i]!=0){
            size++;
        }
    }
    return size;
}
};
