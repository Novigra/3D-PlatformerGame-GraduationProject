
# A 3D Platformer Game Graduation Project

# Content

- [Important Note](#Important-Note)
- [Introduction](#Introduction)
- [Game Design](#Game-Design)
  - [Game Story](#Game-Story)
  - [Gameplay Loop](#Gameplay-Loop)
  - [Character Movement &. Camera Placement](#CharMoveAndCamPlace)
  - [Level Design](#LevelDesign)
  - [Objectives](#Objectives)
    - [Section One](#Section-One)
    - [Section Two](#Section-Two)
    - [Section Three](#Section-Three)
    - [Section Four](#Section-Four)
    - [Section Five](#Section-Five)
  - [Items](#Items)
  - [User Interface](#UI)
    - [Character Interaction &. Dialogue](#Character-Interaction-&.-Dialogue)
    - [Free Roam](#Free-Roam)
    - [Indication](#Indication)
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

---

<a name="Game-Design"></a>
![GameDesign](https://github.com/user-attachments/assets/88c74aa6-465f-43a5-90a4-8e87f65b2f78)

The game was inspired by fromsoftware games world design where you start in an area and start exploring it, and when you want to go to the next area, you must finish the main objective, defeat a boss in Dark Souls, for example.

Also, it is inspired by different 3D platformer games, famously the Mario franchise, in which you collect coins, jump around, run through the fields, and have mechanics like wall running.
But before we delve into level design, character movement, gameplay loop and more. Let’s talk about the story of the game.

---

<a name="Game-Story"></a>
![GameStory](https://github.com/user-attachments/assets/c16f026a-c61e-4e78-b27a-52fd8aebd3b7)

The game story follows a character called Munda. She’s a mother who lost her child and is looking for.

Throughout the game, she will meet different characters who are in trouble and need help. Munda will help them, and in return, they will help her find her child.

---

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

---

<a name="CharMoveAndCamPlace"></a>
![CharMoveAndCamPlace](https://github.com/user-attachments/assets/1efd7a0a-9fb8-43b2-9d97-9f013c75e22b)

As the game is a 3D platformer game. It is very important to make the character easy and enjoyable to control.

The player can:

1. Run.

2. Do wall running.

3. Jump.

4. Double jump.

Important note: the jumping mechanic has a counter to dictate how many times the player can jump. e.g. the first jump count is 1, and the second jump count is 2. Keep this in mind once you reach the [hyperlink]Item section.

As mentioned earlier, the game is supposed to be the introduction to the beginners and newcomers, so it is important to use a control scheme that is similar to other games, like how W, A, S, and D are famously used in most games for character movement, so we need to put that under consideration.

![2-ControlScheme](https://github.com/user-attachments/assets/5d9819d8-90df-461d-b6c3-2d882d98e17c)

Normally, 3D platformers use the third-person perspective, so we followed the same camera placement. Also, the camera isn’t attached to the model of the character, both have independent rotation, but the camera is attached to the root of the character so when the player starts moving, the camera will follow them.

![3-Camera](https://github.com/user-attachments/assets/447143f7-1a45-4b45-8225-84f2332975fe)

---

<a name="LevelDesign"></a>
![LevelDesign](https://github.com/user-attachments/assets/d914738b-f4c6-417c-9a3d-2dc749d3cd12)

The game has a map that can be opened by pausing the game and opening the map menu; therefore, the level has to be designed in such a way that the player doesn’t have to open the map frequently, as it may annoy the player after doing so for a while.

Designing a level can be a hard task as it must be designed in a way so that you can direct the player to the place you want them to go to. The problem was solved by these two approaches.

In the first approach, in the area, there will be coins, and they’re placed in a way, so when the player collects them, the player will go to the desired location.

![4-CoinExample](https://github.com/user-attachments/assets/9ad5494a-5d6d-4ec9-8acb-c1bb7a3d0857)

In the second approach, points of interest like a building, a NPC, etc. are placed in locations that lead to the main objective, so the player stays on track and doesn’t go wandering in a different place and get lost.

![5-SectionOne](https://github.com/user-attachments/assets/332520fc-7417-4a00-9b33-a9de8a5e3af2)

By using both approaches, if done right, the player doesn’t even need to open the map and can use the observation skills to reach the objective, which can be more rewarding and more fun!

---

<a name="Objectives"></a>
![Objectives](https://github.com/user-attachments/assets/ac19882f-b7d2-4fca-ad79-bedd2aa3bcfe)

Each area has its own unique main objective to add variety.

### Section One

In the first area, the NPC will ask the player to find their child. The child will be hiding in huge grass blades, and the player must catch them before the time runs out.

![6-InteractiveGrass](https://github.com/user-attachments/assets/14885c75-0770-4273-8c53-56a81cc8a499)

### Section Two

In the second area, the player has to catch a fish for the NPC. The main objective takes place at the beach, and to reach the fish, the player can steer a boat to it. A fish under the water will be hard to detect, so to solve this problem, a floating indicator widget will be above the fish so that the player can go there without wasting time and getting lost.

![7-FishWidget](https://github.com/user-attachments/assets/07e1a23f-f1e3-48f5-85aa-e11b6f500885)

When the player finally reaches the fish, the player can start fishing. The fishing mechanic goes like this: a bar will pop up, and there will be a needle that goes left and right randomly. The player must place the needle in the middle; the closer the needle gets to the middle, the more points you earn. If the points exceeded the success rate, the player would catch the fish; otherwise, the fish would escape and the player has to try again. Also, there’s a timer for this mechanic.

![8-FishingDesign](https://github.com/user-attachments/assets/bd0c208e-47b2-4c2a-bd8e-278e63cdc3fa)

### Section Three

In the third area, the player is tasked with getting a ring from up the mountain. In terms of mechanics, this objective is pretty simple, as the player will only need to hit a button and that’s it, but the ring is up the mountain, so there will be some platforming to reach the apex.

![9-SecThreeDesign](https://github.com/user-attachments/assets/48c52b37-698f-4516-a888-739d6b3af7cd)

![10-Mountain](https://github.com/user-attachments/assets/81edaa26-e061-4e64-8f77-7bbab8f504dc)

### Section Four

In the fourth area, the objective takes place in a palace. The player will meet a NPC that needs help with cooking and cleaning so, the objective has two sub-objectives and once both of them are done, the main objective will be over and the timer will stop.

<p>Cooking: -</p>
Cooking is one of the sub-objectives that need to be finished. In order to finish this sub-objective, you need to cook three meals and place them on the table. Each meal has its own ingredients, and the player has the freedom to choose which ingredient they want to include. The player can only add 5 ingredients max in order to cook the meal. Once the maximum number has been reached, a timer starts, and when it's done, the player can pick up the meal and place it on the table.

![11-CookingDesign](https://github.com/user-attachments/assets/b6ecc7e4-8c9d-4c1c-bb2c-fd4758fd50ad)

![12-CookingLayout](https://github.com/user-attachments/assets/16fb8380-72d5-4a4d-96a8-885b93d93a1a)

<p>Cleaning: -</p>
Cleaning is another sub-objective the player must do. It is a simple mechanic; the player has to pick up the broom and start cleaning. The way it works is that once the player has the broom, they only need to move around, and there’s a counter that calculates the progress.

![13-CleaningDesign](https://github.com/user-attachments/assets/cc66b017-d851-4bf0-be8f-deb652247b4a)

![14-CleaningLayout](https://github.com/user-attachments/assets/73af7a94-20cd-47ea-8a11-e5a1fff748fd)

Important note: the player can choose whether to start with cleaning or cooking.

![15-CastleLayoutDrawing](https://github.com/user-attachments/assets/d6381f9d-a5ae-490c-a49b-eef5ae7f8746)

![16-CastleLayout](https://github.com/user-attachments/assets/7fd9dcbf-f05b-4d8c-8a97-564d9c8a5027)

### Section Five

In the fifth area, which is the final area. Once the player passes the gate, they have to place and rearrange the maps they got from the NPCs they met throughout the game, so the player has a full map for the last area, and they need to follow it to reach the missing child.

![17-MapsOrderDesign](https://github.com/user-attachments/assets/4e933ae8-d041-476a-aa23-a7e1673de661)

---

<a name="Items"></a>
![Items](https://github.com/user-attachments/assets/1c968764-bd70-4f7d-8047-60cdfd6ea52d)

Throughout the game, the player can collect coins to buy items to help them finish objectives that might be a bit challenging. Each item is objective-based.

The game has 3 items:

1. Jumping Boots: Help player to jump higher distance. At the beginning of the game, the player jumping count maximum number is equal to two. If the player buys the boots, then the jumping count maximum number will be three. This item would help the player in the third area, especially where there is so much platforming.

![18-BootsItem](https://github.com/user-attachments/assets/6a9456a2-6964-4565-9bf4-931d9b8c975c)

2. Fishing rod: as mentioned earlier in the second area, the player goes on a fishing mission. When the player starts fishing, a timer will start. The timer decreases at a specific rate, and if the player bought the fishing rod item, the rate would change and the timer would decrease much slower.

![19-Fishingrod](https://github.com/user-attachments/assets/bf1618f3-db23-49d5-baeb-d531912ec926)

3. Services tools: in the third area, the player has to finish two sub-objectives, cooking and cleaning. Both of them have timers, so like the fishing rod, it slows the rate of the timer.

![20-ServicesTools](https://github.com/user-attachments/assets/9b72079c-dabc-4108-b32f-333e1356bb65)

---

<a name="UI"></a>
![UI](https://github.com/user-attachments/assets/8ffa008c-87ff-4851-a69d-2e533fadab1c)

The game follows a simplistic approach for the UI design and only shows information that matters. The user interface is not just there to make the game visually interesting but also used for information like how much time is left, whether the player picked the items, or how many items the player has.

In the following sections, we will talk about what the UI design looks like in every aspect of the game.

### Character Interaction &. Dialogue

When the player approaches the NPC, a popup shows up to indicate that the player can interact with the NPC, and the player must be at a specific distance to be able to start the dialogue.

![21-CharacterInteraction](https://github.com/user-attachments/assets/60310999-b035-429f-8e12-3858df22fa77)

<div style="display: flex; justify-content: space-around;">
  <img src="https://github.com/user-attachments/assets/3c751026-d2fe-40d3-b148-4446f18e3fba" alt="Image 1" width="330"/>
  <img src="https://github.com/user-attachments/assets/49fbc866-8edf-46e6-8ba9-f82b1ad7c840" alt="Image 2" width="330"/>
  <img src="https://github.com/user-attachments/assets/a40e8e0f-c7b4-4bcd-8d60-c3d3e33d9a79" alt="Image 3" width="330"/>
</div>

As this project was created by students who had 7 other projects to take care of, we didn’t have the capability to do a full cutscene, so we followed a famous approach used in other games like [hyperlink]Hollow Knight and [hyperlink]Persona, in which when the dialogue starts, the text shows up and the player can start reading. It is like the subtitles, but the player has the power to control the dialogue and proceed with their own pace.

### Free Roam

When the player walks around and doesn’t talk to the NPC, nothing gets shown, as mentioned earlier. We follow a simple design and only show information that matters, so when the player starts an objective, a timer shows up at the top of the screen.

![23-Timer](https://github.com/user-attachments/assets/cb749f7b-8b3b-4e43-80b4-967556a5a5a9)

### Indication

When the player’s state changes, the game must show a message that something happened so the player can keep up with the game and don’t get confused or lost, e.g. the objective started or the player collected something.

| Caught a Fish                      | Objective Started                        | Picked Item                       |
|:-------------------------------------:|:------------------------------------:|:----------------------------------:|
| ![24-CaughtFish](https://github.com/user-attachments/assets/854914a9-0dcf-4cca-a1cd-eb76a4e87aa7) | ![24-ObjectiveStarted](https://github.com/user-attachments/assets/aa2594d3-d0dd-4f16-995a-5b504c8f82e0) | ![24-PickedItem](https://github.com/user-attachments/assets/7e5a33a2-2a78-4e34-8a38-8eada17374a5) |

