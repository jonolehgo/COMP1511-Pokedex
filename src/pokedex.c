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
#include <assert.h>


// Add any extra #includes your code needs here.
#include <string.h>
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


// Add prototypes for any extra functions you create here.
void add_to_end(Pokedex pokedex, struct pokenode *node);
void hidden_pokemon_name(char *pokemonName);
void remove_evolve_to(Pokedex pokedex, struct pokenode *curr_node,
                                                                int pokemonId);
int type_is_none(const char *pokemonType2);
int evolution_chain_check (struct pokenode *pokenode);
int curr_pokemon_id(Pokedex pokedex);

// You need to implement the following 20 functions.
// In other words, replace the lines calling fprintf & exit with your code.
// You can find descriptions of what each function should do in pokedex.h


Pokedex new_pokedex(void) {
    Pokedex new_pokedex = malloc(sizeof (struct pokedex));
    assert(new_pokedex != NULL);
    // add your own code here
    new_pokedex->head = NULL;
    return new_pokedex;
}


////////////////////////////////////////////////////////////////////////
//                         Stage 1 Functions                          //
////////////////////////////////////////////////////////////////////////

// Fucntion: adds pokemon to pokedex
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
        node->curr_pokemon_selected = TRUE;
        
    // add pokenode to end of list
    } else {
        
        while (curr_node->next != NULL) {
        
            curr_node = curr_node->next;
            
        }
        
        curr_node->next = node;    
        
    }        
                         
                         
                         
}
            
// Function: prints out pokemon detail - id, name, height, weight, type1, type2           
void detail_pokemon(Pokedex pokedex) {
    
    struct pokenode *curr_node = pokedex->head;
    
    // if there is at least one pokemon in the pokedex
    if (curr_node != NULL) {
            
        // loops from list to find selected pokemon/////////////////////////////
        while (curr_node != NULL) {
            
            if (curr_node->curr_pokemon_selected == TRUE) {
                
                break; 
            
            } else {
            
                curr_node = curr_node->next;
                
            }
            
        }
        
        // pokemon detail variables ////////////////////////////////////////////
        // id, name, height, weight
        int pokemonId = pokemon_id(curr_node->pokemon);
        char *pokemonName = pokemon_name(curr_node->pokemon);
        double pokemonHeight = pokemon_height(curr_node->pokemon);
        double pokemonWeight = pokemon_weight(curr_node->pokemon);
        // type 1
        pokemon_type pokemon_Type_1 = pokemon_first_type(curr_node->pokemon);
        const char *pokemonType1 =  pokemon_type_to_string(pokemon_Type_1);
        // type 2
        pokemon_type pokemon_Type_2 = pokemon_second_type(curr_node->pokemon);
        const char *pokemonType2 = pokemon_type_to_string(pokemon_Type_2);    
        ////////////////////////////////////////////////////////////////////////
        
        // if selected pokemon has been found
        if (curr_node->pokemon_found == TRUE) {
        
            printf("Id: %03d\n", pokemonId);
            printf("Name: %s\n", pokemonName);
            printf("Height: %.1lfm\n", pokemonHeight);
            printf("Weight: %.1lfkg\n", pokemonWeight);
            
            // if pokemon has two types
            if (type_is_none(pokemonType2) == FALSE) {
            
                printf("Type: %s %s\n", pokemonType1, pokemonType2);
            
            // if pokemon has only one type   
            } else {
                
                printf("Type: %s \n", pokemonType1);
                
            }
        
        // if selected pokemon has not been found    
        } else {
            
            printf("Id: %03d\n", pokemonId);
            printf("Name: ");
            // prints character name in '*'
            hidden_pokemon_name(pokemonName);
            printf("\n");          
            printf("Height: --\n");
            printf("Weight: --\n");
            printf("Type: --\n");
         
        } 
    
    // if there is no pokemon in the pokedex
    } else {
    
        printf("Pokedex is empty\n");
        
    }



}

