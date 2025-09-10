#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;
struct nodoRecurso{
    string dominio;
    string path;
    string titulo;
    int tiempo;
};
//Dice que se hace con hash , y el hash debe usar una funcion de doble hash. Pero no se sobre que, no lo pense.
struct tablaHash {
    nodoRecurso* tabla;
    int largo;
    int cantidadaRecursos;
};

class hashCerrado {
    private:
    tablaHash*tH;


    int fh(int i,string dominio){
        return h1(dominio) + i*h2(dominio);
    }

    int h1 (string aPoner){
        
    }
    int h2 (string aPoner){
        
    }

    void PUTRecursivo(string dominio, string path, string titulo, int tiempo){
        if(this->tH[fh(0,dominio)])
    }
        
    public:
    void PUT(dominio,path,titulo,tiempo){
        this->PUTRecursivo(dominio,path,titulo,tiempo);
    };

    void GET(dominio,path){

    };
    
    void REMOVE(dominio,path){

    };
    
    void CONTAINS(dominio,path){

    };
    
    void COUNT_DOMAIN(dominio){

    };
    
    void LIST_DOMAIN(dominio){

    };

    void CLEAR_DOMAIN(dominio){

    };

    void SIZE(){

    };

    void CLEAR(){

    };
    
};


int main()
{
    // TODO
    return 0;
}