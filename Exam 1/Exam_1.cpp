#include <math.h>
#include <iostream>
#include <vector>
#include "TgaImage.h"
#include <algorithm>

using namespace std;

vector<vector<int>> LinePoints(int xa, int ya, int xb, int yb) {
    vector<vector<int>> line;
    int dx = abs(xb - xa);
    int dy = abs(yb - ya);
    int sx = xb >= xa ? 1 : -1;
    int sy = yb >= ya ? 1 : -1;

    if (dy <= dx) {
        int d = (dy << 1) - dx;
        int d1 = dy << 1;
        int d2 = (dy - dx) << 1;
        int x = xa + sx;
        int y = ya;

        line.push_back(vector<int>{xa, ya});
        for (int i = 1; i <= dx; i++, x += sx) {
            if (d > 0) {
                d += d2;
                y += sy;
            }
            else {
                d += d1;
            }
            line.push_back(vector<int>{x, y});
        }
    }
    else {
        int d = (dx << 1) - dy;
        int d1 = dx << 1;
        int d2 = (dx - dy) << 1;
        int x = xa;
        int y = ya + sy;

        line.push_back(vector<int>{xa, ya});
        for (int i = 1; i <= dy; i++, y += sy) {
            if (d > 0) {
                d += d2;
                x += sx;
            }
            else {
                d += d1;
            }
            line.push_back(vector<int>{x, y});
        }
    }
    return line;
}

void draw_triangle(TgaImage& image, vector<int> A, vector<int> B, vector<int> C, uint32_t color) { // Треугольник
    vector<vector<int>> line1 = LinePoints(A[0], A[1], B[0], B[1]);
    vector<vector<int>> line2 = LinePoints(B[0], B[1], C[0], C[1]);
    vector<vector<int>> line3 = LinePoints(C[0], C[1], A[0], A[1]);

    vector<vector<int>> edges;
    edges.insert(edges.end(), line1.begin(), line1.end());
    edges.insert(edges.end(), line2.begin(), line2.end());
    edges.insert(edges.end(), line3.begin(), line3.end());

    int minY = min(A[1], min(B[1], C[1]));
    int maxY = max(A[1], max(B[1], C[1]));

    for (int y = minY; y <= maxY; y++) {
        vector<int> x_coords;
        for (const auto& point : edges) {
            if (point[1] == y) {
                x_coords.push_back(point[0]);
            }
        }
        if (x_coords.size() < 2) continue;

        int minX = *min_element(x_coords.begin(), x_coords.end());
        int maxX = *max_element(x_coords.begin(), x_coords.end());

        for (int x = minX; x <= maxX; x++) {
            image.putPixel(x, y, color);
        }
    }
}

void draw_rectangle(TgaImage& image, vector<int> topLeft, int width, int height, uint32_t color) { // Прямоугольник
    for (int y = topLeft[1]; y <= topLeft[1] + height; y++) {
        for (int x = topLeft[0]; x <= topLeft[0] + width; x++) {
            image.putPixel(x, y, color);
        }
    }
}

void draw_circle(TgaImage& image, vector<int> center, int radius, uint32_t color) { // Окружность
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                image.putPixel(center[0] + x, center[1] + y, color);
            }
        }
    }
}

void draw_rhombus(TgaImage& image, vector<int> center, int radius, uint32_t color) { // Ромб
    vector<int> top = { center[0], center[1] - radius }; 
    vector<int> right = { center[0] + radius, center[1] };
    vector<int> bottom = { center[0], center[1] + radius }; 
    vector<int> left = { center[0] - radius, center[1] }; 

    vector<vector<int>> line1 = LinePoints(top[0], top[1], right[0], right[1]);
    vector<vector<int>> line2 = LinePoints(right[0], right[1], bottom[0], bottom[1]);
    vector<vector<int>> line3 = LinePoints(bottom[0], bottom[1], left[0], left[1]);
    vector<vector<int>> line4 = LinePoints(left[0], left[1], top[0], top[1]);

    for (const auto& point : line1) image.putPixel(point[0], point[1], color);
    for (const auto& point : line2) image.putPixel(point[0], point[1], color);
    for (const auto& point : line3) image.putPixel(point[0], point[1], color);
    for (const auto& point : line4) image.putPixel(point[0], point[1], color);
}

void draw_polygon(TgaImage& image, vector<vector<int>> vertices, uint32_t color) { // Многоугольник
    int n = vertices.size();
    for (int i = 0; i < n; i++) {
        vector<vector<int>> edge = LinePoints(vertices[i][0], vertices[i][1],
            vertices[(i + 1) % n][0], vertices[(i + 1) % n][1]);
        for (const auto& point : edge) {
            image.putPixel(point[0], point[1], color);
        }
    }
}

int main() {
    TgaImage image(512, 512);

    vector<int> A = { 50, 50 };
    vector<int> B = { 200, 50 };
    vector<int> C = { 125, 200 };
    draw_triangle(image, A, B, C, image.rgbToInt(0xFF, 0xFF, 0));

    vector<int> rectTopLeft = { 300, 50 };
    draw_rectangle(image, rectTopLeft, 100, 150, image.rgbToInt(0xFF, 0, 0));

    vector<int> circleCenter = { 100, 400 };
    draw_circle(image, circleCenter, 50, image.rgbToInt(0, 0xFF, 0));

    vector<int> rhombusCenter = { 256, 256 }; 
    int rhombusRadius = 50;
    draw_rhombus(image, rhombusCenter, rhombusRadius, image.rgbToInt(0, 0, 0xFF));

    vector<vector<int>> polygonVertices = { {300, 300}, {350, 400}, {450, 400}, {400, 300} };
    draw_polygon(image, polygonVertices, image.rgbToInt(0xFF, 0xFF, 0xFF));

    image.writeToFile("Exam.tga");
    image.clear();

    return 0;
}
