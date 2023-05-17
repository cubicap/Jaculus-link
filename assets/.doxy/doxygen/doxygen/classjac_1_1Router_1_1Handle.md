
# Class jac::Router::Handle



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**Router**](classjac_1_1Router.md) **>** [**Handle**](classjac_1_1Router_1_1Handle.md)



_A handle for receiving packets from a data link._ 

* `#include <router.h>`



Inherits the following classes: [jac::DataLinkRx](classjac_1_1DataLinkRx.md)
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Handle**](#function-handle-23) (const [**Handle**](classjac_1_1Router_1_1Handle.md) &) = delete<br> |
|   | [**Handle**](#function-handle-33) ([**Handle**](classjac_1_1Router_1_1Handle.md) && other) <br> |
|  [**Handle**](classjac_1_1Router_1_1Handle.md) & | [**operator=**](#function-operator) (const [**Handle**](classjac_1_1Router_1_1Handle.md) &) = delete<br> |
|  [**Handle**](classjac_1_1Router_1_1Handle.md) & | [**operator=**](#function-operator_1) ([**Handle**](classjac_1_1Router_1_1Handle.md) && other) <br> |
| virtual void | [**processPacket**](#function-processpacket) (uint8\_t channel, std::span&lt; const uint8\_t &gt; data) override<br>_Process a received packet on the given channel._  |
|   | [**~Handle**](#function-handle) () <br> |

## Public Functions inherited from jac::DataLinkRx

See [jac::DataLinkRx](classjac_1_1DataLinkRx.md)

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


### function Handle [2/3]

```C++
jac::Router::Handle::Handle (
    const Handle &
) = delete
```




### function Handle [3/3]

```C++
inline jac::Router::Handle::Handle (
    Handle && other
) 
```




### function operator= 

```C++
Handle & jac::Router::Handle::operator= (
    const Handle &
) = delete
```




### function operator= 

```C++
inline Handle & jac::Router::Handle::operator= (
    Handle && other
) 
```




### function processPacket 

_Process a received packet on the given channel._ 
```C++
inline virtual void jac::Router::Handle::processPacket (
    uint8_t channel,
    std::span< const uint8_t > data
) override
```





**Parameters:**


* `channel` the channel 
* `data` data of the packet 




        
Implements [*jac::DataLinkRx::processPacket*](classjac_1_1DataLinkRx.md#function-processpacket)


### function ~Handle 

```C++
inline jac::Router::Handle::~Handle () 
```


## Friends Documentation



### friend Router 

```C++
class jac::Router::Handle::Router (
    Router
) 
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/router.h`