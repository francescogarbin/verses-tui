# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Verses TUI is a Linux terminal user interface (TUI) application for the Verses note-taking platform. It's written in modern C++ and serves as a command-line front-end for managing self-hosted notes, emphasizing micro-data sovereignty.

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
