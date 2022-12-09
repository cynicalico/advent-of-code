use aoc2022::common::read_lines;
use std::str;

fn main() {
    let lines: Vec<String> = match read_lines("res/p5.txt") {
        Ok(v) => v.into_iter().filter_map(|e| e.ok()).collect(),
        Err(e) => panic!("Failed to read input file: {}", e),
    };

    // Process the input and split it into a few pieces:
    // 1) The lines that give the initial crate stack state
    // 2) The line that has each stack number listed
    // 3) The moves
    let mut lines_iter = lines.iter();
    let stacks_def: Vec<&String> = lines_iter
        .by_ref()
        .take_while(|l| l.starts_with([' ', '[']))
        .collect();
    let (stacks_list, stacks_init) = stacks_def.split_last().unwrap();
    let moves: Vec<&String> = lines_iter.collect();

    // Divide by 4 to account for one space padding, then
    // add 1 for the final stack
    let stack_count = (stacks_list.len() / 4) + 1;
    let mut stacks: Vec<Vec<String>> = vec![vec![]; stack_count];

    for init_raw in stacks_init.iter().rev() {
        let init = init_raw
            .as_bytes()
            .chunks(4) // 4 instead of 3 to account for one space padding
            .map(|buf| {
                unsafe { str::from_utf8_unchecked(buf) }
                    .replace(['[', ']'], "") // Get rid of extra chars
                    .trim() // No whitespace
                    .to_owned() // Make it a real string
            })
            .collect::<Vec<String>>();
        for (i, e) in init.into_iter().enumerate() {
            if !e.is_empty() {
                stacks[i].push(e.to_owned());
            }
        }
    }

    // We need a separate copy to do the second part of the question,
    // as well as a buffer to handle the new way the crates are moved
    let mut stacks_p2 = stacks.clone();
    let mut stack_buf: Vec<String> = vec![];

    // Part 1
    for m in moves.iter() {
        let ms: Vec<&str> = m.split_whitespace().collect();
        let count: u32 = ms[1].parse().unwrap();
        let src: usize = ms[3].parse().unwrap();
        let dst: usize = ms[5].parse().unwrap();

        for _ in 0..count {
            let n = stacks[src - 1].pop().unwrap();
            stacks[dst - 1].push(n);
        }
    }

    let p1_ans = stacks.iter().fold("".to_owned(), |s, crates| {
        s + crates.last().unwrap().as_str()
    });

    // Part 2
    for m in moves.iter() {
        let ms: Vec<&str> = m.split_whitespace().collect();
        let count: u32 = ms[1].parse().unwrap();
        let src: usize = ms[3].parse().unwrap();
        let dst: usize = ms[5].parse().unwrap();

        for _ in 0..count {
            stack_buf.push(stacks_p2[src - 1].pop().unwrap());
        }
        while !stack_buf.is_empty() {
            stacks_p2[dst - 1].push(stack_buf.pop().unwrap());
        }
    }

    let p2_ans = stacks_p2.iter().fold("".to_owned(), |s, crates| {
        s + crates.last().unwrap().as_str()
    });

    // P1: JRVNHHCSJ
    // P2: GNFBSBJLH
    println!("P1: {}\nP2: {}", p1_ans, p2_ans);
}
