#pragma once
#include <string>
#include <string.h>
#include <vector>
#include <typeinfo>


namespace CXXBinaryLoader{

namespace CXXBinaryFrame{

void GetNumArrayPointers(const std::string& typename_str ,
std::vector<unsigned>& array_dimension_size , unsigned& pointer_count);


}
}
