// Tecnologico de Costa Rica - Proyecto 1A - Katerine Guzman Flores (2019390523) - Jose Pablo Aguero Mora (2021126372) - Prof: Victor Garro Abarca
// Funciones.h

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <random> 
#include <vector>
#include <algorithm>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


using namespace std;
#pragma warning(disable:4996);
#define FPS 30.0
#pragma once

/////////////
// Sección de funciones - Lista simple
/////////////

///// Variables globales ///////
int pruebaPiso = 285;
int pruebaTorre = 433;
int pruebaTercero = 85;

bool sigo = true;
vector<int> numeros;
///// Fin Variables globales ///////

typedef struct TEspacio // Nueva estructura de tipo TEspacio
{
	int CodigoP;
	int PosX;
	int PosY;
	bool Ocupado;
	int Columna;
	TEspacio* Siguiente;
}*PtrTEspacio;

typedef struct TCarro // Nueva estructura de tipo TCarro
{
	int CodigoP;
	int PosX;
	int PosY;
	int Skin;
	ALLEGRO_BITMAP* Personaje2;
	bool Parqueado;
	bool Sale;
	bool Pintar;
	TCarro* Siguiente;
}*PtrTCarro;

void InicializarInventario(PtrTEspacio& Lista)
{
	Lista = NULL; 
}

void InicializarInventarioCarro(PtrTCarro& Lista)
{
	Lista = NULL; 
}

PtrTEspacio CrearEspacio3(int NCodigo, int NNombre) // Para parqueo 2 pisos
{
	PtrTEspacio Pieza = new(TEspacio);

	// Asignacion de valores según cada ciclo
	Pieza->CodigoP = NCodigo;
	if (NCodigo == 7) {
		Pieza->PosY = 325;
		pruebaTercero = 85;
	}
	Pieza->PosX = pruebaTercero;
	if (NCodigo >= 7) {
		Pieza->PosY = 325;
		pruebaTercero += 120 - ((NCodigo - 6) * 2);
	}
	else {
		Pieza->PosY = 245;
		pruebaTercero += 120 - (NCodigo * 2);
	}
	Pieza->Ocupado = false;
	Pieza->Siguiente = NULL;
	return Pieza;
}

PtrTEspacio CrearEspacio2(int NCodigo, int NNombre) // Para parqueo 1
{
	PtrTEspacio Pieza = new(TEspacio);

	// Asignacion de valores según cada ciclo
	Pieza->CodigoP = NCodigo;
	if (NCodigo == 8) {
		pruebaPiso = 285;
	}
	if (NCodigo >= 8) {
		Pieza->PosY = 300;
	}
	else {
		Pieza->PosY = 130;
	}
	Pieza->PosX = pruebaPiso;
	pruebaPiso += 65;
	Pieza->Ocupado = false;
	Pieza->Siguiente = NULL;
	return Pieza;
}

PtrTEspacio CrearEspacio1(int NCodigo, int NNombre) // Para parqueo torre
{
	PtrTEspacio Pieza = new(TEspacio);

	// Asignacion de valores según cada ciclo
	Pieza->CodigoP = NCodigo;
	if (NCodigo == 10) {
		pruebaTorre = 433;
	}
	if (NCodigo >= 10) {
		Pieza->PosX = 470;
	}
	else {
		Pieza->PosX = 310;
	}
	Pieza->PosY = pruebaTorre;
	pruebaTorre -= 50;
	Pieza->Ocupado = false;

	Pieza->Siguiente = NULL;
	return Pieza;
}

int crearRandom(int inicio, int final) // Genera un entero aleatorio entre dos parámetros
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(inicio, final);
	return dis(gen);
}

PtrTCarro CrearCarro3(int NCodigo, int NNombre) // Crea carro de parqueo 2 pisos
{
	PtrTCarro Pieza = new(TCarro);

	// Asignacion de valores según cada ciclo
	Pieza->CodigoP = NCodigo;
	Pieza->PosX = -50;
	Pieza->PosY = 395;
	Pieza->Parqueado = false;
	Pieza->Sale = false;

	int numCarro = crearRandom(1, 4);
	Pieza->Skin = numCarro;
	Pieza->Pintar = true;
	Pieza->Siguiente = NULL;
	return Pieza;
} 

