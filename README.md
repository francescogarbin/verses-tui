# Verses TUI

A Linux TUI front-end application for Verses.

<img width="1242" height="719" alt="image" src="https://github.com/user-attachments/assets/a432ba60-f26f-4fe0-8e54-a73c55f9c20d" />

## Verses aims at micro-data-sovereignty

Verses is a note taking server-side application providing aiming at personal data sovereignty.

Note taking is an essential task of our digital lives, Verses lets you host and control your notes and personal memories on your own server.

Verses-TUI is the Linux-friendly, command-line oriented, zen-minded front-end for managing your notes.

Install the Verses server application on your own servers and download Verses-TUI to work on your notes from a mindful Linux terminal.  

## How is works

Verses TUI is a self-contained Linux terminal application written in modern C++.

## Configuring Verses TUI

You configure Verses TUI via dotfiles located accordingly to the XDG Base Directory Specification (https://specifications.freedesktop.org/basedir/latest/).

Configuration is stored in $XDG_CONFIG_HOME/verses-tui. $XDG_CONFIG_HOME generally maps to $HOME/.config.

The configuration file adopts the TOML format and is named verses-tui.toml.

## Configuring the server address or URL

Edit $XDG_CONFIG_HOME/verses-tui/config.toml in the server default value with your address or URL of choice. Relaunch the app to see the effects of your edits. The server address is always in quotes.  

[server]

address = "<ip address v4 or url, examples: 1.2.3.4, http://verses.notsecure.com, https://www.mypersonalnotes.com>"

## Customizing colors

Edit $XDG_CONFIG_HOME/verses-tui/config.toml in the Colors section and replace the default HTML colors with colors of your choice. Relaunch the app to see the effects of your edits.

[colors]

color_plain = "#5E81AC"

color_strong = "#BBBBBB"

color_warning = "#BC4C4D"

color_titles = "#BBBBBB"

## Launching the app and authenticating

Launch the app with the curverses command and authenticate with username and password.

<img width="491" height="322" alt="image" src="https://github.com/user-attachments/assets/c404b9ac-f527-489e-899b-ee41f86f9b19" />

Confirm by hitting the RETURN key. Quit the app by hitting the ESC key.

## The application window

<img width="1100" height="706" alt="verses-tui-panels" src="https://github.com/user-attachments/assets/295994d5-e667-4e56-a0e8-3ad48ccb403d" />

The interface is minimal. It consists of three panels and a bottom toolbar. 

From left to right:

Notebooks list panel. The "All Notes" notebook contains all your notes and cannot be edited or deleted. All other notebooks can be created, edited and deleted when empty of notes.

Notes list panel. A list of your notes in the currently selected notebook. The panel shows all your notes, regardless of the notebook they belong to, when the All Notes notebook is selected.

Note preview panel. A preview of the content of your currently selected note, text is always wrapped, no markdown formatting is applied. To edit the note, hit the RETURN key to launch the system editor configured in the $EDITOR environment variable.

Toobar. A context-sensitive toolbar displaying the commands available for the currently selected item. The toolbar commands reflect the right-most selected item: when a notebook is the right-most selected item, the toolbar displays and process commands that affect notebooks such as new, edit, delete. When a note is the right-most selected item, the toolbar displays and process commands that affect notes such as:

- create new note

- move the selected note to another notebook

- delete the selected note

- find text in notes

The toolbar displays two commands that are always available:
- sync with the server
- show the help dialog 

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

Select a noteb

