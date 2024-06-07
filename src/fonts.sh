#! /bin/bash
if [ ! -d "$HOME/.fonts" ]; then
    mkdir "$HOME/.fonts"
fi

cd "$HOME/config-switcher/fonts"

for i in *; do
    cp -r "$i" "$HOME/.fonts"
done
