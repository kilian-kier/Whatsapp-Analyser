#include "include/output.h"

void init_picture_buffer() {
    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            global_picture_buffer[y][x].character = ' ';
            global_picture_buffer[y][x].foreground = white;
            global_picture_buffer[y][x].background = black;

        }
    }
}

void print_to_buffer(char string[], int xpos, int ypos, Color foreground, Color background) {
    static int y = 0;
    static int x = 0;
    if (xpos >= 0) {
        x = xpos;
    }
    if (ypos >= 0) {
        y = ypos;
    }
    int to_print = (int)strlen(string);
    for (int i = 0; i < to_print; i++) {
        if (y >= y_size) {
            return;
        }
        if (string[i] == '\n') {
            y++;
            if (xpos > 0) {
                x = xpos;
            } else {
                x = 0;
            }
            continue;
        }
        global_picture_buffer[y][x].character = string[i];
        global_picture_buffer[y][x].foreground = foreground;
        global_picture_buffer[y][x].background = background;
        x++;
    }
}

void draw_rect(int xpos, int ypos, int xsize, int ysize, Color color, bool fill, bool layer) {
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            if (fill || (!x || !y || y == ysize - 1 || x == xsize - 1)) {
                if (layer) {
                    global_picture_buffer[y + ypos][x + xpos].character = -37;
                    global_picture_buffer[y + ypos][x + xpos].foreground = color;
                } else {
                    global_picture_buffer[y + ypos][x + xpos].character = ' ';
                    global_picture_buffer[y + ypos][x + xpos].background = color;
                }
            }
        }
    }
}

void draw_picture(char *pointer1, char*pointer2, int xpos, int ypos, int xsize, int ysize) {
    char temp[100];
    unsigned char color;
    int ret = 1;
    int columns = 0;
    int rows = 0;
    FILE*picture;

    if (xsize + xpos > x_size || ysize + ypos > y_size) {
        printf("Bild ist zu gross");
        return;
    }

    if(pointer2==NULL) {
        picture = fopen(pointer1, "rb");
        if (picture == NULL) {
            perror("fopen");
            return;
        }
        rewind(picture);
        for (int i = 0; i < 2; i++) {
            fgets(temp, 100, picture);
        }
        fscanf(picture, "%d %d\n", &columns, &rows);
        fgets(temp, 100, picture);
    }else{
        int i=0;
        while(i<2){
            if(*pointer1=='\n') i++;
            pointer1++;
        }
        for(i=0;pointer1[i]!=' ';i++);
        pointer1[i]=0;
        columns=atoi(pointer1);
        pointer1=&pointer1[i]+1;
        for(i=0;pointer1[i]!='\n';i++);
        pointer1[i]=0;
        rows=atoi(pointer1);


        for(pointer1;*pointer1!='\n';pointer1++);
        pointer1++;
    }
    unsigned char (*buffer)[rows][columns][3] = (unsigned char (*)[rows][columns][3]) malloc(
            sizeof(unsigned char) * rows * columns * 3);

    if(pointer2==NULL){
        for (int y = 0; y < rows && ret == 1; y++) {
            for (int x = 0; x < columns && ret == 1; x++) {
                fread(&color, 1, 1, picture);
                (*buffer)[y][x][0] = color;
                fread(&color, 1, 1, picture);
                (*buffer)[y][x][1] = color;
                ret = fread(&color, 1, 1, picture);
                (*buffer)[y][x][2] = color;
            }
        }
        fclose(picture);
    }else{
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < columns; x++) {
                (*buffer)[y][x][0] = *pointer1;
                pointer1++;
                (*buffer)[y][x][1] = *pointer1;
                pointer1++;
                (*buffer)[y][x][2] = *pointer1;
                pointer1++;
            }
        }
    }

    int newx;
    int newy;
    for (int y = 0; y < ysize; y++) {
        for (int x = 0; x < xsize; x++) {
            newx = x * columns / xsize;
            newy = y * rows / ysize;
            global_picture_buffer[y + ypos][x + xpos].character = ' ';
            global_picture_buffer[y + ypos][x + xpos].background = (Color) {(*buffer)[newy][newx][0], (*buffer)[newy][newx][1],
                                                                     (*buffer)[newy][newx][2]};
        }
    }
    free((*buffer));
}

void draw_picture_buffer() {
    int r;
    int br;
    int g;
    int bg;
    int b;
    int bb;
    setvbuf(stdout, NULL, _IOFBF, (x_pos + x_size) * (y_pos + y_size) * 25);
    printf("\x1b[%d;%dH", y_pos + 1, x_pos + 1);
    for (int y = 0; y < y_size; y += 1) {
        for (int x = 0; x < x_size; x++) {
            if (global_picture_buffer[y][x].background.r != br || global_picture_buffer[y][x].background.g != bg ||
                global_picture_buffer[y][x].background.b != bb) {
                br = global_picture_buffer[y][x].background.r;
                bg = global_picture_buffer[y][x].background.g;
                bb = global_picture_buffer[y][x].background.b;
                background_color(br, bg, bb);
            }
            if (global_picture_buffer[y][x].foreground.r != br || global_picture_buffer[y][x].foreground.g != bg ||
                global_picture_buffer[y][x].foreground.b != bb) {
                r = global_picture_buffer[y][x].foreground.r;
                g = global_picture_buffer[y][x].foreground.g;
                b = global_picture_buffer[y][x].foreground.b;
                foreground_color(r, g, b);
            }

            printf("%c", global_picture_buffer[y][x].character);
        }
        printf("\x1b[%dD\x1b[1B", x_size);
    }
    fflush(stdout);
    foreground_color(255, 255, 255);
    printf("\x1b[H");
    setvbuf(stdout, NULL, _IONBF, 0);
}

void clear_screen() {
    printf("\x1b[H\x1b[0J");
}

void foreground_color(int r, int g, int b) {
    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

void background_color(int r, int g, int b) {
    printf("\x1b[48;2;%d;%d;%dm", r, g, b);
}