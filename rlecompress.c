#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: rlecompress <infile> <outfile>\n");
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

    int c, lastc = -1, count = 0;

    while ((c = fgetc(in)) != EOF)
    {
        if (lastc == -1)
        {
            lastc = c;
            count++;
        }
        else
        {
            if (c == lastc)
            {
                if (count == 256)
                {
                    fputc(0, out);
                    fputc(lastc, out);

                    count = 1;
                }
                else
                {
                    count++;
                }
            }
            else
            {
                if (count == 256)
                {
                    fputc(0, out);
                }
                else
                {
                    fputc(count, out);
                }
                fputc(lastc, out);

                count = 1;
                lastc = c;
            }
        }
    }
    if (lastc != -1)
    {
        if (count == 256)
        {
            fputc(0, out);
        }
        else
        {
            fputc(count, out);
        }
        fputc(lastc, out);
    }

    fclose(in);
    fclose(out);

    return 0;
}
