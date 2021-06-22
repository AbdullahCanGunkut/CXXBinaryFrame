#pragma once
#include <type_traits>
#include <CXXBinaryLoaderBinaryFrame.hpp>
#include <CXXBinaryFrameTypename.h>
#include <exception>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wterminate"
#pragma GCC diagnostic ignored "-Wnarrowing"
#pragma GCC diagnostic ignored "-Wpointer-arith"





template <typename T>
#if CXX_STANDARD_VERSION >= 20
using GetRawType = typename std::remove_pointer<typename std::remove_cvref<typename std::remove_all_extents<T>::type>::type>::type;
#else
using GetRawType = typename std::remove_pointer<typename std::remove_reference<typename std::remove_volatile<typename std::remove_all_extents<T>::type>::type >::type >::type;

#endif



#define CLASSIC_ASSERT_FOR_FACILITATE \
static_assert(!std::is_base_of<FrameObjectBase , T>::value ,  "Type isn't must be derive of FrameObjectBase !");

#define BINARY_FRAME_POINTER(TARGET) PointerStorage<FrameObjectBase>\
(static_cast<FrameObjectBase*>(new CXXBinaryLoader::CXXBinaryFrame::FrameObjectPointer<\
GetRawType<decltype(TARGET)>>(TARGET , (size_type)(sizeof(TARGET) / sizeof(GetRawType<decltype(TARGET)>)) )))

