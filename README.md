# Verses TUI

A Linux TUI front-end application for Verses.

<img width="1256" height="731" alt="image" src="https://github.com/user-attachments/assets/74ad1317-9b00-41a6-b203-b3cf0947189a" />

## Verses aims at micro-data-sovereignty

Verses is a note taking server-side application aiming at personal data sovereignty.

Note taking is an essential task of our digital lives, Verses lets you host and control your notes and personal memories on your own server.

Verses-TUI is the Linux-friendly, command-line oriented, zen-minded front-end for managing your notes.

Install the Verses server application on your own servers and download Verses-TUI to work on your notes from a mindful Linux terminal.  

## How is works

Verses TUI is a self-contained Linux terminal application written in modern C++.

## Configuring Verses TUI

You configure Verses TUI via dotfiles located accordingly to the XDG Base Directory, see https://specifications.freedesktop.org/basedir/latest/.

Configuration is stored in $XDG_CONFIG_HOME/verses-tui. $XDG_CONFIG_HOME generally maps to $HOME/.config.

The configuration file adopts the TOML format and is named verses-tui.toml.

## Configuring the server address or URL

Edit $XDG_CONFIG_HOME/verses-tui/config.toml in the server default value with your address or URL of choice. Relaunch the app to see the effects of your edits.

The server address is always in quotes and includes Verses API port, default is 8000.

#### TOML Sintax

```toml
[server]
address = "<examples: 1.2.3.4:8000, http://verses.notsecure.com:8000, https://www.verses.me:8000>"
```

#### Examples

1. Your Verses server is located at verses.mydomain.me, Verses API port was not changed and therefore sits at 8000.
```toml
[server]
address = "verses.mydomain.com:8000"
```

2. You're testing Verses and Verses-TUI on your local machine.
```toml
[server]
address = "localhost:8000"
```

## Launching the app and authenticating

Launch the app with the curverses command and authenticate with username and password created registering on the Verses web application. 

<img width="482" height="404" alt="image" src="https://github.com/user-attachments/assets/813344d3-f846-4d87-a8ba-2e05b9ace23e" />

Confirm by hitting the RETURN key. Quit the app by hitting the ESC key.

The server address is entered once, saved or updated in the configuration file and filled from configuration at subsequent launches.

## The application window

The interface is minimal. It consists of three panels and a bottom toolbar. 

From left to right:

Notebooks list panel. The "All Notes" notebook contains all your notes and cannot be edited or deleted. All other notebooks can be created, edited and deleted when empty of notes.

Notes list panel. A list of your notes in the currently selected notebook. The panel shows all your notes, regardless of the notebook they belong to, when the All Notes notebook is selected.

Note preview panel. A preview of the content of your currently selected note, text is always wrapped, no markdown formatting is applied. To edit the note, hit the RETURN key to launch the system editor configured in the $EDITOR environment variable.

Toobar. App name, version and shortcuts to common commands, available with CTRL+key.

## The menu system

<img width="1199" height="698" alt="image" src="https://github.com/user-attachments/assets/59e04809-98b3-4c9a-9344-ade5d4a036b7" />

The menu is contextual and its items reflect the operations available for the currently selected item.

<img width="819" height="347" alt="image" src="https://github.com/user-attachments/assets/6a658479-ace1-4b9b-a370-b3bf65bf2107" />

When a Notebook is selected, only Notebook-related actions are listed.

When a note is selected, actions can be performed on the selected note as well as on the notebook containing the note.   

## Operating the application with the keyboard

Hit ARROW LEFT/RIGHT to horizontally move the selector across panel.

Hit ARROW UP/DOWN to move the selector vertically in a list.

Command the application by hitting the underlined letters in the toolbar, no modifiers required.

Hit F1 to show help.

Hit Q to leave the application.

## Scrolling the Note Preview Panel with the keyboard

Long notes may not entirely visibile. When a note is selected and it exceeds the height of the Note Preview Panel, scroll the note with a combination of CTRL+UP/DOWN arrow keys:

CTRL + ARROW UP scrolls down the Note Preview Panel 

CTRL + ARROW DOWN scrolls up the Note Preview Panel    

## Using the mouse

The mouse is supported. Select a notebook or a note with a left-click of the mouse. Scroll the preview panel of a long note with the mouse wheel.

## Editing your notes

Verses TUI does not edit your notes directly. It delegates editing to your text or markdown editor of choice.

The app forks the system $EDITOR on your machine and resyncs the note on your Verses server when the editor returns control to Verses TUI.

Notes are temporarily downloaded for editing in directory $XDG_CACHE_HOME/verses-tui/.

Cached files are deleted following server forwarding of your changes to prevent storing your information indefinitely on your personal computer.

## Creating a new notebook

Navigate the left-most column and hit N to open the New Notebook dialog box. Input a title and hit RETURN to save the new notebook. Hit ESC to cancel the operation.  

## Editing the selected notebook

Navigate the left-most column and position the selection cursor on the notebook to edit. Hit the Edit key and enter the new title of the notebook. Hit RETURN to confirm, ESC to cancel.

## Delete a notebook

Only empty notebooks can be deleted: make sure you delete all the contained notes or move them to another notebook to allow notebook deletion.

Select a notebook and hit the corresponding key to delete the selected botebook. A dialog box appears requesting confirmation, hit RETURN to confirm, ESC to abort the operation.

## Creating a new note

Open the menu, select New note in the selected notebook. A new empty note appears at the top of the Notes list, the Note Preview panel invites you to fill with your editor.

## Synchronizing

Verses TUI does not store data locally. It only consumes data from the server and keeps it volatile in RAM, sync'ing with the server at launch and downloading all notes and the corresponding notebooks.

<img width="411" height="221" alt="image" src="https://github.com/user-attachments/assets/2bb4d6fe-a4c1-43ac-8735-ffef62f5661b" />

A dedicated keybinding allows further synchronizations while the app is running and the sync state is reflected by the "pill" located on the bottom-right corner of the app window.

## Backlog / TODO's

- color themes in configuration
- user registration via TUI
- ...and soooo much more!

## Building from Source

### Prerequisites

Ensure you have the following installed on your system:

- A C++17 compatible compiler (GCC 8+ or Clang 7+)
- CMake 3.14 or higher
- libcurl development headers
- Git

On Debian/Ubuntu:
```bash
sudo apt install build-essential cmake libcurl4-openssl-dev git
```

On Arch Linux:
```bash
sudo pacman -S base-devel cmake curl git
```

On Fedora:
```bash
sudo dnf install gcc-c++ cmake libcurl-devel git
```

### Building

Clone the repository and build:

```bash
git clone https://github.com/yourusername/verses-tui.git
cd verses-tui
mkdir build && cd build
cmake ..
make
```

The compiled binary `curverses` will be available in the `build` directory.

### Installing

To install system-wide:

```bash
sudo make install
```

This installs `curverses` to `/usr/local/bin` by default.
