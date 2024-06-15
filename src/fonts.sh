#! /bin/bash
if [ ! -d "$HOME/.fonts" ]; then
    mkdir "$HOME/.fonts"
fi

cd "$HOME/Conf-Loader/fonts"

for i in *; do
    cp -r "$i" "$HOME/.fonts"
done
fc-cache -fv
