/*
Matching with Shape Contexts
Fernanda Nava Moya - A01023896
30/11/2021
*/

#include <bits/stdc++.h>

using namespace std;

// class of Points of figure
class Point {
public:
    // x-axis and y-axis coordenates of point
    int x, y;
    // class inizializers
    Point(int x, int y){
        this->x = x;
        this->y = y;
    }
    Point(){}
};

// class for Segment of log-polar histogram
class Segment {
public:
    Point p1, p2; // pionts
    float distance, angule; // distance and angule of segments
    // class inizializers
    Segment(Point p1, Point p2, float d, float a){
        this->p1 = p1;
        this->p2 = p2;
        distance = d;
        angule = a;
    }
    Segment(){}
};

// pythagoren method
float pythagoras (Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) * 1.0);
};

// get angule of a truangule using trigonometry
float getAngle (Point p1, Point p2) {
    // get angle
    float angle = atan2(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI;
    // if the angle is less than 0 then add 360 degrees to it
    if (angle<0)
        angle += 360;
    return angle;
}

int main(int argc, char *argv[]) {
    // get number of points
    int num = stoi(argv[1]);
    // vector where we are going to store the points
    vector<Point> points;
    // vector of x-axis and y-axis of points
    vector<int> x,y;

    int counter = 1;
    // get x-axis values
    for(int i = 2; i < num + 2; i++) {
        counter++;
        x.push_back(stoi(argv[i]));
    }
    // get y-axis values
    for(int i = 2; i < num + 2; i++) {
        counter++;
        y.push_back(stoi(argv[counter]));
    }
    // create points and add then to 'points' vector
    for (int i = 0; i < num; i++)
        points.push_back(Point(x[i],y[i]));


    for (int i = 0; i< num; i++) {
        // vector of points 
        vector<Point> temp = points;
        // first point 
        Point firstPoint = points[i];

        // substract the first piont to all the points in the vector temp
        for(auto &it : temp) {
            it.x -= firstPoint.x;
            it.y -= firstPoint.y;
        }

        // vector of segments
        vector<Segment> segments;

        for (auto it : temp) {
            // get ditance and angule between current point and i-th point in temp
            float distance = pythagoras(temp[i], it);
            float angule = getAngle(temp[i], it);
            // add a segment to vector segments between the two points and 
            // the distance and angule between both points
            if(distance > 0 && distance < 10)
                segments.push_back(Segment(temp[i], it, distance, angule));
            else // if is the same point then it continues
                continue;
        }

        // vector of vector where we're add 1 if there is a point in that position
        vector<vector<int>> solution(5,vector<int>(12,0)); // inicialize vector of vectors

        // iterate segments
        for (auto it : segments) {
            int bin = floor (it.angule/30);
            int radius = floor(it.distance/2);
            solution[radius][bin] += 1; // add 1 to that position
        } 

        // iterate through solution vector
        for (int i = 0; i < 5; i++) {
            // iterate through vector in solution vector
            for (int j = 0; j < 12; j++) 
                cout << solution[i][j] << " "; // print matrix
            cout<<endl;        
        }
        cout <<endl;
    }    
}