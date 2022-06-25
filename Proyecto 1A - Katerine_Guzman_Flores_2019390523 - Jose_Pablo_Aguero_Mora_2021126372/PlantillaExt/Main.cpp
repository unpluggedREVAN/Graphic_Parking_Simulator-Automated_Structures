// Tecnologico de Costa Rica - Proyecto 1A - Katerine Guzman Flores (2019390523) - Jose Pablo Aguero Mora (2021126372) - Prof: Victor Garro Abarca
// Main.cpp

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Funciones.h"

using namespace std;
#pragma warning(disable:4996);
#define FPS 60.0

int alturaDeFrame = 3700;
int AnchoDeFrame = 3000;

int main()
{
	if (!al_init())
	{
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede inicializar Allegro", NULL, NULL);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_mouse();

	int ResX = 800;
	int ResY = 500;
	int mousex = 0;
	int mousey = 0;

	ALLEGRO_MONITOR_INFO monitor;
	al_get_monitor_info(0, &monitor);
	const int RX = monitor.x2 - monitor.x1;
	const int RY = monitor.y2 - monitor.y1;

	///////////// Comienzo del menú ///////////////////////
	ALLEGRO_DISPLAY* pantalla = al_create_display(800, 500); // RX / RY

	al_set_window_title(pantalla, "Menu Estacionamientos");// Título de la ventana
	if (!pantalla)
	{
		//Si el display no se ejecuta se lanza el mensaje de error
		al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede crear la pantalla", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	//Se crean todos los punteros propios de Allegro y se carga el multimedia y los timers
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER* timerD = al_create_timer(1.0 / 15);

	ALLEGRO_EVENT_QUEUE* cola_eventos = al_create_event_queue();

	ALLEGRO_FONT* fuente1;
	ALLEGRO_FONT* fuente2;
	ALLEGRO_FONT* fuente3;

	ALLEGRO_BITMAP* Fondo = al_load_bitmap("Imagenes/vectorP.png");

	fuente1 = al_load_font("pixel.ttf", 80, NULL);
	fuente2 = al_load_font("pixel.ttf", 50, NULL);
	fuente3 = al_load_font("pixel.ttf", 30, NULL);

	//Se registran las fuentes de eventos(timers y periféricos) en la cola de eventos

	al_register_event_source(cola_eventos, al_get_timer_event_source(timer));
	al_register_event_source(cola_eventos, al_get_timer_event_source(timerD));
	al_register_event_source(cola_eventos, al_get_display_event_source(pantalla));
	al_register_event_source(cola_eventos, al_get_keyboard_event_source());
	al_register_event_source(cola_eventos, al_get_mouse_event_source());

	bool hecho2 = true;

	//Se obtienen las dimensiones de la pantalla en donde se proyecta el juego para que este se ajuste a las dimensiones
	int X = al_get_display_width(pantalla);
	int Y = al_get_display_height(pantalla);

	//Se reproduce la música del menú principal e inician timers
	al_start_timer(timer);
	al_start_timer(timerD);

	while (hecho2)
	{
		ALLEGRO_EVENT eventos;
		al_wait_for_event(cola_eventos, &eventos);

		if (eventos.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			//Se registra la posición en x y y del mouse
			mousex = eventos.mouse.x;
			mousey = eventos.mouse.y;

		}
		if (eventos.type == ALLEGRO_EVENT_TIMER)
		{
			if (eventos.timer.source == timer)
			{
				//Se dibuja el fondo y las opciones del menú en la ventana principal
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_scaled_bitmap(Fondo, 0, 0, 1600, 1000, 0, 0, 800, 500, NULL); // 1920
				al_draw_text(fuente1, al_map_rgb(53, 44, 25), X / 2, (RY * (50.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "ESTACIONAMIENTOS");
				al_draw_text(fuente2, al_map_rgb(0, 0, 0), X / 2, (RY * (100.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "PARQUEO DE TORRE");
				al_draw_text(fuente2, al_map_rgb(0, 0, 0), X / 2, (RY * (130.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "PARQUEO UN PISO");
				al_draw_text(fuente2, al_map_rgb(0, 0, 0), X / 2, (RY * (160.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "PARQUEO DOS PISOS");
				al_draw_text(fuente2, al_map_rgb(0, 0, 0), X / 2, (RY * (190.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SALIR");
			}
		}
		// Si el cursor se posiciona por encima, se resalta el botón / Opción Parqueo de torre
		if ((mousex >= X / 2 - 145 && mousex <= X / 2 + 145) && (mousey >= (RY * 100.0 / 768.0) && mousey <= (RY * 130.0 / 768.0))) {
			al_draw_text(fuente2, al_map_rgb(243, 123, 104), X / 2, (RY * (100.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "PARQUEO DE TORRE");
			if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (eventos.mouse.button & 1) {
					sigo = true;
					system("CLS");
					al_destroy_display(pantalla);

					PtrTEspacio ListaEspacios;
					PtrTCarro ListaCarros;

					LlenarListaEnlazada1(ListaEspacios);
					LlenarListaEnlazadaCarro1(ListaCarros);
					LlenarPorcentajeOcupado1(ListaEspacios, ListaCarros);

					ALLEGRO_DISPLAY* pantalla2 = al_create_display(ResX, ResY);
					al_set_window_position(pantalla2, RX / 4 - ResX / 4, RY / 4 - ResY / 4);
					al_set_window_title(pantalla2, "Proyecto 1A - Parqueo de torre");

					printf("----- Bienvenido al sistema de parqueos ----- \n");
					printf("Siga las instrucciones en pantalla para ingresar o retirar vehiculos \n");

					juego1(ListaCarros, ListaEspacios);

					if (!pantalla2)
					{
						al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede crear la pantalla", NULL, ALLEGRO_MESSAGEBOX_ERROR);
						return -1;
					}
					DestruirInventarioEspacios(ListaEspacios);
					DestruirInventarioCarros(ListaCarros);
					al_destroy_display(pantalla2);
					main();
					hecho2 = false;
				}
			}
		}
		// Si el cursor se posiciona por encima, se resalta el botón / Opción Parqueo de un piso
		if ((mousex >= X / 2 - 140 && mousex <= X / 2 + 140) && (mousey >= (RY * (130.0 / 768.0)) && mousey <= (RY * 160.0 / 768.0))) {
			al_draw_text(fuente2, al_map_rgb(243, 123, 104), X / 2, (RY * (130.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "PARQUEO UN PISO");
			if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (eventos.mouse.button & 1) {
					sigo = true;
					system("CLS");
					al_destroy_display(pantalla);

					PtrTEspacio ListaEspacios;
					PtrTCarro ListaCarros;

					LlenarListaEnlazada2(ListaEspacios);
					LlenarListaEnlazadaCarro2(ListaCarros);
					LlenarPorcentajeOcupado2(ListaEspacios, ListaCarros);

					ALLEGRO_DISPLAY* pantalla2 = al_create_display(ResX, ResY);
					al_set_window_position(pantalla2, RX / 4 - ResX / 4, RY / 4 - ResY / 4);
					al_set_window_title(pantalla2, "Proyecto 1A - Parqueo de un piso");

					printf("----- Bienvenido al sistema de parqueos ----- \n");
					printf("Siga las instrucciones en pantalla para ingresar o retirar vehiculos \n");

					juego2(ListaCarros, ListaEspacios);

					if (!pantalla2)
					{
						al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede crear la pantalla", NULL, ALLEGRO_MESSAGEBOX_ERROR);
						return -1;
					}
					DestruirInventarioEspacios(ListaEspacios);
					DestruirInventarioCarros(ListaCarros);
					al_destroy_display(pantalla2);
					main();
					hecho2 = false;
				}
			}
		}
		// Si el cursor se posiciona por encima, se resalta el botón / Opción Parqueo de dos pisos
		if ((mousex >= X / 2 - 145 && mousex <= X / 2 + 145) && (mousey >= (RY * (160.0 / 768.0)) && mousey <= (RY * (190.0 / 768.0)))) {
			al_draw_text(fuente2, al_map_rgb(243, 123, 104), X / 2, RY * (160.0 / 768.0), ALLEGRO_ALIGN_CENTRE, "PARQUEO DOS PISOS");
			if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (eventos.mouse.button & 1) {
					sigo = true;
					system("CLS");
					al_destroy_display(pantalla);

					PtrTEspacio ListaEspacios;
					PtrTCarro ListaCarros;

					LlenarListaEnlazada3(ListaEspacios);
					LlenarListaEnlazadaCarro3(ListaCarros);
					LlenarPorcentajeOcupado3(ListaEspacios, ListaCarros);

					ALLEGRO_DISPLAY* pantalla2 = al_create_display(ResX, ResY);
					al_set_window_position(pantalla2, RX / 4 - ResX / 4, RY / 4 - ResY / 4);
					al_set_window_title(pantalla2, "Proyecto 1A - Parqueo de dos pisos");

					printf("----- Bienvenido al sistema de parqueos ----- \n");
					printf("Siga las instrucciones en pantalla para ingresar o retirar vehiculos \n");

					juego3(ListaCarros, ListaEspacios);

					if (!pantalla2)
					{
						al_show_native_message_box(NULL, "Ventana Emergente", "Error", "No se puede crear la pantalla", NULL, ALLEGRO_MESSAGEBOX_ERROR);
						return -1;
					}
					DestruirInventarioEspacios(ListaEspacios);
					DestruirInventarioCarros(ListaCarros);
					al_destroy_display(pantalla2);
					main();
					hecho2 = false;
				}
			}
		}
		if ((mousex >= X / 2 - 120 && mousex <= X / 2 + 120) && (mousey >= (RY * (190.0 / 768.0)) && mousey <= (RY * (220.0 / 768.0)))) {
			//Si se presiona la  opción de salir se sale de la cola de eventos y termina la aplicación
			al_draw_text(fuente2, al_map_rgb(243, 123, 104), X / 2, (RY * (190.0 / 768.0)), ALLEGRO_ALIGN_CENTRE, "SALIR");
			if (eventos.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				if (eventos.mouse.button & 1) {
					hecho2 = false;
					al_destroy_display(pantalla);
					system("CLS");
				}
			}
		}
		if (eventos.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			//Si se presiona la tecla escape se sale del juego
			switch (eventos.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				hecho2 = false;
			}
		}
		else if (eventos.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			hecho2 = false;
		}
		al_flip_display();
	}
	//al_destroy_display(pantalla);
}