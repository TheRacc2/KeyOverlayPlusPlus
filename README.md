## KeyOverlay++

KeyOverlay++ is a C++ Keyboard Overlay, using [ImGui](https://github.com/ocornut/imgui) and [GLFW](https://www.glfw.org/)

![In Action](https://github.com/TheRacc2/KeyOverlayPlusPlus/blob/main/example.gif)
## Installation

Once downloaded from the [releases](https://github.com/TheRacc2/KeyOverlayPlusPlus/releases/tag/v1.0) page, it's as simple as doubleclicking!

## Source Code

This project is open source, free to use and modify.

```bash
git clone https://github.com/TheRacc2/KeyOverlayPlusPlus
```

**You will need to modify the *freeglut* and *glew* paths in Visual Studio**

## Usage

The first time the application is opened, it will generate a **config.json** file. All values in section *color* are **Hexacedimal RGBA** values, stored like **#RRGGBBAA** or **0xRRGGBBAA**.
The program will automatically include maximum alpha for any hex color without alpha.

**font** path is absolute. Make sure you include the **whole path**!

When adding to OBS, select **Add Source->Game Capture** and click **Allow Transparency**. Simply select the window and you're good to go!

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Credits
A large portion of the logic codebase for KeyOverlay++ was kindly contributed by [Lexika](https://github.com/lexika979).
