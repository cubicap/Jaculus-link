
# Struct jac::CobsEncoder::PacketStructure



[**ClassList**](annotated.md) **>** [**PacketStructure**](structjac_1_1CobsEncoder_1_1PacketStructure.md)










Inherited by the following classes: [jac::CobsEncoder::Packetizer](classjac_1_1CobsEncoder_1_1Packetizer.md)








## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::array&lt; uint8\_t, OFFSET\_DATA+SIZE\_DATA\_MAX+SIZE\_CHECKSUM &gt; | [**buffer**](#variable-buffer)  <br> |

## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr uint8\_t | [**DELIMITER**](#variable-delimiter)   = = 0x00<br> |
|  constexpr size\_t | [**OFFSET\_CHANNEL**](#variable-offset_channel)   = = OFFSET\_COBS + 1<br> |
|  constexpr size\_t | [**OFFSET\_COBS**](#variable-offset_cobs)   = = 2<br> |
|  constexpr size\_t | [**OFFSET\_DATA**](#variable-offset_data)   = = OFFSET\_CHANNEL + SIZE\_CHANNEL<br> |
|  constexpr size\_t | [**OFFSET\_DELIMITER**](#variable-offset_delimiter)   = = 0<br> |
|  constexpr size\_t | [**OFFSET\_LENGTH**](#variable-offset_length)   = = 1<br> |
|  constexpr size\_t | [**SIZE\_CHANNEL**](#variable-size_channel)   = = 1<br> |
|  constexpr size\_t | [**SIZE\_CHECKSUM**](#variable-size_checksum)   = = 2<br> |
|  constexpr size\_t | [**SIZE\_DATA\_MAX**](#variable-size_data_max)   = = 254 - SIZE\_CHANNEL - SIZE\_CHECKSUM<br> |
|  constexpr size\_t | [**SIZE\_LENGTH**](#variable-size_length)   = = 1<br> |









## Public Attributes Documentation


### variable buffer 

```C++
std::array<uint8_t, OFFSET_DATA + SIZE_DATA_MAX + SIZE_CHECKSUM> jac::CobsEncoder::PacketStructure::buffer;
```



## Public Static Attributes Documentation


### variable DELIMITER 

```C++
constexpr uint8_t jac::CobsEncoder::PacketStructure::DELIMITER;
```




### variable OFFSET\_CHANNEL 

```C++
constexpr size_t jac::CobsEncoder::PacketStructure::OFFSET_CHANNEL;
```




### variable OFFSET\_COBS 

```C++
constexpr size_t jac::CobsEncoder::PacketStructure::OFFSET_COBS;
```




### variable OFFSET\_DATA 

```C++
constexpr size_t jac::CobsEncoder::PacketStructure::OFFSET_DATA;
```




### variable OFFSET\_DELIMITER 

```C++
constexpr size_t jac::CobsEncoder::PacketStructure::OFFSET_DELIMITER;
```




### variable OFFSET\_LENGTH 

```C++
constexpr size_t jac::CobsEncoder::PacketStructure::OFFSET_LENGTH;
```




### variable SIZE\_CHANNEL 

```C++
constexpr size_t jac::CobsEncoder::PacketStructure::SIZE_CHANNEL;
```




### variable SIZE\_CHECKSUM 

```C++
constexpr size_t jac::CobsEncoder::PacketStructure::SIZE_CHECKSUM;
```




### variable SIZE\_DATA\_MAX 

```C++
constexpr size_t jac::CobsEncoder::PacketStructure::SIZE_DATA_MAX;
```




### variable SIZE\_LENGTH 

```C++
constexpr size_t jac::CobsEncoder::PacketStructure::SIZE_LENGTH;
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/encoders/cobs.h`