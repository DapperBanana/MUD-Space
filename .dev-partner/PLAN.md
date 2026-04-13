## Phase 1: Networking Foundation
- [x] Project skeleton with CMake
- [x] Set up Boost.Asio TCP server accepting connections
- [x] Basic telnet client session handling
- [x] Echo server to validate round-trip communication
- [x] Wire Session into Server accept handler
- [x] Handle multiple concurrent sessions

## Phase 2: Core MUD Loop
- [x] Command parser (input tokenizer)
- [x] Basic command dispatch (look, say, help, quit)
- [x] Game loop with tick-based updates
- [ ] Player session state management
- [x] Room/location data structures
- [ ] Broadcast messages to other sessions in same room

## Phase 3: World Building
- [ ] Room graph with exits/connections
- [ ] Movement between rooms
- [ ] Room descriptions and object placeholders
- [ ] Persistent world state