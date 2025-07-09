#include "extern_template.h"

// Non-extern instantiation of the template. This is where the template is instantiated.
// This is the only file where the template is instantiated.
template std::ostream &print(std::ostream &os, const std::string &str);