// Assignment 2 19T1 COMP1511: Pokedex
// pokedex.c
//
// This program was written by Jonathan Tea (z5146699)
// on 01-05-2019
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: Minor clarifications about `struct pokenode`.
// Version 1.1.0: Moved destroy_pokedex function to correct location.
// Version 1.1.1: Renamed "pokemon_id" to "id" in change_current_pokemon.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


// Add any extra #includes your code needs here.
// But note you are not permitted to use functions from string.h
// so do not #include <string.h>

#include "pokedex.h"

// Add your own #defines here.
#define TRUE 1
#define FALSE 0

// Note you are not permitted to use arrays in struct pokedex,
// you must use a linked list.
//
// You are also not permitted to use arrays in any of the functions
// below.
//
// The only exception is that char arrays are permitted for
// search_pokemon and functions it may call, as well as the string
// returned by pokemon_name (from pokemon.h).
//
// You will need to add fields to struct pokedex.
// You may change or delete the head field.

struct pokedex {
    struct pokenode *head;
    struct pokenode *tail;

};


// You don't have to use the provided struct pokenode, you are free to
// make your own struct instead.
// If you use the provided struct pokenode, you will need to add fields
// to it to store other information.

struct pokenode {
    struct pokenode *next;
    struct pokenode *prev;
    struct pokenode *evolve_to;
    Pokemon         pokemon;
    int             pokemon_found;
    int             curr_pokemon_selected;
    
 
};

// Add any other structs you define here.
struct pokenode *new_pokenode(Pokemon pokemon);
// Return the pokenode with currently selected pokemon.
struct pokenode *get_current_pokenode(Pokedex pokedex);


// Add prototypes for any extra functions you create here.
void add_to_end(Pokedex pokedex, struct pokenode *node);
void hidden_pokemon_name(char *pokemonName);
void set_all_found(Pokedex pokedex);
void bubble_sort(Pokedex pokedex);
int type_is_none(const char *pokemonType2);
bool string_match(char *name, char *text);

// You need to implement the following 20 functions.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h


