# streamscraper-gui

streamscraper-gui is a cross-platform GUI application written on top of Qt 5.
It provides an easy-to-use graphical interface for working with [streamscraper](https://github.com/mihaly044/streamscraper).

## Installation
All streamscraper-gui releases comes with streamscraper bundled. Windows releases also contain ffmpeg bundled.

#### Windows
Download the latest release from [the releases page](https://github.com/mihaly044/streamscraper-gui/releases/tag/v0.1.rev-be66af-alpha).
You can either download an installer, or a portable version. After you have downloaded either version, start the program by double clicking on streamscraperGui.exe. Additionally if you have chosen the setup version, you'll have an icon on your desktop that starts the program.

#### Unix-like systems (Linux)
Download and extract the latest  release for Linux systems: [streamscraper-gui-linux-x64-bundle-rev71bf0d.tar.gz](https://github.com/mihaly044/streamscraper-gui/releases/download/v0.1.rev-be66af-alpha/streamscraper-gui-linux-x64-bundle-rev71bf0d.tar.gz)

```bash
wget https://github.com/mihaly044/streamscraper-gui/releases/download/v0.1.rev-be66af-alpha/streamscraper-gui-linux-x64-bundle-rev71bf0d.tar.gz)
tar -xzf streamscraper-gui-linux-x64-bundle-rev71bf0d.tar.gz 
```
After the download has completed, run the application by starting `streamscraperGui.sh`:

```bash
cd streamscraper-gui-linux-x64-bundle-rev71bf0d
chmod +x ./streamscraperGui.sh
./streamscraperGui.sh
```
**Notice**: Linux releases don't come with ffmpeg. You need to install it on your system. For example on Debian systems (*buntu, linuxmint, debian), you'd install it as follows:
```bash
sudo apt-get install -y ffmpeg
```

