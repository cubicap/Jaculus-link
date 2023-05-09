# Architecture

The model of Jaculus-link is split into three layers:

1. Data link layer
2. Routing layer
3. Communicator layer

## Data link

The data link is responsible for transmitting data along with channel identifiers. The data link provided in this
library is implemented in the `Mux` class, which multiplexes 256 channels on a single stream connection.

It is possible to use other implementations which use different protocols, provided that they implement the
`ChannelTransmitter` interface for transmission and provide a way to connect them to a `ChannelReceiver` for
processing received data.

## Routing layer

The routing layer is responsible for routing received data to the consumer of the channel. The routing layer
is implemented in the `Router` class.

A `Router` instance can be connected to multiple data links and will route data from all of them to the
appropriate consumer with the information about the link it was received from. It also allows sending data
to a specific link and channel.

## Communicator layer

The communicator layer is used as an abstraction layer for communicating through channels. Typically, the
communicator is associated with a single channel and provides either an interface for sending data or
receiving data.

Communicators used for receiving data from a `Router` must implement the `Consumer` interface, which allows
them to be subscribed to a specific channel on a `Router` instance. They must process the received data without
blocking, preferably only by storing the data in a buffer and processing it later.

Communicators that send data access the `Router` instance directly and send data to a specific channel on
a specific link (or links).

The provided communicator types are:

- `OutputStreamCommunicator` - sends data as a stream of bytes
- `InputStreamCommunicator` - receives data as a stream of bytes
- `OutputPacketCommunicator` - sends data while exposing the underlying data framing
- `InputPacketCommunicator` - receives data while exposing the underlying data framing

The communicators for the `Router` class are implemented in [`jac/link/routerCommunicator.h`](/doxygen/routerCommunicator_8h/)
