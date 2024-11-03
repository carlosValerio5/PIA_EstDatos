/* EQUIPO 3
*  CARLOS HECTOR LEAL DELGADO
*  CARLOS MANUEL VALERIO RIOS
*  GUILLERMO BAUTISTA HERNANDEZ
*  EDER ABISAI ESQUIVEL MALDONADO
*/
#include<iostream>
#include <limits>
#include<string>
#include <iomanip>
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
void imprimir(Talumnos &,Talumnos &);
char menuReportes();
void agregarAlumno(Talumnos &);
int contarAlumnos(Talumnos );
void listaAArray(Talumnos , Talumnos* , int );
void arrayALista(Talumnos* , Talumnos& , int );
void quickSort(Talumnos* , int , int );
int busquedaBinaria(Talumnos* , int , int );
int busquedaSecuencial(Talumnos *, int);
void modifdatos(Talumnos &);
void creargrupos(Talumnos &);

//Funciones de Baja y alta de estudiantes
int menuBaja();
void eliminar(Talumnos &, Talumnos&);
void eliminarPorMatricula(Talumnos&, int, Talumnos&);
void eliminarPorNombre(Talumnos&, Talumnos&, string);
void recuperarAlumno(Talumnos &, Talumnos &);






int main(){
    int op;
    Talumnos alumnos=NULL;
    Talumnos PilaEliminados=NULL;
    do{
        cout<<"\n\n----------MENU----------"<<endl;
        cout<<"1.Agregar alumno\n2.Baja de estudiantes\n3.Recuperar alumno\n4.Reportes\n5.Modificacion de Datos\n6.Creacion de Grupos\n7.Salir\n"<<endl;
        cout<<"\nIngresa una opcion: ";cin>>op;
        while(op<1 || op >7){
            cout<<"Error. Ingrese un valor entre 1 y 7"<<endl;
            system("pause"); system("cls");
            cout<<"\n\n\n----------MENU----------"<<endl;
            cout<<"1.Agregar alumno\n2.Baja de estudiantes\n3.\n4.Reportes\n5.Modificacion de Datos\n6.Creacion de Grupos\n7.Salir\n"<<endl;
            cout<<"\nIngresa una opcion: ";cin>>op;
            if (cin.fail()) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                op = 0;
            }
        }
            switch(op){
                case 1:agregarAlumno(alumnos);
                    break;

                case 2:eliminar(alumnos, PilaEliminados);
                    break;

                case 3: if(PilaEliminados != NULL){
                    recuperarAlumno(PilaEliminados,alumnos);
                    }else{
                        cout << "\nNo hay alumnos dados de baja ";
                    }
                    break;

                case 4:imprimir(alumnos, PilaEliminados);
                    break;

                case 5:modifdatos(alumnos);
                    break;

                case 6:creargrupos(alumnos);
                    break;
            }

        }while(op!=7);



    return 0;
}

//-----------------------------------------------------------------------
int menuBaja(){
    int op;

    do
    {
        cout << "\n\n1.-Por matricula. \n2.-Por nombre.";
        cout << "\nSelecciona una opcion para dar de baja: ";
        cin >> op;
        if (cin.fail()) {
            cout << "Entrada invalida. Por favor ingresa un numero." << endl;
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            op = 0;
        }
    } while (op != 1 && op != 2);
    
    return op;
}


void eliminarPorMatricula(Talumnos &listaAlumnos, int posE, Talumnos &Pila)
{
    Talumnos p, ant = NULL;
    int i =0;
    p = listaAlumnos;
    
    while(i <= posE)
    {
        if(i == posE)
        {
            if(p == listaAlumnos)
            {
                listaAlumnos = listaAlumnos->sgtAlumno;
            }else{
                ant->sgtAlumno = p->sgtAlumno;
            }
            //Asignamos el nuevo elemento a la pila
            if(Pila == NULL)
            {
                Pila = p;
                Pila->sgtAlumno = NULL;
            }else{
                p->sgtAlumno = Pila;
                Pila = p;
            }
            return;
        }
        ant = p;
        p = p->sgtAlumno;
        i++;
    }
}


