#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *suffix;

long calculate_file_size(FILE * file)
{
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    return file_size;
}

int main(int argc, char* argv[])
{
    if (argc != 2 && argc != 3)
    {
        printf("Usage %s [-d] <to compresse a file>\n", argv[0]);
        printf("-d to decompresse provided file\n");
        return 0;
    }

    char* input_file_name;
    bool decompresse = false;

    if (argc == 2)
    {
       input_file_name = argv[1]; 
    }

    else if (argc == 3)
    {
        char *decompress_flag = argv[1];

        if (!strcmp(decompress_flag, "-d"))
        {
            decompresse = true;
            input_file_name = argv[2];
        }

        else
        {
            printf("Invalid option %s\n", decompress_flag);
            return -1;
        }
    }
    

    // input file
    FILE* input_file_pointer = fopen(input_file_name, "rb");

    if (input_file_pointer == NULL)
    {
        perror("Failed To Opening The Input File");
        return -1;
    }

    suffix = decompresse ? ".decompressed" : ".compressed"; 

    // output file (The compressed file)
    int file_name_length = strlen(input_file_name) + strlen(suffix) + 1; 
    char output_file_name[file_name_length];



    for (int i = 0; i < file_name_length; ++i)
        output_file_name[i] = 0;

    for (size_t i = 0; i < strlen(input_file_name); ++i)
        output_file_name[i] = input_file_name[i];


    strcat(output_file_name, suffix);

    FILE* output_file_pointer = fopen(output_file_name, "wb");

    if (output_file_pointer == NULL)
    {
        perror("Failed To Opening The Output File");
        return -1;
    }

    
    long file_size = calculate_file_size(input_file_pointer);

    unsigned char *input_data = malloc(file_size);
    int c;
    long i = 0;

    while  ( (c = getc(input_file_pointer)) != EOF)
    {
        input_data[i++] = c;
    }
    
    int output_data_size = 0;


    unsigned char *result;

    if(decompresse)
    {
        printf("Decompressed Data\n");
        result = DecompressData(input_data, file_size, &output_data_size);
    }

    else
    {

        printf("Compressed Data\n");
        result = CompressData(input_data, file_size, &output_data_size);
    }

    for (int j=0; j < output_data_size; ++j)
    {
        putc(result[j], output_file_pointer);
    }


    MemFree(result);


    return 0;
}

