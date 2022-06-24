#include "Or.h"

void Or::jumping(const uint32_t &to, const uint32_t &from) {
  int label = to != 0 ? to : new_label();
  expr1()->jumping(label, 0);
  expr2()->jumping(to, from);
  if (!to) {
    emit_label(label);
  }
}