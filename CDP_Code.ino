#include <Pixy2.h>
Pixy2 pixy;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pixy.init();
  pixy.setLamp(1, 1);
}

boolean hasRun = false;
char grid[11][11] = {

  { '*', '*', '*', '*', '*', '*', 'N', '*', '*', '*', '*' },

  { '*', '0', '*', '0', '*', '0', '*', '0', '*', '0', '*' },

  { '*', '*', 'G', '*', '*', '*', '*', '*', '*', '*', '*' },

  { '*', '0', '*', '0', '*', '0', '*', '0', '*', '0', '*' },

  { '*', '*', '*', '*', '*', '*', '*', '*', 'N', '*', '*' },

  { '*', '0', '*', '0', '*', '0', '*', '0', '*', '0', '*' },

  { 'B', '*', 'G', '*', '*', '*', 'G', '*', '*', '*', 'R' },

  { '*', '0', '*', '0', '*', '0', '*', '0', '*', '0', '*' },

  { '*', '*', '*', '*', 'N', '*', '*', '*', '*', '*', '*' },

  { '*', '0', '*', '0', '*', '0', '*', '0', '*', '0', '*' },

  { '*', '*', 's', '*', '*', '*', '*', '*', '*', '*', '*' },

};
//N = Blue, G= Red
void loop() {
  int x, y;
  // put your main code here, to run repeatedly:
  if (hasRun == false)
  {

    grid1();

    for (y = 0; y < 11; ++y)
    {
      Serial.println("");
      for (x = 0; x < 11; ++x)
      {
        Serial.print( grid[y][x]);
        Serial.print("|");
      }
    }

  }
  hasRun = true;
}

