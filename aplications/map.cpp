#include <iostream>
#include <map>
#include <vector>
#include <fstream>

void citire(std::map<float, std::vector<std::string>> &map, std::string filename) {
	std::ifstream file(filename);
	std::string nume;
	float val;
	while (file >> nume >> val) {
		map[val].push_back(nume);
	}
}
void afisareDupaPret(std::map<float, std::vector<std::string>>& map, float p) {
	std::vector<std::string> names = map[p];
	for (int i = 0;i < names.size();i++) {
		std::cout << names[i] << " ";
	}
	std::cout << std::endl;
}
void dupaInterval(std::map<float, std::vector<std::string>>& map, float p, float p2) { //doar daca stim sigur ca gasim p si p2
	auto first = map.find(p), second = map.find(p2);
	auto it=first;
	for (it = first;it != second;it++) {
		for (int i = 0; i < it->second.size();i++) {
			std::cout << it->second[i]<<" ";
		}
	}
	for (int i = 0; i < it->second.size();i++) {
		std::cout << it->second[i] << " ";
	}
	std::cout << std::endl;
}
void dupaInterval2(std::map<float, std::vector<std::string>>& map, float p, float p2) { 
	auto first = map.lower_bound(p), second = map.upper_bound(p2);
	auto it = first;
	for (it = first;it != second;it++) {
		for (int i = 0; i < it->second.size();i++) {
			std::cout << it->second[i] << " ";
		}
	}
	/*for (int i = 0; i < it->second.size();i++) {  // aici upper_bound e strict mai mare
		std::cout << it->second[i] << " ";
	}*/
}

//set
struct complex {
	int re, im;
	complex(int a = 0, int b = 0) : re(a), im(b) {}
	double modul() const
	{
		return sqrt(re * re + im * im);
	}
	void print() const
	{
		std::cout << re << " + ";
		if (im < 0)
			std::cout << "(" << im << ")i";
		else if (im > 0)
			std::cout << im << "i";
	}
};

class compare {
public:
	bool operator () (const complex& z1, const complex& z2)
		const
	{
		return z1.modul() < z2.modul();
	}
};


int main() {
	std::map<float, std::vector<std::string>> map;
	citire(map, "map.txt");
	afisareDupaPret(map, 43);
	dupaInterval(map, 22, 36);
	dupaInterval2(map, 23, 36);
	return 0;
}