# FramelessHelper

## Features

- Frameless but have frame shadow.
- Drag and resize.
- High DPI scaling.
- Multi-monitor support (different resolution and DPI).
- Windows platform: act like a normal window, such as have animations when minimizing and maximizing, support tile windows, etc ...

## Usage

### Windows

```cpp
// include other files ...
#include "winnativeeventfilter.h"
// include other files ...

// Anywhere you like, we use the main function here.
int main(int argc, char *argv[]) {
    // ...
    QWidget widget;
    // Do this before the widget is shown.
    WinNativeEventFilter::addFramelessWindow(reinterpret_cast<HWND>(widget.winId()));
    widget.show();
    // ...
}
```

### Linux and macOS

```cpp
// include other files ...
#include "framelesshelper.h"
// include other files ...

// Anywhere you like, we use the main function here.
int main(int argc, char *argv[]) {
    // ...
    QWidget widget;
    FramelessHelper helper;
    // Do this before the widget is shown.
    // Only QWidget and QWindow are supported.
    helper.setFramelessWindows({&widget});
    widget.show();
    // ...
}
```

Notes

- The `setFramelessWindows`/`addFramelessWindow` function must not be called after the widget is shown. However, for QWindows, it must be called after they are shown.
- I use `startSystemMove` and `startSystemResize` which are only available since Qt 5.15 for moving and resizing frameless windows on UNIX platforms, so if your Qt version is below that, you can't compile this code. I'm sorry for it but using the two functions is the easiest way to achieve this.
- Any widgets (or Qt Quick elements) in the titlebar area will not be resposible because the mouse events are intercepted. Try if `setIgnoreAreas` and `setDraggableAreas` can help.
- Only top level windows can be frameless. Applying this code to child windows or widgets will result in unexpected behavior.
- If you want to use your own border width, border height, titlebar height or maximum/minimum window size, just use the original numbers, no need to scale them according to DPI, this code will do the scaling automatically.

## Supported Platforms

- Windows 7 ~ 10
- Should work on X11, Wayland and macOS, but not tested.

## Notes for Windows developers

- The `FramelessHelper` class is just a simple wrapper of the `WinNativeEventFilter` class, you can use the latter directly instead if you encounter with some strange problems.
- **As you may have found, if you use this code, the resize areas will be inside the frameless window, however, a normal Win32 window can be resized outside of it.** Here is the reason: the `WS_THICKFRAME` window style will cause a window has three transparent areas beside the window's left, right and bottom edge. Their width/height is 8px if the window is not scaled. In most cases, they are totally invisible. It's DWM's responsibility to draw and control them. They exist to let the user resize the window, visually outside of it. They are in the window area, but not the client area, so they are in the non-client area actually. But we have turned the whole window area into client area in `WM_NCCALCSIZE`, so the three transparent resize areas also become a part of the client area and thus they become visible. When we resize the window, it looks like we are resizing inside of it, however, that's because the transparent resize areas are visible now, we ARE resizing outside of the window actually. But I don't know how to make them become transparent again without breaking the frame shadow drawn by DWM. If you really want to solve it, you can try to embed your window into a larger transparent window and draw the frame shadow yourself.
- If you are using `WinNativeEventFilter` directly, don't forget to call `FramelessHelper::updateQtFrame` everytime after you make a widget or window become frameless, it will make the new frame margins work correctly if `setGeometry` or `frameGeometry` is called.
- Don't change the window flags (for example, enable the Qt::FramelessWindowHint flag) because it will break the functionality of this code. I'll get rid of the window frame (including the titlebar of course) in Win32 native events.
- All traditional Win32 APIs are replaced by their DPI-aware ones, if there is one.
- Start from Windows 10, normal windows usually have a one pixel width border line, I don't add it because not everyone like it. You can draw one manually if you really need it.
- The frame shadow will get lost if the window is totally transparent. It can't be solved unless you draw the frame shadow manually.
- On Windows 7, if you disabled the Windows Aero, the frame shadow will be disabled as well because it's DWM's resposibility to draw the frame shadow.
- The border width (8 if not scaled), border height (8 if not scaled) and titlebar height (30 if not scaled) are acquired by Win32 APIs and are the same with other standard windows, and thus you should not modify them.
- You can also copy all the code to `[virtual protected] bool QWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)` or `[virtual protected] bool QWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)`, it's the same with install a native event filter to the application.

## References for Windows developers

### Microsoft Docs

- <https://docs.microsoft.com/en-us/archive/blogs/wpfsdk/custom-window-chrome-in-wpf>
- <https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-nccalcsize>
- <https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-nchittest>
- <https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-ncactivate>
- <https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-erasebkgnd>
- <https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-getminmaxinfo>
- <https://docs.microsoft.com/en-us/windows/win32/dwm/customframe>
- <https://docs.microsoft.com/en-us/windows/win32/hidpi/high-dpi-desktop-application-development-on-windows>

### Chromium

- <https://github.com/chromium/chromium/blob/master/ui/base/win/hwnd_metrics.cc>
- <https://github.com/chromium/chromium/blob/master/ui/display/win/screen_win.cc>
- <https://github.com/chromium/chromium/blob/master/ui/views/win/hwnd_message_handler.cc>
- <https://github.com/chromium/chromium/blob/master/ui/views/widget/desktop_aura/desktop_window_tree_host_win.cc>
- <https://github.com/chromium/chromium/blob/master/ui/views/widget/desktop_aura/desktop_native_widget_aura.cc>
- <https://github.com/chromium/chromium/blob/master/ui/views/widget/native_widget_aura.cc>
- <https://github.com/chromium/chromium/blob/master/ui/views/widget/widget.cc>

### Mozilla Firefox

- <https://github.com/mozilla/gecko-dev/blob/master/widget/windows/nsWindow.cpp>

### Windows Terminal

- <https://github.com/microsoft/terminal/blob/master/src/cascadia/WindowsTerminal/IslandWindow.cpp>
- <https://github.com/microsoft/terminal/blob/master/src/cascadia/WindowsTerminal/NonClientIslandWindow.cpp>

### GitHub

- <https://github.com/rossy/borderless-window>
- <https://github.com/Bringer-of-Light/Qt-Nice-Frameless-Window>
- <https://github.com/dfct/TrueFramelessWindow>
- <https://github.com/qtdevs/FramelessHelper>

### Qt

- <https://doc.qt.io/qt-5/qcoreapplication.html#installNativeEventFilter>
- <https://doc.qt.io/qt-5/qcoreapplication.html#removeNativeEventFilter>
- <https://doc.qt.io/qt-5/qobject.html#installEventFilter>
- <https://doc.qt.io/qt-5/qobject.html#removeEventFilter>
- <https://doc.qt.io/qt-5/qwindow.html#startSystemMove>
- <https://doc.qt.io/qt-5/qwindow.html#startSystemResize>

## Special Thanks

Thanks **Lucas** for testing this code in many various conditions.

Thanks [**Shujaat Ali Khan**](https://github.com/shujaatak) for searching so many useful articles and repositories for me.

## License

```text
MIT License

Copyright (C) 2020 by wangwenx190 (Yuhang Zhao)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
