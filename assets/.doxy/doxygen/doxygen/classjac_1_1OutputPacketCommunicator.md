
# Class jac::OutputPacketCommunicator



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md)



_Communicator interface that can be used to send packets._ 

* `#include <communicator.h>`





Inherited by the following classes: [jac::RouterOutputPacketCommunicator](classjac_1_1RouterOutputPacketCommunicator.md)










## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OutputPacketCommunicator**](#function-outputpacketcommunicator-12) () = default<br> |
|   | [**OutputPacketCommunicator**](#function-outputpacketcommunicator-22) (const [**OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md) &) = delete<br> |
| virtual std::unique\_ptr&lt; [**Packet**](classjac_1_1Packet.md) &gt; | [**buildPacket**](#function-buildpacket) (std::vector&lt; int &gt; links) = 0<br>_Build a packet for the given data links._  |
| virtual size\_t | [**maxPacketSize**](#function-maxpacketsize) (std::vector&lt; int &gt; links) const = 0<br>_Get the maximum packet size for the given data links._  |
|  [**OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md) & | [**operator=**](#function-operator) (const [**OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md) &) = delete<br> |
| virtual  | [**~OutputPacketCommunicator**](#function-outputpacketcommunicator) () = default<br> |








## Public Functions Documentation


### function OutputPacketCommunicator [1/2]

```C++
jac::OutputPacketCommunicator::OutputPacketCommunicator () = default
```




### function OutputPacketCommunicator [2/2]

```C++
jac::OutputPacketCommunicator::OutputPacketCommunicator (
    const OutputPacketCommunicator &
) = delete
```




### function buildPacket 

_Build a packet for the given data links._ 
```C++
virtual std::unique_ptr< Packet > jac::OutputPacketCommunicator::buildPacket (
    std::vector< int > links
) = 0
```





**Parameters:**


* `links` the data link ids 



**Returns:**

The packet 





        

### function maxPacketSize 

_Get the maximum packet size for the given data links._ 
```C++
virtual size_t jac::OutputPacketCommunicator::maxPacketSize (
    std::vector< int > links
) const = 0
```





**Parameters:**


* `links` the data link ids 



**Returns:**

The maximum packet size 





        

### function operator= 

```C++
OutputPacketCommunicator & jac::OutputPacketCommunicator::operator= (
    const OutputPacketCommunicator &
) = delete
```




### function ~OutputPacketCommunicator 

```C++
virtual jac::OutputPacketCommunicator::~OutputPacketCommunicator () = default
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/communicator.h`