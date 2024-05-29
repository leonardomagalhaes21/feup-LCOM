#!/bin/bash

# Define the target resolution
target_width=1280
target_height=1024

# Function to calculate new dimensions while maintaining aspect ratio
calculate_new_dimensions() {
    original_width=1152
    original_height=864

    # Calculate scaling factors
    scaling_factor_width=$(bc -l <<< "$target_width / $original_width")
    scaling_factor_height=$(bc -l <<< "$target_height / $original_height")

    # Choose the smaller scaling factor to maintain aspect ratio
    if (( $(echo "$scaling_factor_width < $scaling_factor_height" | bc -l) )); then
        new_width=$target_width
        new_height=$(bc <<< "scale=0; $original_height * $scaling_factor_width")
    else
        new_width=$(bc <<< "scale=0; $original_width * $scaling_factor_height")
        new_height=$target_height
    fi
}

# Resize each image while maintaining aspect ratio
resize_with_aspect_ratio() {
    for img in "$@"; do
        calculate_new_dimensions "$img"
        output_dir="../../110/backgrounds/"
        output_file="${output_dir}$(basename ${img%.*})_110.xpm"
        convert "$img" -resize ${new_width}x${new_height} "$output_file"
    done
}

# Call the function with the list of images
resize_with_aspect_ratio "hearth2.xpm" "monster2.xpm" "monster1.xpm" "square.xpm" "bala.xpm" "ScoreBoardBackgrd.xpm" "LeaderboardMenu.xpm" "full_Menu.xpm" "background.xpm"
