---
title: Moving command handling to Session centralizes game logic
date: 2026-04-05
tags: [design, refactor, session]
type: pattern
project: DapperBanana/MUD-Space
---

The decision to move command handling into the `Session` class is a good architectural choice. It centralizes the game's logic and state management within a single, well-defined scope. This reduces coupling with other parts of the system, improves code organization, and makes it easier to reason about the game's behavior. Before, the command dispatcher felt detached; now it's directly tied to the player's session.
