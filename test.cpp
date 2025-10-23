#include <iostream>
#include <ctime> // pour clock()

int main() {
    // Temps de départ
    clock_t start = std::clock();

    // Exemple : une tâche un peu longue
    for (volatile int i = 0; i < 100000000; ++i);

    // Temps de fin
    clock_t end = std::clock();

    // Différence en secondes
    double duration = double(end - start) / CLOCKS_PER_SEC;

    std::cout << "Durée écoulée : " << duration << " secondes" << std::endl;
    return 0;
}
