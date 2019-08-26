# DIY Arcade Cabinet

This is a guide for putting together a complete arcade cabinet, as well as software for running custom-built games.

You can find full instructions and files in the wiki.

# Installation

Go [here to download raspbian](https://www.raspberrypi.org/downloads/raspbian/). [Flash](https://www.balena.io/etcher/) the image to a microSD card, at least 32 GB. Pop the card into your raspberrry pi, and boot up the system. Open a terminal and get ready to run a whole bunch of commands.

You will obviously need a copy of this code. Either fork your own version, or use mine, with its games and config. Up to you.

```
cd ~
mkdir Dev/ && cd Dev/
git clone https://github.com/djpeach/DIY-Arcade-Cabinet.git

```

Great you have the code! Now lets get it to run.

## Run script

You will need to create a run script, using the editor of your choice. If you want vim, you will need to install it. 

```
sudo apt-get install vim

```

I store my run script in `/usr/local/bin/custom/run_ac_menu`. 

```
cd /usr/local/bin/
mkdir custom/
cd custom/
sudo vim run_ac_menu

```

Next, add this to your path and make it executable. Assuming you use .bashrc as your ...bashrc file:

```
echo PATH=$PATH:/usr/local/bin/custom/ >> ~/.bashrc
sudo chmod +x /usr/local/bin/custom/run_ac_menu

```

Type in the following:

```
amixer cset numid=3 1;
cd ~/Dev/DIY-Arcade-Cabinet;
git pull;
cd menu/menu/;
cmake .;
make;
./menu;

```

## SFML

The menu is written in C++ and uses (SFML)[https://github.com/SFML/SFML.git], so you will need to build it on your pi. To do so, we will clone it, and use cmake to compile, after installing all dependencies.

First, lets clone it.

```
cd ~
mkdir lib/ && cd lib/
git clone https://github.com/SFML/SFML.git

```

Next, the dependencies, including cmake.

```
sudo apt-get update
sudo apt-get install cmake libflac-dev libogg-dev libvorbis-dev libjpeg8-dev libfreetype6-dev libudev-dev libraspberrypi-dev libx11-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev libxrandr-dev libxi-dev

```

Now to build the Makefile.

```
cd ~/lib/SFML/
mkdir build/ && cd build/
cmake ..
sudo make
sudo make install

```

## Running on startup

Coming next. (we use systemd)
