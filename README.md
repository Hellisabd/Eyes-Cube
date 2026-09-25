*This project has been created as part of the 42 curriculum by bgrosjea, amirloup.*

# Eyes-Cube

![Eyes-Cube in game](assets/in_game.png)

## Description

**Eyes-Cube** is our take on **cub3D**, the 42 project inspired by *Wolfenstein 3D*, the first true first-person shooter (id Software, 1992). The goal is to build a raycasting engine in C: from a 2D map described in a `.cub` file, the program renders a first-person 3D view of a maze that the player can walk through in real time.

We turned the exercise into a small horror maze: the walls are made of blinking eyes, the view fades into fog, the player carries a swinging light, and a creature hunts them down while they look for the exit.

### Mandatory part

- Parsing of a `.cub` scene file: four wall textures (`NO`, `SO`, `WE`, `EA`), floor (`F`) and ceiling (`C`) colours in `R,G,B`, then the map.
- Map validation: only valid characters, exactly one player start (`N`, `S`, `E` or `W`), map closed by walls. Any misconfiguration exits cleanly with `Error` followed by an explicit message.
- Raycasting: for each screen column a ray is cast from the player (66° field of view) and stepped cell by cell through the grid until it hits a wall; the distance gives the height of the wall slice, corrected for the fish-eye effect.
- A different texture for each wall orientation (north, south, east, west).
- Controls: `W` `A` `S` `D` to move, `←` `→` to look around, `ESC` or the window's red cross to quit cleanly.

### Bonus part

| Subject bonus | Implementation |
|---|---|
| Wall collisions | The player and the enemy cannot walk through walls or closed doors. |
| Minimap | A 2D map of the level, with the player and the rays being cast. |
| Doors which open and close | `D` cells on the map, opened and closed with `E`, with a 24-frame animation. |
| Animated sprites | Blinking eye walls (several frames per texture) and an animated enemy. |
| Rotate the point of view with the mouse | Mouse look, with a key to release the cursor. |

Additional features:

- **Enemy** (`A` on the map): moves towards the player; if it reaches them, the game ends on a death screen.
- **Exit** (`X` on the map): reaching it ends the game on a success screen.
- **Sprint and stamina**: `Left Shift` makes the player run and drains a stamina bar that refills over time.
- **Fog and light**: a radial fog darkens the edges of the view, and a hand-held light bobs as the player walks (faster when sprinting).

The subject allows adding map symbols for the bonus part, so our `.cub` files may contain `D`, `A` and `X` in addition to `0`, `1` and the player start.

## Instructions

### Requirements

- Linux, `cc`, `make`
- `cmake` and GLFW (`libglfw3-dev` on Debian / Ubuntu), used to build [MLX42](https://github.com/codam-coding-college/MLX42)

### Build

```bash
git clone https://github.com/Hellisabd/Eyes-Cube.git
cd Eyes-Cube
make mlx_init    # builds MLX42 in MLX42/build
make             # builds libft, then cub3D
```

If the `MLX42` folder is missing or broken, `make mlx_re` downloads and rebuilds it.

Other rules: `make clean`, `make fclean`, `make re`.

### Run

Run the program from the root of the repository (texture paths in the `.cub` files are relative to it):

```bash
./cub3D maps/level_1.cub
```

Available maps:

| Map | Content |
|---|---|
| `maps/map.cub` | The example map from the subject, with plain coloured textures |
| `maps/test.cub` | Parsing test: elements separated by several spaces and empty lines |
| `maps/level_1.cub` | A small level with doors, an enemy and an exit |
| `maps/level_2.cub` | A larger maze with several doors |
| `maps/round.cub` | An open, rounded arena with an enemy and an exit |

### Controls

| Key | Action |
|---|---|
| `W` `A` `S` `D` | Move forward, left, backward, right |
| `←` `→` / mouse | Look left and right |
| `Left Shift` | Sprint (uses stamina) |
| `E` | Open or close the adjacent door |
| `B` | Release / capture the mouse cursor |
| `ESC` or red cross | Quit |

### `.cub` file format

```
NO assets/walls/red_eye.png
SO assets/walls/blue_eye.png
WE assets/walls/green_red_eye.png
EA assets/walls/green_eye.png

F 115,36,36
C 64,73,146

111111
1N0D01
1000X1
111111
```

- The six elements can come in any order and be separated by empty lines; the map always comes last.
- Map characters: `0` floor, `1` wall, `N` / `S` / `E` / `W` player start and orientation, spaces allowed outside the walls.
- Bonus characters: `D` door, `A` enemy, `X` exit.

## Project structure

```
.
├── main.c              # argument check, parsing, then game loop
├── cub3D.h             # structures and prototypes
├── parsing/            # reading and validating the .cub file
├── game/
│   ├── init_game/      # window, images and hooks
│   ├── display/        # raycasting, wall rendering, fog, line drawing
│   ├── player/         # movement, collisions, doors, stamina
│   ├── enemy/          # enemy sprite and movement
│   ├── exit/           # exit sprite and win condition
│   └── animation/      # animated walls, light, death screen
├── minimap/            # 2D minimap
├── free_and_destroy/   # memory and MLX cleanup
├── Libft/              # our libft
├── MLX42/              # graphics library
├── assets/             # textures and sprites
└── maps/               # .cub scenes
```

## Resources

- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html): the reference tutorial for grid-based raycasting.
- [Permadi — Ray-Casting Tutorial for Game Development](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/): the geometry behind the projection and the fish-eye correction.
- [MLX42 documentation](https://github.com/codam-coding-college/MLX42/tree/master/docs): windows, images, textures, key and cursor hooks.
- [Bresenham's line algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm): used to draw the rays on the minimap.
- [Wolfenstein 3D](http://users.atw.hu/wolf3d/): the original game, playable in a browser.

### Use of AI

The game code (parsing, raycasting, rendering, gameplay) was written by the two of us, without AI-generated code. An AI assistant (Claude) was used to write this README from the subject and the source code; we reviewed its content.
