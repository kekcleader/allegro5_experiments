#include <stdio.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#define maxWindows 20

ALLEGRO_DISPLAY *windows[maxWindows];
int windowCount;

ALLEGRO_EVENT_QUEUE* queue;

void Draw(ALLEGRO_DISPLAY *win) {
  al_set_target_backbuffer(win);
  al_clear_to_color(al_map_rgb(60, 120, 30));
  ALLEGRO_COLOR c = al_map_rgb(220, 220, 200);
  al_draw_filled_rectangle(300.5, 3.5, 316.5, 19.5, al_map_rgb(0, 0, 0));
  al_draw_rectangle(300.5, 3.5, 316.5, 19.5, c, 1);
  al_draw_line(300.5, 3.5, 316.5, 19.5, c, 1);
  al_draw_line(316.5, 3.5, 300.5, 19.5, c, 1);
  al_flip_display();
}

void DrawAllWindows() {
  int i;
  for (i = 0; i < windowCount; i++) {
    Draw(windows[i]);
  }
}

void OpenWindow() {
  if (windowCount < maxWindows) {
    ALLEGRO_DISPLAY *disp = al_create_display(320, 200);
    al_register_event_source(queue, al_get_display_event_source(disp));
    windows[windowCount] = disp;
    windowCount++;
  }
}

void CloseWindow(ALLEGRO_DISPLAY *win) {
  int i = 0;
  while (windows[i] != win) i++;
  windows[i] = windows[windowCount - 1];
  windowCount--;
  al_destroy_display(win);
}

void HandleMouseDown(ALLEGRO_MOUSE_EVENT *event, bool *done) {
  int x = event->x;
  int y = event->y;
  if ((300 <= x) && (x <= 316) && (4 <= y) && (y <= 20)) {
    CloseWindow(event->display);
    if (windowCount == 0) *done = true;
  } else {
    OpenWindow();
  }
}

void DestroyAllWindows() {
  int i;
  for (i = 0; i < windowCount; i++) {
    al_destroy_display(windows[i]);
  }
}

void HandleWindowClose(ALLEGRO_DISPLAY_EVENT *event, bool *done){
  if (windowCount == 1) {
    *done = true;
  } else {
    CloseWindow(event->source);
    if (windowCount == 0) *done = true;
  }
}

int main() {
  al_init();
  al_install_keyboard();
  al_install_mouse();
  al_init_primitives_addon();

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30.0);
  queue = al_create_event_queue();
  windowCount = 0;
  OpenWindow();

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());
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
      // &event.mouse is the same as (ALLEGRO_MOUSE_EVENT *)&event
      // as the type ALLEGRO_EVENT is a C union.
      HandleMouseDown(&event.mouse, &done);
    } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      // &event.display is the same as (ALLEGRO_DISPLAY_EVENT *)&event
      // as the type ALLEGRO_EVENT is a C union.
      HandleWindowClose(&event.display, &done);
    }

    if (redraw && al_is_event_queue_empty(queue)) {
      DrawAllWindows();
      redraw = false;
    }
  }

  DestroyAllWindows();
  al_destroy_event_queue(queue);

  return 0;
}
