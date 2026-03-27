---
title: Using `io_context::run()` for concurrency
date: 2026-03-27
tags: [boost, asio, concurrency]
type: technique
project: DapperBanana/MUD-Space
---

Boost.Asio's `io_context` provides a mechanism for handling asynchronous operations. Calling `io_context::run()` starts the event loop, and multiple threads can call `run()` to distribute the workload. Each thread picks up pending asynchronous operations, allowing the server to handle multiple client connections concurrently. This avoids the need for explicit thread management for each connection, simplifying the concurrency model.
