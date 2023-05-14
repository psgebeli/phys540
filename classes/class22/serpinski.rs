//        1
//       1 1
//      1 2 1
//     1 3 3 1

const N:usize = 15; // keep this odd

fn show_num(a:&[u32; N]) {
    
    for i in 0..N-1 {

        print!("{:4} ", a[i]);

    }
    println!("{:4}", a[i]);
}

fn main() {

    let mut current:[u32; N]; // N u32 integers
    let n0 = (N-1)/2;
    current[n0] = 1;
    let mut next:[u32, N] = [0, N];
    for _ in 0..N {

        next[0] = current[1];
        next[N-1] = current[N-2];
        for i in 1..N-1 { 
            
            next[i] = current[i-1] + current[i+1];

        }
        show_num(&current);
        if current[0] != 0 break;
        current = next;
    }
}