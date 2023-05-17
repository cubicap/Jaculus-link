
# Class jac::DataLinkTx



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**DataLinkTx**](classjac_1_1DataLinkTx.md)



_Interface that allows for creation and sending of packets to a data link._ 

* `#include <linkTypes.h>`





Inherited by the following classes: [jac::Mux](classjac_1_1Mux.md)










## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DataLinkTx**](#function-datalinktx-13) () = default<br> |
|   | [**DataLinkTx**](#function-datalinktx-23) (const [**DataLinkTx**](classjac_1_1DataLinkTx.md) &) = delete<br> |
|   | [**DataLinkTx**](#function-datalinktx-33) ([**DataLinkTx**](classjac_1_1DataLinkTx.md) &&) = delete<br> |
| virtual std::unique\_ptr&lt; [**Packet**](classjac_1_1Packet.md) &gt; | [**buildPacket**](#function-buildpacket) (uint8\_t channel) = 0<br>_Build a packet for the given channel._  |
| virtual size\_t | [**maxPacketSize**](#function-maxpacketsize) () const = 0<br>_Get the maximum packet size for the given channel._  |
|  [**DataLinkTx**](classjac_1_1DataLinkTx.md) & | [**operator=**](#function-operator) (const [**DataLinkTx**](classjac_1_1DataLinkTx.md) &) = delete<br> |
|  [**DataLinkTx**](classjac_1_1DataLinkTx.md) & | [**operator=**](#function-operator_1) ([**DataLinkTx**](classjac_1_1DataLinkTx.md) &&) = delete<br> |








## Public Functions Documentation


### function DataLinkTx [1/3]

```C++
jac::DataLinkTx::DataLinkTx () = default
```




### function DataLinkTx [2/3]

```C++
jac::DataLinkTx::DataLinkTx (
    const DataLinkTx &
) = delete
```




### function DataLinkTx [3/3]

```C++
jac::DataLinkTx::DataLinkTx (
    DataLinkTx &&
) = delete
```




### function buildPacket 

_Build a packet for the given channel._ 
```C++
virtual std::unique_ptr< Packet > jac::DataLinkTx::buildPacket (
    uint8_t channel
) = 0
```





**Parameters:**


* `channel` the channel 



**Returns:**

The packet 





        

### function maxPacketSize 

_Get the maximum packet size for the given channel._ 
```C++
virtual size_t jac::DataLinkTx::maxPacketSize () const = 0
```





**Parameters:**


* `channel` the channel 



**Returns:**

The maximum packet size 





        

### function operator= 

```C++
DataLinkTx & jac::DataLinkTx::operator= (
    const DataLinkTx &
) = delete
```




### function operator= 

```C++
DataLinkTx & jac::DataLinkTx::operator= (
    DataLinkTx &&
) = delete
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/linkTypes.h`