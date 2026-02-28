pub fn isIsogram(str: []const u8) bool {
    if (str.len == 0) {
        return true;
    }
    var seen: [26]bool = [_]bool{false} ** 26;
    var index: u8 = 0;
    for (str) |c| {
        if ((c < 'a' or c > 'z') and (c < 'A' or c > 'Z')) {
            continue;
        }
        if (c >= 'a' and c <= 'z') {
            index = c - 'a';
        } else {
            index = c - 'A';
        }

        if (seen[index]) {
            return false;
        }
        seen[index] = true;
    }
    return true;
}
