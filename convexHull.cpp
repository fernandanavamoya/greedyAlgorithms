/*
Convex Hull's ALGORITHM
Finds the line that completely encloses a set of points in a plane so that there are no concavities in the line.

Fernanda Nava Moya - A01023896
06/11/2021
*/

#include <iostream>
#include <stack>
#include <stdlib.h>
#include <vector>

using namespace std;

// Point constructor
struct Point {
    // accepts the coordinates
	int x, y;
};

// A global point variabl for sorting points with reference to the first point
Point p0;

// function that finds the next to top in a stack
Point nextToTop(stack<Point> &S) {
	Point p = S.top(); // get top of stack
	S.pop(); // update top
	Point res = S.top(); // get new top
	S.push(p); // push original top
	return res; // return new top
}

// function that swaps two points
void swap(Point &p1, Point &p2) {
	Point temp = p1; // save temporarily point 1
	p1 = p2; // swap points point 1
	p2 = temp; // swap point 2
}

// function that returns the square of the distance between p1 and p2
int distSq(Point p1, Point p2) {
    // gets and returnn square of the distance
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}

// function that returns the orentation, clockwise and counterclockwise
int orientation(Point p, Point q, Point r) {
    // get value
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0; // if the value is equal to 0 then it means it's collinear
	return (val > 0)? 1: 2; // if its bigger than zero then it's clockwise, else it's counterclock wise
}

// function that sorts the array of points with respect to the first point
int compare(const void *vp1, const void *vp2) {
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;

    // gets orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

    return (o == 2)? -1: 1;
}

// function that prints convex hull of a set of N points.
void convexHull(Point points[], int num) {
    // gets the bottommost point
    int ymin = points[0].y, min = 0;
    for (int i = 1; i < num; i++) {
        int y = points[i].y;
        // get the bottom-most or chose the left-most point in case of tie
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // swap the bottom-most point to the first position
    swap(points[0], points[min]);
    p0 = points[0];
    // sort points with compare function
    qsort(&points[1], num-1, sizeof(Point), compare);
    // If two or more points make same angle with p0 it'll remove all but the one that is farthest from p0
    int m = 1; // Initialize size of modified array to 1
    for (int i = 1; i < num; i++) {
        // remove 'i' until the angle of 'i' and i+1 is the same as p0
        while (i < num - 1 && orientation(p0, points[i], points[i+1]) == 0)
            i++;
        points[m] = points[i];
        m++; // update size of modified array
    }

    // if the modified array of points is less than 3 points the it means the convex hull is not possible
    if (m < 3) return;

    // empty stack 
    stack<Point> S;
    // push the first three points to it
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // process the remaining num-3 points
    for (int i = 3; i < m; i++) {
        // remove the top until the angle formed by points makes a non-left turn
        while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop(); // remoce point
        S.push(points[i]);
    }

    // print the contents of stack
    while (!S.empty()) {
        Point p = S.top(); // get top
        cout << p.x << " " << p.y << endl; // prints content of stack
        S.pop(); // remove top point
    }
}

int main(int argc, char *argv[])
{
    // get number of vertex
    int num = stoi(argv[1]);

    //create vectors for x-axis and y-axis
    vector<int> x, y;

    int counter = 1;
    //get x-axis coordinates
    for (int i = 2; i < num + 2; i++) {
        counter++;
        x.push_back(stoi(argv[i]));
    }
    //get y-axis coordinates
    for (int i = 2; i < num + 2; i++) {
        counter++;
        y.push_back(stoi(argv[counter]));
    }
    
    // create Point type array of size num
    Point coordinates[num];
    // fill coordinates array with resived coordinates of 'x' and 'y' axis
    for(int i = 0; i < num; i++) {
        coordinates[i] = {x[i],y[i]};
    }

    // get len
    int len = sizeof(coordinates)/sizeof(coordinates[0]);
    // call convexHull funciton
    convexHull(coordinates, len);
    
    return 0;
}
