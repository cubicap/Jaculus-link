
# Class jac::Duplex



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**Duplex**](classjac_1_1Duplex.md)



_Interface for an byte input/output stream._ 

* `#include <stream.h>`



Inherits the following classes: [jac::InputStream](classjac_1_1InputStream.md),  [jac::OutputStream](classjac_1_1OutputStream.md)


Inherited by the following classes: [jac::Duplexify](classjac_1_1Duplexify.md)



















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























------------------------------
The documentation for this class was generated from the following file `src/jac/link/stream.h`