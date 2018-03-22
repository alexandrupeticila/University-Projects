#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"

#pragma pack(1)

typedef struct pixel
{
    unsigned char b, g, r;
} px;

typedef struct zn
{
    unsigned char b, g, r;
    int k;
} zn;

typedef struct tpl
{
    unsigned char b, g, r;
    short l, c;
} tpl;

typedef struct coada
{
    unsigned short l, c;
} cd;

#pragma pack()

int padding(int width)
{
    int multiplu = 0, i = 1;
    while(multiplu < (width * 3))
    {
        multiplu = 4 * i;
        i++;
    }

    return (multiplu - (width * 3));
}

bfh *citire_fh(char numeimg[100], bfh *fh)
{
    FILE *in = fopen(numeimg, "rb");

    fh = calloc(1, sizeof(bfh));
    fread(&fh->fileMarker1, sizeof(char), 1, in);
    fread(&fh->fileMarker2, sizeof(char), 1, in);
    fread(&fh->bfSize, sizeof(int), 1, in);
    fread(&fh->unused1, sizeof(short), 1, in);
    fread(&fh->unused2, sizeof(short), 1, in);
    fread(&fh->imageDataOffset, sizeof(int), 1, in);

    fclose(in);

    return fh;
}

bih *citire_ih(char numeimg[100], bih *ih)
{
    FILE *in = fopen(numeimg, "rb");
    fseek(in, 14, SEEK_SET);

    ih = calloc(1, sizeof(bih));
    fread(&ih->biSize, sizeof(int), 1, in);
    fread(&ih->width, sizeof(int), 1, in);
    fread(&ih->height, sizeof(int), 1, in);
    fread(&ih->planes, sizeof(short), 1, in);
    fread(&ih->bitPix, sizeof(short), 1, in);
    fread(&ih->biCompression, sizeof(int), 1, in);
    fread(&ih->biSizeImage, sizeof(int), 1, in);
    fread(&ih->biXPelsPerMeter, sizeof(int), 1, in);
    fread(&ih->biYPelsPerMeter, sizeof(int), 1, in);
    fread(&ih->biClrUsed, sizeof(int), 1, in);
    fread(&ih->biClrImportant, sizeof(int), 1, in);

    fclose(in);

    return ih;
}

px **citire_mat(char numeimg[100], bih *ih, bfh *fh, px **mat)
{
    int pad = padding(ih->width), i, j;
    FILE *in = fopen(numeimg, "rb");
    fseek(in, fh->imageDataOffset, SEEK_SET);

    mat = calloc(ih->height, sizeof(px*));
    for(i = 0; i < ih->height; i++)
        mat[i] = calloc(ih->width, sizeof(px));

    for(i = ih->height - 1; i >= 0 ; i--)
    {
        for(j = 0; j < ih->width; j++)
        {
            fread(&mat[i][j].b, sizeof(char), 1, in);
            fread(&mat[i][j].g, sizeof(char), 1, in);
            fread(&mat[i][j].r, sizeof(char), 1, in);
        }
        fseek(in, pad, SEEK_CUR);
    }

    fclose(in);

    return mat;

}

void headw(char img[100], bih *ih, bfh *fh)
{
    int i;
    char zero = 0;
    FILE *out = fopen(img, "wb");

    fwrite(&fh->fileMarker1, sizeof(char), 1, out);
    fwrite(&fh->fileMarker2, sizeof(char), 1, out);
    fwrite(&fh->bfSize, sizeof(int), 1, out);
    fwrite(&fh->unused1, sizeof(short), 1, out);
    fwrite(&fh->unused2, sizeof(short), 1, out);
    fwrite(&fh->imageDataOffset, sizeof(int), 1, out);
    fwrite(&ih->biSize, sizeof(int), 1, out);
    fwrite(&ih->width, sizeof(int), 1, out);
    fwrite(&ih->height, sizeof(int), 1, out);
    fwrite(&ih->planes, sizeof(short), 1, out);
    fwrite(&ih->bitPix, sizeof(short), 1, out);
    fwrite(&ih->biCompression, sizeof(int), 1, out);
    fwrite(&ih->biSizeImage, sizeof(int), 1, out);
    fwrite(&ih->biXPelsPerMeter, sizeof(int), 1, out);
    fwrite(&ih->biYPelsPerMeter, sizeof(int), 1, out);
    fwrite(&ih->biClrUsed, sizeof(int), 1, out);
    fwrite(&ih->biClrImportant, sizeof(int), 1, out);

    for(i = ftell(out); i < fh->imageDataOffset; i++)
        fwrite(&zero, sizeof(char), 1, out);

    fclose(out);
}

