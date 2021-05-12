# LittlevGL Sandbox - PC Simulator using Visual Studio 2017/2019

This is a pre-configured Visual Studio project to try LGL on a Windows PC. The project uses the [SDL](https://www.libsdl.org/) library which is copied and linked to the project, so you can compile it without any extra dependencies. The 64 bit libraries are used so it will work out-of-the-box on 64-bit systems.

Instructions for cloning, building and running the application are found below.

## How to Clone

This repos contains other, necessary LVGL software repositories as [git sub-modules](https://git-scm.com/book/en/v2/Git-Tools-Submodules).  Those sub-modules are not pulled in with the basic git clone command and they will be needed. Please follow the sequence below.

### Get the repo and submodules

These commands will clone this top level repo and all submodules and prepare them,

### One at a time the long way
```
git clone https://github.com/DeonMarais64/lvgl_sandbox_sim_vs.git
cd lvgl_sandbox_sim_vs\visual_studio_2017_sdl
git clone https://github.com/lvgl/lvgl.git
git clone https://github.com/lvgl/lv_drivers.git
git clone https://github.com/lvgl/lv_examples.git
cd lvgl
git switch release/v7
cd ..\lv_drivers
git switch release/v7
cd ..\lv_examples
git switch release/v7
cd ..\..

```

## How To Build & Run

Open the `lvgl_sandbox_sim_vs.sln` file in Visual Studio.
Press F5 to build and run the project.

Open main.c and try the different pages and applications by commenting / uncommenting as appropriate.

Any feedback welcome.

## Also see,
This repo is a variation of https://github.com/littlevgl/lv_sim_visual_studio_sdl

