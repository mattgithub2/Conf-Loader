# reloads fish
function reload
    exec fish
    set -l config (status -f)
    echo "reloading: $config"
end

# Function for starting spotify-tui
function music
    if test -z (ps -xj | pgrep spotifyd)
        spotifyd
    end
    spt
end

# makes cursor faster
xset r rate 300 50

# System information tool
# Adding some padding to fastfetch because it looks bad
# --logo-color-1 blue --logo-color-2 blue --color-keys blue 
function ff
    echo
    fastfetch --logo Linux_small --logo-padding-left 2 --color-keys yellow
    echo
end

ff
# clears and runs fetch cli
alias c="clear;ff"

# TODO get rid of this
set -x WINIT_UNIX_BACKEND x11

# sxhkd needs this to be here
export XDG_CONFIG_HOME=$HOME/.config


if status is-login
    if test -z "$DISPLAY"
        exec startx -- -keeptty
    end
end

function otw
    set level $argv[1]
    if test -n "$level"
        ssh bandit$level@bandit.labs.overthewire.org -p 2220 -C
    else
        echo "Needs a username."
    end
end

# Useful for transfering files via scp
function transfer
  set remote_path $argv[1]
  set local_destination $argv[2]
  echo "Transferring files from $remote_path to $local_destination..."
  scp -r z2004200@hopper.cs.niu.edu:$remote_path $local_destination
  echo "Transfer complete."
end

# Setting PATHS
set -e fish_user_paths
set -U fish_user_paths $HOME/.bin $HOME/.local/bin $HOME/Applications $fish_user_paths $HOME/scripts

# Sets tools
set -x EDITOR nvim
set -x VISUAL nano

# Sets the terminal type for proper colors
set TERM "xterm-256color"

# Suppresses fish's intro message
set fish_greeting

set fish_prompt_pwd_dir_length 0

alias update="sudo pacman -Syyu"


