
# Class jac::Duplexify



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**Duplexify**](classjac_1_1Duplexify.md)



_A duplex stream that wraps an input and output stream._ 

* `#include <stream.h>`



Inherits the following classes: [jac::Duplex](classjac_1_1Duplex.md)
























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Duplexify**](#function-duplexify) (std::unique\_ptr&lt; [**InputStream**](classjac_1_1InputStream.md) &gt; in, std::unique\_ptr&lt; [**OutputStream**](classjac_1_1OutputStream.md) &gt; out) <br> |
| virtual bool | [**flush**](#function-flush) () override<br> |
| virtual int | [**get**](#function-get) () override<br>_Get a single byte from the stream._  |
| virtual void | [**onData**](#function-ondata) (std::function&lt; void(void)&gt;) override<br>_Register a callback to be called when data is available._  |
| virtual bool | [**put**](#function-put) (uint8\_t c) override<br>_Write a single byte to the stream._  |
| virtual size\_t | [**read**](#function-read) (std::span&lt; uint8\_t &gt; data) override<br>_Read data from the stream._  |
| virtual size\_t | [**write**](#function-write) (std::span&lt; const uint8\_t &gt; data) override<br>_Write a buffer to the stream._  |


## Public Functions inherited from jac::InputStream

See [jac::InputStream](classjac_1_1InputStream.md)

| Type | Name |
| ---: | :--- |
| virtual int | [**get**](#function-get) () = 0<br>_Get a single byte from the stream._  |
| virtual void | [**onData**](#function-ondata) (std::function&lt; void(void)&gt;) = 0<br>_Register a callback to be called when data is available._  |
| virtual size\_t | [**read**](#function-read) (std::span&lt; uint8\_t &gt; data) = 0<br>_Read data from the stream._  |
| virtual  | [**~InputStream**](#function-inputstream) () = default<br> |

## Public Functions inherited from jac::OutputStream

See [jac::OutputStream](classjac_1_1OutputStream.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**flush**](#function-flush) () = 0<br> |
| virtual bool | [**put**](#function-put) (uint8\_t c) = 0<br>_Write a single byte to the stream._  |
| virtual size\_t | [**write**](#function-write) (std::span&lt; const uint8\_t &gt; data) = 0<br>_Write a buffer to the stream._  |
| virtual  | [**~OutputStream**](#function-outputstream) () = default<br> |





























## Public Functions Documentation


### function Duplexify 

```C++
inline jac::Duplexify::Duplexify (
    std::unique_ptr< InputStream > in,
    std::unique_ptr< OutputStream > out
) 
```




### function flush 

```C++
inline virtual bool jac::Duplexify::flush () override
```



Implements [*jac::OutputStream::flush*](classjac_1_1OutputStream.md#function-flush)


### function get 

_Get a single byte from the stream._ 
```C++
inline virtual int jac::Duplexify::get () override
```





**Note:**

This method should not block.




**Returns:**

The byte or -1 if no data is available 





        
Implements [*jac::InputStream::get*](classjac_1_1InputStream.md#function-get)


### function onData 

_Register a callback to be called when data is available._ 
```C++
inline virtual void jac::Duplexify::onData (
    std::function< void(void)>
) override
```





**Note:**

The callback will not be called in parallel.




**Parameters:**


* `onData` the callback 




        
Implements [*jac::InputStream::onData*](classjac_1_1InputStream.md#function-ondata)


### function put 

_Write a single byte to the stream._ 
```C++
inline virtual bool jac::Duplexify::put (
    uint8_t c
) override
```





**Note:**

This method should not block.




**Parameters:**


* `c` the byte 



**Returns:**

true if the byte was written, false otherwise 





        
Implements [*jac::OutputStream::put*](classjac_1_1OutputStream.md#function-put)


### function read 

_Read data from the stream._ 
```C++
inline virtual size_t jac::Duplexify::read (
    std::span< uint8_t > data
) override
```





**Note:**

This method should not block.




**Parameters:**


* `data` the buffer to read into 



**Returns:**

The number of bytes read 





        
Implements [*jac::InputStream::read*](classjac_1_1InputStream.md#function-read)


### function write 

_Write a buffer to the stream._ 
```C++
inline virtual size_t jac::Duplexify::write (
    std::span< const uint8_t > data
) override
```





**Note:**

This method should not block.




**Parameters:**


* `data` the buffer to write 



**Returns:**

The number of bytes written 





        
Implements [*jac::OutputStream::write*](classjac_1_1OutputStream.md#function-write)


------------------------------
The documentation for this class was generated from the following file `src/jac/link/stream.h`