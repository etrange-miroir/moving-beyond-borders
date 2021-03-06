## Install openframeworks

In the pi home : `cd ~`

[http://forum.openframeworks.cc/t/raspberry-pi-2-setup-guide/18690](http://forum.openframeworks.cc/t/raspberry-pi-2-setup-guide/18690)

## Modify `ofSerial.cpp`

Add these lines in row 374 (after `options.c_cflag |= CS8;`)

```
options.c_cflag |= CRTSCTS;
options.c_lflag &= ~(ICANON | ECHO | ISIG);
```

## Install ofxOMXPlayer

```
cd ~/of_v0.8.4_linuxarmv7l_release/addons/
git clone https://github.com/jvcleave/ofxOMXPlayer.git
```

## Install wiringPi

```
cd ~
git clone git://git.drogon.net/wiringPi
cd wiringPi
./build
```

## `/etc/fstab` for USB stick

USB stick must be FAT32 and add this at the end of the file.
Should work with any USB stick, if not use `sudo blkid` to get the UUID and use it instead of `/dev/sda1` (e.g. `UUID=E3AB-886E`).

```
/dev/sda1 /media/mbb       vfat    defaults          0       2
```

## Clone the project

```
cd ~
git clone https://github.com/etrange-miroir/moving-beyond-borders.git
```

## Overclock RPi2

Copy `misc/config.txt` to `/boot/config.txt`

```
sudo cp misc/config.txt /boot/config.txt
```

## Compile and run it

Add the env variables to the `/etc/environment` file (once)

```
MAKEFLAGS=-j4
PLATFORM_VARIANT=rpi2
```

Compile and run (for developement)

```
make
sudo MAKEFLAGS=-j4 PLATFORM_VARIANT=rpi2 make run
```

## `init.d` script

Copy the following

```
sudo cp misc/moving-beyond-borders /etc/init.d/
sudo chmod +x /etc/init.d/moving-beyond-borders
sudo update-rc.d moving-beyond-borders defaults
```

This will make the app run at startup

## Arduino code

Arduino code is in the `arduino` folder.

## Naming videos

Put videos at the root of the USB stick. Use a suffix to specify tha language (e.g: _en, _fr, _es, _it, _ar).

Example for english videos:

- intro_en.mp4
- page1_en.mp4
- page2_en.mp4
- outro_en.mp4

Loops for intro and outro dont have a language and are named:

- introLoop.mp4
- outroLoop.mp4

## Convert a video

Not sure it's the best way, but it makes the video very light.

```
avconv -i input.mp4 -vcodec h264 -profile:v main -preset medium -tune animation -crf 18 -b-pyramid none -acodec ac3 -ab 1536k -scodec copy output.mp4
```
