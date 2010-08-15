#ifndef SINGLETON_TEST_CLASSES_H
#define SINGLETON_TEST_CLASSES_H

#include "PluggableSingleton.h"

class FromHeader
{
  public:
  int getValue() const { return 10; }

  protected:
  FromHeader() {}
};

class FromCpp
{
  public:
  int getValue() const;

  protected:
  FromCpp();
};

#endif
