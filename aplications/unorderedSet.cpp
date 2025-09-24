#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <fstream>

//ex1

void citire(std::vector<int>& s1, std::vector<int>& s2) {
	std::ifstream file("Text.txt");
	int n, m;
	int x;
	file >> n;
	while (n) {
		file >> x;
		s1.push_back(x);
		n--;
	}
	file >> m;
	while (m) {
		file >> x;
		s2.push_back(x);
		m--;
	}
}

void intersectie(std::vector<int> s1, std::vector<int> s2) {
	std::unordered_set<int> un_set(s1.begin(),s1.end());
	for (const auto& nr : s2) {
		if (un_set.count(nr) > 0)
		{
			std::cout << nr << ", ";
		}
	}
}


int main() {
	std::vector<int> s1, s2;
	citire(s1, s2);
	intersectie(s1, s2);
	return 0;
}