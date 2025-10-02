
// Archivo: biblioteca.cpp
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// ===== STRUCTS =====

struct Autor {
    int id;
    string nombre;
    string nacionalidad;
};

struct Libro {
    int id;
    string titulo;
    int anio;
    int id_autor;
    bool disponible = true;
};

struct Estudiante {
    int id;
    string nombre;
    string carrera;
};

struct Prestamo {
    int id;
    int id_libro;
    int id_estudiante;
    string fecha_prestamo;
    string fecha_devolucion;
    bool devuelto;
};

// ===== CLASE BIBLIOTECA (simula la BD) =====

class BibliotecaDB {
public:
    vector<Libro> libros;
    vector<Autor> autores;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;

    void agregarLibro(Libro l) {
        for (auto& b : libros) {
            if (b.id == l.id) {
                cout << "Error: ID de libro duplicado." << endl;
                return;
            }
        }
        libros.push_back(l);
    }

    void listarLibros() {
        for (auto& l : libros) {
            cout << l.id << " | " << l.titulo << " | " << l.anio << " | Autor ID: " << l.id_autor << " | ";
            cout << (l.disponible ? "Disponible" : "Prestado") << endl;
        }
    }

    void guardarLibros() {
        ofstream archivo("libros.txt");
        for (auto& l : libros) {
            archivo << l.id << "," << l.titulo << "," << l.anio << "," << l.id_autor << "," << l.disponible << endl;
        }
        archivo.close();
    }

    void cargarLibros() {
        ifstream archivo("libros.txt");
        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string parte;
            Libro l;
            getline(ss, parte, ','); l.id = stoi(parte);
            getline(ss, parte, ','); l.titulo = parte;
            getline(ss, parte, ','); l.anio = stoi(parte);
            getline(ss, parte, ','); l.id_autor = stoi(parte);
            getline(ss, parte, ','); l.disponible = stoi(parte);
            libros.push_back(l);
        }
        archivo.close();
    }
};

// ===== MAIN =====

int main() {
    BibliotecaDB db;
    db.cargarLibros();

    int opcion;
    do {
        cout << "\n--- MENU BIBLIOTECA ---\n";
        cout << "1. Agregar libro\n";
        cout << "2. Listar libros\n";
        cout << "3. Guardar y salir\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1) {
            Libro l;
            cout << "ID: "; cin >> l.id; cin.ignore();
            cout << "Título: "; getline(cin, l.titulo);
            cout << "Año: "; cin >> l.anio;
            cout << "ID Autor: "; cin >> l.id_autor;
            db.agregarLibro(l);
        } else if (opcion == 2) {
            db.listarLibros();
        } else if (opcion == 3) {
            db.guardarLibros();
            cout << "Datos guardados. Saliendo..." << endl;
        }
    } while (opcion != 3);

    return 0;
}
