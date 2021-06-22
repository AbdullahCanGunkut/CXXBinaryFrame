#include <CXXBinaryFrameTypename.h>

void CXXBinaryLoader::CXXBinaryFrame::GetNumArrayPointers(const std::string& typename_str ,
std::vector<unsigned>& array_dimension_size , unsigned& pointer_count){
  for (unsigned i = 0; i < typename_str.size(); i++){
    char __char = typename_str[i];
    if (__char == 'A'){//Check if Typename have an array dimension !
    size_t location = 0x00;//Readed numeric characters count !
    unsigned count = std::stoul(std::string(&typename_str[i + 1]) , &location , 0);
    if (location){
      if (typename_str[i + location + 1] == '_')
      {array_dimension_size.push_back(count);i += location + 1;}
      else break;
    }
    else break;
    }
    else if (__char == 'P')
    pointer_count++;
    else break;

  }
}
