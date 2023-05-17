
# Namespace jac



[**Namespace List**](namespaces.md) **>** [**jac**](namespacejac.md)















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**CobsEncoder**](structjac_1_1CobsEncoder.md) <br> |
| class | [**Consumer**](classjac_1_1Consumer.md) <br>_Interface for a packet consumer._  |
| class | [**Crc16**](classjac_1_1Crc16.md) <br> |
| class | [**DataLinkRx**](classjac_1_1DataLinkRx.md) <br>_Interface that allows for receiving and processing packets from a data link._  |
| class | [**DataLinkTx**](classjac_1_1DataLinkTx.md) <br>_Interface that allows for creation and sending of packets to a data link._  |
| struct | [**DecodeResult**](structjac_1_1DecodeResult.md) <br> |
| class | [**Duplex**](classjac_1_1Duplex.md) <br>_Interface for an byte input/output stream._  |
| class | [**Duplexify**](classjac_1_1Duplexify.md) <br>_A duplex stream that wraps an input and output stream._  |
| class | [**InputPacketCommunicator**](classjac_1_1InputPacketCommunicator.md) <br>_Communicator interface that can be used to receive packets._  |
| class | [**InputStream**](classjac_1_1InputStream.md) <br>_Interface for a binary input stream._  |
| class | [**InputStreamCommunicator**](classjac_1_1InputStreamCommunicator.md) <br>_Communicator interface that can be used to receive stream data._  |
| class | [**Mux**](classjac_1_1Mux.md) &lt;class Encoder&gt;<br>_A multiplexer that creates 256 channels on a single stream connection._  |
| class | [**OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md) <br>_Communicator interface that can be used to send packets._  |
| class | [**OutputStream**](classjac_1_1OutputStream.md) <br>_Interface for a binary output stream._  |
| class | [**OutputStreamCommunicator**](classjac_1_1OutputStreamCommunicator.md) <br>_Communicator interface that can be used send stream data._  |
| class | [**Packet**](classjac_1_1Packet.md) <br>_Interface for building packets._  |
| class | [**Router**](classjac_1_1Router.md) <br>_A router that can route packets from multiple data links to to consumers on specific channels._  |
| class | [**RouterInputPacketCommunicator**](classjac_1_1RouterInputPacketCommunicator.md) <br> |
| class | [**RouterInputStreamCommunicator**](classjac_1_1RouterInputStreamCommunicator.md) <br> |
| class | [**RouterOutputPacketCommunicator**](classjac_1_1RouterOutputPacketCommunicator.md) <br> |
| class | [**RouterOutputStreamCommunicator**](classjac_1_1RouterOutputStreamCommunicator.md) <br> |

## Public Types

| Type | Name |
| ---: | :--- |
| enum int | [**MuxError**](#enum-muxerror)  <br> |












## Public Types Documentation


### enum MuxError 

```C++
enum jac::MuxError {
    INVALID_RECEIVE = 1,
    PACKETIZER = 2,
    PROCESSING = 3
};
```




------------------------------
The documentation for this class was generated from the following file `src/jac/link/communicator.h`