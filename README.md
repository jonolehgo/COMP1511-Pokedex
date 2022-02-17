## How to compile and run
gcc -o pokedex main.c pokemon.c pokedex.c
./pokedex

## Usage
\===========================[ Pokédex ]==========================<br>
            Welcome to the Pokédex!  How can I help?<br>
\================================================================<br>


Enter command: ?<br>
  a [pokemon_id] [name] [height] [weight] [type1] [type2]<br>
    Add a Pokemon to the Pokedex<br>
  p<br>
    Print all of the Pokemon in the Pokedex (in the order they were added)<br>
  d<br>
    Display details of the currently selected Pokemon<br>
  ><br>
    Move the cursor to the next Pokemon in the Pokedex<br>
  < <br>
    Move the cursor to the previous Pokemon in the Pokedex<br>
  m [pokemon_id]<br>
    Move the cursor to the Pokemon with the specified pokemon_id<br>
  r<br>
    Remove the current Pokemon from the Pokedex<br>
  x [seed] [factor] [how_many]<br>
    Go exploring for Pokemon<br>
  f<br>
    Set the current Pokemon to be found<br>
  c<br>
    Print out the count of Pokemon who have been found<br>
  t<br>
    Print out the total count of Pokemon in the Pokedex<br>
  e [pokemon_A] [pokemon_B]<br>
    Add an evolution from Pokemon A to Pokemon B<br>
  s<br>
    Show evolutions of the currently selected Pokemon<br>
  q<br>
    Quit<br>
  ?<br>
    Show help<br>
<br>
## Example
Enter command: a 1 Bulbasaur 0.7 6.9 poison grass
Added Bulbasaur to the Pokedex!
