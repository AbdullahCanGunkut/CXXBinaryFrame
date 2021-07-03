#pragma once
#include <CXXBinaryLoaderBinaryFrame.hpp>

#define CXX_BINARY_FRAME_STREAM_NAMESPACE CXXBinaryLoader::CXXBinaryFrame::CXXBinaryStream

#define MAKE_BINARY_FRAME_OBJECTS(...) CXX_BINARY_FRAME_STREAM_NAMESPACE::BinaryFrameStream::BinaryObjectFrames({__VA_ARGS__})
#define MAKE_BINARY_FRAME_STREAM(NAME , ...) CXX_BINARY_FRAME_STREAM_NAMESPACE::BinaryFrameStream NAME(__VA_ARGS__)

namespace CXXBinaryLoader{

namespace CXXBinaryFrame{

namespace CXXBinaryStream{



enum class  BinaryStreamSearchFlag  : unsigned {
BinaryStreamSearch_JustChild,
BinaryStreamSearch_Deep
};

class BinaryFrameStream{ // Very important class for encode and decode instructions and also saving the binary buffer to  a file or loading binary buffer from a file.

public:

typedef PointerStorage<FrameObjectBase> FrameObjectPtr;
typedef std::vector<FrameObjectPtr> BinaryObjectFrames;





BinaryFrameStream();
BinaryFrameStream(BinaryObjectFrames&& frames);
BinaryFrameStream(BinaryObjectFrames&& frames , const BinaryFrameBuffer& buffer);
virtual ~BinaryFrameStream();



FrameObjectBase* GetFrameObjectFromIndex(unsigned index) noexcept(false);
std::vector<FrameObjectBase*> GetFrameObjectsByName(const std::string& name , BinaryStreamSearchFlag flag = BinaryStreamSearchFlag::BinaryStreamSearch_Deep) noexcept(false);




bool GetBufferFromFile(const std::string& file_name) noexcept(false);//Getting binary buffer from a file.
bool SaveBufferToFile(const std::string& file_name) noexcept(false);//Saving encoded data (binary buffer) to a file.

virtual void Encode() noexcept(false);//Encoding all FrameObjects in 'frames' into the buffer.
virtual void Decode() noexcept(false);//Decoding the buffer (binary buffer) into the frames.


BinaryFrameBuffer GetBinaryFrameBuffer() noexcept(false);




//For Range Based Loop
typename BinaryObjectFrames::iterator begin ();
typename BinaryObjectFrames::iterator end ();



protected:
BinaryFrameBuffer buffer;
BinaryObjectFrames frames;


};

}



}


}
