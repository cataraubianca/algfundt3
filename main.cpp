#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <bits/stdc++.h>
#include <tuple>

using namespace std;

ifstream f("abc.in");
ofstream g("abc.out");

#define nmax 50001
#define NMax 100001



class graf{
private:
    int n, m, cost_total;
    vector <vector <int> > muchii;
    void DFS(int s, vector<int>&vizitate);
    void st(int a, vector<int> vizitate, stack<int>& s);
    //tema 2
    priority_queue<int, vector <int>, greater<int> > pq;
    vector <pair<int,int> >graf_ponderat;
    vector<int> parinte;
    vector<int>inaltime;
    vector<pair<int,pair<int,int>>> muchii_cu_cost;
    vector<int>distanta;
    vector <bool> InCoada;
    vector <int> vizitate;
    int radacina_disjuncte(int n);
    //tema 3
    vector <int> adj_list[NMax];


public:
    graf(int n, int m);
    void citire_orientat(int m);
    void citire_neorientat(int m);
    void bfs(int s);
    int conexe(int s);
    bool Havel_Hakimi(vector<int>v, int n);
    void sortare_topologica(int n);
    //tema 2
    void dijkstra(int nod, vector <pair<int, int>>G[nmax]);
    void afiseaza_dijkstra();
    void bellman_ford(int nod, vector <pair<int, int>>G[nmax]);
    void kruskall();
    void uniune_disjuncte(int x,int y);
    bool aceeasi_padure(int x, int y);
    //tema 3
    graf(int n);
    void bfs_darb(int s, int &ultim, int &dist_max);
    void darb();
    void roy_floyd(int matrice[105][105]);
    void royfloyd();

};
//---------------------------------------------------------TEMA-1-------------------------------------------------------//
graf::graf(int n, int m)
{
    this->n=n;
    this->m=m;
}
graf::graf(int n)
{
    this->n=n;
}
void graf::citire_neorientat(int m)
{
    int nod1, nod2;
    for (int i = 0; i <= m; i++)
    {
        f >> nod1 >> nod2;
        muchii[nod1].push_back(nod2);
        muchii[nod2].push_back(nod1);
    }
}
void graf::citire_orientat(int m)
{
    int nod1, nod2;
    for (int i = 0; i <= m; i++)
    {
        f >> nod1 >> nod2;
        muchii[nod1].push_back(nod2);
    }
}

void graf::bfs(int s)
{

    queue<int> q;
    vector<bool> vizitat;
    vector<int> distanta;
    for (int i = 0; i < n; i++)
        vizitat[i] = false;
    for (int i = 0; i <= n; i++)
    {
        vizitat.push_back(0);
        distanta.push_back(-1);
    }          //populeza vectorii si ii initializeaza ca si nevizitati
    q.push(s); //adaugam in coada s-ul de start si il marcam ca vizitat si distanta 0
    vizitat[s] = true;
    distanta[s] = 0;
    while (!q.empty()) //daca avem elemente in coada, executam:
    {
        int curent = q.front(); //nodul curent devine cel mai vechi nod adaugat in coada
        q.pop();
        //parcurgem lista de adicaneta pt a gasi varfurile adiacente nevizitate ale noduliui curent
        for (auto i:muchii[curent])
        {
            if (!vizitat[i])
            {
                vizitat[i] = true;
                q.push(i);
                distanta[i] = distanta[curent] + 1;
            }
        }
    }

}

void graf::DFS(int s, vector<int> &vizitate)
{
    vizitate[s] = 1;
    for (int i : muchii[s])
    {
        if (vizitate[i] == 0)
        {
            DFS(i, vizitate);
        }
    }
}

int graf::conexe(int s)
{   vector<int>vizitate;
    int componente_conexe = 0;
    int i;
    do
    {
        vizitate.push_back(0);
        i++;

    } while (i <= n);

    for (i = 1; i < vizitate.size(); i++)
    {
        if (vizitate[i] == 0)
        {
            DFS(i, vizitate);
            componente_conexe++;
        }
    }
    return componente_conexe;
}

