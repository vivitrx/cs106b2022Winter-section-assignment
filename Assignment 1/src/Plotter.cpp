#include "Plotter.h"
#include "strlib.h"
using namespace std;
struct last_location{
    double x = 0;
    double y = 0;
};

void runPlotterScript(istream& input) {
    /* TODO: Delete this line and the one after it, then implement this function. */
    int pen_flag = 1; // pen_flag，用于指示pen是否触及纸面，1就是up（抬起）， 0就是down（落下）
    last_location last_locat;
    PenStyle penStyle = {1,"#2e2f30"};

    for (string input_line; getline(input, input_line); )
    {
        Vector<string> split_word = stringSplit(input_line, " ");
        // 吔！六重if！出来！
        if (toUpperCase(split_word[0]) == "PENDOWN")
        {
            pen_flag = 0;
        }else if (toUpperCase(split_word[0]) == "PENUP")
        {
            pen_flag = 1;
        }else if (toUpperCase(split_word[0]) == "MOVEABS")
        {
            if (pen_flag == 0) // pen_flag为0才能执行
            {
                drawLine(last_locat.x,
                         last_locat.y,
                         stringToReal(split_word[1]),
                         stringToReal(split_word[2]),
                         penStyle);
            }
            last_locat.x = stringToReal(split_word[1]); // 不要把这行放入if(pen == 0)里面去，因为有这么一种场景，人家不打算画线，只是想把笔移动到其他位置
            last_locat.y = stringToReal(split_word[2]); // 不要把这行放入if(pen == 0)里面去，因为有这么一种场景，人家不打算画线，只是想把笔移动到其他位置
        }else if (toUpperCase(split_word[0]) == "MOVEREL")
        {
            if (pen_flag == 0) // pen_flag为0才能执行
            {
                drawLine(last_locat.x,
                         last_locat.y,
                         last_locat.x + stringToReal(split_word[1]),
                         last_locat.y + stringToReal(split_word[2]),
                         penStyle);
            }
            last_locat.x = last_locat.x + stringToReal(split_word[1]); // 不要把这行放入if(pen == 0)里面去，因为有这么一种场景，人家不打算画线，只是想把笔移动到其他位置
            last_locat.y = last_locat.y + stringToReal(split_word[2]); // 不要把这行放入if(pen == 0)里面去，因为有这么一种场景，人家不打算画线，只是想把笔移动到其他位置
        }else if (toUpperCase(split_word[0]) == "PENCOLOR")
        {
            penStyle.color = split_word[1];
        }else if (toUpperCase(split_word[0]) == "PENWIDTH")
        {
            penStyle.width = stringToReal(split_word[1]);
        }
    }
}
