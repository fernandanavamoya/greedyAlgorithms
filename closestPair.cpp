/*
CLOSEST PAIR PROBLEM 
Given n points in the plane, find a pair of points with the smallest
Euclidean distance between them. 
*/

#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

bool sortByX (const vector<int>& a, const vector<int>& b) {
    return a[0] < b[0];
}


float smallestDistance(vector<vector<int>> points) {
    //Pythagorean Theorem --> distance = ((x2 - x1)^2 + (y2 - y1)^2)^(1/2)
    tuple<vector<int>, vector<int>, float> smallest; 
    float distance = 0.0;

    for (int i; i < points.size(); i++) {
        float distance_i = sqrt(pow(points[i + 1][1] - points[i][1], 2) + pow(points[i + 1][2] - points[i][2], 2) * 1.0);
        
        if (distance_i < distance) distance = distance_i;
    }

    return distance;
}


//point = [[x0, y0], [x1, y1], ...]
vector<vector<int>> closestPair(vector<vector<int>> points) {
    //Sort by x-axis
    sort(points.begin(), points.end(), sortByX);

    //Line L, where half the point are on each side of the line
    vector<vector<int>> left, right;
    int half = points.size() / 2;
    int count = 0;
    float delta;

    //Add points in left and right side
    for (int i = 0; i < points.size(); i++) {
        if(count < half) {
            right.push_back(points[i]);
            count++;
        }
        else {
            left.push_back(points[i]);
            count++;
        }
    }

    //Get the smallest distance in both left and right, and the minumun distance from does two
    delta = min(smallestDistance(right), smallestDistance(left));

    for (int i = 0; )

    float stripClosest(Point strip[], int size, float d)
    {
        float min = d; // Initialize the minimum distance as d
    
        qsort(strip, size, sizeof(Point), compareY);
    
        // Pick all points one by one and try the next points till the difference
        // between y coordinates is smaller than d.
        // This is a proven fact that this loop runs at most 6 times
        for (int i = 0; i < size; ++i)
            for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j)
                if (dist(strip[i],strip[j]) < min)
                    min = dist(strip[i], strip[j]);
    
        return min;
    }
 
}