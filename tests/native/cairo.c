#include <cairo.h>

typedef struct CairoNative {
  cairo_surface_t *surface;
  cairo_t *cr;
} Cairo_Context_Native;

typedef struct Cairo_Context {
  Cairo_Context_Native _ctx;
} Cairo_Context;

void Cairo_InitContext(Cairo_Context *ctx, int width, int height) {
  ctx->_ctx.surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
  ctx->_ctx.cr = cairo_create(ctx->_ctx.surface);
}

void Cairo_DestroyContext(Cairo_Context *ctx) {
  cairo_destroy(ctx->_ctx.cr);
  cairo_surface_destroy(ctx->_ctx.surface);
}

void Cairo_WriteToPNG(Cairo_Context *ctx, const char *fileName, int len) {
  cairo_surface_write_to_png(ctx->_ctx.surface, fileName);
}

void Cairo_MoveTo(Cairo_Context *ctx, float x, float y) {
  cairo_move_to(ctx->_ctx.cr, x, y);
}

void Cairo_LineTo(Cairo_Context *ctx, float x, float y) {
  cairo_line_to(ctx->_ctx.cr, x, y);
}

void Cairo_Stroke(Cairo_Context *ctx) {
  cairo_stroke(ctx->_ctx.cr);
}
