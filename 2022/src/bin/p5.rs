use aoc2022::common::read_lines;
use std::str;

fn main() {
    let lines: Vec<String> = match read_lines("res/p5.txt") {
        Ok(v) => v.into_iter().filter_map(|e| e.ok()).collect(),
        Err(e) => panic!("Failed to read input file: {}", e),
    };

    let mut lines_iter = lines.iter();
    let stacks_def: Vec<&String> = lines_iter
        .by_ref()
        .take_while(|l| l.starts_with([' ', '[']))
        .collect();
    let (stacks_list, stacks_init) = stacks_def.split_last().unwrap();
    let moves: Vec<&String> = lines_iter.collect();

    let stack_count = (stacks_list.len() / 4) + 1;
    let mut stacks: Vec<Vec<String>> = vec![vec![]; stack_count];

    for init_raw in stacks_init.iter().rev() {
        let init = init_raw
            .as_bytes()
            .chunks(4)
            .map(|buf| {
                unsafe { str::from_utf8_unchecked(buf) }
                    .replace(['[', ']'], "")
                    .trim()
                    .to_owned()
            })
            .collect::<Vec<String>>();
        for (i, e) in init.into_iter().enumerate() {
            if !e.is_empty() {
                stacks[i].push(e.to_owned());
            }
        }
    }

    for m in moves {
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

    // P1: JRVNHHCSJ
    // P2: 
    println!("P1: {}", p1_ans);
}
