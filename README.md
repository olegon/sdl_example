# SDL Example

I was listening to a podcast and I was challenged to paint an animation on screen using C++. SDL library was my first choose, because it doesn't have huge abstractions and I've used it in the past. I can't draw anything, so I got some free sprites on [Game Art 2D](https://www.gameart2d.com/freebies.html).

## Running it

```bash
make && ./sdl-example.out
```

## Interacting with it

| Key | Animation |
|:-:|:-:|
| nothing... | Idle |
| `D` or `ARROW RIGHT` | Walking |
| `Shift + D` or `Shift + ARROW RIGHT` | Running |
| `W` or `SPACEBAR` or `ARROW UP`  | Jumping |
| `S` or `ARROW DOWN` | Dying |

## Libraries used

- SDL
- SDL_image

## Reference

- [amazing lazyfoo website](https://lazyfoo.net/)
- [SDL wiki](https://wiki.libsdl.org/)
