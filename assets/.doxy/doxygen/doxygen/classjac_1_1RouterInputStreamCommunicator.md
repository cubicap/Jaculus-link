
# Class jac::RouterInputStreamCommunicator



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**RouterInputStreamCommunicator**](classjac_1_1RouterInputStreamCommunicator.md)








Inherits the following classes: [jac::InputStreamCommunicator](classjac_1_1InputStreamCommunicator.md),  [jac::Consumer](classjac_1_1Consumer.md)




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RouterInputStreamCommunicator**](#function-routerinputstreamcommunicator) (std::set&lt; int &gt; links) <br> |
| virtual size\_t | [**available**](#function-available) () override<br>_Get the number of bytes available to read._  |
| virtual void | [**cancelRead**](#function-cancelread) () override<br>_Cancel any blocking read._  |
| virtual void | [**clear**](#function-clear) () override<br>_Clear the buffer._  |
| virtual void | [**filter**](#function-filter) (std::set&lt; int &gt; links) override<br>_Set filter to only receive data from the given data links. Empty links for any._  |
| virtual int | [**get**](#function-get) () override<br>_Get a single byte from the stream._  |
| virtual void | [**processPacket**](#function-processpacket) (int linkId, std::span&lt; const uint8\_t &gt; data) override<br> |
| virtual size\_t | [**read**](#function-read) (std::span&lt; uint8\_t &gt; data) override<br>_Read data from the stream._  |

## Public Functions inherited from jac::InputStreamCommunicator

See [jac::InputStreamCommunicator](classjac_1_1InputStreamCommunicator.md)

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

## Public Functions inherited from jac::Consumer

See [jac::Consumer](classjac_1_1Consumer.md)

| Type | Name |
| ---: | :--- |
|   | [**Consumer**](#function-consumer-13) () = default<br> |
|   | [**Consumer**](#function-consumer-23) (const [**Consumer**](classjac_1_1Consumer.md) &) = delete<br> |
|   | [**Consumer**](#function-consumer-33) ([**Consumer**](classjac_1_1Consumer.md) &&) = delete<br> |
|  [**Consumer**](classjac_1_1Consumer.md) & | [**operator=**](#function-operator) (const [**Consumer**](classjac_1_1Consumer.md) &) = delete<br> |
|  [**Consumer**](classjac_1_1Consumer.md) & | [**operator=**](#function-operator_1) ([**Consumer**](classjac_1_1Consumer.md) &&) = delete<br> |
| virtual void | [**processPacket**](#function-processpacket) (int linkId, std::span&lt; const uint8\_t &gt; data) = 0<br> |
| virtual  | [**~Consumer**](#function-consumer) () = default<br> |






















## Public Functions Documentation


### function RouterInputStreamCommunicator 

```C++
inline jac::RouterInputStreamCommunicator::RouterInputStreamCommunicator (
    std::set< int > links
) 
```




### function available 

_Get the number of bytes available to read._ 
```C++
inline virtual size_t jac::RouterInputStreamCommunicator::available () override
```





**Returns:**

The number 





        
Implements [*jac::InputStreamCommunicator::available*](classjac_1_1InputStreamCommunicator.md#function-available)


### function cancelRead 

```C++
inline virtual void jac::RouterInputStreamCommunicator::cancelRead () override
```



Implements [*jac::InputStreamCommunicator::cancelRead*](classjac_1_1InputStreamCommunicator.md#function-cancelread)


### function clear 

```C++
inline virtual void jac::RouterInputStreamCommunicator::clear () override
```



Implements [*jac::InputStreamCommunicator::clear*](classjac_1_1InputStreamCommunicator.md#function-clear)


### function filter 

_Set filter to only receive data from the given data links. Empty links for any._ 
```C++
inline virtual void jac::RouterInputStreamCommunicator::filter (
    std::set< int > links
) override
```





**Parameters:**


* `links` the data link ids 




        
Implements [*jac::InputStreamCommunicator::filter*](classjac_1_1InputStreamCommunicator.md#function-filter)


### function get 

_Get a single byte from the stream._ 
```C++
inline virtual int jac::RouterInputStreamCommunicator::get () override
```





**Note:**

This method blocks until data is available.




**Returns:**

the byte or -1 if no data is available 





        
Implements [*jac::InputStreamCommunicator::get*](classjac_1_1InputStreamCommunicator.md#function-get)


### function processPacket 

```C++
inline virtual void jac::RouterInputStreamCommunicator::processPacket (
    int linkId,
    std::span< const uint8_t > data
) override
```



Implements [*jac::Consumer::processPacket*](classjac_1_1Consumer.md#function-processpacket)


### function read 

_Read data from the stream._ 
```C++
inline virtual size_t jac::RouterInputStreamCommunicator::read (
    std::span< uint8_t > data
) override
```





**Note:**

This method blocks until data is available.




**Parameters:**


* `data` the buffer to read into 



**Returns:**

The number of bytes read 





        
Implements [*jac::InputStreamCommunicator::read*](classjac_1_1InputStreamCommunicator.md#function-read)


------------------------------
The documentation for this class was generated from the following file `src/jac/link/routerCommunicator.h`