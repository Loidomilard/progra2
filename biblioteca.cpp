#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------- CLASE LIBRO ----------
class Libro {
public:
    string titulo;
    string autor;
    bool estaDisponible;

    // Constructor por defecto
    Libro() {
        estaDisponible = true; // Cuando se crea un libro, por defecto está disponible
    }

    // Mostrar los datos completos del libro
    void mostrarDetallesCompletos() {
        cout << " Titulo: " << titulo << endl;
        cout << " Autor: " << autor << endl;
        cout << "Estado: " << (estaDisponible ? "Disponible" : "Prestado") << endl;
        cout << "---------------------------" << endl;
    }
};

// ---------- CLASE BIBLIOTECA ----------
class Biblioteca {
private:
    vector<Libro> coleccion;

public:
    // Agrega un libro a la lista
    void agregarLibro(const Libro& nuevoLibro) {
        coleccion.push_back(nuevoLibro);
    }

    // Muestra todos los libros de la biblioteca
    void mostrarInventario() {
        if (coleccion.empty()) {
            cout << "No hay libros registrados aun." << endl;
            return;
        }
        for (const auto& libro : coleccion) {
            libro.mostrarDetallesCompletos();
        }
    }

    // Busca libro por su titulo y devuelve un puntero a ese libro
    Libro* buscarLibro(const string& tituloBuscado) {
        for (auto& libro : coleccion) {
            if (libro.titulo == tituloBuscado) {
                return &libro;
            }
        }
        return nullptr; // Si no lo encuentra
    }

    // Prestar libro (cambia a NO disponible si lo encuentra y está libre)
    void prestarLibro(const string& tituloPrestamo) {
        Libro* libro = buscarLibro(tituloPrestamo);
        if (libro == nullptr) {
            cout << "Ese libro no esta en la biblioteca." << endl;
        } else if (!libro->estaDisponible) {
            cout << "El libro ya esta prestado." << endl;
        } else {
            libro->estaDisponible = false;
            cout << "Se presto correctamente el libro: " << tituloPrestamo << endl;
        }
    }

    // Devolver libro (cambia a disponible si estaba prestado)
    void devolverLibro(const string& tituloDevolucion) {
        Libro* libro = buscarLibro(tituloDevolucion);
        if (libro == nullptr) {
            cout << "Ese libro no pertenece a esta biblioteca." << endl;
        } else if (libro->estaDisponible) {
            cout << "El libro ya estaba disponible, no estaba prestado." << endl;
        } else {
            libro->estaDisponible = true;
            cout << "Gracias por devolver el libro: " << tituloDevolucion << endl;
        }
    }
};

// ---------- FUNCION PRINCIPAL ----------
int main() {
    Biblioteca miBiblioteca;
    int opcion = 0;

    // Agregar un libro ya cargado
    Libro libroInicial;
    libroInicial.titulo = "El Hobbit";
    libroInicial.autor = "J.R.R. Tolkien";
    miBiblioteca.agregarLibro(libroInicial);

    // Menu principal
    while (opcion != 5) {
        cout << "\n====== BIBLIOTECA DIGITAL ======" << endl;
        cout << "1. Añadir libro" << endl;
        cout << "2. Mostrar inventario" << endl;
        cout << "3. Prestar libro" << endl;
        cout << "4. Devolver libro" << endl;
        cout << "5. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar buffer por si el usuario mete texto

        if (opcion == 1) {
            // Agregar nuevo libro
            Libro nuevo;
            cout << "Titulo del libro: ";
            getline(cin, nuevo.titulo);
            cout << "Autor del libro: ";
            getline(cin, nuevo.autor);
            miBiblioteca.agregarLibro(nuevo);
            cout << "Libro agregado correctamente!" << endl;
        }
        else if (opcion == 2) {
            // Mostrar inventario
            miBiblioteca.mostrarInventario();
        }
        else if (opcion == 3) {
            // Prestar libro
            string titulo;
            cout << "Titulo del libro a prestar: ";
            getline(cin, titulo);
            miBiblioteca.prestarLibro(titulo);
        }
        else if (opcion == 4) {
            // Devolver libro
            string titulo;
            cout << "Titulo del libro a devolver: ";
            getline(cin, titulo);
            miBiblioteca.devolverLibro(titulo);
        }
        else if (opcion == 5) {
            cout << "Gracias por usar la biblioteca digital." << endl;
        }
        else {
            cout << "Opcion invalida, intenta de nuevo." << endl;
        }
    }

    return 0;
}
