
# Exercise 1

```
$ make largearray largearrayinit 
make: `largearray' is up to date.
make: `largearrayinit' is up to date.
$ ls -lh largearray largearrayinit
-rwxr-xr-x 1 noah noah 8.4K Mar 28 11:14 largearray
-rwxr-xr-x 1 noah noah 204K Mar 28 11:14 largearrayinit
```

The initialized array is about 196k larger than the unintialized one, because the space for the initial data for the array is included in the executable.

# Exercise 2

```
$ ./argtest "hello world 123 test"
The argument array contains:
0:hello
1:world
2:123
3:test
```

# Exercise 3

The modified code is in makeargv.c. Sample output:
```
$ ./argtest "hello world test 123"
The argument array contains:
0:hello
1:world
2:test
3:123
```
Strtok_r modifies the saveptr parameter, using it as scratch space. It is re-entrant: because
it uses saveptr rather than a static buffer, it can be overlapped by calls to different strings.
The book doesn't really define "thread-safe", but as re-entrant doesn't imply thread-safe, this
doesn't necessarily make strtok_r thread-safe.

# Exercise 4
```
symbol       | linkage   | storage
-----------------------------------
count        | internal  | static
onepass()    | internal  | N/A
a[]          | N/A       | automatic
n            | N/A       | automatic
i            | N/A       | automatic
interchanges | N/A       | automatic
temp         | N/A       | automatic
clearcount() | external  | N/A
getcount()   | external  | N/A
bubblesort() | external  | N/A
i            | N/A       | automatic
```

# Exercise 5
Sample output:
```
$ ./keeplog
echo "hello world"
hello world
ls
argtest        bubblesort.c      convertlinux.ed  getpaths.c      keeplog.c     largearrayinit    log.h       README         showtimestest.c   wordaveragetest
argtest.c      bubblesorttest    environ          getpathstest    keeploglib.c  largearrayinit.c  loglib.c    showtimes      wastetime.c       wordaveragetestbad
argtestfree    bubblesorttest.c  environ.c        getpathstest.c  largearray    listlib.c         makeargv.c  showtimes.c    wordaveragebad.c  wordaveragetest.c
argtestfree.c  convertlinux      freemakeargv.c   keeplog         largearray.c  listlib.h         makefile    showtimestest  wordaverage.c
cat bubblesort.c
static int count = 0;
...
         break;
}


>>>>>>The list of commands executed is:
Command: echo "hello world"
Time: Mon Mar 28 14:14:54 2016

Command: ls
Time: Mon Mar 28 14:14:56 2016

Command: cat bubblesort.c
Time: Mon Mar 28 14:15:09 2016
```
```
$ ./keeplog history
echo test
test
ls
argtest        bubblesort.c      convertlinux.ed  getpaths.c      keeplog.c     largearrayinit    log.h       README         showtimestest.c   wordaveragetest
argtest.c      bubblesorttest    environ          getpathstest    keeploglib.c  largearrayinit.c  loglib.c    showtimes      wastetime.c       wordaveragetestbad
argtestfree    bubblesorttest.c  environ.c        getpathstest.c  largearray    listlib.c         makeargv.c  showtimes.c    wordaveragebad.c  wordaveragetest.c
argtestfree.c  convertlinux      freemakeargv.c   keeplog         largearray.c  listlib.h         makefile    showtimestest  wordaverage.c
history
Command: echo test
Time: Mon Mar 28 14:18:54 2016

Command: ls
Time: Mon Mar 28 14:19:28 2016



>>>>>>The list of commands executed is:
Command: echo test
Time: Mon Mar 28 14:18:54 2016

Command: ls
Time: Mon Mar 28 14:19:28 2016
```

# Exercise 6
Listlib.h/.c uses the "static" keyword to approximate private variables and functions, and
instance variables (which can be made public with the "extern" keyword). What it can't do
is create seperate instances.

We actually saw a few hacks to fix this in OS161, such as passing a struct of state information
to "member" functions or creating whole "classes" using preprocessor directives to create
lists of different types.

