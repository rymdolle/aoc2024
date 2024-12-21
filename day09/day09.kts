import java.io.File

val records = mutableListOf<Int>()
val spaces = mutableListOf<Int>()
val data = File("input.txt").readText().trim()
for (i in data.indices) {
    if (i % 2 == 0)
        records.add(data[i].digitToInt())
    else
        spaces.add(data[i].digitToInt())
}

val part1 = part1(records, spaces)
val part2 = part2(records, spaces)
println(part1)
println(part2)

fun part1(records: List<Int>, spaces: List<Int>): Long {
    var index = 0
    var part1: Long = 0
    val copy = records.toMutableList()
    for (id in records.indices) {
        for (i in 0 until copy[id]) {
            part1 += id * index
            index++
        }
        copy[id] = 0
        if (id >= spaces.size)
            continue
        val s = spaces[id]
        for (i in 0 until s) {
            for (r in records.indices.reversed()) {
                if (copy[r] > 0) {
                    part1 += r * (index + i)
                    copy[r]--
                    break
                }
            }
        }
        index += s
    }
    return part1
}

fun part2(records: List<Int>, spaces: List<Int>): Long {
    var index = 0
    var part2: Long = 0
    val copy = records.toMutableList()
    for (id in records.indices) {
        for (i in 0 until copy[id]) {
            part2 += id * (index+i)
        }
        index += records[id]
        copy[id] = 0
        if (id >= spaces.size)
            continue
        var space = spaces[id]
        for (rid in records.indices.reversed()) {
            if (copy[rid] in 1..space) {
                for (i in 0 until copy[rid]) {
                    part2 += rid * (index+i)
                }
                space -= copy[rid]
                index += copy[rid]
                copy[rid] = 0
            }
            if (space == 0)
                break
        }
        index += space
    }
    return part2
}
