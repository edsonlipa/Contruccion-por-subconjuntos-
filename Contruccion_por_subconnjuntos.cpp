#include<bits/stdc++.h>
using namespace std;
map<string,vector<int>> Fctrs; //feactures
map<int,std::vector<pair<int,int>>> Transitions;
std::vector<std::set<int>> Solution;
std::vector<tuple<int,int,int>> ans_trans;
void inputext(string filename){
	ifstream file(filename);
	string name;
	while(file>>name){
		int n,e,f,t;

		if (name=="Trancisiones(x,y,z)_epsilon=-1")
		{
			file>>n;
			for(int i=0; i<n ; i++){
				file>>f>>e>>t;
				Transitions[f].push_back(make_pair(t,e));
			}
		}else{
			file>>n;
			for(int i=0; i<n ; i++){
				file>>e;
				Fctrs[name].push_back(e);
			}
		}
	}
}
void print_Fctrs(){
	for (auto i:Fctrs){
		cout<< get<0>(i)<<endl;
		for(auto j:i.second)
			std::cout << j << '\n';
	}
}
void mover(set<int> v,int entrada,set<int> &ans){
  for(auto i:v){
    for(auto j:Transitions){
      if (j.first==i) {
        for (auto k:j.second) {
          if (k.second==entrada) {
            ans.insert(k.first);
          }
        }
      }
    }
  }
}
void mover(int v,int entrada,set<int> &ans){
		for(auto j:Transitions){
			if (j.first==v) {
				for (auto k:j.second) {
					if (k.second==entrada) {
						ans.insert(k.first);
					}
				}
			}
		}
}
set<int> e_clausuere(set<int> v) {
	stack<int> pila;
	set<int> ans=v;
	mover(v,-1,ans);
	for(auto i:ans){
		pila.push(i);
	}
	while (!pila.empty()) {
		int ts=pila.top();
		pila.pop();
		std::set<int> temp;
    mover(ts,-1,temp);
    mover(temp,-1,temp);
		for(auto i:temp){
			if (find(ans.begin(),ans.end(),i)==ans.end()) {
				pila.push(i);
				ans.insert(i);
			}
		}
	}
		return ans;
}
void SubSetContructions(){
	set<vector<int>> comparator;
	int current =0; // index del orden de las soluciones
	set<int> in={Fctrs["Estados"][0]};
	Solution.push_back(e_clausuere(in));
  while (current<Solution.size()) {
		// std::cout << "\t"<<current<<'\t'<<Solution.size() << '\n';
			for (auto i:Fctrs["Entradas"]) {
				// std::cout << "entrada " <<i <<'\n';
				set<int> m;
        mover(Solution[current],i,m);
				set<int> ec=e_clausuere(m);

        if (!ec.empty()) {
          int antes=Solution.size();
          if (find(Solution.begin(),Solution.end(),ec)!=Solution.end()) {
						for (size_t l = 0; l < Solution.size(); l++) {
							if (ec==Solution[l]) {
								ans_trans.push_back(make_tuple(current,i,l));
							}
						}
					}else{
						// for(auto j: ec)
						// std::cout << " "<<j ;
						// std::cout  << '\n';

						Solution.push_back(ec);
            for(auto ea:Fctrs["Estados_de_aceptacion"]){
              if (find(ec.begin(),ec.end(),ea)!=ec.end()) {

                Fctrs["Nueva_stados_de_aceptacion"].push_back(Solution.size()-1);
              }
            }
						ans_trans.push_back(make_tuple(current,i,Solution.size()-1));
					}
				}
			}
		current++;
	}
}
void write_file(string filename){
	ofstream out_file(filename);
	int contar = 0;
	out_file << "Estados" << '\n';
	for(auto i:Solution){
		out_file <<contar <<" = {";
		for(auto j:i)
		out_file << j<<" ";
		out_file  <<"}"<< '\n';
		contar++;
	}

	out_file << "Estados_de_aceptacion" << '\n';
	for(auto j: Fctrs["Nueva_stados_de_aceptacion"])
	out_file << " "<<j ;
	out_file  << '\n';
	out_file << "Trancisiones(x,y,z)" << '\n';
  for(auto i:ans_trans){
    out_file << " "<<get<0>(i)<<" "<<get<1>(i)<<" "<<get<2>(i)<< '\n';
  }
}
int main(int argc, char const *argv[]) {
  if(argc!=2){		cout<<"error"<<endl;return 0;}
  else{inputext(argv[1]);
    // print_Fctrs();
  }
  SubSetContructions();
	write_file("salida.out");
	return 0;
}
