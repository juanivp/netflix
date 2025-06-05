#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>


const int MAX_PELICULAS = 100;

struct Pelicula {
    char titulo[100];
    int anio;
    char pais[50];
    long reproducciones;
};

int cargarPeliculas(const char* archivoNombre, Pelicula peliculas[]) {
    std::ifstream archivo(archivoNombre);
    if (!archivo.is_open()) return 0;

    std::string linea;
    std::getline(archivo, linea); // Cabecera

    int cantidad = 0;
    while (std::getline(archivo, linea) && cantidad < MAX_PELICULAS) {
        std::istringstream ss(linea);
        std::string campo;

        std::getline(ss, campo, ',');
        strncpy(peliculas[cantidad].titulo, campo.c_str(), sizeof(peliculas[cantidad].titulo));
        
        std::getline(ss, campo, ',');
        peliculas[cantidad].anio = std::atoi(campo.c_str());

        std::getline(ss, campo, ',');
        strncpy(peliculas[cantidad].pais, campo.c_str(), sizeof(peliculas[cantidad].pais));

        std::getline(ss, campo, ',');
        peliculas[cantidad].reproducciones = std::atol(campo.c_str());

        cantidad++;
    }

    return cantidad;
}

void buscarPorTitulo(Pelicula peliculas[], int cantidad, const char* consulta) {
    bool encontrado = false;

    //TODO modificar para que encuentre ingresando solo parte del titulo

    for (int i = 0; i < cantidad; ++i) {
        if (strstr(peliculas[i].titulo, consulta)) {
            std::cout << peliculas[i].titulo << " (" << peliculas[i].anio << ", "
                      << peliculas[i].pais << ") - Reproducciones: "
                      << peliculas[i].reproducciones << "\n";
            encontrado = true;
        }
    }
    if (!encontrado) {
        std::cout << "No se encontraron coincidencias.\n";
    }
}

void ordenarPorReproducciones(Pelicula peliculas[], int cantidad) {
//ordenando de mayor a menor usando insertion sort.

    for(int i = 0; i < cantidad; i++){
       Pelicula key =  peliculas[i];
        int j = i - 1;
        while(j >= 0 && peliculas[j].reproducciones < key.reproducciones){
            peliculas[j + 1] = peliculas[j];
            j = j - 1;
        }
        peliculas[j + 1] = key;
    }
    
}

void ordenarPorTitulo(Pelicula peliculas[], int cantidad) {
    //TODO implementar ordenamiento insertion sort
     for (int i = 1; i < cantidad; i++) {
        Pelicula aux = peliculas[i];
        int j = i - 1;

                        
        while (j >= 0 && strcmp(peliculas[j].titulo, aux.titulo) > 0) {
            peliculas[j + 1] = peliculas[j];
            j--;
        }

        peliculas[j + 1] = aux;
    }
}

void mostrarPeliculas(Pelicula peliculas[], int cantidad) {
    for (int i = 0; i < cantidad; ++i) {
        std::cout << peliculas[i].titulo << " (" << peliculas[i].anio << ", "
                  << peliculas[i].pais << ") - Reproducciones: "
                  << peliculas[i].reproducciones << "\n";
    }
}

int main() {
    Pelicula peliculas[MAX_PELICULAS];
    int cantidad = cargarPeliculas("../reproducciones_netflix.csv", peliculas);

    if (cantidad == 0) {
        std::cerr << "No se pudieron cargar las películas.\n";
        return 1;
    }

    int opcion;
    do {
        std::cout << "\n--- Menu de Consultas ---\n";
        std::cout << "1 - Buscar por título\n";
        std::cout << "2 - Listar por cantidad de reproducciones (descendente)\n";
        std::cout << "3 - Listar alfabéticamente por título\n";
        std::cout << "0 - Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        std::cin.ignore();

        if (opcion == 1) {
            char consulta[100];
            std::cout << "Ingrese título a buscar: ";
            std::cin.getline(consulta, sizeof(consulta));
            buscarPorTitulo(peliculas, cantidad, consulta);
        } else if (opcion == 2) {
            ordenarPorReproducciones(peliculas, cantidad);
            mostrarPeliculas(peliculas, cantidad);
        } else if (opcion == 3) {
            ordenarPorTitulo(peliculas, cantidad);
            mostrarPeliculas(peliculas, cantidad);
        }

    } while (opcion != 0);

    return 0;
}