---
title: Encapsulating connection logic in a `Session` class
date: 2026-03-27
tags: [design, object-oriented]
type: pattern
project: DapperBanana/MUD-Space
---

Wrapping the connection-specific logic (reading, writing, handling messages) in a `Session` class is a clean way to manage each client connection. This approach promotes code reusability and separation of concerns. Each `Session` instance owns its socket and buffers, preventing data races and making the code easier to reason about. The server's accept handler then becomes responsible for creating and starting these `Session` objects.
