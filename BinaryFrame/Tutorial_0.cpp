#include <stdio.h>
#include <iostream>

#include <CXXBinaryLoaderBinaryFrame.hpp>
#include <CXXBinaryFrameFacilitateDynamic.hpp>
#include <CXXBinaryFrameFacilitateStatic.h>
#include <CXXBinaryFrameBinaryStream.h>


using namespace CXXBinaryLoader::CXXBinaryFrame;
static constexpr const char*
AnimalNames[] = {"Zoe" , "Leon" , "Hyena" , "Turtle"};

int main (){


class Database{
public:

Database() = default;
Database(const std::string& name  , const std::string& job , unsigned id , unsigned age) : id(id) , age(age){

memcpy(this->name , name.c_str() , name.size() + 1);
memcpy(this->job , job.c_str() , job.size() + 1);
}
void Print(){



std::cout << "ID : " << this->id << std::endl;
std::cout << "Name : " << name << std::endl;
std::cout << "Job : " << job << std::endl;
std::cout << "Age : " << age << std::endl;
std::cout << std::endl;


}

char name[16];
char job[16];
unsigned id;
unsigned age;

};



class Database2{
public:

Database2() = default;
Database2(unsigned animal_id , float length) : animal_id(animal_id) , length(length){}



void Print(){

std::cout << "Animal Name : " << ::AnimalNames[this->animal_id] << std::endl;
std::cout << "Length : " << this->length << std::endl << std::endl;

}
unsigned animal_id;
float length;


};

Database human_database[]{
Database("Mohammed Ali" , "Boxing" , 89 , 16) ,
Database("Jack Doc" , "Doctor" , 1 , 24),
Database("Julie Nipingo" , "Surgeon" , 6 , 20)};

Database human_database_decoded[sizeof(human_database) / sizeof(Database)];

Database2 animal_database[]{
Database2(1 , 4.78f) ,
Database2(3 , 8.60f),
Database2(0 , 13),
Database2(0 , 1.0f),
Database2(2 , 12)
} , animal_database_decoded[ sizeof(animal_database) / sizeof(Database2)];


{

MAKE_BINARY_FRAME_STREAM
(stream , MAKE_BINARY_FRAMEBUFFER(
BINARY_FRAME_POINTER(human_database) ,
BINARY_FRAME_POINTER(animal_database) ,
FRAME_OBJECT_STRING("hello my friend !")
));

stream.Encode();
stream.SaveBufferToFile("Hello.txt");

BinaryFrameBuffer buff = stream.GetBinaryFrameBuffer();

using
CXXBinaryLoader::CXXBinaryFrame::IndexArray;


MAKE_BINARY_FRAME_STREAM(stream2 ,
MAKE_BINARY_FRAMEBUFFER(
BINARY_FRAME_POINTER(human_database_decoded) ,
BINARY_FRAME_POINTER(animal_database_decoded),
FRAME_OBJECT_STRING("hello my friend !")
) , buff);


try{
stream2.Decode();
}catch(std::exception exception){
printf("%s\n" , exception.what());
}

std::cout << "Humans : " << std::endl;
for (unsigned i = 0; i < stream2.GetFrameObjectFromIndex(0)->GetExtent()[0]; i++){
Database* data = (Database*)stream2.GetFrameObjectFromIndex(0)->GetObj(IndexArray({i}));
data->Print();
}


std::cout << "-------------------------------" << std::endl;
std::cout << "Animals : " << std::endl;

for (unsigned i = 0; i < stream2.GetFrameObjectFromIndex(1)->GetExtent()[0]; i++){
Database2* data = (Database2*)stream2.GetFrameObjectFromIndex(1)->GetObj(IndexArray({i}));
data->Print();
}

std::string* name = (std::string*)stream2.GetFrameObjectFromIndex(2)->GetObj();
std::cout << "Name :" <<  *name <<  std::endl;



}


}


//BinaryFrameStream stream();

//printf("%s %s\n" , typeid(ClassA).name(),  stream.GetCurrentFrameObject()->GetTypename().c_str());
