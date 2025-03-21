/*
lineage.cpp
Purpose: to ask the user for an input file, to read in the input file related
to a number of genes and its possible mutations and energy costs. The program
then asks the user to input a query and outputs a different statement depending
on the query the user inputs. There are multiple possible queries.
Created by Cheryl Melwani (cmelwa01)
Date: November 5th, 2019
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

const int NUM_MUT = 5;
const string PRINT_DATA = "p";
const string MUTATION_POSSIBLE = "m";
const string MUTATION_WITH_ENERGY = "me";
const string QUIT = "q";
const string EVOLUTION = "e";
const string ENERGETIC_EVOLUTION = "ene";
const string COMMON_ANCESTOR = "c";

struct Gene;
struct Mutation;

struct Gene {
  string name; //name of the gene
  Mutation *mutations[NUM_MUT];
  //array of 5 pointers that point to mutation structs
};

struct Mutation {
  string m_name; //name of the mutated gene
  Gene *mutated_gene; //a pointer of type gene that points to the mutated gene
  int energy_input; //integer cost of energy of each mutation
};

Gene *read_genes(string filename, int *num_genes_p);
void init_genes(Gene *genes, int num_genes);
Gene *find_gene(Gene *genes, int num_genes, string gene_name);
void populate_genes(Gene *genes, int num_genes, ifstream *infile);
void add_mutation(Gene *genes, int num_genes, Gene *current_gene,
  string gene_name, string mutation_name, int energy_input);
void query_p(Gene *genes, int num_genes);
void query_m(Gene *genes, int num_genes, string source_gene,
  string target_gene);
void query_me(Gene *genes, int num_genes, string source_gene,
  string target_gene, int energy_input);
bool can_mutate_stepwise(Gene *genes, int num_genes, string source_gene,
    string target_gene, int max_steps);
bool can_mutate_energywise(Gene *genes, int num_genes, string source_gene,
      string target_gene, int energy_input);
void common_ancestor(Gene *genes, int num_genes, string source_gene,
        string target_gene);

/* Purpose: is to output specific statements to the user depending on what query
they input. The main function serves as somewhat of a print function. */
int main() {
  string filename;
  string query;
  string source_gene;
  string target_gene;
  int energy_input = 0;
  int max_steps = 0;
  cout << "Enter data file name: ";
  cin >> filename;
  cout << "Enter a query: ";
  cin >> query;

  int num_genes;
  Gene *genes = read_genes(filename, &num_genes);

  while (query != QUIT) {
    if (query == PRINT_DATA) {
      query_p(genes, num_genes);
    }
    else if (query == MUTATION_POSSIBLE) {
      cin >> source_gene >> target_gene;
      query_m(genes, num_genes, source_gene, target_gene);
    }
    else if (query == MUTATION_WITH_ENERGY) {
      cin >> source_gene >> target_gene >> energy_input;
      query_me(genes, num_genes, source_gene, target_gene, energy_input);
    }
    else if (query == EVOLUTION) {
      cin >> source_gene >> target_gene >> max_steps;
      if(can_mutate_stepwise(genes, num_genes, source_gene, target_gene,
        max_steps)) {
        cout << source_gene << " can evolve into " << target_gene <<
        " in " << max_steps << " steps or less" << endl;
      } else {
        cout << source_gene << " cannot evolve into " << target_gene <<
        " in " << max_steps << " steps or less" << endl;
      }
    }
    else if (query == ENERGETIC_EVOLUTION) {
      cin >> source_gene >> target_gene >> energy_input;
      if(can_mutate_energywise(genes, num_genes, source_gene,
      target_gene, energy_input)) {
        cout << source_gene << " can evolve into " << target_gene <<
        " with at most " << energy_input << " evolutionary cost" << endl;
      } else {
        cout << source_gene << " cannot evolve into " << target_gene <<
        " with at most " << energy_input << " evolutionary cost" << endl;
      }
    }
    else if(query == COMMON_ANCESTOR) {
      common_ancestor(genes, num_genes, source_gene, target_gene);
    }
    cout << "\n" << "Enter a query: ";
    cin >> query;
  }

  if (query == QUIT) {
    /* makes sure that the array of genes structs is deleted after the program
    outputs what needs to be outputted to not waste any memory */
    for (int i = 0; i < num_genes; i++) {
      for (int j = 0; j < NUM_MUT; j++) {
        if (genes[i].mutations[j] != nullptr) {
          delete genes[i].mutations[j];
        }
      }
    }
    delete [] genes;
    return 0;
  }
}

