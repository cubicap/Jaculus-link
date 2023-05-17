
# Class jac::Crc16



[**ClassList**](annotated.md) **>** [**jac**](namespacejac.md) **>** [**Crc16**](classjac_1_1Crc16.md)




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Crc16**](#function-crc16) () <br> |
|  void | [**reset**](#function-reset) () <br> |
|  void | [**update**](#function-update-12) (uint8\_t c) <br> |
|  void | [**update**](#function-update-22) (std::span&lt; const uint8\_t &gt; data) <br> |
|  uint16\_t | [**value**](#function-value) () const<br> |








## Public Functions Documentation


### function Crc16 

```C++
inline jac::Crc16::Crc16 () 
```




### function reset 

```C++
inline void jac::Crc16::reset () 
```




### function update [1/2]

```C++
inline void jac::Crc16::update (
    uint8_t c
) 
```




### function update [2/2]

```C++
inline void jac::Crc16::update (
    std::span< const uint8_t > data
) 
```




### function value 

```C++
inline uint16_t jac::Crc16::value () const
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/util/crc.h`