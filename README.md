# Terminal Emulator Prototype

A small Windows console project for learning command parsing, dispatch, and filesystem access in C++. The current implementation recognizes one built-in command, `dir`, and lists subdirectories of the requested path.

## What is implemented

- A prompt and line-based input loop.
- Tokenization of commands and arguments with `std::wistringstream`.
- Command dispatch through a map of function pointers.
- Directory traversal with `std::filesystem`.
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
cl /nologo /EHsc /std:c++latest /FIformat /Fo:build-local\terminal.obj /Fe:build-local\terminal.exe TerminalEmulator\main.cpp
build-local\terminal.exe
```

This project uses Windows-specific headers and `_setmode`; it is not currently a Linux/macOS application.

## Usage

At the application's prompt:

```text
dir
dir C:\Windows
dir C:\Windows C:\Users
```

- `dir` lists subdirectories under the current drive's root (`\`).
- One or more arguments select directories to inspect.
- Output contains subdirectory names and last-write timestamps. Regular files are currently omitted.
- Unknown commands produce an error message.

Close the console window to exit. A built-in `exit` command is not implemented.

## Source map

The implementation is in [TerminalEmulator/main.cpp](TerminalEmulator/main.cpp):

- `commands` maps command names to handlers.
- `dir()` enumerates directories.
- `main()` reads, splits, and dispatches input.

[TerminalEmulator.vcxproj](TerminalEmulator/TerminalEmulator.vcxproj) contains the Visual Studio project settings.

## Current limitations

Only lowercase `dir` is recognized. There is no `cd`, quoted-path parsing, command history, piping, or process execution. Paths containing spaces are split into separate arguments. Blank input is not checked before indexing the token list, and filesystem exceptions are not handled; either can terminate the program.

Natural next steps are robust input handling, explicit error reporting, quoted arguments, and additional built-in commands.
