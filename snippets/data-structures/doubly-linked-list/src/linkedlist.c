#include "defs.h"
#include "list.h"
#include "printing.h"

#include <stdlib.h>


typedef struct lnode lnode_t;
struct lnode {
  lnode_t *next;
  lnode_t *prev;
  void *item;
};

struct list {
  lnode_t *head;
  lnode_t *tail;
  size_t length;
  cmp_fn cmpfn;
};

struct list_iter {
  list_t *list;
  lnode_t *node;
};


static lnode_t *newnode(void *item) {
  lnode_t *newNode;
  newNode = malloc(sizeof *newNode);
  if (NULL == newNode) {
    pr_error("Failed to allocate new node for linked list\n");
    return NULL; 
  }

  newNode->next = NULL;
  newNode->prev = NULL;
  newNode->item = item;

  return newNode;
}

list_t *list_create(const cmp_fn cmpfn) {
  if (NULL == cmpfn) {
    pr_error("Failed compare function not given %s, %d\n", __FILE__, __LINE__);
    return NULL;
  }

  list_t *newList;
  newList = malloc(sizeof *newList);
  if (NULL == newList) {
    pr_error("Failed to allocate memory for list %s, %d\n", __FILE__, __LINE__);
    return NULL;
  }
  newList->head = NULL;
  newList->tail = NULL;
  newList->length = 0;
  newList->cmpfn = cmpfn;

  return newList;
}

void list_destroy(list_t *list, free_fn item_free) {
  if (NULL == list) {
    pr_info("List is already empty\n");
    return;
  }

  lnode_t *iter = list->head;
  // iterate through the whole list and free each node.
  // If a item_free funciton is provided we call it every node->data
  while (NULL != iter) {
    lnode_t *next = iter->next;
    if (NULL != item_free) item_free(iter->item);
    free(iter);
    iter = next; 
  }

  list->head = NULL;
  list->tail = NULL;
  free(list);
}

size_t list_length(list_t *list) { return list->length; }

int list_addfirst(list_t *list, void *item) {
  if (NULL == list || NULL == item) {
    pr_error("List parameter and item parameter not given\n");
    return -1; 
  }

  lnode_t *node;
  node = newnode(item);

  // if the list is empty we set the new node as both head and tail
  if (0 == list->length) {
    list->head = node;
    list->tail = node;
  }

  // if it is not empty we set the new node as the head node and update the old head node
  if (0 < list->length) {
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
  }

  list->length += 1;

  return 0;
}

int list_addlast(list_t *list, void *item) {
  if (NULL == list || NULL == item) {
    pr_error("List parameter and item parameter not given\n");
    return -1; 
  }

  lnode_t *node;
  node = newnode(item);
  
  // if the list is empty, we set the new node as both head and tail
  if (0 == list->length) {
    list->head = node;
    list->tail = node;
  }

  // if it is not emprt we set the new node as the tail node and update the old tail node
  if (0 < list->length) {
    node->prev = list->tail;
    list->tail->next = node;
    list->tail = node;
  }
  
  list->length += 1;

  return 0;
}

void *list_popfirst(list_t *list) {
  if (NULL == list) PANIC("List is empty, PANICING(exiting)\n");
  
  lnode_t *oldHead = list->head;
  void *returnData = list->head->item;

  // We're removing the first item of the list so we go next
  list->head = list->head->next;
  
  // if the list is now empty, we update the lists tail node accordingly
  if (NULL == list->head) {
    list->tail = NULL;
  }

  free(oldHead);
  list->length -= 1;

  return returnData;
}

void *list_poplast(list_t *list) {
  if (NULL == list) PANIC("List is empty, PANICING(exiting)\n");

  lnode_t *oldTail = list->tail;
  void *returnData = list->tail->item;

  list->tail = list->tail->prev;

  // if the list is now empty, we update the lists head node accordingly
  if (NULL == list->tail) {
    list->head = NULL;
  }

  free(oldTail);
  list->length -= 1;

  return returnData;
}

int list_contains(list_t *list, void *item) {
  lnode_t *iter = list->head;

  while (NULL != iter) {
    if (list->cmpfn(iter->item, item) == 0) return 1;
    iter = iter->next;
  }

  return 0;
}