PtrTCarro CrearCarro2(int NCodigo, int NNombre) // Crea carro de parqueo 1 piso
{
	PtrTCarro Pieza = new(TCarro);

	// Asignacion de valores según cada ciclo
	Pieza->CodigoP = NCodigo;
	Pieza->PosX = -50;
	Pieza->PosY = 220;
	Pieza->Parqueado = false;
	Pieza->Sale = false;

	int numCarro = crearRandom(1, 4);
	Pieza->Skin = numCarro;
	Pieza->Pintar = true;
	Pieza->Siguiente = NULL;
	return Pieza;
}

PtrTCarro CrearCarro1(int NCodigo, int NNombre) // Crea carro de parqueo torre
{
	PtrTCarro Pieza = new(TCarro);

	// Asignacion de valores según cada ciclo
	Pieza->CodigoP = NCodigo;
	Pieza->PosX = 390;
	Pieza->PosY = 478;
	Pieza->Parqueado = false;
	Pieza->Sale = false;

	int numCarro = crearRandom(1, 4);
	Pieza->Skin = numCarro;
	Pieza->Pintar = true;
	Pieza->Siguiente = NULL;
	return Pieza;
}

// Para insertar en lista de espacios
void AgregarInicioInventario(PtrTEspacio& Lista, PtrTEspacio& Nuevo)
{
	Nuevo->Siguiente = Lista;
	Lista = Nuevo;
}

// Para insertar en lista de carros
void AgregarInicioInventarioCarro(PtrTCarro& Lista, PtrTCarro& Nuevo)
{
	Nuevo->Siguiente = Lista;
	Lista = Nuevo;
}

// Llenar parqueo 2 pisos
void LlenarListaEnlazada3(PtrTEspacio& Lista)
{
	PtrTEspacio Nuevo;
	InicializarInventario(Lista);
	for (int i = 1; i <= 12; i++)
	{
		Nuevo = CrearEspacio3(i, i);
		AgregarInicioInventario(Lista, Nuevo);
	}
}

// Llenar parqueo 1 piso
void LlenarListaEnlazada2(PtrTEspacio& Lista)
{
	PtrTEspacio Nuevo;
	InicializarInventario(Lista);
	for (int i = 1; i <= 14; i++)
	{
		Nuevo = CrearEspacio2(i, i);
		AgregarInicioInventario(Lista, Nuevo);
	}
}

// Llenar parqueo torre
void LlenarListaEnlazada1(PtrTEspacio& Lista)
{
	PtrTEspacio Nuevo;
	InicializarInventario(Lista);
	for (int i = 1; i <= 18; i++)
	{
		Nuevo = CrearEspacio1(i, i);
		AgregarInicioInventario(Lista, Nuevo);
	}
}

// Llenar lista carros parqueo 2 pisos
void LlenarListaEnlazadaCarro3(PtrTCarro& Lista)
{
	PtrTCarro Nuevo;
	InicializarInventarioCarro(Lista);
	for (int i = 1; i <= 5; i++) 
	{
		Nuevo = CrearCarro3(i, i);
		AgregarInicioInventarioCarro(Lista, Nuevo);
	}
}

// Llenar lista carros parqueo 1 piso
void LlenarListaEnlazadaCarro2(PtrTCarro& Lista)
{
	PtrTCarro Nuevo;
	InicializarInventarioCarro(Lista);
	for (int i = 1; i <= 5; i++) 
	{
		Nuevo = CrearCarro2(i, i);
		AgregarInicioInventarioCarro(Lista, Nuevo);
	}
}

// Llenar lista carros parqueo torre
void LlenarListaEnlazadaCarro1(PtrTCarro& Lista)
{
	PtrTCarro Nuevo;
	InicializarInventarioCarro(Lista);
	for (int i = 1; i <= 5; i++) 
	{
		Nuevo = CrearCarro1(i, i);
		AgregarInicioInventarioCarro(Lista, Nuevo);
	}
}

