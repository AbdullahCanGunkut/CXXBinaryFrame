#pragma once
#include <type_traits>
#include <CXXBinaryLoaderBinaryFrame.hpp>
#include <CXXBinaryFrameTypename.h>
#include <exception>



#define CXX_BINARY_FRAME_FACILITATE_STATIC_NAMESPACE CXX_BINARY_FRAME_NAMESPACE::CXXBinaryFrameFacilitateStatic


#define FRAME_OBJECT_STRING(...) CXX_BINARY_FRAME_NAMESPACE::PointerStorage\
<CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase>( \
(CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase*)new CXX_BINARY_FRAME_FACILITATE_STATIC_NAMESPACE::FrameObjectString(__VA_ARGS__))

#define FRAME_OBJECT_PACKAGE(...) CXX_BINARY_FRAME_NAMESPACE::PointerStorage\
<CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase>( \
(CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase*)new CXX_BINARY_FRAME_FACILITATE_STATIC_NAMESPACE::FrameObjectPackage(__VA_ARGS__))



namespace CXXBinaryLoader{

namespace CXXBinaryFrame{

namespace CXXBinaryFrameFacilitateStatic{


/*Holding the FrameObjects and you think it as Folder*/
class FrameObjectPackage : public FrameObject<std::vector<PointerStorage<FrameObjectBase >>> {//A FrameObject holder .
using Base = FrameObject<std::vector<PointerStorage<FrameObjectBase>>>;

public:
typedef std::vector<PointerStorage<FrameObjectBase>> ObjectType;


FrameObjectPackage(const ObjectType& arr = ObjectType() , const std::string& name = "");


virtual size_type Encode(BinaryFrameBuffer& stack) noexcept;
virtual size_type Decode(void* ref , unsigned remain) noexcept;

virtual ObjPtr GetObj (const IndexArray& arr = IndexArray()) noexcept;
virtual size_type GetSizeof() noexcept;
virtual ExtentArray GetExtent() noexcept;


};


/*Saving A String As Binary*/
class FrameObjectString : public FrameObject<std::string> {
using Base = FrameObject<std::string>;

public:

FrameObjectString(const std::string& str = "" , const std::string& name = "");


virtual size_type Encode(BinaryFrameBuffer& stack) noexcept;
virtual size_type Decode(void* ref , unsigned remain) noexcept;

virtual ObjPtr GetObj (const IndexArray& arr = IndexArray()) noexcept;
virtual size_type GetSizeof() noexcept;
virtual ExtentArray GetExtent() noexcept;


};


}
}
}
