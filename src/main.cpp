// STL libraries
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

// Project libraries
#include "epics_lex_analysis.hpp"
#include "epics_latex_gen.hpp"
#include "epics_record_chain.hpp"

// The command argument will look like the following
// ./main --files test_files/sample7.db test_files/sample1.db --subs test_files/x.sub

// Function for removing large comment blocks

int main(int argc, char *argv[])
{ 
    if (argc <= 1)
        return EXIT_FAILURE;

    bool is_input = false, is_output = false;
    std::vector<std::string> input_name;
    std::string output_name;

    for (int i = 1; i < argc; i++)
    {
        if (is_output)
        {
            output_name = argv[i];
        }
        else if (is_input)
        {
            std::string str(argv[i]);
            input_name.push_back(str);
        }
        else
        {
            if (argv[i] == "--input")
            {
                is_input = true;
                is_output = false;
            }
            else if (argv[i] == "--output")
            {
                is_input = false;
                is_output = true;
            }
        }
    }

    EpicsDbFileLexAnalysis x("test_files/example3.db");
    x.parse_dft();

    q_token q_state = x.get_q_state();
    x.print_q_state();
    
    EpicsRecordChain y(q_state);
    y.print_adj_mat();
    y.create_visual_graph("hmm.dot");
    //y.traverse(0, 0);
    
    //EpicsLatexGen gen("test_files/example.db", q_state);
    //gen.save_as_file("test");

    return EXIT_SUCCESS;
}
