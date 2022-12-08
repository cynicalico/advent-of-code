use aoc2022::common::read_lines;

fn main() {
    let lines: Vec<String> = match read_lines("res/p4.txt") {
        Ok(v) => v.into_iter().filter_map(|e| e.ok()).collect(),
        Err(e) => panic!("Failed to read input file: {}", e),
    };

    let (p1_ans, p2_ans) = lines.iter().fold((0, 0), |(p1_tot, p2_tot), l| {
        let l: Vec<&str> = l.split(',').collect();
        let r1: Vec<i32> = l[0].split('-').map(|e| e.parse().unwrap()).collect();
        let r2: Vec<i32> = l[1].split('-').map(|e| e.parse().unwrap()).collect();

        let contains = (r1[0] <= r2[0] && r1[1] >= r2[1]) || (r2[0] <= r1[0] && r2[1] >= r1[1]);
        let overlaps = contains
            || (r1[0] < r2[0] && r1[1] >= r2[0] && r1[1] < r2[1])
            || (r2[0] < r1[0] && r2[1] >= r1[0] && r2[1] < r1[1]);

        (
            if contains { p1_tot + 1 } else { p1_tot },
            if overlaps { p2_tot + 1 } else { p2_tot },
        )
    });

    // P1: 538
    // P2: 792
    println!("P1: {}\nP2: {}", p1_ans, p2_ans);
}
