#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/*PART 1 HELPERS*/

/*Takes in a string and returns whether or not its a valid int.*/
bool check_valid_int(int size, const char str[size]){
    char * endptr;
    strtol(str, &endptr, 10);       

    if (endptr && endptr[0] != '\0') { //does not contain valid int
        return false;
    } 
    else {
        return true;
    }
}

/*Takes in a sequence of integers and prints them in this formatting:
  [4, 1, 3, 1, 2, 4, 3, 2]*/
void print_sequence(int size, const int *sequence){
    printf("[");

    // Print everything but last element for formatting purposes.
    for (int i = 0; i < size - 1; i++){
        printf("%d, ", sequence[i]);
    }

    printf("%d]\n", sequence[size - 1]);
}

/*PART 2 HELPERS*/

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

    // Initialize each value to 0 in case there's any junk at that memory location.
    // (This was necessary because I was experiencing bugs because of it).
    for (int i = 0; i < size; i++){
        skipped_indexes[i] = 0;
    }

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

int compute_x_helper(int n){
    if (n % 4 == 0){
        return (n / 4);
    }
    else{
        return (n / 4 + 1);
    }
}

/*Retuns an array of all evens or odds in a given range. If even_or_odd == 0,
  it will return all the odd numbers, if even_or_odd == 1, it will return
  all the evens. Stores the slength of array at i = 0. */
int * evens_or_odds_in_range(int start, int end, int even_or_odd){
    
    if (start % 2 == even_or_odd){
        start += 1;
    }

    // This long formula just computes what the size of the array should be. Add +1 to store length.
    int size_of_new_arr = ((end - start + 1) / 2) + ((end - start + 1) % 2);
    int *evens_or_odds = malloc(sizeof(int) * (size_of_new_arr + 1));

    // Loading everything into new array
    evens_or_odds[0] = size_of_new_arr;
    int index_to_load = 1;
    for (int i = start; i <= end; i+=2){
       evens_or_odds[index_to_load] = i;
       index_to_load++; 
    }

    return evens_or_odds;
}

int * reverse_sequence(int size, const int * original_sequence){
    int * reverse_sequence = malloc(sizeof(int) * size);
    
    // Iterate through loop in reverse and load into reverse requence
    int index_to_load = 0;
    for (int i = (size - 1); i >= 0; i-=1){
        reverse_sequence[index_to_load] = original_sequence[i];
        index_to_load++;
    }

    return reverse_sequence;
}

/*Appends an array to an array. Assumes you won't surpass the capacity. Returns new append point.*/
int append_array_to_array(int append_point, int * arr1, int size2, const int * arr2){
    for (int i = 0; i < size2; i++){
        arr1[append_point] = arr2[i];
        append_point++;
    }

    return append_point;
}

void create_and_print_langford(int n){
    // Check if impossible for n
    if ((n % 4 == 1) || (n % 4 == 2) || n < 1){
        printf("No results found.\n");
    }

    // Otherwise build pairing
    else{
        // Compute variables as descibed in YouTube video.
        int x = compute_x_helper(n);
        int a = 2 * x - 1;
        int b = 4 * x - 2;
        int c = 4 * x - 1;
        int d = 4 * x;
        int *p = evens_or_odds_in_range(1, a-1, 0);
        int *r = evens_or_odds_in_range(a+2, b-1, 0);
        int *q = evens_or_odds_in_range(2, a-1, 1);
        int *s = evens_or_odds_in_range(a+1, b-1, 1);

            // Store their sizes and Remove arr[0] for p,r,q,s to remove their size from array.
            int size_p = p[0];
            int size_r = r[0];
            int size_q = q[0];
            int size_s = s[0];
            p++;
            r++;
            q++;
            s++;

        int *rev_p = reverse_sequence(size_p, p);
        int *rev_r = reverse_sequence(size_r, r);
        int *rev_q = reverse_sequence(size_q, q);
        int *rev_s = reverse_sequence(size_s, s);

        int *langford_pairing = malloc(sizeof(int) * 2 * n);

        /*Note to TA: I know there are chucks of repeated code here, but it would have taken more lines of code
          to pass all of the information I needed to turn this into a function. I didn't feel it was necessary to 
          make a function since I'd only need to repeat this twice.*/  
        if (n % 4 == 0){
            int append_point=0;
            append_point = append_array_to_array(append_point, langford_pairing, size_s, rev_s);
            append_point = append_array_to_array(append_point, langford_pairing, size_p, rev_p);
            langford_pairing[append_point] = b; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_p, p);
            langford_pairing[append_point] = c; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_s, s);
            langford_pairing[append_point] = d; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_r, rev_r);
            append_point = append_array_to_array(append_point, langford_pairing, size_q, rev_q);
            langford_pairing[append_point] = b; append_point++;
            langford_pairing[append_point] = a; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_q, q);
            langford_pairing[append_point] = c; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_r, r);
            langford_pairing[append_point] = a; append_point++;
            langford_pairing[append_point] = d; append_point++;
        }

        else{
            int append_point=0;
            append_point = append_array_to_array(append_point, langford_pairing, size_s, rev_s);
            append_point = append_array_to_array(append_point, langford_pairing, size_p, rev_p);
            langford_pairing[append_point] = b; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_p, p);
            langford_pairing[append_point] = c; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_s, s);
            langford_pairing[append_point] = a; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_r, rev_r);
            append_point = append_array_to_array(append_point, langford_pairing, size_q, rev_q);
            langford_pairing[append_point] = b; append_point++;
            langford_pairing[append_point] = a; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_q, q);
            langford_pairing[append_point] = c; append_point++;
            append_point = append_array_to_array(append_point, langford_pairing, size_r, r);
        }

        print_sequence(2 * n, langford_pairing);
    }
}

/*MAIN*/
int main(int argc, char **argv){
    /*TASK 1*/

    // Program Usage Check
    if ((argc < 2) || (strcmp(argv[1], "-h") == 0)){
        fprintf(stderr, "usage: %s [-h] -c n | num...\n", argv[0]);
        return 0;
    }

    // Create Mode checks
    else if (strcmp(argv[1], "-c") == 0){
        // Error 1
        if (argc < 3){
            fprintf(stderr, "%s: -c option requires an argument.\n", argv[0]);
            return 1;
        } 
        // Error 2
        else if (argc > 3){
            fprintf(stderr, "%s: -c option received too many arguments.\n", argv[0]);
            return 1;
        } 
        // Error 3
        else if (!check_valid_int(sizeof(argv[2])/sizeof(char *), argv[2])){
            fprintf(stderr, "error: %s is not an integer.\n", argv[2]);
            return 1;
        }
        // No Error! :)
        else{
            int n = strtol(argv[2], NULL, 10);
            printf("Creating a langford pairing with n=%d\n", n);
            create_and_print_langford(n);
        }
    }

    // Check mode checks
    else{
        int nums_size = argc - 1;
        int *nums = malloc(sizeof(int) * (nums_size)); 
        for (int i = 1; i < argc; i++){
            if (!check_valid_int(sizeof(argv[i])/sizeof(char *), argv[i])){
                fprintf(stderr, "error: %s is not an integer.\n", argv[i]);
                return 1;
            }
            nums[i - 1] = strtol(argv[i], NULL, 10);
        }

        printf("Your sequence: ");
        print_sequence(nums_size, nums);
        bool is_valid = is_langford_pairing(nums_size, nums);

        if (is_valid){
            printf("It is a langford pairing!\n");
        }
        else{
            printf("It is NOT a langford pairing.\n");
        }
    }

	return 0;
}