void bw(char nume[100], bih *ih, bfh *fh, px **mat)
{
    char *pct, zero = 0, medie, numeimg[100];
    int pad = padding(ih->width), i, j;

    strcpy(numeimg, nume);
    pct = strchr(numeimg, '.');
    strcpy(pct, "_black_white.bmp");

    headw(numeimg, ih, fh);

    FILE *out = fopen(numeimg, "ab");

    for(i = ih->height - 1; i >= 0 ; i--)
    {
        for(j = 0; j < ih->width; j++)
        {
            medie = (mat[i][j].b + mat[i][j].g + mat[i][j].r) / 3;
            fwrite(&medie, sizeof(char), 1, out);
            fwrite(&medie, sizeof(char), 1, out);
            fwrite(&medie, sizeof(char), 1, out);
        }
        for(j = 0; j < pad; j++)
            fwrite(&zero, sizeof(char), 1, out);
    }

    fclose(out);
}

px *flt(bih *ih, px **mat, px *pixelf, char filtru[4][4], int l, int c)
{
    int i, j, fi = 0, fj = 0;
    int b = 0, g = 0, r = 0;

    for(i = l - 1; i <= l + 1; i++)
    {
        fj = 0;
        for(j = c - 1; j <= c + 1; j++)
        {
            if(i >= 0 && i < ih->height && j >= 0 && j < ih->width)
            {
                b += mat[i][j].b * filtru[fi][fj];
                g += mat[i][j].g * filtru[fi][fj];
                r += mat[i][j].r * filtru[fi][fj];
            }
            fj++;
        }
        fi++;
    }
    if(b > 255)
        pixelf->b = 255;
    else if(b < 0)
        pixelf->b = 0;
    else
        pixelf->b = b;

    if(g > 255)
        pixelf->g = 255;
    else if(g < 0)
        pixelf->g = 0;
    else
        pixelf->g = g;

    if(r > 255)
        pixelf->r = 255;
    else if(r < 0)
        pixelf->r = 0;
    else
        pixelf->r = r;

    return pixelf;
}

void f1(char nume[100], bih *ih, bfh *fh, px **mat)
{
    int pad = padding(ih->width), i, j;
    px *pixelf = calloc(1, sizeof(px));
    char *pct, zero = 0, numeimg[100];
    char filtru[4][4] = {
                {-1, -1, -1},
                {-1, 8, -1},
                {-1, -1, -1}
	};

	strcpy(numeimg, nume);
    pct = strchr(numeimg, '.');
    strcpy(pct, "_f1.bmp");

    headw(numeimg, ih, fh);

    FILE *out = fopen(numeimg, "ab");

    for(i = ih->height - 1; i >= 0 ; i--)
    {
        for(j = 0; j < ih->width; j++)
        {
            pixelf = flt(ih, mat, pixelf, filtru, i, j);
            fwrite(&pixelf->b, sizeof(char), 1, out);
            fwrite(&pixelf->g, sizeof(char), 1, out);
            fwrite(&pixelf->r, sizeof(char), 1, out);
        }
        for(j = 0; j < pad; j++)
            fwrite(&zero, sizeof(char), 1, out);
    }

    free(pixelf);
    fclose(out);
}

