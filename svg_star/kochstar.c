#include <stdio.h>
#include <cmath.h>

void drawLine(double x1, double y1, double x2, double y2)
{
    printf("M%d,%d L%d,%d ", x1, y1, x2, y2);
}

void kochStar(double x1, double y1, double x2, double y2, int depth)
{
    if (depth == 0)
    {
        drawLine(x1, y1, x2, y2);
    }
    else
    {
        double length = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        // double deltaX = x2 - x1;
        // double deltaY = y2 - y1;

        // double newX = x1 + deltaX / 3;
        // double newY = y1 + deltaY / 3;

        // double x3 = newX + (deltaX / 6) + (deltaY * 0.577);
        // double y3 = newY + (deltaY / 6) - (deltaX * 0.577);

        // double x4 = x1 + 2 * deltaX / 3;
        // double y4 = y1 + 2 * deltaY / 3;

        kochStar(x1, y1, newX, newY, depth - 1);
        kochStar(newX, newY, x3, y3, depth - 1);
        kochStar(x3, y3, x4, y4, depth - 1);
        kochStar(x4, y4, x2, y2, depth - 1);
    }
}

int main()
{
    int width = 500;
    int height = 500;
    int depth = 4;

    printf("<?xml version=\"1.0\"?>\n"
           "<svg version=\"1.1\" width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\">\n"
           "<path fill=\"none\" stroke=\"blue\" d=\"",
           width, height);

    kochStar(width / 2 - 100, height / 2 + 50, width / 2 + 100, height / 2 + 50, depth);
    kochStar(width / 2 + 100, height / 2 + 50, width / 2, height / 2 - 100, depth);
    kochStar(width / 2, height / 2 - 100, width / 2 - 100, height / 2 + 50, depth);

    printf("\"/>\n</svg>\n");

    return 0;
}
