# CXXBinaryFrame
* A Basic Saving and Loading a Data as Binary For C++


# Where I use it ?
* Save and Load Everything in C++ as orderly ! But Expect of the them : 
  * You can save the class but derived classes are expect it because you must write a FrameObject for save and load the derived classes ! (Pointers are raise an         issue ! segmentation-faults etc...)
  * 

# Pros and Cons 
* Pros :
  * when you'll save a class and it has any pointer member then this big problem because FrameObject is copying the memory address of pointer. when you'll to load     the this binary object then this is high probability (%99.9) would give a segmentation fault error when get the this member ! (Because memory address are         would change or delete !)

* Cons :


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
