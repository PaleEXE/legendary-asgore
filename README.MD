# Asgore's Bizarre Adventure

## build for windows:
```bash
gcc main.c -o main -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
```

## build for macOS:
```bash
gcc main.c -o main -Iinclude -Llib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
```