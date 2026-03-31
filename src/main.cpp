#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Estructura del producto
struct Producto {
    int id;
    string nombre;
    double precio;
    string categoria;
    int stock;
    double calificacion;
};

int main() {

    vector<Producto> productos;

    string nombres[] = {"Laptop", "Camisa", "Libro", "Celular", "Mesa", "Audifonos"};
    string categorias[] = {"Electronica", "Ropa", "Libros", "Hogar"};

    srand(time(0));

    // Crear 50 productos
    for (int i = 1; i <= 50; i++) {
        Producto p;

        p.id = i;
        p.nombre = nombres[rand() % 6] + " " + to_string(i);
        p.precio = 10 + rand() % 500;
        p.categoria = categorias[rand() % 4];
        p.stock = rand() % 100;

        // Calificación decimal
        p.calificacion = 1.0 + (rand() % 40) / 10.0;

        productos.push_back(p);
    }

    // Mostrar productos
    cout << "===== LISTA DE PRODUCTOS =====\n\n";
    for (const auto& p : productos) {
        cout << p.nombre << " | $" << p.precio << " | Rating: " << p.calificacion << endl;
    }

    // ORDENAR POR PRECIO
    sort(productos.begin(), productos.end(), [](Producto a, Producto b) {
        return a.precio < b.precio;
    });

    cout << "\n=== ORDENADOS POR PRECIO ===\n";
    for (const auto& p : productos) {
        cout << p.nombre << " - $" << p.precio << endl;
    }

    // ORDENAR POR CALIFICACION
    sort(productos.begin(), productos.end(), [](Producto a, Producto b) {
        return a.calificacion > b.calificacion;
    });

    cout << "\n=== ORDENADOS POR CALIFICACION ===\n";
    for (const auto& p : productos) {
        cout << p.nombre << " - Rating: " << p.calificacion << endl;
    }

    return 0;
}