Pokedex new_pokedex(void) {
    Pokedex new_pokedex = malloc(sizeof (struct pokedex));
    assert(new_pokedex != NULL);
    // add your own code here
    new_pokedex->head = NULL;
    new_pokedex->tail = NULL;
    return new_pokedex;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Fucntion: adds a pokemon to pokedex
void add_pokemon(Pokedex pokedex, Pokemon pokemon) {
    struct pokenode *pokenode = new_pokenode(pokemon);
    add_to_end(pokedex, pokenode);
}

// Function: create and malloc node for new pokemon
struct pokenode *new_pokenode(Pokemon pokemon) {
    struct pokenode *pokenode;
    pokenode = malloc(sizeof(struct pokenode));
    pokenode->next = NULL;
    pokenode->prev = NULL;
    pokenode->evolve_to = NULL;
    pokenode->pokemon = pokemon;  
    pokenode->pokemon_found = FALSE;
    pokenode->curr_pokemon_selected = FALSE;
    return pokenode;
}

// Function: adds pokemon node to end of pokedex list
void add_to_end(Pokedex pokedex, struct pokenode *node) {  
    struct pokenode *curr_node = pokedex->head;
    // if there are no pokemon, then pokenode added will become the new head
    if (pokedex->head == NULL) {
        pokedex->head = node;
        pokedex->tail = node;
        node->curr_pokemon_selected = TRUE;
    
    // if there is only one pokemon, assign new nodes prev to pokedex head
    } else if (curr_node == pokedex->tail) {
      node->prev = curr_node;
      curr_node->next = node;
      pokedex->tail = node;
    
    // find last pokemon and add pokenode to end of list
    } else {
        while (curr_node->next != NULL) {
            curr_node = curr_node->next;
        }
        node->prev = curr_node;
        curr_node->next = node;
        pokedex->tail = node;
    }           
}

// Function: returns the pokenode with the current selected pokemon
struct pokenode *get_current_pokenode(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    // if there are no pokemon in the pokedex
    if (curr_node == NULL) {
        return NULL;
    }        
    // find the selected pokemon node
    while (curr_node != NULL) {
        if (curr_node->curr_pokemon_selected == TRUE) {
            return curr_node;
        } else {
            curr_node = curr_node->next;
        }
    }  
}

// Function: returns the selected pokemon
Pokemon get_current_pokemon(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    if (curr_node == NULL) {
        return NULL;
    } else {
        while (curr_node != NULL) {
            if (curr_node->curr_pokemon_selected == TRUE) {
                return curr_node->pokemon;
            } else {
                curr_node = curr_node->next;
            }
        }
    }   
}

// Function: prints out pokemon details of the selected pokemon        
void detail_pokemon(Pokedex pokedex) {
    // if there are no pokemon in the pokedex
    if (pokedex->head == NULL) {
        printf("Pokedex is empty\n");
        return;
    }
    struct pokenode *curr_node = get_current_pokenode(pokedex);
    // pokemon details    
    int pokemonId = pokemon_id(curr_node->pokemon);
    char *pokemonName = pokemon_name(curr_node->pokemon);
    double pokemonHeight = pokemon_height(curr_node->pokemon);
    double pokemonWeight = pokemon_weight(curr_node->pokemon);
    pokemon_type pokemon_Type_1 = pokemon_first_type(curr_node->pokemon);
    const char *pokemonType1 =  pokemon_type_to_string(pokemon_Type_1);
    pokemon_type pokemon_Type_2 = pokemon_second_type(curr_node->pokemon);
    const char *pokemonType2 = pokemon_type_to_string(pokemon_Type_2);    
        
    // if selected pokemon has been 'found' print details
    if (curr_node->pokemon_found == TRUE) {
        printf("Id: %03d\n", pokemonId);
        printf("Name: %s\n", pokemonName);
        printf("Height: %.1lfm\n", pokemonHeight);
        printf("Weight: %.1lfkg\n", pokemonWeight);
        // pokemon has two types
        if (type_is_none(pokemonType2) == FALSE) {
            printf("Type: %s %s\n", pokemonType1, pokemonType2);
        // pokemon has only one type   
        } else {
            printf("Type: %s \n", pokemonType1);
        }
    
    // if selected pokemon has not been 'found' print hidden details version 
    } else {
        printf("Id: %03d\n", pokemonId);
        printf("Name: ");
        hidden_pokemon_name(pokemonName); // this function will replace the pokemon's name with '*''s
        printf("\n");          
        printf("Height: --\n");
        printf("Weight: --\n");
        printf("Type: --\n");
    } 
}

// Function: tags current pokemon as 'found' allowing for details to be revealed
void find_current_pokemon(Pokedex pokedex) {
    if (pokedex->head == NULL) {
        printf("Pokedex is empty\n");
    } else {
        struct pokenode *curr_node = get_current_pokenode(pokedex);
        curr_node->pokemon_found = TRUE;
    }
}
    
// Function: prints all of the pokemon
void print_pokemon(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    // pokedex is empty
    if (curr_node == NULL) {  
        printf("Pokedex is empty\n");
        return;
    }    
    // iterate through pokedex      
    while (curr_node != NULL) {
        int pokemonId = pokemon_id(curr_node->pokemon);
        char *pokemonName = pokemon_name(curr_node->pokemon);
        // print an arrow for 'selected' pokemon
        if (curr_node->curr_pokemon_selected == TRUE) {
            printf("--> ");
        } else {
            printf("    ");
        }
        // reveal pokemon details if pokemon is 'found'
        if (curr_node->pokemon_found == TRUE) {
            printf("#%03d: %s", pokemonId, pokemonName); 
        // print the hidden version of the pokemon        
        } else {
            printf("#%03d: ", pokemonId);
            hidden_pokemon_name(pokemonName);    
        }
        printf("\n");
        // continue printing other pokenodes
        if (curr_node->next != NULL) {
            curr_node = curr_node->next;
        } else {
            return;            
        }        
    }  
}     

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Function: makes next pokemon on the list the currently selected pokemon
void next_pokemon(Pokedex pokedex) {
    if (pokedex->head == NULL) { return; }
    struct pokenode *curr_node = get_current_pokenode(pokedex);
    if (curr_node->next != NULL) {
        curr_node->curr_pokemon_selected = FALSE;
        curr_node->next->curr_pokemon_selected = TRUE;
    }
}

// Function : makes previous pokemon on the list the currently selected pokemon
void prev_pokemon(Pokedex pokedex) {
    if (pokedex->head == NULL) { return; }
    struct pokenode *curr_node = get_current_pokenode(pokedex);
    if (curr_node->prev != NULL) {
        curr_node->curr_pokemon_selected = FALSE;
        curr_node->prev->curr_pokemon_selected = TRUE;
    }
}

// Function: takes input as pokemon id and makes that pokemon current selected
//           pokemon
void change_current_pokemon(Pokedex pokedex, int id) {
    if (pokedex->head == NULL) { return; }
    struct pokenode *curr_node = pokedex->head;
    struct pokenode *prev_pokemon_selected = get_current_pokenode(pokedex);    
    while (curr_node != NULL) {
        int pokemonId = pokemon_id(curr_node->pokemon);  
        if (pokemonId == id) {
            // swap states if pokemon id exists
            curr_node->curr_pokemon_selected = TRUE;
            prev_pokemon_selected->curr_pokemon_selected = FALSE;
        }
        curr_node = curr_node->next;
    }
}
    
// Function: removes current selected pokemon from list
void remove_pokemon(Pokedex pokedex) {
    if (pokedex->head == NULL) { return; }
    struct pokenode *curr_node = get_current_pokenode(pokedex);  
    struct pokenode *curr_node_prev = curr_node->prev;
    struct pokenode *curr_node_next = curr_node->next;

    // if deleting the only pokemon in pokedex
    if (curr_node == pokedex->head && curr_node == pokedex->tail) {
        pokedex->head = NULL;
        pokedex->tail = NULL;
    // if deleting first pokemon in pokedex
    } else if (curr_node == pokedex->head && curr_node != pokedex->tail) {
        pokedex->head = curr_node_next;
        curr_node_next->prev = NULL;
        curr_node_next->curr_pokemon_selected = TRUE;
    // if deleting last pokemon in pokedex
    } else if (curr_node == pokedex->tail) {
        pokedex->tail = curr_node_prev;
        curr_node_prev->curr_pokemon_selected = TRUE;
        curr_node_prev->next = NULL;
    // if deleting within middle of list
    } else if (curr_node != pokedex->head && curr_node != pokedex->tail) {
        curr_node_prev->next = curr_node_next;
        curr_node_next->prev = curr_node_prev;
        curr_node_next->curr_pokemon_selected = TRUE;
    }
        destroy_pokemon(curr_node->pokemon);
        free(curr_node);   
}

// Function: destroys pokedex and all pokenodes/pokemon within that pokedex.
void destroy_pokedex(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    struct pokenode *store;
    while (curr_node != NULL) {    
        destroy_pokemon(curr_node->pokemon);            
        store = curr_node->next;
        free(curr_node);
        curr_node = store;        
    }
    free(pokedex);
}


////////////////////////////////////////////////////////////////////////
//                         Stage 3 Functions                          //
////////////////////////////////////////////////////////////////////////

// Function: allows user to randomly discover hidden pokemon according to the
//           seed is for random number generator 
//           factor output (highest pokemon ID to search for by 'factor - 1' inclusive)
//           for an x amount of times
//           tags pokemon with generated ID as found
void go_exploring(Pokedex pokedex, int seed, int factor, int how_many) {
    struct pokenode *curr_node = pokedex->head;
    if (curr_node == NULL) {
        printf("Pokedex is empty\n");
        return;
    }
    srand(seed);
    int i = 0;
    while (i < how_many) {
        int number_generated = rand() % factor;
        while (curr_node != NULL) {
            int pokemonId = pokemon_id(curr_node->pokemon);
            if (number_generated == pokemonId) {
                curr_node->pokemon_found = TRUE;
            }
            curr_node = curr_node->next;
        }
        curr_node = pokedex->head;
        i++;
    }
}

// Function: return the total amount of pokemon in pokedex
int count_total_pokemon(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    int total_pokemon_count = 0;
    while (curr_node != NULL) {
        total_pokemon_count++;
        curr_node = curr_node->next;
    }
    return total_pokemon_count;
}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Function: allows user to input evolution data with from id and to id
void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    struct pokenode *curr_node = pokedex->head;
    struct pokenode *evolve_from;
    struct pokenode *evolve_to;
    if (curr_node == NULL) {
        printf("Pokedex is empty\n");
        return;
    }
    while (curr_node != NULL) {
        int pokemonId = pokemon_id(curr_node->pokemon);
        if (pokemonId == from_id) {
            evolve_from = curr_node;     
        }
        if (pokemonId == to_id) {
            evolve_to = curr_node;
        }
        curr_node = curr_node->next;
    }
    if (evolve_from != NULL && evolve_to != NULL) {
        evolve_from->evolve_to = evolve_to;
    }   
}

