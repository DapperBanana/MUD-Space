---
title: Use `init` pattern for complex object setup
date: 2026-04-22
tags: [object-lifecycle, c++, initialization]
type: pattern
project: DapperBanana/MUD-Space
---

Moving the room initialization logic from the `Game` constructor to a separate `init` method is a good pattern, especially as the game world becomes more complex.  Constructors should ideally perform minimal work, mainly focusing on setting up the object's core state.  Moving heavier initialization logic to an `init` method (or similar) allows for more controlled startup, potential error handling during initialization, and clearer separation of concerns.  This pattern is especially useful if the initialization process might fail, as constructors in C++ don't have a straightforward way to signal errors (other than exceptions, which aren't always the best choice).
