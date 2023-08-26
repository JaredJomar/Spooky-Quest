# Project_06
# Spooky Quest Game Project 

## Objective

The objective of the "Spooky Quest Game Project" for the CIIC4010/ICOM4015 course is to enhance the Spooky Quest game by adding new features and functionality. The base game has two areas and two types of enemies, and your task is to add new elements to it. The game involves player movement, battling enemies in a Rock, Paper, Scissors style, and progressing through different areas.

## Project Overview

In this project, you will work on Spooky Quest, a text-based game with areas, enemies, and player interactions. The project is divided into three phases, each introducing new specifications and features with increasing complexity.

## General Instructions

- You will work in teams of two students.
- Personal repositories will not be graded.
- One partner will create the team repository, and the other will join it using their GitHub credentials.
- Team members should include their names and emails in the README.md file.
- Each partner should commit their contributions using their individual GitHub credentials.
- Collaboration and professionalism are essential throughout the project.
- If you encounter any issues or problems with your partner, follow the outlined steps to resolve them.

## Phase 1 (Suggested Deadline: October 21)

**Specifications:**

- **Walking Patterns**: Change the walking patterns of the enemies from a square to a triangular path. The orientation of the triangle does not matter.
- **Pause State**: Create a Pause State for the game. Pressing the 'ESC' key will trigger this pause state, and pressing it again will exit it. The pause state should only be accessible from the Battle State or the Overworld State.
- **Heads-Up Display (HUD)**: Display the Area name, Player health, and current living Enemies in the Overworld State only.
- **DEBUG Keys**: Pressing 'h' will reset the Player's health to full, and pressing 'r' will respawn all defeated enemies in the Overworld.

## Phase 2 (Suggested Deadline: October 31)

**Specifications:**

- **New Area**: Create a new area that comes after Area 1 and before Area 2. This area should have an overworld effect on the player, either slowly draining or restoring the player's health over time. It should also contain enemies, and winning the final battle will take the player to Area 2.
- **Create Immovable Entities**: Using the refactored Entity class, add instances of immovable entities to the map. These entities should not move or be interactable, but the player should not be able to move through them when they collide with them. Examples of immovable entities could be trees or buildings.

## Phase 3 (Suggested Deadline: November 11)

**Specifications:**

- **Friend Entity**: Implement a Friend class that inherits from the Entity class. Players can interact with a Friend by pressing the 'e' key when colliding with them. Interactions should display speech from the Friend on the screen or provide another indicator of interaction. The displayed text should disappear after a fixed amount of time or when any key is pressed. Friends should move in a pattern like Enemies but should not have health or base damage. Include at least one instance of a Friend in the game.
- **Boss Entity**: Implement a Boss class that inherits from the Enemy class. Bosses appear in an Area after all other Enemies in that area are defeated. A Boss Battle should have at least two phases, requiring the player to deplete the Boss's health bar twice to defeat them. Defeating a Boss should move the player to the next Area or a Win State if there are no remaining Areas. Include at least one Boss instance per Area of the game.
- **Spawn Boss**: Pressing the 'b' key should spawn the boss in the area, regardless of how many enemies are left. Beating the boss should also take the player to the next area, independent of remaining enemies.
