# VRogue #

Simple rogue-like game.

![Screenshot](screenshot.png)
 

# Usage #

The source code is cross-platform, so, it can be used both on Windows and *nix systems. But for better performance (i.e. sounds) use it with Windows and Visual Studio. 

 If you are using VS, go to `Project` -> `Properties` -> `Configuration properties` -> `Linker` -> `Input` -> `Additional dependencies` and add `winmm.lib;` to it. This should make the sounds work.

# How to play #
### Who is who ###
| Sign | Character |
| ----- | ------ |
| **@** | player |
| **g** | goblin |
| **O** | ogre |
| **D** | dragon |
| **0-9** | door |

### Rules ###

* Move player with standard **w, s, a, d** buttons (you must switch to US/english language).
* Avoid or fight goblins and ogres. On the last level there will be a boss - dragon.


# Warning

This is currently a **_very-alpha_** version of this project, so, some features are in progress now, some bugs may appear and not all the maps are drawn.