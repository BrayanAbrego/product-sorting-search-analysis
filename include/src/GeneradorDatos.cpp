#include "GeneradorDatos.h"
#include <cstdlib>
#include <ctime>

vector<Producto> generarProductos(int cantidad) {
    vector<Producto> productos;

    string nombres[] = {"Laptop", "Camisa", "Libro", "Celular", "Mesa", "Audifonos"};
    string categorias[] = {"Electronica", "Ropa", "Libros", "Hogar"};

    srand(time(0));

    for (int i = 1; i <= cantidad; i++) {
        Producto p;

        p.id = i;
        p.nombre = nombres[rand() % 6] + " " + to_string(i);
        p.precio = 10 + (rand() % 500);
        p.categoria = categorias[rand() % 4];
        p.stock = rand() % 100;
        p.calificacionPromedio = 1 + (rand() % 5);

        productos.push_back(p);
    }

    return productos;
}
