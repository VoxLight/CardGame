## COP2220 Spring 2023 Final Project
by Samuel Lovitt

## Card Attributes
Each card has the following attributes:
- ### Name
    Unique identifier to distinguish between different cards.

- ### Pip Cost
    Cost to play a card, ranging from 0 to 3 pips.

- ### Attack
    Value used to calculate damage during the [battle phase](#battle-phase).

- ### Defense
    Value used to determine card survival upon receiving damage. A card is destroyed if attacked by a card with a higher attack value.

## Player Attributes
Each player has the following attributes:

- ### Name
    Identifier for the player. Unique names are recommended for clarity.

- ### Player Pips
    Resource used to summon cards, with a maximum of 3 pips. Refreshed during the [draw phase](#draw-phase).

- ### Health Points
    Determines player survival. The last player with HP > 0 wins. Lose HP when targeted by attacking monsters.

- ### Deck
    Collection of [cards](#card-attributes) owned by the player.

- ### Hand
    Collection of [cards](#card-attributes) held by the player.

## Phases

- ### Draw Phase
    Player turn changes. The previous player exits their attack phase, and the next player enters the draw phase, drawing a card from their [deck](#deck).

- ### Main Phase
    Players can play cards by expending pips equal to the combined cost of all cards played. Players can't summon a card if its pip cost exceeds their remaining pips.

- ### Battle Phase
    Players finalize summons and spend pips. They can target one card or player per summoned monster on their field. Multiple monsters can target a single card or player, but each monster can only target one entity at a time.
