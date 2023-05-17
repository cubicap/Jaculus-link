
# Class jac::OutputStream



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**OutputStream**](classjac_1_1OutputStream.md)



_Interface for a binary output stream._ 

* `#include <stream.h>`





Inherited by the following classes: [jac::Duplex](classjac_1_1Duplex.md)










## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**flush**](#function-flush) () = 0<br> |
| virtual bool | [**put**](#function-put) (uint8\_t c) = 0<br>_Write a single byte to the stream._  |
| virtual size\_t | [**write**](#function-write) (std::span&lt; const uint8\_t &gt; data) = 0<br>_Write a buffer to the stream._  |
| virtual  | [**~OutputStream**](#function-outputstream) () = default<br> |








## Public Functions Documentation


### function flush 

```C++
virtual bool jac::OutputStream::flush () = 0
```




### function put 

_Write a single byte to the stream._ 
```C++
virtual bool jac::OutputStream::put (
    uint8_t c
) = 0
```





**Note:**

This method should not block.




**Parameters:**


* `c` the byte 



**Returns:**

true if the byte was written, false otherwise 





        

### function write 

_Write a buffer to the stream._ 
```C++
virtual size_t jac::OutputStream::write (
    std::span< const uint8_t > data
) = 0
```





**Note:**

This method should not block.




**Parameters:**


* `data` the buffer to write 



**Returns:**

The number of bytes written 





        

### function ~OutputStream 

```C++
virtual jac::OutputStream::~OutputStream () = default
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/stream.h`