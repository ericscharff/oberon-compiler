typedef struct LangExtensions_NatBuf_Native {
  OBERON_INTEGER nativeQ;
  OBERON_INTEGER nativeR;
} LangExtensions_NatBuf_Native;

typedef struct LangExtensions_NatBuf LangExtensions_NatBuf;

typedef void (*LangExtensions_CallbackFuncNative)(OBERON_INTEGER);

void LangExtensions_SetNativeVal(LangExtensions_NatBuf *b, OBERON_INTEGER val) {
  ((LangExtensions_NatBuf_Native*)b)->nativeQ = val;
  ((LangExtensions_NatBuf_Native*)b)->nativeR = val + 1;
}

void LangExtensions_CallNative(LangExtensions_NatBuf *b) {
  LangExtensions_NatBuf_Native* nat = (LangExtensions_NatBuf_Native*)b;
  printf("Native code called, buf.nativeQ = %d, nativeR = %d.\n", nat->nativeQ, nat->nativeR);
}

void LangExtensions_NativeCallback(OBERON_INTEGER i, LangExtensions_CallbackFuncNative f) {
  printf("About to call callback with i=%d.\n", i+1);
  f(i+1);
  printf("NativeCallback completed\n");
}
