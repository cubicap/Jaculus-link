# Usage

## Build

The library is header-only and does not require any additional dependencies.

It uses the CMake build system and exports a `jac-link` target that can be used to link against the library.

## Example

The following code shows how to configure the whole communication stack and send and receive data.

```cpp
#include <jac/link/mux.h>
#include <jac/link/router.h>
#include <jac/link/routerCommunicator.h>
#include <jac/link/encoders/cobs.h>


using namespace jac;

// Define a stream connection - read operations are non-blocking
class MyStream : public Duplex {
public:
    int get() override { ... }
    size_t read(std::span<uint8_t> data) override { ... }
    bool put(uint8_t c) override { ... }
    size_t write(std::span<const uint8_t> data) override { ... }
    bool flush() override { ... }
};

int main() {
    // Create a router
    Router router;

    // Create a stream connection
    auto stream = std::make_unique<MyStream>();

    // Configure a data link
    Mux<CobsEncoder> mux(std::move(stream));

    // Connect the data link to the router
    auto handle = router.subscribeTx(1, mux);
    mux.bindRx(std::make_unique<decltype(handle)>(std::move(handle)));


    // Create an input stream communicator
    RouterInputStreamCommunicator input({});

    // Subscribe the communicator to the router
    router.subscribeChannel(1, input);

    // Create an output stream communicator and connect it to router
    RouterOutputStreamCommunicator output(router, 1, {});


    // Send data
    std::vector<uint8_t> buffer = { 1, 2, 3, 4, 5 };
    output.write(std::span(buffer.data(), buffer.size()));

    // Receive data - blocks until any data is received
    std::vector<uint8_t> received(64);
    input.read(std::span(received.data(), received.size()));
}
```
