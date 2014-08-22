#ifndef SIMIT_STORAGE_H
#define SIMIT_STORAGE_H

#include "irvisitors.h"

#include <cstdlib>
#include <vector>
#include <map>
#include <memory>

namespace simit {
namespace internal {

class Storage {
 public:
  Storage(int size) : size(size) { data = malloc(size); }
  ~Storage() { free(data); }

  void *getData() { return data; }
  int getSize() const { return size; }

 private:
  void *data;
  int size;
};

class TemporaryAllocator : IRVisitor {
 public:
  TemporaryAllocator() {}

  std::map<IRNode*, void*> allocateTemporaries(Function *f);
  std::vector<std::shared_ptr<Storage>> getTemporaries() const {return storage;}

 private:
  std::vector<std::shared_ptr<Storage>> storage;
  std::map<IRNode*, void*> temps;
};

}} // namespace simit::internal
#endif
