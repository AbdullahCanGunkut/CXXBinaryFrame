#include <CXXBinaryFrameFacilitateStatic.h>




#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wterminate"
#pragma GCC diagnostic ignored "-Wnarrowing"
#pragma GCC diagnostic ignored "-Wpointer-arith"

#elif defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4267)

#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wterminate"
#pragma clang diagnostic ignored "-Wnarrowing"
#pragma clang diagnostic ignored "-Wpointer-arith"


#endif

#define TargetNamespace CXX_BINARY_FRAME_FACILITATE_STATIC_NAMESPACE



using CXX_BINARY_FRAME_NAMESPACE::ExtentArray;
using CXX_BINARY_FRAME_NAMESPACE::ObjPtr;
using CXX_BINARY_FRAME_NAMESPACE::size_type;
using CXX_BINARY_FRAME_NAMESPACE::BinaryFrameBuffer;
using CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase;
using CXX_BINARY_FRAME_NAMESPACE::PointerStorage;




#pragma region FrameObjectPackage

TargetNamespace::FrameObjectPackage::FrameObjectPackage(const ObjectType& arr , const std::string& name) : Base(arr , name){}

size_type TargetNamespace::FrameObjectPackage::Encode(BinaryFrameBuffer& stack) noexcept(false){
unsigned total_size = 0 , iterator = 0;

for (PointerStorage<FrameObjectBase>& object : this->obj){
if (object.Check())
CXX_BINARY_FRAME_THROW(std::runtime_error ,
(std::string("Object is null at Index : ") + std::to_string(iterator) +  " and Name : " + object->name ));
total_size += object->Encode(stack);
}

return total_size;
}

size_type TargetNamespace::FrameObjectPackage::Decode(void* ref , unsigned remain) noexcept(false){
unsigned total_size = 0 , iterator = 0;

for (PointerStorage<FrameObjectBase>& object : this->obj){
if (object.Check())
CXX_BINARY_FRAME_THROW(std::runtime_error ,
(std::string("Object is null at Index : ") + std::to_string(iterator) +  " and Name : " + object->name ));
total_size += object->Decode((unsigned char*)ref + total_size , remain - total_size);
iterator++;
}

return total_size;
}

ObjPtr TargetNamespace::FrameObjectPackage::GetObj(const IndexArray& arr) noexcept(false){return (ObjPtr)&(this->obj[arr[0]]);}
size_type TargetNamespace::FrameObjectPackage::GetSizeof() noexcept(false){return this->obj.size();}
ExtentArray TargetNamespace::FrameObjectPackage::GetExtent() noexcept(false){return ExtentArray({this->obj.size()});}

#pragma endregion



#pragma region FrameObjectString
/*
BINARY STRUCT :
SIZEOF | STR (CHAR)[SIZEOF]
*/
TargetNamespace::FrameObjectString::FrameObjectString(const std::string& str , const std::string& name )  : Base(str , name){}

size_type TargetNamespace::FrameObjectString::Encode(BinaryFrameBuffer& stack) noexcept(false) {
unsigned loc = stack.size() ,
__sizeof = sizeof(size_type) + this->obj.size();

stack.resize(loc + __sizeof);
*(size_type*)&stack[loc] = this->obj.size();
memcpy(&stack[loc + sizeof(size_type)] , &this->obj[0] , this->obj.size());

return __sizeof;
}

size_type TargetNamespace::FrameObjectString::Decode(void* ref , unsigned remain) noexcept(false){
CHECK_REMAIN(remain , sizeof(size_type) , "Index out of Range !");

const
unsigned __sizeof = *(size_type*)ref;
remain -= sizeof(size_type);

CHECK_REMAIN(remain , __sizeof , "Index out of Range !");

this->obj.resize(__sizeof);
memcpy(&this->obj[0] , (unsigned char*) ref + sizeof(size_type) , __sizeof);
return __sizeof + sizeof(size_type);
}

ObjPtr TargetNamespace::FrameObjectString::GetObj (const IndexArray& arr)  noexcept(false){return (ObjPtr)&this->obj;}
size_type TargetNamespace::FrameObjectString::GetSizeof() noexcept(false){return this->obj.size();}
ExtentArray TargetNamespace::FrameObjectString::GetExtent() noexcept(false){return ExtentArray({this->obj.size()});}

#pragma endregion


#if defined(__GNUC__)
#pragma GCC diagnostic pop

#elif defined(_MSC_VER)
#pragma warning(pop)
#elif defined(__clang__)
#pragma clang diagnostic pop

#endif
