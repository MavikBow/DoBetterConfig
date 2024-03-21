# DoBetterConfig

This is a supplementary program for the 2004 video game Cave Story, that allows a greater flexibility with control settings. 

## Table of contents
1. [What is this app?](#what-is-this-app)
2. [How to use the app?](#how-to-use-the-app)
3. [How it works?](#how-it-works)
4. [Compatibility](#compatibility)
5. [Pros and Cons](#pros-and-cons)
6. [How to compile the app?](#how-to-compile-the-app)
7. [License](#license)

## What is this app?

Have you been tired of trying the beat Cave Story with the annoying default settings it has? Does the default `DoConfig.exe` not provide the flexibility you want? Do other solutions online seem too complex to bother? Well, it's your lucky day! This app will hopefully solve your issues and make you forget about the days of confusing jumping and shooting using `Z` and `X`.

## How to use the app?

In order to use this app, you need to either download the `DoBetterConfig.exe` or compile it yourself. Then, simply put it in the same folder where you have `Doukutsu.exe` and you're good to go. Upon opening the app, you'll be greeted with a small window with a list of controls and keys responsible for them.

To change a certain key, find it on the list, press it and then press the key you want it replaced with. Certain keys are not supported, if you try to use it, the sound will play and the key will revert to its' previous self.

You also cannot have the same key be responsible for more than one action, so if you want to run left using `A`, you'll need to set the action on `A` to be something else first.

## How it works?

The app works by automating the binary patching method described in [this Cave Story forum post](https://forum.cavestory.org/threads/help-changing-controls.3017/)

## Compatibility

This program was written for the Windows Operating System.

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

### Pros:
 * **PORTABLE** : Just place this 100kb file in the same folder as Cave Story. (Right above `DoConfig.exe` where it belongs, lol).
 * **A ONE TIME DEED** : As this app patches the .exe of the game, you only need to do this once. The patched executable with have the same settings wherever you decide to play the game (I personally carry my game on a USB drive and play on different computers).
 * **NO ADMIN ACCESS** : One of the solutions I've found online was to install third party keyboard hookers like [`GRebind`](https://www.cavestory.org/download/miscellaneous-tools.php) or [`AutoHotKey`](https://www.autohotkey.com/). But installing them requires admin access, and I didn't have that on all computers I was using. `DoBetterConfig` has no need for admin access.
 * **EASY TO USE** : No need to worry about setting up scripts and stuff. It's a one window program, similar to the original `DoConfig.exe`. 
 * **NO ADDITIONAL INSTALLATIONS** : [`GRebind`](https://www.cavestory.org/download/miscellaneous-tools.php) in particular requires to have .NET installed. And there's a chance you don't have/want that.

### Cons:
 * **NOT ALL KEYS ARE SUPPORTED** : Because of the nature of the executable file, there's no way (at least, in my understanding) for all keys to be supported. For example, such popular keys as `LMB`, `RMB`, `Enter` and `Backspace` cannot be applied, so you'll have to do with other keys. On the up side, if a key is not supported, the app will simply refuse to apply it, so you don't need to worry about realizing this while already in the game.
 * **NOT FULLY TESTED** : You can trust the compatibility table I wrote further up in this document. But that means not all Windows versions have beed tested yet. I'll be trying to solve this, but that means that if you have an old Windows XP computer and the app doesn't work yet, I'm sorry.
 * **FOR WINDOWS ONLY** : Pretty self explanatory. The app relies on the windows.h library and the structure of the executable file compiled for the Windows Operating System.

## How to compile the app?

### Reaquirements
 - `GNU Make`
 - `gcc`
 - `comctl32.dll`
 - `gdi32.dll`
### Compilation
In order to compile:
 - Clone the repository
 - In DoBetterConfig directory run
```
make
```
After compiling you should find `DoBetterConfig.exe` in the `build\` directory.
 - Clean the mid-compilation files by running
```
make clean
```

## License

This project contains parts of the Microsoft Windows SDK.
They're licensed under Microsofts EULA. To use it you must read and agree to it.

The rest is licensed under the "Unlicense" license.
