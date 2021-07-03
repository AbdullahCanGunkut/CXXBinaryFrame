#include <stdio.h>
#include <iostream>

#include <CXXBinaryLoaderBinaryFrame.hpp>
#include <CXXBinaryFrameFacilitateStatic.h>
#include <CXXBinaryFrameBinaryStream.h>

int main (){

{

MAKE_BINARY_FRAME_STREAM
(stream , MAKE_BINARY_FRAME_OBJECTS(
FRAME_OBJECT_STRING("hello my friend !" , "Message"),
FRAME_OBJECT_STRING("Good Bye !" , "Message") ,
FRAME_OBJECT_STRING("Get out !" , "Command"),
FRAME_OBJECT_STRING("Close the door !" , "Command")
)); //We are initializing our datas.

stream.Encode();//Encoding the our datas as binary.

CXX_BINARY_FRAME_NAMESPACE::BinaryFrameBuffer buff = stream.GetBinaryFrameBuffer();//Get encoded binary data.


using
CXXBinaryLoader::CXXBinaryFrame::IndexArray;


MAKE_BINARY_FRAME_STREAM(stream2 ,
MAKE_BINARY_FRAME_OBJECTS(
FRAME_OBJECT_STRING("",  "Message"),
FRAME_OBJECT_STRING("" , "Message") ,
FRAME_OBJECT_STRING("" , "Command"),
FRAME_OBJECT_STRING("" , "Command")
) , buff /*Encoded binary data*/);


try{
stream2.Decode(); // Decoding our binary data and it's the buff.
}catch(std::exception exception){//Exception checking
printf("%s\n" , exception.what());
}

std::vector<CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase*>
messages = stream2.GetFrameObjectsByName("Message") , commands = stream2.GetFrameObjectsByName("Command");

std::cout << "Messages : " << std::endl;

for (CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase*  obj : messages)
std::cout << *(std::string*)obj->GetObj() << std::endl;
std::cout << std::endl;

std::cout << "Commands : " << std::endl;


for (CXX_BINARY_FRAME_NAMESPACE::FrameObjectBase*  obj : commands)
std::cout << *(std::string*)obj->GetObj() << std::endl;
std::cout << std::endl;

}

return 0;

}


//BinaryFrameStream stream();

//printf("%s %s\n" , typeid(ClassA).name(),  stream.GetCurrentFrameObject()->GetTypename().c_str());
