#ifndef FEATURES_H
#define FEATURES_H

#define weak __attribute__((__weak__))
#define hidden __attribute__((__visibility__("hidden")))
#define weak_alias(from, to)                                                   \
  extern __typeof(from) to __attribute__((__weak__, __alias__(#from)))

#define __TODO(msg)                                                            \
  ({                                                                           \
    _Static_assert(0, "Unimplemented: " msg);                                  \
    0;                                                                         \
  })

#endif
