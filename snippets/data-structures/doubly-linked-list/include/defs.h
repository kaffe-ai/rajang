/**
 * @authors
 * Odin Bjerke <odin.bjerke@uit.no>
 */

#ifndef DEFS_H
#define DEFS_H

#include <sys/cdefs.h>
#include <stdint.h>

#ifndef __fallthrough
/* attribute intentional switch case fallthrough (silence warning) */
#  define __fallthrough __attribute__((fallthrough))
#endif /* __fallthrough */

/**
 * @brief Type of comparison function
 *
 * @returns
 * - 0 on equality
 *
 * - >0 if a > b
 *
 * - <0 if a < b
 *
 * @note When passing references to comparison functions as parameters
 * typecast to cmp_fn if said functions' parameters are non-void pointers.
 */
typedef int (*cmp_fn)(const void *, const void *);

/**
 * @brief Type of free (resource deallocation) function
 * @note may be the actual `free` function, or another user-defined function
 */
typedef void (*free_fn)(void *);

/**
 * @brief Type of 64-bit hash function
 */
typedef uint64_t (*hash64_fn)(const void *);


#endif /* DEFS_H */