// Function: Prints out the pokemons evolution chain
void show_evolutions(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    if (curr_node == NULL) {
        printf("Pokedex is empty\n");
        return;
    }
    curr_node = get_current_pokenode(pokedex);
    if (curr_node->evolve_to != NULL) {
        while (curr_node != NULL) {
            int pokemonId = pokemon_id(curr_node->pokemon);
            char *pokemonName = pokemon_name(curr_node->pokemon);
            pokemon_type pokemon_Type_1 = pokemon_first_type(curr_node->pokemon);
            const char *pokemonType1 =  pokemon_type_to_string(pokemon_Type_1);
            pokemon_type pokemon_Type_2 = pokemon_second_type(curr_node->pokemon);
            const char *pokemonType2 = pokemon_type_to_string(pokemon_Type_2);
            
            if (curr_node->pokemon_found == TRUE) {
                printf("#%03d %s ", pokemonId, pokemonName);            
                // if pokemon has two types, print both types   
                if (type_is_none(pokemonType2) == FALSE) {
                    printf("[%s %s] ", pokemonType1, pokemonType2);
                } else {
                    printf("[%s] ", pokemonType1);
                }
            } else {
                printf("#%03d ???? [????] ", pokemonId);
            }
            // if pokemon has an evolution to then print '-->'
            if (curr_node->evolve_to != NULL) {
                printf("--> ");
            // if not more evolutions on chain print new line    
            } else {
                printf("\n");
            }
            curr_node = curr_node->evolve_to;
        }
    }
}

