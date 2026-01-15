# Verses TUI - Development Backlog

## Sprint 1: Read-Only Navigation
- Fetch notebooks from `/notebooks` endpoint
- Fetch notes from `/notebooks/{id}/notes` endpoint
- Implement three-column layout (Notebooks | Notes | Preview)
- Arrow key navigation (UP/DOWN, LEFT/RIGHT)
- Pills display (notebook count, note count, word/letter count)
- Sync pill display (Synced/Syncing/Offline)

## Sprint 2: Synchronization
- Manual sync on 'S' keypress
- Fetch all data from server
- Progress bar during sync (deterministic)
- Update sync pill status
- Error handling for offline/unreachable server

## Sprint 3: CRUD Operations
- Menu system (context-sensitive)
- New notebook dialog
- Delete notebook (with confirmation)
- Rename notebook
- Delete note (with confirmation)
- Move note to notebook (with list selection)
- Filter notes in current notebook

## Sprint 4: Editor Integration
- Launch $EDITOR on RETURN keypress
- fork() and wait for editor to close
- Download note to `/tmp/verses_<note_id>.md`
- Detect changes (hash comparison)
- Upload modified note to server
- Handle save errors

## Sprint 5: Polish & Refinements
- Help dialog with all keybindings
- About dialog with version info
- Improved error messages
- Loading indicators
- Keyboard shortcuts optimization
- Documentation

## Future Ideas (Icebox)
- Offline mode with local cache
- Conflict resolution UI
- Search across all notebooks
- Export notes to files
- Configurable keybindings
- Multiple account support
