use std::io;

static N: i32 = (1<<5) - 5 - 1;

fn fillG() -> [i32; 26] {
    let mut G: [i32; 26] = [0;26];
    let mut index: i32 = 0;
    for i in 0..32
    {
        if countBits(i) > 1 {
            G[index as usize] = i<<(N) ^ (1<<(N - index - 1));
            index += 1;
        }
    }
    return G;
}

fn countBits(num: i32) -> i32
{
    let mut count = 0;
    let mut n = num;
    while n != 0 {
        n &= n-1;
        count += 1;
    }
    return count;
}

fn main() {
    let G: [i32; 26] = fillG();
    for i in 0..26 {
        println!("{:031b}", G[i]);
    }
}
