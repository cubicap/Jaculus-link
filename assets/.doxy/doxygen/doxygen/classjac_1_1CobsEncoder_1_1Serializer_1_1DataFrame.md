
# Class jac::CobsEncoder::Serializer::DataFrame



[**ClassList**](annotated.md) **>** [**DataFrame**](classjac_1_1CobsEncoder_1_1Serializer_1_1DataFrame.md)








Inherits the following classes: jac::CobsEncoder::PacketStructure












## Public Functions

| Type | Name |
| ---: | :--- |
|  std::span&lt; const uint8\_t &gt; | [**finalize**](#function-finalize) (uint8\_t channel) <br> |
|  bool | [**put**](#function-put-12) (uint8\_t c) <br> |
|  size\_t | [**put**](#function-put-22) (std::span&lt; const uint8\_t &gt; data) <br> |
|  size\_t | [**size**](#function-size) () const<br> |








## Public Functions Documentation


### function finalize 

```C++
inline std::span< const uint8_t > DataFrame::finalize (
    uint8_t channel
) 
```




### function put [1/2]

```C++
inline bool DataFrame::put (
    uint8_t c
) 
```




### function put [2/2]

```C++
inline size_t DataFrame::put (
    std::span< const uint8_t > data
) 
```




### function size 

```C++
inline size_t DataFrame::size () const
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/encoders/cobs.h`