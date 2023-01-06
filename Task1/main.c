#include <stdio.h>
#include <stdbool.h>

//we can leave this as a constant
#define MIN_FLOOR 0


// function that prints the options for the user to choose. It also shows the current floor
void print_option_list(int current_floor, int num_passengers) {
    printf("\nYou're currently on floor: %d\n", current_floor);
    printf("Number of passengers: %d\n", num_passengers);
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

int get_new_floor() {
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
        printf("\nGoing up...\n");
        for (int i = current_floor + 1; i <= new_floor; i++) {
            printf("%d...\n", i);
        }

    } else if (new_floor < current_floor) {
        printf("\nGoing down...\n");
        for (int i = current_floor - 1; i >= new_floor; i--) {
            printf("%d...\n", i);
        }
    }
    current_floor = new_floor;
}

//a function that adds or removes passenegrs from the elevator
void load_unload_passengers(int *num_of_passengers) {
    char load_or_unload;
    do {
        printf("Type [L] to load passengers or type [U] to unload passengers: ");
        scanf(" %c", &load_or_unload);

        //if statement that proceeds if the input is L or U otherwise give an "invalid input" message
        if (load_or_unload == 'L') {
            int num;
            do {
                printf("Number of passengers to load: ");
                scanf("%d", &num);
                if (num < 0) {
                    printf("Invalid input. Please enter a positive number.\n");
                } else if (*num_of_passengers + num > 10) // the elevator can accept up to 10 passengers
                    {
                    printf("Elevator is full. Can't load more than 10 passengers.\n");
                } else {
                    *num_of_passengers += num; //add the number of the paseengers the user wants
                                                // to load the current number of passengers
                    break;
                }
            } while (true);
            break;
        } else if (load_or_unload == 'U') {
            int num;
            do {
                printf("Number of passengers to unload: ");
                scanf("%d", &num);

                if (num < 0) {
                    printf("Invalid input. Please enter a positive number.\n");
                }else if (num > *num_of_passengers) {
                    printf("Elevator is empty. Can't unload more passengers than there are in the elevator.");
                } else {
                    *num_of_passengers -= num;
                    break;
                }
            } while (true);
            break;
        } else {
            printf("Invalid input. Please enter L or U.\n");
        }
    } while (true);
}


int main(void) {
    printf("Welcome!\n");

    int current_floor = MIN_FLOOR; //we start from floor 0, aka ground floor
    int num_of_passengers = 1;

    //        // Read the current floor from a file, if it exists
        FILE *fp;
        fp = fopen("current_floor.txt", "r"); // Open the file in read mode
        if (fp != NULL) { // If the file exists
            fscanf(fp, "%d", &current_floor); // Read the current floor from the file
            fclose(fp); // Close the file
        }

    while (true) {
        // if the number of the passengers is zero, so the user unloads all the passengers then the program ends
        if (num_of_passengers == 0) {
            printf("Bye!\n");
            break;
        }
            print_option_list(current_floor,
                              num_of_passengers);//print the list and current floor and number of passengers

            int new_floor = get_new_floor(); //we get the new floor from the user and the number of passengers
            if (new_floor == -1) {
                break; //we finish if new_floor is -1, which means that the user lastly inputted "A"
            }
            load_unload_passengers(&num_of_passengers);//load or unload the passengers according to the user's input
            moving_elevator(current_floor,
                            new_floor); //the motion of the elevator moving from current floor to new floor is printed
            current_floor = new_floor; //we save the new floor as the current floor until the next move
        }
//     Save the current floor to a file before exiting the program
        fp = fopen("current_floor.txt", "w"); // Open the file in write mode
        fprintf(fp, "%d", current_floor); // Save the current floor to the file
        fclose(fp); // Close the file
        return 0;

    }
