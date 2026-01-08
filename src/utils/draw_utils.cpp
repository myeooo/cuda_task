
#ifndef DRAW_UTILS_H
#define DRAW_UTILS_H

#include "draw_utils.h"
#include <GL/glew.h>
#include <cmath>
namespace DrawUtils {

void drawCircle(float centerX, float centerY, float radius) {
    int segments = 64; // càng cao càng mượt
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; i++) {
        float theta = (2.0f * 3.1415926f * float(i)) / float(segments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex3f(centerX + x, centerY + y, 0.0f);
    }
    glEnd();
}
}
#endif
