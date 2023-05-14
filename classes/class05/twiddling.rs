fn main()
{

	let mut byte:u8 = 0b0000_0000; // mut means mutable (can change)

	byte |= 0b0100_0100; // byte = byte | 0b0100_0100; (| is or)
	println!("{:08b}",byte);
	println!(" ^   ^");
	println!("set tye 3rd and 7th bits\n");

	byte = !byte; // ~byte in C/C++ for complement, ! in rust
	println!("{:08b}",byte);
	println!("^^^^^^^^");
	println!("flip all bits\n");

	byte &= !0b1000_0000; 
	println!("{:08b}",byte);
	println!("^");
	println!("unset the most significant bit");

	byte ^= 0b0000_1111; // exclusive or xor (this or that or not both)
	println!("{:08b}",byte);
	println!("    ^^^^");
	println!("toggle 4 least significant bits");
}