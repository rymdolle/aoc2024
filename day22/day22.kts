import java.io.File
File("input.txt").readLines().sumOf {
    var secret = it.toLong()
    for (i in 0 until 2000) {
        secret = ((secret * 64) xor secret) % 16777216
        secret = ((secret / 32) xor secret) % 16777216
        secret = ((secret * 2048) xor secret) % 16777216
    }
    secret
}