void *list_remove(list_t *list, void *item)
{
  if (NULL == list || NULL == item) return NULL;

  lnode_t *iter = list->head;
  void* returnData = NULL;

  // iterate through list and use compare on each item in list
  // compare function returns 0 when the items are equal
  while (NULL != iter) {
    if (list->cmpfn(iter->item, item) == 0) {

      // case when item is found at head
      // since its the head node head->prev and iter->prev 
      // should both be NULL
      if (NULL == iter->prev) {
        returnData = list->head->item;
        list->head = list->head->next;
        
        // check if enw head exists before setting prev
        if (NULL != list->head) {
          list->head->prev = NULL;
        } else {
          // list is now empty, update tail
          list->tail = NULL;
        }
        
        list->length -= 1;
        free(iter);
        return returnData;
      }

      // case when item is found at tail
      if (NULL == iter->next) {
        returnData= list->tail->item;

        list->tail = list->tail->prev;
        if (NULL != list->tail) {
          list->tail->next = NULL;
        } else {
          list->head = NULL;
        }

        list->length -= 1;
        free(iter);
        return returnData;
      }

      // case for middle node
      iter->prev->next = iter->next;
      iter->next->prev = iter->prev;
      returnData = iter->item;

      free(iter);
      list->length -= 1;

      return returnData;
    }

    // go next
    iter = iter->next;
  }

  // item is not found so returns NULL
  return NULL;
}


/* ---- mergesort: Steffen Viken Valvaag ---- */


/*
 * Merges two sorted lists a and b using the given comparison function.
 * Only assigns the next pointers; the prev pointers will have to be
 * fixed by the caller.  Returns the head of the merged list.
 */

static lnode_t *merge(lnode_t *a, lnode_t *b, cmp_fn cmpfn) {
  lnode_t *head, *tail;

  if (cmpfn(a->item, b->item) < 0) {
    head = tail = a;
    a = a->next;
  } else {
    head = tail = b;
    b = b->next;
  }

  /* Now repeatedly pick the smallest head node */
  while (a && b) { 
    if (cmpfn(a->item, b->item) < 0) {
      tail->next = a;
      tail = a;
      a = a->next;
    } else {
      tail->next = b;
      tail = b;
      b = b->next;
    }
  }

  /* Append the remaining non-empty list (if any) */
 if (a) {
    tail->next = a;
 } else {
    tail->next = b;
 }

  return head;
}

/**
 * Splits the given list in two halves, and returns the head of
 * the second half.
 */ 
static lnode_t *splitlist(lnode_t *head) {
  /* Move two pointers, a 'slow' one and a 'fast' one which moves
   * twice as fast.  When the fast one reaches the end of the list,
   * the slow one will be at the middle.
   */

  lnode_t *slow = head;
  lnode_t *fast = head->next;

  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
  }

  /* Now 'cut' the list and return the second half */
  lnode_t *half = slow->next;
  slow->next = NULL;

  return half;
}

/**
 * Recursive merge sort.  This function is named mergesort_ to avoid
 * collision with the mergesort function that is defined by the standard
 * library on some platforms.
 */
static lnode_t *mergesort_(lnode_t *head, cmp_fn cmpfn){
  if (head->next == NULL) {
    return head;
  }

  lnode_t *half = splitlist(head);
  head = mergesort_(head, cmpfn);
  half = mergesort_(half, cmpfn);

  return merge(head, half, cmpfn);
}

void list_sort(list_t *list) {
  /* Recursively sort the list */
  list->head = mergesort_(list->head, list->cmpfn);

  /* Fix the tail and prev links */
  lnode_t *prev = NULL;
  for (lnode_t *n = list->head; n != NULL; n = n->next) {
    n->prev = prev;
    prev = n;
  }
  list->tail = prev;
}


list_iter_t *list_createiter(list_t *list) {
  if (NULL == list) {
    pr_error("Given list is empty\n");
    return NULL;
  }

  list_iter_t *iter;  
  iter = malloc(sizeof *iter);
  if (NULL == iter) {
    pr_error("Failed to allocate list iter\n");
    return NULL;
  }

  iter->list = list;
  iter->node = list->head;

  return iter;
}

void list_destroyiter(list_iter_t *iter) { if (iter) free(iter); }

int list_hasnext(list_iter_t *iter) {
  if (NULL == iter->node) return 0;

  return 1;
}

void *list_next(list_iter_t *iter) {
  if (NULL == iter) {
    return NULL;
  }

  void *returnData = iter->node->item;

  if (list_hasnext(iter)) {
    iter->node = iter->node->next;
  }

  return returnData;
}

void list_resetiter(list_iter_t *iter) {
  if (NULL == iter) {
    return;
  } 

  iter->node = iter->list->head;  
}