// Function: prints the evolution pokemon if current pokemon does evolve
int get_next_evolution(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    if (curr_node == NULL) {
        printf("Pokedex is empty\n");
        exit(1);
    }    
    curr_node = get_current_pokenode(pokedex);
    // if current pokemon evolves to something return the evolutions id
    if (curr_node->evolve_to != NULL) {
        int evolve_to_id = pokemon_id(curr_node->evolve_to->pokemon);
        return evolve_to_id;
    } else {    
        return DOES_NOT_EVOLVE;
    }
}

////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// Function: Copy all the found pokemon with given type to a new pokedex
Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
    struct pokenode *curr_node = pokedex->head;
    Pokedex type_pokedex = new_pokedex();
    while(curr_node != NULL) {
        if (curr_node->pokemon_found == TRUE) {
            pokemon_type pokemon_type_1 = pokemon_first_type(curr_node->pokemon);
            pokemon_type pokemon_type_2 = pokemon_second_type(curr_node->pokemon);
            if (pokemon_type_1 == type || pokemon_type_2 == type) {
                Pokemon pokemon_copy = clone_pokemon(curr_node->pokemon);
                add_pokemon(type_pokedex, pokemon_copy);
            }
        }
        curr_node = curr_node->next;
    }
    set_all_found(type_pokedex);
    return type_pokedex;

}

// Function: Copy all the found pokemon to a new pokedex and sorts them by pokemon ID
Pokedex get_found_pokemon(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    Pokedex found_pokedex = new_pokedex();
    while(curr_node != NULL) {
        if (curr_node->pokemon_found == TRUE) {
                Pokemon pokemon_copy = clone_pokemon(curr_node->pokemon);
                add_pokemon(found_pokedex, pokemon_copy);
        }
        curr_node = curr_node->next;
    }
    set_all_found(found_pokedex);
    bubble_sort(found_pokedex);
    return found_pokedex;
}

