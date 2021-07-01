#include <stdio.h>
#include <iostream>

#include <CXXBinaryLoaderBinaryFrame.hpp>
#include <CXXBinaryFrameFacilitateDynamic.hpp>
#include <CXXBinaryFrameBinaryStream.h>




int main (){






class ClassA{
public:
ClassA(const std::string& name = ""){
memcpy(&this->name[0] , &name[0] , name.size() + 1);
}
char name[64];
};




MAKE_BINARY_FRAME_STREAM
(stream , MAKE_BINARY_FRAMEBUFFER(
FRAME_OBJECT_VECTOR(ClassA , "MyVector" ,
ClassA("Money") , ClassA("Car") ,
ClassA("World") , ClassA("Trade") ,
ClassA("Jump")  , ClassA("Ride")),

)); //We are initializing our datas.

stream.Encode();//Encoding the our datas as binary.
std::cout << "Encode Completed !" << std::endl;

CXX_BINARY_FRAME_NAMESPACE::BinaryFrameBuffer buff = stream.GetBinaryFrameBuffer();//Get encoded binary data.


using
CXXBinaryLoader::CXXBinaryFrame::IndexArray;


MAKE_BINARY_FRAME_STREAM(stream2 ,
MAKE_BINARY_FRAMEBUFFER(
FRAME_OBJECT_VECTOR(ClassA , "MyVector")
) , buff /*Encoded binary data*/);


try{
stream2.Decode(); // Decoding our binary data and it's the buff.
}catch(std::exception exception){//Exception checking
printf("%s\n" , exception.what());
}
std::cout << "Decode Completed !" << std::endl;



CXX_BINARY_FRAME_FACILITATE_DYNAMIC_NAMESPACE::FrameObjectVector<ClassA>& ClassAVector = *(CXX_BINARY_FRAME_FACILITATE_DYNAMIC_NAMESPACE::FrameObjectVector<ClassA>*) stream2.GetFrameObjectFromIndex(0);


try {

stream2.GetFrameObjectFromIndex(4);
}catch(const std::out_of_range& err){
std::cout << "Err : " << err.what() << std::endl;


}
std::cout << "Class A : " << std::endl;

for (ClassA& obj : ClassAVector)
std::cout <<  obj.name << std::endl;
std::cout << std::endl;





}


//BinaryFrameStream stream();

//printf("%s %s\n" , typeid(ClassA).name(),  stream.GetCurrentFrameObject()->GetTypename().c_str());
