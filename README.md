# Gainer LV2 Plugin

Simple stereo volume control plugin. Input mapping : 0% = mute, 100% = 0 dB, 200% = +6 dB.

## Features

- Stereo input/output
- Volume range : mute to +6 dB
- No dependencies beyond LV2 SDK

## Project Home

<https://simdott.github.io/gainer>

## Plugin URI

`urn:simdott:gainer`

## Dependencies

- C compiler (gcc, clang, etc.)
- LV2 development headers

### Installation by distribution

**Debian/Ubuntu :**
sudo apt-get install build-essential lv2-dev

**Fedora :**
sudo dnf install gcc lv2-devel

**Arch :**
sudo pacman -S base-devel lv2

## Build and Install

1. Download the source :
   git clone https://github.com/simdott/gainer-lv2
   cd gainer-lv2

2. Make the install script executable :
   chmod +x install.sh

3. Install for current user (recommended) :
   ./install.sh
   
   Or install system-wide (requires sudo) :
   sudo ./install.sh

## Verification

List installed plugins :
lv2ls | grep gainer

Should show : `urn:simdott:gainer`

## Usage

Load in any LV2-compatible host (Ardour, Carla, Reaper, etc.). Connect stereo inputs/outputs. Volume control ranges from mute (-inf dB) to +6 dB with 0 dB at center position.

## Files

- gainer.c - Plugin source code
- gainer.ttl - Plugin description (ports, properties)
- manifest.ttl - Bundle manifest
- install.sh - Build and install script
- uninstall.sh - Uninstall script

## Uninstall

1. Make the uninstall script executable :
   chmod +x uninstall.sh

2. Uninstall for current user :
   ./uninstall.sh
   
   Or uninstall system-wide :
   sudo ./uninstall.sh
   
### v1.0.0 (2025-02-27)

- Initial release   

## License

GPL-2.0-or-later

## Author

Simon Delaruotte (simdott) 
