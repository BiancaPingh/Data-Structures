#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <vector>


struct hash_table {
    std::vector<std::list<std::pair<std::string, int>>> v;


   
    unsigned int predefA = 2654435769u;
    unsigned int w = 32;                 
    unsigned int l = 3;                  
    unsigned int shiftare = 32 - 3;      // w - l
    float load_factor = 0.0f;
    float max_load_factor = 1.0f;
    int nr_elem = 0, nr_buckets = 8;

    hash_table() {
        v.resize(nr_buckets);
    }

    int GetBucket(const std::string& key) {
        std::hash<std::string> hashing;
        unsigned int k = (unsigned int)hashing(key);
        unsigned int form = (predefA * k) >> shiftare;
        return form;
    }

    // load_factor > max_load_factor
    void rehash() {
        nr_buckets *= 2;
       
        l++;
        shiftare = w - l;

        std::vector<std::list<std::pair<std::string, int>>> newv(nr_buckets);

        for (auto& lista : v) {
            for (auto& p : lista) {
                int newBucket = GetBucket(p.first);
                newv[newBucket].push_back(p);
            }
        }

        v.swap(newv);

        load_factor = nr_elem * 1.0f / nr_buckets;
    }

    void insert(const std::pair<std::string, int>& p) {
        int bucket = GetBucket(p.first);
        std::list<std::pair<std::string, int>>& lista = v[bucket];

        
        for (auto& pair : lista) {
            if (pair.first == p.first) {
                return;
            }
        }

        lista.push_back(p);
        nr_elem++;

        load_factor = nr_elem * 1.0f / nr_buckets;
        if (load_factor > max_load_factor) {
            rehash();
        }
    }

 
    std::pair<std::string, int>& cautare(const std::string& key) {
        for (auto& lista : v) {
            for (auto& pair : lista) {
                if (pair.first == key) {
                    return pair;
                }
            }
        }
        static std::pair<std::string, int> not_found = { "-", -1 };
        return not_found;
    }

    void afisare() {
        for (int i = 0; i < nr_buckets; i++) {
            std::cout << "[Bucket " << i << "]: ";
            for (auto& pair : v[i]) {
                std::cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    hash_table h;

    while (true) {
        std::cout << "\n--- MENIU ---\n";
        std::cout << "1. Adauga (cheie, valoare)\n";
        std::cout << "2. Cauta cheie\n";
        std::cout << "3. Afisare tabela\n";
        std::cout << "4. Iesire\n";
        std::cout << "Alege optiunea: ";

        int opt;
        std::cin >> opt;

        switch (opt) {
        case 1: {
            std::string c;
            int v;
            std::cout << "Introduceti (cheie, valoare): ";
            std::cin >> c >> v;
            h.insert({ c, v });
            std::cout << "Pereche adaugata cu succes.\n";
            break;
        }
        case 2: {
            std::string c;
            std::cout << "Introduceti cheia de cautat: ";
            std::cin >> c;
            auto& rezultat = h.cautare(c);
            if (rezultat.second == -1) {
                std::cout << "Cheia '" << c << "' nu a fost gasita.\n";
            }
            else {
                std::cout << "Valoare asociata cheii '" << c << "': "
                    << rezultat.second << "\n";
            }
            break;
        }
        case 3:
            std::cout << "Continutul tabelei:\n";
            h.afisare();
            break;

        case 4:
            std::cout << "Iesire din program.\n";
            return 0;

        default:
            std::cout << "Optiune invalida!\n";
        }
    }


    return 0;
}