/* Purpose: reads the file inputted by the user and takes in the number of
genes found. Creates a new array of gene structs with the size being the number
of genes. This function calls the initialize function and the populate genes
function. Returns a correctly populated array of gene structs that resembles
that of the input file. */
Gene *read_genes(string filename, int *num_genes_p) {
  ifstream infile(filename.c_str());
  if (infile.fail()) {
    cerr << "“ERROR OPENING FILE: Exiting Program" << endl;
    exit(EXIT_FAILURE);
  }

  infile >> *num_genes_p;
  infile.ignore();
    if (infile.fail()) {
      cerr << "ERROR: Reading the number of genes failed." << endl;
      exit(EXIT_FAILURE);
    }

    Gene *new_genes = new Gene[*num_genes_p];
    init_genes(new_genes, *num_genes_p); //initialize the array of new genes
    populate_genes(new_genes, *num_genes_p, &infile); //populate the array
    return new_genes;
}

/* Purpose: To initialize the array of gene structs so that there isn't any
garbage value in the array that could cause any errors. */
void init_genes(Gene *genes, int num_genes) {
  for (int i = 0; i < num_genes; i++) {
    genes[i].name = "";
    for (int j = 0; j < NUM_MUT; j++) {
      genes[i].mutations[j] = nullptr;
    }
  }
}
/* Purpose: Is to find a specific gene name in the array of gene structs or
find an empty space in the array to put a gene name inside the array. If the
name of the gene is found in the array of gene structs, the function will
return the pointer to that gene struct. If the gene is not found, the function
will return a pointer to the address of the next free space in the array of
gene structs. */
Gene *find_gene(Gene *genes, int num_genes, string gene_name) {
  for (int i = 0; i < num_genes; i++) {
    if (genes[i].name == gene_name) {
      return &genes[i];
    } else if (genes[i].name == "") {
      return &genes[i];
    }
  }
  return nullptr;
}

/* Purpose: Is to populate the genes array with the information found in the
input file. This function calls the find_gene function and inputs the specific
gene in question into the array of gene structs if it hasn't been inputted yet
in the next available space in the array. This function also populates the
gene names of the possible mutations and adds all of this information into
the array of gene structs. */
void populate_genes(Gene *genes, int num_genes, ifstream *infile) {
  istringstream line_stream;
  string gene_name, mutation_name, line_info;
  int energy_input;
  getline(*infile, line_info);
  while (!infile->eof()) {
    line_stream.str(line_info);
    line_stream >> gene_name;
    Gene *current_gene = find_gene(genes, num_genes, gene_name);
    if (current_gene != nullptr && current_gene->name == "") {
      current_gene->name = gene_name;
    }
    line_stream >> mutation_name >> energy_input;
    while (!line_stream.fail()) {
      add_mutation(genes, num_genes, current_gene, gene_name, mutation_name,
      energy_input);
      line_stream >> mutation_name >> energy_input;
    }
    line_stream.clear();
    getline(*infile, line_info);
  }
}

/* Purpose: Is to populate the mutation name, energy input, and pointer to the
mutation gene in the array of gene structs. Takes the information regarding
the possible mutations from the input file and populates each gene struct
with that information. This is done by calling the array of mutation pointers
within the gene struct.
 */
