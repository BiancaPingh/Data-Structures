#include <iostream>
#include <queue>
#include <string>
#include <ctime>

struct Task {
	std::string nume;
	int durata, prioritate;
	Task() {};
	Task(std::string nume, int durata, int prioritate) : nume(nume), durata(durata), prioritate(prioritate) {};
	bool operator<(const Task &other) const {
		if (prioritate == other.prioritate)
			return durata < other.durata;
		return prioritate < other.prioritate;
	}
	void afisare() {
		std::cout << nume << " " << durata << " " << prioritate<<std::endl;
	}
};

void generare(std::priority_queue<Task>& pq, std::vector<std::string> s) {
	Task sarcina;
	std::string nume_sarcina = s[rand() %
		s.size()];
	int durata = rand() % 8 + 1;
	int prioritate = rand() % 3;
	sarcina = { nume_sarcina, durata, prioritate };
	pq.push(sarcina);
}

void sarcini(std::priority_queue<Task> &pq) {
	std::vector<std::string> s = { "comanda_noua", "rezolva_corespondenta", "livreaza_intern", "livreaza_extern", "calculeaza_plati"};
	//generare random de task
	Task sarcina;
	for(int i=0;i<4;i++) {
		generare(pq,s);
	}
	for (int i = 0;i < 10;i++) {
		sarcina = pq.top();
		pq.pop();
		sarcina.afisare();
		generare(pq, s);
	}
	
}

int main() {
	std::priority_queue<Task> pq;
	sarcini(pq);
	return 0;
}