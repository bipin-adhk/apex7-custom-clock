# Custom OLED Clock for SteelSeries Apex 7

A high-performance, native C implementation that displays a custom clock on your SteelSeries Apex 7 keyboard OLED screen.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Language](https://img.shields.io/badge/language-C-brightgreen.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)

## ✨ Features

- ⚡ **Ultra-lightweight** - Only 2-5 MB RAM usage
- 🚀 **Native executable** - No Node.js or Python required
- 🎯 **Zero dependencies** - Single .exe file, works out of the box
- ⏱️ **Real-time updates** - Clock updates every second
- 🎨 **Custom format** - Clean two-line display
- 🔄 **Auto-start** - Runs automatically when Windows boots
- 🔇 **Silent operation** - No console window

## 📸 Display Format

19:45:30
2025/Dec/09

text

**Line 1:** Time in `HH:MM:SS` format  
**Line 2:** Date in `YYYY/MMM/DD` format

## 🖥️ System Requirements

- **Operating System:** Windows 10 or Windows 11
- **Keyboard:** SteelSeries Apex 7 (or any SteelSeries keyboard with OLED)
- **Software:** SteelSeries GG or SteelSeries Engine 3
- **Compiler** (for building from source): GCC (MinGW-w64)

## 📦 Quick Start (Pre-compiled)

**Don't want to compile? Download the ready-to-use .exe:**

1. Download `apex7_clock.exe` from [Releases](https://github.com/bipin-adhk/apex7-custom-clock/releases)
2. Double-click to run
3. Check your keyboard OLED - the clock should appear!

**To stop:** Open Task Manager (`Ctrl+Shift+Esc`) → End `apex7_clock.exe`

## 🔧 Building from Source

### Step 1: Install MinGW-w64

1. Download from: [MinGW-w64 Releases](https://github.com/niXman/mingw-builds-binaries/releases)
2. Get: `x86_64-13.2.0-release-posix-seh-ucrt-rt_v11-rev1.7z`
3. Extract to `C:\mingw64`
4. Add to PATH:
   - Press `Win + R` → type `sysdm.cpl` → Enter
   - **Advanced** → **Environment Variables**
   - Edit **Path** → Add `C:\mingw64\bin`
5. Restart Command Prompt

**Verify installation:**
gcc --version

text

### Step 2: Clone the Repository

git clone https://github.com/bipin-adhk/apex7-custom-clock.git
cd apex7-custom-clock

text

### Step 3: Compile

**Standard build (with console for debugging):**
mingw32-make

text

**Release build (silent, no console window):**
mingw32-make release

text

### Step 4: Run

apex7_clock.exe

text

## 🚀 Auto-Start on Windows Boot

### Method 1: Task Scheduler (Recommended)

1. Press `Win + R` → type `taskschd.msc` → Enter

2. Click **"Create Basic Task"**

3. **Name:** `Apex 7 Clock`  
   **Description:** `Custom OLED clock`  
   Click **Next**

4. **Trigger:** Select **"When I log on"** → **Next**

5. **Action:** Select **"Start a program"** → **Next**

6. **Program/script:** Browse to `apex7_clock.exe` → **Next**

7. Check **"Open the Properties dialog when I click Finish"** → **Finish**

8. In Properties:
   - **General** tab:
     - ✓ Run with highest privileges
     - ✓ Hidden
   - **Conditions** tab:
     - ✗ Start only if on AC power (uncheck this)
   - **Settings** tab:
     - ✓ If the task fails, restart every: **1 minute**
     - Set attempts to: **3**

9. Click **OK**

10. **Restart your computer** to test

### Method 2: Startup Folder (Simpler)

1. Press `Win + R` → type `shell:startup` → Enter

2. Right-click → **New** → **Shortcut**

3. Browse to your `apex7_clock.exe`

4. Name it **"Apex 7 Clock"** → **Finish**

5. **Restart your computer** to test


## 🛠️ How It Works

1. **Reads SteelSeries config** from `C:\ProgramData\SteelSeries\SteelSeries Engine 3\coreProps.json`
2. **Extracts GameSense API address** (usually `127.0.0.1:PORT`)
3. **Registers custom event** with SteelSeries Engine
4. **Sends time/date updates** every second via HTTP POST
5. **Keyboard displays** the formatted time on OLED screen

Uses SteelSeries GameSense™ API with native Windows HTTP (WinHTTP) - no external libraries needed.

##  Customization

### Change Time Format

Edit `time_formatter.c` → `format_time_hms()`:

// Current: "19:45:30"
snprintf(buffer, buffer_size, "%02d:%02d:%02d", ...);

// Example: "19h 45m 30s"
snprintf(buffer, buffer_size, "%02dh %02dm %02ds", ...);

text

### Change Date Format

Edit `time_formatter.c` → `format_date_ymd()`:

// Current: "2025/Dec/09"
snprintf(buffer, buffer_size, "%04d/%s/%02d", ...);

// Example: "Dec 09, 2025"
snprintf(buffer, buffer_size, "%s %02d, %04d", ...);

text

### Change Update Interval

Edit `config.h`:

#define UPDATE_INTERVAL_MS 1000 // Change to 5000 for 5 seconds

text

Recompile after changes:
mingw32-make clean
mingw32-make release

text

##  Troubleshooting

### Clock doesn't appear on OLED

**Check:**
- ✓ Is SteelSeries GG/Engine running?
- ✓ Is your keyboard connected?
- ✓ Is `apex7_clock.exe` running? (Check Task Manager)
- ✓ Is the config file at `C:\ProgramData\SteelSeries\SteelSeries Engine 3\coreProps.json`?

**Fix:**
1. Restart SteelSeries GG
2. Run `apex7_clock.exe` manually
3. Check console output for errors

### Compilation errors

**Error:** `gcc: command not found`
- **Fix:** MinGW not in PATH. Re-add `C:\mingw64\bin` to environment variables.

**Error:** `winhttp.h: No such file`
- **Fix:** Install full MinGW-w64 package (not MinGW32).

### Program crashes on startup

- **Fix:** Make sure SteelSeries Engine is running BEFORE starting the clock
- Run the debug build (without `-mwindows`) to see error messages

## 📊 Performance Comparison

|   Version    | RAM Usage | Startup Time | Dependencies |
|--------------|-----------|--------------|--------------|
| **C (This)** |   2-5 MB  |     <0.1s    |     None     |
|   Node.js    |  30-50 MB |     1-2s     | Node.js runtime |
|    Python    |  15-25 MB |     0.5-1s   | Python runtime |

## Contributing

This is a personal project, but improvements are welcome!

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/improvement`)
3. Commit your changes (`git commit -m 'Add improvement'`)
4. Push to the branch (`git push origin feature/improvement`)
5. Open a Pull Request

## 📜 License

MIT License

Copyright (c) 2025 Bipin Adhikari

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

## 👨‍💻 Author

**Bipin Adhikari**

- GitHub: [@bipin-adhk](https://github.com/bipin-adhk)
- Project: [apex7-custom-clock](https://github.com/bipin-adhk/apex7-custom-clock)

Built with for the SteelSeries community

---

## Show Your Support

If this project helped you, please give it a ⭐ on GitHub!

## Changelog

### Version 1.0.0 (December 2025)
- Initial C implementation
- Native Windows executable
- Auto-start support
- Custom time/date formatting
- Zero external dependencies