// Function: gets current pokemon
Pokemon get_current_pokemon(Pokedex pokedex) {
   
    struct pokenode *curr_node = pokedex->head;
    
    // if there is at least one pokemon in the pokedex
    if (curr_node != NULL) {
    
        while (curr_node != NULL) {
            
            if (curr_node->curr_pokemon_selected == TRUE) {
            
                return curr_node->pokemon;
                
            }      
            
            if (curr_node->next != NULL) {
            
                curr_node = curr_node->next;    
                
            } else {
            
                return NULL;
                
            }
        }
            
    
    } else { 
    
        return NULL;
        
    }
    
    return NULL;
 
 
 
    
}

// Function: tags current pokemon as found allowing for details to be revealed
void find_current_pokemon(Pokedex pokedex) {
    
    struct pokenode *curr_node = pokedex->head;
    
    // if there is at least one pokemon in the pokedex
    if (curr_node != NULL) {
    
        // loops from list to find selected pokemon/////////////////////////////
        while (curr_node != NULL) {
        
            if (curr_node->curr_pokemon_selected == TRUE) {
            
                break; 
                
            } else {
            
                curr_node = curr_node->next;
   
            }
            
        }
        
        // sets pokemon found condition to be true    
        curr_node->pokemon_found = TRUE;
       
    }
    
    
    
}
    
// print all pokemon in the list
void print_pokemon(Pokedex pokedex) {

    struct pokenode *curr_node = pokedex->head;
    
    // if there is at least one pokemon in the pokedex    
    if (curr_node != NULL) {  
          
        // loops from begininning of list to end of list////////////////////////
        while (curr_node != NULL) {
            
            int pokemonId = pokemon_id(curr_node->pokemon);
            char *pokemonName = pokemon_name(curr_node->pokemon);
            
            // print an arrow for selected pokemon
            if (curr_node->curr_pokemon_selected == TRUE) {
            
                printf("--> ");
                
            } else {
            
                printf("    ");
            }
            
            // print pokemon details if pokemon is found
            if (curr_node->pokemon_found == TRUE) {
            
                printf("#%03d: %s", pokemonId, pokemonName); 
            
            // print hidden pokemon name        
            } else {
                
                printf("#%03d: ", pokemonId);
                // print pokemon name in '*'
                hidden_pokemon_name(pokemonName);
                
                    
            }
            
            printf("\n");
            
            // if next pokenode is not the end of the list keep going
            if (curr_node->next != NULL) {
            
                curr_node = curr_node->next;
            
            // otherwise exit loop    
            } else {
            
                break;
                
            }    
            
         
        }  
         
     
    } else {
        printf("Pokedex is empty\n");
    }
        
  
    
}     
    

////////////////////////////////////////////////////////////////////////
//                         Stage 2 Functions                          //
////////////////////////////////////////////////////////////////////////

// Function: makes next pokemon on the list the currently selected pokemon
void next_pokemon(Pokedex pokedex) {

    struct pokenode *curr_node = pokedex->head; 
    
    // loops from list to find selected pokemon/////////////////////////////////   
    while (curr_node != NULL) {
    
        // if pokenode is not current pokemon selected and not at then end of  
        // then continue iterating through list
        if (curr_node->curr_pokemon_selected == FALSE && 
        curr_node->next != NULL) {
            
            if (curr_node->next != NULL) {
                curr_node = curr_node->next;
                
            } else {
            
                break;
            
            }
            
        } else { 
        
            if (curr_node->next != NULL) {
                
                // move current selected pokemon to next pokemon on list   
                curr_node->curr_pokemon_selected = FALSE;
                curr_node->next->curr_pokemon_selected = TRUE;
                
                break;
            
            } else {
            
                break;
            
            }
            
        }
        
    }    
    
    
    
}

// Function : makes previous pokemon on the list the current selected pokemon
void prev_pokemon(Pokedex pokedex) {

    struct pokenode *curr_node = pokedex->head;   
    struct pokenode *temp;
     
    while (curr_node != NULL) {
    
        if (curr_node->curr_pokemon_selected == FALSE) {
           
            temp = curr_node;
            curr_node = curr_node->next;
            curr_node->prev = temp;
        
        } else { 
        
            if (curr_node->prev != NULL) {
            
                curr_node->curr_pokemon_selected = FALSE;
                curr_node->prev->curr_pokemon_selected = TRUE;
                break;
                
            } else {
            
                break;
                
            }
            
        }
        
    }    
  
  
    
}

