#include <iostream>
#include <string>
#include <sstream>
#include "Definiciones.h"
#include "Usuario.h"
#include "Producto.h"
#include "Mesa.h"
#include "Reserva.h"
#include "Historial.h"
#include "Pedido.h"

using namespace std;

int main() {
    // 1. Inicializacion de todas las estructuras de datos (Punteros a NULL)
    TpUsuario listaUsuarios = NULL;
    TpProducto listaProductos = NULL;
    TpMesa listaMesas = NULL;
    TpReserva listaReservas = NULL;
    
    // Pila para el historial (LIFO)
    TpHistorial pilaAcciones = NULL;
    
    // Cola para la cocina (FIFO)
    TpPedido frenteCocina = NULL;
    TpPedido finalCocina = NULL;

    // 2. Carga de datos de prueba (Quemados en memoria para testing)
    // Usuarios
    listaUsuarios = registrarUsuario(listaUsuarios, 1, "admin", "admin123", "Administrador");
    listaUsuarios = registrarUsuario(listaUsuarios, 2, "fernando", "1234", "Cliente");
    listaUsuarios = registrarUsuario(listaUsuarios, 3, "diego", "qwer", "Trabajador");

    // Inventario inicial
    listaProductos = agregarProducto(listaProductos, 101, "Combo Hamburguesa Big Boss", 20, 18.50);
    listaProductos = agregarProducto(listaProductos, 102, "Pollo Frito Crujiente KFC", 15, 21.90);
    listaProductos = agregarProducto(listaProductos, 103, "Mostrito con Pollo a la Brasa", 0, 19.00); // Agotado

    // Salon (Mesas)
    listaMesas = agregarMesa(listaMesas, 1, 2); 
    listaMesas = agregarMesa(listaMesas, 2, 4); 
    listaMesas = agregarMesa(listaMesas, 3, 6); 

    // Contadores globales para IDs correlativos
    int idPedGlobal = 1;
    int idAccGlobal = 1;
    int idReservaActual = 1; 

    // Variables de control de flujo
    int op, opSub;
    string user, pass;
    TpUsuario logueado = NULL;

    do {
        cout << "\n=========================================\n";
        cout << "   SISTEMA DE GESTION DE RESTAURANTE\n";
        cout << "=========================================\n";
        cout << "1. Iniciar Sesion\n";
        cout << "2. Ver Menu Digital (Publico)\n";
        cout << "3. Salir del Sistema\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op) {
            case 1:
                cout << "Usuario: "; cin >> user;
                cout << "Contrasena: "; cin >> pass;
                
                logueado = login(listaUsuarios, user, pass);
                
                if(logueado != NULL) {
                    cout << "\n>> Acceso Concedido. Bienvenido, " << logueado->nombre << "!\n";
                    
                    // MENU INTERNO COMPLETO SEGUN ROLES
                    do {
                        cout << "\n--- PANEL DE OPERACIONES: " << logueado->rol << " ---\n";
                        
                        // Opciones para Administrativos (Admin y Trabajador)
                        if(logueado->rol == "Administrador" || logueado->rol == "Trabajador") {
                            cout << "1. Ver Menu e Inventario de Almacen\n";
                            cout << "2. Modificar Inventario (Reabastecer / Modificar Stock)\n";
                            cout << "3. Ver Estado del Salon (Mesas)\n";
                            cout << "4. Registrar Nueva Reserva\n";
                            cout << "5. Ver Reservas Activas\n";
                            cout << "6. Generar Nuevo Pedido (Salon / Delivery)\n";
                            cout << "7. Ver y Procesar Cola de Cocina (FIFO)\n";
                            cout << "8. Despachar Pedido de Delivery (Validacion)\n";
                            cout << "9. Control de Cambios: Historial y Deshacer (LIFO)\n";
                        } 
                        // Opciones exclusivas para Clientes logueados
                        else if(logueado->rol == "Cliente") {
                            cout << "1. Ver Menu Digital\n";
                            cout << "2. Solicitar una Reserva presencial\n";
                        }
                        
                        cout << "0. Cerrar Sesion\n";
                        cout << "Opcion: ";
                        cin >> opSub;

                        // --- LOGICA DE EJECUCION DE LAS OPCIONES ---
                        
                        if(opSub == 1) {
                            mostrarMenuDigital(listaProductos);
                        }
                        
                        else if(opSub == 2 && (logueado->rol == "Administrador" || logueado->rol == "Trabajador")) {
                            int idProd, cant, accionInv;
                            cout << "\n1. Descontar por Venta Directa | 2. Reabastecer Almacen: "; cin >> accionInv;
                            cout << "ID Producto: "; cin >> idProd;
                            cout << "Cantidad de unidades: "; cin >> cant;
                            
                            if(accionInv == 1) {
                                if(verificarStock(listaProductos, idProd, cant)) {
                                    actualizarStock(listaProductos, idProd, cant);
                                    cout << ">> Stock actualizado con exito.\n";
                                    
                                    stringstream ss;
                                    ss << "Venta/Descuento de producto ID " << idProd;
                                    registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
                                } else {
                                    cout << ">> ERROR: Stock insuficiente o producto No Disponible.\n";
                                }
                            } else if(accionInv == 2) {
                                actualizarStock(listaProductos, idProd, -cant); // Pasamos negativo para sumar
                                cout << ">> Almacen reabastecido con exito.\n";
                                
                                stringstream ss;
                                ss << "Reabastecimiento de producto ID " << idProd;
                                registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
                            }
                        }
                        
                        else if(opSub == 3 && (logueado->rol == "Administrador" || logueado->rol == "Trabajador")) {
                            mostrarMesas(listaMesas);
                        }
                        
                        else if(opSub == 4) { // Funciona tanto para Admin/Trabajador como Cliente (opcion 2)
                            string f, h;
                            int numP, idM;
                            cout << "Fecha (DD/MM/AAAA): "; cin >> f;
                            cout << "Hora (HH:MM): "; cin >> h;
                            cout << "Numero de personas: "; cin >> numP;
                            
                            mostrarMesas(listaMesas);
                            cout << "Seleccione ID de mesa: "; cin >> idM;
                            
                            // Guardamos el estado anterior por si se desea deshacer
                            listaReservas = crearReserva(listaReservas, listaMesas, idReservaActual, f, h, numP, idM);
                            
                            stringstream ss;
                            ss << "Se registro la Reserva #" << idReservaActual;
                            registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
                            idReservaActual++;
                        }
                        
                        else if(opSub == 5 && (logueado->rol == "Administrador" || logueado->rol == "Trabajador")) {
                            mostrarReservas(listaReservas);
                        }
                        
                        else if(opSub == 6 && (logueado->rol == "Administrador" || logueado->rol == "Trabajador")) {
                            int tPed;
                            float subt, dist = 0;
                            cout << "Tipo de pedido (1. Salon | 2. Delivery): "; cin >> tPed;
                            cout << "Monto Subtotal de consumo: S/. "; cin >> subt;
                            
                            if(tPed == 2) {
                                cout << "Distancia estimada de entrega (Km): "; cin >> dist;
                                encolarPedido(frenteCocina, finalCocina, idPedGlobal, "Delivery", subt, dist);
                            } else {
                                encolarPedido(frenteCocina, finalCocina, idPedGlobal, "Salon", subt, 0);
                            }
                            
                            stringstream ss;
                            ss << "Se encol� el Pedido #" << idPedGlobal;
                            registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
                            idPedGlobal++;
                        }
                        
                        else if(opSub == 7 && (logueado->rol == "Administrador" || logueado->rol == "Trabajador")) {
                            mostrarColaCocina(frenteCocina);
                            if(frenteCocina != NULL) {
                                int accC;
                                cout << "\n1. Atender y preparar siguiente pedido en cola | 2. Volver: "; cin >> accC;
                                if(accC == 1) {
                                    atenderPedidoCocina(frenteCocina);
                                    registrarAccion(pilaAcciones, idAccGlobal++, "Se despacho pedido de Cocina");
                                }
                            }
                        }
                        
                        else if(opSub == 8 && (logueado->rol == "Administrador" || logueado->rol == "Trabajador")) {
                            int idP, idR;
                            string dir, tel;
                            cout << "Ingrese ID del pedido de Delivery a despachar: "; cin >> idP;
                            cout << "ID del Repartidor asignado: "; cin >> idR;
                            cout << "Direccion de entrega (sin espacios): "; cin >> dir;
                            cout << "Telefono de contacto: "; cin >> tel;
                            
                            // Llama a la funcion con validaciones estrictas del PDF
                            despacharDelivery(frenteCocina, idP, idR, dir, tel);
                            
                            stringstream ss;
                            ss << "Despacho delivery de Pedido #" << idP;
                            registrarAccion(pilaAcciones, idAccGlobal++, ss.str());
                        }
                        
                        else if(opSub == 9 && (logueado->rol == "Administrador" || logueado->rol == "Trabajador")) {
                            mostrarHistorial(pilaAcciones);
                            if(pilaAcciones != NULL) {
                                int accH;
                                cout << "\n1. [DESHACER] Revertir ultima accion | 2. Volver: "; cin >> accH;
                                if(accH == 1) {
                                    deshacerAccion(pilaAcciones);
                                }
                            }
                        }

                    } while(opSub != 0);
                    
                    logueado = NULL; // Limpiamos la sesion al salir
                    cout << ">> Sesion cerrada.\n";
                } else {
                    cout << "\n>> ERROR: Credenciales invalidas.\n";
                }
                break;
                
            case 2:
                mostrarMenuDigital(listaProductos);
                break;
                
            case 3:
                cout << "\nFinalizando ejecucion del sistema. �Buen dia, Grupo 4!\n";
                break;
                
            default:
                cout << "Opcion incorrecta.\n";
        }
    } while(op != 3);

    return 0;
}
