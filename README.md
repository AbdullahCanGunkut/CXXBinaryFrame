# CXXBinaryFrame
* A Basic Saving and Loading a Data as Binary (Byte by Byte) For C++


# Where I use it ?
* Save and Load Everything in C++ as orderly ! But Expect of the them : 
  * You can save the class but derived classes are expect it because you must write a FrameObject for save and load the derived classes ! (Pointers are               troubleshooting ! segmentation-faults etc...)
  * 

# Pros and Cons 
* Pros :
  * when you'll save a class and it has any pointer member then this big problem because FrameObject is copying the memory address of pointer. when you'll to load     the this binary object then this would give a segmentation fault error when get the this member ! (Because memory address are may changed or deleted !)

* Cons :

# Which C++ Standard Versions Supported ?
* C++ 11 and Upper Versions 

# A Facilitate for your CXXBinaryFrame and this is 'The CXXBinaryLoaderFacilitate Library' !
  * # What is That ?
    * This is a bunch of FrameObject Library !
    * Save Your Objects with CXXBinaryLoaderFacilitate. (You can for now save the below objects as now ! In future times we add a lot of them)
      * ## Static CXXBinaryLoaderFacilitate
        * Package **(FrameObjectPackage)**
        * String **(FrameObjectString)**
        
      * ## Dynamic CXXBinaryLoaderFacilitate (like the STL)
        * Vectors **(FrameObjectVector)**
        * Pointer **(FrameObjectPointer)**
        * Array   **(FrameObjectArray)**

# Futures
   * ### Hashing
   * ### Compression
   * ### New Facilitate FrameObjects

# A Basic Example
```cpp
#include <stdio.h>
#include <iostream>
#include <CXXBinaryLoaderBinaryFrame.hpp>
#include <CXXBinaryFrameBinaryStream.h>

int main (){

/*What is the FrameObject ? FrameObject is for Encode/Decode our data into the a byte array (or binary buffer).
(Note : A Binary Stream Holding the Bunch of the FrameObjects and if you call Encode/Decode from Binary Stream then it's calling each FrameObjects Encode/Decode
from Binary Stream)*/

class MyObject final{//A Example Class For Save a Object.(But class is'nt must be derive of any class ! because vtable ptr is troubleshooting)
public:

struct ID{
public:
ID(unsigned id = 0 , const char* name = "") : id(id){
memcpy(this->name , name , strlen(name) + 1);
}
unsigned id;
char name[32];

void Print(){
  std::cout << "Id : " << id << std::endl;
  std::cout << "Name : " << name << std::endl;
}


};
struct Properties{
public:
Properties(float walkSpeed = 0 , float runSpeed = 0 , float jumpSpeed = 0) : walkSpeed(walkSpeed) , runSpeed(runSpeed) , jumpSpeed(jumpSpeed){}
float walkSpeed , runSpeed ,  jumpSpeed;

void Print(){
  std::cout << "Walk Speed : " << walkSpeed << std::endl;
  std::cout << "Run Speed : " << runSpeed << std::endl;
  std::cout << "Jump Speed : " << jumpSpeed << std::endl;
}
};

MyObject(bool isHuman = true , const Properties& property = Properties() , const ID& id = ID()) : property(property) , id(id) , isHuman(isHuman){}

void Print(){
std::cout <<"My Object" << std::endl;
this->id.Print();
this->property.Print();
std::cout << "Is Human ? " <<  std::boolalpha << isHuman << std::endl;

}


ID id;
Properties property;
bool isHuman;

};


MAKE_BINARY_FRAME_STREAM(stream , //We making a frame stream for encoding and decoding the our FrameObjects.
MAKE_BINARY_FRAME_OBJECTS(
FRAME_OBJECT(MyObject , "Animal", false , MyObject::Properties(12 , 62.54 , 40) , MyObject::ID(1 , "Unknown Animal")),
FRAME_OBJECT(MyObject , "Man" , true , MyObject::Properties(12 , 30 , 20) , MyObject::ID(54 , "Man"))
));//We making a Binary Frame Buffer because it's holding the our FrameObjects for Encode And Decode.


try {
stream.Encode();//Encoding Our Data
}catch(std::exception error){
std::cout << error.what() << std::endl;
exit(1);
}

MAKE_BINARY_FRAME_STREAM(stream2 ,
MAKE_BINARY_FRAME_OBJECTS(
FRAME_OBJECT(MyObject , "Animal"),//if you decoding an stream then you must make the FrameObjects as same order of a stream and otherwise you would get an error !
FRAME_OBJECT(MyObject , "Man")),
stream.GetBinaryFrameBuffer() //Loading Encoded data from stream.
);

try{
stream2.Decode();//Decoding our BinaryFrameBuffer into the FrameObjects of stream2
}catch(std::exception error){
std::cout << error.what() << std::endl;
exit(1);
}


for (unsigned i = 0; i < 2; i++){
MyObject* obj = (MyObject*)stream2.GetFrameObjectFromIndex(i)->GetObj();
obj->Print();
std::cout << std::endl;
}

}

```

# How I install it with Cmake ?

### Linux
```

git clone git://github.com/AbdullahCanGunkut/CXXBinaryFrame
mkdir CXXBinaryFrame/BinaryFrame/build
cd CXXBinaryFrame/BinaryFrame/build
cmake -DCXX_STANDARD_VERSION=11 -build ..
make
```
