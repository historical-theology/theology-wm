# theology-wm
Dr. Corey Stephan's custom build of the suckless project's dwm with efficiency boosters for scholarly research and writing

The focal point of this build is the centeredmaster patch:
https://dwm.suckless.org/patches/centeredmaster/

I also have the cool autostart patch:
https://dwm.suckless.org/patches/cool_autostart/

To launch dwm from a display manager such as lightdm, which often prohibits using an autostart patch or script, then:
(1) Copy dwm.desktop into /usr/share/xsessions/ with Exec=dwm-session (rather than simply Exec=dwm)
(2) Copy dwm-session (with autostart tasks) into /usr/local/bin/ and make sure that it is executable

This build of dwm depends on the following being installed:
* alacritty
* firefox

This build is meant to be used in conjunction with my homogenously Nord Theme [Theological Dotfiles](https://github.com/historical-theology/theological-dots).