// Function: takes input as pokemon id and makes that pokemon current selected
//           pokemon
void change_current_pokemon(Pokedex pokedex, int id) {
    
    struct pokenode *curr_node = pokedex->head; 
    
    while (curr_node != NULL) {
     
        int pokemonId = pokemon_id(curr_node->pokemon);
    
        if (curr_node->curr_pokemon_selected == TRUE) {
        
            curr_node->curr_pokemon_selected = FALSE;
            
        }
      
        if (pokemonId == id) {
        
            curr_node->curr_pokemon_selected = TRUE;
            
        }
        
        curr_node = curr_node->next;
              
    }
   
        
   
}
    
// Function: removes current selected pokemon from list
void remove_pokemon(Pokedex pokedex) {

    struct pokenode *curr_node = pokedex->head;  
    struct pokenode *temp = pokedex->head;
   
    // checks and removes elvolve_to data for any pokemon which evolves to 
    // current pokemon that will be deleted  
    int curr_id = curr_pokemon_id(pokedex); 
    remove_evolve_to(pokedex, curr_node, curr_id);
    
                    
    while (curr_node != NULL) {
            
        // if deleting first pokenode
        if (curr_node->curr_pokemon_selected == TRUE && curr_node->next != NULL) {
            
            // next pokemon on list becomes current pokemon selected    
            curr_node->next->curr_pokemon_selected = TRUE;
            
            // steps to remove pokenode 
               
            temp = curr_node->next;
            pokedex->head = temp;
            // function below removes pokemon data in pokenode
            destroy_pokemon(curr_node->pokemon); 
            free(curr_node);
            
            // loop not needed anymore as pokemon found and deleted
            break;
            
        }
            
        // if deleting last and only pokenode /////////////////////////////////
        
        if (curr_node->curr_pokemon_selected == TRUE && 
            curr_node->next == NULL) {
        
            // steps to remove pokenode
            
            // function below frees pokemon data in pokenode
            destroy_pokemon(curr_node->pokemon);     
            free(curr_node);
            pokedex->head = NULL;
            
            // loop not needed anymore as pokemon found and deleted
            break;

        }
            
           
        // if deleting any pokenode besides first //////////////////////////////
        
        // loops until finds the pokenode before the current pokenode
        if (curr_node->next->curr_pokemon_selected == TRUE) {

            // steps to remove pokenode
               
            // creating a temp to store current pokenode
            temp = curr_node->next;
            // linking current pokenode to pokenode after deleted
            curr_node->next = temp->next;
            // function below frees pokemon data in pokenode
            destroy_pokemon(temp->pokemon); 
            // freeing deleted pokenode
            free(temp);
                
            // if the deleted pokenode is the not the last pokenode then the 
            // pokenode afterwards will be the current pokemon, otherwise if the 
            // deleted pokenode is last then the pokenode before it will be the 
            // current
            if (curr_node->next != NULL) {
             
                curr_node->next->curr_pokemon_selected = TRUE;
                       
            } else { 
       
                curr_node->curr_pokemon_selected = TRUE;
                
            }
            
            
            // loop not needed anymore as pokemon found and deleted    
            break;
                
        }
           
        curr_node = curr_node->next;           
      
            
    } 
  
       
   
}

