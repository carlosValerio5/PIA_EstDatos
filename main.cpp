#include<iostream>
using namespace std;

struct datosAlumnos{
    int matricula;
    string nombre;
    float promedioG;
    string direccion;
    string telefono;
    struct datosAlumnos *sgtAlumno;
};

typedef struct datosAlumnos *Talumnos;
void imprimir(Talumnos &alumnosT);
void agregarAlumno(Talumnos &alumnosT);

int main(){
    int op;
    Talumnos alumnos=NULL;
    do{
        cout<<"----------MENU----------"<<endl;
        cout<<"1.Agregar alumno\n2.\n3.\n4.\n5.\n6.Mostrar(Temporal)\n7.Salir\n"<<endl;
        cout<<"\nIngresa una opcion: ";cin>>op;
            switch(op){
                case 1:agregarAlumno(alumnos);
                    break;

                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    break;

                case 6:imprimir(alumnos);
                    break;
            }

        }while(op!=7);



    return 0;
}


void imprimir(Talumnos &alumnosT){
    Talumnos q;
    q=alumnosT;

    while(q!=NULL){
        cout<<q->matricula<<endl;
        q=q->sgtAlumno;
    }
}

void agregarAlumno(Talumnos &alumnosT) {
    Talumnos aux = new(struct datosAlumnos);
    Talumnos p;

    cout<<"\n\t\t\tDATOS DEL ALUMNO\n";
    cout<<"Ingrese la numero de matricula: ";cin>>aux->matricula;
    cin.ignore();
    //validacion para nombre
    do{
        cout<<"Ingrese el nombre: ";getline(cin,aux->nombre);
        if(aux->nombre.length() == 0)
            cout<<"\nEl campo no puede estar vacio"<<endl;
    }while(aux->nombre.length() == 0);

        // Validación para promedio general
    do{
        cout << "Ingrese el promedio general: ";
        cin >> aux->promedioG;

        if (aux->promedioG <= 0 || aux->promedioG > 100) {
            cout << "\nEl promedio general no puede ser menor a 0 o mayor a 100" << endl;
        }
    }while (aux->promedioG <= 0 || aux->promedioG > 100);
    cin.ignore();

    // Validación para dirección
    do{
        cout << "Ingrese la direccion: ";
        getline(cin, aux->direccion);

        if (aux->direccion.length() == 0) {
            cout << "\nEl campo no puede estar vacio" << endl;
        }
    }while (aux->direccion.length() == 0);

    // Validación para número de teléfono
    do{
        cout << "Ingrese el numero de telefono: ";
        getline(cin, aux->telefono);

        if (aux->telefono.length() != 10) {
            cout << "\nEl telefono debe ser de 10 digitos" << endl;
        }
    }while (aux->telefono.length() != 10);

    if (alumnosT == NULL) {
        alumnosT = aux;
    } else {
        p = alumnosT;
        while (p->sgtAlumno != NULL) {
            p = p->sgtAlumno;
        }
        p->sgtAlumno = aux;
    }
}
