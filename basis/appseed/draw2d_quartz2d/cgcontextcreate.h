inline CGContextRef CGContextCreate(CGSize size)
{
	CGColorSpaceRef space = CGColorSpaceCreateDeviceRGB();
	CGContextRef ctx = CGBitmapContextCreate(nil, size.width, size.height, 8, size.width * (CGColorSpaceGetNumberOfComponents(space) + 1), space, kCGImageAlphaPremultipliedLast);
	CGColorSpaceRelease(space);

	return ctx;
}