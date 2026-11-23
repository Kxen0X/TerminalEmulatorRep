# Terminal Emulator Prototype

A small Windows console project for learning command parsing, dispatch, and filesystem access in C++. The final version implements seven built-in commands for navigation, directory management, console clearing, and help.

## What is implemented

- A prompt and line-based input loop.
- Tokenization of commands and arguments with `std::wistringstream`.
- Command dispatch through a map of function pointers.
- File and directory listings, directory navigation, creation, and removal through `std::filesystem`.
- Case-insensitive command dispatch and separate source files for each command.
- UTF-16 input/output mode for the Windows console.
- An error message for unknown commands.

This is a command-interpreter prototype, not a terminal renderer or a complete replacement for `cmd.exe` or PowerShell. It does not start external programs, create a pseudoterminal, or interpret ANSI escape sequences.

## Build on Windows

Requirements: Visual Studio 2022 with the **Desktop development with C++** workload, the MSVC v143 toolset, and a Windows SDK. Use a recent C++ standard-library implementation with `std::format` and filesystem time formatting support.

```bat
git clone https://github.com/Kxen0X/TerminalEmulatorRep.git
cd TerminalEmulatorRep
```

Open `TerminalEmulator.sln`, select the C++ project, and use **C++23 / Latest** in its language-standard settings for your selected configuration.

The source calls `std::format` without explicitly including `<format>`. Add that include when building in an IDE if your compiler reports it as undeclared. The command-line alternative below forces the header without editing the source.

### Developer Command Prompt

From the repository root, in an x64 Native Tools Command Prompt for Visual Studio:

```bat
mkdir build-local
cl /nologo /EHsc /std:c++latest /FIformat /Fo:build-local\ /Fe:build-local\terminal.exe TerminalEmulator\main.cpp TerminalEmulator\dir.cpp TerminalEmulator\cd.cpp TerminalEmulator\mkdir.cpp TerminalEmulator\rmdir.cpp TerminalEmulator\cls.cpp TerminalEmulator\exit.cpp TerminalEmulator\help.cpp
build-local\terminal.exe
```

This project uses Windows-specific headers and `_setmode`; it is not currently a Linux/macOS application.

## Usage

The prompt tracks its own current-directory string, initially `\` (the current drive's root).

| Command | Action |
| --- | --- |
| `dir [path ...]` | List files and directories, with timestamps |
| `cd path` | Change the application's current directory |
| `mkdir name ...` | Create directories under the current directory |
| `rmdir path ...` | Remove empty directories |
| `cls` | Clear the console |
| `help` | Show the built-in command descriptions |
| `exit` | Exit the application |

For a read-only first look, run `help`, `dir`, and then `exit`. Test directory-changing commands in a disposable folder. Command names are normalized to lowercase.

## Source map

[TerminalEmulator/main.cpp](TerminalEmulator/main.cpp) handles input and dispatch. Each command has a matching `.cpp`/`.h` pair in [TerminalEmulator](TerminalEmulator), including `dir`, `cd`, `mkdir`, `rmdir`, `cls`, `exit`, and `help`.

[TerminalEmulator.vcxproj](TerminalEmulator/TerminalEmulator.vcxproj) contains the Visual Studio project settings.

## Current limitations

There is no general quoted-argument parser, command history, piping, or external-process execution. `cd` has custom handling for multiple tokens, but path behavior is not consistent across commands. Blank input is not checked before indexing the token list, and filesystem exceptions are not handled; either can terminate the program.

Natural next steps are robust input handling, explicit error reporting, quoted arguments, and additional built-in commands.