Pokedex search_pokemon(Pokedex pokedex, char *text) {
    struct pokenode *curr_node = pokedex->head;
    Pokedex search_pokedex = new_pokedex();
    while(curr_node != NULL) {
        char *name = pokemon_name(curr_node->pokemon);
        if (curr_node->pokemon_found == TRUE && string_match(name, text)) {
            Pokemon pokemon_copy = clone_pokemon(curr_node->pokemon);
            add_pokemon(search_pokedex, pokemon_copy);
        }
        curr_node = curr_node->next;
    }
    set_all_found(search_pokedex);
    return search_pokedex;
}

////////////////////////////////////////////////////////////////////////
//                       ADDITIONAL FUNCTIONS                         //        
////////////////////////////////////////////////////////////////////////

// Function: finds length of string and prints '*' according to string length
void hidden_pokemon_name(char *pokemonName) {
    int pokemon_name_length = 0;     
    while (pokemonName[pokemon_name_length] != '\0') {
        pokemon_name_length++;
    }
    for (int i = 0; i < pokemon_name_length; i++) {
        printf("*");
    }
}

// Function: checks if type is none and returns true or false
int type_is_none(const char *pokemonType2) {
    if (pokemonType2[0] == 'N' &&
        pokemonType2[1] == 'o' &&
        pokemonType2[2] == 'n' &&
        pokemonType2[3] == 'e') {
        return TRUE;
    }
    return FALSE;
}

// Function: sets all pokemon in a given pokedex to found
void set_all_found(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    while(curr_node != NULL) {
        curr_node->pokemon_found = TRUE;
        curr_node = curr_node->next;
    }
}

// Function: sort pokedex list in ascending order via bubble sort
void bubble_sort(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    if (curr_node == NULL) {
        return;
    }
    // if there is one pokemon to swap
    if (curr_node->next == NULL) {
        return;
    }

    // if there are more than one pokemons to swap
    // sort pokedex by id using bubblesort
    int curr_id;
    int next_id;
    int i = 0;
    while(i < count_total_pokemon(pokedex)) {
        while(curr_node->next != NULL) {
            curr_id = pokemon_id(curr_node->pokemon);
            next_id = pokemon_id(curr_node->next->pokemon);

            if (curr_id > next_id) {
                // swap pokemon
                Pokemon swap_pokemon = curr_node->next->pokemon;
                curr_node->next->pokemon = curr_node->pokemon;
                curr_node->pokemon = swap_pokemon;
            }
            curr_node = curr_node->next;

        }
        i++;
        curr_node = pokedex->head;
    }
}

// Function: return the amount of found pokemon in pokedex
int count_found_pokemon(Pokedex pokedex) { 
    struct pokenode *curr_node = pokedex->head;
    int found_pokemon_count = 0;
    while (curr_node != NULL) {
        if (curr_node->pokemon_found == TRUE) {
            found_pokemon_count++;
        }
        curr_node = curr_node->next;
    }
    return found_pokemon_count;
}

// Function: checks if a string is within a pokemons name
bool string_match(char *name, char *text) {
    int text_length = 0; 
    int name_length = 0;    
    while (text[text_length] != '\0') {
        text_length++;
    }
    while (name[name_length] != '\0') {
        name_length++;
    }
    if (text_length > name_length) {
        return FALSE;
    }
    int i = 0;
    int x = 0;
    char n_ch;
    char t_ch;
    while (i < name_length) {
        n_ch = name[i];
        t_ch = text[x];
        // convert to lowercase
        if (t_ch >= 'A' && t_ch <= 'Z') {t_ch = t_ch + 32;}
        if (n_ch >= 'A' && n_ch <= 'Z') {n_ch = n_ch + 32;}

        if (t_ch == n_ch) {
            x++;
        } else {
            x = 0;
        }
        if (x == text_length) {
            return TRUE;
        }
        i++;
    }
    return FALSE;
}