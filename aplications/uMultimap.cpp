#include <iostream>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <fstream>

using concurent = std::tuple < std::string, std::string, int >;

struct custom_hash {
	std::size_t operator()(const concurent& c) const {
		std::hash<std::string> h;
		std::hash<int> h_int;
		std::size_t h_nume = h(std::get<0>(c));
		std::size_t h_prenume = h(std::get<1>(c));
		std::size_t h_varsta = h_int(std::get<2>(c));
		//return h_nume ^ h_prenume ^ h_varsta; // met 1 - xor intre ele

		std::size_t res = 17;
		res = res * 33 + h_nume;
		res = res * 33 + h_prenume;
		res = res * 33 + h_varsta;
		return res; //met 2 - ecuatie polinomiala (hash polinomial)
	}
};


void citire(std::unordered_map<concurent,std::vector<std::string>,custom_hash>& tab) {
	std::ifstream file("comp.txt");
	int nr_comp,nr_pers;
	std::string nume, prenume,comp;
	int varsta;
	file >> nr_comp;
	for (int i = 0;i < nr_comp;i++) {
		file >> comp >> nr_pers;
		for (int j = 0;j < nr_pers;j++){
			file >> nume >> prenume >> varsta;
			tab[{nume, prenume, varsta}].push_back(comp);
		}
	}
}
void citireMutimap(std::unordered_multimap<concurent, std::string, custom_hash>& tab) {
	std::ifstream file("comp.txt");
	int nr_comp, nr_pers;
	std::string nume, prenume, comp;
	int varsta;
	file >> nr_comp;
	for (int i = 0;i < nr_comp;i++) {
		file >> comp >> nr_pers;
		for (int j = 0;j < nr_pers;j++) {
			file >> nume >> prenume >> varsta;
			tab.insert({ { nume,prenume,varsta }, comp });
		}
	}
}

void afisareTabela(std::unordered_map<concurent, std::vector<std::string>, custom_hash> tab) {
	
	for (const auto& info : tab) {
		std::cout << std::get<0>(info.first) << " " << std::get<1>(info.first) << " " << std::get<2>(info.first)<<" : ";
		for (const auto& comp : info.second) {
			std::cout << comp<<" ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}


void afisareTabelaMultimap(std::unordered_multimap<concurent, std::string, custom_hash> tab) {

	/*for (const auto& info : tab) {
		std::cout << std::get<0>(info.first) << " " << std::get<1>(info.first) << " " << std::get<2>(info.first) << " : ";
		std::cout << info.second;
		std::cout << std::endl;
	}
	std::cout << std::endl;*/

	for (auto it = tab.begin();it != tab.end();) {
		auto range = tab.equal_range(it->first);
		std::cout<< std::get<0>(it->first) << " " << std::get<1>(it->first) << " " << std::get<2>(it->first) << " : ";
		for (auto it2 = range.first; it2 != range.second;it2++) {
			std::cout << it->second<<" ";
			it++;
		}
		std::cout << std::endl;
	}
}


int main() {
	std::unordered_map<concurent, std::vector<std::string>,custom_hash> tab;
	citire(tab);
	afisareTabela(tab);
	std::unordered_multimap<concurent, std::string, custom_hash> tab2;
	citireMutimap(tab2);
	afisareTabelaMultimap(tab2);
	return 0;
}