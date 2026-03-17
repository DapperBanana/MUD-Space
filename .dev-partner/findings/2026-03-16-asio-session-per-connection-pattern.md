---
title: Per-connection Session objects with Asio read loop
date: 2026-03-16
tags: [pattern, networking]
type: pattern
project: DapperBanana/MUD-Space
---

Setting up individual Session instances per accepted connection is solid for a MUD — it keeps state isolated and scales better than a monolithic accept loop. Each session owns its socket and handles its own async reads, which naturally decouples connection lifecycle from the server's main accept thread.

One thing to watch: if Session stores the socket directly (non-const reference or move), ensure you're not accidentally keeping copies or letting socket lifetime outlive the session. Asio sockets aren't copyable by design, so if Session construction is trying to copy or pass by reference carelessly, you'll hit compile errors — that's actually good feedback to catch ownership issues early.

As the MUD grows and you add command parsing, room state, or player persistence, each Session will become the natural home for that per-connection context. Just be mindful of thread safety if you start doing any cross-session communication (broadcasting to other players, etc.) — you'll want atomic flags or a message queue pattern rather than direct session pointers.
