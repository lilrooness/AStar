import math

a = [
   0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,
   0,1,1,1,0,0,0,0,0,0,
   0,1,0,0,1,0,0,0,0,0,
   0,1,0,0,0,1,0,0,0,0,
   0,0,0,0,0,0,1,0,0,0,
   0,0,0,1,1,1,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,
   0,0,0,0,0,0,0,0,0,0,
]

startx  = 2
starty = 4

targetx = 5
targety = 3

mapWidth = 10
mapHeight = 10

def findpath(sx, sy, tx, ty, tilemap, xMax, yMax):
    closed = [False for x in range(len(tilemap))]
    opened = [False for x in range(len(tilemap))]
    closed[getIndex(sx, sy, xMax)] = True

    hVals = [0 for x in range(len(tilemap))]
    # hVals[getIndex(sx, sy, xMax)] = 0
    gVals = [0 for x in range(len(tilemap))]
    parents = [-1 for x in range(len(tilemap))]
    fVals = [0 for x in range(len(tilemap))]

    currX = sx
    currY = sy

    while currX != tx or currY != ty:
        currNode = int(getIndex(currX, currY, xMax))
        # close current node
        closed[currNode] = True
        opened[currNode] = False

        # find new nodes
        newOpened = getNewOpenNodes(opened, closed, currX, currY, tilemap, xMax, yMax)
        for x in newOpened:
            parents[x] = getNewParentValue(currNode, x, gVals, parents)
            gVals[x] = getNewGVal(currNode, x, gVals, parents)
            hVals[x] = getHVal(x, getIndex(tx, ty, xMax), tilemap, xMax)
            fVals[x] = gVals[x] + hVals[x]
            opened[x] = True

        # now choose next currNode
        # currX, currY = indexToXY(min([fVals[i] for i in range(len(opened)) if opened[i] == True]), xMax)
        openedIndexes = [(i, fVals[i]) for i in range(len(opened)) if opened[i] == True]
        smallesedFVal = (-1, -1)
        for openIndex in openedIndexes:
          if smallesedFVal[0] == -1:
            smallesedFVal = (openIndex[0], openIndex[1])
          else:
            if smallesedFVal[1] > openIndex[1]:
              smallesedFVal = (openIndex[0], openIndex[1])

        currX, currY = indexToXY(smallesedFVal[0], xMax)


    path = []
    targetNode = getIndex(tx, ty, xMax)
    startNode = getIndex(sx, sy, xMax)
    currNode = targetNode

    while currNode != startNode:
      path.append(parents[currNode])
      currNode = parents[currNode]

    return path
    # return parents


def getHVal(node, targetNode, tilemap, xMax):
  return nodeDist(node, targetNode, xMax)

def getNewGVal(currNode, targetNode, gVals, parents):
  if parents[targetNode] == currNode:
    return gVals[currNode] + 10
  else:
    return gVals[targetNode]

def getNewParentValue(currNode, targetNode, gVals, parents):
  if(parents[targetNode] == -1):
    return currNode

  if(parents[targetNode] != currNode):
    if gVals[targetNode] > gVals[currNode] + 10:
      return currNode
    else:
      # dont change the parent in this case
      return parents[targetNode]

  # target node's parent is already the current node 
  return currNode

def getNewOpenNodes(opened, closed, currX, currY, tilemap, xMax, yMax):
    new = []
    if currX + 1 < xMax and testIfNodeIsNew(getIndex(currX + 1, currY, xMax), tilemap, xMax, yMax, opened, closed):
        new.append(getIndex(currX + 1, currY, xMax))
    if currX - 1 > -1 and testIfNodeIsNew(getIndex(currX - 1, currY, xMax), tilemap, xMax, yMax, opened, closed):
        new.append(getIndex(currX - 1, currY, xMax))

    if currY < yMax and testIfNodeIsNew(getIndex(currX, currY + 1, xMax), tilemap, xMax, yMax, opened, closed):
        new.append(getIndex(currX, currY + 1, xMax))
    if currY > -1 and testIfNodeIsNew(getIndex(currX, currY - 1, xMax), tilemap, xMax, yMax, opened, closed):
        new.append(getIndex(currX, currY - 1, xMax))

    return new

def testIfNodeIsNew(newNode, tilemap, xMax, yMax, opened, closed):
    x, y = indexToXY(newNode, xMax)
    if x < xMax and y < yMax and x > -1 and y > -1:
        if closed[newNode] == False and tilemap[newNode] == 0:
            return True
    return False

def hVal(i, tilemap, xMax):
    x, y = indexToXY(i, xMax)

def indexToXY(i, xMax):
    x = i % xMax
    y = int(math.ceil(i/xMax))
    return (x, y)

def nodeDist(i, j, xMax):
  ix, iy = indexToXY(i, xMax)
  jx, jy = indexToXY(j, xMax)
  return dist(ix, iy, jx, jy)

#manhatten distance
def dist(sx, sy, tx, ty):
    return abs(sx - tx) + abs(sy - ty)

def getIndex(x, y, xMax):
    return x + (y * xMax)

def getMinIndex(a):
  minIndex = -1
  minVal = -1
  for i in range(len(a)):
    if minIndex == -1:
      minIndex = i
      minVal = a[i]
    else:
      if a[i] < a[minIndex]:
        minIndex = i
        minVal = a[i]

  return minIndex

path = findpath(startx, starty, targetx, targety, a, mapWidth, mapHeight)

lineString = []
counter = 0
for i in range(len(a)):
  if counter == mapWidth:
    counter = 0
    print(",".join(lineString))
    lineString = []

  counter = counter + 1
  if i in path:
    lineString.append("#")
  elif a[i] == 1:
    lineString.append("1")
  else:
    lineString.append("0")
