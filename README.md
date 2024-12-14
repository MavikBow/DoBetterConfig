# DoBetterConfig

![screenshot\_v111.png](/screenshot_v111.png)

This is a supplementary program for the 2004 video game Cave Story, that allows greater flexibility with control settings.

### Total downloads: 478

## Table of contents

- [DoBetterConfig](#dobetterconfig)
  - [Table of contents](#table-of-contents)
  - [What is this app?](#what-is-this-app)
  - [How to use the app?](#how-to-use-the-app)
  - [How does it work?](#how-does-it-work)
  - [Compatibility](#compatibility)
  - [Pros and Cons](#pros-and-cons)
    - [Pros](#pros)
    - [Cons](#cons)
  - [How to compile the app?](#how-to-compile-the-app)
    - [Requirements](#requirements)
    - [Compilation](#compilation)
  - [License](#license)

## What is this app?

Have you been tired of trying to beat Cave Story with the annoying default settings it has? Does the default `DoConfig.exe` not provide the flexibility you want? Do other solutions online seem too complex to bother? Well, it's your lucky day! This app will hopefully solve your issues and make you forget about the days of confusing jumping and shooting using `Z` and `X`.

## How to use the app?

To use this app, first either download the `DoBetterConfig.exe` or compile it yourself. Then, put it in the same folder where you have your `Doukutsu.exe`. Upon opening the app, you'll be greeted with a small window with a list of controls and keys responsible for them.

To change a certain key, find it on the list, press it (use mouse keys, `ENTER` or `SPACE` for that) and then press the key you want it replaced with. Certain keys are not supported. If you try to use them, the sound will play and the key will revert to its previous self.

You also cannot have the same key be responsible for more than one action, so if you want to run left using `A`, you'll need to set the action on `A` to be something else first (or disable that action first).

You can disable keys with `BACKSPACE`.

## How does it work?

The app works by automating the binary patching method described in [this Cave Story forum post](https://forum.cavestory.org/threads/help-changing-controls.3017/)

## Compatibility

This program was written for the Windows operating system.

| OS version | Works (.exe) | Compiles |
| ---------- | :----------: | :------: |
| Windows 11 | Yes | [Not tested] |
| Windows 10 | Yes | Yes |
| Windows 8  | [Not tested] | [Not tested] |
| Windows 7  | Yes | Yes |
| Windows Vista | [Not tested] | [Not tested] |
| Windows XP | [Not tested] | [Not tested] |
| Windows 2000 | [Not tested] | [Not tested] |

## Pros and Cons

### Pros

- **PORTABLE** : Just place this 63kb file in the same folder as Cave Story (right above `DoConfig.exe` where it belongs, lol).
- **A ONE TIME DEED** : As this app patches the .exe of the game, you only need to do this once. The patched executable will have the same settings wherever you decide to play the game (I, personally, carry my game on a USB drive and play on different computers).
- **NO ADMIN ACCESS** : One of the solutions I've found online was to install third-party keyboard hookers like [`GRebind`](https://www.cavestory.org/download/miscellaneous-tools.php) or [`AutoHotKey`](https://www.autohotkey.com/). But installing them requires admin access, and I didn't have that on all the computers I was using. `DoBetterConfig` has no need for admin access.
- **EASY TO USE** : No need to worry about setting up scripts and stuff. It's a one-window program, similar to the original `DoConfig.exe`.
- **NO ADDITIONAL INSTALLATIONS** : [`GRebind`](https://www.cavestory.org/download/miscellaneous-tools.php) in particular, requires having .NET installed. And there's a chance that you don't have it and don't want to install it.

### Cons

- **NOT ALL KEYS ARE SUPPORTED** : Because of the nature of the executable file, there's no way (at least, in my understanding) for all keys to be supported. For example, such popular keys as `LMB`, `RMB`, `Enter` and `Backspace` cannot be applied, so you'll have to stick with other keys. On the other hand, if a key is not supported, the app will simply refuse to apply it, so you don't need to worry about realizing this while already in the game.
- **NOT FULLY TESTED** : You can trust the compatibility table I wrote further up in this document. But that means that not all Windows versions have been tested yet. I'll be trying to solve this, but that means that if you have an old Windows XP computer, and the app doesn't work yet, I'm sorry.
- **FOR WINDOWS ONLY** : Pretty self-explanatory. The app relies on the windows.h library and the structure of the executable file, which is created during compilation, is intended for the Windows operating system only.

## How to compile the app?

### Requirements

- `GNU Make`
- `gcc`
- `comctl32.dll`
- `gdi32.dll`

### Compilation

In order to compile:

1. Clone the repository

    ```sh
    git clone https://github.com/MavikBow/DoBetterConfig.git
    ```

2. In the DoBetterConfig directory run

    ```sh
    make launch
    ```

    After compiling, you should find `DoBetterConfig.exe` in the `build` directory

3. Clean the mid-compilation files by running

    ```sh
    make clean
    ```

## License

This project contains parts of the Microsoft Windows SDK.
They're licensed under Microsoft's EULA. To use it, you must read and agree to it.

The rest is licensed under the "Unlicense" license.
