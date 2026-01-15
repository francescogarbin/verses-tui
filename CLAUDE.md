# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Verses TUI is a Linux terminal user interface (TUI) application for the Verses note-taking platform. It's written in modern C++ and serves as a command-line front-end for managing self-hosted notes, emphasizing micro-data sovereignty.

## Key Principles
1. Maximum sovereignty - native binary, no runtime deps
2. Unix philosophy - do one thing well, integrate with $EDITOR
3. User respect - for sysadmins/power users, not hand-holding
4. Iterative development - ship working software, refine later

## Tech Stack & Why
- **C++ (modern, C++17)** - native binary, zero runtime
- **FTXUI** - modern C++ TUI framework, component-based
- **libcurl** - HTTP client for API calls
- **nlohmann/json** - JSON parsing
- **CMake** - build system

## Guidelines to develop in C++
- no smart pointers and limit the use of pointers in general
- use STL containers and range-based loops, no indexes
- make extensive use of noexcept methods, ideally the code throws no exception
- apply the latest guidelines of Stroustroup 
- when pointers are used, always initialize with nullpts

## Current Repository State

The repository currently contains only documentation (README.md, LICENSE, .gitignore). Source code has not yet been committed. When source is added, expect:
- C++ source files with standard build artifacts (.o, .so, .a, etc.)
- A build system (likely Makefile or CMake)
- TUI library integration (probably ncurses or similar)
- HTTP client for Verses server communication
- TOML configuration parsing

## Architecture

**Three-Panel Layout:**
- Left: Notebooks list panel
- Center: Notes list panel
- Right: Note preview panel (read-only, text-wrapped)
- Bottom: Context-sensitive toolbar

**Key Design Decisions:**
- No in-app editing - delegates to system `$EDITOR` via fork/exec
- No local data storage - all data volatile in RAM, synced from server
- Temporary note files cached in `$XDG_CACHE_HOME/verses-tui/`, deleted after sync

**Configuration:**
- Location: `$XDG_CONFIG_HOME/verses-tui/verses-tui.toml` (follows XDG spec)
- Format: TOML
- Sections: `[server]` (address), `[colors]` (theming)

## Application Entry Point

The compiled binary is named `curverses`.

## Environment Variables

- `EDITOR` - System editor launched for note editing
- `XDG_CONFIG_HOME` - Configuration directory (typically `~/.config`)
- `XDG_CACHE_HOME` - Cache directory for temporary note files


## Applicatio UI Architecture Overview
- Three-column layout: Notebooks → Notes → Preview
- Read-only browser + external editor integration via fork()
- Online-only, no local caching (except auth token)
- "Last save wins" conflict resolution

## Current Sprint
See TASKS.md for Sprint 0 (auth + token management)

## API Integration
Backend: FastAPI on https://your-server.com
Server address is loaded from the TUI configuration file
See API.md for endpoints documentation

## Design References
Figma: [https://www.figma.com/design/3JJrQIIDyAVjpl54SSC8wF/Verses-TUI?node-id=0-1&t=Csn9DupTndzwRO0h-1]
Inspired by: Yazi file manager
Theme: Nord palette

## Development Workflow
1. Read TASKS.md for current sprint
2. Implement features incrementally
3. Test manually (no automated tests for now)
4. Update BACKLOG.md when sprint is complete

## Notes for Claude Code
- This is a "vibe coding" project - balance creativity with pragmatism
- Sprint-based development, not waterfall
- User (Francesco) is CTO with strong opinions - ask when unsure
- XDG Base Directory compliance is non-negotiable
