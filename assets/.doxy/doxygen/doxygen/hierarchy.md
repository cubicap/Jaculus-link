# Class Hierarchy

This inheritance list is sorted roughly, but not completely, alphabetically:


* **class** [**jac::CobsEncoder::Serializer**](classjac_1_1CobsEncoder_1_1Serializer.md) 
* **class** [**jac::Consumer**](classjac_1_1Consumer.md) _Interface for a packet consumer._   
  * **class** [**jac::RouterInputPacketCommunicator**](classjac_1_1RouterInputPacketCommunicator.md) 
  * **class** [**jac::RouterInputStreamCommunicator**](classjac_1_1RouterInputStreamCommunicator.md) 
* **class** [**jac::Crc16**](classjac_1_1Crc16.md) 
* **class** [**jac::DataLinkRx**](classjac_1_1DataLinkRx.md) _Interface that allows for receiving and processing packets from a data link._   
  * **class** [**jac::Router::Handle**](classjac_1_1Router_1_1Handle.md) _A handle for receiving packets from a data link._ 
* **class** [**jac::DataLinkTx**](classjac_1_1DataLinkTx.md) _Interface that allows for creation and sending of packets to a data link._   
  * **class** [**jac::Mux**](classjac_1_1Mux.md) _A multiplexer that creates 256 channels on a single stream connection._ 
* **class** [**jac::InputStream**](classjac_1_1InputStream.md) _Interface for a binary input stream._   
  * **class** [**jac::Duplex**](classjac_1_1Duplex.md) _Interface for an byte input/output stream._   
    * **class** [**jac::Duplexify**](classjac_1_1Duplexify.md) _A duplex stream that wraps an input and output stream._ 
* **class** [**jac::OutputStream**](classjac_1_1OutputStream.md) _Interface for a binary output stream._   
  * **class** [**jac::Duplex**](classjac_1_1Duplex.md) _Interface for an byte input/output stream._   
    * **class** [**jac::Duplexify**](classjac_1_1Duplexify.md) _A duplex stream that wraps an input and output stream._ 
* **class** [**jac::InputPacketCommunicator**](classjac_1_1InputPacketCommunicator.md) _Communicator interface that can be used to receive packets._   
  * **class** [**jac::RouterInputPacketCommunicator**](classjac_1_1RouterInputPacketCommunicator.md) 
* **class** [**jac::InputStreamCommunicator**](classjac_1_1InputStreamCommunicator.md) _Communicator interface that can be used to receive stream data._   
  * **class** [**jac::RouterInputStreamCommunicator**](classjac_1_1RouterInputStreamCommunicator.md) 
* **class** [**jac::OutputPacketCommunicator**](classjac_1_1OutputPacketCommunicator.md) _Communicator interface that can be used to send packets._   
  * **class** [**jac::RouterOutputPacketCommunicator**](classjac_1_1RouterOutputPacketCommunicator.md) 
* **class** [**jac::OutputStreamCommunicator**](classjac_1_1OutputStreamCommunicator.md) _Communicator interface that can be used send stream data._   
  * **class** [**jac::RouterOutputStreamCommunicator**](classjac_1_1RouterOutputStreamCommunicator.md) 
* **class** [**jac::Packet**](classjac_1_1Packet.md) _Interface for building packets._ 
* **class** [**jac::Router**](classjac_1_1Router.md) _A router that can route packets from multiple data links to to consumers on specific channels._ 
* **struct** [**jac::CobsEncoder**](structjac_1_1CobsEncoder.md) 
* **struct** [**jac::DecodeResult**](structjac_1_1DecodeResult.md) 
* **struct** [**jac::CobsEncoder::PacketStructure**](structjac_1_1CobsEncoder_1_1PacketStructure.md)   
  * **class** [**jac::CobsEncoder::Packetizer**](classjac_1_1CobsEncoder_1_1Packetizer.md) 
* **class** **jac::CobsEncoder::PacketStructure**  
  * **class** [**jac::CobsEncoder::Packetizer**](classjac_1_1CobsEncoder_1_1Packetizer.md) 
  * **class** [**jac::CobsEncoder::Serializer::DataFrame**](classjac_1_1CobsEncoder_1_1Serializer_1_1DataFrame.md) 