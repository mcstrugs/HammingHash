use array2d::Array2D;

extern crate image;


static N: i32 = (1<<5) - 5 - 1;
static G: [i32; 26] = [
0b0001110000000000000000000000000,
0b0010101000000000000000000000000,
0b0011000100000000000000000000000,
0b0011100010000000000000000000000,
0b0100100001000000000000000000000,
0b0101000000100000000000000000000,
0b0101100000010000000000000000000,
0b0110000000001000000000000000000,
0b0110100000000100000000000000000,
0b0111000000000010000000000000000,
0b0111100000000001000000000000000,
0b1000100000000000100000000000000,
0b1001000000000000010000000000000,
0b1001100000000000001000000000000,
0b1010000000000000000100000000000,
0b1010100000000000000010000000000,
0b1011000000000000000001000000000,
0b1011100000000000000000100000000,
0b1100000000000000000000010000000,
0b1100100000000000000000001000000,
0b1101000000000000000000000100000,
0b1101100000000000000000000010000,
0b1110000000000000000000000001000,
0b1110100000000000000000000000100,
0b1111000000000000000000000000010,
0b1111100000000000000000000000001
];

#[allow(dead_code)]
fn fill_g() -> [i32; 26] {
    let mut gm: [i32; 26] = [0;26];
    let mut index: i32 = 0;
    for i in 0..32
    {
        if count_bits(i) > 1 {
            gm[index as usize] = i<<(N) ^ (1<<(N - index - 1));
            index += 1;
        }
    }
    return gm;
}

fn count_bits(num: i32) -> i32
{
    let mut count = 0;
    let mut n = num;
    while n != 0 {
        n &= n-1;
        count += 1;
    }
    return count;
}

fn left_multiply_g(a: i32) -> i32
{
    let mut code = 0;
    let n = N;
    for i in 0..n {
        code = code^((a & 1<<i)>>i) * G[(n - i - 1) as usize];
    }
    return code;
}

#[allow(dead_code)]
fn is_adjacent(a: i32, b: i32) -> bool
{
    let a_code = left_multiply_g(a);
    let b_code = left_multiply_g(b);
    let diff = a_code ^ b_code;

    return count_bits(diff) == 3;
}

#[allow(dead_code)]
fn hamming_distance(a: i32, b: i32) -> i32
{
    let a_code = left_multiply_g(a);
    let b_code = left_multiply_g(b);
    return count_bits(a_code ^ b_code);
}

#[allow(dead_code)]
fn draw_set(set: Array2D<bool>) { // boolean only
    let imgy = set.column_len() as u32;
    let imgx = set.row_len() as u32;
    let mut imgbuf = image::ImageBuffer::new(imgx,imgy);
    for (x,y,pix) in imgbuf.enumerate_pixels_mut() {
        let is_shaded = *set.get(y as usize, x as usize).unwrap();
        if is_shaded {
            *pix = image::Rgb([0 as u8, 0 as u8,0 as u8]);
        } else {
            *pix = image::Rgb([255 as u8, 255 as u8, 255 as u8]);
        }
    }
    imgbuf.save("img.png").unwrap();
}

#[allow(dead_code)]
fn draw_dists(set: Array2D<i32>) {
    let imgy = set.column_len() as u32;
    let imgx = set.row_len() as u32;
    let mut imgbuf = image::ImageBuffer::new(imgx,imgy);
    for (x,y,pix) in imgbuf.enumerate_pixels_mut() {
        let dist = *set.get(y as usize, x as usize).unwrap();
        let col = dist*8;
        if dist == 3 { // Draw dist 3's red, change to 'false' to just draw ham dist
            *pix = image::Rgb([255 as u8, 0 as u8, 0 as u8]);
        } else {
            *pix = image::Rgb([col as u8, col as u8,col as u8]);
        }
    }
    imgbuf.save("dist.png").unwrap();
}

fn main() {

    /*
    for i in 0..26 {
        println!("{:031b}", G[i]);
    }
    */

    /*
    let h = 2048;
    let w = 2048;
    let mut set = Array2D::filled_with(false, h as usize, w as usize);
    let mut set_non_code = Array2D::filled_with(false, h as usize, w as usize);
    for i in 0..h {
        for j in 0..w {
            if is_adjacent(i,j) {
                let result = set.set(i as usize,j as usize,true);
                assert_eq!(result, Ok(()));
            }
            if count_bits(i^j) == 1 { // ham distance between integers
                let result = set_non_code.set(i as usize,j as usize, true);
                assert_eq!(result, Ok(()));
            }
        }
    }
    draw_set(set);
    */

    let h = 2*2048;
    let w = 2*2048;
    let mut dists = Array2D::filled_with(0 as i32, h as usize, w as usize);
    for i in 0..h {
        for j in 0..w {
            let dist = hamming_distance(i,j);
            #[allow(unused_must_use)]
            let result = dists.set(i as usize, j as usize, dist);
            assert_eq!(result, Ok(()));
        }
    }
    draw_dists(dists);
}
