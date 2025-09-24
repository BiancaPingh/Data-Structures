#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <ctype.h>

void citireEc(std::string& ec) {
	std::ifstream file("ecuatie.txt");
	file >> ec;
}

int prioritate(char ch) {
	if (ch == '(')
		return -1; 
	if (ch == '*' || ch == '/' || ch == '^')
		return 2;
	return 1;
}

void formaPoloneza(std::vector<char>& pol, std::string ec) {
	std::stack<char> op_stack;
	for (auto ch : ec) {
		if (isdigit(ch)) {
			pol.push_back(ch);
		}
		else if (ch == '(') {
			op_stack.push(ch);
		}
		else if (ch == ')') {
			while (!op_stack.empty() && op_stack.top() != '(') {
				pol.push_back(' ');
				pol.push_back(op_stack.top());
				op_stack.pop();
			}
			if (!op_stack.empty())
				op_stack.pop(); //scoatem paranteza
			else if (op_stack.empty())
			{
				std::cout << "Eroare la paranteze";
				exit(1);
			}
		}
		else { 
			pol.push_back(' ');
			while (!op_stack.empty() && prioritate(op_stack.top()) >= prioritate(ch)) {
				pol.push_back(op_stack.top());
				pol.push_back(' ');
				op_stack.pop();
			}
			op_stack.push(ch);

		}
	}
	while (!op_stack.empty() && op_stack.top()!='(') {
		pol.push_back(' ');
		pol.push_back(op_stack.top());
		op_stack.pop();
	}
	if (!op_stack.empty()&&op_stack.top() == '(') {
		std::cout << "Eroare la paranteze";
		exit(1);
	}
}
void afisareEcuatiePol(std::vector<char> pol) {
	for (int i = 0; i < pol.size();i++) {
		std::cout << pol[i];
	}
	std::cout << '\n';
}

bool op_valid(char ch) {
	if (ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == '^')
		return true;
	return false;
}

int calcul(char ch, int a, int b) {
	if (ch == '+')
		return a + b;
	if (ch == '-')
		return a - b;
	if (ch == '/')
		return a / b;
	if (ch == '*')
		return a * b;
	if (ch == '^') {
		while (b) {
			a *= a;
			b--;
		}
		return a;
	}
		
}

int RaspunsEcuatie(std::vector<char> pol) {
	std::stack<int> numere;
	int nrIntermediar=0;
	for (int i = 0; i < pol.size();i++) {
		if (isdigit(pol[i])) {
			nrIntermediar = nrIntermediar * 10 + pol[i]-'0';
			if (pol[i + 1] == ' ') {
				numere.push(nrIntermediar);
				nrIntermediar = 0;
			}
		}
		else if (op_valid(pol[i])) {
			int a = numere.top();
			numere.pop();
			int b = numere.top();
			numere.pop();
			numere.push(calcul(pol[i], b, a));
		}
	}
	return numere.top();
}

bool formaCorecta(std::vector<char> pol) {
	int operanzi=0, operatori=0;
	for (int i = 0;i<pol.size();i++) {
		if (op_valid(pol[i]))
		{
			operatori++;
		}
		else if (isdigit(pol[i]))
		{
			if (pol[i + 1] == ' ')
				operanzi++;
		}
		else if (pol[i] == ' ') {
			continue;
		}
		else {
			std::cout <<"Operator invalid \n";
			return false;
		}
	}
	if (operanzi == operatori+1)
		return true;
	std::cout << "Numar de operatori invalid \n";
	return false;
}

void main() {
	std::string ec;
	std::vector<char> pol;
	citireEc(ec);
	std::cout << ec << '\n';
	formaPoloneza(pol,ec);
	afisareEcuatiePol(pol);
	std::cout<<"Raspunsul este "<<RaspunsEcuatie(pol)<<std::endl;
	if (formaCorecta(pol))
		std::cout << "Forma este corecta";
}