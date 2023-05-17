
# Class jac::InputStreamCommunicator



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**InputStreamCommunicator**](classjac_1_1InputStreamCommunicator.md)



_Communicator interface that can be used to receive stream data._ 

* `#include <communicator.h>`





Inherited by the following classes: [jac::RouterInputStreamCommunicator](classjac_1_1RouterInputStreamCommunicator.md)










## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**InputStreamCommunicator**](#function-inputstreamcommunicator-12) () = default<br> |
|   | [**InputStreamCommunicator**](#function-inputstreamcommunicator-22) (const [**InputStreamCommunicator**](classjac_1_1InputStreamCommunicator.md) &) = delete<br> |
| virtual size\_t | [**available**](#function-available) () = 0<br>_Get the number of bytes available to read._  |
| virtual void | [**cancelRead**](#function-cancelread) () = 0<br>_Cancel any blocking read._  |
| virtual void | [**clear**](#function-clear) () = 0<br>_Clear the buffer._  |
| virtual void | [**filter**](#function-filter) (std::set&lt; int &gt; links) = 0<br>_Set filter to only receive data from the given data links. Empty links for any._  |
| virtual int | [**get**](#function-get) () = 0<br>_Get a single byte from the stream._  |
|  [**InputStreamCommunicator**](classjac_1_1InputStreamCommunicator.md) & | [**operator=**](#function-operator) (const [**InputStreamCommunicator**](classjac_1_1InputStreamCommunicator.md) &) = delete<br> |
| virtual size\_t | [**read**](#function-read) (std::span&lt; uint8\_t &gt; data) = 0<br>_Read data from the stream._  |
| virtual  | [**~InputStreamCommunicator**](#function-inputstreamcommunicator) () = default<br> |








## Public Functions Documentation


### function InputStreamCommunicator [1/2]

```C++
jac::InputStreamCommunicator::InputStreamCommunicator () = default
```




### function InputStreamCommunicator [2/2]

```C++
jac::InputStreamCommunicator::InputStreamCommunicator (
    const InputStreamCommunicator &
) = delete
```




### function available 

_Get the number of bytes available to read._ 
```C++
virtual size_t jac::InputStreamCommunicator::available () = 0
```





**Returns:**

The number 





        

### function cancelRead 

```C++
virtual void jac::InputStreamCommunicator::cancelRead () = 0
```




### function clear 

```C++
virtual void jac::InputStreamCommunicator::clear () = 0
```




### function filter 

_Set filter to only receive data from the given data links. Empty links for any._ 
```C++
virtual void jac::InputStreamCommunicator::filter (
    std::set< int > links
) = 0
```





**Parameters:**


* `links` the data link ids 




        

### function get 

_Get a single byte from the stream._ 
```C++
virtual int jac::InputStreamCommunicator::get () = 0
```





**Note:**

This method blocks until data is available.




**Returns:**

the byte or -1 if no data is available 





        

### function operator= 

```C++
InputStreamCommunicator & jac::InputStreamCommunicator::operator= (
    const InputStreamCommunicator &
) = delete
```




### function read 

_Read data from the stream._ 
```C++
virtual size_t jac::InputStreamCommunicator::read (
    std::span< uint8_t > data
) = 0
```





**Note:**

This method blocks until data is available.




**Parameters:**


* `data` the buffer to read into 



**Returns:**

The number of bytes read 





        

### function ~InputStreamCommunicator 

```C++
virtual jac::InputStreamCommunicator::~InputStreamCommunicator () = default
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/communicator.h`