---
title: Removing redundant `return` statements clarifies control flow
date: 2026-04-05
tags: [bugfix, readability]
type: gotcha
project: DapperBanana/MUD-Space
---

The removal of the redundant `return` statement in `Session::do_read` highlights the importance of clean control flow. Redundant returns can make code harder to read and debug, as they introduce unnecessary complexity. This small fix improves the clarity and maintainability of the code. This is a good practice for any language but especially so in C++ due to the potential for RAII interactions.
