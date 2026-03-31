#include <iostream>
#include <vector>
#include "GeneradorDatos.h"

using namespace std;

int main() {

    vector<Producto> productos = generarProductos(50);

    for (const auto& p : productos) {
        cout << p.id << " | " << p.nombre << " | $" << p.precio << endl;
    }

    return 0;
}