// Ocupación por default parqueo 2 pisos
void LlenarPorcentajeOcupado3(PtrTEspacio& ListaEspacios, PtrTCarro& ListaCarros)
{
	PtrTEspacio EActual;

	PtrTCarro CActual;
	CActual = ListaCarros;
	int contadorA = 1;
	while (contadorA != 6) // Realiza el proceso con los 5 primeros carros de la lista enlazada
	{
		EActual = ListaEspacios; // Vuelve al inicio a buscar
		int numRand = crearRandom(1, 12);

		numeros.push_back(50); // Agrega al vector para no repetir random

		while (*find(numeros.begin(), numeros.end(), numRand) == numRand) {
			numRand = crearRandom(1, 12);
		}

		numeros.push_back(numRand);
		
		while (EActual->CodigoP != numRand)
		{
			EActual = EActual->Siguiente;
		}
		
		EActual->Ocupado = true;
		CActual->Parqueado = true;

		int posAuxX = EActual->PosX;
		int posAuxY = EActual->PosY;

		CActual->PosX = posAuxX;
		CActual->PosY = posAuxY;

		CActual = CActual->Siguiente; 
		contadorA += 1; 
	}
}

// Ocupación por default parqueo 1 piso
void LlenarPorcentajeOcupado2(PtrTEspacio& ListaEspacios, PtrTCarro& ListaCarros)
{
	PtrTEspacio EActual;

	PtrTCarro CActual;
	CActual = ListaCarros;
	int contadorA = 1;
	while (contadorA != 6) // Realiza el proceso con los 5 primeros carros de la lista enlazada
	{
		EActual = ListaEspacios; // Vuelve al inicio a buscar
		int numRand = crearRandom(1, 14);

		numeros.push_back(50); // Agrega al vector para no repetir random

		while (*find(numeros.begin(), numeros.end(), numRand) == numRand) {
			numRand = crearRandom(1, 14);
		}

		numeros.push_back(numRand);

		while (EActual->CodigoP != numRand)
		{
			EActual = EActual->Siguiente;
		}

		EActual->Ocupado = true;
		CActual->Parqueado = true;

		int posAuxX = EActual->PosX;
		int posAuxY = EActual->PosY;

		CActual->PosX = posAuxX;
		CActual->PosY = posAuxY;

		CActual = CActual->Siguiente;
		contadorA += 1; 
	}
}

// Ocupación por default parqueo torre
void LlenarPorcentajeOcupado1(PtrTEspacio& ListaEspacios, PtrTCarro& ListaCarros)
{
	PtrTEspacio EActual;

	PtrTCarro CActual;
	CActual = ListaCarros;
	int contadorA = 1;
	while (contadorA != 6) // Realiza el proceso con los 5 primeros carros de la lista enlazada
	{
		EActual = ListaEspacios; // Vuelve al inicio a buscar
		int numRand = crearRandom(1, 16);

		numeros.push_back(50); // Agrega al vector para no repetir random

		while (*find(numeros.begin(), numeros.end(), numRand) == numRand) {
			numRand = crearRandom(4, 17);
		}

		numeros.push_back(numRand);

		while (EActual->CodigoP != numRand)
		{
			EActual = EActual->Siguiente;
		}

		EActual->Ocupado = true;
		CActual->Parqueado = true;

		int posAuxX = EActual->PosX;
		int posAuxY = EActual->PosY;

		CActual->PosX = posAuxX;
		CActual->PosY = posAuxY;

		CActual = CActual->Siguiente;
		contadorA += 1; 
	}
}

// Retorna nodo de carro buscado
PtrTCarro BuscarCarro(PtrTCarro& ListaCarros, int cual)
{
	PtrTCarro AuxCarro;
	AuxCarro = ListaCarros;
	while (AuxCarro->CodigoP != cual) 
	{
		AuxCarro = AuxCarro->Siguiente;
	}
	return AuxCarro;
}

////////// Sección Borrar /////////////

// Destruir lista carros
void DestruirInventarioCarros(PtrTCarro& Lista)
{
	PtrTCarro Aux;
	Aux = Lista;
	while (Aux != NULL)
	{
		Lista = Lista->Siguiente;
		delete(Aux);
		Aux = Lista;
	}
}

// Destruir lista espacios
void DestruirInventarioEspacios(PtrTEspacio& Lista)
{
	PtrTEspacio Aux;
	Aux = Lista;
	while (Aux != NULL)
	{
		Lista = Lista->Siguiente;
		delete(Aux);
		Aux = Lista;
	}
}

////////// Fin Sección Borrar /////////////

void LiberarEspacio(PtrTEspacio& ListaEspacio, int cual) // Verifica espacios disponibles
{
	PtrTEspacio AuxEspacio;
	AuxEspacio = ListaEspacio;
	while (AuxEspacio->CodigoP != cual)
	{
		AuxEspacio = AuxEspacio->Siguiente;
	}

	AuxEspacio->Ocupado = false;
}

