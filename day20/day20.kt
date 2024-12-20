import java.io.File

data class Point(val x: Int, val y: Int)
val dirs = listOf(
    Point(0, -1),
    Point(1, 0),
    Point(0, 1),
    Point(-1, 0)
)
fun main() {
    val grid: MutableList<String> = mutableListOf()
    var start = Point(-1, -1)
    File("day20/input.txt").readLines().forEachIndexed() { index, it ->
        grid.add(it)
        if (it.indexOf('S') >= 0) {
            start = Point(it.indexOf('S'), index)
            println("start: $start")
        }

        if (it.indexOf('E') >= 0) {
            println("end:   ${Point(it.indexOf('E'), index)}")
        }
    }
    val score = findPath(start, grid)
    val cheats = findCheats(start, grid)
    val saves = mutableMapOf<Int, Int>()
    println("shortest path: $score")
    println("total cheats:  ${cheats.size}")
    println()
    for (c in cheats) {
        val gridCopy = grid.toMutableList()
        gridCopy[c.y] = gridCopy[c.y].replaceRange(c.x, c.x+1, ".")
        val path = findPath(start, gridCopy)
        if (path < score) {
            saves[score-path] = saves.getOrDefault(score-path, 0) + 1
        }
    }

    // part 1
    println(saves.keys.fold(0) { acc, key ->
        if (key >= 100) acc+saves[key]!!
        else acc
    })
}

fun findCheats(start: Point, grid: List<String>): List<Point> {
    val q = mutableListOf(listOf(0, start.x, start.y))
    val seen = mutableSetOf<Point>()
    val cheats = mutableSetOf<Point>()
    while (q.isNotEmpty()) {
        val (i,x,y) = q.removeFirst()
        if (Point(x,y) in seen || grid[y][x] == 'E')
            continue
        seen.add(Point(x,y))
        for ((dx, dy) in dirs) {
            if (grid[y+dy][x+dx] != '#')
                q.add(listOf(i+1, x+dx, y+dy))
            else if (y+(dy*2) in grid.indices && x+(dx*2) in grid.indices && grid[y+(dy*2)][x+(dx*2)] != '#') {
                cheats.add(Point(x+dx, y+dy))
                q.add(listOf(i+2, x+(dx*2), y+(dy*2)))
            }
        }
    }
    return cheats.toList()
}

fun findPath(start: Point, grid: List<String>): Int {
    val q = mutableListOf(listOf(0, start.x, start.y))
    val seen = mutableSetOf<Point>()
    while (q.isNotEmpty()) {
        val (i,x,y) = q.removeFirst()
        if (grid[y][x] == 'E')
            return i
        if (Point(x,y) in seen)
            continue
        seen.add(Point(x,y))
        for ((dx, dy) in dirs) {
            if (grid[y+dy][x+dx] != '#')
                q.add(listOf(i+1, x+dx, y+dy))
        }
    }
    return 0
}
