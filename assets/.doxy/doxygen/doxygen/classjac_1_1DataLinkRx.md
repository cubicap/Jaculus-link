
# Class jac::DataLinkRx



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**DataLinkRx**](classjac_1_1DataLinkRx.md)



_Interface that allows for receiving and processing packets from a data link._ 

* `#include <linkTypes.h>`





Inherited by the following classes: [jac::Router::Handle](classjac_1_1Router_1_1Handle.md)










## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**DataLinkRx**](#function-datalinkrx-13) () = default<br> |
|   | [**DataLinkRx**](#function-datalinkrx-23) (const [**DataLinkRx**](classjac_1_1DataLinkRx.md) &) = delete<br> |
|   | [**DataLinkRx**](#function-datalinkrx-33) ([**DataLinkRx**](classjac_1_1DataLinkRx.md) &&) = delete<br> |
|  [**DataLinkRx**](classjac_1_1DataLinkRx.md) & | [**operator=**](#function-operator) (const [**DataLinkRx**](classjac_1_1DataLinkRx.md) &) = delete<br> |
|  [**DataLinkRx**](classjac_1_1DataLinkRx.md) & | [**operator=**](#function-operator_1) ([**DataLinkRx**](classjac_1_1DataLinkRx.md) &&) = delete<br> |
| virtual void | [**processPacket**](#function-processpacket) (uint8\_t channel, std::span&lt; const uint8\_t &gt; data) = 0<br>_Process a received packet on the given channel._  |
| virtual  | [**~DataLinkRx**](#function-datalinkrx) () = default<br> |








## Public Functions Documentation


### function DataLinkRx [1/3]

```C++
jac::DataLinkRx::DataLinkRx () = default
```




### function DataLinkRx [2/3]

```C++
jac::DataLinkRx::DataLinkRx (
    const DataLinkRx &
) = delete
```




### function DataLinkRx [3/3]

```C++
jac::DataLinkRx::DataLinkRx (
    DataLinkRx &&
) = delete
```




### function operator= 

```C++
DataLinkRx & jac::DataLinkRx::operator= (
    const DataLinkRx &
) = delete
```




### function operator= 

```C++
DataLinkRx & jac::DataLinkRx::operator= (
    DataLinkRx &&
) = delete
```




### function processPacket 

_Process a received packet on the given channel._ 
```C++
virtual void jac::DataLinkRx::processPacket (
    uint8_t channel,
    std::span< const uint8_t > data
) = 0
```





**Parameters:**


* `channel` the channel 
* `data` data of the packet 




        

### function ~DataLinkRx 

```C++
virtual jac::DataLinkRx::~DataLinkRx () = default
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/linkTypes.h`