bool VerificaSigo(PtrTEspacio& ListaEspacio) //	Verifica si el parqueo está lleno
{
	int contadorX = 0;
	PtrTEspacio AuxEspacio;
	AuxEspacio = ListaEspacio;

	while (AuxEspacio != NULL) { // Encuentra el último espacio 
		if (AuxEspacio->Ocupado == false) {
			contadorX += 1;
		}
		AuxEspacio = AuxEspacio->Siguiente;
	}

	if (contadorX == 0) { // Si no hay disponibles
		sigo = false;
		return false;
	}
	else {
		sigo = true;
	}
	return true;
}

bool VerificaMismo(PtrTCarro& ListaEspacio, int cual)
{
	PtrTCarro AuxEspacio;
	AuxEspacio = ListaEspacio;

	if (cual == 0) {
		return false;
	}

	while (AuxEspacio != NULL) { // Encuentra el último espacio
		if (AuxEspacio->CodigoP == cual) {
			return true;
		}
		AuxEspacio = AuxEspacio->Siguiente;
	}
	return false;
}

/////////////
// Fin sección funciones - Lista simple
/////////////


////////////
// Sección funciones juego (3 parqueos)
////////////

void juego3(PtrTCarro& Lista, PtrTEspacio& ListaEspacio) {

	if (!al_init()) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede inicializar Allegro", NULL, NULL);
		return;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	al_init_primitives_addon();
	al_install_keyboard();
	int ResX = 800;
	int ResY = 500;

	ALLEGRO_EVENT_QUEUE* cola_eventos = al_create_event_queue();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* Personaje = al_load_bitmap("redRojo.png");
	ALLEGRO_BITMAP* Personaje2 = al_load_bitmap("blueAzul.png");
	ALLEGRO_BITMAP* Personaje3 = al_load_bitmap("greenVerde.png");
	ALLEGRO_BITMAP* Personaje4 = al_load_bitmap("brownCafe.png");
	ALLEGRO_BITMAP* Fondo = al_load_bitmap("pilaMapa.png");

	al_register_event_source(cola_eventos, al_get_timer_event_source(timer));
	al_register_event_source(cola_eventos, al_get_keyboard_event_source());

	bool hecho = true; // Mantiene el ciclo principal

	int PosJugX = 438; // Posición inicial del personaje  
	int PosJugY = 400; 
	int cont = 1;

	al_start_timer(timer);

	PtrTCarro AuxCarro;
	AuxCarro = Lista;
	PtrTCarro Aux1;
	Aux1 = Lista;

	int general = 6;

	while (hecho) { // Ciclo se repite hasta tocar escape

		ALLEGRO_EVENT eventos;
		al_wait_for_event(cola_eventos, &eventos);
		if (eventos.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (eventos.keyboard.keycode) { // Registra eventos de teclado para reaccionar
			case ALLEGRO_KEY_ESCAPE:
				hecho = false;
				break;
			case ALLEGRO_KEY_R: // Al registrar el evento R se permite guardar datos
				int val;
				printf("Ingrese los datos: ");
				cin >> val;

				printf("\n");
				printf("Informacion registrada, seleccione una opcion (A = Ingresar / W = Retirar)\n");
				printf("\n");
				break;
			case ALLEGRO_KEY_A: // Evento A permite ingresar vehículos
				if (sigo == true) {
					if ((VerificaMismo(Lista, val)) == false) { // Solo si no hay otra placa igual
						PtrTCarro Nuevo;

						Nuevo = CrearCarro3(val, general);
						printf("\n");
						printf(" Ingresando el vehiculo con la Placa: %i \n", val);
						printf("\n");
						AgregarInicioInventarioCarro(Lista, Nuevo);
						Aux1 = Lista;
					}
					else {
						printf("\n");
						printf("Esta placa ya se ha registrado, ingrese una nueva \n");
						printf("\n");
					}
				}
				
				break;
			case ALLEGRO_KEY_W: // Evento W para retirar vehículos
				AuxCarro = Lista;
				while (AuxCarro->CodigoP != val && AuxCarro->Siguiente != NULL)
				{
					AuxCarro = AuxCarro->Siguiente;
				}

				if (AuxCarro->CodigoP != val) {
					printf("Esta placa no se encuentra registrada \n");
				}
				else {
					if (AuxCarro->Parqueado == true) {
						printf("Sacando el vehiculo del edificio... \n");

						AuxCarro->Sale = true;
						int cual = AuxCarro->CodigoP;

						LiberarEspacio(ListaEspacio, cual);
					}
				}
				break;
			}
		}
		if (eventos.type == ALLEGRO_EVENT_TIMER)
		{
			if (eventos.timer.source == timer)
			{
				PtrTEspacio AuxEspacio;
				AuxEspacio = ListaEspacio;

				VerificaSigo(ListaEspacio); // Comprueba el estado del valor sigo

				while (AuxEspacio->Ocupado == true && sigo == true)
				{
					if (AuxEspacio->Siguiente != NULL) {
						AuxEspacio = AuxEspacio->Siguiente;
					}
				}

				// Aquí ya se encontró el espacio disponible en AuxEspacio
				if (Aux1->Parqueado == false) { // Inicio del movimiento
					if (Aux1->PosX < AuxEspacio->PosX) { 
						Aux1->PosX = Aux1->PosX + 5; 
					}
					else {
						if (Aux1->PosY > AuxEspacio->PosY) {
							Aux1->PosY = Aux1->PosY - 5;
						}
						else {
							AuxEspacio->Ocupado = true;
							Aux1->Parqueado = true;
							AuxEspacio->CodigoP = Aux1->CodigoP; // Se le asigna la placa al código de espacio
							Aux1 = Aux1->Siguiente;
						}
					} 
				}
				else {
					if (Aux1->Siguiente != NULL) {
						Aux1 = Aux1->Siguiente;
					}
				}

				if (AuxCarro->Sale == true) {
					if (AuxCarro->PosY < 395) {
						AuxCarro->PosY = AuxCarro->PosY + 5;
					}
					else {
						if (AuxCarro->PosX < 900) {
							AuxCarro->PosX = AuxCarro->PosX + 5;
						}
					}
				}
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_scaled_bitmap(Fondo, 0, 0, 1920, 1100, 0, 0, 800, 500, NULL);
				PtrTCarro Aux;
				Aux = Lista;
				while (Aux != NULL)
				{
					if (Aux->Skin == 1) {
						al_draw_bitmap(Personaje, Aux->PosX, Aux->PosY, NULL);
					}
					if (Aux->Skin == 2) {
						al_draw_bitmap(Personaje2, Aux->PosX, Aux->PosY, NULL);
					}
					if (Aux->Skin == 3) {
						al_draw_bitmap(Personaje3, Aux->PosX, Aux->PosY, NULL);
					}
					if (Aux->Skin == 4) {
						al_draw_bitmap(Personaje4, Aux->PosX, Aux->PosY, NULL);
					}
					
					Aux = Aux->Siguiente; // se pasa al siguiente nodo
				}
			}
		}
		al_flip_display();
	}
	pruebaPiso = 285;
	pruebaTorre = 433;
	pruebaTercero = 85;
	numeros.clear();
	al_destroy_event_queue(cola_eventos);
	al_destroy_timer(timer);
}

