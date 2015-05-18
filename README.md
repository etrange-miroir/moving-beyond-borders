## Install openframeworks

In the pi home : `cd ~`

[http://forum.openframeworks.cc/t/raspberry-pi-2-setup-guide/18690](http://forum.openframeworks.cc/t/raspberry-pi-2-setup-guide/18690)

## Install ofxOMXPlayer

```
cd ~/of_v0.8.4_linuxarmv7l_release/addons/
git clone https://github.com/jvcleave/ofxOMXPlayer.git
```

## `/etc/fstab` for USB stick

USB stick must be FAT32 and add this at the end of the file.
Should work with any USB stick, if not use `sudo blkid` to get the UUID and use it instead of `/dev/sda1` (`UUID=E3AB-886E`).

```
/dev/sda1 /media/mbb       vfat    defaults          0       2
```

## Use 384Mo for GPU memory

## Clone the project

```
cd ~
git clone https://github.com/xseignard/mbb.git
```

## Compile and run it

Make sure you have the following env variables

```
export MAKEFLAGS=-j4 PLATFORM_VARIANT=rpi2
```

Compile and run

```
make
make run
```

## Upload Standard Firmata on the Arduino

Plain simple

## Naming videos

Put videos at the root of the USB stick.

- intro.mp4
- page1.mp4
- ...
- outro.mp4

## Convert a video

Not sure it's the best way, but it makes the video very light.

```
avconv -i input.mp4 -vcodec h264 -profile:v main -preset medium -tune animation -crf 18 -b-pyramid none -acodec ac3 -ab 1536k -scodec copy output.mp4
```

## TODO

- use init.d to run the app at startup
