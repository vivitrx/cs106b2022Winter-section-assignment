#include "Sierpinski.h"
#include "error.h"
using namespace std;

/**
 * Draws a triangle with the specified corners in the specified window. Feel free
 * to edit this function as you see fit to change things like color, fill style,
 * etc. in whatever way you'd like!
 *
 * @param window The window in which to draw the triangle.
 * @param x0 y0 The first corner of the triangle.
 * @param x1 y1 The second corner of the triangle.
 * @param x2 y2 The third corner of the triangle.
 */
void drawTriangle(GWindow& window,
                  double x0, double y0,
                  double x1, double y1,
                  double x2, double y2) {
    window.setColor("black");
    window.fillPolygon({ x0, y0, x1, y1, x2, y2 });
}


void drawSierpinskiTriangle(GWindow& window,
                  double x0, double y0,
                  double x1, double y1,
                  double x2, double y2,
                  int order)
{
    // error case
    if (order < 0)
    {
        error("不要输入小于0的order");
    }
    // base case
    if (order == 0)
    {
        drawTriangle(window,
                     x0, y0,
                     x1, y1,
                     x2, y2);
        return;
    }

    // 得到1阶谢尔宾斯基三角形的组件 /////////
    // p0 与 p1的中点 pc0
    double xc0 = (x0 + x1) / 2;
    double yc0 = (y0 + y1) / 2;

    // p1 与 p2的中点 pc1
    double xc1 = (x1 + x2) / 2;
    double yc1 = (y1 + y2) / 2;

    // p0 与 p2的中点 pc2
    double xc2 = (x0 + x2) / 2;
    double yc2 = (y0 + y2) / 2;
    // 得到1阶谢尔宾斯基三角形的组件 /////////

    int new_order = order - 1;
    drawSierpinskiTriangle(window,
                           x0,  y0,
                           xc0,  yc0,
                           xc2,  yc2,
                           new_order);
    drawSierpinskiTriangle(window,
                           xc0,  yc0,
                           x1,  y1,
                           xc1,  yc1,
                           new_order);
    drawSierpinskiTriangle(window,
                           xc2,  yc2,
                           xc1,  yc1,
                           x2,  y2,
                           new_order);
}

// 2024年5月26日17:38:50 完成！








