//
//  RoundWindow.m
//  RoundWindow
//
//  Created by Matt Gallagher on 12/12/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//

#import "RoundWindow.h"
#import "RoundWindowFrameView.h"

@implementation RoundWindow

//
// initWithContentRect:styleMask:backing:defer:screen:
//
// Init method for the object.
//
- (id)initWithContentRect:(NSRect)contentRect
	styleMask:(NSUInteger)windowStyle
	backing:(NSBackingStoreType)bufferingType
	defer:(BOOL)deferCreation
{
	self = [super
		initWithContentRect:contentRect
		styleMask:NSBorderlessWindowMask
		backing:bufferingType
		defer:deferCreation];
	if (self)
	{
		[self setOpaque:NO];
		[self setBackgroundColor:[NSColor clearColor]];
		
		[[NSNotificationCenter defaultCenter]
			addObserver:self
			selector:@selector(mainWindowChanged:)
			name:NSWindowDidBecomeMainNotification
			object:self];
		
		[[NSNotificationCenter defaultCenter]
			addObserver:self
			selector:@selector(mainWindowChanged:)
			name:NSWindowDidResignMainNotification
			object:self];
      
      m_controller = [[NSWindowController alloc] initWithWindow:self];
 
      [self create_view];
      
	}
   
	return self;
   
}

//
// dealloc
//
// Releases instance memory.
//
- (void)dealloc
{
	[[NSNotificationCenter defaultCenter]
		removeObserver:self];
//	[super dealloc];
}


//
// setContentSize:
//
// Convert from childContentView to frameView for size.
//
- (void)setContentSize:(NSSize)newSize
{
	//NSSize sizeDelta = newSize;
	//NSSize childBoundsSize = [childContentView bounds].size;
	//sizeDelta.width -= childBoundsSize.width;
	//sizeDelta.height -= childBoundsSize.height;
	
//	RoundWindowFrameView *frameView = [super contentView];
	//NSSize newFrameSize = [frameView bounds].size;
	//newFrameSize.width += sizeDelta.width;
	//newFrameSize.height += sizeDelta.height;
	
	[super setContentSize:newSize];
}

//
// mainWindowChanged:
//
// Redraw the close button when the main window status changes.
//
- (void)mainWindowChanged:(NSNotification *)aNotification
{
	[closeButton setNeedsDisplay];
}

//
// setContentView:
//
// Keep our frame view as the content view and make the specified "aView"
// the child of that.
//
- (void)create_view
{

	NSRect bounds = [self frame];
	
   bounds.origin = NSZeroPoint;

	RoundWindowFrameView * frameView = [[RoundWindowFrameView alloc] initWithFrame : bounds] ;
   
   frameView->m_roundwindow =  self;
		
	[super setContentView : frameView];

	//	closeButton = [NSWindow standardWindowButton:NSWindowCloseButton forStyleMask:NSTitledWindowMask];
	//	NSRect closeButtonRect = [closeButton frame];
	//	[closeButton setFrame:NSMakeRect(WINDOW_FRAME_PADDING - 20, bounds.size.height - (WINDOW_FRAME_PADDING - 20) - closeButtonRect.size.height, closeButtonRect.size.width, closeButtonRect.size.height)];
	//	[closeButton setAutoresizingMask:NSViewMaxXMargin | NSViewMinYMargin];
	//	[frameView addSubview:closeButton];
	//childContentView = frameView;
   
	[frameView setFrame : [self contentRectForFrameRect : bounds]];
   
	[frameView setAutoresizingMask:NSViewWidthSizable | NSViewHeightSizable];
   
//	[frameView addSubview:childContentView];
   
}

//
// contentView
//
// Returns the child of our frame view instead of our frame view.
//
- (NSView *)contentView
{
	return childContentView;
}

//
// canBecomeKeyWindow
//
// Overrides the default to allow a borderless window to be the key window.
//
- (BOOL)canBecomeKeyWindow
{
	return YES;
}

//
// canBecomeMainWindow
//
// Overrides the default to allow a borderless window to be the main window.
//
- (BOOL)canBecomeMainWindow
{
	return YES;
}

//
// contentRectForFrameRect:
//
// Returns the rect for the content rect, taking the frame.
//
- (NSRect)contentRectForFrameRect:(NSRect)windowFrame
{
  // bounds = windowFrame;
	windowFrame.origin = NSZeroPoint;
	return NSInsetRect(windowFrame, WINDOW_FRAME_PADDING, WINDOW_FRAME_PADDING);
}

//
// frameRectForContentRect:styleMask:
//
// Ensure that the window is make the appropriate amount bigger than the content.
//
+ (NSRect)frameRectForContentRect:(NSRect)windowContentRect styleMask:(NSUInteger)windowStyle
{
	return NSInsetRect(windowContentRect, -WINDOW_FRAME_PADDING, -WINDOW_FRAME_PADDING);
}



//
// drawRect:
//
// Draws the frame of the window.
//
- (void)drawRect:(NSRect)rect
{
	[[NSColor clearColor] set];
	NSRectFill(rect);
	
	NSBezierPath *circlePath = [NSBezierPath bezierPathWithOvalInRect:[self frame]];
	
	NSGradient* aGradient =
   [[NSGradient alloc]
    initWithColorsAndLocations:
    [NSColor whiteColor], (CGFloat)0.0,
    [NSColor lightGrayColor], (CGFloat)1.0,
    nil];
	[aGradient drawInBezierPath:circlePath angle:90];
   
	[[NSColor whiteColor] set];
	[circlePath stroke];
	
	/*NSRect resizeRect = [self resizeRect];
	NSBezierPath *resizePath = [NSBezierPath bezierPathWithRect:resizeRect];
   
	[[NSColor lightGrayColor] set];
	[resizePath fill];
   
	[[NSColor darkGrayColor] set];
	[resizePath stroke];
	
	[[NSColor blackColor] set];
	NSString *windowTitle = [[self window] title];
	NSRect titleRect = [self bounds];
	titleRect.origin.y = titleRect.size.height - (WINDOW_FRAME_PADDING - 7);
	titleRect.size.height = (WINDOW_FRAME_PADDING - 7);
	NSMutableParagraphStyle *paragraphStyle =
   [[NSMutableParagraphStyle alloc] init];
	[paragraphStyle setAlignment:NSCenterTextAlignment];
	[windowTitle
    drawWithRect:titleRect
    options:0
    attributes:[NSDictionary
                dictionaryWithObjectsAndKeys:
                paragraphStyle, NSParagraphStyleAttributeName,
                [NSFont systemFontOfSize:14], NSFontAttributeName,
                nil]];*/
}

@end
