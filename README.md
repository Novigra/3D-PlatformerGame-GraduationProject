
# A 3D Platformer Game Graduation Project

# Content

- [Important Note](#Important-Note)
- [Introduction](#Introduction)
- [Game Design](#Game-Design)
  - [Game Story](#Game-Story)
  - [Gameplay Loop](#Gameplay-Loop)
  - [Character Movement &. Camera Placement](#CharMoveAndCamPlace)
  - Level Design
  - Objectives
    - Section One
    - Section Two
    - Section Three
    - Section Four
    - Section Five
  - Items
  - User Interface
    - Character Interaction &. Dialogue
    - Free Roam
    - Indication
    - Menu
    - Fishing
    - Cooking
    - Arranging Maps
  - Saving &. Loading
- Technical Implementation
  - Player Input
  - Character Interaction &. Dialogue
  - User Interface
    - Pause Menu
  - Game Mechanics
    - Section One
    - Section Two
    - Section Three
    - Section Four
    - Section Five
  - Saving &. Loading
- Conclusion
---

# Important Note

If you want to see visual representations for each implementation before reading the documentation, like character interactions and dialogue, objective mechanics like catching a fish, cooking, and much more, [A Dropbox link is available.](https://www.dropbox.com/scl/fo/pfwxpptmny7z9q3yzszba/AMsKb4H2txQgSXODNPbkuyU?rlkey=rzvb1vh2fcwj47t54txzl67ks&st=umbg66l8&dl=0)

# Introduction

This project is a graduation project that I and my team worked on. It is a 3D platformer game in which you play as a character who is looking for their child. We developed the game to be an introduction for people who want to enter the gaming world but are having a hard time doing so as, in our current day and age, games are more complex in terms of game systems and more difficult. Therefore, we wanted to develop a game that anyone can play and finish. especially children, who are our main target demographic, but other demographics can have fun.

The game is a 3D platformer game because 3D platformers mostly focus on movement and passing obstacles, and as someone who is still new to this medium, it is the ideal game type to help players get good at moving characters and get them more comfortable with the controls.
<br></br>

<a name="Game-Design"></a>
![GameDesign](https://github.com/user-attachments/assets/88c74aa6-465f-43a5-90a4-8e87f65b2f78)

The game was inspired by fromsoftware games world design where you start in an area and start exploring it, and when you want to go to the next area, you must finish the main objective, defeat a boss in Dark Souls, for example.

Also, it is inspired by different 3D platformer games, famously the Mario franchise, in which you collect coins, jump around, run through the fields, and have mechanics like wall running.
But before we delve into level design, character movement, gameplay loop and more. Let’s talk about the story of the game.
<br></br>

<a name="Game-Story"></a>
![GameStory](https://github.com/user-attachments/assets/c16f026a-c61e-4e78-b27a-52fd8aebd3b7)

The game story follows a character called Munda. She’s a mother who lost her child and is looking for.

Throughout the game, she will meet different characters who are in trouble and need help. Munda will help them, and in return, they will help her find her child.
<br></br>

<a name="Gameplay-Loop"></a>
![GameplayLoop](https://github.com/user-attachments/assets/99ad8377-f408-4c88-b683-e06a49834799)

The game follows a basic game loop.
![1-GameLoop](https://github.com/user-attachments/assets/658dfea3-6345-4ee1-b7f6-fbc3af378ae9)

Important note: each area isn’t a level; instead, the areas are on one level, but each of them is separated by a gate.

When you start exploring the area, you can collect coins and talk to a Non-Player Character (NPC) to give you the main objective to finish. After finishing talking to them, the NPC gives a map to help the player navigate the area.

The game has difficulty, but to spice it up, the game has a timer that starts after talking to the NPC, and if it runs out, the player loses, and they need to start from the latest saved checkpoint.

So the sequence of interaction between the player and the NPC goes like this:

1. The player interacts with the NPC.

2. Dialogue stars.

3. Dialogue ends.

4. The NPC gives a map to the player.

5. Timer starts.

If the player finishes the main objective, the timer stops, and the player must talk to the NPC to continue the dialogue, then the NPC gives a key to the player, and finally the player can pass the gate.
<br></br>

<a name="CharMoveAndCamPlace"></a>
![CharMoveAndCamPlace](https://github.com/user-attachments/assets/1efd7a0a-9fb8-43b2-9d97-9f013c75e22b)
