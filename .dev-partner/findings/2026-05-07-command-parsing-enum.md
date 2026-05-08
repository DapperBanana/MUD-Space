---
title: Direction parsing uses an enum now
date: 2026-05-07
tags: [enums, parsing, c++]
type: pattern
project: DapperBanana/MUD-Space
---

The new movement command parsing cleanly uses an enum ( `enum class Direction`) to represent the cardinal directions. This is a good practice. Using an enum makes the code more readable and maintainable compared to using string literals or integer constants.  The `switch` statement handling the `Direction` enum is much cleaner. This approach also helps prevent errors, as the compiler can catch invalid direction values at compile time, rather than at runtime.
