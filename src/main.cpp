#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>

using namespace std;

// ==========================
// Estructura del Producto
// ==========================
struct Producto {
    int id;
    string nombre;
    double precio;
    string categoria;
    int stock;
    double calificacion;
};

// ==========================
// QuickSort por precio
// ==========================
void quickSortPrecio(vector<Producto>& arr, int low, int high) {
    if (low < high) {
        double pivot = arr[high].precio;
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr[j].precio < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);
        int pi = i + 1;

        quickSortPrecio(arr, low, pi - 1);
        quickSortPrecio(arr, pi + 1, high);
    }
}

// ==========================
// Búsqueda binaria por ID
// ==========================
int busquedaBinaria(const vector<Producto>& arr, int objetivo) {
    int izquierda = 0;
    int derecha = arr.size() - 1;

    while (izquierda <= derecha) {
        int medio = (izquierda + derecha) / 2;

        if (arr[medio].id == objetivo)
            return medio;

        if (arr[medio].id < objetivo)
            izquierda = medio + 1;
        else
            derecha = medio - 1;
    }

    return -1;
}

// ==========================
// Main
// ==========================
int main() {
    vector<Producto> productos;

    string nombres[] = {"Laptop", "Camisa", "Libro", "Celular", "Mesa", "Audifonos"};
    string categorias[] = {"Electronica", "Ropa", "Libros", "Hogar"};

    srand(time(0));

    // 🔹 Crear 50 productos aleatorios
    for (int i = 1; i <= 50; i++) {
        Producto p;
        p.id = i;
        p.nombre = nombres[rand() % 6] + " " + to_string(i);
        p.precio = 10 + rand() % 500;
        p.categoria = categorias[rand() % 4];
        p.stock = rand() % 100;
        p.calificacion = 1.0 + (rand() % 40) / 10.0; // Rating entre 1.0 y 5.0
        productos.push_back(p);
    }

    // 🔹 Mostrar productos originales
    cout << "===== LISTA DE PRODUCTOS =====\n\n";
    for (const auto& p : productos) {
        cout << "ID: " << p.id
             << " | " << p.nombre
             << " | $" << p.precio
             << " | Rating: " << p.calificacion
             << endl;
    }

    // ==========================
    // ORDENAR POR ID (para búsqueda binaria)
    // ==========================
    sort(productos.begin(), productos.end(), [](Producto a, Producto b) {
        return a.id < b.id;
    });

    // ==========================
    // ORDENAR POR PRECIO (QuickSort)
    // ==========================
    auto inicio = chrono::high_resolution_clock::now();
    quickSortPrecio(productos, 0, productos.size() - 1);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;

    cout << "\n=== ORDENADOS POR PRECIO (QuickSort) ===\n";
    for (const auto& p : productos) {
        cout << p.nombre << " - $" << p.precio << endl;
    }
    cout << "Tiempo QuickSort (precio): " << duracion.count() << " ms\n";

    // ==========================
    // ORDENAR POR CALIFICACION (Sort con lambda)
    // ==========================
    sort(productos.begin(), productos.end(), [](Producto a, Producto b) {
        return a.calificacion > b.calificacion;
    });

    cout << "\n=== ORDENADOS POR CALIFICACION ===\n";
    for (const auto& p : productos) {
        cout << p.nombre << " - Rating: " << p.calificacion << endl;
    }

    // ==========================
    // BÚSQUEDA BINARIA POR ID
    // ==========================
    int idBuscado = 10; // Cambia este valor para probar otros IDs
    auto inicioBusqueda = chrono::high_resolution_clock::now();
    int posicion = busquedaBinaria(productos, idBuscado);
    auto finBusqueda = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempoBusqueda = finBusqueda - inicioBusqueda;

    if (posicion != -1) {
        cout << "\nProducto encontrado: " << productos[posicion].nombre
             << " | ID: " << productos[posicion].id << endl;
    } else {
        cout << "\nProducto NO encontrado" << endl;
    }

    cout << "Tiempo de búsqueda: " << tiempoBusqueda.count() << " ms\n";

    return 0;
}
