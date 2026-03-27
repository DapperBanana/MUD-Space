---
title: Session object lifetime management
date: 2026-03-27
tags: [c++, memory-management, boost.asio]
type: gotcha
project: DapperBanana/MUD-Space
---

The `Session` object is now instantiated on `accept`. Pay close attention to how the lifetime of the `Session` object is managed, especially in relation to the `boost::asio::io_context`. If the `Session` object is destroyed prematurely (e.g., goes out of scope), the asynchronous operations might lead to errors or unexpected behavior. Consider using `std::shared_ptr` to tie the session's lifetime to the asynchronous operations that are pending. This ensures that the session object remains alive as long as there are outstanding asynchronous operations associated with it.