void f2(char nume[100], bih *ih, bfh *fh, px **mat)
{
    int pad = padding(ih->width), i, j;
    px *pixelf = calloc(1, sizeof(px));
    char *pct, zero = 0, numeimg[100];
    char filtru[4][4] = {
                {0, 1, 0},
                {1, -4, 1},
                {0, 1, 0}
	};

	strcpy(numeimg, nume);
    pct = strchr(numeimg, '.');
    strcpy(pct, "_f2.bmp");

    headw(numeimg, ih, fh);

    FILE *out = fopen(numeimg, "ab");

    for(i = ih->height - 1; i >= 0 ; i--)
    {
        for(j = 0; j < ih->width; j++)
        {
            pixelf = flt(ih, mat, pixelf, filtru, i, j);
            fwrite(&pixelf->b, sizeof(char), 1, out);
            fwrite(&pixelf->g, sizeof(char), 1, out);
            fwrite(&pixelf->r, sizeof(char), 1, out);
        }
        for(j = 0; j < pad; j++)
            fwrite(&zero, sizeof(char), 1, out);
    }

    free(pixelf);
    fclose(out);
}

void f3(char nume[100], bih *ih, bfh *fh, px **mat)
{
    int pad = padding(ih->width), i, j;
    px *pixelf = calloc(1, sizeof(px));
    char *pct, zero = 0, numeimg[100];
    char filtru[4][4] = {
                {1, 0, -1},
                {0, 0, 0},
                {-1, 0, 1}
	};

    strcpy(numeimg, nume);
    pct = strchr(numeimg, '.');
    strcpy(pct, "_f3.bmp");

    headw(numeimg, ih, fh);

    FILE *out = fopen(numeimg, "ab");

    for(i = ih->height - 1; i >= 0 ; i--)
    {
        for(j = 0; j < ih->width; j++)
        {
            pixelf = flt(ih, mat, pixelf, filtru, i, j);
            fwrite(&pixelf->b, sizeof(char), 1, out);
            fwrite(&pixelf->g, sizeof(char), 1, out);
            fwrite(&pixelf->r, sizeof(char), 1, out);
        }
        for(j = 0; j < pad; j++)
            fwrite(&zero, sizeof(char), 1, out);
    }

    free(pixelf);
    fclose(out);
}

int gol(int vf)
{
    if(vf >= 0)
        return 1;
    else
        return 0;
}

cd *push(int i, int j, int *vf, cd *elem)
{
    (*vf)++;
    elem[*vf].l = i;
    elem[*vf].c = j;

    return elem;
}

void pop(int *vf, int *i, int *j, cd *elem)
{
    if(gol(*vf) == 1)
    {
        *j = elem[0].c;
        *i = elem[0].l;
        memmove(elem, elem + 1, *vf * sizeof(cd));
        (*vf)--;
    }
}

zn **fill(int i, int j, bih *ih, px pixelb, zn **zona, int thr, int k)
{
    int vf = -1, b, g, r;
    cd *elem;
    elem = calloc(5000, sizeof(cd));

    elem = push(i, j, &vf, elem);
    while(gol(vf))
    {
        pop(&vf, &i, &j, elem);
        b = abs(pixelb.b - zona[i][j].b);
        g = abs(pixelb.g - zona[i][j].g);
        r = abs(pixelb.r - zona[i][j].r);
        if(zona[i][j].k == 0 && (b + g + r) <= thr)
        {
            zona[i][j].b = pixelb.b;
            zona[i][j].g = pixelb.g;
            zona[i][j].r = pixelb.r;
            zona[i][j].k = k;
            if(j < ih->width - 1)
                elem = push(i, j + 1, &vf, elem);
            if(j > 0)
                elem = push(i, j - 1, &vf, elem);
            if(i < ih->height - 1)
                elem = push(i + 1, j, &vf, elem);
            if(i > 0)
                elem = push(i - 1, j, &vf, elem);
        }
    }
    free(elem);
    return zona;
}

