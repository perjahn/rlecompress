#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: rledecompress <infile> <outfile>\n");
        return 1;
    }

    char *infile, *outfile;
    infile = argv[1];
    outfile = argv[2];

    FILE *in, *out;

    if (!(in = fopen(infile, "r")))
    {
        printf("Couldn't open infile: '%s'\n", infile);
        return 1;
    }

    if (!(out = fopen(outfile, "w")))
    {
        printf("Couldn't open outfile: '%s'\n", outfile);
        return 1;
    }

    int c, count;

    while ((count = fgetc(in)) != EOF && (c = fgetc(in)) != EOF)
    {
        if (count == 0)
        {
            count = 256;
        }

        for (int i = 0; i < count; i++)
        {
            fputc(c, out);
        }
    }

    fclose(in);
    fclose(out);

    return 0;
}
