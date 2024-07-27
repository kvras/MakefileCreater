#include <stdio.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <cstring>

int main(int argc, char **argv)
{
    DIR *dir;
    struct dirent *ent;
    std::string str;

    if(argc != 2){
        std::cout<<"pass the name of programme as a parametre \n";
        return 0;
    }
    if ((dir = opendir (".")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (std::strlen(ent->d_name) > 4 && std::strcmp(ent->d_name + std::strlen(ent->d_name) - 4, ".cpp") == 0) {
                str +=ent->d_name;
                str += "\t";
            }
        }
        closedir (dir);
    } else {
        std::cerr << "Could not open directory" << std::endl;
        return 1;
    }
    std::ofstream file("Makefile");
    if (!file)
        std::cout << "error\n";
    file << "CC = c++\nFLAGS = -Wall -Werror -Wextra -std=c++98\nNAME = ";
    file << argv[1];
    file << "\nSRC = ";
    file << str;
    file << "\n";
    str = "OBJ = $(SRC:.c=.o)\nINC = ";
    if ((dir = opendir (".")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (std::strlen(ent->d_name) > 4 && std::strcmp(ent->d_name + std::strlen(ent->d_name) - 4, ".hpp") == 0) {
                str +=ent->d_name;
                str += "\t";
            }
        }
        closedir (dir);
    } else {
        std::cerr << "Could not open directory" << std::endl;
        return 1;
    }
    file << str;
    file << "\n\n";
    file << "all: $(NAME)\n\n$(NAME): $(INC) $(OBJ)\n\t$(CC) $(FLAGS) $(OBJ) -o $(NAME)\n\n";
    file << "%.o: %.c $(INC)\n\t$(CC) $(CFLAGS) -c $< -o $@\n\n";
    file << "clean:\n\trm -rf $(NAME)\n\n";
    file << "fclean:\tclean\n\n";
    file << "re:\tfclean all\n\n";
    file << ".PHONY:\tclean";

file.close();

    file.close();
}