bool Havel_Hakimi(vector<int> &v, int n)
{
    bool stare=1;
    while (stare)
    {
        sort(v.begin(), v.end(), greater<int>());
        if (v[0] == 0)
            return true; //verificam daca primul element e 0 dupa sortare

        int a = v[0];           //salvam valoarea primului el inainte sa il stergem
        v.erase(v.begin() + 0); //stergem primul element
        if (a > v.size())
            return false; //atunci nu vom avea cum sa scadem 1 din primele a elemente ramase
        for (int i = 0; i < a; i++)
        {
            v[i]--;
            if (v[i] < 0)
                return false; //oprim executarea deoarece o valoare nu poate fi negativa in cazul in care putem avea graf
        }
    }
}
void graf::st(int a, vector<int> vizitate, stack<int>& s)
{
    vizitate[a]=1; //marcam ca vizitat primul nod
    for(int i=1;i< muchii.size()-1;i++)
        if(vizitate[a]==0)//daca gasim un nod nevizitat, aplicam sort top pe el recursiv
            st(i, vizitate, s);
    s.push(a);//punem nodul curent in stack
}
void graf::sortare_topologica(int n)
{
    stack<int> s;
    vector<int> vizitate;
    for(int i=0;i<n;i++)
        vizitate[i]=0; //marcam ca fiind nevizitate

    for(int i=0; i<n;i++)
        if(vizitate[i]==0)
            st(i,vizitate,s);
    while(s.empty()==false)
    {cout<<s.top()<<"";
    s.pop();}//afisam stiva cu rezultatul final

}
////------------------------------------------TEMA-2------------------------------------------------------------///
void graf::dijkstra(int s, vector <pair<int, int>>G[nmax])
{
    int distanta[n], nod_curent;
    bool vizitate[n];
    for(int i=1;i<=n;i++)
        {distanta[i] = INT_MAX;
        vizitate[i]=false;}

    distanta[s] = 0;
    pq.push(s);
    vizitate[s] = true;

    while(!pq.empty()){
        nod_curent=pq.top();
        vizitate[nod_curent]=false;
        pq.pop();

    for(int i = 0; i < G[nod_curent].size(); i++)
    {
        int vecin = G[nod_curent][i].first;
        int cost = G[nod_curent][i].second;

        if(distanta[nod_curent] + cost < distanta[vecin])
        {
            distanta[vecin] = distanta[nod_curent] + cost;
            if(!vizitate[vecin])
            {
                pq.push(vecin);
                vizitate[vecin] = true;
            }


        }
    }

}}
void graf::afiseaza_dijkstra(){
    for(int i = 2; i <= n; i++)
        if(distanta[i] !=INT_MAX)
            g << distanta[i] << " ";
        else
            g <<" 0 "<<" ";
}
void graf::bellman_ford (int s, vector <pair<int, int>>G[nmax]){
    queue<int>q;
    bool exista_cost_negativ = false;
    for(int i=0;i<n;i++)
        {distanta[i]=INT_MAX;
        InCoada[i]=false;
        vizitate[i]=0;}
    distanta[s]=0;
    q.push(s);
    InCoada[s] = true;
    while(q.empty() == false && exista_cost_negativ == false)
    {
        int nod_curent = q.front();
        vizitate[nod_curent]=1;
        q.pop();
        InCoada[nod_curent]=false;
        for ( size_t i = 0; i < G[nod_curent].size(); i++ )
        {
             int vecin = G[nod_curent][i].first;
             int cost = G[nod_curent][i].second;
             if(distanta[nod_curent]+cost< distanta[vecin])
             {
                 distanta[vecin]=distanta[nod_curent]+cost;
                 if(InCoada[vecin]==false)
                    q.push(vecin);
                    InCoada[vecin]=true;
             }
             vizitate[vecin]++;
             if(vizitate[i]>=n) //adica avem ciclu negativ,avand un nod care isi micsoreaza costul in continuare la mai mult de n-1 iteratii
             {
                 exista_cost_negativ=true;
                 break;
             }
        }
    }
    if (exista_cost_negativ==false){
        for(int i=1; i <=n;i++)
            g<<distanta[i]<<" ";
    }
    else g<<"Graful contine un ciclu negativ";
}
int graf:: radacina_disjuncte(int n){
    while(n!=parinte[n]){
        parinte[n]=radacina_disjuncte(parinte[n]);
        //apelam recursiv pana ajungem la radacina
    }
    return n;
}

void graf::uniune_disjuncte(int x, int y){
    if (radacina_disjuncte(x)!=radacina_disjuncte(y))
    {   if(inaltime[x]>inaltime[y])
            {parinte[radacina_disjuncte(x)]=radacina_disjuncte(y);
            inaltime[x] += inaltime[y];}
        else
            {parinte[radacina_disjuncte(y)]=radacina_disjuncte(x);
            inaltime[x] += inaltime[x];}
    }
}
bool graf::aceeasi_padure(int x, int y){
    if (radacina_disjuncte(x)==radacina_disjuncte(y))
        return true;
    return false;
}
void graf:: kruskall(){

        sort(muchii_cu_cost.begin(),muchii_cu_cost.end());
        for(auto i:muchii_cu_cost) //ne folosim de functiile de la paduri de multimi disjuncte care erau deja implementate
            if(!aceeasi_padure(i.second.first , i.second.second)) //verificam sa nu se formeze ciclu
            {   uniune_disjuncte(i.second.second,i.second.first);
                graf_ponderat.push_back(make_pair(i.second.first, i.second.second)); //adaugam in arborele de afisare
                cost_total=cost_total+i.first;  } //salvam costul
                g<<cost_total<<endl; //afisam costul arborelui

        g<<graf_ponderat.size()<<endl; //afisam nr de linii
        for(int i=0; i< graf_ponderat.size(); i++)
            g<<graf_ponderat[i].first<<" "<<graf_ponderat[i].second<<endl; //afisam capetele muchiilor din arbore doua cate doua, cum se specifica in cerinta

}

