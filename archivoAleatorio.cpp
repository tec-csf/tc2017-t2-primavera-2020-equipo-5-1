#include <stdio.h>
#include<iostream> 
#include <time.h>
#include<string.h>
#include<vector>
#include <math.h>


#include <cstdlib>

using namespace std;

#define N 4

template <class T>
struct Node
{
    T key[N];
    int nivel;
};


template <class T>
class FileManager{
    public:
    Node<T> temp;
    FILE* archivo;

FileManager(){
      archivo = fopen("datos.dat", "w+b");
}
~FileManager(){
     fclose(archivo);
}
void leerArchivo(){
    fseek(archivo, 0, SEEK_SET);

    if(!archivo) 
        printf("no existe archivo a leer"); 
    if(archivo != NULL){
        while(fread (&temp, sizeof(temp), 1, archivo)== 1){
        for(int i=0; i<N; i++){
        printf ("nodo = %d\n", temp.key[i]);
        }
        cout<<"-----------"<<endl;
        }
    }else{
        perror("No se puede abrir datos.dat");
    }
}



void escribirRegistro(int i, Node<int> m)
{   
    fseek(archivo, (i)*sizeof(temp), SEEK_SET);
    fwrite (&m, sizeof(temp), 1, archivo);
}

void agregarRegistro(Node<int> m)
{   
    fseek(archivo, 0, SEEK_END);
    fwrite (&m, sizeof(temp), 1, archivo);
}

int finalIndice(){
    fseek(archivo, 0, SEEK_END);
    return ftell(archivo)/sizeof(temp);
}


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
bool NodeFull(int index){
    Node<I> root = f.leerConIndice(index);
    for(int i=0; i<N; i++){
        if(root.key[i]==0){
            return false;
        }
    }
    return true;
}




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
      
       if(current_node.key[i]> in || current_node.key[i]==0){
           if(nivel!=depth){
                int child = getChildLeft(current_index+i);
               current_index = child/N;
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
       }else{
           if(i==N-1){
                splitChild(current_index, in);
                current_index=0;
                nivel=0;
               break;
           }
       }

    
   } 
      
      
    }
}

void insertNode(I in, int where_insert){
    Node<I> n= f.leerConIndice(where_insert);
    vector<I> vec = nodeToArray(n);
    vec.push_back(in);
    sort(vec.begin(), vec.end());
    n = arrayToNode(vec); 
   
    f.escribirRegistro(where_insert, n);
    
}   


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
    f.escribirRegistro(index_to_split, childFul);
    moveAll(1,index_to_split+1);
    f.escribirRegistro(index_to_split+1, *bigger);
    int p = getParentRight(index_to_split);
    if(p!=-1){
        if(NodeFull(p/N)){ 
            splitChild(p/N, vector_temp.at(N/2));
        }else{
            insertNode(vector_temp.at(N/2), p);
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

void fillInOthers(){
    Node<I> fill; 
    fill= initialize(fill);
    for(int i=getLast(depth); i>f.finalIndice(); i--){
        f.escribirRegistro(i, fill);
    }
}

void moveAll(int no_move, int initial){
    Node<I> n;
    for(int i= getLast(depth); i>=initial; i--){
        n = f.leerConIndice(i);
        f.escribirRegistro(i+no_move, n);
    }
    n= initialize(n);
    for(int i=initial; i<no_move; i++){
        f.escribirRegistro(i, n);
    }
}

int getLast(int d){
    int acum=0;
    for(int i=0; i<=d; i++){
        acum+=pow(N+1, i);
    }
    return acum-1;
}

int getFirst(int d){
    return getLast(d-1)+1;
}
Node<I> initialize(Node<I> node){
    for(int i=0; i<N; i++){
        node.key[i]=0;
    }
    return node;
}

int getParentRight(int child)
{
    int n_inicia= getFirst(nivel);
    cout<<" this is nivel "<<nivel<<endl;
    if(child==0){
        return -1;
    }
    return ((child-n_inicia)/N);
}

int getChildLeft(int parent){
    int n_inicia= N*getFirst(nivel+1);
    return (parent*N)+n_inicia;
}


};

int main(){
    BTree<int> arb;
    cout<<"this is parent of 20 "<<arb.getParentRight(20)<<endl;
    int insert[14] = {10, 20, 65, 4, 5, 8, 12, 18, 25, 56, 70, 75, 80, 85};
    for(int i=0; i<14; i++){
        arb.Insert(insert[i]);
    }
    arb.Insert(78);
    cout<<"this is the result"<<endl;
    arb.f.leerArchivo();

    return 0;
}
