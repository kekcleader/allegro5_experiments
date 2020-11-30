#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

static int Z = 10;

void draw() {
  al_clear_to_color(al_map_rgb(40, 0, 0));
  float Q = Z;

  al_draw_line(Q + 30.5, 30.5, Q + 0.5, 120.5, al_map_rgb(255, 155, 0), 0);
  al_draw_line(Q + 30.5, 30.5, Q + 70.5, 70.5, al_map_rgb(255, 155, 0), 0);
  al_draw_line(Q + 70.5, 70.5, Q + 0.5, 120.5, al_map_rgb(255, 155, 0), 0);
}

int main() {
  al_init();
  al_install_keyboard();
  al_install_mouse();
  al_init_primitives_addon();

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  ALLEGRO_DISPLAY* disp = al_create_display(320, 200);

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  bool redraw = true;
  bool done = false;
  ALLEGRO_EVENT event;

  al_start_timer(timer);
  while (!done) {
    al_wait_for_event(queue, &event);

    if (event.type == ALLEGRO_EVENT_TIMER) {
      redraw = true;
    } else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
      Z += 5;
    } else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) ||
               (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)) {
      done = true;
    }

    if (redraw && al_is_event_queue_empty(queue)) {
      draw();
      al_flip_display();
      redraw = false;
    }
  }

  al_destroy_display(disp);
  al_destroy_event_queue(queue);

  return 0;
}
