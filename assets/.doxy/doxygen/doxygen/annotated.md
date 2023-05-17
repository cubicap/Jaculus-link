# Class List

Here are the classes, structs, unions and interfaces with brief descriptions:


* **namespace** [**jac**](namespacejac.md)   
  * **struct** [**CobsEncoder**](structjac_1_1CobsEncoder.md)   
    * **class** [**Packetizer**](classjac_1_1CobsEncoder_1_1Packetizer.md)   
    * **class** [**Serializer**](classjac_1_1CobsEncoder_1_1Serializer.md)   
  * **class** [**Consumer**](classjac_1_1Consumer.md) _Interface for a packet consumer._   
  * **class** [**Crc16**](classjac_1_1Crc16.md)   
  * **class** [**DataLinkRx**](classjac_1_1DataLinkRx.md) _Interface that allows for receiving and processing packets from a data link._   
  * **class** [**DataLinkTx**](classjac_1_1DataLinkTx.md) _Interface that allows for creation and sending of packets to a data link._   
  * **struct** [**DecodeResult**](structjac_1_1DecodeResult.md)   
  * **class** [**Duplex**](classjac_1_1Duplex.md) _Interface for an byte input/output stream._ 
  * **class** [**Duplexify**](classjac_1_1Duplexify.md) _A duplex stream that wraps an input and output stream._   
  * **class** [**InputPacketCommunicator**](classjac_1_1InputPacketCommunicator.md) _Communicator interface that can be used to receive packets._   
  * **class** [**InputStream**](classjac_1_1InputStream.md) _Interface for a binary input stream._   
  * **class** [**InputStreamCommunicator**](classjac_1_1InputStreamCommunicator.md) _Communicator interface that can be used to receive stream data._   
  * **class** [**Mux**](classjac_1_1Mux.md) _A multiplexer that creates 256 channels on a single stream connection._   
  * **class** [**OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md) _Communicator interface that can be used to send packets._   
  * **class** [**OutputStream**](classjac_1_1OutputStream.md) _Interface for a binary output stream._   
  * **class** [**OutputStreamCommunicator**](classjac_1_1OutputStreamCommunicator.md) _Communicator interface that can be used send stream data._   
  * **class** [**Packet**](classjac_1_1Packet.md) _Interface for building packets._   
  * **class** [**Router**](classjac_1_1Router.md) _A router that can route packets from multiple data links to to consumers on specific channels._   
    * **class** [**Handle**](classjac_1_1Router_1_1Handle.md) _A handle for receiving packets from a data link._   
  * **class** [**RouterInputPacketCommunicator**](classjac_1_1RouterInputPacketCommunicator.md)   
  * **class** [**RouterInputStreamCommunicator**](classjac_1_1RouterInputStreamCommunicator.md)   
  * **class** [**RouterOutputPacketCommunicator**](classjac_1_1RouterOutputPacketCommunicator.md)   
  * **class** [**RouterOutputStreamCommunicator**](classjac_1_1RouterOutputStreamCommunicator.md)   
* **struct** [**PacketStructure**](structjac_1_1CobsEncoder_1_1PacketStructure.md)   
* **class** [**DataFrame**](classjac_1_1CobsEncoder_1_1Serializer_1_1DataFrame.md)   
* **class** [**MuxPacket**](classjac_1_1Mux_1_1MuxPacket.md)   
* **class** [**MulticastPacket**](classjac_1_1Router_1_1MulticastPacket.md)   