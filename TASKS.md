# TASKS.md

# Sprint 0: Authentication & Token Management

## Goal
User authenticates to Verses backend and obtains session token.
Token is cached for subsequent app launches.

## Tasks

### 1. Project Setup
- [ ] Initialize CMake project
- [ ] Add FTXUI as dependency (FetchContent or submodule)
- [ ] Add libcurl dependency
- [ ] Add nlohmann/json dependency
- [ ] Create basic directory structure (src/, include/, etc.)

### 2. XDG Directory Support
- [ ] Implement XDG Base Directory detection
  - `$XDG_CONFIG_HOME/verses-tui/` (default: `~/.config/verses-tui/`)
  - `$XDG_CACHE_HOME/verses-tui/` (default: `~/.cache/verses-tui/`)
- [ ] Create directories if they don't exist
- [ ] Config file: `config.toml` with server address

### 3. Login UI (LoginWindow)
- [ ] Implement LoginWindow component with FTXUI
- [ ] Three input fields: Server address, Username, Password
- [ ] Password masking with asterisks
- [ ] TAB navigation between fields
- [ ] "Login with RETURN" action
- [ ] Nord theme colors

### 4. HTTP Authentication
- [ ] Implement HTTP POST to `/auth/login` endpoint
- [ ] Send JSON: `{"username": "...", "password": "..."}`
- [ ] Parse response: `{"access_token": "...", "token_type": "bearer"}`
- [ ] Handle errors (invalid credentials, server unreachable)

### 5. Token Caching
- [ ] Save token to `$XDG_CACHE_HOME/verses-tui/token`
- [ ] Load token on startup
- [ ] Validate token (optional: check expiry if backend provides it)

### 6. Error Dialog
- [ ] Implement MessageDialogBox overlay
- [ ] Show error message on auth failure
- [ ] ESC/RETURN to close dialog

### 7. Config Persistence
- [ ] Save server address to `config.toml`
- [ ] Load server address on subsequent launches
- [ ] Allow editing server address in login form

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
