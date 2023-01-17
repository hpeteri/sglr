#ifndef SGLR_ASSERT_H
#define SGLR_ASSERT_H

#if defined(SGLR_DEBUG_BUILD)

#define SGLR_ASSERT(expression)                 \
  { if(!(expression)){                          \
      printf("sglr_assertion failed:\n");       \
      printf("file: %s\n", __FILE__);           \
      printf("file: %s\n", __FILE__);                      \
      printf("func: '%s' at line '%d'\n", __func__, __LINE__);  \
      *(int*)NULL = 0;}}
#else

#define SGLR_ASSERT(expression) 

#endif

#endif
