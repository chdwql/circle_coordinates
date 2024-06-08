#define _USE_MATH_DEFINES  // 在包含 math.h 之前定义 _USE_MATH_DEFINES
#include <math.h>

// 或者手动定义 M_PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EARTH_RADIUS 6378137.0
#define NUM_POINTS 360
#define VERSION "1.0"
#define AUTHOR "WANG Qinglin (chd_wql@qq.com)"

// 定义一个结构体来存储地理坐标
typedef struct {
    double lon;
    double lat;
} GeoPoint;

// 计算给定角度和半径下的新地理坐标点
GeoPoint calculate_new_point(double center_lon, double center_lat, double angle, double radius) {
    GeoPoint point;
    double radian_angle = angle * M_PI / 180.0;  // 将角度转换为弧度
    point.lat = center_lat + (radius / EARTH_RADIUS) * (180 / M_PI) * sin(radian_angle);
    point.lon = center_lon + (radius / EARTH_RADIUS) * (180 / M_PI) * cos(radian_angle) / cos(center_lat * M_PI / 180);
    return point;
}

// 显示版本信息
void print_version() {
    printf("circle_coordinates version %s\n", VERSION);
}

// 显示作者信息
void print_author() {
    printf("Author: %s\n", AUTHOR);
}

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "--version") == 0) {
        print_version();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "--author") == 0) {
        print_author();
        return 0;
    }

    if (argc != 5) {
        printf("Usage: %s <center_lon> <center_lat> <radius> <output_file>\n", argv[0]);
        return 1;
    }

    // 圆心坐标
    double center_lon = atof(argv[1]);
    double center_lat = atof(argv[2]);

    // 半径（米）
    double radius = atof(argv[3]) * 1000;

    // 生成圆周上的点
    GeoPoint circle_points[NUM_POINTS];
    for (int i = 0; i < NUM_POINTS; i++) {
        double angle = (360.0 / NUM_POINTS) * i;
        circle_points[i] = calculate_new_point(center_lon, center_lat, angle, radius);
    }

    // 输出结果到文本文件
    FILE *file = fopen(argv[4], "w");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file for writing\n");
        return 1;
    }

    for (int i = 0; i < NUM_POINTS; i++) {
        fprintf(file, "%.6f, %.6f\n", circle_points[i].lon, circle_points[i].lat);
    }

    fclose(file);

    printf("Circle coordinates have been written to %s\n", argv[4]);

    return 0;
}
