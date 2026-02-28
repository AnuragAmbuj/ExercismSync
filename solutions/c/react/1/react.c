#include "react.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

struct cell {
  int value;
  struct reactor *reactor;
  struct cell **dependencies;
  int num_dependencies;
  compute1 compute1_fn;
  compute2 compute2_fn;
  callback *callbacks;
  void **callback_contexts;
  int num_callbacks;
};

struct reactor {
  struct cell **cells;
  int num_cells;
};

struct reactor *create_reactor(void) {
  struct reactor *r = (struct reactor *)malloc(sizeof(struct reactor));
  r->cells = NULL;
  r->num_cells = 0;
  return r;
}

void destroy_reactor(struct reactor *r) {
  for (int i = 0; i < r->num_cells; ++i) {
    free(r->cells[i]->dependencies);
    free(r->cells[i]->callbacks);
    free(r->cells[i]->callback_contexts);
    free(r->cells[i]);
  }
  free(r->cells);
  free(r);
}

struct cell *create_input_cell(struct reactor *r, int initial_value) {
  struct cell *c = (struct cell *)malloc(sizeof(struct cell));
  c->value = initial_value;
  c->reactor = r;
  c->dependencies = NULL;
  c->num_dependencies = 0;
  c->compute1_fn = NULL;
  c->compute2_fn = NULL;
  c->callbacks = NULL;
  c->callback_contexts = NULL;
  c->num_callbacks = 0;

  r->cells = (struct cell **)realloc(r->cells, (r->num_cells + 1) *
                                                   sizeof(struct cell *));
  r->cells[r->num_cells++] = c;
  return c;
}

struct cell *create_compute1_cell(struct reactor *r, struct cell *dependency,
                                  compute1 compute_fn) {
  struct cell *c = create_input_cell(r, compute_fn(dependency->value));
  c->dependencies = (struct cell **)malloc(sizeof(struct cell *));
  c->dependencies[0] = dependency;
  c->num_dependencies = 1;
  c->compute1_fn = compute_fn;

  return c;
}

struct cell *create_compute2_cell(struct reactor *r, struct cell *dep1,
                                  struct cell *dep2, compute2 compute_fn) {
  struct cell *c = create_input_cell(r, compute_fn(dep1->value, dep2->value));
  c->dependencies = (struct cell **)malloc(2 * sizeof(struct cell *));
  c->dependencies[0] = dep1;
  c->dependencies[1] = dep2;
  c->num_dependencies = 2;
  c->compute2_fn = compute_fn;

  return c;
}

static int update_compute_cell(struct cell *c) {
  int old_value = c->value;
  if (c->num_dependencies == 1 && c->compute1_fn) {
    c->value = c->compute1_fn(c->dependencies[0]->value);
  } else if (c->num_dependencies == 2 && c->compute2_fn) {
    c->value =
        c->compute2_fn(c->dependencies[0]->value, c->dependencies[1]->value);
  }
  return old_value != c->value;
}

int get_cell_value(struct cell *c) { return c->value; }

void set_cell_value(struct cell *c, int new_value) {
  if (c->value != new_value) {
    c->value = new_value;
    for (int i = 0; i < c->reactor->num_cells; ++i) {
      struct cell *dependent_cell = c->reactor->cells[i];
      if (dependent_cell->num_dependencies > 0) {
        int updated = update_compute_cell(dependent_cell);
        if (updated) {
          for (int j = 0; j < dependent_cell->num_callbacks; ++j) {
            dependent_cell->callbacks[j](dependent_cell->callback_contexts[j],
                                         dependent_cell->value);
          }
        }
      }
    }
  }
}

callback_id add_callback(struct cell *c, void *context, callback cb) {
  c->callbacks = (callback *)realloc(c->callbacks,
                                     (c->num_callbacks + 1) * sizeof(callback));
  c->callback_contexts = (void **)realloc(
      c->callback_contexts, (c->num_callbacks + 1) * sizeof(void *));
  c->callbacks[c->num_callbacks] = cb;
  c->callback_contexts[c->num_callbacks] = context;
  return c->num_callbacks++;
}

void remove_callback(struct cell *c, callback_id id) {
  if (id < 0 || id >= c->num_callbacks) {
    return; // Invalid callback ID
  }

  for (int i = id; i < c->num_callbacks - 1; ++i) {
    c->callbacks[i] = c->callbacks[i + 1];
    c->callback_contexts[i] = c->callback_contexts[i + 1];
  }
  --c->num_callbacks;
  c->callbacks =
      (callback *)realloc(c->callbacks, c->num_callbacks * sizeof(callback));
  c->callback_contexts =
      (void **)realloc(c->callback_contexts, c->num_callbacks * sizeof(void *));
}
