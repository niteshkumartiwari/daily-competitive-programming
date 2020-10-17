/*
In a N x N grid composed of 1 x 1 squares, each 1 x 1 square consists of a /, \, or blank space.  These characters divide the square into contiguous regions.

(Note that backslash characters are escaped, so a \ is represented as "\\".)

Return the number of regions.

 

Example 1:

Input:
[
  " /",
  "/ "
]
Output: 2
Explanation: The 2x2 grid is as follows:

Example 2:

Input:
[
  " /",
  "  "
]
Output: 1
Explanation: The 2x2 grid is as follows:

Example 3:

Input:
[
  "\\/",
  "/\\"
]
Output: 4
Explanation: (Recall that because \ characters are escaped, "\\/" refers to \/, and "/\\" refers to /\.)
The 2x2 grid is as follows:

Example 4:

Input:
[
  "/\\",
  "\\/"
]
Output: 5
Explanation: (Recall that because \ characters are escaped, "/\\" refers to /\, and "\\/" refers to \/.)
The 2x2 grid is as follows:

Example 5:

Input:
[
  "//",
  "/ "
]
Output: 3
Explanation: The 2x2 grid is as follows:

 

Note:

1 <= grid.length == grid[0].length <= 30
grid[i][j] is either '/', '\', or ' '.
*/

import java.util.*;

class Solution {
    boolean[][][] visited;
    String[] matrix;
    int height;
    int width;

    boolean inside(int r, int c) {
        return (r >= 0 && r < height && c >= 0 && c < width);
    }

    void dfs(int r, int c, int type) {
        if (!inside(r, c) || visited[r][c][type])
            return;

        visited[r][c][type] = true;
        // connect to different-grid
        switch (type) {
            case 0:
                dfs(r - 1, c, 2);
            case 1:
                dfs(r, c + 1, 3);
            case 2:
                dfs(r + 1, c, 0);
            case 3:
                dfs(r, c - 1, 1);
        }

        // connect in same-grid
        if (matrix[r].charAt(c) != '/')
            dfs(r, c, type ^ 1);

        if (matrix[r].charAt(c) != '\\')
            dfs(r, c, type ^ 3);
    }

    public int regionsBySlashes(String[] grid) {
        height = grid.length;
        width = grid[0].length();
        visited = new boolean[31][31][4];
        matrix = grid;

        int region = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                for (int type = 0; type < 4; type++) {
                    if (!visited[height][width][type]) {
                        dfs(i, j, type);
                        region++;
                    }
                }
            }
        }

        return region;
    }
}

class Driver {
    public static void main(String[] args) {
        Solution sol = new Solution();

        String[] grid = { " /", "/ " };

        System.out.println(sol.regionsBySlashes(grid));
    }
}