namespace CXXBinaryLoader{

namespace CXXBinaryFrame{


typedef unsigned CountType;


template<typename T>
unsigned CalculateIndexFromIndexArray(const IndexArray& arr) noexcept{
using namespace std::literals::string_literals;

static_assert(std::is_array<T>::value , "T is must be array !" );


static constexpr CountType __rank = std::rank<T>::value ,
                           MAXIMUN_INDEX = sizeof(T) / sizeof(typename std::remove_all_extents<T>::type);


std::vector<unsigned> t_array_dim;

{
unsigned pointer_count;
GetNumArrayPointers(typeid(T).name() , t_array_dim , pointer_count);
}
if (arr.size() != __rank)return NULL;

unsigned count = 1 , index = 0;
const unsigned last = arr.size() - 1;

for (int i = arr.size() - 1; i >= 0; i--){
count *= (i == last ?  1 : t_array_dim[i + 1]) ,index += count * arr[i];
if (index >= MAXIMUN_INDEX)
throw std::out_of_range(

#ifdef __cpp_lib_format
std::format("Index out of range ! Maximun Index : {:d} , Current Index : {:d}" , MAXIMUN_INDEX - 1  , i)
#else
"Index out of range ! Maximun Index : "s + std::to_string(MAXIMUN_INDEX - 1) + " , Current Index : " + std::to_string(i)
#endif
);
}

return index;
}

template <typename T>
//[DATA]
class FrameObjectArray : public FrameObject<T> {//An Array Encode/Decoder. T must be type of an array.

CLASSIC_ASSERT_FOR_FACILITATE;

using Base = FrameObject<T>;
typedef typename std::remove_all_extents<T>::type RawType;

public:

static_assert(std::is_array<T>::value , "T is must be array type !");
FrameObjectArray(T arr , const ObjectName& name = "") : Base(arr , name){}

virtual size_type Encode(BinaryFrameBuffer& stack) noexcept{
const unsigned long location = stack.size();
stack.resize(stack.size() + sizeof(T));
memcpy(&stack[location] , this->obj , sizeof(T));
return sizeof(T);
}

virtual size_type Decode(void* ref , unsigned remain) noexcept{
CHECK_REMAIN(remain , sizeof(T) , "Index out of Range !");
memcpy(this->obj , ref , sizeof(T));
return sizeof(T);
}

virtual ObjPtr GetObj (const IndexArray& arr = IndexArray()) noexcept{
return  ((ObjPtr)this->obj) +
(arr.size() ? CalculateIndexFromIndexArray<T>(arr) * sizeof(RawType) : 0);

}


};

template <typename T> //[COUNT] | [DATA]
class FrameObjectPointer : public FrameObject<T*>{

CLASSIC_ASSERT_FOR_FACILITATE;

using Base = FrameObject<T*>;
static_assert(!std::is_pointer<T>::value && !std::is_array<T>::value , "T is must have'nt a Pointer or Array ! (Must be Simple Type)");

public:

FrameObjectPointer(T* obj , size_type count , const ObjectName& name = "") : Base(obj , name) , count(count){}
virtual ~FrameObjectPointer(){if (this->isDestroyable && this->obj)delete [] this->obj;}

virtual size_type Encode(BinaryFrameBuffer& stack) noexcept{
if (!this->obj)throw std::runtime_error("Obj is null !");

const unsigned long location = stack.size();
stack.resize(stack.size() + sizeof(T) * this->count + sizeof(size_type));
*(size_type*)&stack[location] = this->count;
memcpy(&stack[location + sizeof(size_type)] , this->obj , sizeof(T) * this->count);
return sizeof(T) * this->count + sizeof(size_type);
}

virtual size_type Decode(void* ref , unsigned remain) noexcept{

CHECK_REMAIN(remain , sizeof(size_type) , "Index out of Range ! (count wasn't get)");
this->count = *(size_type*)ref , remain -= sizeof(size_type);

unsigned allocated_size = sizeof(T) * this->count;
CHECK_REMAIN(remain , allocated_size , "Index out of Range !");
allocated_size += sizeof(size_type);

if (isDestroyable && this->obj)delete[] this->obj;
else if (!isDestroyable) isDestroyable = !isDestroyable;

this->obj = (T*)::operator new(sizeof(T) * this->count);
memcpy(this->obj , ref + sizeof(size_type) , sizeof(T) * this->count);
return allocated_size;
}

virtual ObjPtr GetObj (const IndexArray& arr = IndexArray()) noexcept{
if (arr[0] >= this->count)CXX_BINARY_FRAME_THROW(std::out_of_range , "[T*] Index out of Range ! ");

return (ObjPtr)&(this->obj[arr[0]]);
}

virtual size_type GetSizeof() noexcept{return sizeof(T) * this->count;}
virtual ExtentArray GetExtent() noexcept{return ExtentArray({this->count});}


protected:
size_type count;
bool isDestroyable = 0;
};




template <typename T> //[COUNT] | [DATA]
class FrameObjectVector : public FrameObject<std::vector<T>>{
CLASSIC_ASSERT_FOR_FACILITATE;
static_assert(!std::is_pointer<T>::value && !std::is_array<T>::value  , "T is must have'nt a Pointer or Array ! (Must Be Simple Type)");


using Base = FrameObject<std::vector<T>>;

public:
typedef std::vector<T> ObjectType;

FrameObjectVector(const ObjectType& obj) : Base(obj){}
virtual ~FrameObjectVector (){}



virtual size_type Encode(BinaryFrameBuffer& stack) noexcept{
if (!this->obj)throw std::runtime_error("Obj is null !");


const
unsigned count = this->obj.size();

const unsigned long location = stack.size();
stack.resize(stack.size() + sizeof(T) * count + sizeof(size_type));
*(size_type*)&stack[location] = count;
memcpy(&stack[location + sizeof(size_type)] , this->obj.data() , sizeof(T) * count);
return sizeof(T) * count + sizeof(size_type);
}

virtual size_type Decode(void* ref , unsigned remain) noexcept{

CHECK_REMAIN(remain , sizeof(size_type) , "Index out of Range ! (count wasn't get)");
const
unsigned count = *(size_type*)ref ;
remain -= sizeof(size_type);
this->obj.resize(count);

unsigned allocated_size = sizeof(T) * count;
CHECK_REMAIN(remain , allocated_size , "Index out of Range !");
allocated_size += sizeof(size_type);

memcpy(this->obj.data() , ref + sizeof(size_type) , sizeof(T) * count);
return allocated_size;
}

virtual ObjPtr GetObj (const IndexArray& arr = IndexArray()) noexcept{
if (arr[0] >= this->obj.size())CXX_BINARY_FRAME_THROW(std::out_of_range , "[vector<T>] Index out of Range !");
return (ObjPtr)&(this->obj[arr[0]]);
}

virtual size_type GetSizeof() noexcept{return sizeof(T) * this->obj.size();}
virtual ExtentArray GetExtent() noexcept{return ExtentArray({this->obj.size()});}



};





}

}
#pragma GCC diagnostic pop
