## How to compile and run
gcc -o pokedex main.c pokemon.c pokedex.c
./pokedex

## Usage
\===========================[ Pokédex ]==========================<br>
            Welcome to the Pokédex!  How can I help?<br>
\================================================================


Enter command: ?<br>
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
  q
    Quit
  ?
    Show help

## Example
Enter command: a 1 Bulbasaur 0.7 6.9 poison grass
Added Bulbasaur to the Pokedex!
