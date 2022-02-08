#include <cairo.h>

typedef struct CairoNative {
  cairo_surface_t *surface;
  cairo_t *cr;
} Cairo_Context_Native;

typedef struct Cairo_Context Cairo_Context;

void Cairo_InitContext(Cairo_Context *ctx, int width, int height) {
  Cairo_Context_Native *c = (Cairo_Context_Native*)ctx;
  c->surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  c->cr = cairo_create(c->surface);
}

void Cairo_DestroyContext(Cairo_Context *ctx) {
  Cairo_Context_Native *c = (Cairo_Context_Native*)ctx;
  cairo_destroy(c->cr);
  cairo_surface_destroy(c->surface);
}

void Cairo_WriteToPNG(Cairo_Context *ctx, const char *fileName, int len) {
  Cairo_Context_Native *c = (Cairo_Context_Native*)ctx;
  cairo_surface_write_to_png(c->surface, fileName);
}

void Cairo_MoveTo(Cairo_Context *ctx, float x, float y) {
  Cairo_Context_Native *c = (Cairo_Context_Native*)ctx;
  cairo_move_to(c->cr, x, y);
}

void Cairo_LineTo(Cairo_Context *ctx, float x, float y) {
  Cairo_Context_Native *c = (Cairo_Context_Native*)ctx;
  cairo_line_to(c->cr, x, y);
}

void Cairo_Stroke(Cairo_Context *ctx) {
  Cairo_Context_Native *c = (Cairo_Context_Native*)ctx;
  cairo_stroke(c->cr);
}