void add_mutation(Gene *genes, int num_genes, Gene *current_gene,
  string gene_name, string mutation_name, int energy_input) {

  Gene *gene_p = find_gene(genes, num_genes, gene_name);
  if (gene_p != nullptr && gene_p->name == "") {
    gene_p->name = gene_name;
  }

  for (int i = 0; i < NUM_MUT; i++) {
    if (current_gene->mutations[i] == nullptr) {
      current_gene->mutations[i] = new Mutation;
      current_gene->mutations[i]->m_name = mutation_name;
      current_gene->mutations[i]->energy_input = energy_input;
      current_gene->mutations[i]->mutated_gene = gene_p;
      break;
    }
  }
}
/* Purpose: If query p is chosen, the function is called and cleans up the
information and outputs the information regarding the gene and its possible
mutations in a neat format. */
void query_p(Gene *genes, int num_genes) {
  for(int i = 0; i < num_genes; i++) {
    cout << "== " << genes[i].name << " ==" << endl;
    cout << "Mutations: " << endl;
    for(int j = 0; j < NUM_MUT; j++) {
      if(genes[i].mutations[0] == nullptr) {
        cout << "None" << endl;
        break;
      }
      Mutation *current_mutation = genes[i].mutations[j];
      if(current_mutation != nullptr) {
        cout << current_mutation->m_name << " - " << "Cost: "
        << current_mutation->energy_input << endl;
      }
    }
  }
}
/* Purpose: If query m is chosen, the function is called and checks whether
the soure gene can be mutated into the target gene. The function outputs to
the user whether this is possible or not. */
void query_m(Gene *genes, int num_genes, string source_gene,
  string target_gene) {
  bool check = false;
  for(int i = 0; i < num_genes; i++) {
    if(source_gene == genes[i].name) {
      for(int j = 0; j < NUM_MUT; j++) {
        /* (line 233)to account for the fact that not all genes have
        5 mutations */
        if(genes[i].mutations[j] == nullptr) {
          break;
        }
        if(target_gene == genes[i].mutations[j]->m_name) {
          cout << source_gene << " can mutate into " << target_gene << endl;
          check = true;
        }
      }
    }
  }
  if(check == false) {
    cout << source_gene << " cannot mutate into " << target_gene << endl;
  }
}
/*Purpose: If query me is chosen, this function is called and it checks whether
the source gene can mutate into the target gene with the specific amount of
energy that the user inputted. If this is possible, it will output that this
is possible to the user. If the source gene can be mutated with the target gene
but not with that specific amount of energy then it will tell the user that.
If the source gene cant be mutated into the target gene, the program will output
this answer to the user as well.
*/
void query_me(Gene *genes, int num_genes, string source_gene,
  string target_gene, int energy_input) {
  bool check = false;
  for(int i = 0; i < num_genes; i++) {
    if(source_gene == genes[i].name) {
      for(int j = 0; j < NUM_MUT; j++) {
        if(genes[i].mutations[j] == nullptr) {
          break;
        }
        /* If the energy cost is greater then the
        required energy cost, the program will still state that it can be
        mutated with the greater energy cost. */
        if(target_gene == genes[i].mutations[j]->m_name
        && energy_input >= (genes[i].mutations[j]->energy_input)){
          cout << source_gene << " can mutate into " << target_gene <<
          " with evolutionary cost " << energy_input << endl;
          check = true;
        }
        else if(target_gene == genes[i].mutations[j]->m_name
        && energy_input != genes[i].mutations[j]->energy_input){
          cout << source_gene << " can mutate into " << target_gene <<
          " but not with evolutionary cost " << energy_input << endl;
          check = true;
        }
      }
    }
  }
  if(check == false) {
    cout << source_gene << " cannot mutate into " << target_gene << endl;
  }
}

