# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://

## [Unreleased]
- MQTT support
- RTC support
- WiFi connectivity

## [0.0.4] - 16/11/2019
### Changed
- CleanOldLogs Function. It was adding some invisible end of line character that on some text edditors gave problems.
- Aesthetic minor changes.

## [0.0.3] - 16/11/2019
### Added
- SD card keeping a 24h data register.
- Time mark based on delay (seconds from start)
- Round-Robin type management of reg24h.txt
- Reading the file through Serial input.
- Changelog.md

### Changed
- Moved some code out of the main sketch to a library.

## [0.0.2] - 14/11/2019
### Added
- LICENSE
- README.md
### Removed
- Illuminance sensor reading.

## [0.0.1] - 13/11/2019
### Added
- Arduino MKR-Environment shield, reading of all sensors and dumping via Serial Monitor.