void juego2(PtrTCarro& Lista, PtrTEspacio& ListaEspacio) {

	if (!al_init()) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede inicializar Allegro", NULL, NULL);
		return;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	al_init_primitives_addon();
	al_install_keyboard();
	int ResX = 800;
	int ResY = 500;

	ALLEGRO_EVENT_QUEUE* cola_eventos = al_create_event_queue();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* Personaje = al_load_bitmap("rojo.png");
	ALLEGRO_BITMAP* Personaje2 = al_load_bitmap("azul.png");
	ALLEGRO_BITMAP* Personaje3 = al_load_bitmap("amarillo.png");
	ALLEGRO_BITMAP* Personaje4 = al_load_bitmap("gris.png");
	ALLEGRO_BITMAP* Fondo = al_load_bitmap("piso.png");

	al_register_event_source(cola_eventos, al_get_timer_event_source(timer));
	al_register_event_source(cola_eventos, al_get_keyboard_event_source());

	bool hecho = true;

	int PosJugX = 438;
	int PosJugY = 400;
	int cont = 1;

	al_start_timer(timer);

	PtrTCarro AuxCarro;
	AuxCarro = Lista;
	PtrTCarro Aux1;
	Aux1 = Lista;

	int general = 6;

	while (hecho) {

		ALLEGRO_EVENT eventos;
		al_wait_for_event(cola_eventos, &eventos);
		if (eventos.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (eventos.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				hecho = false;
				break;
			case ALLEGRO_KEY_R:
				int val;
				printf("Ingrese los datos: ");
				cin >> val;

				printf("\n");
				printf("Informacion registrada, seleccione una opcion (A = Ingresar / W = Retirar)\n");
				printf("\n");
				break;
			case ALLEGRO_KEY_A:
				if (sigo == true) {
					if ((VerificaMismo(Lista, val)) == false) { // Solo si no hay otra placa igual
						PtrTCarro Nuevo;

						Nuevo = CrearCarro2(val, general);
						printf("\n");
						printf(" Ingresando el vehiculo con la Placa: %i \n", val);
						printf("\n");
						AgregarInicioInventarioCarro(Lista, Nuevo);
						Aux1 = Lista;
					}
					else {
						printf("\n");
						printf("Esta placa ya se ha registrado, ingrese una nueva \n");
						printf("\n");
					}
				}
				break;

			case ALLEGRO_KEY_W:
				AuxCarro = Lista;
				while (AuxCarro->CodigoP != val && AuxCarro->Siguiente != NULL)
				{
					AuxCarro = AuxCarro->Siguiente;
				}

				if (AuxCarro->CodigoP != val) {
					printf("Esta placa no se encuentra registrada \n");
				}
				else {
					if (AuxCarro->Parqueado == true) {
						printf("Sacando el vehiculo del edificio... \n");

						AuxCarro->Sale = true;
						int cual = AuxCarro->CodigoP;

						LiberarEspacio(ListaEspacio, cual);
					}
				}
				break;
			}
		}
		if (eventos.type == ALLEGRO_EVENT_TIMER)
		{
			if (eventos.timer.source == timer)
			{
				PtrTEspacio AuxEspacio;
				AuxEspacio = ListaEspacio;

				VerificaSigo(ListaEspacio);

				while (AuxEspacio->Ocupado == true && sigo == true) // Verifica movimiento de indice
				{
					if (AuxEspacio->Siguiente != NULL) {
						AuxEspacio = AuxEspacio->Siguiente; // se pasa al siguiente nodo
					}
				}

				// Aquí ya se encontró el espacio disponible en AuxEspacio
				if (Aux1->Parqueado == false) {
					if (Aux1->PosX <= 175) {
						Aux1->PosX = Aux1->PosX + 5;
					}
					else {
						if (AuxEspacio->PosY == 130) { // (130 = Arriba / 300 = Abajo)
							if (Aux1->PosY != AuxEspacio->PosY - 100 && Aux1->PosX != AuxEspacio->PosX) {
								Aux1->PosY = Aux1->PosY - 5;
							}
							else {
								if (Aux1->PosX != AuxEspacio->PosX) {
									Aux1->PosX = Aux1->PosX + 5;
								}
								else { // Cuando llega al espacio
									if (Aux1->PosY != AuxEspacio->PosY) {
										Aux1->PosY = Aux1->PosY + 5;
									}
									else {
										AuxEspacio->Ocupado = true;
										Aux1->Parqueado = true;
										AuxEspacio->CodigoP = Aux1->CodigoP; // Se le asigna la placa al código de espacio
										Aux1 = Aux1->Siguiente;
									}
								}
							}
						}
						else {
							if (Aux1->PosY != AuxEspacio->PosY + 100 && Aux1->PosX != AuxEspacio->PosX) {
								Aux1->PosY = Aux1->PosY + 5;
							}
							else {
								if (Aux1->PosX != AuxEspacio->PosX) {
									Aux1->PosX = Aux1->PosX + 5;
								}
								else { // Cuando llega al espacio
									if (Aux1->PosY != AuxEspacio->PosY) {
										Aux1->PosY = Aux1->PosY - 5;
									}
									else {
										AuxEspacio->Ocupado = true;
										Aux1->Parqueado = true;
										AuxEspacio->CodigoP = Aux1->CodigoP; // Se le asigna la placa al código de espacio
										Aux1 = Aux1->Siguiente;
									}
								}
							}
						}
					}
				}
				else {
					if (Aux1->Siguiente != NULL) {
						Aux1 = Aux1->Siguiente;
					}
				}

				if (AuxCarro->Sale == true) {
					if (AuxCarro->PosY <= 219) { // Si es arriba
						if (AuxCarro->PosY != 130 - 100 && AuxCarro->PosX >= 175) {
							AuxCarro->PosY = AuxCarro->PosY - 5;
						}
						else {
							if (AuxCarro->PosX >= 175) { 
								AuxCarro->PosX = AuxCarro->PosX - 5;
							}
							else {
								if (AuxCarro->PosY != 220) { 
									AuxCarro->PosY = AuxCarro->PosY + 5;
								}
								else {
									if (AuxCarro->PosX >= -50) {
										AuxCarro->PosX = AuxCarro->PosX - 5;
									}
								}
							}
						}
					}
					else { // Si es abajo
						if (AuxCarro->PosY != 300 + 100 && AuxCarro->PosX >= 175) { 
							AuxCarro->PosY = AuxCarro->PosY + 5;
						}
						else {
							if (AuxCarro->PosX >= 175) {
								AuxCarro->PosX = AuxCarro->PosX - 5;
							}
							else {
								if (AuxCarro->PosY != 220) {
									AuxCarro->PosY = AuxCarro->PosY - 5;
								}
								else {
									if (AuxCarro->PosX >= -50) {
										AuxCarro->PosX = AuxCarro->PosX - 5;
									}
								}
							}
						}
					}
				}
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_scaled_bitmap(Fondo, 0, 0, 1920, 1100, 0, 0, 800, 500, NULL);
				PtrTCarro Aux;
				Aux = Lista;
				while (Aux != NULL)
				{
					if (Aux->Skin == 1) {
						al_draw_bitmap(Personaje, Aux->PosX, Aux->PosY, NULL);
					}
					if (Aux->Skin == 2) {
						al_draw_bitmap(Personaje2, Aux->PosX, Aux->PosY, NULL);
					}
					if (Aux->Skin == 3) {
						al_draw_bitmap(Personaje3, Aux->PosX, Aux->PosY, NULL);
					}
					if (Aux->Skin == 4) {
						al_draw_bitmap(Personaje4, Aux->PosX, Aux->PosY, NULL);
					}

					Aux = Aux->Siguiente; // se pasa al siguiente nodo
				}
			}
		}
		al_flip_display();
	}
	pruebaPiso = 285;
	pruebaTorre = 433;
	pruebaTercero = 85;
	numeros.clear();
	al_destroy_event_queue(cola_eventos);
	al_destroy_timer(timer);
}

