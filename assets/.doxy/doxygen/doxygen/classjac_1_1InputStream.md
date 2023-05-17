
# Class jac::InputStream



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**InputStream**](classjac_1_1InputStream.md)



_Interface for a binary input stream._ 

* `#include <stream.h>`





Inherited by the following classes: [jac::Duplex](classjac_1_1Duplex.md)










## Public Functions

| Type | Name |
| ---: | :--- |
| virtual int | [**get**](#function-get) () = 0<br>_Get a single byte from the stream._  |
| virtual void | [**onData**](#function-ondata) (std::function&lt; void(void)&gt;) = 0<br>_Register a callback to be called when data is available._  |
| virtual size\_t | [**read**](#function-read) (std::span&lt; uint8\_t &gt; data) = 0<br>_Read data from the stream._  |
| virtual  | [**~InputStream**](#function-inputstream) () = default<br> |








## Public Functions Documentation


### function get 

_Get a single byte from the stream._ 
```C++
virtual int jac::InputStream::get () = 0
```





**Note:**

This method should not block.




**Returns:**

The byte or -1 if no data is available 





        

### function onData 

_Register a callback to be called when data is available._ 
```C++
virtual void jac::InputStream::onData (
    std::function< void(void)>
) = 0
```





**Note:**

The callback will not be called in parallel.




**Parameters:**


* `onData` the callback 




        

### function read 

_Read data from the stream._ 
```C++
virtual size_t jac::InputStream::read (
    std::span< uint8_t > data
) = 0
```





**Note:**

This method should not block.




**Parameters:**


* `data` the buffer to read into 



**Returns:**

The number of bytes read 





        

### function ~InputStream 

```C++
virtual jac::InputStream::~InputStream () = default
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/stream.h`