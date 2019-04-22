# Barrier
Application for manual control of the parking barrier. 

* Raspberry Pi Qt 5.12.0
* Pin control: 23 (WiringPi pin 14)
* Web-configuration: http://raspberry_pi_ip:8080
* Web authorization: admin:admin

Added suport RTC ds1307
echo ds1307 0x68 > /sys/class/i2c-adapter/i2c-1/new_device
sudo hwclock -s

sudo apt-get purge wolfram-engine scratch scratch2 nuscratch sonic-pi idle3 -y
sudo apt-get purge smartsim java-common minecraft-pi libreoffice* -y
sudo apt-get clean
sudo apt-get autoremove -y
sudo apt-get install -y ttf-mscorefonts-installer unclutter x11-xserver-utils

* /etc/xdg/lxsession/LXDE-pi/autostart
#@lxpanel --profile LXDE-pi
#@pcmanfm --desktop --profile LXDE-pi
#@xscreensaver -no-splash
#point-rpi

@/home/pi/barrier/HumanBarrier &

@numlockx on
@unclutter
@xset s off
@xset s noblank
@xset -dpms
