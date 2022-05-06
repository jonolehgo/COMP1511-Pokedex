<p align="center">
  <a href="https://example.com/">
    <img src="https://static.wikia.nocookie.net/pokemontheherosrise/images/b/b7/Pok%C3%A9dex-logo.png/revision/latest?cb=20200820224717" alt="Logo" width=72 height=72>
  </a>

  <h3 align="center">A Pokedex in C</h3>

  <p align="center">
    <br>
    <a href="https://reponame/issues/new?template=bug.md">Report bug</a>
    ·
    <a href="https://reponame/issues/new?template=feature.md&labels=feature">Request feature</a>
  </p>
</p>


## Table of contents

- [How to compile & run](#how-to-compile-&-run)
- [Status](#status)
- [Stages](#stages)
- [Creators](#creators)
- [Thanks](#thanks)
- [Usage](#usage)


## How to compile & run

Compile program: gcc -o pokedex main.c pokemon.c pokedex.c -l winmm <br/>
Run program: ./pokedex

Note: Compiling with '-l winmm' uses windows dynamic link library to enable BGM music whilst application is running.

## Status

Pokedex stages 5/5 completed.

## Stages

```
Stage1/
  ├── (a) Add a pokemon 
  ├── (g) Get currently selected pokemon
  ├── (d) Display details of selected pokemon
  ├── (f) Set currently selected pokemon as found 
  └── (p) Print all pokemon in pokedex
Stage2/
  ├── (>) Move cursor to next pokemon on right
  ├── (<) Move cursor to previous pokemon on left
  ├── (m) Move cursor via input pokemon id
  ├── (r) Remove current pokemon from list
  └── (<) Move cursor to previous pokemon on left
Stage3/
  ├── (x) Explore for new pokemon
  └── (c) Find the total amount of pokemon
Stage4/
  ├── (e) Add evolution details of a pokemon
  ├── (s) Show evolution details of a currently selected pokemon
  └── (n) Show evolution details of a next selected pokemon
Stage5/
  ├── (T) Create a new pokedex containing only pokemon of a specific Type
  ├── (F) Create a new pokedex containing only pokemon which has been found
  └── (S) Create a new pokedex containig only pokemon from a search query
```

## Creators

**Jonathan Tea**

- <https://github.com/jonolehgo>

## Thanks

COMP1511 Project in asscociation with The University of New South Wales.

## Usage
```
===========================[ Pokédex ]========================
            Welcome to the Pokédex!  How can I help?
==============================================================

Enter command: ?
  
  a [pokemon_id] [name] [height] [weight] [type1] [type2]
    Add a Pokemon to the Pokedex
  p
    Print all of the Pokemon in the Pokedex (in the order they were added)
  d
    Display details of the currently selected Pokemon
  >
    Move the cursor to the next Pokemon in the Pokedex
  < 
    Move the cursor to the previous Pokemon in the Pokedex
  m [pokemon_id]
    Move the cursor to the Pokemon with the specified pokemon_id
  r
    Remove the current Pokemon from the Pokedex
  x [seed] [factor] [how_many]
    Go exploring for Pokemon
  f
    Set the current Pokemon to be found
  c
    Print out the count of Pokemon who have been found
  t
    Print out the total count of Pokemon in the Pokedex
  e [pokemon_A] [pokemon_B]
    Add an evolution from Pokemon A to Pokemon B
  s
    Show evolutions of the currently selected Pokemon
  n
    Show next evolution of current selected Pokemon
  F
     Create a new Pokedex containing Pokemon that have previously been found
  S [string]
     Create a new Pokedex containing Pokemon that have the specified string in their name
  T [type]
     Create a new Pokedex containing Pokemon that have the specified type
  q
    Quit
  ?
    Show help
``` 
**Example 1: Adding Pokemon** <br/>
Input:
```
a 1 Bulbasaur 0.7 6.9 poison grass
```
Output:
```
Added Bulbasaur to the Pokedex!
```

**Example 2: Printing Pokedex** <br/>
Input:
```
p
```
Output:
```
--> #001: *********
```

