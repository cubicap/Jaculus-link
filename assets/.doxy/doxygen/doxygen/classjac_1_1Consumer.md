
# Class jac::Consumer



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**Consumer**](classjac_1_1Consumer.md)



_Interface for a packet consumer._ 

* `#include <linkTypes.h>`





Inherited by the following classes: [jac::RouterInputPacketCommunicator](classjac_1_1RouterInputPacketCommunicator.md),  [jac::RouterInputStreamCommunicator](classjac_1_1RouterInputStreamCommunicator.md)










## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Consumer**](#function-consumer-13) () = default<br> |
|   | [**Consumer**](#function-consumer-23) (const [**Consumer**](classjac_1_1Consumer.md) &) = delete<br> |
|   | [**Consumer**](#function-consumer-33) ([**Consumer**](classjac_1_1Consumer.md) &&) = delete<br> |
|  [**Consumer**](classjac_1_1Consumer.md) & | [**operator=**](#function-operator) (const [**Consumer**](classjac_1_1Consumer.md) &) = delete<br> |
|  [**Consumer**](classjac_1_1Consumer.md) & | [**operator=**](#function-operator_1) ([**Consumer**](classjac_1_1Consumer.md) &&) = delete<br> |
| virtual void | [**processPacket**](#function-processpacket) (int linkId, std::span&lt; const uint8\_t &gt; data) = 0<br> |
| virtual  | [**~Consumer**](#function-consumer) () = default<br> |








## Public Functions Documentation


### function Consumer [1/3]

```C++
jac::Consumer::Consumer () = default
```




### function Consumer [2/3]

```C++
jac::Consumer::Consumer (
    const Consumer &
) = delete
```




### function Consumer [3/3]

```C++
jac::Consumer::Consumer (
    Consumer &&
) = delete
```




### function operator= 

```C++
Consumer & jac::Consumer::operator= (
    const Consumer &
) = delete
```




### function operator= 

```C++
Consumer & jac::Consumer::operator= (
    Consumer &&
) = delete
```




### function processPacket 

```C++
virtual void jac::Consumer::processPacket (
    int linkId,
    std::span< const uint8_t > data
) = 0
```




### function ~Consumer 

```C++
virtual jac::Consumer::~Consumer () = default
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/linkTypes.h`