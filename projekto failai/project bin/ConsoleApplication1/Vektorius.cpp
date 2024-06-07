#include "Vektorius.h"
#include <iostream>
#include <utility> // for std::pair
#include <vector> // palyginimui
#include <chrono> // laiko matavimui

void VectorExample()
{
    // Create a vector containing integers
    Vector<int> v = { 8, 4, 5, 9 };
    // Add two more integers to vector
    v.push_back(6);
    v.push_back(9);
    // Overwrite element at position 2
    v[2] = -1;
    std::cout << "Is vektoriaus tikimasi skaiciu: 8 4 -1 9 6 9" << std::endl;
    // Print out the vector
    for (int n : v)
        std::cout << n << ' ';
    std::cout << '\n';
}

int sumVector(const Vector<int>& vec) {
    int sum = 0;
    for (int elem : vec) {
        sum += elem;
    }
    return sum;
}

bool isSorted(const Vector<int>& vec) {
    return std::is_sorted(vec.begin(), vec.end());
}

void removeDuplicates(Vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
    vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
}

Vector<int> mergeSortedVectors(const Vector<int>& vec1, const Vector<int>& vec2) {
    Vector<int> merged(vec1.size() + vec2.size());
    std::merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), merged.begin());
    return merged;
}

std::pair<int, int> findMaxElement(const Vector<int>& vec) {
    if (vec.empty())
        return { -1, -1 }; // Indicate empty vector
    int maxIndex = 0;
    int maxValue = vec[0];
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] > maxValue) {
            maxIndex = i;
            maxValue = vec[i];
        }
    }
    return { maxIndex, maxValue };
}
void VectorUzpildymas()
{
    unsigned int sz = 10000;  // 100000, 1000000, 10000000, 100000000
    std::vector<int> v1;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
        v1.push_back(i);
    auto end = std::chrono::high_resolution_clock::now();
    double trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v1 (std::vector) uzpildymas uztruko: " << trukme << " s\n";
    Vector<int> v2;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
        v2.push_back(i);
    end = std::chrono::high_resolution_clock::now();
    trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v2 (Vector) uzpildymas uztruko: " << trukme << " s\n";
    sz = 100000;
    std::vector<int> v3;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
		v3.push_back(i);
	end = std::chrono::high_resolution_clock::now();
    trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v3 (std::vector) uzpildymas uztruko: " << trukme << " s\n";
    Vector<int> v4;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
		v4.push_back(i);
    end = std::chrono::high_resolution_clock::now();
    trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v4 (Vector) uzpildymas uztruko: " << trukme << " s\n";
    sz = 1000000;
    std::vector<int> v5;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
        v5.push_back(i);
    end = std::chrono::high_resolution_clock::now();
    trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v5 (std::vector) uzpildymas uztruko: " << trukme << " s\n";
    Vector<int> v6;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
		v6.push_back(i);
	end = std::chrono::high_resolution_clock::now();
    trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v6 (Vector) uzpildymas uztruko: " << trukme << " s\n";
    sz = 10000000;
    std::vector<int> v7;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
		v7.push_back(i);
    end = std::chrono::high_resolution_clock::now();
    trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v7 (std::vector) uzpildymas uztruko: " << trukme << " s\n";
    Vector<int> v8;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
        v8.push_back(i);
    end = std::chrono::high_resolution_clock::now();
    trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v8 (Vector) uzpildymas uztruko: " << trukme << " s\n";
    sz = 100000000;
    std::vector<int> v9;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
        v9.push_back(i);
    end = std::chrono::high_resolution_clock::now();
    trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v9 (std::vector) uzpildymas uztruko: " << trukme << " s\n";
    Vector<int> v10;
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= sz; ++i)
		v10.push_back(i);
    end = std::chrono::high_resolution_clock::now();
    trukme = std::chrono::duration<double>(end - start).count();
    std::cout << "Vektoriaus v10 (Vector) uzpildymas uztruko: " << trukme << " s\n";
    std::cout << std::endl;
    std::cout << "Uzpildymo perskirstymu skaiciu palyginimas tarp std::vector ir Vector klases" << std::endl;
    //--------------------------------------------------------------------------------
    // Uzpildymo perskirstymu skaiciu palyginimas tarp std::vector ir Vector klases
    // std::vector
    std::vector<int> v91;
    int perskirstymuskaicius = 0;
    for (int i = 1; i <= sz; ++i) {
        v91.push_back(i);
        if (v9.capacity() == v91.size()) {
            std::cout << "std::vector perskirstytas i dydi: " << v91.size() << std::endl;
            perskirstymuskaicius +=1;
        }
    }
    std::cout << "std::vector perskirstymu skaicius: " << perskirstymuskaicius << std::endl;
    perskirstymuskaicius = 0;
    // Vector
    Vector<int> v101;
    for (int i = 1; i <= sz; ++i) {
        v101.push_back(i);
        if (v101.capacity() == v101.size()) {
            std::cout << "Vector perskirstytas i dydi: " << v101.size() << std::endl;
            perskirstymuskaicius +=1;
        }
    }
    std::cout << "Vector perskirstymu skaicius: " << perskirstymuskaicius << std::endl;
}


