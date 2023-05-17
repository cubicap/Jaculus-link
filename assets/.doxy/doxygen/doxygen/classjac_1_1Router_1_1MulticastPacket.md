
# Class jac::Router::MulticastPacket



[**ClassList**](annotated.md) **>** [**MulticastPacket**](classjac_1_1Router_1_1MulticastPacket.md)








Inherits the following classes: [jac::Packet](classjac_1_1Packet.md)
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MulticastPacket**](#function-multicastpacket) ([**Router**](classjac_1_1Router.md) & router, uint8\_t channel, std::vector&lt; int &gt; links) <br> |
|  bool | [**put**](#function-put-12) (uint8\_t c) override<br> |
|  size\_t | [**put**](#function-put-22) (std::span&lt; const uint8\_t &gt; data) override<br> |
|  bool | [**send**](#function-send) () override<br> |
|  size\_t | [**space**](#function-space) () override const<br> |

## Public Functions inherited from jac::Packet

See [jac::Packet](classjac_1_1Packet.md)

| Type | Name |
| ---: | :--- |
|   | [**Packet**](#function-packet-12) () = default<br> |
|   | [**Packet**](#function-packet-22) (const [**Packet**](classjac_1_1Packet.md) &) = delete<br> |
|  [**Packet**](classjac_1_1Packet.md) & | [**operator=**](#function-operator) (const [**Packet**](classjac_1_1Packet.md) &) = delete<br> |
| virtual bool | [**put**](#function-put-12) (uint8\_t c) = 0<br> |
| virtual size\_t | [**put**](#function-put-22) (std::span&lt; const uint8\_t &gt; data) = 0<br> |
| virtual bool | [**send**](#function-send) () = 0<br> |
| virtual size\_t | [**space**](#function-space) () const = 0<br> |
| virtual  | [**~Packet**](#function-packet) () = default<br> |















## Public Functions Documentation


### function MulticastPacket 

```C++
inline MulticastPacket::MulticastPacket (
    Router & router,
    uint8_t channel,
    std::vector< int > links
) 
```




### function put [1/2]

```C++
inline bool MulticastPacket::put (
    uint8_t c
) override
```




### function put [2/2]

```C++
inline size_t MulticastPacket::put (
    std::span< const uint8_t > data
) override
```




### function send 

```C++
inline bool MulticastPacket::send () override
```




### function space 

```C++
inline size_t MulticastPacket::space () override const
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/router.h`