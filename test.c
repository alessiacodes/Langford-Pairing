#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*Takes in an array of integers and checks if an element exists in the array.*/
bool element_in_array(int size, const int *arr, int element){
    for (int i = 0; i < size; i++){
        if (arr[i] == element){
            return true;
        }
    }
    return false;
}

/*Takes in a sequence and returns whether or not its a valid langford pairing.*/
bool is_langford_pairing(int size, const int *sequence){
    // if we found a valid pairing, its pair index should not be checked in the for loop below
    int *skipped_indexes = malloc(sizeof(int) * (size)); 

    // We are keeping track of the max value to determine if the size of the array does not
    // make sense for the given n. This means we must be missing a value in between,
    // therefore it is an invalid pairing.
    int max_of_array = 0;
    for(int i = 0; i < size; i++){
        // check if element needs to be checked before doing computation
        if(i < 1 || !element_in_array(size, skipped_indexes, i)){
            int exp_pair_index = i + sequence[i] + 1;

            // if the pair is not in the right position
            if (sequence[exp_pair_index] != sequence[i]){
                return false;
            }

            skipped_indexes[i] = exp_pair_index;
        }

        // if the array contains an invalid integer
        else if (sequence[i] < 1){
            return false;
        }

        if (sequence[i] > max_of_array){
            max_of_array = sequence[i];
        }
    }

    if((max_of_array * 2) != size){
        return false;
    }

    free(skipped_indexes);
    return true;
}

/*MAIN*/
int main(int argc, char **argv){
    printf("hello!S");
    int testarr[22] = {1, 8, 1, 4, 7, 5, 9, 10, 4, 11, 8, 5, 7, 6, 2, 3, 9, 2, 10, 3, 6, 11};
    bool result = is_langford_pairing(22, testarr);
    printf("%d\n", result);
    return 0;
}
