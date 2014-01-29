#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void tampil_grid(int[9][9]);
void solusi_grid(int[9][9]);
static int iter = 0;    //menghitung jumlah iterasi

int main(void)
{
    int grid[9][9];
    if(ambil_grid(grid, "grid1.txt") == 0)
        return -1;
    printf("\nSudoku Puzzle:");    
    tampil_grid(grid);
    
    clock_t start=clock();
    
    solusi_grid(grid);
    tampil_grid(grid);
       
    clock_t end=clock();

    double solvingtime=(double)(end-start)/CLOCKS_PER_SEC;

    printf("Jumlah iterasi : %d\n",iter);
    printf ("Membutuhkan %.4lf detik untuk mendapatkan solusi.\n\n",solvingtime ); 
    system("PAUSE");
    return 0;
}

int ambil_grid(int grid[9][9], const char *path)
{
    FILE *file_grid = fopen(path, "r");
    if(file_grid != NULL)
    {
        int i,
            j;
        for(i = 0; i < 9; ++i)
        {
            for(j = 0; j < 9; ++j)
                grid[i][j] = fgetc(file_grid) - '0';
            fgetc(file_grid);
        }
        fclose(file_grid);
        return 1;
    }
    return 0;
}

void tampil_grid(int grid[9][9])
{
  int i, j;
  printf("\n- - - - - - -   - - - - - - -   - - - - - - -\n");
  for(i=0; i<9; i++)
  {
    printf("| ");
    for(j=0;j<9;j++)
    {
       if(grid[i][j] > 0)
         printf("%d | ", grid[i][j]);
       else
         printf("* | ");

       if(j == 2 || j == 5)
         printf("  | ");
    }
    printf("\n- - - - - - -   - - - - - - -   - - - - - - -\n");
    if(i == 2 || i == 5)
      printf("\n- - - - - - -   - - - - - - -   - - - - - - -\n");
    
  }
    putchar('\n');
}

int baris(int n, int grid[9][9], int baris)
{
    int i;
    for(i = 0; i < 9; ++i)
        if(grid[baris][i] == n)
            return 1;
    return 0;
}

int kolom(int n, int grid[9][9], int kolom)
{
    int i;
    for(i = 0; i < 9; ++i)
        if(grid[i][kolom] == n)
            return 1;
    return 0;
}

int kotak_kecil(int n, int grid[9][9], int x, int y)
{
    int i = 3*(x/3),
        j = 3*(y/3);
    for(x = i; x < i+3; ++x)
        for(y = j; y < j+3; ++y)
            if(grid[x][y] == n)
                return 1;
    return 0;
}

void solusi_grid(int grid[9][9])
{
    printf("%s Solusinya (^_^)", is_grid_ok(grid, 0, 0) == 1 ? "Ini" : "Tidak Ada");
}

int is_grid_ok(int grid[9][9], int x, int y)
{
    int n;
    /*jika seluruh grid telah diuji, it's ok*/
    if(y == 9)
        return 1;
    /*jika kasus ini benar, menguji kasus berikutnya*/
    if(grid[x][y] != 0)
        return is_grid_ok(grid, (x+1)%9, y+((x+1)/9));
    /*jika tidak, test setiap kemungkinan untuk kasus grid [x][y]*/
    for(n = 1; n <= 9; ++n)
    {
        iter++;
        if(!baris(n, grid, x) && !kolom(n, grid, y) && !kotak_kecil(n, grid, x, y))
        {
            grid[x][y] = n;
            if(is_grid_ok(grid, (x+1)%9, y+((x+1)/9)))
                return 1;
        }
        grid[x][y] = 0;
    }
    
    return 0;
}
