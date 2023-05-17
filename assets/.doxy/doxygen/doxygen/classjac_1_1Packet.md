
# Class jac::Packet



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**Packet**](classjac_1_1Packet.md)



_Interface for building packets._ 

* `#include <linkTypes.h>`















## Public Functions

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


### function Packet [1/2]

```C++
jac::Packet::Packet () = default
```




### function Packet [2/2]

```C++
jac::Packet::Packet (
    const Packet &
) = delete
```




### function operator= 

```C++
Packet & jac::Packet::operator= (
    const Packet &
) = delete
```




### function put [1/2]

```C++
virtual bool jac::Packet::put (
    uint8_t c
) = 0
```




### function put [2/2]

```C++
virtual size_t jac::Packet::put (
    std::span< const uint8_t > data
) = 0
```




### function send 

```C++
virtual bool jac::Packet::send () = 0
```




### function space 

```C++
virtual size_t jac::Packet::space () const = 0
```




### function ~Packet 

```C++
virtual jac::Packet::~Packet () = default
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/linkTypes.h`