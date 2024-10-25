#include <vector>
#include <cmath>
#include <limits>
#include <utility>
#include <iostream>
using namespace std;


// Structure to represent a 2D point
struct Point {
    float x, y;
};

// Function to calculate Euclidean distance between two points
float distance(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Function to find the closest pair of points
std::pair<Point, Point> closestPair(const std::vector<Point>& points) {
    if (points.size() < 2) {
       //std::cout<<"At least two points required \n";
    }

    std::pair<Point, Point> closestPoints = {points[0], points[1]};
    float minDistance = distance(points[0], points[1]);

    for (int i = 0; i < points.size(); ++i) {
        for (int j = i + 1; j < points.size(); ++j) {
            float dist = distance(points[i], points[j]);
            if (dist < minDistance) {
                minDistance = dist;
                closestPoints = {points[i], points[j]};
            }
        }
    }

    return closestPoints;
}

// Example usage:
int main() {
    std::vector<Point> points = {{1.0, 1.0}, {2.0, 2.1}, {1.0, 2.0}, {2.0, 3.0}, {4.0, 4.1}};
        std::pair<Point, Point> closestPoints = closestPair(points);
        std::cout << "Closest points: (" << closestPoints.first.x << ", " << closestPoints.first.y << "), ("
                  << closestPoints.second.x << ", " << closestPoints.second.y << ")" << std::endl;
    return 0;
}