# Exercise 7
Book version:
```
$ ./environ
The environment list follows:
environ[0]: XDG_VTNR=8
environ[1]: XDG_SESSION_ID=c1
environ[2]: SSH_AGENT_PID=1885
environ[3]: SELINUX_INIT=YES
environ[4]: SESSION=xfce
environ[5]: GPG_AGENT_INFO=/run/user/1000/keyring-UrWbM1/gpg:0:1
environ[6]: GLADE_PIXMAP_PATH=:
environ[7]: XDG_MENU_PREFIX=xfce-
environ[8]: TERM=screen
environ[9]: SHELL=/bin/bash
environ[10]: XDG_SESSION_COOKIE=d947311143955d577253bdb156edef85-1458594108.962044-1928015582
environ[11]: WINDOWID=58720260
environ[12]: OLDPWD=/home/noah/Documents/usp-code
environ[13]: UPSTART_SESSION=unix:abstract=/com/ubuntu/upstart-session/1000/1376
environ[14]: GNOME_KEYRING_CONTROL=/run/user/1000/keyring-UrWbM1
environ[15]: USER=noah
environ[16]: LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arj=01;31:*.taz=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lz=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.axv=01;35:*.anx=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.axa=00;36:*.oga=00;36:*.spx=00;36:*.xspf=00;36:
environ[17]: GLADE_MODULE_PATH=:
environ[18]: SSH_AUTH_SOCK=/tmp/ssh-wbKKSxJ0rTHv/agent.1884
environ[19]: USERNAME=noah
environ[20]: SESSION_MANAGER=local/noah-mintvm:@/tmp/.ICE-unix/1878,unix/noah-mintvm:/tmp/.ICE-unix/1878
environ[21]: DEFAULTS_PATH=/usr/share/gconf/xfce.default.path
environ[22]: TMUX=/tmp/tmux-1000/default,3541,0
environ[23]: XDG_CONFIG_DIRS=/etc/xdg/xdg-xfce:/usr/share/upstart/xdg:/etc/xdg:/etc/xdg
environ[24]: PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
environ[25]: DESKTOP_SESSION=xfce
environ[26]: GDM_XSERVER_LOCATION=local
environ[27]: PWD=/home/noah/Documents/usp-code/chapter02
environ[28]: JOB=dbus
environ[29]: LANG=en_US.UTF-8
environ[30]: GNOME_KEYRING_PID=1786
environ[31]: MANDATORY_PATH=/usr/share/gconf/xfce.mandatory.path
environ[32]: TMUX_PANE=%2
environ[33]: IM_CONFIG_PHASE=1
environ[34]: MDM_XSERVER_LOCATION=local
environ[35]: GDMSESSION=xfce
environ[36]: SESSIONTYPE=
environ[37]: XDG_SEAT=seat0
environ[38]: SHLVL=2
environ[39]: HOME=/home/noah
environ[40]: UPSTART_INSTANCE=
environ[41]: XDG_SESSION_DESKTOP=xfce
environ[42]: UPSTART_EVENTS=started xsession
environ[43]: LOGNAME=noah
environ[44]: XDG_DATA_DIRS=/usr/share/xfce:/usr/share/xfce4:/usr/local/share/:/usr/share/:/usr/share/mdm/:/usr/share
environ[45]: DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-MOKkphYOPn
environ[46]: LESSOPEN=| /usr/bin/lesspipe %s
environ[47]: MDMSESSION=xfce
environ[48]: WINDOWPATH=8
environ[49]: UPSTART_JOB=startxfce4
environ[50]: TEXTDOMAIN=im-config
environ[51]: INSTANCE=
environ[52]: XDG_RUNTIME_DIR=/run/user/1000
environ[53]: DISPLAY=:0.0
environ[54]: MDM_LANG=en_US.UTF-8
environ[55]: GLADE_CATALOG_PATH=:
environ[56]: XDG_CURRENT_DESKTOP=XFCE
environ[57]: LESSCLOSE=/usr/bin/lesspipe %s %s
environ[58]: TEXTDOMAINDIR=/usr/share/locale/
environ[59]: XAUTHORITY=/home/noah/.Xauthority
environ[60]: COLORTERM=xfce4-terminal
environ[61]: _=./environ
```
My environ.c (customized to use strtok to split key/value pairs):
```
$ ./environ 
USER: noah
LS_COLORS: rs
GLADE_MODULE_PATH: :
SSH_AUTH_SOCK: /tmp/ssh-wbKKSxJ0rTHv/agent.1884
USERNAME: noah
SESSION_MANAGER: local/noah-mintvm:@/tmp/.ICE-unix/1878,unix/noah-mintvm:/tmp/.ICE-unix/1878
DEFAULTS_PATH: /usr/share/gconf/xfce.default.path
TMUX: /tmp/tmux-1000/default,3541,0
XDG_CONFIG_DIRS: /etc/xdg/xdg-xfce:/usr/share/upstart/xdg:/etc/xdg:/etc/xdg
PATH: /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
DESKTOP_SESSION: xfce
GDM_XSERVER_LOCATION: local
PWD: /home/noah/Documents/sos/spring/usp/chapter02
JOB: dbus
LANG: en_US.UTF-8
GNOME_KEYRING_PID: 1786
MANDATORY_PATH: /usr/share/gconf/xfce.mandatory.path
TMUX_PANE: %6
IM_CONFIG_PHASE: 1
MDM_XSERVER_LOCATION: local
GDMSESSION: xfce
Unable to tokenize environ SESSIONTYPE.
XDG_SEAT: seat0
SHLVL: 2
HOME: /home/noah
Unable to tokenize environ UPSTART_INSTANCE.
XDG_SESSION_DESKTOP: xfce
UPSTART_EVENTS: started xsession
LOGNAME: noah
XDG_DATA_DIRS: /usr/share/xfce:/usr/share/xfce4:/usr/local/share/:/usr/share/:/usr/share/mdm/:/usr/share
DBUS_SESSION_BUS_ADDRESS: unix:abstract
LESSOPEN: | /usr/bin/lesspipe %s
MDMSESSION: xfce
WINDOWPATH: 8
UPSTART_JOB: startxfce4
TEXTDOMAIN: im-config
Unable to tokenize environ INSTANCE.
XDG_RUNTIME_DIR: /run/user/1000
DISPLAY: :0.0
MDM_LANG: en_US.UTF-8
GLADE_CATALOG_PATH: :
XDG_CURRENT_DESKTOP: XFCE
LESSCLOSE: /usr/bin/lesspipe %s %s
TEXTDOMAINDIR: /usr/share/locale/
XAUTHORITY: /home/noah/.Xauthority
COLORTERM: xfce4-terminal
_: ./environ
```
Checking it:
```
$ ./getpathstest 
[0]:/usr/local/sbin
[1]:/usr/local/bin
[2]:/usr/sbin
[3]:/usr/bin
[4]:/sbin
[5]:/bin
[6]:/usr/games
[7]:/usr/local/games
$ echo $PATH
/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games
```
# Exercise 8
exit() calls user exit handlers defined by atexit() or on_exit(), flushes buffers, and closes
open streams. _exit() and _Exit() don't call user handlers and may or may not release open
resources. _Exit() is written with a more modern code standard than _exit().

Exiting via "return" uses exit(), or exit() with status 0 if the end of main is reached.
# Exercise 9
An exit handler is a user defined function that runs during exit(). It isn't called if the
process is terminated via _exit() or _Exit().
