# CXXBinaryFrame
* A Basic Saving and Loading a Data as Binary For C++


# Where I use it ?
* Save and Load Everything in C++ as orderly ! But Expect of them : 
  * You can save the class but derived classes are expect it because you must write a FrameObject for save and load the derived classes ! (Pointers are raise an    issue !)
  * 

# Pros and Cons 
* Pros :
  * when you'll save a class've any pointer type then this big problem because FrameObject is copying the memory address of pointer. when you'll to load the this     binary object then this is high probability (%99.9) will give a segmentation fault error when get the this member ! (Because memory address are would change       or delete !)

* Cons :


# A Facilitate for your CXXBinaryFrame and this is a 'CXXBinaryLoaderFacilitate' !
  * # What is That ?
    * This is a bunch of FrameObject Library !
    * Save Your Objects with CXXBinaryLoaderFacilitate. (You can for now save the below objects as now ! In future times we add a lot of them)
      * Static CXXBinaryLoaderFacilitate
        * Package (We Explained in our Guide pls seek ...)
        * String
      * Dynamic CXXBinaryLoaderFacilitate
        * Vectors

