// Distributed Systems - 2022
// Pierre Perrin - protoxvga

#include <iostream>
#include <fstream>
#include <mpi.h>

//Global variables
const int arraySize = 520;
std::string textArray[arraySize];

// searchData helper method - Do not modify
int searchData(std::string* searchArray, const int size, const char* needle)
{
    /* SEARCH METHOD
    This method examines the search space,
    and returns the number of hits found.
    */
    
    int foundhits = 0;
    
    for(int i = 0; i < size; i++){
        if (searchArray[i].compare(needle) == 0) foundhits++;
    }

    return foundhits;
}

//createData helper method - Do not modify
void createData(int rank)
{
    /* DATA METHOD
    This method populates an array with the text read from file.examines the search
    */
    
    std::string myText;

    // Read from the text file (each node reads from a different file concurrently)
    std::string nodeFileName = "searchText" + std::to_string(rank) + ".txt";
    std::ifstream MyReadFile(nodeFileName);
    
    std::cout << "Node " << rank <<  "  reading file: " << nodeFileName << std::endl;
    
    // Use a while loop together with the getline() function to read the file line by line
    int i = 0;
    while (getline (MyReadFile, myText, ' ')) {
        // add text from file into array
        textArray[i] = myText;
        i++;
    }

    // Close the file
    MyReadFile.close();
}

// Check if there is an argument when executing, if not : the searched string is "none".
char *errorGesture(int argc, char **argv)
{
    if (argc != 2) {
        return ((char *) "none");   // If there is no argument or too mutch arguments, the function return the string: "none"
    } else {
        return ((char *) argv[1]);  // If there is a string passed in argument, the function return this string
    }
}

int main(int argc, char** argv)
{
    int node_rank = 0;     // Variable to store the process rank
    int world_size = 0;     // Variable to store the number of processes
    int node_hits = 0;      // Variable to store the number of hits for the actual node
    int total_hits = 0;     // Variable to store the number of hits in all the processes (for node 3 as asked)

    char *search_word = errorGesture(argc, argv);   // Variable to store the string returned by the errorGesture function (see upper)

    MPI_Init(NULL, NULL);   // Init the MPI library

    MPI_Comm_rank(MPI_COMM_WORLD, &node_rank);     // Get the rank number of the actual node and store it in the node_rank variable
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);     // Get the number of processes running and store it in the world_size variable

    createData(node_rank);     // Fill the textArray global array with words to search our string in it.
    std::cout << "Process " << node_rank << " is searching." << std::endl;     // Print that our process start searching

    node_hits = searchData(textArray, arraySize, search_word);      // Search among the textArray global array our string and store the result in the 'node_hits' variable
    std::cout << "Process " << node_rank << " found " << node_hits << " times the word '" << search_word << "'" << std::endl;      // Print the amount of time the actual node found our string in from the text

    MPI_Reduce(&node_hits, &total_hits, 1, MPI_INT, MPI_SUM, 3, MPI_COMM_WORLD);    // Send the number of hits we have got to the node 3 and do the sum of all the processes results, storing it in the 'total_hits' variable.

    if (node_rank == 3)
        std::cout << "In all processes, the total number of '" << search_word << "' is: " << total_hits << std::endl;   // If we are the node 3, print the total of hits from all the processes (thanks to MPI_Reduce methode)

    MPI_Finalize(); // Close the MPI library

    return (0);     // Return control to the OS
}


