# Tribe 2.0

## Summary

I wasn't satisfied with the last version. Due to bad design choices in some places there were some issues. I wasn't satisfied with SDL2 either, so I used glfw here instead. This was also not just a remake of Tribe 1.0, it was also a challange for me. I wanted 2.0 to support opengl3 and vulkan both, whilst making it possible to "hot"-reload. 

## Why a revision?
After finishing Tribe 1.0 for my school project, I came to the conclusion there were some problems and mistakes. I had many ideas in my mind on how to fix these problems and mistakes, but that would've taken a whole overhaul of the engine. So instead of altering all the existing code, I chose to revision the engine. I wanted to take the opportunity to challange myself and research more on certain aspects. Eventually I chose to move from SDL2 to GLFW, but not only that, I wanted to make it "hot"-reloadable between opengl and vulkan. 

In comparison to Tribe 1.0, Tribe 2.0 will have cross platform due to development with Cmake. This was yet another challange, since I've never used Cmake before.

This project was mainly aimed to test my programming skills, but also to broaden my knowledge about more libraries.

### From `Windows + vs22 + vcpkg` To `linux + vscode`
It was fully developed on a windows machine with VS22, with the use of an experimental package manager called vcpkg. This choice was made due to vcpkg being appealing in theory and it was nice to use. Yet it came with it's drawbacks too. Some packages still were a nightmare to make them work and even some packages aren't supported a.k.a not downloadable through vcpkg. It was also annoying for different users, since they had to install vcpkg completely, just to make anything work. After all this was still an experiment to see how usefull vcpkg could be.

In the meantime I made the complete switch to linux. I also switch to developing in vscode with cmake. This would make it possible to even cross compile Tribe 2.0, where as Tribe 1.0 was Windows specific.

### From `SDL2` To `GLFW`
In Tribe 1.0, SDL2 was used in combination with opengl. There were no issues with this setup, but personnaly it felt way to out-dated. Since SDL2 is written in C, all the SDL function calls had c-style code around it. 

So while researching the revision of Tribe, I stumbled upon GLFW. GLFW seemed like a powerfull, modern c++ library. It definitly got my attention and eventually I decided to replace SDL2 with GLFW.

### General programming knowledge
In Tribe 1.0 I avoided smart pointers in certain parts of the code. Since then, I have researched more on modern C++. In Tribe 2.0 the aim is to use smart pointers as much as possible. There will also be a preference to std::string_view rather than std::string. 

### Extra features
I also laid out a challange for me in Tribe 2.0. I aimed to try and make the engine "hot"-reloadable between multiple renderers. For the moment Tribe 2.0 will only support opengl3 and vulkan, but there might be more to come.

There are plans on adding an editor aswell.
