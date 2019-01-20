#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Disjoint_Set{
    vector<int> parent;
    vector<int> ranks;
    Disjoint_Set(int _size){
        for(int i = 0; i <= _size; i++){
            parent.push_back(i);
            ranks.push_back(1);
        }
    }

    int parent_of(int x){
        int curr = x;
        while(curr != parent[curr]){
            curr = parent[curr];
            parent[curr] = parent[parent[curr]];
        }
        return curr;
    }

   bool join(int a, int b){
        int parent_a = parent_of(a);
        int parent_b = parent_of(b);
        if(parent_a == parent_b)
            return true;
        if(ranks[parent_a] < ranks[parent_b]){
            parent[parent_a] = parent_b;
            ranks[parent_b] += ranks[parent_a];
        }else{
            parent[parent_b] = parent_a;
            ranks[parent_a] += ranks[parent_b];
        }
        return false;
    }

    bool same_parent(int a, int b){
        return parent_of(a) == parent_of(b);
    }
};

struct edge{
	int from, to, cost;
	edge(int _from, int _to, int _cost){
		from = _from;
		to = _to;
		cost = _cost;
	}
};

int n;
vector<edge> edgelist;
vector<edge> result;

void mst(){
    sort(edgelist.begin(), edgelist.end(), [](edge &a, edge &b){
        return a.cost < b.cost;
    });
    int edges = 0;
    Disjoint_Set uf = Disjoint_Set(n);
    for(int i = 0; i < edgelist.size() && edges < n; i++)
        if(!uf.join(edgelist[i].from, edgelist[i].to)){
            edges++;
            result.push_back(edgelist[i]);
        }
    return;
}


int main(){

	int x;
	cin >> n;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			cin >> x;
			if(x > 0)
				edgelist.push_back(edge(i, j, x));
		}
	}

	mst();

	for(int i = 0; i < result.size(); i++)
		cout << result[i].from << ' ' << result[i].to<< endl;

}