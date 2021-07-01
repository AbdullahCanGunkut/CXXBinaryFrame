#pragma once

#include <CXXBinaryFrameTypename.h>
#include <CXXBinaryLoaderBinaryFrame.hpp>


namespace CXXBinaryLoader{
namespace CXXBinaryFramePointerNode{

  using CXXBinaryFrame::IndexArray;
  using CXXBinaryFrame::ExtentArray;

  class PointerNode  final{//This Very important struct ! Holding the pointer counts of a pointer array.
  public:

  PointerNode(const PointerCount pointer_count = 0x00, void* data_ptr = NULL);//Resizing the 'pointers'.
  PointerNode(const PointerCount pointer_count , const vector<PointerNode>& pointers);
  ~PointerNode() = default;

  bool CheckIndexArray(const IndexArray& indices);
  CXX_BIN_LOADER_INLINE unsigned GetCount(){return this->pointers.size();}//Returning the count of 'pointers'.
  PointerNode& operator [](unsigned index) noexcept;
  void* operator()(unsigned index) noexcept;
  void GetPointerNodeFromIndexArray(const IndexArray& indices);

  static PointerNode& DeletePointerNode(const PointerNode& node , DeallocFunc dealloc_func = NULL , const DeallocationMode mode = DeallocationMode::Flush) noexcept;

  const DataCount single_pointer_count;
  const PointerCount pointer_count;
  vector<PointerNode> pointers;
  void* data_ptr;

  };

  void EncodePointerNode(FrameObjectBase* base_ptr , ) noexcept{}



}
}
