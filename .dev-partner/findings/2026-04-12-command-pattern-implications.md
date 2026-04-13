---
title: Command Pattern Granularity
date: 2026-04-12
tags: [command pattern, game design]
type: pattern
project: DapperBanana/MUD-Space
---

The recent commits heavily leverage the command pattern. While this offers excellent extensibility for adding new player actions, it's worth considering the granularity of the commands. Currently, it seems like each player action (e.g., 'look', 'quit') gets its own command class.  For a small MUD, this is fine, but as the game grows, the number of command classes could become unwieldy.  Consider grouping related actions under a single command, possibly using a data structure within the command to specify the precise action.  This could help reduce the overall complexity and number of classes to maintain. For example, an `InventoryCommand` could handle 'look inventory', 'take item', 'drop item', etc.
