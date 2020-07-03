//  Algorytm Diakstry
//  main.cpp
//  AiSD_10
//
//  Created by Piotr Sularz on 19/12/2019.
//  Copyright © 2019 Piotr Sularz. All rights reserved.
//

#include <iostream>

using namespace std;

struct edge{
    int s; //start
    int t;
    int v;
};

class Graph{
    private:
        int** adjMatrix;
        int n;                //liczba węzłów
    public:
    Graph(int n, int m, edge edges[], bool directed = true){    //tworzy graf w oparciu o pdaną listę krawędzi
        this->n=n;
        adjMatrix=new int* [n];
        for(int i=0;i<n;i++){
            adjMatrix[i]=new int[n];
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                adjMatrix[i][j]=1000;
                for(int k=0;k<m;k++){
                    if(edges[k].s == i && edges[k].t == j){
                        adjMatrix[i][j]=edges[k].v;
                    }
                }
            }
        }
    }
    
    int edgeCnt(){
        int m=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;i++){
                if(adjMatrix[i][j]==1){
                    m++;
                }
            }
        }
        return m/2;
    }                    //zwraca liczbę krawędzi
    
    int nodeCnt(){
        return n;
    }                    //zwraca liczbę węzłów
    void insertEdge(int u, int v,int value){
        adjMatrix[u][v]=value;
    }            //wstawia krawędź
    void deleteEdge(int u, int v){
        adjMatrix[u][v]=0;
    }            //usuwa krawędź
    bool check(int u, int v){
        return adjMatrix[u][v]>0;
    }
    
    void vistitNode(int node,bool* visited){
        visited[node]=true;
        cout<<node<<" ";
        for(int i=0;i<n;i++){
            if(!visited[i] && adjMatrix[i][node]==1){
                vistitNode(i,visited);
            }
        }
    }
    
    int* Dijkstra(int s){ // s węzeł źródłowy, zwraca tabelę odległości
        int liczbaWezlow = nodeCnt();
        int* d=new int[liczbaWezlow];
        int* pi=new int[liczbaWezlow];
        int* S=new int[liczbaWezlow];
        int u=0;
        
        for(int i=0;i<liczbaWezlow;i++){
            d[i]=1000;
            pi[i]=-1;
            S[i]=0;
        }
        d[s]=0;
        
        for(int i=0;i<liczbaWezlow;i++){
            u = find(d,S,liczbaWezlow);
            S[u]=1;
        
            for(int v=0;v<liczbaWezlow;v++){
                if(d[v]>d[u]+adjMatrix[u][v]){
                    d[v]=d[u]+adjMatrix[u][v];
                    pi[v]=u;
                }
            }
        }
        return d;
    }
    
    int find(int* d,int* S,int n){
        int min=0;
        int wartosc=1000;
        for(int i=0;i<n;i++){
            if(S[i]==0 && d[i]<wartosc){
                min=i;
                wartosc=d[i];
            }
        }
        return min;
    }
    
    void path(int s, int t){
        int* d=Dijkstra(s);
        cout<<"Najkrotsza sciazka pomiedzy "<<s<<" i "<<t<<":"<<d[t];
        cout<<"\n";
    }
    
    void path2(int s,int t){ // s węzeł źródłowy, zwraca tabelę odległości
            int liczbaWezlow = nodeCnt();
            int* d=new int[liczbaWezlow];
            int* pi=new int[liczbaWezlow];
            int* S=new int[liczbaWezlow];
            int u=0;
            
            for(int i=0;i<liczbaWezlow;i++){
                d[i]=1000;
                pi[i]=-1;
                S[i]=0;
            }
            
            d[s]=0;
            
            for(int i=0;i<liczbaWezlow;i++){
                u = find(d,S,liczbaWezlow);
                S[u]=1;
            
                for(int v=0;v<liczbaWezlow;v++){
                    if(adjMatrix[u][v]!=1000){
                        if(d[v]>d[u]+adjMatrix[u][v]){
                            d[v]=d[u]+adjMatrix[u][v];
                            pi[v]=u;
                        }
                    }
                }
            }
            cout<<"Najkrotsza sciazka pomiedzy "<<s<<" i "<<t<<" : ";
            bool glebiej=true;
            int wczesniejszy=t;
            cout<<t<<"\t";
            while(glebiej){
                cout<<pi[wczesniejszy]<<"\t";
                wczesniejszy=pi[wczesniejszy];
                if(wczesniejszy==s){
                    glebiej=false;
                }
            }
            cout<<"\n";
        }
    
        friend ostream& operator<<(ostream& out, Graph& g);
    ~Graph(){
        for(int i=0;i<n;i++){
            delete adjMatrix[i];
        }
        delete adjMatrix;
    }
};

ostream& operator<<(ostream& out, Graph& g){
    out<<"Macierz sasiedztwa:\n";
    for(int i=0;i<g.n;i++){
        for(int j=0;j<g.n;j++){
            out<<g.adjMatrix[i][j];
            out<<"\t";
            if(g.adjMatrix[i][j]!=1000){
                out<<"\t";
            }
        }
        out<<"\n";
    }
    return out;
}

void rysuj(int skala){
    int n=skala;
    //1 poziom
    for(int i=0;i<n-4;i++){
            for(int k=0;k<n-i;k++){
                cout<<" ";
            }
            for(int k=0;k<2*i+1;k++){
                cout<<"*";
            }
            cout<<"\n";
    }
    //2 poziom
    for(int i=1;i<n-2;i++){
            for(int k=0;k<n-i;k++){
                cout<<" ";
            }
            for(int k=0;k<2*i+1;k++){
                cout<<"*";
            }
            cout<<"\n";
    }
    //3 poziom
    for(int i=1;i<n;i++){
        for(int k=0;k<n-i;k++){
            cout<<" ";
        }
        for(int k=0;k<2*i+1;k++){
            cout<<"*";
        }
        cout<<"\n";
    }
    //konar
    int m=(n-2);
    for(int i=0;i<m;i++){
        cout<<" ";
    }
    for(int i=0;i<3;i++){
        cout<<"*";
    }
    cout<<"\n";
}

int main(int argc, const char * argv[]) {
    int n = 10, m =19;
    edge undirectedConnectedGraph[]={{0,1,5}, {4,0,2}, {6,0,5}, {1,2,2}, {1,7,3},{7,1,3}, {2,3,7},{3,2,7}, {2,8,6}, {5,3,2}, {3,9,5}, {7,4,1}, {5,8,5},{8,5,5}, {6,7,5},{7,6,5}, {7,8,1},{8,7,1}, {9,8,4}};
    Graph g(n,m,undirectedConnectedGraph);
    cout<<g;
    int* tab=g.Dijkstra(0);
    for(int i=0;i<n;i++){
        cout<<i<<": "<<tab[i]<<"\n";
    }
    g.path(0, 6);
    g.path2(0, 6);
    
    rysuj(13);
    return 0;
}
