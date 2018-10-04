#include <bits/stdc++.h>
using namespace std;
map<string,vector<int>> Fctrs; //feactures
map<int,std::vector<pair<int,int>>> Transitions;
std::vector<std::vector<int>> Solution;
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
vector<int> mover(vector<int> v,int entrada){
	std::vector<int> ans;
	for (int i = 0; i < v.size(); i++) {
		for(auto j:Transitions){
			if (j.first==v[i]) {
				for (auto k:j.second) {
					if (k.second==entrada) {
						// std::cout << " vec push "<<k.first << '\n';
						ans.push_back(k.first);
					}
				}
			}
		}
	}
	return ans;
}
vector<int> mover(int v,int entrada){
	std::vector<int> ans;
		for(auto j:Transitions){
			if (j.first==v) {
				for (auto k:j.second) {
					if (k.second==entrada) {
						// std::cout << "est push "<<k.first << '\n';
						ans.push_back(k.first);
					}
				}
			}
		}
	return ans;
}
vector<int> e_clausuere(vector<int> v) {
	stack<int> pila;
	std::vector<int> ans=v;
	std::vector<int> mtemp=mover(v,-1);
	ans.insert(ans.end(),mtemp.begin(),mtemp.end());
	for(auto i:ans){
		pila.push(i);
	}
	while (!pila.empty()) {
		int ts=pila.top();
		pila.pop();
		std::vector<int> temp=mover(ts,-1);
		std::vector<int> next=mover(temp,-1);
		temp.insert(temp.end(),next.begin(),next.end());
		for(auto i:temp){
			if (find(ans.begin(),ans.end(),i)==ans.end()) {
				pila.push(i);
				ans.push_back(i);
			}
		}
	}
		return ans;
}
void SubSetContructions(){
	set<vector<int>> comparator;
	int current =0; // index del orden de las soluciones
	std::vector<int> in={Fctrs["Estados"][0]};
	Solution.push_back(e_clausuere(in));
	comparator.insert(Solution[0]);
	while (current<Solution.size()) {
		// std::cout << "\t"<<current<<'\t'<<Solution.size() << '\n';
			for (auto i:Fctrs["Entradas"]) {
				// std::ccout << "entrada " <<i <<'\n';
				std::vector<int> m=mover(Solution[current],i);
				// for(auto j: m)
				// std::cout << " "<<j ;
				// std::cout  << '\n';
				std::vector<int> ec=e_clausuere(m);
				int antes=comparator.size();
				comparator.insert(ec);
				int despues=comparator.size();
				if (!ec.empty()) {
					if (antes==despues) {
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
						ans_trans.push_back(make_tuple(current,i,Solution.size()-1));
					}
				}
			}
		current++;
	}
}
int main(int a, char* b[]){
	if(a!=2){		cout<<"error"<<endl;return 0;}
	else{inputext(b[1]);
		// print_Fctrs();
	}

	SubSetContructions();
	std::cout << "Estados" << '\n';
	set<set<int>> conjunto;
	int contar = 0;
	for(auto i:Solution){
		std::cout <<contar <<" = {";
		sort(i.begin(),i.end());
		for(auto j:i)
		std::cout << j<<" ";
		std::cout  <<"}"<< '\n';
		contar++;
	}
  std::cout << "Trancisiones(x,y,z)" << '\n';
  for(auto i:ans_trans){
    std::cout << " "<<get<0>(i)<<" "<<get<1>(i)<<" "<<get<2>(i)<< '\n';
  }
	// std::cout << "/* message */" << '\n';
	// for(auto j:Transitions){
	// 	for (auto k:j.second) {
	// 		std::cout << j.first<<" "<<k.first<<" "<<k.second << '\n';
	// 	}
	// }

return 0;
}
