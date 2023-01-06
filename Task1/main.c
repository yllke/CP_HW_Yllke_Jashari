#include <stdio.h>
#include <stdbool.h>

//we can leave this as a constant
#define MIN_FLOOR 0


// function that prints the options for the user to choose. It also shows the current floor
void print_option_list(int current_floor) {
    printf("\nYou're currently on floor: %d\n", current_floor);
    printf("\n");
    printf("Menu:\n");
    printf("  [G] Ground floor (0) \n");
    printf("  [1] 1st floor\n");
    printf("  [2] 2nd floor\n");
    printf("  [3] 3rd floor\n");
    printf("  [4] 4th floor\n");
    printf("  [5] 5th floor\n");
    printf("  [A] Alight\n");
}


// function that gets the new floor the user wants to go to

int get_new_floor(int current_floor) {
    char new_floor[2]; // declare new_floor as a string with length of 2
    do {
        printf("\nEnter the floor you want to go to: ");
        scanf("%s", new_floor); // read a string into new_floor

        printf("\n");
        //if statement to validate the input of the user
        if (new_floor[0] == 'A' && new_floor[1] == '\0') {
            printf("Bye!"); //inputting "A" ends the program
            return -1;
        } else if (new_floor[0] == 'G' && new_floor[1] == '\0') {
            return MIN_FLOOR; //ground floor = 0
        } else if (new_floor[0] >= '1' && new_floor[0] <= '5' && new_floor[1] == '\0') {
            return new_floor[0] - '0'; //if new_floor is between 1-5 then we do decimal number of that character(from ASCII table)
                                       // minus 49, which is the decimal number of '0' in the ascii table
        } else {
            printf("Invalid input. Please enter a valid floor.\n([G]round floor, 1, 2, 3, 4, 5, [A]light)\n");
        }
    } while (true);
}


// function of movement of the elevator from the current floor to the new floor
void moving_elevator(int current_floor, int new_floor) {
    if (new_floor > current_floor) {
        printf("Going up...\n");
        for (int i = current_floor + 1; i <= new_floor; i++) {
            printf("%d...\n", i);
        }

    } else if (new_floor < current_floor) {
        printf("Going down...\n");
        for (int i = current_floor - 1; i >= new_floor; i--) {
            printf("%d...\n", i);
        }
    }
    current_floor = new_floor;
}

int main(void) {
    printf("Welcome!\n");

    int current_floor = MIN_FLOOR; //we start from floor 0, aka ground floor

    while (true) {
        print_option_list(current_floor);//print the list and current floor

        int new_floor = get_new_floor(current_floor); //we get the new floor from the user
        if (new_floor == -1) {
            break; //we finish if new_floor is -1, which means that the user lastly inputted "A"
        }
        moving_elevator(current_floor, new_floor); //the motion of the elevator moving from current floor to new floor is printed
        current_floor = new_floor; //we save the new floor as the current floor until the next move
    }
    return 0;
}