int grid1()
{
  int i, sig, j = 0, k = 0;
  int RedBalls[2][3] = {};
  int BlueBalls[2][3] = {};
  // grab blocks!
  int x, y;

  for (y = 0; y < 11; ++y)
  {
    Serial.println("");
    for (x = 0; x < 11; ++x)
    {
      Serial.print( grid[y][x]);
      Serial.print("|");
    }
  }
  Serial.println("");
  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks)
  {
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i = 2; i < pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
      sig = pixy.ccc.blocks[i].m_signature;
      if (sig == 1)
      {

        RedBalls[0][j] = pixy.ccc.blocks[i].m_x;
        RedBalls[1][j] = pixy.ccc.blocks[i].m_y;
        j++;
      }
      else if (sig == 2)
      {

        BlueBalls[0][k] = pixy.ccc.blocks[i].m_x;
        BlueBalls[1][k] = pixy.ccc.blocks[i].m_y;
        k++;
      }
    }
  }
  for (i = 0; i < 3; i++)
  {
    Serial.print("  BlueBalls: ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(BlueBalls[0][i]);
    Serial.print(" ");
    Serial.println(BlueBalls[1][i]);
    Serial.print("  RedBalls: ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.print(RedBalls[0][i]);
    Serial.print(" ");
    Serial.println(RedBalls[1][i]);
  }


  int xpixel, ypixel, xloc, yloc, xpixel1, ypixel1 = 0;
  int xaxis[2][6] = { { 85, 115, 145, 175, 205, 235},
    { 1,  2,   3,   4,   5,   6 }
  };
  int yaxis[2][6] = { { 175, 145, 115, 85, 55, 25},
    { 7,  8,   9,   11, 13,  17 }
  };
  int axismatch[3][36] = {
    {  7, 14, 21,28,  35, 42, 8,16, 24, 32, 40, 48, 9, 18, 27, 36, 45, 54, 11, 22, 33, 44, 55, 66, 13, 26, 39, 52, 65, 78, 17, 34, 51, 68, 85, 102 },
    { 10, 10, 10, 10, 10, 10, 8, 8,  8,  8,  8,  8, 6,  6,  6,  6,  6,  6,  4,  4,  4,  4,  4,  4,  2,  2,  2,  2,  2,  2,  0,  0,  0,  0,  0,   0 },
    {  0,  2,  4, 6,   8, 10, 0, 2,  4,  6,  8, 10, 0,  2,  4,  6,  8, 10,  0,  2,  4,  6,  8, 10,  0,  2,  4,  6,  8, 10,  0,  2,  4,  6,  8,  10 },
  };
  //xpixel= pixy.ccc.blocks[i].m_x;
  // ypixel= pixy.ccc.blocks[i].m_y;
  // cin >> xpixel >> ypixel;

  for (int n = 0; n < 3; n++)
  {
    xpixel = RedBalls[0][n];
    ypixel = RedBalls[1][n];
    for (int i = 0; i < 6; i++)
    {
      if (xpixel >= xaxis[0][i] && xpixel <= (xaxis[0][i] + 29))
      {
        //   cout << xaxis[1][i]<< endl;
        xloc = xaxis[1][i];
        //        Serial.print("  Rxloc ");
        //        Serial.print(i);
        //        Serial.print(" :");
        //        Serial.println(xloc);
      }
    }

    for (int i = 0; i < 6; i++)
    {
      if (ypixel >= yaxis[0][i] && ypixel <= (yaxis[0][i] + 29))
      {
        //   cout << yaxis[1][i] << endl;
        yloc = yaxis[1][i];
        //        Serial.print("  Ryloc ");
        //        Serial.print(i);
        //        Serial.print(" :");
        //        Serial.println(yloc);
      }
    }

    for (int i = 0; i <= 35; i++)
    {
      if ((xloc * yloc == axismatch[0][i]))
      {
        Serial.print("  beforeRGridaxismatch: ");
        Serial.print(i);
        Serial.print(" :");
        Serial.println(grid[axismatch[1][i]][axismatch[2][i]]);
        grid[axismatch[1][i]][axismatch[2][i]] = 'r';
        //        Serial.print("  Raxismatch: ");
        //        Serial.print(i);
        //        Serial.print(" :");
        //        Serial.println(axismatch[1][i]);
        //        Serial.println(axismatch[2][i]);
        // cout << axismatch[1][i] << axismatch[2][i] << endl;
        Serial.print("  RGridaxismatch: ");
        Serial.print(i);
        Serial.print(" :");
        Serial.println(grid[axismatch[1][i]][axismatch[2][i]]);
      }
    }
  }

  for (int n = 0; n < 3; n++)
  {
    xpixel1 = BlueBalls[0][n];
    ypixel1 = BlueBalls[1][n];
    for (int i = 0; i < 6; i++)
    {
      if (xpixel1 >= xaxis[0][i] && xpixel1 <= (xaxis[0][i] + 29))
      {
        //   cout << xaxis[1][i]<< endl;
        xloc = xaxis[1][i];
        //        Serial.print("  Bxloc: ");
        //        Serial.print(i);
        //        Serial.print(" :");
        //        Serial.println(xloc);
      }
    }

    for (int i = 0; i < 6; i++)
    {
      if (ypixel1 >= yaxis[0][i] && ypixel1 <= (yaxis[0][i] + 29))
      {
        //   cout << yaxis[1][i] << endl;
        yloc = yaxis[1][i];
        //        Serial.print("  Byloc: ");
        //        Serial.print(i);
        //        Serial.print(" :");
        //        Serial.println(yloc);
      }
    }

    for (int i = 0; i <= 35; i++)
    {
      if ((xloc * yloc == axismatch[0][i]))
      {
        // cout << axismatch[1][i] << axismatch[2][i] << endl;
        Serial.print("  beforeBGridaxismatch: ");
        Serial.print(i);
        Serial.print(" :");
        Serial.println(grid[axismatch[1][i]][axismatch[2][i]]);
        grid[axismatch[1][i]][axismatch[2][i]] = 'b';
        //        Serial.print("  Baxismatch: ");
        //        Serial.print(i);
        //        Serial.print(" :");
        //        Serial.println(axismatch[1][i]);
        //        Serial.println(axismatch[2][i]);
        Serial.print("  BGridaxismatch: ");
        Serial.print(i);
        Serial.print(" :");
        Serial.println(grid[axismatch[1][i]][axismatch[2][i]]);
        xloc = yloc = 0;
      }
    }
  }

  //cout << minDistance(grid);
  //cout << grid;


  return 0;
}
////  0=White area, *=black line, r=Red Ball, b=Blue Ball, R=Red Drop-off, B=Blue Drop-off, s=Start
