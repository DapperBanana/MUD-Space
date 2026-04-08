---
title: Integrating the Player struct into the Game Loop
date: 2026-04-08
tags: [game-state, design]
type: technique
project: DapperBanana/MUD-Space
---

The `Player` struct has been integrated into the main game loop. This is a key step for managing game state and player interactions. The game loop now handles the creation of new players and, presumably, will eventually manage their actions, locations, and other game-relevant properties. This integration centralizes player management within the core game logic, which is crucial for building complex game mechanics later. Consider the lifetime and scope of these `Player` instances. Are they intended to persist across game sessions, or are they temporary objects created and destroyed within a single game run? Also, consider the data structure used to store these players.