// Function: destroys pokedex and all pokenodes/pokemon within that pokedex.
void destroy_pokedex(Pokedex pokedex) {
    
    struct pokenode *curr_node = pokedex->head;
    struct pokenode *store = pokedex->head;
    
    
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
//           factor output, for an x amount of times, and tags them as found
void go_exploring(Pokedex pokedex, int seed, int factor, int how_many) {
    
    struct pokenode *curr_node = pokedex->head;
    int i = 0;
    // call random generated number function from <time.h>
    srand(seed);
    
    if (curr_node != NULL) {
    
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
        
    } else {
        
        printf("There are no pokemon in your pokedex!\n");
        
        // freeing memory asscoiated with pokedex.
        destroy_pokedex(pokedex);
        
        exit(1);
        
    }
    
    
    
}

// Function: return the total amount of pokemon in pokedex
int count_total_pokemon(Pokedex pokedex) {
    struct pokenode *curr_node = pokedex->head;
    
    int total_pokemon_count = 0;
    
    while (curr_node != NULL) {
        
        int pokemonId = pokemon_id(curr_node->pokemon);
           
        if (pokemonId > 0) {
        
            total_pokemon_count++;
        
        }
        curr_node = curr_node->next;
        
    }
    
    return total_pokemon_count;
    


}

////////////////////////////////////////////////////////////////////////
//                         Stage 4 Functions                          //
////////////////////////////////////////////////////////////////////////

// Function: allows user to input evolution data from pokemon id too another
//           pokemon id
void add_pokemon_evolution(Pokedex pokedex, int from_id, int to_id) {
    
    struct pokenode *curr_node = pokedex->head;
    struct pokenode *temp_from = pokedex->head;
    struct pokenode *temp_to = pokedex->head;
    
    while (curr_node != NULL) {
    
        int pokemonId = pokemon_id(curr_node->pokemon);
        
        if (pokemonId == from_id) {
        
            temp_from = curr_node;
             
        }
        
        if (pokemonId == to_id) {
        
            temp_to = curr_node;
            
            break;
            
        }
        
        curr_node = curr_node->next;
        
    }
    
    
    if (temp_from != NULL && temp_to != NULL) {
    
        temp_from->evolve_to = curr_node;
        
   
    }
    
    
    
}

// Function: Prints out the pokemons evolution chain
void show_evolutions(Pokedex pokedex) {
    
    struct pokenode *curr_node = pokedex->head;
    
    if (curr_node != NULL) {  
             
        while (curr_node != NULL) {
           
            if (curr_node->curr_pokemon_selected == TRUE) {
                
                if (curr_node->evolve_to != NULL) {
                    
                    // pokemon 1 data field ////////////////////////////////////
                    int pokemonId = pokemon_id(curr_node->pokemon);
                    char *pokemonName = pokemon_name(curr_node->pokemon);
                    pokemon_type pokemon_Type_1 = pokemon_first_type
                                                (curr_node->pokemon);
                    const char *pokemonType1 =  pokemon_type_to_string
                                                (pokemon_Type_1);
                    pokemon_type pokemon_Type_2 = pokemon_second_type
                                                (curr_node->pokemon);
                    const char *pokemonType2 = pokemon_type_to_string
                                                (pokemon_Type_2);   
                    ////////////////////////////////////////////////////////////
                    
                    // pokemon 2 data field ////////////////////////////////////
                    int pokemonId2 = pokemon_id(curr_node->evolve_to->pokemon);
                    char *pokemonName2 = pokemon_name
                                        (curr_node->evolve_to->pokemon);
                    pokemon_type pokemon_Type_3 = pokemon_first_type
                                        (curr_node->evolve_to->pokemon);
                    const char *pokemonType3 =  pokemon_type_to_string
                                        (pokemon_Type_3);
                    pokemon_type pokemon_Type_4 = pokemon_second_type
                                        (curr_node->evolve_to->pokemon);
                    const char *pokemonType4 = pokemon_type_to_string
                                        (pokemon_Type_4);    
                    ////////////////////////////////////////////////////////////
                
                    // pokemon 1 
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
                    
                    printf("--> ");
                    
                    // pokemon 2
                    if (curr_node->evolve_to->pokemon_found == TRUE) {
        
                        printf("#%03d %s ", pokemonId2, pokemonName2);
                        
                        // if pokemon has two types, print both types
                        if (type_is_none(pokemonType4) == FALSE) {
            
                            printf("[%s %s] ", pokemonType3, pokemonType4);
                
                        } else {
            
                            printf("[%s] ", pokemonType3);
                
                        }
                        
                    } else {
                    
                        printf("#%03d ???? [????] ", pokemonId2);
                        
                        
                    }
                    
                    
                    // pokemon 3
                    // pokemon 3 data field ////////////////////////////////////
                    if (curr_node->evolve_to->evolve_to != NULL) {
                        int pokemonId3 = pokemon_id
                                    (curr_node->evolve_to->evolve_to->pokemon);
                        char *pokemonName3 = pokemon_name
                                    (curr_node->evolve_to->evolve_to->pokemon);
                        pokemon_type pokemon_Type_5 = pokemon_first_type
                                    (curr_node->evolve_to->evolve_to->pokemon);
                        const char *pokemonType5 =  pokemon_type_to_string
                                    (pokemon_Type_5);
                        pokemon_type pokemon_Type_6 = pokemon_second_type
                                    (curr_node->evolve_to->evolve_to->pokemon);
                        const char *pokemonType6 = pokemon_type_to_string
                                    (pokemon_Type_6);    
                    ////////////////////////////////////////////////////////////
                        
                        printf("--> ");    
                        
                        if (curr_node->evolve_to->evolve_to->
                                                        pokemon_found == TRUE) {
            
                            printf("#%03d %s ", pokemonId3, pokemonName3);
                           
                            // if pokemon has two types, print both types
                            if (type_is_none(pokemonType6) == FALSE) {
                
                                printf("[%s %s] ", pokemonType5, pokemonType6);
                    
                            } else {
                
                                printf("[%s] ", pokemonType5);
                    
                            }
                            
                        } else {
                        
                            printf("#%03d ???? [????] ", pokemonId3);
                            
                            
                        }
                    
                    }
                    
                    // new line for end of pokemon evolution chain for either
                    // two pokemon or threw pokemon
                    printf("\n");
                    
                    
                    break;
                    
                // if pokemon does not evolve to another pokemon id and name
                } else {
                    
                    // current pokemon data field //////////////////////////////
                    int pokemonId = pokemon_id(curr_node->pokemon);
                    char *pokemonName = pokemon_name(curr_node->pokemon);
                    pokemon_type pokemon_Type_1 = pokemon_first_type
                                                (curr_node->pokemon);
                    const char *pokemonType1 =  pokemon_type_to_string
                                                (pokemon_Type_1);
                    pokemon_type pokemon_Type_2 = pokemon_second_type
                                                (curr_node->pokemon);
                    const char *pokemonType2 = pokemon_type_to_string
                                                (pokemon_Type_2);   
                    ////////////////////////////////////////////////////////////
                    
                    // current pokemon
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
                    
                    printf("\n");
                    
                    // printf("this pokemon does not evolve\n"); - test
                    
                    break;
                    
                }
                
                
            }
        
            curr_node = curr_node->next;
        
        }
    
    // if there are no pokemon in pokedex exit program    
    } else {
    
        printf("No pokemon in your pokedex!");
        exit(1);
        
    }
 
 
 
}

// Function: prints the evolution pokemon if current pokemon does evolve
int get_next_evolution(Pokedex pokedex) {

    struct pokenode *curr_node = pokedex->head;
    
    // if there is at least one pokemon in the pokedex
    if (curr_node != NULL) {
            
        // loops from list to find selected pokemon/////////////////////////////
        while (curr_node != NULL) {
            
            if (curr_node->curr_pokemon_selected == TRUE) {
                
                break; 
            
            } else {
            
                curr_node = curr_node->next;
                
            }
            
        }
        
    }
    
    // if current pokemon evolves to something return the evolutions id
    if (curr_node->evolve_to != NULL) {
        
        // function below returns finds ppokemon id 
        int evolve_id = pokemon_id(curr_node->evolve_to->pokemon);
        
        return evolve_id;
    
    // else return does not evolve     
    } else {
    
        return DOES_NOT_EVOLVE;
        
    }
    
    
       
}


////////////////////////////////////////////////////////////////////////
//                         Stage 5 Functions                          //
////////////////////////////////////////////////////////////////////////

// STAGE FIVE IMCOMPLETE *

Pokedex get_pokemon_of_type(Pokedex pokedex, pokemon_type type) {
     
    Pokedex type_pokedex = new_pokedex();
    assert(type_pokedex != NULL);
    return type_pokedex;
    
    /*
    struct pokenode *curr_node = pokedex->head;

    while(curr_node != NULL) {
    
        pokemon_type pokemon_Type_1 = pokemon_first_type(curr_node->pokemon);

        pokemon_type pokemon_Type_2 = pokemon_second_type(curr_node->pokemon);
    
           
        if (pokemon_Type_1 == type || pokemon_Type_2 == type) {
                
            Pokemon cloned_pokemon = clone_pokemon(curr_node->pokemon);
            assert(cloned_pokemon != NULL);
            add_pokemon(type_pokedex, cloned_pokemon);
                
            
            while (curr_type_node != NULL) {
                curr_type_node->pokemon_found = TRUE;
                curr_type_node = curr_type_node->next;
            }

          
        
            curr_type_node = type_pokedex->head;
            while (curr_type_node != NULL) {
                curr_type_node->evolve_to = NULL;
                curr_type_node = curr_type_node->next;
            }

                      
                
        }
            
        if (curr_node->next != NULL) {
            
            curr_node = curr_node->next;
            
        } else {
          
            break;
            
        }
   
   
    }
    
    //return type_pokedex;
    */

}



Pokedex get_found_pokemon(Pokedex pokedex) {
// comment: *still in progress* functioning however have not implements the 
// ascending order details correctly

    Pokedex found_pokedex = new_pokedex();
    assert(found_pokedex != NULL);
    
    struct pokenode *curr_node = pokedex->head;
    
    while(curr_node != NULL) {
    
        if (curr_node->pokemon_found == TRUE) {
                
            Pokemon cloned_pokemon = clone_pokemon(curr_node->pokemon);
            assert(cloned_pokemon != NULL);
            add_pokemon(found_pokedex, cloned_pokemon);
                
            struct pokenode *curr_found_node = found_pokedex->head;
            while (curr_found_node != NULL) {
                curr_found_node->pokemon_found = TRUE;
                curr_found_node->evolve_to = NULL;
                curr_found_node = curr_found_node->next;
            }
            
         
         /* ascending order detail ///////////////////////////
         // trying to get found_pokedex into ascening order //
         
            curr_found_node = found_pokedex->head;
            
            while (curr_found_node != NULL) {
            
           
                int pokemonId = pokemon_id(curr_node->pokemon);
                
                if (curr_found_node->next != NULL) {
                
                    int pokemonIdNext = pokemon_id(curr_node->next->pokemon);
                    
                    if (pokemonId > pokemonIdNext) {
                    
                        struct pokenode *temp = found_pokedex->head;
                        
                        temp = curr_found_node->next;
                        curr_found_node->next = curr_found_node;
                        curr_found_node = temp;
                        //free(temp);
                        printf("here\n");
                        
                    } else {
                    
                        break;
                        
                    }
                           
                    curr_found_node = curr_found_node->next;
                        
                } else {
                
                    break;
                    
                }   
            
                
            }
            
            *////////////////////////////////////////////////////   
                
        }
         
            
        if (curr_node->next != NULL) {
            
            curr_node = curr_node->next;
            
        } else {
          
            break;
            
        }
   
   
    }
    
    return found_pokedex;
    

}

Pokedex search_pokemon(Pokedex pokedex, char *text) {
    fprintf(stderr, "exiting as STAGE 5 search_pokemon not completed\n");
    exit(1);
    
    
    
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

// Function: iterates though pokedex and if there is a pokemon that evolves to
//           input parameter pokemonId, remove that info.
void remove_evolve_to(Pokedex pokedex, struct pokenode *curr_node, 
                                                        int pokemonId) {

    struct pokenode *counter_node = pokedex->head;
    
    while (counter_node != NULL) {
        
        if (counter_node->evolve_to != NULL) {
    
            int counter_pokemonId = pokemon_id
                (counter_node->evolve_to->pokemon);
        
            if (counter_pokemonId == pokemonId) {
            
                counter_node->evolve_to = NULL;
                // printf("counter_node->evolve_to now equals NULL\n"); - test
                
            }
             
        }    
    
        counter_node = counter_node->next;
        
    }
    
    
    
}

// Function: returns the id of the current selected pokemon
int curr_pokemon_id(Pokedex pokedex) {
    
    
    struct pokenode *curr_node = pokedex->head;
    
    while (curr_node != NULL) {
    
        int pokemonId = pokemon_id(curr_node->pokemon);
    
        if (curr_node->curr_pokemon_selected == TRUE) {
        
            return pokemonId;
        }
        
        curr_node = curr_node->next;
        
    }
    
    return 0;
    
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
