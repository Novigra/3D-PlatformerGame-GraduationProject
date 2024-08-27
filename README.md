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
    - [Menu](#Menu)
    - [Fishing](#Fishing)
    - [Cooking](#Cooking)
    - [Arranging Maps](#Arranging-Maps)
  - [Saving &. Loading](#SaveLoad)
- [Technical Implementation](#Tech)
  - [Player Input](#PInput)
  - [Character Interaction &. Dialogue](#CharInt)
  - [User Interface](#TUI)
    - [Pause Menu](#Pause-Menu)
  - [Game Mechanics](#GameMech)
    - [Tech - Section One](#Tech-Section-One)
    - [Tech - Section Two](#Tech-Section-Two)
    - [Tech - Section Three](#Tech-Section-Three)
    - [Tech - Section Four](#Tech-Section-Four)
    - [Tech - Section Five](#Tech-Section-Five)
  - [Saving &. Loading](#TechSaveLoad)
- [Conclusion](#Conc)
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

Important note: the jumping mechanic has a counter to dictate how many times the player can jump. e.g. the first jump count is 1, and the second jump count is 2. Keep this in mind once you reach the [Item section](#Items).

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

As this project was created by students who had 7 other projects to take care of, we didn’t have the capability to do a full cutscene, so we followed a famous approach used in other games like Hollow Knight and Persona, in which when the dialogue starts, the text shows up and the player can start reading. It is like the subtitles, but the player has the power to control the dialogue and proceed with their own pace.

### Free Roam

When the player walks around and doesn’t talk to the NPC, nothing gets shown, as mentioned earlier. We follow a simple design and only show information that matters, so when the player starts an objective, a timer shows up at the top of the screen.

![23-Timer](https://github.com/user-attachments/assets/cb749f7b-8b3b-4e43-80b4-967556a5a5a9)

### Indication

When the player’s state changes, the game must show a message that something happened so the player can keep up with the game and don’t get confused or lost, e.g. the objective started or the player collected something.

| Caught a Fish                      | Objective Started                        | Picked Item                       |
|:-------------------------------------:|:------------------------------------:|:----------------------------------:|
| ![24-CaughtFish](https://github.com/user-attachments/assets/854914a9-0dcf-4cca-a1cd-eb76a4e87aa7) | ![24-ObjectiveStarted](https://github.com/user-attachments/assets/aa2594d3-d0dd-4f16-995a-5b504c8f82e0) | ![24-PickedItem](https://github.com/user-attachments/assets/7e5a33a2-2a78-4e34-8a38-8eada17374a5) |

### Menu

When pausing the game, we first decided to make the screen blur and then load the widget, Nier Automata style, but later on we didn’t like it, so we decided to have a 3D book, and when the player hits the pause button, a book spawns on the right of the screen, moves to the center of the screen, and finally moves towards the camera, and when it reaches a specific destination, a widget gets drawn on the screen.

![25-FlyingBook](https://github.com/user-attachments/assets/d0d84746-dae8-4551-9dfc-781c1fe56d36)

Once the widget gets added to the viewport, the pause menu, the player has multiple choices like opening the maps, loading the last saved checkpoint, remapping keys, or closing the game. The way the widget works is that there are the options on the left and, on the right, the details of the option the player picked.

![26-PauseMenuOptions](https://github.com/user-attachments/assets/9d0fe7a6-6adc-43eb-955b-349abd5872b3)

### Fishing

When the player starts the fishing mini-game, a widget appears and a bar appears, and the player has to control that moves left and right. The red, yellow, and green colors will give the message to the player that they must place the needle in the middle of the bar.

![27-FishingUI](https://github.com/user-attachments/assets/2d9ed3ef-3053-4b86-a768-bf6dc7d21000)

### Cooking

When the player enters the room, a message written on the wall explains to them what is required of them to do. A popup message could’ve been more appropriate, but this was a last-minute decision, so the message was added on the wall as, in terms of technicality, this was the faster approach.

![28-WallWriting](https://github.com/user-attachments/assets/1fb5259d-52d0-4e59-8ddc-f51718fda864)

Above each ingredient, a text to indicate what it is. For static meshes, it is good practice to add something that tells the player that they can interact with it. For example, add glowing to the object, add text, etc.

![29-IngredientsUI](https://github.com/user-attachments/assets/bc14530c-781a-4bde-8080-83ffa54588e0)

For the pot, there’s a floating text to indicate how many ingredients the player collected, so the player knows whether they can start cooking or not. After you start cooking, the timer shows up.

![30-NumberOfIngredients](https://github.com/user-attachments/assets/4ec0b944-c6f1-4323-9239-f573ec236125)

### Arranging Maps

In the last area, the player has to arrange the maps they got to get the full map of the last area.

![31-ArrangeMapsUI](https://github.com/user-attachments/assets/df8d6dca-361a-4a2b-afc9-c2612851f243)

---

<a name="SaveLoad"></a>
![SaveLoad](https://github.com/user-attachments/assets/f72a847a-899c-4a05-a61f-22a83aa22ee7)

The game saves the data in the following states:

1. The player talked to the NPC, and the main objective got initiated.

2. The player talked to the NPC and took the key after finishing the main objective.

3. The player closed the game.

And the game loads in the following states:

1. When clicking on the load button.

2. When clicking on the load the last saved checkpoint button.

3. When the time runs out.

4. When the player loses their full health.

After knowing everything about the game design and how the game works theoretically. Let’s head and talk about the technical implementation and show how we turned these ideas into the final product.

---

<a name="Tech"></a>
![Tech](https://github.com/user-attachments/assets/696b6272-565e-4c03-8389-4e4ee9e66249)

Before delving into the specifics, it's crucial to acknowledge the extensive nature of the code. Therefore, we will limit our discussion to essential details such as the rationale behind our decisions or the underlying principles. For example, when discussing player input, we will discuss why the project has different Input Mapping Contexts (IMCs) and how the system works; there’s no reason to mention bindings as it’s self-explanatory.

---

<a name="PInput"></a>
![PInput](https://github.com/user-attachments/assets/e5d29da1-aed2-47ec-a5ec-627757d13b64)

The game uses the new “Enhanced Input” system, which is much more powerful than the older system. In the older system, you can only bind input, and if the same button is bound with multiple functionalities, all of them will be listening for the button, so you had to create states, which is cumbersome. Luckily, Epic Games has developed a new system to solve this problem.

When managing input, you have to ask a couple of questions:

1. What kinds of states are available? Can the player run? Can they steer a boat? Are they controlling the UI?
2. Which keys can be used and what type of input is it? Is it a Boolean (ON/OFF) or is it a float (0 to 1) “normalized”?

Asking these questions is important as you don’t go to the project settings and manage keys in the input tab; instead, you first create an Input Mapping Context (IMC), which represents the state of the player, and inside it you add the actions “Input Actions” that the player can do while they are in this state. Let’s pick a scenario to understand the workflow of setting up the input.

Let’s say that you want to manage player movement. First, we create an IMC called “IMC_Movement”, but to follow the project, we will call it “IMC_RabbitContext”, which honestly the first name makes more sense, but for the sake of consistency, we will follow the actual names that were used in the project.

![32-MovementIMC](https://github.com/user-attachments/assets/b36416cd-d810-4010-8c90-c149ea35f0c1)

The “IMC_RabbitContext” is the state that represents player movement, so if the player is in this state, they can run, jump, do wall running, and more, but to represent these actions, IMC is not enough, so we use Input Actions (IAs) to represent such actions.

![33-IMCDetails](https://github.com/user-attachments/assets/f44f8f61-ad61-47a1-81d5-b08a8251ef4f)

Each input action can have its own modifiers and triggers. They add functionalities like how the input is supposed to react if the player presses on a button and holds it for an extended period of time, for example.

Once finishing up the IMC, it must be added to the player class, “AMotherRabbit”, so it can be added to the local player subsystem. You can think of the subsystem as the brain of the player; not only does the subsystem hold IMCs, but it also sets priorities. Let’s say the button “W” can make the player move forward, but it can also make the player navigate through the user interface, the pause menu, for example. Now let’s say that the player decided to pause the game, so another IMC gets added to the subsystem, which means we have two active IMCs, “IMC_RabbitContext” and "IMC_UserInterfaceContext". Both of them use “W”, and of course, the player doesn't move forward while using the pause menu; this is where priority is needed.

This is how input mostly works: you define the IMCs and IAs and then decide how the IMCs should be read, and of course there’s a crucial step, which is binding them, and it is a straight-forward step.

[MotherRabbit.h - Different IMCs and IAs](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Public/Characters/MotherRabbit/MotherRabbit.h)

```cpp
// Input Mapping Contexts
UPROPERTY(Specifiers)
class UInputMappingContext* MovementMappingContext;

UPROPERTY(Specifiers)
class UInputMappingContext* UserInterfaceMappingContext;

UPROPERTY(Specifiers)
class UInputMappingContext* FishingMappingContext;

UPROPERTY(Specifiers)
class UInputMappingContext* BoatMappingContext;
...
// Input Actions
UPROPERTY(Specifiers)
class UInputAction* MovementAction;

UPROPERTY(Specifiers)
class UInputAction* JumpAction;

UPROPERTY(Specifiers)
class UInputAction* LookAction;

UPROPERTY(Specifiers)
class UInputAction* EnterAction;

UPROPERTY(Specifiers)
class UInputAction* BackAction;

UPROPERTY(Specifiers)
class UInputAction* NavigationAction;

UPROPERTY(Specifiers)
class UInputAction* PauseAction;
...
```

[MotherRabbit.cpp - bind navigation input action (navigation used for UI)](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/Characters/MotherRabbit/MotherRabbit.cpp)

```cpp
void AMotherRabbit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Use CastChecked so when casting fails, crash the game
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked< UEnhancedInputComponent>(PlayerInputComponent))
	{
		// UI
		EnhancedInputComponent->BindAction(NavigationAction, ETriggerEvent::Started, this, &AMotherRabbit::Navigation);
	}
}
```

[MotherRabbit.cpp - navigation logic](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/Characters/MotherRabbit/MotherRabbit.cpp)

```cpp
void AMotherRabbit::Navigation(const FInputActionValue& Value)
{
	const float ActionValue = Value.Get<float>();

	if (Controller && (ActionValue != 0.0f))
	{
		PrintScreen(false, 10.0f, FColor::Green, "Current Page Navigation (Action Value) = %f", ActionValue);
		OnPressingNavigationAction.Broadcast(ActionValue);
	}
}
```

---

<a name="CharInt"></a>
![CharInt](https://github.com/user-attachments/assets/d490c93e-bd60-45bf-a06d-f6a9367e900c)

There are multiple key points that must be discussed regarding the interaction between the player and the NPC:

1. When initiating the dialogue, the camera's location and rotation get updated to a new camera placement (the red arrow in the picture below).

2. The movement IMC gets removed, and the dialogue IMC gets added.

3. The dialogue widget gets drawn on the screen.

![34-NPCDetails](https://github.com/user-attachments/assets/a079e4eb-2b0e-478b-bdb7-8eb6a1759ec5)

Throughout the entirety of the project, when two entities interact with each other, we care about two things:

1. Is the communication direct?

2. How will the interaction be handled?

When programming interactions, it is a good practice to keep entities separate in terms of logic. For example, when a player hits the collision of the NPC and presses the “E” button to initiate the dialogue, instead of calling the dialogue system in the player class, we just add an even dispatcher, so when the player presses the button, all the objects that are listening and waiting for the call start executing.

The event dispatcher is a powerful tool, so if you were put in a situation where you had to drastically change your code, you wouldn’t have to change the code in the player class, which solves the reliance problem, and you could swap codes without breaking anything.

[MotherRabbit.cpp - Interaction Action](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/Characters/MotherRabbit/MotherRabbit.cpp)

```cpp
void AMotherRabbit::Interact(const FInputActionValue& Value)
{
	const bool ActionValue = Value.Get<bool>();
	CameraGameplayTransform = GetPlayerCameraTransform();

	if (Controller && ActionValue)
	{
		OnInteractAction.Broadcast();
	}
}
```

This piece of code is incredible; a delegate “OnInteractAction” was created in the player class and then broadcasted, so the listeners can do the actions that were bound to the delegate. What’s awesome about this function is that it is used for different applications in the game, like collecting the ring, collecting the ingredients, placing dishes, and more.

If you noticed in the function, we also store the transform (location, rotation, and scale, but scale isn’t necessary for the logic), as the camera’s transform will be updated when the dialogue starts and then go back to the original transform when the dialogue is done.

Starting a dialogue could be done in multiple ways: the way it's done in the project, the dialogue gets initiated in the NPC class, and as mentioned earlier, the camera's transform changes, IMCs get removed and added, and the dialogue widget shows up.

[NPC.cpp - Dialogue Initiation](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/Characters/NPC/NPC.cpp)

```cpp
void ANPC::StartDialogue() 
 { 
         bStartCameraTransition = true; 
         Player->CurrentInteractNPC = this; 
  
         Player->RemovePlayerAllMappingContexts(); 
         Player->SetPlayerMappingContext(Player->DialogueMappingContext, 0); 
  
         APlayerController* PlayerController = Cast<APlayerController>(Player->GetController()); 
         if (PlayerController) 
         { 
                 UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, DialogueMenuUI); 
                 Widget->AddToViewport(); 
         } 
  
         Player->SetInteractWidgetVisibility(false); 
 }
```

<p>There are two important processes that happen simultaneously:</p>
First, in code, there's a boolean “bStartCameraTransition” that, when set to true, the camera starts transitioning to the new camera placement. This process doesn't happen in one frame; it updates over time, which means the functionality must happen in the tick function that gets executed multiple times throughout the entity's lifetime.

The way the location and rotation get updated, we use interpolation, and the idea behind it is that you have a set of data and we are interested in two points to estimate the midpoint. There are different interpolations, like linear, polynomial, and more. In an unreal engine, you don’t need to do the math; the engine provides different types out of the box, and you choose the type that suits the application. 

Two interpolations have been made. First, VInterpTo is the interpolation of the location, and ‘V’ stands for vector (x, y, z). Second, QInterpTo, which is also interpolation, but for the pitch, yaw, and roll of the camera, and ‘Q’ stands for quaternion, which is a much better approach than Euler to avoid gimbal lock and it's much more efficient.

[NPC.cpp - Camera Transform Update](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/Characters/NPC/NPC.cpp)

```cpp
// Called every frame 
 void ANPC::Tick(float DeltaTime) 
 { 
         Super::Tick(DeltaTime); 
  
         CameraTransition(DeltaTime); 
 }

void ANPC::CameraTransition(float DeltaTime) 
 { 
         if (bStartCameraTransition) 
         { 
                 FTransform PlayerCamera = Player->GetPlayerCameraTransform(); 
                 FTransform CameraPlacement = DialogueCameraPlacementArrow->GetComponentTransform(); 
  
                 FVector CurrentCameraLocation = FMath::VInterpTo(PlayerCamera.GetLocation(), CameraPlacement.GetLocation(), DeltaTime, CameraTransitionSpeed); 
                 FQuat CurrentCameraRotation = FMath::QInterpTo(PlayerCamera.GetRotation(), CameraPlacement.GetRotation(), DeltaTime, CameraTransitionSpeed); 
  
                 FTransform Transition; 
                 Transition.SetLocation(CurrentCameraLocation); 
                 Transition.SetRotation(CurrentCameraRotation); 
                 Transition.SetScale3D(FVector(1.0f)); 
  
                 Player->SetPlayerCameraTransform(Transition); 
  
                 PrintScreen(false, 2.0f, FColor::Green, "CurrentCameraLocation = %f X : %f Y : %f Z", CurrentCameraLocation.X, CurrentCameraLocation.Y, CurrentCameraLocation.Y); 
         } 
 }
```

The second process that happens is the initiation of the dialogue widget. In this section, we will focus on the logic of the dialogue itself, but the UI design and implementation will be discussed in [the user interface section](#TUI).

When implementing a dialogue system, it is a good practice to create a whole class for it with the identifiers and content, but the game is simple and there're no different kinds of NPCs that need special functionality in terms of processing the dialogue; therefore, the dialogue implementation was done in the dialogue widget.

The content of the dialogue depends on the NPC; a TMap declared in the NPC class holds an integer key and a text struct, which is the content itself, and we also have an array of “NameHeader” that includes a sequence of names. Keep in mind that the content and the active names of each party, the player and the NPC, are all stored in the NPC class. This approach only works if the game follows simple scene design and interactions.

![35-DialogueContent](https://github.com/user-attachments/assets/ff8ee2ae-b1fa-45e6-b015-36ab94a45593)

Back to the dialogue implementation in the dialogue UI. The way it gets shown is pretty simple; we just increment the index of the next piece of dialogue that gets shown on the screen every time the player presses the ‘E’ button, and if you noticed in the picture above of the dialogue content, there are empty spaces; these are the stopping points. Throughout the game, the player meets the NPC two times, and to separate each interaction, we used empty cells that, when detected, the dialogue stops, and what happens next depends on whether the player finishes the main objective or not.

[DialogueMenuUI.cpp - Dialogue Implementation](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/UserInterface/DialogueMenuUI.cpp)

```cpp
void UDialogueMenuUI::NextDialogueText() 
 {
         // If the cell is not empty proceed to the next lines of dialogue
         if (!NPC->GetNameHeader(Index).IsEmpty()) 
         { 
                 Speaker->SetText(NPC->GetNameHeader(Index)); 
                 Dialogue->SetText(NPC->GetDialogue(Index)); 
  
                 Index++; 
         } 
         else 
         { 
                 // Increment, so the starting line next time is not empty and remove bindings
                 NPC->SetDialogueIndex(++Index); 
                 NPC->OnFinishDialogue(); 
                 
                 // Remove IMCs, unbind any delegates
                 Player->RemovePlayerAllMappingContexts(); 
                 NPC->SetNPCInteractionAvailability(false); 
                 NPC->SetCameraSceneState(false); 

                 // Get the NPC Level ID and make the map available to the player according to the level ID
                 int32 Level = NPC->GetNPCCurrentLevel(); 
                 Player->CollectedMaps[Level] = true; 
                 //NPC->SetCameraToOriginalState(true); 

                 // Reset the camera and add movement IMC
                 Player->SetPlayerCameraTransform(Player->GetPlayerOriginalCameraTransform()); 
                 Player->SetPlayerMappingContext(Player->MovementMappingContext, 0); 
  
                 // If starting the objective, prepare widgets and timers, else player is allowed to open the gate
                 if (!NPC->GetObjectiveComplete()) 
                 { 
                         if (APlayerController* PlayerController = Cast<APlayerController>(Player->GetController())) 
                         { 
                                 UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, MissionIndicationUI); 
                                 Widget->AddToViewport(); 
                         } 
  
                         UGameplayHUDUI* GameWidget = Player->GameplayHUDWidget; 
                         GameWidget->Player = Player; 
                         GameWidget->NPC = NPC; 
                         GameWidget->CurrentTimer = NPC->GetObjectiveTimer(); 
                         GameWidget->ObjectiveAnimEvent(); 
                         GameWidget->Timer->SetText(FText::AsNumber(NPC->GetObjectiveTimer())); 
                         GameWidget->CurrentObjective->SetText(NPC->GetCurrentObjective()); 
                         GameWidget->bStartTimer = true; 
                 } 
                 else 
                 { 
                         Player->CollectedKeys[Level] = true; 
                 } 
  
                 // Saving the data asynchronously
                 APlayerGameModeBase* GameMode = Player->GetPlayerGameMode(); 
                 if (GameMode) 
                 { 
                         GameMode->SaveAllPlayerData(1); 
                 } 
  
                 RemoveFromParent(); 
         } 
 }
```

<p>Now that we understand interaction and dialogue implementation, we keep talking about widget initiations, but how does it work?</p>
Well, let's dive deep and understand the user interface in Unreal Engine.

---

<a name="TUI"></a>
![UI](https://github.com/user-attachments/assets/ec2becca-fb9d-453c-9910-7511c71f79e8)

For UI, two paths can be chosen: UMG, which is more designer-friendly; you can drag and drop and see changes in real-time. Slate is the second option, but it's harder and it's more code-centric, which means higher performance. But it doesn't mean that UMG is bad in terms of performance; it highly depends on what kind of UI you're doing and if using Slate over UMG would have a significant or a margin effect.

The project only uses UMG as the UI isn't too complex to warrant the use of Slate. We will talk about the process of creating a pause menu widget, and pause menu is specifically picked as it covers everything regarding the creation of a user interface.

### Pause Menu

As mentioned in the game design section, when the player pauses the game, a book flies to the middle of the screen, then towards the player, and when it reaches a specific location, the widget gets added to the screen.

The logic behind the flying book is pretty simple. The book spawns to the right of the screen, which means the location and rotation of the player camera must be known, and we must decide how far it gets from the camera. One way of doing it is to get the front/forward vector and the right vector of the camera and add both of them to get the new vector, which will be the spawning location of the book, and the front/forward vector is also used for book transition.

Finally, when the book reaches the location we specified, a couple of things happen:

1. The widget gets created and added to the viewport.

2. The player controller has multiple input modes, like “UI only”, “Game only”, and “Game and UI”. These modes dictate how the game will read the input from the user. For example, if “UI only” was the current active mode, then the user wouldn’t be able to interact with the entities in the world, and the only things that are interactable are the widget elements. Pause menu is using “Game and UI” mode.

3. The mouse cursor gets shown on the screen.

It’s important to mention that we need to know the player controller so we can modify the HUD and show the correct widget. Luckily, the game is a single-player game, and we only have one local player host, so it is a straight-forward approach, but if the game is a multi-player game, then there is a lot more planning that needs to be done.

[FlyingBook.cpp - Adding a Widget to The Viewport](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/UserInterface/FlyingBook.cpp)

```cpp
void AFlyingBook::SpawnPauseUI()
{
	if (AMyPlayerController* PlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0)))
	{
		PlayerController->CurrentHUD = CreateWidget<UUserWidget>(PlayerController, PauseMenuUI);
		PlayerController->CurrentHUD->AddToViewport();
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
	}
}
```

For widget creation, we follow the same steps we did for other classes. We first create a C++ class for the widget, and we inherit from the “UUserWidget” class to use all the widget components. In the class, you can define the elements that should be there, and you can also add a specifier that forces the designer to add the element that must be there.

[PauseMenuUI.h - Button Creation](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Public/UserInterface/PauseMenuUI.h)

```cpp
// BindWidget specifier is there, so if the continue button doesn't exist when working on the design of the button, the blueprint won't compile
UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
class UButton* BtnContinue;
```

Honestly, using “BindWidget” could bring problems and a whole lot of back and forth between the designer and programmer, so communication is an important key, especially when working on anything related to the user interface.

The UI implementation has a huge weakness, which is repetition. For example, the navigation system between buttons was written multiple times throughout the classes, which is not ideal. Normally, you create a class that could be a UI manager, and it has the functionalities that many classes will use. This problem was known, but because of time constraints, we couldn’t clean up the code. In terms of performance, it won’t affect it, but for code readability, it can be a bit frustrating to read.

For widget class creation, there are three important functions that need to be considered:

1. Native Construct: anything inside this function will get executed when the widget fully launches.

2. Native Pre Construct: anything inside this function will get executed once the widget gets created, which means that the widget isn’t fully created, but code can still get executed.

3. Native Tick: anything inside this function will get executed every frame.

For each button that got created, they are added to an array of buttons, so in the navigation system, we can switch between different buttons, and we also have an array of widget animations, so when navigating to the next button, an animation associated with the index of the button gets played. We also have a delegate, so if the player presses the enter or left-click button, the button gets executed.

[PauseMenuUI.h - Load Button Example](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Public/UserInterface/PauseMenuUI.h)

```cpp
// Delegate creation
DECLARE_DELEGATE(FButtonAction);

class GRIEF_API UPauseMenuUI : public UUserWidget
{
	// It will hold the index of the button and the function that is associated to it
	TMap<int32, FButtonAction> BtnAction;

	// Load button creation
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* BtnLoad;
	...
	
	void SetupButtons();
	
	UFUNCTION()
	void Interact();
	
	UFUNCTION()
	void Load();
}
```

[PauseMenuUI.cpp - Load Button Example (continue)](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/UserInterface/PauseMenuUI.cpp)

```cpp
// Execute when the widget is fully created
void UPauseMenuUI::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Get the reference of the player
	Player = UGameplayStatics::GetPlayerController(this, 0)->GetPawn<AMotherRabbit>();
	if (Player)
	{
		// Bind the enter action delegate to the interact function
		Player->OnPressingEnterAction.AddDynamic(this, &UPauseMenuUI::Interact);
	}
	
	SetupButtons();
}

void UPauseMenuUI::SetupButtons()
{
	// Bind mouse click action to the load function
	// Index 0 -> Continue, Index 1 -> Load, etc.
	BtnArr[1]->OnClicked.AddDynamic(this, &UPauseMenuUI::Load);
	
	// Add the index that represents the load button, and associate it to the load function
	BtnAction.Add(1, FButtonAction::CreateUObject(this, &UPauseMenuUI::Load));
}

void UPauseMenuUI::Interact()
{
	// Execute it when the player presses the enter button
	if (BtnAction[BtnArrIndex].IsBound())
	{
		BtnAction[BtnArrIndex].Execute();
	}
}

void UPauseMenuUI::Load()
{
	if (PlayerController)
	{
		// Create the loading screen widget and add it to the viewport
		UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, LoadingScreenUI);
		Widget->AddToViewport();
		
		// Load player's last saved data
		APlayerGameModeBase* GameMode = Player->GetPlayerGameMode();
		if (GameMode)
		{
			GameMode->LoadAllPlayerData();
		}
	}
}
```

This is how most of the buttons are working. After finishing each button's logic and functionality, we create a blueprint that is derived from this class to start designing and animating.

![36-PauseMenuUI](https://github.com/user-attachments/assets/fef3d128-370c-418f-9293-753077cadcf1)

![37-PauseMenuUIAnim](https://github.com/user-attachments/assets/d34269ab-cac8-43bc-a758-d596cbb29481)

In the pause menu, we can press the map button or settings, which means new elements are supposed to show up. One way of doing it in an efficient way is to create a separate widget that holds the elements, and we also add a container in the pause menu widget to hold the child widget.

![38-ChildPause](https://github.com/user-attachments/assets/ff8e0d8f-2299-41e7-957c-4f68b9d960f7)

![39-ChildMap](https://github.com/user-attachments/assets/423c3871-5443-4ee6-a020-8cdca1550497)

[PauseMenuUI.h - Child Widget](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Public/UserInterface/PauseMenuUI.h)

```cpp
class GRIEF_API UPauseMenuUI : public UUserWidget
{
	// Current active child widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenus")
	class UUserWidget* CurrentChildUI;
	
	// Variables that hold the widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenus")
	TSubclassOf<class UUserWidget> MapMenuUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD|ChildMenus")
	TSubclassOf<class UUserWidget> ToolsMenuUI;
	...
	
	UFUNCTION()
	void Maps();
	
	UFUNCTION()
	void Tools();
	
	UFUNCTION()
	void OpenChildUI(TSubclassOf<class UUserWidget> Map);
}
```

[PauseMenu.cpp - Child Widget (Continue)](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/UserInterface/PauseMenuUI.cpp)

```cpp
// Executed when the player presses on the maps button
void UPauseMenuUI::Maps()
{
	if(!CurrentChildUI)
		OpenChildUI(MapMenuUI);
}

// Executed when the player presses on the tools button
void UPauseMenuUI::Tools()
{
	if(!CurrentChildUI)
		OpenChildUI(ToolsMenuUI);
}
...

// Add the child widget to the viewport on the second half of the screen
void UPauseMenuUI::OpenChildUI(TSubclassOf<class UUserWidget> Widget)
{
	if (PlayerController)
	{
		// Create the widget and add it to the horizontal box container
		CurrentChildUI = CreateWidget<UUserWidget>(PlayerController, Widget);
		ChildUI_HorizontalBox->AddChild(CurrentChildUI);

		bChildHudOpen = true;
		
		// Increment so to keep up with the number of opened child widgets
		PlayerController->NumberOfOpenChildren++;
	}
}
```

And removing the child widget is a straight-forward approach. The widgets get added to a tree-like structure, and the child can be removed from such a tree.

[PauseMenuUI.cpp - Remove Child Widget](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/UserInterface/PauseMenuUI.cpp)

```cpp
void UPauseMenuUI::CloseChildUI()
{
	// A child widget must be active
	// And the number of active children must be less than two, which means that only one is currently active
	// For example: close the child widget (Map widget) if it is the only active child. Pause Menu-> Maps Menu (Total = 1)
	// But don't close if multiple ones are open. Pause Menu -> Maps Menu -> Map One (Total = 2)
	if (CurrentChildUI && (PlayerController->NumberOfOpenChildren < 2))
	{
		ChildUI_HorizontalBox->RemoveChild(CurrentChildUI);
		CurrentChildUI = nullptr;
		PlayerController->NumberOfOpenChildren--;

		bChildHudOpen = false;
	}
}
```

That’s how the UI mostly works, but of course each widget has its own logic and implementation and slight differences.

---

<a name="GameMech"></a>
![GameMech](https://github.com/user-attachments/assets/f1052ea0-1009-4bf5-a220-dd811da90b94)

Each level has a main objective that needs to be met. Each main objective has unique interactions, and we will talk about each main objective implementation.

### Tech - Section One

In the first main objective, the player has to catch a child who is running in between long grass blades. There are four important components:

1 . There is a huge collision box that adds a new IMC to the player controller subsystem so that the ‘E’ button logic changes. The reason behind this logic is that the ‘E’ button is already assigned in the Movement IMC, so if the player pressed ‘E’ to catch the NPC, but coincidentally, the player interacted with another entity that can read the ‘E’ button, confusion could happen and it could lead to crashing, so to avoid that, we added a new IMC, so when the player enters the collision, the key ‘E’ would only do one action, which is to catch the child.

2. A navigation box is placed in the area, so the child moves randomly in the navigation box.

3. We have the child, placed in the map.

4. Finally, when the player catches the child, the NPC that the player talked to earlier will spawn in a pre-determined area.

![40-ChildLocation](https://github.com/user-attachments/assets/fa47cd15-a153-4575-a98e-af97642ec3a5)

![41-NewActorLocation](https://github.com/user-attachments/assets/58652b4c-b089-4e91-a736-bb69b4b18b0f)

![42-Association](https://github.com/user-attachments/assets/e8c536dd-e9f8-487c-babc-18e1cf4454d3)

The code is super simple; you need collision-hit listeners, modify IMCs, and bind delegates like the interact action. You can check [CatchActorSite.cpp](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/GameLogic/CatchActorSite.cpp) and [Child.cpp](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/Characters/NPC/Child.cpp).

### Tech - Section Two

The second main objective is to go fishing, which means we need a boat to steer and a fish to grab.

For the boat, we have a big mesh that represents the boat that the player will be able to stand on and control, which means we need to decide where the player can control the boat, and we can do that through a collision box that if the player hits, they can control the boat. Also, we need a socket, which can be used to place the player on it, so the character won’t move around while moving the boat. 

![43-BoatBP](https://github.com/user-attachments/assets/b5585118-7882-4d9c-874e-43631dd6701f)

![44-BoatSocket](https://github.com/user-attachments/assets/e6bceb86-3420-4020-b5dc-d6b37e321b4d)

Controlling the boat means that the player's state changes from moving on the ground to steering the boat, which means we need to change IMCs. Thus,  the player won’t be able to jump or run; they can only steer the boat left or right, move forward/backward, and also catch fish.

The fish has multiple important components:

1. The collision if the player hits it, the fishing mini-game will start.

2. A huge widget pops up above the fish when the player enters the second location, so the player knows where the fish is and goes to it.

3. When starting the fishing mini-game, a widget gets added to the screen, if the player exceeds the success rate, then the fish gets added to the boat, but if the player fails to reach the success rate, the fish location changes and the player has to try again.

![45-Fish](https://github.com/user-attachments/assets/94fd550d-5a86-4bb4-9c47-a848a48c09e2)

![46-StartFishing](https://github.com/user-attachments/assets/de2108f8-0f41-4235-975b-c1e07939e30c)

![47-FishingMinigame](https://github.com/user-attachments/assets/e1f5e632-9e5e-40a1-93c3-fda5d7a778ed)

![48-CaughtFish](https://github.com/user-attachments/assets/43218df7-0456-43de-bd2c-dd9f1c0a082c)

### Tech - Section Three

The desert level might be the easiest when it comes to implementation. The player has to grab the ring up the mountain, so you only need to manage collisions and interact with the action delegate. This objective heavily relies on platforming and passing obstacles.

![49-Mountain](https://github.com/user-attachments/assets/1200ceb7-5eb4-4faf-b5d8-d9dd407b2e29)

![50-Ring](https://github.com/user-attachments/assets/316e2c81-36f6-4f17-a211-cd6cc5a07a3d)

### Tech - Section Four

This level is unique in terms of managing whether the player finishes the main objective or not. The past objectives had only one activity, but this time we have two, which means we have sub-objectives; therefore, we need a counter that keeps up with how many objectives were done.

Cleaning is one of the sub-objectives that must be done to proceed to the next area. We need a broom placed in the area so the player can pick it up. There’s a socket attached to the hand bone of the character, so when the player picks up the broom, it sticks to the socket, and a different animation gets played.

![51-MundaSocket](https://github.com/user-attachments/assets/3a579336-0081-4a57-b08f-d4810f4d2d23)

[Cleaning.cpp - Attaching the broom to the player](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/GameLogic/Cleaning.cpp)

```cpp
void ACleaning::CollectBroom()
{
	Player->bCollectedBroom = true;
	// Get the socket, the name must match up
	const USkeletalMeshSocket* RightHandSocket = Player->GetMesh()->GetSocketByName("RightHandSocket");
	if (RightHandSocket)
	{
		// Disable collision to avoid weird behavior
		Broom->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		// Remove the 'E' key interaction widget and remove any delegates that were bound in the class
		Player->SetInteractWidgetVisibility(false);
		Player->OnInteractAction.RemoveAll(this);
		
		// Attach it to the player
		RightHandSocket->AttachActor(this, Player->GetMesh());
	}
	else
	{
		// For debugging
		PrintScreen(true, 10.0f, FColor::Red, "Socket is null");
	}
}
```

For the cleaning mechanics, the player only needs to move around, and there’s a number that adds up every time the player moves, and if reached, the broom gets despawned. A number was essential to be visible, so the player understands that there’s progress, but unfortunately, because of time constraints, the number visuals weren't added.

Cooking is the second sub-objective that must be done. Keep in mind that there’s no specific sequence; the player has the freedom to play any of the sub-objectives in any order.

There are three important entities:

1. Ingredients

There are different ingredients that are placed in the room, and the player can pick up to the inventory capacity. 

[Ingredient.cpp - Collect Ingredients](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/GameLogic/Ingredient.cpp)

```cpp
void AIngredient::CollectIndgredient()
{
	if (!(Player->NumberOfIngredients == InventoryCapacity))
	{
		FPlayerItemStruct PlayerItem;
		PlayerItem.ItemName = IngredientName;
		PlayerItem.ItemType = "Ingredient";
		PlayerItem.bOwnItem = true;

		Player->PlayerItem.Add(PlayerItem);
		Player->NumberOfIngredients++;
		
		// A custom event so that a pop-up message shows up to indicate that the player collected the item
		Player->OnPickingItemEvent();
	}
}
```

If you noticed in the code, there’s a data type called “FPlayerItemStruct”, which is a struct that represents the item and its details, and it is used as an inventory system.

[MohterRabbit.h - Player Item Struct](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Public/Characters/MotherRabbit/MotherRabbit.h)

```cpp
struct FPlayerItemStruct
{
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	FString ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemDetails")
	bool bOwnItem;

	// Initializer list to avoid null values and building problems
	FPlayerItemStruct() : ItemName(TEXT("")), ItemType(TEXT("")), bOwnItem(false){}
};
```

This structure isn’t only used for holding the ingredients. In the game design section, we discussed that the player can buy items that can help them throughout the game, and the struct is also used for holding the items that are bought.

After the player collects the ingredients, they can go to the pot to start cooking, and above the pot there will be a floating widget to indicate how many ingredients the player collected. If the required number is reached, the player can start the cooking, and a timer pops up. When the cooking timer reaches zero, the player can pick up the food, and then finally, they can place the dishes on the table.

![52-PlaceIngredients](https://github.com/user-attachments/assets/1c239faf-d872-41c8-8fe0-70a95db1b2a4)

![53-WaitForTheDish](https://github.com/user-attachments/assets/7cd8fd32-ff08-45cb-944b-28b2852ff846)

![54-PlaceDish](https://github.com/user-attachments/assets/488365c1-d10c-4b36-a52e-bcb8e1ee144c)

### Tech - Section Five

This is the last area. When the player passes the gate, a widget will show up so the player can assemble the maps to have one final map that the player has to follow to reach the missing child. A dialogue plays when reaching them, and this is the end.

![55-ArrangeMaps](https://github.com/user-attachments/assets/a30e3374-671f-4a30-b872-c8d6698c0127)

![56-WrongOption](https://github.com/user-attachments/assets/c0745ae4-8de9-406e-a91b-cb4daeb8c7aa)

![57-MapDirections](https://github.com/user-attachments/assets/73c26d79-5c13-439b-aa21-44ba3dc38f65)

---

<a name="TechSaveLoad"></a>
![SaveLoad](https://github.com/user-attachments/assets/ec181228-0d09-4419-9beb-3b43281942b9)

When wanting to save data, you first need to layout all the variables that you want to save.

[SaveLocalPlayerGame.h - Data](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Public/Data/SaveLocalPlayerGame.h)

```cpp
class GRIEF_API USaveLocalPlayerGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	USaveLocalPlayerGame();

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	FTransform PlayerPosition;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	float Timer;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	int32 Coins;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	int32 NumberOfLives;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	TArray<FPlayerOwnedItemStruct> PlayerOwnedItems;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	TArray<bool> CollectedMaps;

	UPROPERTY(VisibleAnywhere, Category = "Game|Player")
	TArray<bool> CollectedKeys;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	class AActor* LastMetNPC;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	int32 DialogueIndex;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	bool bStartConversation;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	bool bCanInteract;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	bool bIsObjectiveComplete;

	UPROPERTY(VisibleAnywhere, Category = "Game|NPC")
	bool bSpawnSubActor;
};
```

After that, in the custom gamemode class, which basically dictates the game rules and holds the current players, we save or load the data, and you have two options when it comes to saving:

1. Synchronous saving: when the game starts saving, the whole game stops until saving ends. It is used when the game closes, as we don’t want the game to close and the game didn’t fully save, so it forces the game to wait until the saving process finishes, thus avoiding corrupted save files.

2. Asynchronous saving: here the game saves the data, but at the same time the game continues. This tool is convenient when using it midgame, as it would be annoying for the players to see the game stutters during their game session.

Important detail, which is the saving slots. You can have multiple saved data points, so you need to define two important details: the name of the slot and the index. The game only has one save slot, so there is no need to keep up with different saved data.

[PlayerGameModeBase.cpp - Saving Data](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/Characters/MotherRabbit/PlayerGameModeBase.cpp)

```cpp
void APlayerGameModeBase::SaveAllPlayerData(int32 SaveDataType)
{
	// Only need one saving slot
	FString SaveSlotName = TEXT("DefaultSaveSlot");
	int32 UserIndex = 0;
	USaveLocalPlayerGame* SaveGameInstance;
	
	// Check if the data exists. if it does, then load it, otherwise create a new one
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, UserIndex))
	{
		SaveGameInstance = Cast<USaveLocalPlayerGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, UserIndex));
	}
	else
	{
		SaveGameInstance = Cast<USaveLocalPlayerGame>(UGameplayStatics::CreateSaveGameObject(USaveLocalPlayerGame::StaticClass()));
	}

	if (SaveGameInstance && Player)
	{
		// Save player data
		SaveGameInstance->PlayerPosition	= Player->GetActorTransform();
		SaveGameInstance->Timer				= Player->LastTimerNumber;
		SaveGameInstance->Coins				= Player->CollectedCoins;
		SaveGameInstance->NumberOfLives		= Player->NumberOfLives;
		SaveGameInstance->CollectedKeys		= Player->CollectedKeys;
		SaveGameInstance->CollectedMaps		= Player->CollectedMaps;
		SaveGameInstance->LastMetNPC		= Player->CurrentInteractNPC;

		for (int32 Index = 0; Index < Player->PlayerItem.Num(); ++Index)
		{
			FPlayerOwnedItemStruct SavePlayerItem;
			SavePlayerItem.ItemName = Player->PlayerItem[Index].ItemName;
			SavePlayerItem.bOwnItem = Player->PlayerItem[Index].bOwnItem;

			SaveGameInstance->PlayerOwnedItems.Add(SavePlayerItem);
		}

		//Save NPC data
		if (ANPC* NPC = Cast<ANPC>(Player->CurrentInteractNPC))
		{
			SaveGameInstance->DialogueIndex			= NPC->GetDialogueIndex();
			SaveGameInstance->bStartConversation	= NPC->GetStartConversation();
			SaveGameInstance->bCanInteract			= NPC->GetNPCInteractionAvailability();
			SaveGameInstance->bIsObjectiveComplete	= NPC->GetObjectiveComplete();
			SaveGameInstance->bSpawnSubActor		= NPC->GetSpawnSubActor();
		}
		
		// Test if the process is successful
		FAsyncSaveGameToSlotDelegate SaveDelegate;
		SaveDelegate.BindUObject(this, &APlayerGameModeBase::SaveResult);
		
		// 0 -> Save synchronously
		// 1 -> Save asynchronously
		if (SaveDataType == 0)
		{
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex);
		}
		else
		{
			UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveSlotName, UserIndex, SaveDelegate);
		}
	}
}

void APlayerGameModeBase::SaveResult(const FString& SaveSlotName, const int32 UserIndex, bool bSuccess)
{
	// Print if the process is successful or not (for debug reasons)
	if (bSuccess)
	{
		PrintScreen(true, 5.0f, FColor::Green, "Game Saved");
	}
	else
	{
		PrintScreen(true, 5.0f, FColor::Red, "WARNING::GAME FAILED TO SAVE");
	}
}
```

For loading the game, we follow the same approach, but reversed. These functions get called in different locations. For example, in the pause menu, we have the load function that loads the saved data, and in the quit function, we save the data “synchronously” before closing the game.

[PauseMenuUI.cpp - Loading and Saving example](https://github.com/Novigra/3D-PlatformerGame-GraduationProject/blob/main/Source/Grief/Private/UserInterface/PauseMenuUI.cpp)

```cpp
void UPauseMenuUI::Load()
{
	if (PlayerController)
	{
		UUserWidget* Widget = CreateWidget<UUserWidget>(PlayerController, LoadingScreenUI);
		Widget->AddToViewport();

		APlayerGameModeBase* GameMode = Player->GetPlayerGameMode();
		if (GameMode)
		{
			// Load all required data
			GameMode->LoadAllPlayerData();
		}
	}
}

void UPauseMenuUI::Quit()
{
	APlayerGameModeBase* GameMode = Player->GetPlayerGameMode();
	if (GameMode)
	{
		// Saving all data. 0 -> Save synchronously
		GameMode->SaveAllPlayerData(0);
		UKismetSystemLibrary::QuitGame(Player->GetPlayerWorld(), PlayerController, EQuitPreference::Quit, true);
	}
}
```

---

<a name="Conc"></a>
![Conc](https://github.com/user-attachments/assets/e6ffcc99-400a-4ea6-86de-5b9838c37746)

Developing the game was incredibly hard in terms of scope; some functionalities were done early in the development phase, like player movement and input, but some functionalities took months, like UI in terms of code, design, and animations, and the same with the character model. The rest of the game, like the main objectives and world creation, was done in a month and a half, so the fact that the game is playable from start to finish without crashing or reaching deadlocks is a miracle and a huge achievement.

We wanted the game to be more complex, but the time constraint was the big hurdle, not to mention the other responsibilities we had like other college-related projects, assignments, and exams. So even though this isn’t how the final product we wanted to look like, we are happy with the results, and we learned a lot while working on such a behemoth of a game for such a small team. It is truly inspiring how indie developers finish their games.
