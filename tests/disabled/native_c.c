typedef struct NativeC_NatBuf_Native {
  OBERON_INTEGER nativeQ;
  OBERON_INTEGER nativeR;
} NativeC_NatBuf_Native;

typedef struct NativeC_NatBuf NativeC_NatBuf;

typedef void (*NativeC_CallbackFuncNative)(OBERON_INTEGER);

void NativeC_SetNativeVal(NativeC_NatBuf *b, OBERON_INTEGER val) {
  ((NativeC_NatBuf_Native*)b)->nativeQ = val;
  ((NativeC_NatBuf_Native*)b)->nativeR = val + 1;
}

void NativeC_CallNative(NativeC_NatBuf *b) {
  NativeC_NatBuf_Native* nat = (NativeC_NatBuf_Native*)b;
  printf("Native code called, buf.nativeQ = %d, nativeR = %d.\n", nat->nativeQ, nat->nativeR);
}

void NativeC_NativeCallback(OBERON_INTEGER i, NativeC_CallbackFuncNative f) {
  printf("About to call callback with i=%d.\n", i+1);
  f(i+1);
  printf("NativeCallback completed\n");
}
