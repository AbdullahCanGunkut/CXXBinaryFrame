#include <CXXBinaryFramePointerNode.h>

using TargetNamespace = CXXBinaryLoader::CXXBinaryFramePointerNode;


TargetNamespace::PointerNode::PointerNode(const PointerCount pointer_count , void* data_ptr) :
pointer_count(pointer_count) , data_ptr(data_ptr) {}
TargetNamespace::PointerNode::PointerNode(const PointerCount pointer_count , void* data_ptr ,  const vector<PointerNode>& pointers) :
pointers(pointers) , pointer_count(pointer_count) , data_ptr(data_ptr){}

bool TargetNamespace::PointerNode::CheckIndexArray(const IndexArray& indices){

  if (indices.size() > this->pointers.size())return 0x00;
  unsigned it = 0x00;
  for (PointerNode& node = this->pointers[0]; indices[it] < node.GetCount() && (node = node.pointers[indices[it]] , 1); it++);

  return it == indices.size();
}

TargetNamespace::PointerNode TargetNamespace::PointerNode::operator [](unsigned index){return this->pointers[index];}

void* TargetNamespace::PointerNode::operator()(unsigned index){
if (index >= this->pointers.size())throw std::out_of_range("Index is out of the 'pointers' !");
return ((void**)this->data_ptr)[index];
}

void TargetNamespace::PointerNode::GetPointerNodeFromIndexArray(const IndexArray& indices){
if (indices.size() > this->pointers.size())throw std::out_of_range("Argument 'indices' out range of pointers.");

PointerNode& target_node = *this;

unsigned it = 0;
for (auto a : indices)
if (a >= target_node.GetCount())
throw std::out_of_range(string("Index Out Of Range At ") + to_string(it) + string(" , and target index : ") + to_string(a));
else
target_node = target_node[a] , ++it;


return target_node;
}

static void DeleteNode(PointerNode& node , DeallocFunc func){

if (node.pointer_count != 1)
for (unsigned i = 0; i < node.GetCount(); i++)
DeleteNode(node[i] ,dealloc_func);


if (node.data_ptr)
if (func)delete node.data_ptr;
else func(node.data_ptr);


}

void TargetNamespace::PointerNode::DeletePointerNode(PointerNode& node , DeallocFunc dealloc_func , const DeallocationMode mode){
for (auto a : node.pointers)
DeleteNode(a , dealloc_func);

}
