#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#define W 640
#define H 400

static float t = 1.0;

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP *S; /* Screen */
ALLEGRO_LOCKED_REGION *screenRegion;

void lock_screen() {
  screenRegion = al_lock_bitmap(S, ALLEGRO_PIXEL_FORMAT_ANY,
    ALLEGRO_LOCK_READWRITE);
}

void unlock_screen() {
  al_unlock_bitmap(S);
}

void flip() {
  unlock_screen();
  al_set_target_backbuffer(disp);
  al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ZERO);
  al_draw_bitmap(S, 0, 0, 0);
  al_flip_display();
  lock_screen();
}

void draw() {
  int x, y, i, j, pitch;
  uint32_t *data;
  uint32_t n;

  al_set_target_bitmap(S);
  data = (int32_t *)screenRegion->data;
  pitch = screenRegion->pitch / 4; /* Must be divisible by 4*/

  j = 0;
  for (y = 0; y < H; y++) {
    i = j;
    for (x = 0; x < W; x++) {
      n = (uint32_t)(t * x * y) % 256;
      data[i] = (255 << 24) | n;
      i++;
    }
    j += pitch; /* May even be negative */
  }
}

int main() {
  al_init();
  al_install_keyboard();

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  disp = al_create_display(W, H);

  al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ABGR_8888);
  al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_FORCE_LOCKING);
  S = al_create_bitmap(W, H);
  lock_screen();

  al_register_event_source(queue, al_get_keyboard_event_source());
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
    } else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) ||
               (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)) {
      done = true;
    }

    if (redraw && al_is_event_queue_empty(queue)) {
      t *= 1.0001;
      draw();
      flip();
      redraw = false;
    }
  }

  al_destroy_bitmap(S);
  al_destroy_display(disp);
  al_destroy_event_queue(queue);

  return 0;
}
