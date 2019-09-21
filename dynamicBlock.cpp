#include<bits/stdc++.h>
using namespace std;

#define st first
#define nd second
#define mp make_pair
#define pb push_back
#define db(x) cerr << #x << " == " << x << endl;
#define _ << " " <<

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;

int main(int argc, char *argv[]) {
   
    srand(time(NULL));
    vector<vector<ii>> cliques_vertices;
    vector<vi> Cliques;
    vector<vi> ladj;
    vector<vi> madj;
   
    int n;
    n = atoi(argv[1]);
    while(n-- > 0)
    {
        if(Cliques.size() == 0)
        {
            Cliques.pb({0});
            cliques_vertices.pb({mp(0, 0)});
            ladj.pb({});
        }
        else
        {
            int v = rand() % (Cliques.size());
            // db(v);
            if (Cliques[v].size() > 1)
            {
                // Adiciona na lista de adjacência
                ladj.pb({v});
                ladj[v].pb(Cliques.size());
               
                // cout << "Vértice separador " << endl;
                cliques_vertices.pb({mp(v, 1), mp(Cliques.size(), 0)});
                Cliques[v].pb(cliques_vertices.size() - 1);
                Cliques.pb({cliques_vertices.size() - 1});
            }
            else
            {
                int operacao = rand() % 2;
                if(operacao == 1)
                {
                    // Adiciona na lista de adjacência
                    ladj[v].pb(Cliques.size());
                    ladj.pb({v});
                   
                    // cout << "Vértice simplicial, criar nova clique" << endl;
                    if(Cliques.size() == 1)
                    {
                        cliques_vertices[0].pb(mp(Cliques.size(), 0));
                    }
                    else
                    {
                        cliques_vertices.pb({mp(v, 1), mp(Cliques.size(), 0)});
                        Cliques[v].pb(cliques_vertices.size() - 1);
                    }
                    Cliques.pb({cliques_vertices.size() - 1});
                    for(auto &vertice : cliques_vertices[Cliques[v][0]])
                    {
                        if(vertice.st == v)
                        {
                            vertice.nd = 1;
                        }
                    }
                }
                else
                {
                    // Adiciona na lista de adjacência de todos os vértices
                    ladj.pb({});
                    for(auto &vertice : cliques_vertices[Cliques[v][0]])
                    {
                        ladj[vertice.st].pb(Cliques.size());
                        ladj[ladj.size()-1].pb(vertice.st);
                    }
                   
                    // cout << "Vértice simplicial, aumentar tamanho da clique " << endl;
                    cliques_vertices[Cliques[v][0]].pb(mp(Cliques.size(), 0));
                    Cliques.pb({Cliques[v][0]});
                }
            }
        }
    }
   
    int i = 0;

    stringstream out;
    stringstream aux;
    i = 0;
    for (auto x : ladj)
    {
        stringstream ss;
        ss << i++ << ": [";
        for (auto y : x)
        {
            ss << y << ", ";
        }
        string s = ss.str().substr(0, ss.str().size() - 2);
        s += "]";
        aux << s << "\n";
    }
   
    out << aux.str().substr(0, aux.str().size() - 1) << "|";

    // inicializando a matriz de adjacência
    for(int i = 0; i < ladj.size(); i++)
    {
        vi linha;
        for(int j = 0; j < ladj.size(); j++)
        {
            linha.pb(0);
        }
        madj.pb(linha);
    }
   
    for(int i = 0; i < ladj.size(); i++)
    {
        for(int j = 0; j < ladj[i].size(); j++)
        {
            madj[i][ladj[i][j]] = 1;
        }
    }

    for (auto x : madj)
    {
        stringstream ss;
        ss << "[";
        for (auto y : x)
        {
            ss << y << ", ";
        }
        string s = ss.str().substr(0, ss.str().size() - 2);
        s += "]";
        out << s << endl;
    }
    cout << out.str();
}