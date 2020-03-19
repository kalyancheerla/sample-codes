#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <jansson.h>

#define JSON_PRETTY_PRINT_FLAGS JSON_INDENT(4)

/* Return the offset of the first newline in text or the length of
   text if there's no newline */
static int newline_offset(const char *text)
{
    const char *newline = strchr(text, '\n');
    if(!newline)
        return strlen(text);
    else
        return (int)(newline - text);
}

int main(int argc, char *argv[])
{
    // Check for no. of arg's
    if(argc != 2)
    {
        fprintf(stderr, "usage: %s <file-name>\n\n", argv[0]);
        fprintf(stderr, "List commits from github json dump file.\n\n");
        return -1;
    }

    // Get file pointer & total size of file
    FILE *fp = fopen(argv[1], "rb");
    fseek(fp, 0, SEEK_END);
    long fsize = ftell (fp);
    fseek(fp, 0, SEEK_SET);

    // Dynamically allocate memory for text buffer
    char *text = malloc (fsize + 1);
    fread(text, 1, fsize, fp);
    fclose(fp);

    // Add NULL termination at the end
    text[fsize] = 0;

    json_t *root = NULL;
    json_error_t error = {0};

    root = json_loads(text, 0, &error);
    free(text);

    if(!root)
    {
        fprintf(stderr, "error: on line %d: %s\n", error.line, error.text);
        return 1;
    }

    if(!json_is_array(root))
    {
        fprintf(stderr, "error: root is not an array\n");
        json_decref(root);
        return 1;
    }

    for(int i = 0; i < json_array_size(root); i++)
    {
        json_t *data, *sha, *commit, *message;
        const char *message_text;

        data = json_array_get(root, i);
        if(!json_is_object(data))
        {
            fprintf(stderr, "error: commit data %d is not an object\n", (int)(i + 1));
            json_decref(root);
            return 1;
        }

        sha = json_object_get(data, "sha");
        if(!json_is_string(sha))
        {
            fprintf(stderr, "error: commit %d: sha is not a string\n", (int)(i + 1));
            json_decref(root);
            return 1;
        }

        commit = json_object_get(data, "commit");
        if(!json_is_object(commit))
        {
            fprintf(stderr, "error: commit %d: commit is not an object\n", (int)(i + 1));
            json_decref(root);
            return 1;
        }

        message = json_object_get(commit, "message");
        if(!json_is_string(message))
        {
            fprintf(stderr, "error: commit %d: message is not a string\n", (int)(i + 1));
            json_decref(root);
            return 1;
        }

        message_text = json_string_value(message);
        printf("%.8s %.*s\n",
               json_string_value(sha),
               newline_offset(message_text),
               message_text);
    }

    // Pretty Print JSON
    size_t size = json_dumpb(root, NULL, 0, JSON_PRETTY_PRINT_FLAGS);
    if (size == 0)
        return -1;

    char *buf = alloca(size);

    size = json_dumpb(root, buf, size, JSON_PRETTY_PRINT_FLAGS);
    buf[size] = 0;
    printf("Message: (%ld bytes)\n%s", size, buf);

    // As alloca is used free is not required
    //free(buf);

    json_decref(root);
    return 0;
}
