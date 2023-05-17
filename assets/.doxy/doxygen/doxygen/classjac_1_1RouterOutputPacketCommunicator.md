
# Class jac::RouterOutputPacketCommunicator



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**RouterOutputPacketCommunicator**](classjac_1_1RouterOutputPacketCommunicator.md)








Inherits the following classes: [jac::OutputPacketCommunicator](classjac_1_1OutputPacketCommunicator.md)
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RouterOutputPacketCommunicator**](#function-routeroutputpacketcommunicator) ([**Router**](classjac_1_1Router.md) & router, uint8\_t channel) <br> |
| virtual std::unique\_ptr&lt; [**Packet**](classjac_1_1Packet.md) &gt; | [**buildPacket**](#function-buildpacket) (std::vector&lt; int &gt; links) override<br>_Build a packet for the given data links._  |
| virtual size\_t | [**maxPacketSize**](#function-maxpacketsize) (std::vector&lt; int &gt; links) override const<br>_Get the maximum packet size for the given data links._  |

## Public Functions inherited from jac::OutputPacketCommunicator

See [jac::OutputPacketCommunicator](classjac_1_1OutputPacketCommunicator.md)

| Type | Name |
| ---: | :--- |
|   | [**OutputPacketCommunicator**](#function-outputpacketcommunicator-12) () = default<br> |
|   | [**OutputPacketCommunicator**](#function-outputpacketcommunicator-22) (const [**OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md) &) = delete<br> |
| virtual std::unique\_ptr&lt; [**Packet**](classjac_1_1Packet.md) &gt; | [**buildPacket**](#function-buildpacket) (std::vector&lt; int &gt; links) = 0<br>_Build a packet for the given data links._  |
| virtual size\_t | [**maxPacketSize**](#function-maxpacketsize) (std::vector&lt; int &gt; links) const = 0<br>_Get the maximum packet size for the given data links._  |
|  [**OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md) & | [**operator=**](#function-operator) (const [**OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md) &) = delete<br> |
| virtual  | [**~OutputPacketCommunicator**](#function-outputpacketcommunicator) () = default<br> |















## Public Functions Documentation


### function RouterOutputPacketCommunicator 

```C++
inline jac::RouterOutputPacketCommunicator::RouterOutputPacketCommunicator (
    Router & router,
    uint8_t channel
) 
```




### function buildPacket 

_Build a packet for the given data links._ 
```C++
inline virtual std::unique_ptr< Packet > jac::RouterOutputPacketCommunicator::buildPacket (
    std::vector< int > links
) override
```





**Parameters:**


* `links` the data link ids 



**Returns:**

The packet 





        
Implements [*jac::OutputPacketCommunicator::buildPacket*](classjac_1_1OutputPacketCommunicator.md#function-buildpacket)


### function maxPacketSize 

_Get the maximum packet size for the given data links._ 
```C++
inline virtual size_t jac::RouterOutputPacketCommunicator::maxPacketSize (
    std::vector< int > links
) override const
```





**Parameters:**


* `links` the data link ids 



**Returns:**

The maximum packet size 





        
Implements [*jac::OutputPacketCommunicator::maxPacketSize*](classjac_1_1OutputPacketCommunicator.md#function-maxpacketsize)


------------------------------
The documentation for this class was generated from the following file `src/jac/link/routerCommunicator.h`