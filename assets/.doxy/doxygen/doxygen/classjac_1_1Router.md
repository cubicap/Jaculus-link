
# Class jac::Router



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**Router**](classjac_1_1Router.md)



_A router that can route packets from multiple data links to to consumers on specific channels._ 

* `#include <router.h>`










## Classes

| Type | Name |
| ---: | :--- |
| class | [**Handle**](classjac_1_1Router_1_1Handle.md) <br>_A handle for receiving packets from a data link._  |





## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Router**](#function-router-13) () = default<br> |
|   | [**Router**](#function-router-23) (const [**Router**](classjac_1_1Router.md) &) = delete<br> |
|   | [**Router**](#function-router-33) ([**Router**](classjac_1_1Router.md) &&) = delete<br> |
|  std::unique\_ptr&lt; [**Packet**](classjac_1_1Packet.md) &gt; | [**buildPacket**](#function-buildpacket) (uint8\_t channel, std::vector&lt; int &gt; links) <br>_Build a packet for a channel and data links._  |
|  size\_t | [**maxPacketSize**](#function-maxpacketsize) (uint8\_t channel, std::vector&lt; int &gt; links) <br>_Get the maximum packet size for a channel and data links._  |
|  [**Router**](classjac_1_1Router.md) & | [**operator=**](#function-operator) (const [**Router**](classjac_1_1Router.md) &) = delete<br> |
|  [**Router**](classjac_1_1Router.md) & | [**operator=**](#function-operator_1) ([**Router**](classjac_1_1Router.md) &&) = delete<br> |
|  void | [**setGlobalCallback**](#function-setglobalcallback) (std::function&lt; void(int linkId, uint8\_t channel, std::span&lt; const uint8\_t &gt; data)&gt; callback) <br>_Set global callback which is called whenever a packet is received on any channel and data link._  |
|  void | [**subscribeChannel**](#function-subscribechannel) (uint8\_t channel, [**Consumer**](classjac_1_1Consumer.md) & consumer) <br>_Subscribe a channel to a consumer._  |
|  [**Handle**](classjac_1_1Router_1_1Handle.md) | [**subscribeTx**](#function-subscribetx) (int id, [**DataLinkTx**](classjac_1_1DataLinkTx.md) & tx) <br>_Subscribe a data link transmitter to the router._  |








## Public Functions Documentation


### function Router [1/3]

```C++
jac::Router::Router () = default
```




### function Router [2/3]

```C++
jac::Router::Router (
    const Router &
) = delete
```




### function Router [3/3]

```C++
jac::Router::Router (
    Router &&
) = delete
```




### function buildPacket 

_Build a packet for a channel and data links._ 
```C++
inline std::unique_ptr< Packet > jac::Router::buildPacket (
    uint8_t channel,
    std::vector< int > links
) 
```





**Parameters:**


* `channel` the channel 
* `links` the data links 



**Returns:**

The packet 





        

### function maxPacketSize 

_Get the maximum packet size for a channel and data links._ 
```C++
inline size_t jac::Router::maxPacketSize (
    uint8_t channel,
    std::vector< int > links
) 
```





**Parameters:**


* `channel` the channel 
* `links` the data links 



**Returns:**

The maximum packet size 





        

### function operator= 

```C++
Router & jac::Router::operator= (
    const Router &
) = delete
```




### function operator= 

```C++
Router & jac::Router::operator= (
    Router &&
) = delete
```




### function setGlobalCallback 

_Set global callback which is called whenever a packet is received on any channel and data link._ 
```C++
inline void jac::Router::setGlobalCallback (
    std::function< void(int linkId, uint8_t channel, std::span< const uint8_t > data)> callback
) 
```





**Parameters:**


* `callback` the callback 




        

### function subscribeChannel 

_Subscribe a channel to a consumer._ 
```C++
inline void jac::Router::subscribeChannel (
    uint8_t channel,
    Consumer & consumer
) 
```





**Note:**

All packets received on the channel will be passed to the consumer.




**Parameters:**


* `channel` the channel 
* `consumer` the consumer 




        

### function subscribeTx 

_Subscribe a data link transmitter to the router._ 
```C++
inline Handle jac::Router::subscribeTx (
    int id,
    DataLinkTx & tx
) 
```





**Note:**

This allows router to send packets to the data link id. Reciever should be then bound to the returned handle.




**Parameters:**


* `id` id of the data link 
* `tx` the transmitter 



**Returns:**

The handle 





        

------------------------------
The documentation for this class was generated from the following file `src/jac/link/router.h`