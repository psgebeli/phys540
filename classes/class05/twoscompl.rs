fn dotdot()
{
	println!("    .");
	println!("    .");

}

fn showbits_u8(x:i32) // take one single argument x as a 32 bit integer
{
	// u is signed int, i is unsigned int
	println!("{:5} {:08b}", x, (x as u8));
	// print x with 5 spaces and then 8 spaces in binary
	// cast it to 8 bit unsigned integer

}

fn showbits_i8(x:i32)
{
	println!("{:5} {:08b}", x, (x as i8));

}

fn main()
{
	// unsigned binary
	println!("Ranging 0...255 with type u8 (unsigned 8bit int)");
	for x in 0..10 // INCLUDES 10
	{
		showbits_u8(x);
	}
	dotdot();
	for x in 246..256
	{
		showbits_u8(x);
	}

	// signed binary (twos complement)
	println!("\nRanging =127..128 with type i8 (signed 8bit int)");
	for x in -128..-118
	{
		showbits_i8(x);
	}
	dotdot();
	for x in -5..6
	{
		showbits_i8(x);
	}
	dotdot();
	for x in 118..128
	{
		showbits_i8(x);
	}
}