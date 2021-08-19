# newtex
A utility for spinning up new files from templates. This program copies files from a template directory into the current directory. newtex was originally designed to help with LaTeX files, where one frequently needs to churn out new documents with the same format. Although newtex works with .tex files by default, it can easily work with other templates. It is recommended that users create aliases to use with a wide variety of file types.

## Requirements
newtex relies upon libconfig, which should be pre-installed on most Linux systems. If not, then simply do one of the following:
```pacman -S libconfig
pkg_add libconfig
apt-get install libconfig
```
or whatever your preferred package manager is.


## Installation
To install newtex, simply run `make install` as super user.
So, something like `doas make install` or `sudo make install`

## Configuration
To configure newtex simply edit `/etc/newtex.d/newtex.conf`. Currently you can edit the template directory (`template_dir`), extension(`extension`), and default template (`template`). newtex uses libconfig, so the format of options is `option_name = "option";`
