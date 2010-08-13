#include "SingletonClasses.h"

int FromCpp::getValue() const { return 20; }

PluggableSingleton<FromHeader, false> PluggableSingleton<FromHeader, false>::_s;
PluggableSingleton<FromCpp, true> PluggableSingleton<FromCpp, true>::_s;
