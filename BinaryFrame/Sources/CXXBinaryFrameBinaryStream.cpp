#include <CXXBinaryFrameBinaryStream.h>
#include <CXXBinaryFrameFacilitateStatic.h>

#define TargetNamespace CXX_BINARY_FRAME_STREAM_NAMESPACE

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

using CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase;
using CXX_BINARY_FRAME_FACILITATE_STATIC_NAMESPACE::FrameObjectPackage;






static void SearchBinaryFrameObjectByName(std::vector<FrameObjectBase*>& buffer , FrameObjectBase* current , const std::string& name) noexcept(false){
FrameObjectPackage* package = dynamic_cast<FrameObjectPackage*>(current);


if (package){
const
unsigned size = package->GetExtent()[0];

for (unsigned i = 0; i < size; i++){
FrameObjectBase* frame_obj = (FrameObjectBase*)current->GetObj(i);
if (frame_obj)CXX_BINARY_FRAME_THROW(std::runtime_error , "[FrameObjectPackage] Object is Null !");
SearchBinaryFrameObjectByName(buffer , frame_obj  , name);
}

}

else if (current == NULL)
CXX_BINARY_FRAME_THROW(std::runtime_error , "Object is Null ! ");
else if (current->name == name)
buffer.push_back(current);


}

//BinaryFrameStream(BinaryObjectFrames frames , BinaryFrameIOFlag flag = BinaryFrameIOFlag::Readable) : frames(frames) , flag(flag){}

TargetNamespace::BinaryFrameStream::BinaryFrameStream(){}
TargetNamespace::BinaryFrameStream::BinaryFrameStream(BinaryObjectFrames&& frames) : frames(frames){}
TargetNamespace::BinaryFrameStream::BinaryFrameStream(BinaryObjectFrames&& frames , const BinaryFrameBuffer& buffer) : frames(frames) , buffer(buffer){}
TargetNamespace::BinaryFrameStream::~BinaryFrameStream(){}




FrameObjectBase* TargetNamespace::BinaryFrameStream::GetFrameObjectFromIndex(unsigned index) noexcept(false){
if (index >= this->frames.size())CXX_BINARY_FRAME_THROW(std::out_of_range ,"Index out of range !");
return &*this->frames[index];
}


std::vector<FrameObjectBase*> TargetNamespace::BinaryFrameStream::GetFrameObjectsByName(const std::string& name , BinaryStreamSearchFlag flag) noexcept(false){
std::vector<FrameObjectBase*> objects;

for (FrameObjectPtr& ptr : this->frames){
if (!ptr.Get())CXX_BINARY_FRAME_THROW(std::runtime_error , "[FrameObject] Object is Null !");
SearchBinaryFrameObjectByName(objects , ptr.Get() , name);
}

return objects;

}

bool TargetNamespace::BinaryFrameStream::GetBufferFromFile(const std::string& file_name) noexcept(false){//Getting binary buffer from a file.
//if (this->flag != BinaryFrameIOFlag::Readable)throw std::runtime_error("flag is must be Readable !");
std::ifstream file(file_name.c_str() , std::ifstream::binary);
if (!file.is_open())return 0;
file.seekg(0 , std::ifstream::end);
int len = file.tellg();
this->buffer.resize(len);
file.read(reinterpret_cast<char*>(this->buffer.data()) , len);
file.close();
return 1;

}

bool TargetNamespace::BinaryFrameStream::SaveBufferToFile(const std::string& file_name) noexcept(false){//Saving encoded data (binary buffer) to a file.

std::ofstream file(file_name.c_str() , std::ofstream::binary);
if (!file.is_open())return 0;
file.write(reinterpret_cast<char*>(this->buffer.data()) , this->buffer.size());
file.close();
return 1;
}

void TargetNamespace::BinaryFrameStream::Encode() noexcept(false){//Encoding all FrameObjects in 'frames' into the buffer.

this->buffer.resize(0);

for (FrameObjectPtr &frame : frames)
frame->Encode(this->buffer);

}

void TargetNamespace::BinaryFrameStream::Decode() noexcept(false){//Decoding the buffer (binary buffer) into the frames.

unsigned it = 0;
for (FrameObjectPtr &frame : frames)
it += frame->Decode(&*(this->buffer.begin() + it) , this->buffer.size() - it);

}

CXX_BINARY_FRAME_NAMESPACE::BinaryFrameBuffer TargetNamespace::BinaryFrameStream::GetBinaryFrameBuffer() noexcept(false){return this->buffer;}


typename TargetNamespace::BinaryFrameStream::BinaryObjectFrames::iterator TargetNamespace::BinaryFrameStream::begin () {return this->frames.begin();}
typename TargetNamespace::BinaryFrameStream::BinaryObjectFrames::iterator TargetNamespace::BinaryFrameStream::end ()  {return this->frames.end();}

#if defined(__GNUC__)
#pragma GCC diagnostic pop

#elif defined(_MSC_VER)

#elif defined(__clang__)
#pragma clang diagnostic pop

#endif
