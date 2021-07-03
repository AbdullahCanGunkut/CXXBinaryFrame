#pragma once

#include <string>
#include <vector>
#include <memory>
#include <tuple>
#include <exception>
#include <typeinfo>
#include <string.h>
#include <fstream>
#include <iostream>
#include <type_traits>
#include <CXXBinaryFrameTypename.h>


/*
Visual Studio       _MSC_VER
gcc                 __GNUC__
clang               __clang__
emscripten          __EMSCRIPTEN__ (for asm.js and webassembly)
MinGW 32            __MINGW32__
MinGW-w64 32bit     __MINGW32__
MinGW-w64 64bit     __MINGW64__
*/


#define CXX_BINARY_FRAME_NAMESPACE CXXBinaryLoader::CXXBinaryFrame


#if defined(__GNUC__) || defined(__GNUG__)
#define CXX_BINARY_FRAME_INLINE
#elif defined(_MSC_VER)
#define CXX_BINARY_FRAME_INLINE __forceinline

#endif


/*Creating a default FrameObject*/
#define FRAME_OBJECT(TYPE ,OBJECT_NAME ,  ...) CXX_BINARY_FRAME_NAMESPACE::PointerStorage<CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase> \
((CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase*) \
new CXX_BINARY_FRAME_NAMESPACE::FrameObject<TYPE>(TYPE(__VA_ARGS__)  ,CXX_BINARY_FRAME_NAMESPACE::ObjectName(OBJECT_NAME)))

#define CXX_BINARY_FRAME_THROW(EXCEPTION , INFO) throw EXCEPTION(std::string("[File : ") + __FILE__ + " , Function : "  + __FUNCTION__ + " , Line : " + std::to_string(__LINE__) + "] " + INFO)
#define CHECK_REMAIN(REMAIN , MAXIMUN , INFO) if (REMAIN < MAXIMUN)CXX_BINARY_FRAME_THROW(std::out_of_range , INFO)
#define INDEX_ARRAY(...) CXX_BINARY_FRAME_NAMESPACE::IndexArray({__VA_ARGS__})


#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wterminate"
#pragma GCC diagnostic ignored "-Wnarrowing"
#pragma GCC diagnostic ignored "-Wpointer-arith"

#elif defined(_MSC_VER)

#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wterminate"
#pragma clang diagnostic ignored "-Wnarrowing"
#pragma clang diagnostic ignored "-Wpointer-arith"


#endif

namespace CXXBinaryLoader{
namespace CXXBinaryFrame{

typedef std::vector<unsigned char> BinaryFrameBuffer;
typedef void* ObjPtr;
typedef unsigned size_type;

class FrameObjectBase;

typedef std::vector<unsigned> IndexArray;
typedef std::vector<unsigned> ExtentArray;
typedef std::string ObjectName;


template <typename T>
class PointerStorage final{//A basic smart pointer for hold the any pointer class or fundamental.
static_assert(!std::is_pointer<T>::value , "T isn't must be a pointer type !");

public:

PointerStorage(T* target = nullptr) : target(target){}//
PointerStorage(const PointerStorage& storage) : target(storage.target){const_cast<PointerStorage&>(storage).target = nullptr;}
PointerStorage(PointerStorage&& storage) : target(storage.target){storage.target = nullptr;}

~PointerStorage(){if (target)delete target;}

PointerStorage& operator = (const PointerStorage& target) {

PointerStorage ref = const_cast<PointerStorage&>(target);
if (this->target)delete this->target;
this->target = ref.target;
ref.target = nullptr;
return *this;

}
//PointerStorage& operator = (PointerStorage&& target){ this->target = target.target , target.target = NULL; return *this;}
T* operator -> (){return this->target;}
T& operator * (){return *this->target;}
CXX_BINARY_FRAME_INLINE T* Get (){return this->target;}


CXX_BINARY_FRAME_INLINE bool Check(){return target != nullptr;}


private:
T* target;


};


class FrameObjectBase{/*A Base for FrameObjects.*/
public:
FrameObjectBase(const ObjectName& name) : name(name){}
virtual ~FrameObjectBase(){}
virtual std::string GetTypename() noexcept(false){return std::string("");}
virtual ExtentArray GetExtent () noexcept(false){
ExtentArray extent;
unsigned count;
GetNumArrayPointers(this->GetTypename() , extent , count);
return extent;
}
virtual size_type GetSizeof() noexcept(false){return 0x00;}
virtual size_type Encode(BinaryFrameBuffer& stack) noexcept(false){return 0x00;}//Write to ref.
virtual size_type Decode(void* ref , unsigned remain) noexcept(false){return 0x00;}//Read from ref.
virtual ObjPtr GetObj (const IndexArray& arr = IndexArray()) noexcept(false){return NULL;} //returning the current class or obj.

ObjPtr GetObj (unsigned index){return GetObj(IndexArray({index}));}

ObjectName name;
};

template <typename T>
class FrameObject : public FrameObjectBase{/*FrameObject contains class and fundamental types ...*/
using Base = FrameObjectBase;

public:

FrameObject(
typename std::conditional<!std::is_array<T>::value && !std::is_pointer<T>::value ,const T& , T>::type obj ,
const ObjectName& name = "") : Base(name){
if constexpr (std::is_array<T>::value)memcpy(this->obj , obj , sizeof(T));
else this->obj = obj;

}
virtual ~FrameObject(){}

std::string GetTypename() noexcept(false) override{return std::string(typeid(T).name());}//Get typename of T as string.
size_type GetSizeof() noexcept(false) override{return sizeof(T);} //Get sizeof T.

virtual size_type Encode(BinaryFrameBuffer& stack) noexcept(false){//Save the obj to the stack.

const unsigned long location = stack.size();
stack.resize(stack.size() + sizeof(T));

if constexpr (std::is_pointer<T>::value)
memcpy(&stack[location] , this->obj , sizeof(T));
else
memcpy(&stack[location] , &this->obj , sizeof(T));

return sizeof(T);
}

virtual size_type Decode(void* ref , unsigned remain) noexcept(false){//Load from ref as obj.

CHECK_REMAIN(remain , sizeof(T) ,  "Index out of Range !");

if constexpr (std::is_pointer<T>::value)
memcpy(this->obj , ref , sizeof(T));
else
memcpy(&this->obj , ref , sizeof(T));

return sizeof(T);
}

virtual ObjPtr GetObj (const IndexArray& arr = IndexArray()) noexcept(false){//Get current obj.
if constexpr (std::is_pointer<T>::value)//Check if type is pointer and return as pointer.
return (ObjPtr)this->obj;
else
return (ObjPtr)&this->obj;
}

protected:
T obj; //holding a object for encode and decode.
};





}

}

#if defined(__GNUC__)
#pragma GCC diagnostic pop

#elif defined(_MSC_VER)

#elif defined(__clang__)
#pragma clang diagnostic pop

#endif
