
# Class jac::Mux

**template &lt;class Encoder class Encoder&gt;**



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**Mux**](classjac_1_1Mux.md)



_A multiplexer that creates 256 channels on a single stream connection._ [More...](#detailed-description)

* `#include <mux.h>`



Inherits the following classes: [jac::DataLinkTx](classjac_1_1DataLinkTx.md)
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Mux**](#function-mux-13) (std::unique\_ptr&lt; [**Duplex**](classjac_1_1Duplex.md) &gt; stream) <br> |
|   | [**Mux**](#function-mux-23) (const [**Mux**](classjac_1_1Mux.md) &) = delete<br> |
|   | [**Mux**](#function-mux-33) ([**Mux**](classjac_1_1Mux.md) &&) = delete<br> |
|  void | [**bindRx**](#function-bindrx) (std::unique\_ptr&lt; [**DataLinkRx**](classjac_1_1DataLinkRx.md) &gt; receiver) <br>_Bind a receiver to this mux. Received packets will be forwarded to the receiver._  |
| virtual std::unique\_ptr&lt; [**Packet**](classjac_1_1Packet.md) &gt; | [**buildPacket**](#function-buildpacket) (uint8\_t channel) override<br>_Build a packet for the given channel._  |
| virtual size\_t | [**maxPacketSize**](#function-maxpacketsize) () override const<br>_Get the maximum packet size for this mux._  |
|  void | [**setErrorHandler**](#function-seterrorhandler) (std::function&lt; void(MuxError, std::any)&gt; handler) <br>_Set the error handler for this mux._  |

## Public Functions inherited from jac::DataLinkTx

See [jac::DataLinkTx](classjac_1_1DataLinkTx.md)

| Type | Name |
| ---: | :--- |
|   | [**DataLinkTx**](#function-datalinktx-13) () = default<br> |
|   | [**DataLinkTx**](#function-datalinktx-23) (const [**DataLinkTx**](classjac_1_1DataLinkTx.md) &) = delete<br> |
|   | [**DataLinkTx**](#function-datalinktx-33) ([**DataLinkTx**](classjac_1_1DataLinkTx.md) &&) = delete<br> |
| virtual std::unique\_ptr&lt; [**Packet**](classjac_1_1Packet.md) &gt; | [**buildPacket**](#function-buildpacket) (uint8\_t channel) = 0<br>_Build a packet for the given channel._  |
| virtual size\_t | [**maxPacketSize**](#function-maxpacketsize) () const = 0<br>_Get the maximum packet size for the given channel._  |
|  [**DataLinkTx**](classjac_1_1DataLinkTx.md) & | [**operator=**](#function-operator) (const [**DataLinkTx**](classjac_1_1DataLinkTx.md) &) = delete<br> |
|  [**DataLinkTx**](classjac_1_1DataLinkTx.md) & | [**operator=**](#function-operator_1) ([**DataLinkTx**](classjac_1_1DataLinkTx.md) &&) = delete<br> |















# Detailed Description




**Template parameters:**


* `Encoder` the encoder to use 




    
## Public Functions Documentation


### function Mux [1/3]

```C++
inline jac::Mux::Mux (
    std::unique_ptr< Duplex > stream
) 
```




### function Mux [2/3]

```C++
jac::Mux::Mux (
    const Mux &
) = delete
```




### function Mux [3/3]

```C++
jac::Mux::Mux (
    Mux &&
) = delete
```




### function bindRx 

_Bind a receiver to this mux. Received packets will be forwarded to the receiver._ 
```C++
inline void jac::Mux::bindRx (
    std::unique_ptr< DataLinkRx > receiver
) 
```





**Parameters:**


* `receiver` the receiver to bind 




        

### function buildPacket 

_Build a packet for the given channel._ 
```C++
inline virtual std::unique_ptr< Packet > jac::Mux::buildPacket (
    uint8_t channel
) override
```





**Parameters:**


* `channel` the channel 



**Returns:**

The packet 





        
Implements [*jac::DataLinkTx::buildPacket*](classjac_1_1DataLinkTx.md#function-buildpacket)


### function maxPacketSize 

_Get the maximum packet size for this mux._ 
```C++
inline virtual size_t jac::Mux::maxPacketSize () override const
```





**Returns:**

The maximum packet size 





        
Implements [*jac::DataLinkTx::maxPacketSize*](classjac_1_1DataLinkTx.md#function-maxpacketsize)


### function setErrorHandler 

_Set the error handler for this mux._ 
```C++
inline void jac::Mux::setErrorHandler (
    std::function< void(MuxError, std::any)> handler
) 
```





**Parameters:**


* `handler` the error handler 




        

------------------------------
The documentation for this class was generated from the following file `src/jac/link/mux.h`