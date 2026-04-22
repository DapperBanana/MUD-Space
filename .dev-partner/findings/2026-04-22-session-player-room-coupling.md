---
title: Session sets player room; consider decoupling
date: 2026-04-22
tags: [coupling, game-design, session-management]
type: gotcha
project: DapperBanana/MUD-Space
---

Having the `Session` directly manipulate the `Player`'s current room creates a tight coupling between these two classes. While it works for a simple game, consider alternative approaches as complexity grows. For instance, the `Game` could manage the players and their rooms, with the `Session` simply requesting the player to be moved to a specific room. This would allow the `Game` to handle any game-world logic associated with player movement (e.g., checking for locked doors, triggering events). Alternatively, a command pattern might be useful, where a `MovePlayerCommand` encapsulates the action of moving a player.
