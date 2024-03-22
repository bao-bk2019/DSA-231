#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

class Point
{
public:
    int x, y;
    Point(int x = 0, int y = 0)
    {
        this->x = x;
        this->y = y;
    }
    void display()
    {
        cout << "(" << x << ", " << y << ")";
    }

    double Euclidean_distance(Point &des_point)
    {
        return sqrt(pow(this->x - des_point.x, 2) + pow(this->y - des_point.y, 2));
    }
};
void closestKPoints(Point points[], int n, Point &des_point, int k)
{
    vector<double> distance;
    for (size_t i = 0; i < n; i++)
    {

        distance.push_back(points[i].Euclidean_distance(des_point));
    }
    vector<pair<Point, double>> pairs;
    for (size_t i = 0; i < n; i++)
    {
        pairs.push_back(make_pair(points[i], distance[i]));
    }
    sort(pairs.begin(), pairs.end(), [](const pair<Point, double> &a, const pair<Point, double> &b)
         {
             return a.second < b.second; // Sắp xếp theo distance
         });
    for (size_t i = 0; i < k; i++)
    {
        pairs[i].first.display();
    }
}
int main()
{
    Point points[] = {{3, 3}, {5, -1}, {-2, 4}};
    int n = sizeof(points) / sizeof(points[0]);
    int k = 2;
    Point des_point = {0, 2};
    closestKPoints(points, n, des_point, k);
    //(-2, 4)
    //(3, 3)
}