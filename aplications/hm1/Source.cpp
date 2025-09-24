#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <vector>

#define PI 3,14


std::ifstream noua("ex9.txt");
std::ifstream G("ex6_1.txt");
std::ifstream C("ex6_2.txt");


void alocareMat(int**& mat, int& n, int& m) {
	noua >> n >> m;
	mat = new int* [n];
	for (int i = 0;i < n;i++) {
		mat[i] = new int[m];
	}
}

void dealocareMat(int**& mat, int n, int m) {
	for (int i = 0;i < n;i++)
		delete[] mat[i];
	delete[] mat;
}

void citireMat(int**& mat, int n, int m) {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < n;j++)
			noua >> mat[i][j];
	}
}

//ex 9
std::string ElemMaxDiagonala(int** mat, int n, int m) {
	int nord=0, sud=0, est=0, vest=0;
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			if (i < j && i + j < m - 1)
				nord += mat[i][j];
			if (i<j && i + j>m - 1)
				est += mat[i][j];
			if (j < i && i + j < n - 1)
				vest += mat[i][j];
			if (j < i && i + j < n - 1)
				sud += mat[i][j];
		}
	}
	dealocareMat(mat, n, m);
	int r = std::max({ nord, sud, est, vest });
	if (r == nord)
		return "nord";
	if (r == sud)
		return "sud";
	if (r == est)
		return "est";
	if (r == vest)
		return "vest";
}

//ex6

struct Alimente {
	int cantitate;
	std::string nume;
};

void citireListe(Alimente* &lista, int &lung) {
	int n, m;
	G >> n;
	C >> m;
	lung = n + m;
	lista = new Alimente[lung];
	std::string nm;
	int c;
	int i = 0;
	while (G >> nm) {
		G >> c;
		if (i < lung) {
			lista[i].cantitate = c;
			lista[i++].nume = nm;
		}
	}
	while (C >> nm) {
		C >> c;
		if (i < lung) {
			lista[i].cantitate = c;
			lista[i++].nume = nm;
		} 
	}
}

void schimbareLista(Alimente* &lista, int& lung) {
	Alimente *aux = new Alimente[lung];
	bool dubla =false;
	int k = 0;
	for (int i = 0;i < lung;i++) {
		for (int j = i + 1;j < lung && dubla == false;j++) {
			if (lista[i].nume == lista[j].nume) {
				lista[j].cantitate = std::max({ lista[i].cantitate,lista[j].cantitate });
				dubla = true;
			}
		}
		if (dubla == false) {
			aux[k].cantitate = lista[i].cantitate;
			aux[k++].nume = lista[i].nume;
		}
		dubla = false;
	}
	delete[] lista;
	lista = aux;
	lung = k;
}

void afisareLista(Alimente* lista, int lung) {
	std::cout <<std::endl<< "Noua lista: " << std::endl;
	for (int i = 0;i < lung;i++) {
		std::cout << "Produs: " << lista[i].nume << " : " <<lista[i].cantitate << std::endl;
	}
}


//ex3

//a)
bool AcelasiCadran(std::pair<float,float> p1, std::pair<float, float> p2) {
	if (p1.first > 0 && p2.first > 0 || p1.first < 0 && p2.first < 0) {
		if (p1.second > 0 && p2.second > 0)
			return true;
		if (p1.second < 0 && p2.second < 0)
			return true;
	}
	return false;
}

//b)
float Distanta(std::pair<float, float> p1, std::pair<float, float> p2) {
	return sqrt(pow(p2.first-p1.first,2)+ pow(p2.second - p1.second, 2));
}

//c)
float Unghiul(std::pair<float, float> p1, std::pair<float, float> p2) {
	float m = (p1.second - p2.second) / (p1.first - p2.first);
	double rezultatInRadians = atan(m);
	if (rezultatInRadians < 0) // din valori -pi/2 pana la pi/2 -> de la 0 la pi (unghiuri pozitive)
		rezultatInRadians += PI;

	//convertie in grade
	double grade = rezultatInRadians * (180.0 / PI);
	return grade; 
}

//ex4

void citireDateEx4(std::vector<float> &note) {
	float x;
	int nr;
	std::cout << "Cate medii introduci: ";
	std::cin >> nr;
	std::cout << "Mediile: ";
	for (int i = 0;i < nr;i++) {
		std::cin >> x;
		note.push_back(x);
	}
}

void statisticaMediilor(std::vector<float> note, std::vector<int> &stats) {
	stats.resize(7, 0);
	std::sort(note.begin(), note.end());
	for (int i = 0;i < note.size();i++) {
		if (note[i] < 5) 
			stats[0]++;
		else 
			stats[round(note[i]) - 4]++;
	}
}

void afisareStatisticaMedii(std::vector<int> stats) {
	std::cout << "Sunt " << stats[0] << " note sub 5"<<std::endl;
	std::cout << "Sunt " << stats[1] << " note intre " << 5 << " si " << 5.5 << std::endl;
	for (int i = 2;i < stats.size()-1;i++) {
		std::cout << "Sunt " << stats[i] << " note intre " << i + 3 + (float)1 / 2<< " si " << i + 4 + (float)1 / 2 << std::endl;
	}
	std::cout << "Sunt " << stats[stats.size()-1] << " note peste 9.50" << std::endl;
}


int main() {
	//ex9
	int** mat, n, m;
	alocareMat(mat, n, m);
	citireMat(mat, n, m);
	std::cout<<ElemMaxDiagonala(mat, n, m);
	noua.close();

	//ex6
	Alimente* lista;
	int lung;
	citireListe(lista, lung);
	schimbareLista(lista, lung);
	afisareLista(lista, lung);
	G.close();
	C.close();

	//ex3
	std::pair<float, float> p1, p2;
	p1 = { 2,-1 }, p2 = { 4,-3 };
	std::cout <<"acelasi cadran valoare de adevar: "<< AcelasiCadran(p1, p2)<<std::endl;
	std::cout << "distanta dintre cele doua puncte: " << Distanta(p1, p2)<<std::endl;
	std::cout << "unghiul dreptei fata de Ox: " << Unghiul(p1, p2)<<std::endl;

	//ex4
	std::vector<float> note;
	std::vector<int> stats;
	citireDateEx4(note);
	statisticaMediilor(note,stats);
	afisareStatisticaMedii(stats);
	return 0;
}