void eliminarPorNombre(Talumnos &listaAlumnos, Talumnos &Pila, string nombre)
{
    Talumnos p, ant = NULL;
    p=listaAlumnos;
    while(p!=NULL)
    {
        if (p->nombre == nombre)
        {
            if (p == listaAlumnos)
            {
                listaAlumnos = listaAlumnos->sgtAlumno;
            }else{
                ant->sgtAlumno = p->sgtAlumno;
            }
            //Asignamos el nuevo elemento a la pila
            if(Pila == NULL)
            {
                Pila = p;
                Pila->sgtAlumno = NULL;
            }else{
                p->sgtAlumno = Pila;
                Pila = p;
            }
            return;
            
        }
        ant = p;
        p = p->sgtAlumno;
    }
    cout << "\nNo se encontro el nombre";
}



void eliminar(Talumnos &alumnosT, Talumnos &Pila){ //Funcion para eliminar alumnos
    if(alumnosT != NULL)//Primero comprobamos si hay elemento para eliminar
    {

        if(menuBaja() == 1)//Eliminar alumno por matricula
        {
            int matricula, posE;
            int cantidad = contarAlumnos(alumnosT);//contamos la cantidad de alumnos
            Talumnos* alumnosArray = new Talumnos[cantidad]; // Crear un array temporal
            listaAArray(alumnosT, alumnosArray, cantidad); // Convertir la lista a array
            do
            {
                cout << "\n\nIngresa la matricula a eliminar: ";
                cin >> matricula;
                //Fragmento de codigo sacado de la funcion agregar funcion es para verificar la matricula
                if (cin.fail() || matricula <= 0 || matricula > 9999999) {
                    cout << "\nLa matricula debe ser un numero de 7 digitos y no puede contener letras." << endl;
                    cin.clear(); // Limpiar el estado de error de cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                posE = busquedaBinaria(alumnosArray, cantidad, matricula); //posE sirvira para saber asta donde recorrer la lista para elimnar el alumno
            } while (matricula <= 0 || matricula > 9999999 ||  busquedaBinaria(alumnosArray, cantidad, matricula)==-1);
            arrayALista(alumnosArray, alumnosT, cantidad);
            eliminarPorMatricula(alumnosT,posE, Pila);
        }else{
            string nombre;
            do {
                cin.ignore();
                cout << "\n\nIngrese el nombre: ";
                getline(cin, nombre);
                if (nombre.length() == 0)
                    cout << "\nEl campo no puede estar vacio" << endl;
            } while (nombre.length() == 0);
            eliminarPorNombre(alumnosT,Pila,nombre);
            
        }
    }else{
        cout << "\nNo se puede eliminar ningun elemento porque la lista esta vacia... ";
    }
}



void recuperarAlumno(Talumnos &pila, Talumnos &listaAlum)
{
    Talumnos aux=NULL;
    int cantidad;
    aux = pila;
    pila = aux->sgtAlumno;

    aux->sgtAlumno=listaAlum;
    listaAlum=aux;
    
    cantidad = contarAlumnos(listaAlum); // Recontar la cantidad de alumnos
    Talumnos* alumnosArray = new Talumnos[cantidad]; // Crear nuevo array para QuickSort
    listaAArray(listaAlum, alumnosArray, cantidad); // Convertir lista a array
    quickSort(alumnosArray, 0, cantidad - 1); // Ordenar el array con QuickSort
    arrayALista(alumnosArray, listaAlum, cantidad); // Convertir array de nuevo a lista
    cout << "\nSe recupero el alumno con exito\n\n\n";
    system("pause");

}

//------------------------------------------------------------------------
//Opcion de reportes
void imprimir(Talumnos &alumnosT, Talumnos &Pila){
    char op;
    float cntA,cntR,cnt;
	Talumnos q, p;
    q=alumnosT;
    p=Pila;
    
    do{
		op = menuReportes();
		cout<<endl;
		switch(op){
			case 'a':
				cout<<left<<setw(10)<<"Matricula"<<setw(25)<<"Nombre"<<setw(10)<<"Promedio"<<endl;
				while(q!=NULL){
					if(q->promedioG>=70){
						cout<<right<<setfill('0')<<setw(7)<<q->matricula<<setfill(' ')<<"   ";
				        cout<<left<<setw(25)<<q->nombre<<setw(10)<<q->promedioG<<endl;
					}
					q=q->sgtAlumno;
			    }
				break;
			case 'b':
				cntA=0;cntR=0;
				while (q != NULL) {
					cnt++;
					if(q->promedioG>=70)
			        	cntA++;
			        else
			        	cntR++;
			        q = q->sgtAlumno;
			    }
			    if((cntA+cntR)!=0)
			    	cout<< "Aprobados: "<<(cntA/(cnt))*100<<"%"<<endl<< "Reprobados: "<<(cntR/(cnt))*100<<"%"<<endl;
			    else
			    	cout << "No hay alumnos."<<endl;
			    
				break;
			case 'c':
				int cal;
				do {
			        if(cin.fail()){
			            cin.clear(); // Limpiar el estado de error de cin
			            cin.ignore(numeric_limits<streamsize>::max(), '\n');} // Limpiar el buffer de entrada
			        cout << "Ingrese el promedio general a buscar: ";
			        cin >> cal;
			
			        if (cin.fail() || cal < 0 || cal > 100) {
			            cout << "\nEl promedio general debe ser un numero entre 0 y 100.\n";
			        }
			    } while (cin.fail()|| cal < 0 || cal > 100);
			    cin.ignore();
			    
			    cout<<left<<setw(25)<<"Nombre"<<setw(10)<<"Promedio"<<endl;
				while(q!=NULL){
					if(q->promedioG>=cal)
				        cout<<left<<setw(25)<<q->nombre<<setw(10)<<q->promedioG<<endl;
					
					q=q->sgtAlumno;
			    }
	
				break;
			case 'd':
				cout<<left<<setw(10)<<"Matricula"<<setw(25)<<"Nombre"<<setw(25)<<"Direccion"<<setw(10)<<"Telefono"<<endl;
				while(q!=NULL){
			        cout<<right<<setfill('0')<<setw(7)<<q->matricula<<setfill(' ')<<"   ";
			        cout<<left<<setw(25)<<q->nombre<<setw(25)<<q->direccion<<setw(10)<<q->telefono<<endl;
			        q=q->sgtAlumno;
			    }
				break;
			case 'e':
				cout<<left<<setw(10)<<"Matricula"<<setw(25)<<"Nombre"<<setw(25)<<"Direccion"<<setw(10)<<"Telefono"<<endl;
				while(p!=NULL){
			        cout<<right<<setfill('0')<<setw(7)<<p->matricula<<setfill(' ')<<"   ";
			        cout<<left<<setw(25)<<p->nombre<<setw(25)<<p->direccion<<setw(10)<<p->telefono<<endl;
			        p=p->sgtAlumno;
			    }
				break;
			case 'f':
				break;
		}
		q = alumnosT;
	} while(op!='f');
	
    
}

char menuReportes(){
	char op;

    do
    {
        cout << "\n\na) Alumnos Aprobados. \nb) Porcentajes. \nc) Busqueda por calificacion.\nd) Datos Generales.\ne) Alumnos inactivos\nf) Salir";
        cout << "\nSelecciona una opcion: ";
        cin >> op;
        if (op != 'a' && op != 'b'&& op != 'c'&& op != 'd'&& op != 'e'&& op != 'f') {
            cout << "Entrada invalida. Por favor ingresa un caracter valido." << endl;
            cin.clear(); 
        }
    } while (op != 'a' && op != 'b'&& op != 'c'&& op != 'd'&& op != 'e'&& op != 'f');
    
    return op;
}

// Funci�n para contar la cantidad de alumnos en la lista (�til para QuickSort)
int contarAlumnos(Talumnos alumnosT) {
    int count = 0;
    while (alumnosT != NULL) {
        count++;
        alumnosT = alumnosT->sgtAlumno;
    }
    return count;
}

// Funci�n para convertir la lista enlazada a un array
void listaAArray(Talumnos alumnosT, Talumnos* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = alumnosT;
        alumnosT = alumnosT->sgtAlumno;
    }
}

