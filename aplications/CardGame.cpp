#include <iostream> 
#include <string>
#include <stack>
#include <fstream>
#include <string>
#include <deque>
#include <vector>


int changeNr(std::string nr) {
	if (nr == "V")
		return 11;
	if (nr == "Q")
		return 12;
	if (nr == "K")
		return 13;
	if (nr == "A")
		return 14;
	return std::stoi(nr);
}

void citireFisier(std::string file, std::stack<std::pair<int,std::string>>& teancCarti) {
	std::ifstream f(file);
	std::string nr, culoare;
	while (f >> nr >> culoare) {
		int numar = changeNr(nr);
		teancCarti.push({ numar,culoare });
	}
}


std::pair<int, int> verificareCastigator(std::vector< std::deque<std::pair<int, std::string>>> manaJucator) {
	int suma,maxSum = INT_MIN;
	std::pair<int, int> raspuns;
	for (int i = 0;i < manaJucator.size();i++) {
		suma = 0;
		while (!manaJucator[i].empty()) {
			suma += manaJucator[i].front().first;
			manaJucator[i].pop_front();
		}
		if (suma > maxSum) {
			raspuns.first = suma;
			maxSum = suma;
			raspuns.second = i;
		}
	}
	return raspuns;
}

void afisareCastigator(int suma, std::deque<std::pair<int, std::string>> manaJucator) {
	std::cout << "Suma castigatorului este: " << suma << "\n";
	while (!manaJucator.empty()) {
		std::cout<< manaJucator.front().first << " "<< manaJucator.front().second<< "\n";
		manaJucator.pop_front();
	}
}

void Joc(int nr_players, int nr_runde, std::stack<std::pair<int, std::string>>& teancCarti) {
	std::stack<std::pair<int, std::string>> decartat;
	std::vector< std::deque<std::pair<int, std::string>>> manaJucator;

	int nr, nr2; std::string culoare, culoare2;

	int copie_nr_players = nr_players;

	while (nr_players) { //impartire carti
		nr = teancCarti.top().first; //carte 1
		culoare = teancCarti.top().second;
		teancCarti.pop();

		nr2 = teancCarti.top().first; //carye 2
		culoare2 = teancCarti.top().second;
		teancCarti.pop();

		std::deque<std::pair<int, std::string>> carti;
		if (nr > nr2) {
			std::swap(nr, nr2);
			std::swap(culoare, culoare2);

		}
		carti.push_back({ nr,culoare });
		carti.push_back({ nr2,culoare2 });
		manaJucator.push_back(carti);
		nr_players--;
	}

	int i = 0;

	
	while (nr_runde && (!teancCarti.empty() || !decartat.empty())) { //daca mai are de unde sa ia carti sa continue

		if (teancCarti.empty() || (!teancCarti.empty() && !decartat.empty() && decartat.top().first > manaJucator[i].back().first)) { // doar daca e mai mare deacat ce are el deja
			nr = decartat.top().first;
			culoare = decartat.top().second;
			decartat.pop();
		}
		else {
			nr = teancCarti.top().first;
			culoare = teancCarti.top().second;
			teancCarti.pop();
		}
		if (manaJucator[i].back().first < nr) { // la dreapta
			manaJucator[i].push_back({ nr,culoare });
		}
		else if (manaJucator[i].front().first > nr) { // la stanga
			manaJucator[i].push_front({ nr,culoare });
		}
		else { // nu a mers la niciuna
			decartat.push({ nr,culoare });
		}

		if (i == copie_nr_players-1) { // trece prin toti jucatorii
			i = 0;
		}
		else
			i++;
		nr_runde--;
	}
	std::pair<int, int> raspuns = verificareCastigator(manaJucator);
	afisareCastigator(raspuns.first, manaJucator[raspuns.second]);

}


int main() {
	std::stack < std::pair<int, std::string>> st;
	citireFisier("fisierInput.txt", st);
	int nr_players = 2, nr_runde;
	std::cin >> nr_runde;
	Joc(nr_players,nr_runde,st);
	return 0;
}