/* Purpose: To see if a source gene can evolve into the target gene in (or
under)the given maximum steps */
bool can_mutate_stepwise(Gene *genes, int num_genes, string source_gene,
  string target_gene, int max_steps) {
  string new_source_gene;

//if the steps inputted are greater than the steps needed to solve the case
  if(max_steps < 0) {
    return false;
  }
  /* this "else if" checks if the source gene that continuesly gets updated ever
  equals the initial target gene. If that is true then it can evolve and the
  function returns true. */
  else if(source_gene == target_gene) {
    return true;
  } else {
  /* iterates through the entire genes struct array to find the inputted
  source gene */
    for(int i = 0; i < num_genes; i++) {
      if(source_gene == genes[i].name) {
        for(int j = 0; j < NUM_MUT; j++) {
  /* if there are no more mutations, the if loop breaks out of the nested
  for loop to avoid any segmentation fault */
          if(genes[i].mutations[j] == nullptr) {
           break;
         }
  /* continuesly updates source_gene to the next mutation name in order to
  compare it to the target gene */
         new_source_gene = genes[i].mutations[j]->m_name;
  /* recersively calls the function but reduces the number of steps by 1
  to get closer to the base case and to see if it can evolve within the
  max number of steps given by the user. If the recursive function returns
  a true that means the new source gene eventually equals the original
  target gene and it can evolve */
         if(can_mutate_stepwise(genes, num_genes, new_source_gene, target_gene,
           max_steps - 1)) {
           return true;
         }
       }
     }
   }
 }
 return false;
}

/* Purpose: Is to see whether the source gene can mutate into the target gene
with the specific amount of energy inputted by the user or less */
bool can_mutate_energywise(Gene *genes, int num_genes, string source_gene,
  string target_gene, int energy_input) {
  string new_source_gene;
  int new_energy_input = 0;

  /* if the energy_input inputted is greater than the energy_input needed to
  evolve then the code wouldn't enter this if loop */
  if(energy_input < 0) {
    return false;
  }
  /* this "else if" checks if the source gene that continuesly gets updated ever
  equals the initial target gene. If that is true then it can evolve and the
  function returns true. */
  else if(source_gene == target_gene) {
    return true;
  } else {
    /* iterates through the entire genes struct array to find the inputted
    source gene */
    for(int i = 0; i < num_genes; i++) {
      /* if there are no more mutations, the if loop breaks out of the nested
      for loop to avoid any segmentation fault */
      if(source_gene == genes[i].name) {
        for(int j = 0; j < NUM_MUT; j++) {
          if(genes[i].mutations[j] == nullptr) {
            break;
          }
    /* continuesly updates source_gene to the next mutation name in order to
    compare it to the target gene and continuesly updates the energy input
    of each mutation */
          new_source_gene = genes[i].mutations[j]->m_name;
          new_energy_input = genes[i].mutations[j]->energy_input;
    /* recersively calls the function but reduce the original energy input
    that is inputted by the user by the new energy input which represents
    the energy needed to mutate or evolve from one gene to the next, which
    gets us closer to the base case of the energy input being 0. If the
    recursive function returns a true that means the new source gene eventually
    equals the original target gene and it can evolve with the energy input
    inputted by the user or less */
          if(can_mutate_energywise(genes, num_genes, new_source_gene,
          target_gene, energy_input-new_energy_input)) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

/* Purpose: Is to see whether a gene is a common ancestor */
void common_ancestor(Gene *genes, int num_genes, string source_gene,
  string target_gene) {
  int steps = 10;
  int count = 0;
  bool check = false;

/* iterating through the array of gene structs to declare a source gene */
  for(int i = 0; i < num_genes; i++) {
    source_gene = genes[i].name;
    /* iterating through the array of gene structs to declare a target gene
    to use when calling can_mutate_stepwise */
    for(int j = 0; j < num_genes; j++) {
      target_gene = genes[j].name;
      /* calling the recursive function can_mutate_stepwise in order to check
      whether the source gene can evolve into the target gene and if it can
      evolve the recursive function will return a true. When it can evolve the
      counter will increase by 1 to keep track of how many genes the source
      gene can evolve into */
      if(can_mutate_stepwise(genes, num_genes, source_gene, target_gene,
      steps)) {
        count++;
      }
    }
    /* if number of genes the source gene can evolve into equals to the
    number of genes in the array of gene structs, then that gene is a
    common ancestor */
    if(count == num_genes) {
      cout << source_gene << " is a common ancestor " << endl;
      check = true;
    }
    /* resetting the count to 0 */
    count = 0;
  }
  /* if check is false the source gene cannot evolve into all of the other
  genes and therefore isn't a common ancestor */
  if(check == false) {
    cout << "There are no common ancestors" << endl;
  }
}
