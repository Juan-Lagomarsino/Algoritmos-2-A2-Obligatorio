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
    nodoRecurso** tabla;
    int largo;
    int cantidadaRecursos;
    tablaHash(int capacidad){
        largo = capacidad;
        cantidadaRecursos = 0;
        tabla = new nodoRecurso*[capacidad];
        for (int i = 0; i < capacidad; i++) {
            tabla[i] = NULL;
        }
        /*tabla = new nodoRecurso[capacidad];
        for (int i = 0; i < capacidad; i++) {
            tabla[i].dominio = "";
            tabla[i].path = "";
            tabla[i].titulo = "";
            tabla[i].tiempo = 0;
        }*/
    }
};

class hashCerrado {
    private:
        tablaHash* tH;

        int fh(int i,string dominio){
            return h1(dominio) + i*h2(dominio);
        }
        
        // Ref: https://hash-table.uruguayan.ninja/9
        int h1 (string aPoner){
            int h = 0;
            for (int i = 0; i < aPoner.length(); i++)
                h = 31 * h + int(aPoner[i]);
            return h;
        }
        
        // Ref: https://hash-table.uruguayan.ninja/9 + Modificacion nuestra.
        int h2 (string aPoner){
            int h = 0;
            for (int i = 0; i < aPoner.length(); i++)
                h = 37 * h + (int(aPoner[i])^2); //37 siguiente primo del 31 
            return h;
        }

        void PUTRecursivo(string dominio, string path, string titulo, int tiempo, int intentos){
            int pos = fh(intentos,dominio) % tH->largo;
            if (tH->tabla[pos].dominio == ""){
                tH->tabla[pos].dominio = dominio;
                tH->tabla[pos].path = path;
                tH->tabla[pos].titulo = titulo;
                tH->tabla[pos].tiempo = tiempo;
                tH->cantidadaRecursos++;
            }else{
                PUTRecursivo(dominio,path,titulo,tiempo,intentos+1);
            }
        }

        nodoRecurso GETRecursivo(string dominio, string path, int intentos){
            int pos = fh(intentos,dominio) % tH->largo;
            if(intentos >= tH->cantidadaRecursos || tH->tabla[pos].dominio == ""){
                //que retorne null pero no se puede
            }else if(tH->tabla[pos].dominio == dominio && tH->tabla[pos].path == path){
                return tH->tabla[pos];
            }else{
                GETRecursivo(dominio, path, intentos++);
            }

        }

        
    public:
    void PUT(string dominio,string path,string titulo,int tiempo){
        this->PUTRecursivo(dominio,path,titulo,tiempo, 0);
    };

    void GET(string dominio,string path){
        this->GETRecursivo(dominio,path,0);
    };
    
    void REMOVE(string dominio,string path){

    };
    
    void CONTAINS(string dominio,string path){

    };
    
    void COUNT_DOMAIN(string dominio){

    };
    
    void LIST_DOMAIN(string dominio){

    };

    void CLEAR_DOMAIN(string dominio){

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