# TASKS.md

# Sprint 0: Authentication & Token Management

## Goal
User authenticates to Verses backend and obtains session token.
Token is cached for subsequent app launches.

## Tasks

### 1. Project Setup
- [x] Initialize CMake project
- [x] Add FTXUI as dependency (FetchContent or submodule)
- [x] Add libcurl dependency
- [x] Add nlohmann/json dependency
- [x] Create basic directory structure (src/, include/, etc.)

### 2. XDG Directory Support
- [x] Implement XDG Base Directory detection
  - `$XDG_CONFIG_HOME/verses-tui/` (default: `~/.config/verses-tui/`)
  - `$XDG_CACHE_HOME/verses-tui/` (default: `~/.cache/verses-tui/`)
- [x] Create directories if they don't exist
- [x] Config file: `config.toml` with server address

### 3. Login UI (LoginWindow)
- [x] Implement LoginWindow component with FTXUI
- [x] Three input fields: Server address, Username, Password
- [x] Password masking with asterisks
- [x] TAB navigation between fields
- [x] "Login with RETURN" action
- [x] Nord theme colors

### 4. HTTP Authentication
- [x] Implement HTTP POST to `/auth/login` endpoint
- [x] Send JSON: `{"username": "...", "password": "..."}`
- [x] Parse response: `{"access_token": "...", "token_type": "bearer"}`
- [x] Handle errors (invalid credentials, server unreachable)

### 5. Token Caching
- [x] Save token to `$XDG_CACHE_HOME/verses-tui/token`
- [x] Load token on startup
- [x] Validate token (optional: check expiry if backend provides it)

### 6. Error Dialog
- [x] Implement MessageDialogBox overlay
- [x] Show error message on auth failure
- [x] ESC/RETURN to close dialog

### 7. Config Persistence
- [x] Save server address to `config.toml`
- [x] Load server address on subsequent launches
- [x] Allow editing server address in login form

## Definition of Done
- User can enter credentials and authenticate
- Token is saved and reused on next launch
- Server address is persisted
- Errors are displayed clearly
- Code compiles and runs on Linux

## Technical Notes
- Use RAII for resource management
- Smart pointers if needed or no pointers at all, no raw `new`/`delete`
- Follow Scott Meyers' STL idioms
- Keep it simple: no premature optimization