//---------------------------------------------TEMA-3-------------------------------------------------------------------------------------//
//DARB
 void graf::bfs_darb(int s, int &ultim, int &dist_max) //am modificat primul bfs ca sa poata salva elem si dist pana la el
{
    dist_max=0;
    queue<int> q;
    int vizitat[NMax];
    int distanta[NMax];
    for (int i = 0; i < n; i++)
        {vizitat[i] = false;
        distanta[i]=0;}        //populeza vectorii si ii initializeaza ca si nevizitati
    q.push(s); //adaugam in coada s-ul de start si il marcam ca vizitat si distanta 0
    vizitat[s] = true;
    distanta[s] = 1;
    while (!q.empty()) //daca avem elemente in coada, executam:
    {
        int curent = q.front(); //nodul curent devine cel mai vechi nod adaugat in coada
        q.pop();
        //parcurgem lista de adicaneta pt a gasi varfurile adiacente nevizitate ale noduliui curent
        for (auto i:adj_list[curent])
        {
            if (!vizitat[i])
            {
                vizitat[i] = true;
                q.push(i);
                distanta[i] = distanta[curent] + 1;
                if(distanta[i]>dist_max)        //atunci cand gasim dist max salvam dist si elem
                {
                    dist_max=distanta[i];
                    ultim=i;
                }
            }
        }
    }

}
void graf::darb(){
    int start_node, end_node, distanta_maxima;
    f >> n;

    int nod1, nod2;
    for(int i = 1; i <= n; ++i)
    {
        f >> nod1 >> nod2;
        adj_list[nod1].push_back(nod2);
        adj_list[nod2].push_back(nod1);
    }

    bfs_darb(1, start_node, distanta_maxima);       //bfs de la nod 1 la prim din bfs final
    bfs_darb(start_node, end_node, distanta_maxima); //bfs de la prim la ultimul nod din bfs final

    g << distanta_maxima;
}
//--------------Roy-Floyd----------------------------------//
void graf::roy_floyd(int matrice[105][105]){
    int i ,j ,k;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if ( matrice[i][j] == 0 && i != j)
                matrice[i][j]==10001;

    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if (matrice[i][k]+matrice[k][j]<matrice[i][j])
                    matrice[i][j]=matrice[i][k]+matrice[k][j];

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if ( matrice[i][j] == 10001)
                matrice[i][j]==0;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            g<<matrice[i][j]<<" ";
        g<<endl;
    }
}

void graf::royfloyd(){
    int n,i ,j;
    f>>n;
    int matrice[105][105];
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            f>>matrice[i][j];
    graf G(n);

    G.roy_floyd(matrice);
}
int main()
{
/*
//Dijkstra--------------------------------------------------DIJKSTRA
    int n,m;
    f >> n >> m;
    int start_edge, end_edge, cost;
    vector <pair<int, int>>G[nmax];
    for(int i = 0; i < m; i++)
    {
        f >> start_edge >> end_edge >> cost;
        G[start_edge].push_back(make_pair(end_edge, cost));
    }
    graf g(n,m);
    g.dijkstra(1, G);
    g.afiseaza_dijkstra();
    return 0;
//---------------Bellman-Ford
    int n,m;
    bool exista_cost_negativ;
    f>>n>>m;
    int start_edge, end_edge, cost;
    vector <pair<int, int>>G[nmax];
    vector<int>distanta;
    for(int i = 0; i < m; i++)
    {
        f >> start_edge >> end_edge >> cost;
        G[start_edge].push_back(make_pair(end_edge, cost));
    }
    graf g(n,m);
    g.bellman_ford(1, G);
    return 0;
//---Paduri disjuncte------------------------------
    int n,m, comanda,x ,y;
    f>>n>>m;
    graf g(n,m);
    vector<int>parinte;
    vector<int>inaltime;
    for ( int i = 1; i <= n; i++ )
        {parinte[i] = i;
        inaltime[i]=1;}
    for(int i=1;i<m;i++){
        f>>comanda>>x>>y;
        if (comanda==1)
            g.uniune_disjuncte( x, y);
        else if(comanda==2)
            g.aceeasi_padure( x,  y);
        return 0;
    }
//---------------------------------------KRUSKAL-----------------------------------------------------------------------//
    int n, m, start_edge, end_edge, cost;
    f>>n>>m;
    graf g(n,m);
    vector<pair<int,pair<int,int>>> muchii_cu_cost;
    vector<int>parinte;
    vector<int>inaltime;
    for(int i=1; i<=m; i++)
    {
        f >> start_edge >> end_edge >> cost;
        muchii_cu_cost.push_back(make_pair(cost,make_pair(start_edge,end_edge))); //lasam costul pe prima pozitie pt sortare
    }
    for(int i=1; i<=n; i++)
    {
        parinte[i] = i;
        inaltime[i] = 1;
    }
    g.kruskall();
    return 0;

//------------------------------------TEMA-3--------------------------------------------------------------------------//
//----DARB--//
    int n;
    graf G(n);
    G.darb();
    return 0;


//-----Roy---Floyd------//
        int n;
    graf G(n);
    G.royfloyd();
    return 0;
*/
}
