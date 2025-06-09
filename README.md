# FindNeighbors

If you have a set of 2 dimensional coordinates, how do you find its N nearest neighbors? This project is for looking at different ideas and hopefully profiling them.

## Option 1
The simple way would be to check against every other point. And what if you need to find the nearest neighbors for _every_ point? This method gets slow fast, but it's simple to implement and can be used as a baseline.

## Option 2
Another option is to maintain a grid of 'bins'. Each bin holds its points. This gives us a way to reduce where we are searching. If we want the nearest 10 points to point x we first search the point's bin. If we need more points we search all adjacent bins. If still more are needed, we again look to the next layer of bins, etc.

## Options 3
Another way I've thought to search is by defining the search area with a crosshair. Instead of maintaining a whole grid of bins, we can just maintain 2 sorted lists of the points: one sorted by x-coordinate, and the other by y-coordinate. When searching for some nearest neighbors we can search outward from the coordinates of the point in question.

I expect this option is particularly useful when searching for all points within a certain distance of another point, instead of the nearest neighbors. It allows us to define the box to search in: if looking for all points within a distance of 15, there's no need to look at points with an x || y distance > 15

#TODO: results,plots