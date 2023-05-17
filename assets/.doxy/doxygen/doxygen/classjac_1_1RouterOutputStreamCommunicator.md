
# Class jac::RouterOutputStreamCommunicator



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**RouterOutputStreamCommunicator**](classjac_1_1RouterOutputStreamCommunicator.md)








Inherits the following classes: [jac::OutputStreamCommunicator](classjac_1_1OutputStreamCommunicator.md)
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RouterOutputStreamCommunicator**](#function-routeroutputstreamcommunicator) ([**Router**](classjac_1_1Router.md) & router, uint8\_t channel, std::vector&lt; int &gt; links) <br> |
| virtual bool | [**put**](#function-put) (uint8\_t c) override<br>_Put a single byte to the stream._  |
| virtual void | [**setRecipients**](#function-setrecipients) (std::vector&lt; int &gt; recipients) override<br>_Set the data links the stream should be sent to. Empty links for broadcast._  |
| virtual size\_t | [**write**](#function-write) (std::span&lt; const uint8\_t &gt; data) override<br>_Write a buffer to the stream._  |

## Public Functions inherited from jac::OutputStreamCommunicator

See [jac::OutputStreamCommunicator](classjac_1_1OutputStreamCommunicator.md)

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


### function RouterOutputStreamCommunicator 

```C++
inline jac::RouterOutputStreamCommunicator::RouterOutputStreamCommunicator (
    Router & router,
    uint8_t channel,
    std::vector< int > links
) 
```




### function put 

_Put a single byte to the stream._ 
```C++
inline virtual bool jac::RouterOutputStreamCommunicator::put (
    uint8_t c
) override
```





**Parameters:**


* `c` the byte to put 



**Returns:**

True if the byte was put successfully 





        
Implements [*jac::OutputStreamCommunicator::put*](classjac_1_1OutputStreamCommunicator.md#function-put)


### function setRecipients 

_Set the data links the stream should be sent to. Empty links for broadcast._ 
```C++
inline virtual void jac::RouterOutputStreamCommunicator::setRecipients (
    std::vector< int > recipients
) override
```





**Parameters:**


* `recipients` the data link ids 




        
Implements [*jac::OutputStreamCommunicator::setRecipients*](classjac_1_1OutputStreamCommunicator.md#function-setrecipients)


### function write 

_Write a buffer to the stream._ 
```C++
inline virtual size_t jac::RouterOutputStreamCommunicator::write (
    std::span< const uint8_t > data
) override
```





**Parameters:**


* `data` the buffer to write 



**Returns:**

The number of bytes put 





        
Implements [*jac::OutputStreamCommunicator::write*](classjac_1_1OutputStreamCommunicator.md#function-write)


------------------------------
The documentation for this class was generated from the following file `src/jac/link/routerCommunicator.h`