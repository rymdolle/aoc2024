import java.io.File

data class Point(val x: Int, val y: Int)
data class Tile(val score: Int, var direction: Int, var pos: Point, val path: MutableList<Point>)
val grid: List<String> = File("input.txt").readLines()
val start = grid.fold(Point(0, 0)) { start, row ->
    row.indexOf('S').let { x ->
        if (x == -1)
            start
        else
            Point(x, grid.indexOf(row))
    }
}

val paths = findPaths(start, grid).sortedBy { it.score }
val best = paths.first()
val seats = paths.filter { it.score == best.score }.map { it.path }.flatten().toSet()

println(best.score)
println(seats.size)

fun findPaths(start: Point, grid: List<String>): List<Tile> {
    val dirs = listOf(
        Point(0, -1),// up
        Point(1, 0), // right
        Point(0, 1), // down
        Point(-1,0)  // left
    )

    val q = mutableListOf(Tile(0, 1, start, mutableListOf()))
    val seen = mutableMapOf<Point, Int>()
    val paths: MutableList<Tile> = mutableListOf()
    while (q.isNotEmpty()) {
        val (score,direction,pos,path) = q.removeFirst()
        val (x,y) = pos
        if (grid[y][x] == 'E') {
            path.add(Point(x, y))
            paths.add(Tile(score,direction,pos,path.toMutableList()))
            continue
        }

        // if we are more than one turn away, skip
        if (pos in seen && score-1001 >= seen[pos]!!)
            continue
        seen[pos] = score
        for ((index, dir) in dirs.withIndex()) {
            val (dx, dy) = dir
            val next = Point(x+dx, y+dy)
            if (next in path)
                continue
            if (next.x !in grid[0].indices || next.y !in grid.indices)
                continue
            if (grid[next.y][next.x] != '#') {
                path.add(Point(x, y))
                val nextScore = score + if (direction == index) 1 else 1001
                q.add(Tile(nextScore, index, next, path.toMutableList()))
            }
        }
    }
    return paths.toList()
}
