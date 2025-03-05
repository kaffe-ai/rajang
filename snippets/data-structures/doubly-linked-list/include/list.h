/**
 * @authors
 * Steffen Viken Valvaag <steffenv@cs.uit.no> 
 * Odin Bjerke <odin.bjerke@uit.no>
 * Tord Mathaissen <https://github.com/omega-twm>
 */

#ifndef LIST_H
#define LIST_H

#include "defs.h"

#include <stdlib.h>

struct list;

/**
 * Type of list. `list_t` is an alias for `struct list`
 */
typedef struct list list_t;

/**
 * @brief Create a new, empty list that uses the given comparison function
 * to compare list items in relevant functions (e.g. `list_contains`).
 * @param cmpfn: reference to comparison function
 * @returns A pointer to the newly allocated list, or `NULL` on failure.
 */
list_t *list_create(cmp_fn cmpfn);

/**
 * @brief Destroy a list, and optionally its items.
 * @param list: pointer to list
 * @param item_free: nullable. If present, called on all items
 */
void list_destroy(list_t *list, free_fn item_free);

/**
 * @brief Get the number of items in a given list, colloquially referred to as its length
 * @param list: pointer to list
 * @returns Number of items in `list`
 */
size_t list_length(list_t *list);

/**
 * @brief Add an item to the start of the given list
 * @param list: pointer to list
 * @param item: pointer to item to be added
 * @returns 0 on success, otherwise a negative error code
 */
int list_addfirst(list_t *list, void *item);

/**
 * @brief Add an item to the end of the given list
 * @param list: pointer to list
 * @param item: pointer to item to be added
 * @returns 0 on success, otherwise a negative error code
 */
int list_addlast(list_t *list, void *item);

/**
 * @brief Remove the first item from the given list
 * @param list: pointer to list
 * @returns A pointer to the removed item
 * @warning should panic if list is empty
 */
void *list_popfirst(list_t *list);

/**
 * @brief Remove the last item from the given list
 * @param list: pointer to list
 * @returns A pointer to the removed item
 * @warning should panic if list is empty
 */
void *list_poplast(list_t *list);

/**
 * @brief Removes the first occurance of an item from the list, using the comparinson function
 * @param list: pointer to list
 * @param item: pointer to an item that compares as equial, usint the list cmpfn
 * @returns Apointer to the removed item, or NULL if not found
 */
void *list_remove(list_t *list, void *item);



/**
 * @brief Search for an item in the given list
 * @param list: pointer to list
 * @param item: pointer to an item that compares as equal, using the list cmpfn
 * @returns 1 if the item was found, otherwise 0
 */
int list_contains(list_t *list, void *item);

/**
 * @brief Sorts the items of the given list, using the comparison function
 * of the list to determine the ordering of the items.
 * @param list: pointer to list
 * @note Items are sorted in `descending` order, meaning each element is `<=` than the next.
 */
void list_sort(list_t *list);

/**
 * Type of list iterator. `list_iter_t` is an alias for `struct list_iter`
 */
typedef struct list_iter list_iter_t;

/**
 * @brief Create an iterator for the given list
 * @param list: pointer to list
 * @returns A pointer to the newly allocated iterator, or `NULL` on failure.
 */
list_iter_t *list_createiter(list_t *list);

/**
 * @brief Destroy a list iterator. Does not free the underlying list
 * @param iter: pointer to iterator
 */
void list_destroyiter(list_iter_t *iter);

/**
 * @brief Check if the given list iterator has reached the end of the underlying list
 * @param iter: pointer to iterator
 * @returns 0 if iterator is exhausted, otherwise 1
 */
int list_hasnext(list_iter_t *iter);

/**
 * @brief Get the next item from the underlying list
 * @param iter: pointer to iterator
 * @returns A pointer to the next item
 */
void *list_next(list_iter_t *iter);

/**
 * @brief Reset the given iterator to the first item in the underlying list
 * @param iter: pointer to iterator
 */
void list_resetiter(list_iter_t *iter);

#endif /* LIST_H */

