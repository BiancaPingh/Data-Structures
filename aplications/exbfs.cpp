#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    // Citim dimensiunea matricei
    int n;
    cout << "Introduceti dimensiunea matricei (n x n): ";
    cin >> n;

    // Initializam matricea cu valorile citite
    vector<vector<int>> matrix(n, vector<int>(n));
    cout << "Introduceti elementele matricei:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    // Matricea pentru marcarea pozitiilor vizitate
    vector<vector<bool>> visited(n, vector<bool>(n, false));

    // Matricea pentru numararea pasilor pana la fiecare pozitie
    vector<vector<int>> steps(n, vector<int>(n, 0));

    // Coada pentru BFS - stocheaza perechi de coordonate (row, col)
    queue<pair<int, int>> q;

    // Pozitia de start (0,0)
    q.push({ 0, 0 });
    visited[0][0] = true;

    // Directiile posibile de miscare: jos, sus, dreapta, stanga
    const int dr[] = { 1, -1, 0, 0 };
    const int dc[] = { 0, 0, 1, -1 };

    // BFS
    while (!q.empty()) {
        // Extragem pozitia curenta
        int currentRow = q.front().first;
        int currentCol = q.front().second;
        q.pop();

        // Valoarea din pozitia curenta (cat putem "sari")
        int jumpValue = matrix[currentRow][currentCol];

        // Incercam toate directiile posibile
        for (int dir = 0; dir < 4; dir++) {
            // Calculam noua pozitie
            int newRow = currentRow + jumpValue * dr[dir];
            int newCol = currentCol + jumpValue * dc[dir];

            // Verificam daca noua pozitie este valida
            bool isInBounds = newRow >= 0 && newRow < n &&
                newCol >= 0 && newCol < n;

            if (isInBounds && !visited[newRow][newCol]) {
                // Marcam pozitia ca vizitata
                visited[newRow][newCol] = true;

                // Actualizam numarul de pasi
                steps[newRow][newCol] = steps[currentRow][currentCol] + 1;

                // Adaugam noua pozitie in coada
                q.push({ newRow, newCol });
            }
        }
    }

    // Verificam daca am ajuns la destinatie (coltul dreapta-jos)
    if (visited[n - 1][n - 1]) {
        cout << "\nNumarul minim de mutari necesare: " << steps[n - 1][n - 1] << "\n";

        // Optional: afisam matricea cu numarul de pasi
        cout << "\nMatricea cu numarul de pasi pentru fiecare pozitie:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (visited[i][j])
                    cout << steps[i][j] << "\t";
                else
                    cout << "X\t";
            }
            cout << "\n";
        }
    }
    else {
        cout << "\nNu exista solutie! Nu se poate ajunge la destinatie.\n";
    }

    return 0;
}