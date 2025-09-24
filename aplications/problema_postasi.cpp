#include <iostream>
#include <queue>
#include <fstream>
#include <math.h>
#define X 5
#define Y 7

double dist(std::pair<int, int> cd) {
	return sqrt(pow(cd.first - X, 2) + pow(cd.second - Y, 2));

}

struct pachet
{
	std::pair<int, int> coord;
	std::string cod;
	int g;
	double distanta = dist(coord);
	bool operator<(const pachet& p) const{
		return dist(coord) < dist(p.coord);
	}
};

void citire(std::string fis, std::priority_queue<pachet> &pq) {
	std::ifstream file(fis);
	std::string cod;
	int x,y,g;
	while (file >> cod >> x >> y >> g) {
		pq.push({ { x,y }, cod, g });
	}
}

void verificare(std::priority_queue<pachet>& pq, std::vector<std::pair<std::string, int>> factori, int i, std::vector<std::string> &vect) {
	int n = pq.top().g;
	double m = pq.top().distanta;
	std::queue<pachet> pq_sarite;
	while (n > 10 || m > factori[i].second) {
		pq_sarite.push(pq.top());
		pq.pop();
		n = pq.top().g;
		m = pq.top().distanta;
	}
	while (n < 10 && !pq.empty()) {
		vect.push_back(pq.top().cod);
		pq.pop();
		n += pq.top().g;
		m = pq.top().distanta;
	}
	while (!pq_sarite.empty()) {
		pq.push(pq_sarite.front());
		pq_sarite.pop();
	}
}
void afisare(std::vector<std::string> v) {
	for (auto cod : v) {
		std::cout << cod << " ";
	}
	std::cout << std::endl;
}
void livrare(std::priority_queue<pachet>& pq, std::vector<std::pair<std::string, int>> factori) {
	std::vector<std::string> ion, andr, mih;
	int n;
	double m;
	for (int i = 0; i < 3;i++) {
		//Ion
		verificare(pq, factori, 0, ion);
		//Andreea
		verificare(pq, factori, 1, andr);
		//Mihai 
		verificare(pq, factori, 2, mih); 
	}
	afisare(ion);
	afisare(andr); 
	afisare(mih);
}



int main() {
	std::priority_queue<pachet> pq;
	std::vector<std::pair<std::string, int>> factori = { {"Ion",INT_MAX}, {"Andreea",10}, {"Mihai",5} };
	citire("pachete.txt", pq);
	livrare(pq,factori);
	return 0;
}