void compress(bih *ih, bfh *fh, px **mat, int thr)
{
    int i, j, k = 1, val = 1, dist;
    zn **zona;
    char nume[15] = "compressed.bin";
    px pixelb;

    headw(nume, ih, fh);

    FILE *out = fopen(nume, "ab");

    zona = calloc(ih->height, sizeof(zn*));
    for(i = 0; i < ih->height; i++)
    {
        zona[i] = calloc(ih->width, sizeof(zn));
        memset(&zona[i]->k, 0, ih->width * sizeof(int));
    }

    for(i = 0; i < ih->height; i++)
        for(j = 0; j < ih->width; j++)
        {
            zona[i][j].b = mat[i][j].b;
            zona[i][j].g = mat[i][j].g;
            zona[i][j].r = mat[i][j].r;
        }

    pixelb.b = zona[0][0].b;
    pixelb.g = zona[0][0].g;
    pixelb.r = zona[0][0].r;
    zona = fill(0, 0, ih, pixelb, zona, thr, 1);

    for(i = 0; i < ih->height; i++)
    {
        for(j = 0; j < ih->width; j++)
            if(zona[i][j].k == 0)
            {
                k++;
                pixelb.b = zona[i][j].b;
                pixelb.g = zona[i][j].g;
                pixelb.r = zona[i][j].r;
                zona = fill(i, j, ih, pixelb, zona, thr, k);
            }
    }

    for(j = 1; j <= ih->width; j++)
    {
        fwrite(&val, sizeof(short), 1, out);
        fwrite(&j, sizeof(short), 1, out);
        fwrite(&zona[0][j-1].r, sizeof(char), 1, out);
        fwrite(&zona[0][j-1].g, sizeof(char), 1, out);
        fwrite(&zona[0][j-1].b, sizeof(char), 1, out);
    }

    for(i = 1; i < ih->height - 1; i++)
    {
        dist = 0;
        k = 0;
        for(j = 0; j < ih->width; j++)
        {
            if(zona[i][j].k != k)
            {
                if(dist > 1)
                {
                    val = i + 1;
                    fwrite(&val, sizeof(short), 1, out);
                    fwrite(&j, sizeof(short), 1, out);
                    fwrite(&zona[i][j - 1].r, sizeof(char), 1, out);
                    fwrite(&zona[i][j - 1].g, sizeof(char), 1, out);
                    fwrite(&zona[i][j - 1].b, sizeof(char), 1, out);
                }
                val = i + 1;
                fwrite(&val, sizeof(short), 1, out);
                val = j + 1;
                fwrite(&val, sizeof(short), 1, out);
                fwrite(&zona[i][j].r, sizeof(char), 1, out);
                fwrite(&zona[i][j].g, sizeof(char), 1, out);
                fwrite(&zona[i][j].b, sizeof(char), 1, out);
                k = zona[i][j].k;
                dist = 0;
            }
            if((zona[i - 1][j].k != k || zona[i + 1][j].k != k) && dist > 0)
            {
                val = i + 1;
                fwrite(&val, sizeof(short), 1, out);
                val = j + 1;
                fwrite(&val, sizeof(short), 1, out);
                fwrite(&zona[i][j].r, sizeof(char), 1, out);
                fwrite(&zona[i][j].g, sizeof(char), 1, out);
                fwrite(&zona[i][j].b, sizeof(char), 1, out);
                k = zona[i][j].k;
                dist = 0;
            }
            if(j == ih->width - 1 && dist > 0)
            {
                val = i + 1;
                fwrite(&val, sizeof(short), 1, out);
                val = j + 1;
                fwrite(&val, sizeof(short), 1, out);
                fwrite(&zona[i][j].r, sizeof(char), 1, out);
                fwrite(&zona[i][j].g, sizeof(char), 1, out);
                fwrite(&zona[i][j].b, sizeof(char), 1, out);
                k = zona[i][j].k;
            }
            dist++;
        }
    }

    for(j = 1; j <= ih->width; j++)
    {
        fwrite(&ih->height, sizeof(short), 1, out);
        fwrite(&j, sizeof(short), 1, out);
        fwrite(&zona[ih->height - 1][j-1].r, sizeof(char), 1, out);
        fwrite(&zona[ih->height - 1][j-1].g, sizeof(char), 1, out);
        fwrite(&zona[ih->height - 1][j-1].b, sizeof(char), 1, out);
    }

    for(i = 0; i < ih->height; i++)
        free(zona[i]);
    free(zona);

    fclose(out);
}

