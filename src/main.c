#include "pebble.h"

Window *main_window;
Layer *text_layer;
GRect bounds, frame;

void draw_text_layer(Layer *me, GContext *ctx) {
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_context_set_text_color(ctx, GColorWhite);
  frame = layer_get_frame(me);
  bounds = layer_get_bounds(me);
  graphics_draw_rect(ctx, GRect(-bounds.origin.x, -bounds.origin.y, frame.size.w, frame.size.h));
  graphics_draw_text(ctx, "Sample Text", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), bounds, GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
}

void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  bounds = layer_get_bounds(text_layer);
  frame = layer_get_frame(text_layer);
  bounds.origin.x += 1;
  frame.origin.x  -= 2;
  frame.size.w    += 4;
  layer_set_bounds(text_layer, bounds);
  layer_set_frame(text_layer, frame);
  layer_mark_dirty(text_layer);
}

void dn_click_handler(ClickRecognizerRef recognizer, void *context) {
  bounds = layer_get_bounds(text_layer);
  frame = layer_get_frame(text_layer);
  bounds.origin.x -= 1;
  frame.origin.x  += 2;
  frame.size.w    -= 4;
  layer_set_bounds(text_layer, bounds);
  layer_set_frame(text_layer, frame);
  layer_mark_dirty(text_layer);
}

void button_config(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, dn_click_handler);
}

void main_window_load(Window *window) {
  text_layer = layer_create(GRect(22, 50, 100, 30));
  layer_set_update_proc(text_layer, draw_text_layer);
  layer_add_child(window_get_root_layer(window), text_layer);
}

int main(void) {
  main_window = window_create();
  window_set_window_handlers(main_window, (WindowHandlers){.load = main_window_load,});
  window_set_click_config_provider(main_window, button_config);
  window_set_background_color(main_window, GColorBlack);
  window_set_fullscreen(main_window, true);
  window_stack_push(main_window, true);
  app_event_loop();
}