void juego1(PtrTCarro& Lista, PtrTEspacio& ListaEspacio) {

	if (!al_init()) {
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede inicializar Allegro", NULL, NULL);
		return;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();

	al_init_primitives_addon();
	al_install_keyboard();
	int ResX = 800;
	int ResY = 500;

	ALLEGRO_EVENT_QUEUE* cola_eventos = al_create_event_queue();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_BITMAP* Personaje = al_load_bitmap("carroRojo.png");
	ALLEGRO_BITMAP* Personaje2 = al_load_bitmap("carroVerde.png");
	ALLEGRO_BITMAP* Personaje3 = al_load_bitmap("carroAzul.png");
	ALLEGRO_BITMAP* Personaje4 = al_load_bitmap("carroCafe.png");
	ALLEGRO_BITMAP* Npc = al_load_bitmap("coolbug.png");
	ALLEGRO_BITMAP* Fondo = al_load_bitmap("torre5.png");

	al_register_event_source(cola_eventos, al_get_timer_event_source(timer));
	al_register_event_source(cola_eventos, al_get_keyboard_event_source());

	bool hecho = true;

	int PosJugX = 438;
	int PosJugY = 400;
	int cont = 1;

	al_start_timer(timer);

	PtrTCarro AuxCarro;
	AuxCarro = Lista;
	PtrTCarro Aux1;
	Aux1 = Lista;

	int general = 6;

	while (hecho) {

		ALLEGRO_EVENT eventos;
		al_wait_for_event(cola_eventos, &eventos);
		if (eventos.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (eventos.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				hecho = false;
				break;
			case ALLEGRO_KEY_R:
				int val;
				printf("Ingrese los datos: ");
				cin >> val;

				printf("\n");
				printf("Informacion registrada, seleccione una opcion (A = Ingresar / W = Retirar)\n");
				printf("\n");
				break;
			case ALLEGRO_KEY_A:
				if (sigo == true) {
					if ((VerificaMismo(Lista, val)) == false) { // Solo si no hay otra placa igual
						PtrTCarro Nuevo;

						Nuevo = CrearCarro1(val, general);
						printf("\n");
						printf(" Ingresando el vehiculo con la Placa: %i \n", val);
						printf("\n");
						AgregarInicioInventarioCarro(Lista, Nuevo);
						Aux1 = Lista;
					}
					else {
						printf("\n");
						printf("Esta placa ya se encuentra registrada, ingrese una nueva \n");
						printf("\n");
					}
				}
				break;
			case ALLEGRO_KEY_W:
				AuxCarro = Lista;
				while (AuxCarro->CodigoP != val && AuxCarro->Siguiente != NULL)
				{
					AuxCarro = AuxCarro->Siguiente;
				}

				if (AuxCarro->CodigoP != val) {
					printf("Esta placa no se encuentra registrada \n");
				}
				else {
					if (AuxCarro->Parqueado == true) {
						printf("Sacando el vehiculo del edificio... \n");

						AuxCarro->Sale = true;
						int cual = AuxCarro->CodigoP;

						LiberarEspacio(ListaEspacio, cual);
					}
				}
				break;
			}
		}
		if (eventos.type == ALLEGRO_EVENT_TIMER)
		{
			if (eventos.timer.source == timer)
			{
				PtrTEspacio AuxEspacio;
				AuxEspacio = ListaEspacio;

				VerificaSigo(ListaEspacio); // Función para modificar el valor sigo

				while (AuxEspacio->Ocupado == true && sigo == true) // Solo si sigo está activo
				{
					if (AuxEspacio->Siguiente != NULL) {
						AuxEspacio = AuxEspacio->Siguiente; // se pasa al siguiente nodo
					}
				}

				// Aquí ya se encontró el espacio disponible en AuxEspacio
				if (Aux1->Parqueado == false) {
					if (Aux1->PosY != AuxEspacio->PosY) {
						Aux1->PosY = Aux1->PosY - 5;
					}
					else {
						if (Aux1->PosX != AuxEspacio->PosX) {
							if (AuxEspacio->PosX > Aux1->PosX) {
								Aux1->PosX = Aux1->PosX + 5;
							}
							else {
								Aux1->PosX = Aux1->PosX - 5;
							}
						}
						else {
							if (Aux1->Siguiente != NULL) {
								AuxEspacio->Ocupado = true;
								Aux1->Parqueado = true;
								AuxEspacio->CodigoP = Aux1->CodigoP; // Se le asigna la placa al código de espacio
								Aux1 = Aux1->Siguiente;
							}
						}
					}
				}
				else {
					if (Aux1->Siguiente != NULL) {
						Aux1 = Aux1->Siguiente;
					}
				}

				if (AuxCarro->Sale == true) {
					if (AuxCarro->PosX != 390)
					{
						if (390 > AuxCarro->PosX) {
							AuxCarro->PosX = AuxCarro->PosX + 5;
						}
						else {
							AuxCarro->PosX = AuxCarro->PosX - 5;
						}
					}
					else {
						if (AuxCarro->PosY != 40) {
							AuxCarro->PosY = AuxCarro->PosY + 5;
						}
						else {
							AuxCarro->Pintar = false;
							int codeCual = AuxCarro->CodigoP;
						}
					}
				}
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_scaled_bitmap(Fondo, 0, 0, 1920, 1100, 0, 0, 800, 500, NULL);
				PtrTCarro Aux;
				Aux = Lista;
				while (Aux != NULL)
				{
					if (Aux->Skin == 1) {
						al_draw_bitmap(Personaje, Aux->PosX, Aux->PosY, NULL);
					}
					if (Aux->Skin == 2) {
						al_draw_bitmap(Personaje2, Aux->PosX, Aux->PosY, NULL);
					}
					if (Aux->Skin == 3) {
						al_draw_bitmap(Personaje3, Aux->PosX, Aux->PosY, NULL);
					}
					if (Aux->Skin == 4) {
						al_draw_bitmap(Personaje4, Aux->PosX, Aux->PosY, NULL);
					}

					Aux = Aux->Siguiente; // se pasa al siguiente nodo
				}
			}
		}
		al_flip_display();
	}
	pruebaPiso = 285;
	pruebaTorre = 433;
	pruebaTercero = 85;
	numeros.clear();
	al_destroy_event_queue(cola_eventos);
	al_destroy_timer(timer);
}

////////////
// Fin Sección funciones juego (3 parqueos)
////////////
