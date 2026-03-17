# MUD-Space Development Plan

## Overview
Space-themed MUD (Multi-User Dungeon) built in C++ using Boost.Asio for networking.

## Phase 1: Networking Foundation
- [x] Project skeleton with CMake
- [x] Set up Boost.Asio TCP server accepting connections
- [x] Basic telnet client session handling
- [x] Echo server to validate round-trip communication
- [ ] Wire Session into Server accept handler
- [ ] Handle multiple concurrent sessions

## Phase 2: Core MUD Loop
- [ ] Command parser (input tokenizer)
- [ ] Game loop with tick-based updates
- [ ] Player session state management
- [ ] Room/location data structures

## Phase 3: World Building
- [ ] Room navigation (north/south/east/west/up/down)
- [ ] Room descriptions and look command
- [ ] Inter-player communication (say, shout)
- [ ] Basic inventory system

## Phase 4: Space Theme
- [ ] Ship systems and navigation
- [ ] Sector/star system map
- [ ] Docking and undocking mechanics

## Tech Stack
- C++17
- CMake build system
- Boost.Asio (async networking)
- gcc / MSVC

## Current Status
Phase 1 — TCP server is up, Session class handles per-connection read/write loop with basic command dispatch (look, quit). Next step is wiring Session into the Server accept handler and managing multiple concurrent sessions.
