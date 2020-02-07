# LittlevGL Sandbox - PC Simulator using Visual Studio 2017/2019

This is a pre-configured Visual Studio project to try LittlevGL on a Windows PC. The project uses the [SDL](https://www.libsdl.org/) library which is copied and linked to the project, so you can compile it without any extra dependencies. The 64 bit libraries are used so it will work out-of-the-box on 64-bit systems.

Instructions for cloning, building and running the application are found below.

## How to Clone

This repos contains other, necessary LittleVGL software repositories as [git sub-modules](https://git-scm.com/book/en/v2/Git-Tools-Submodules).  Those sub-modules are not pulled in with the basic git clone command and they will be needed.  There are a couple of ways to pull in those submodules.

### Get the repo and submodules

This command will clone this top level repo and all submodules in a single step.

```
git clone --recurse-submodules https://github.com/DeonMarais64/lvgl_sandbox_sim_vs.git
cd lvgl_sandbox_sim_vs\visual_studio_2017_sdl
xcopy lv_examples lv_examples-rework /e/s/h
cd lv_examples-rework
git switch rework
```

## How To Build & Run

Open the `lvgl_sandbox_sim_vs` solution file in Visual Studio. Click on the _Local windows Debugger_ button in the top toolbar.  The included project will be built and run, launching from a cmd window.

## Also see,
This repo is a variation of https://github.com/littlevgl/lv_sim_visual_studio_sdl

