#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

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

    srand(time(0)); // inicializa números aleatorios

    // 🔹 Crear 50 productos
    for (int i = 1; i <= 50; i++) {
        Producto p;

        p.id = i;
        p.nombre = nombres[rand() % 6] + string(" ") + to_string(i);
        p.precio = 10 + (rand() % 500);
        p.categoria = categorias[rand() % 4];
        p.stock = rand() % 100;

        // Calificación decimal entre 1.0 y 5.0
        p.calificacion = 1.0 + (rand() % 40) / 10.0;

        productos.push_back(p);
    }

    // 🔹 Mostrar productos
    cout << "===== LISTA DE PRODUCTOS =====\n\n";

    for (const auto& p : productos) {
        cout << "ID: " << p.id
             << " | Nombre: " << p.nombre
             << " | Precio: $" << p.precio
             << " | Categoria: " << p.categoria
             << " | Stock: " << p.stock
             << " | Rating: " << p.calificacion
             << endl;
    }

    return 0;
}
