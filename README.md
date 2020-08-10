# Gyronaut
An open source SDL2 OpenGL game for PC and Android in which you help an astronaut to reach his space station.

## WARNING:
This game is in active development and is not playable yet!

## Abstract
Gyronaut will be a simple 2D game.
An astronaut wants to reach his space station and uses his "space jetpack" to get there.
He will constantly float forward (right) and the player can rotate his direction up and down to avoid obstacles like meteorites.

## Todo
- Draw basic sprites
  - Gyronaut
  - Asteroids
  - Background
- PseudoRandom
- Meteorites
  - generation with prand
  - collision detection
- Space Station
  - Arrow to it
- Basic Game
  - Menu
  - Settings
  - Level system
- Background
  - stars and planets, etc.
  - batch rendered
  - 2nd Layer of bg meteorites
- Particles of Gyronaut
- Render to Framebuffer
  - FishEye effect
  - HUD outside of fisheye sphere
 
## compiling with emscripten:
within a build folder, call:
```shell script
emcc ../src/astronaut.c ../src/background.c ../src/camera.c ../src/game.c ../src/input.c ../src/main.c ../src/meteorite.c ../src/r/*  -I../include/ -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s FULL_ES3=1 -s SDL2_IMAGE_FORMATS='["png"]' --preload-file ../res -s ALLOW_MEMORY_GROWTH=1 -o gyronaut.html
```