void decompress(char nume[100], bih *ih, bfh *fh)
{
    int pad = padding(ih->width), i, j;
    char zero = 0, numeimg[100];
    tpl decomp;
    px **mat;

    strcpy(numeimg, "decompressed.bmp");

    headw(numeimg, ih, fh);

    mat = calloc(ih->height, sizeof(px*));
    for(i = 0; i < ih->height; i++)
        mat[i] = calloc(ih->width, sizeof(px));

    FILE *in = fopen(nume, "rb");
    fseek(in, fh->imageDataOffset, SEEK_SET);

    while(!feof(in))
    {
        fread(&decomp.l, sizeof(short), 1, in);
        fread(&decomp.c, sizeof(short), 1, in);
        fread(&decomp.r, sizeof(char), 1, in);
        fread(&decomp.g, sizeof(char), 1, in);
        fread(&decomp.b, sizeof(char), 1, in);
        for(j = decomp.c - 1; j < ih->width; j++)
        {
            mat[decomp.l - 1][j].b = decomp.b;
            mat[decomp.l - 1][j].g = decomp.g;
            mat[decomp.l - 1][j].r = decomp.r;
        }
    }

    fclose(in);

    FILE *out = fopen(numeimg, "ab");

    for(i = ih->height - 1; i >= 0 ; i--)
    {
        for(j = 0; j < ih->width; j++)
        {
            fwrite(&mat[i][j].b, sizeof(char), 1, out);
            fwrite(&mat[i][j].g, sizeof(char), 1, out);
            fwrite(&mat[i][j].r, sizeof(char), 1, out);
        }
        for(j = 0; j < pad; j++)
            fwrite(&zero, sizeof(char), 1, out);
    }

    fclose(out);

    for(i = 0; i < ih->height; i++)
        free(mat[i]);
    free(mat);
}

int main()
{
    int i, thr;
    char numeimg[100], archive[100], nume[100], *pct;
    px **mat = NULL;
    bfh *fh = NULL;
    bih *ih = NULL;

    FILE *in = fopen("input.txt", "rt");
    fscanf(in, "%s %d %s", numeimg, &thr, archive);

    fclose(in);

    fh = citire_fh(numeimg, fh);
    ih = citire_ih(numeimg, ih);
    mat = citire_mat(numeimg, ih, fh, mat);

    bw(numeimg, ih, fh, mat);

    compress(ih, fh, mat, thr);

    strcpy(nume, numeimg);
    pct = strchr(nume, '.');
    strcpy(pct, "_black_white.bmp");

    for(i = 0; i < ih->height; i++)
        free(mat[i]);
    free(mat);
    mat = citire_mat(nume, ih, fh, mat);

    f1(numeimg, ih, fh, mat);
    f2(numeimg, ih, fh, mat);
    f3(numeimg, ih, fh, mat);

    for(i = 0; i < ih->height; i++)
        free(mat[i]);
    free(mat);
    free(fh);
    free(ih);

    fh = citire_fh(archive, fh);
    ih = citire_ih(archive, ih);

    decompress(archive, ih, fh);

    free(fh);
    free(ih);

    return 0;
}
