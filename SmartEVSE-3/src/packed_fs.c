#include <stddef.h>
#include <time.h>
#if defined(__cplusplus)
extern "C" {
#endif
const char *mg_unlist(size_t no) { (void) no; return NULL; }
const char *mg_unpack(const char *name, size_t *size, time_t *mtime) {
    if (size) *size = 0;
    if (mtime) *mtime = 0;
    (void) name;
    return NULL;
}
#if defined(__cplusplus)
}
#endif
