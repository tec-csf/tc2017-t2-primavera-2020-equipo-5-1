#include <stdio.h>
#include<iostream> 
#include <time.h>
#include<string.h>

#include <cstdlib>


#define N 4

template <class T>
struct Node
{
    T key[N];
};


template <class T>
class FileManager{
    public:
    Node<int> temp;
    FILE* archivo;

void leerArchivo(){
    archivo = fopen("datos.dat", "r+b");
    if(!archivo) 
        printf("no existe archivo a leer"); 
    if(archivo != NULL){
        while(fread (&temp, sizeof(temp), 1, archivo)== 1){
        for(int i=0; i<N; i++){
        printf ("nodo = %d\n", temp.key[i]);
        }
        }
    }else{
        perror("No se puede abrir datos.dat");
    }
    fclose(archivo);
}

void escribirRegistro(int i, Node<int> m)
{   
    archivo = fopen("datos.dat", "a+b"); 
    fseek(archivo, (i)*sizeof(temp), SEEK_SET);
    fwrite (&m, sizeof(temp), 1, archivo);
    fclose(archivo);
}

void leerConIndice(int i)
{   
    archivo = fopen("datos.dat", "rb"); 
    fseek(archivo, (i)*sizeof(temp), SEEK_SET);
    fread (&temp, sizeof(temp), 1, archivo);
    for(int i=0; i<N; i++){
        printf ("nodo = %d\n", temp.key[i]);
    }
    fclose(archivo);
}


};

int main(){
    FileManager<int> f;
    Node<int> n;
    n.key[0]= 30;
    n.key[1]= 40;
    n.key[2]= 50;
    Node<int> b;
    b.key[0]= 20;
    b.key[1]= 23;
    f.escribirRegistro(0, n);
    f.escribirRegistro(1, b);
    f.leerConIndice(1);
    return 0;
}
