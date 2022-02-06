#include <cairo.h>

typedef struct CairoNative {
  cairo_surface_t *surface;
  cairo_t *cr;
} Cairo_Context_Native;
struct Cairo_Context;

void Cairo_InitContext(struct Cairo_Context *ctx, int width, int height);
void Cairo_DestroyContext(struct Cairo_Context *ctx);
void Cairo_WriteToPNG(struct Cairo_Context *ctx, const char *fileName, int len);
void Cairo_MoveTo(struct Cairo_Context *ctx, float x, float y);
void Cairo_LineTo(struct Cairo_Context *ctx, float x, float y);
void Cairo_Stroke(struct Cairo_Context *ctx);
