---
title: Integrating Command Dispatch into Session Read Loop
date: 2026-04-02
tags: [asio, networking, event loop]
type: technique
project: DapperBanana/MUD-Space
---

The command dispatcher is integrated into the `Session`'s read loop, allowing the MUD to process player input as it arrives. Within the read loop, after receiving input from the client via Boost.Asio, the input is parsed, and the corresponding command is dispatched for execution. This ensures that commands are handled in a timely and responsive manner, providing a smooth gameplay experience. It's important to handle potential errors (e.g., invalid commands) gracefully within the read loop to prevent unexpected disconnections or crashes.
