# Asteroids

Asteroids test task for ZeptoLab.

The game was created and compiled in Visual Studio 2015.

Tested on:
- nVidia Shield Tablet.
- Nexus 4.
- x86 Emulator.
- ARM Emulator.

The code is written in C++11. While I was creating the game I created several mini
libraries to help in the development of the game which later on I open sourced, you
can find them all in my github account (http://github.com/arajar).

The game features:
- Full shader based OpenGL ES 2 renderer.
- Read files from within the APK package (http://github.com/arajar/android_file_utils)
- Vector Math library (http://github.com/arajar/math).
- Header-only Entity Component System micro framework (http://github.com/arajar/ecs).
- Custom BMP loader.
- Particle Systems.
- Game States.
- Procedural Asteroid generator: all the asteroids are generated with different shapes.
- Two virtual joystics, one for movement and another one for shooting. Twin stick action!


I used the entity-component-system extensively to control all the aspects of the game:
- Spawn System: Checks that there are enough asteroids on the world and spawns new ones.
- Collision System: Super fast collision detection using spheres, checks if the entities are colliding with
each other.
- Movement System: Takes the current position, direction and speed and moves the entities. Also checks the 
limits of the screen and moves the entities accordingly.
- Shoot System: Checks if the minimum time between shoots has passed and then creates missiles that 
point in the current direction of the player's ship.
- Render System: Creates the needed transformation matrixes for every entity and renders them.
- Debug Render System: Used to help debug the collision and shoot system, renders debug spheres around the
entities.

The code is organized in two main folders:
- framework: where the "engine" is located. There is no gameplay code here.
  - ecs: the header-only entity component system micro framework.  
  - graphics: utility classes to load textures and shaders.
  - input: virtual joysticks.
  - math: my vector math library.
  - particles: the particle systems.
  - states: game state manager.
  - util: some utility classes (singletons, circual arrays, tweeners and file handling).
- game: where all the game code is located.
  - entities: all the needed components and systems for the game.
  - states: menu and gameplay states.
  - util: utilities to create 2d shapes (asteroids, ship, missiles and circles).

I enjoyed a lot the creation of this game, and if it's ok with you I would love to open source it on 
Github and maybe continue working on the game.
  
While creating the game I identified some optimizations for future updates:
- Batching all the particles, asteroids and missiles.
- Binding the shaders only per type of entity.

And also new features, like postfx or more types of particle systems.

Luis.
