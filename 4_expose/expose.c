#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define startW 640
#define startH 400

void draw(int x1, int y1, int x2, int y2) {
  ALLEGRO_COLOR c, w, b;

  static int ZZ = 0;
  if      (ZZ == 0) c = al_map_rgb(225, 30, 30);
  else if (ZZ == 1) c = al_map_rgb(10, 220, 10);
  else if (ZZ == 2) c = al_map_rgb(0, 0, 155);
  else if (ZZ == 3) c = al_map_rgb(235, 155, 20);
  else if (ZZ == 4) c = al_map_rgb(20, 100, 245);
  ZZ = (ZZ + 1) % 5;

  w = al_map_rgb(255, 255, 255);
  b = al_map_rgb(0, 0, 0);

  al_draw_filled_rectangle(x1, y1, x2, y2, c);
  al_draw_rectangle(x1 + 0.5, y1 + 0.5, x2 - 0.5, y2 - 0.5, w, 1);
  al_draw_rectangle(x1 + 1.5, y1 + 1.5, x2 - 1.5, y2 - 1.5, b, 1);
  printf("(%d; %d), (%d; %d)\n", x1, y1, x2, y2);

  al_flip_display();
}

void expose(ALLEGRO_DISPLAY_EVENT *event) {
  int x1, y1, x2, y2;
  x1 = event->x;
  y1 = event->y;
  x2 = x1 + event->width;
  y2 = y1 + event->height;
  draw(x1, y1, x2, y2);
}

int main() {
  al_init();
  al_install_keyboard();
  al_install_mouse();
  al_init_primitives_addon();

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

  al_set_new_display_flags(ALLEGRO_GENERATE_EXPOSE_EVENTS | ALLEGRO_RESIZABLE);
  al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, true, ALLEGRO_REQUIRE);
  ALLEGRO_DISPLAY* disp = al_create_display(startW, startH);

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));

  bool done = false;
  ALLEGRO_EVENT event;

  draw(0, 0, startW, startH);

  while (!done) {
    al_wait_for_event(queue, &event);

    if (event.type == ALLEGRO_EVENT_DISPLAY_EXPOSE) {
      expose(&event.display);
    } else if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
      al_acknowledge_resize(event.display.source);
    } else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) ||
               (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)) {
      done = true;
    }
  }

  al_destroy_display(disp);
  al_destroy_event_queue(queue);

  return 0;
}
