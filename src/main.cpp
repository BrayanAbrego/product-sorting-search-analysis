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
// Función para mostrar productos
// ==========================
void mostrarProductos(const vector<Producto>& productos, const string& titulo) {
    cout << "\n=== " << titulo << " ===\n";
    for (const auto& p : productos) {
        cout << "ID: " << p.id
             << " | " << p.nombre
             << " | $" << p.precio
             << " | Rating: " << p.calificacion
             << " | Stock: " << p.stock
             << " | Cat: " << p.categoria << endl;
    }
}

// ==========================
// Main
// ==========================
int main() {
    vector<Producto> productos;
    vector<Producto> productosOriginal; // Para preservar el original

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
        p.calificacion = 1.0 + (rand() % 40) / 10.0;
        productos.push_back(p);
    }
    
    productosOriginal = productos; // Guardar copia original

    // 🔹 Mostrar productos originales
    mostrarProductos(productos, "PRODUCTOS ORIGINALES");

    // ==========================
    // PRUEBA 1: ORDENAR POR PRECIO (QuickSort)
    // ==========================
    vector<Producto> productosPorPrecio = productosOriginal;
    auto inicio = chrono::high_resolution_clock::now();
    quickSortPrecio(productosPorPrecio, 0, productosPorPrecio.size() - 1);
    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duracion = fin - inicio;

    cout << "\n=== ORDENADOS POR PRECIO (QuickSort) ===\n";
    for (const auto& p : productosPorPrecio) {
        cout << p.nombre << " - $" << p.precio << endl;
    }
    cout << "Tiempo QuickSort (precio): " << duracion.count() << " ms\n";

    // ==========================
    // PRUEBA 2: ORDENAR POR CALIFICACION (Sort con lambda)
    // ==========================
    vector<Producto> productosPorCalif = productosOriginal;
    inicio = chrono::high_resolution_clock::now();
    sort(productosPorCalif.begin(), productosPorCalif.end(), [](Producto a, Producto b) {
        return a.calificacion > b.calificacion;
    });
    fin = chrono::high_resolution_clock::now();
    duracion = fin - inicio;

    cout << "\n=== ORDENADOS POR CALIFICACION ===\n";
    for (const auto& p : productosPorCalif) {
        cout << p.nombre << " - Rating: " << p.calificacion << endl;
    }
    cout << "Tiempo Sort: " << duracion.count() << " ms\n";

    // ==========================
    // PRUEBA 3: BÚSQUEDA BINARIA POR ID (requiere orden por ID)
    // ==========================
    vector<Producto> productosPorId = productosOriginal;
    sort(productosPorId.begin(), productosPorId.end(), [](Producto a, Producto b) {
        return a.id < b.id;
    });

    int idBuscado = 25; // Buscar ID 25
    auto inicioBusqueda = chrono::high_resolution_clock::now();
    int posicion = busquedaBinaria(productosPorId, idBuscado);
    auto finBusqueda = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> tiempoBusqueda = finBusqueda - inicioBusqueda;

    if (posicion != -1) {
        cout << "\n=== BÚSQUEDA BINARIA ===\n";
        cout << "Producto encontrado: " << productosPorId[posicion].nombre
             << " | ID: " << productosPorId[posicion].id
             << " | Precio: $" << productosPorId[posicion].precio << endl;
    } else {
        cout << "\nProducto con ID " << idBuscado << " NO encontrado" << endl;
    }
    cout << "Tiempo de búsqueda: " << tiempoBusqueda.count() << " ms\n";

    // ==========================
    // PRUEBA 4: Mostrar que el original no se modificó
    // ==========================
    cout << "\n=== DEMOSTRACIÓN: DATOS ORIGINALES INTACTOS ===\n";
    cout << "Primer producto original: " << productosOriginal[0].nombre 
         << " (ID: " << productosOriginal[0].id << ")\n";

    return 0;
}
