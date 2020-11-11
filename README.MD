## About this porject

This project is a prototype to capture controller inputs with your computer and redirect them to another device via usb.
Since I am a streamer I was looking for a way to display my inputs in the streaming overlay.
Unfortunately there was only one way to do this with the Nintendo Switch (or consoles in general?).
This way required an softmod which I didn't wanted to do, since it comes with a high risks of being banned.
So I decided to build my own solution, that doesnt require any modifications of the Switch.

This works by connecting your controller to your computer instead of directly to the gaming console.
So you can use the typical tools that are out there to visualize you controller inputs.
Then the pc-software reads all the inputs from your controller and sends them to a microcontroller (actually 2).
These microcontrollers act like a bridge between you computer and the console by emulating an XInput device.

<insert picture>

## How can I get this?

Sadly you can't buy such an adapter at the moment of writing.
But you can build your own based on my project. 
For that you will need some parts. 
I have listed them for you below.

- 2x Arduino Leonardo or a compatatible board (make sure it has native usb support and is supported by the XInput library)
- An adapter that allowes you to connect an XInput device to your switch (for example the Mayflash "MAGIC-NS")
- A soldering iron and few wires
- (Optional) A 3D priter to create a case

For more details, read the tutorial. 

## Which controllers are supported?

Currently all XInput devices are supported.
I plan to add support for the Joycons and the Pro Controller as well.
But I am very busy, so this could take some time.
I may also work on different controllers in the future.

## Can I contribute to this project?

Yes, any contributions are very welcome.
Especially to add support for more controllers.
So feel free to help me to improve this project.

## I have other question...

Feel free to ask me ;P .