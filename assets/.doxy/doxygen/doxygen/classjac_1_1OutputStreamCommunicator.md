
# Class jac::OutputStreamCommunicator



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**OutputStreamCommunicator**](classjac_1_1OutputStreamCommunicator.md)



_Communicator interface that can be used send stream data._ 

* `#include <communicator.h>`





Inherited by the following classes: [jac::RouterOutputStreamCommunicator](classjac_1_1RouterOutputStreamCommunicator.md)










## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OutputStreamCommunicator**](#function-outputstreamcommunicator-12) () = default<br> |
|   | [**OutputStreamCommunicator**](#function-outputstreamcommunicator-22) (const [**OutputStreamCommunicator**](classjac_1_1OutputStreamCommunicator.md) &) = delete<br> |
|  [**OutputStreamCommunicator**](classjac_1_1OutputStreamCommunicator.md) & | [**operator=**](#function-operator) (const [**OutputStreamCommunicator**](classjac_1_1OutputStreamCommunicator.md) &) = delete<br> |
| virtual bool | [**put**](#function-put) (uint8\_t c) = 0<br>_Put a single byte to the stream._  |
| virtual void | [**setRecipients**](#function-setrecipients) (std::vector&lt; int &gt; recipients) = 0<br>_Set the data links the stream should be sent to. Empty links for broadcast._  |
| virtual size\_t | [**write**](#function-write) (std::span&lt; const uint8\_t &gt; data) = 0<br>_Write a buffer to the stream._  |
| virtual  | [**~OutputStreamCommunicator**](#function-outputstreamcommunicator) () = default<br> |








## Public Functions Documentation


### function OutputStreamCommunicator [1/2]

```C++
jac::OutputStreamCommunicator::OutputStreamCommunicator () = default
```




### function OutputStreamCommunicator [2/2]

```C++
jac::OutputStreamCommunicator::OutputStreamCommunicator (
    const OutputStreamCommunicator &
) = delete
```




### function operator= 

```C++
OutputStreamCommunicator & jac::OutputStreamCommunicator::operator= (
    const OutputStreamCommunicator &
) = delete
```




### function put 

_Put a single byte to the stream._ 
```C++
virtual bool jac::OutputStreamCommunicator::put (
    uint8_t c
) = 0
```





**Parameters:**


* `c` the byte to put 



**Returns:**

True if the byte was put successfully 





        

### function setRecipients 

_Set the data links the stream should be sent to. Empty links for broadcast._ 
```C++
virtual void jac::OutputStreamCommunicator::setRecipients (
    std::vector< int > recipients
) = 0
```





**Parameters:**


* `recipients` the data link ids 




        

### function write 

_Write a buffer to the stream._ 
```C++
virtual size_t jac::OutputStreamCommunicator::write (
    std::span< const uint8_t > data
) = 0
```





**Parameters:**


* `data` the buffer to write 



**Returns:**

The number of bytes put 





        

### function ~OutputStreamCommunicator 

```C++
virtual jac::OutputStreamCommunicator::~OutputStreamCommunicator () = default
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/communicator.h`