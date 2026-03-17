---
title: CMakeLists configuration for Boost.Asio
date: 2026-03-16
tags: [build, gotcha]
type: gotcha
project: DapperBanana/MUD-Space
---

Asio is header-only by default, but depending on your Boost version and CMake setup, you might need `find_package(Boost REQUIRED COMPONENTS system)` and link against `Boost::system` even for async I/O. The headers compile fine without it, but runtime errors can creep in on some platforms if the system library isn't linked.

Also worth noting: Asio in standalone mode (not Boost.Asio) is an option if you want to avoid Boost as a dependency — it's just a different include path. If you're keeping Boost for the full ecosystem (threading, signals, etc.), stick with Boost.Asio, but if it's just Asio you need, grabbing the standalone version can simplify deps.

For a MUD that might grow to multiple platforms (Windows, Linux), test your CMake on both early — Windows/MSVC can have finicky Boost detection, and mixing static/dynamic linking can bite you later.
