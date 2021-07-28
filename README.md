# LightsOn

Welcome to my COMP313 Mini Game "Lights On!"

Course Code: COMP313

Name: Maxwell Grigson

Assignment Number: 1

Game Title: Lights On!

Video Links:

Video 1 showing off the Game: https://youtu.be/iTre0UrIPLs
Video 2 showing off the Blueprints / C++ code: https://youtu.be/s3PAVMTmlUU


Game Description:

The main action of my game is to solve puzzles using very simple mechanics. These mechanics are explained in a tutorial and there are both basic and more advanced levels to attempt.


Challenges

In general I had many challenges while working with Unreal having never used it or any other Game Engine before. Meanwhile I had very limited experience with C++.
Some of the major challenges included:

Setting up connections between C++ and the Blueprints. 
This was important as while I could handle the puzzle logic within C++, the flow of the game and the process of loading menus / levels 
all had to be done with Blueprints. This communication was largely done by making the majority of the C++ functions BlueprintCallable.
This allowed the functions to be called from within blueprints which was especially vital for creating levels and knowing when they were completed.

Setting up connections between Widgets and the Blueprints.
A rather interesting stumbling block I had to overcome was the communication between the Tutorial level and the Tutorial screen widget. The widget presented the text and buttons
for the user in a UI style but the tutorial level itself controlled the grids and monitored the players interaction with them. Ultimately this led me to learning about and implementing 
Event Dispatchers which helped the level and widget communicate through a series of calls to and fro.

Working out the math for larger grids.
Not much Unreal / C++ involved but working out the math for correctly placing the blocks (and resizing them) for any size of grid was a fun maths challenge that I was happy to solve.


Most interesting part of the game

For me the tutorial is likely the most interesting part of the game because of how complex it was to put together. Meanwhile for players the most interesting part of the game is 
the puzzles themselves. The basic puzzles can actually be harder than the 'Advanced' ones because there are more lights to turn on and more steps neccessary to solve the puzzles.