// Funci�n para convertir el array de vuelta a la lista enlazada
void arrayALista(Talumnos* array, Talumnos& alumnosT, int size) {
    alumnosT = array[0];
    Talumnos p = alumnosT;
    for (int i = 1; i < size; i++) {
        p->sgtAlumno = array[i];
        p = p->sgtAlumno;
    }
    p->sgtAlumno = NULL; // Terminar la lista
}

// Funci�n para la b�squeda binaria en un array de alumnos por matr�cula
int busquedaBinaria(Talumnos* array, int size, int matricula) {
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (array[mid]->matricula == matricula) {
            return mid; // Matr�cula ya existe
        } else if (array[mid]->matricula < matricula) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

// Funci�n para el QuickSort (ordenar por matr�cula)
void quickSort(Talumnos* array, int low, int high) {
    if (low < high) {
        int pivot = array[high]->matricula;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (array[j]->matricula < pivot) {
                i++;
                swap(array[i], array[j]);
            }
        }
        swap(array[i + 1], array[high]);
        int pi = i + 1;

        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

// Funci�n para agregar un nuevo alumno con validaci�n de matr�cula duplicada
void agregarAlumno(Talumnos &alumnosT) {
    Talumnos aux = new(struct datosAlumnos);
    Talumnos p;
    int matricula;
    float promedioG;

    int cantidadAlumnos = contarAlumnos(alumnosT); // Cantidad de alumnos actuales
    Talumnos* alumnosArray = new Talumnos[cantidadAlumnos]; // Crear un array temporal
    listaAArray(alumnosT, alumnosArray, cantidadAlumnos); // Convertir la lista a array

    cout << "\n\t\t\tDATOS DEL ALUMNO\n";

    // Validaci�n de matr�cula �nica
    do {
        cout << "Ingrese el numero de matricula: ";
        cin >> matricula;

        // Verificar que la entrada sea num�rica y tenga exactamente 7 d�gitos
        if (cin.fail() || matricula <= 0 || matricula > 9999999) {
            cout << "\nLa matricula debe ser un numero de 7 digitos y no puede contener letras." << endl;
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
        } else if (busquedaBinaria(alumnosArray, cantidadAlumnos, matricula)!=-1) {
            cout << "\nLa matricula ya existe, ingrese una diferente." << endl;
        }

    } while (matricula <= 0 || matricula > 9999999 || busquedaBinaria(alumnosArray, cantidadAlumnos, matricula)!=-1);

    aux->matricula = matricula; // Asignar matr�cula
    cin.ignore();

    // Validaci�n para nombre
    do {
        cout << "Ingrese el nombre: ";
        getline(cin, aux->nombre);
        if (aux->nombre.length() == 0)
            cout << "\nEl campo no puede estar vacio" << endl;
    } while (aux->nombre.length() == 0);

    // Validaci�n para promedio general
    do {
        if(cin.fail()){
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');} // Limpiar el buffer de entrada
        cout << "Ingrese el promedio general: ";
        cin >> promedioG;

        if (cin.fail() || promedioG < 0 || promedioG > 100) {
            cout << "\nEl promedio general debe ser un numero entre 0 y 100.\n";
        }
    } while (cin.fail()|| promedioG < 0 || promedioG > 100);

    aux->promedioG = promedioG;
    cin.ignore();

    // Validaci�n para direcci�n
    do {
        cout << "Ingrese la direccion: ";
        getline(cin, aux->direccion);

        if (aux->direccion.length() == 0) {
            cout << "\nEl campo no puede estar vacio" << endl;
        }
    } while (aux->direccion.length() == 0);

    // Validaci�n para n�mero de tel�fono
    do {
        cout << "Ingrese el numero de telefono: ";
        getline(cin, aux->telefono);

        if (aux->telefono.length() != 10) {
            cout << "\nEl telefono debe ser de 10 digitos" << endl;
        }
    } while (aux->telefono.length() != 10);

    // Agregar el nuevo alumno a la lista (como �ltimo elemento)
    aux->sgtAlumno = NULL;
    if (alumnosT == NULL) {
        alumnosT = aux;
    } else {
        p = alumnosT;
        while (p->sgtAlumno != NULL) {
            p = p->sgtAlumno;
        }
        p->sgtAlumno = aux;
    }

    // Ordenar la lista por matr�cula usando QuickSort
    cantidadAlumnos = contarAlumnos(alumnosT); // Recontar la cantidad de alumnos
    alumnosArray = new Talumnos[cantidadAlumnos]; // Crear nuevo array para QuickSort
    listaAArray(alumnosT, alumnosArray, cantidadAlumnos); // Convertir lista a array
    quickSort(alumnosArray, 0, cantidadAlumnos - 1); // Ordenar el array con QuickSort
    arrayALista(alumnosArray, alumnosT, cantidadAlumnos); // Convertir array de nuevo a lista
}

int busquedaSecuencial(Talumnos *array, int cantalumnos){
    string nombusqueda;
    cin.ignore();
    do {
            cout << "Ingrese el nombre: ";
            getline(cin, nombusqueda);
            if (nombusqueda.length() == 0)
                cout << "\n\nEl campo no puede estar vacio" << endl;
    } while (nombusqueda.length() == 0);
        //Usamos busqueda secuencial para poder encontrar el nombre
    for (int i = 0; i<cantalumnos; i++){
        if(array[i]->nombre==nombusqueda){
            return i;
        }
    }
    return -1;
}


//Funcion para modificar datos de los alumnos
void modifdatos(Talumnos &p){

    string nombusqueda;
    int cantidad = contarAlumnos(p);//Cantidad de alumnos en la lista
    Talumnos *array = new Talumnos[cantidad];
    listaAArray(p, array, cantidad);//Convertir a array

    int op, matricula, ubicacion, opmod, condic = 0;
    do{
        cout<<"\n1. Busqueda por Matricula\n2. Busqueda por Nombre\nIngrese una opcion:";
        cin>>op;
        if(cin.fail()||op<1||op>2){
            cout<<"\nOpcion invalida, intente de nuevo."<<endl;
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//Limpiar buffer
        }
    }while(cin.fail()||op<1 || op>2);
    //Busqueda Binaria por matricula
    if(op==1){
        do{
            if (cin.fail()){
                cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//Limpiar buffer
            }
            cout<<"\nIngrese una matricula:";
            cin>>matricula;
            if(cin.fail()||matricula <= 0 || matricula > 9999999){
                cout<<"La matricula debe tener 7 digitos."<<endl;
            }

        }while(cin.fail()||matricula <= 0 || matricula > 9999999);

        //Se busca la matricula ingresada con busqueda binaria
        ubicacion = busquedaBinaria(array, cantidad, matricula);//posicion de la matricula en array

        if(ubicacion == -1){//Caso matricula no encontrada
            cout<<"\nMatricula no encontrada. Regresando a menu.\n"<<endl;
            return;
        }
    }
    //Busqueda por Nombre
    else{
        ubicacion = busquedaSecuencial(array, cantidad);
        if(ubicacion == -1){
            cout<<"\nNombre no encontrado. Regresando a menu.\n"<<endl;
            return;
        }
    }
    do{
        if(cin.fail()){
            cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//Limpiar buffer
        }
        cout << "\n1. Matricula\n2. Nombre\n3. Promedio General\n4. Direccion\n5. Telefono\nIngrese una opcion: ";
        cin>>opmod;
        if(cin.fail()||opmod<1||opmod>5){
            cout<<"Ingrese una opcion entre 1 y 5."<<endl;
        }
    }while(cin.fail()||opmod<1||opmod>5);
    switch (opmod)
    {
    case 1:
        do{
            condic = 0;
            if(cin.fail()){
                cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');//Limpiar buffer
            }
            cout<<"\nIngrese la nueva matricula:";
            cin>>matricula;
            if(cin.fail()|| matricula <= 0 || matricula > 9999999){
                cout<<"La matricula debe tener 7 digitos."<<endl;
            }
            else if(busquedaBinaria(array, cantidad, matricula)!=-1){
                cout<<"\nEsta matricula ya existe intente con otra.";
                condic = 1;
            }
        }while(cin.fail()|| matricula <= 0 || matricula > 9999999 ||condic);
        array[ubicacion]->matricula = matricula;
        quickSort(array, 0, cantidad-1);//volvemos a ordenar a los alumnos por matricula    
        break;
    
    case 2:
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        do {
            cout << "\nIngrese el nombre: ";
            getline(cin, array[ubicacion]->nombre);
            if (array[ubicacion]->nombre.length() == 0)
                cout << "\nEl campo no puede estar vacio" << endl;
        }while (array[ubicacion]->nombre.length() == 0);
        cout<<"\nNombre modificado con exito"<<endl;
        break;
    case 3:
        do {
            if(cin.fail()){
                cin.clear(); // Limpiar el estado de error de cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n');} // Limpiar el buffer de entrada
            cout << "Ingrese el promedio general: ";
            cin >> array[ubicacion]->promedioG;
    
            if (cin.fail() || array[ubicacion]->promedioG < 0 || array[ubicacion]->promedioG > 100) {
                cout << "\nEl promedio general debe ser un numero entre 0 y 100.\n";
            }
        } while (cin.fail()|| array[ubicacion]->promedioG < 0 || array[ubicacion]->promedioG > 100);
        cout<<"Promedio General actualizado con exito."<<endl;
        break;
    case 4:
        cin.ignore();
        do {
            cout << "Ingrese la direccion: ";
            getline(cin, array[ubicacion]->direccion);
    
            if (array[ubicacion]->direccion.length() == 0) {
                cout << "\nEl campo no puede estar vacio" << endl;
            }
        } while (array[ubicacion]->direccion.length() == 0);
        break;
    case 5:
        cin.ignore();
        do {
            cout << "Ingrese el numero de telefono: ";
            getline(cin, array[ubicacion]->telefono);
    
            if (array[ubicacion]->telefono.length() != 10) {
                cout << "\nEl telefono debe ser de 10 digitos" << endl;
            }
        } while (array[ubicacion]->telefono.length() != 10);
        break;
    default:
        break;
    }
    //Despues de haber aplicado los cambios, se actualizan en la lista
    arrayALista(array, p, cantidad);
}

//Funcion para creargrupos
void creargrupos(Talumnos &alumnos){
    int cantalumnos = contarAlumnos(alumnos);
    if (cantalumnos == 0){
        cout<<"Primero agregue al menos un alumno a la lista.";
        return;
    }
    int restantes;
    int numgrupos, alumengrup;//numero de grupos y el numero de alumnos por grupo
    Talumnos *array = new Talumnos[cantalumnos];
    listaAArray(alumnos, array, cantalumnos);
    do{
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout<<"\nIngrese el numero de grupos a crear: ";
        cin>>numgrupos;
        if(cin.fail()||numgrupos<=0||numgrupos>cantalumnos)
            cout<<"\nEl numero de grupos debe ser un numero mayor a cero y menor al total de alumnos.";
        
    }while(cin.fail()||numgrupos<=0||numgrupos>cantalumnos);
    cout<<numgrupos;

    
    restantes = cantalumnos;
    alumengrup = cantalumnos/numgrupos;
    for(int i = 0; i<numgrupos; i++){
        cout<<"\nGrupo "<<i+1;
        //En caso de que estemos en la ultima iteracion el limite seran los alumnos restantes.
        for(int j = 0; j < ((i==numgrupos-1) ? restantes: alumengrup); j++){
            cout<<"\nNombre: "<<array[j+alumengrup*i]->nombre;
            cout<<" Matricula: ";
            cout<<setw(7)<<array[j+alumengrup*i]->matricula;
        }
        //Restamos la cantidad de alumnos en el grupo a el total de alumnos restantes.
        restantes = restantes - alumengrup;
    }

}

