#include <stdio.h>
#include<iostream> 
#include <time.h>
#include<string.h>
#include<vector>
#include<tuple>
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
    int counter =0;
    if(!archivo) 
        printf("no existe archivo a leer"); 
    if(archivo != NULL){
        while(fread (&temp, sizeof(temp), 1, archivo)== 1){
        cout<<"-----------"<<counter<<endl;

        for(int i=0; i<N; i++){
        printf ("nodo = %d\n", temp.key[i]);
        }
        counter++;
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

void fillInOthers(){
    Node<I> fill; 
    fill= initialize(fill);
    for(int i=getLast(depth); i>f.finalIndice(); i--){
        f.escribirRegistro(i, fill);
    }
}

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

int getChildLeft(int index){
    int result=0;
    result= (index/N)+index+1;
    if(result>getLast(depth)){
        return -1;
    }
    return result;
}

int getChildRight(int index){
    int left = getChildLeft(index);
    if(left == -1){
        return left;
    }
    return left+1;
}

int Buscar(int number_to_search){
    current_node= f.leerConIndice(current_index);
    for(int i=0; i<N; i++){
        if(current_node.key[i]==number_to_search){
            return (N*current_index)+i;
        }else if(current_node.key[i]>number_to_search || current_node.key[i]==0){
            current_index= getChildLeft(current_index+i);
            return Buscar(number_to_search);
        }
    }
    current_index=0;
    current_node= f.leerConIndice(current_index);
    return -1;
}


};


int main(){
    BTree<int> arb;
    int array_insert[19] = {10, 20, 65, 90, 4, 5, 25, 56, 57, 60, 70, 75, 12, 18, 80, 85, 94, 95, 8};
    for(int i=0; i<19; i++){
        arb.Insert(array_insert[i]);
    }



  

    cout<<"this is the result"<<endl;
    arb.f.leerArchivo();

    cout<<" searching for 90, found in "<<arb.Buscar(90)<<endl;
        cout<<" searching for 10, found in "<<arb.Buscar(10)<<endl;
        cout<<" searching for 11, found in "<<arb.Buscar(11)<<endl;




    return 0;
}