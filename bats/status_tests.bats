#!/usr/bin/env bats

@test "No argument" {
  run bin/tp2
  [ "$status" -eq 0 ]
}

@test "Too many arguments" {
  run bin/tp2 alpha
  [ "$status" -eq 1 ]
}

@test "Format not supported" {
  run bin/tp2 --output-format image
  [ "$status" -eq 2 ]
}

@test "Format text" {
  run bin/tp2 --output-format text
  [ "$status" -eq 0 ]
}

@test "Format png" {
  run bin/tp2 --output-format png --output-filename /tmp/maze.png
  [ "$status" -eq 0 ]
}

@test "Short options" {
  run bin/tp2 -r 2 -c 2
  [ "$status" -eq 0 ]
}


@test "Invalid number of rows" {
  run bin/tp2 --num-rows a
  [ "$status" -eq 3 ]
}

@test "Invalid number of columns" {
  run bin/tp2 --num-rows 3 --num-cols b
  [ "$status" -eq 3 ]
}

@test "Negative number of rows" {
  run bin/tp2 --num-rows -2 --num-cols 4
  [ "$status" -eq 8 ]
}

@test "Null number of columns" {
  run bin/tp2 --num-rows 5 --num-cols 0
  [ "$status" -eq 8 ]
}

@test "Start and end rooms accepted" {
  run bin/tp2 --num-rows 5 --num-cols 5 --start 0,4 --end 4,0
  [ "$status" -eq 0 ]
}

@test "Invalid start room" {
  run bin/tp2 --num-rows 5 --num-cols 5 --start 0,c4
  [ "$status" -eq 9 ]
}

@test "Invalid end room" {
  run bin/tp2 --num-rows 5 --num-cols 5 --end 0,4?4
  [ "$status" -eq 9 ]
}

@test "Invalid end room message" {
  run bin/tp2 -r 5 -c 5 -e 1,6
  [ "${lines[0]}" = "Error: the end room coordinates 1,6 are out of bound" ]
  [ "$status" -eq 10 ]
}

@test "Start room out of bound" {
  run bin/tp2 --num-rows 5 --num-cols 5 --start 0,5
  [ "$status" -eq 10 ]
}

@test "End room out of bound" {
  run bin/tp2 --num-rows 8 --num-cols 8 --end 11,5
  [ "$status" -eq 10 ]
}

@test "Format png without filename" {
  run bin/tp2 --output-format png
  [ "$status" -eq 4 ]
}

@test "Bad option" {
  run bin/tp2 --bad-option
  [ "$status" -eq 5 ]
}

@test "With solution" {
  run bin/tp2 --with-solution
  [ "$status" -eq 0 ]
}

@test "Black color working" {
  run bin/tp2 --walls-color black --output-format png --output-filename /tmp/maze.png
  [ "$status" -eq 0 ]
}

@test "Blue color working" {
  run bin/tp2 --walls-color blue --output-format png --output-filename /tmp/maze.png
  [ "$status" -eq 0 ]
}

@test "Yellow color working" {
  run bin/tp2 --walls-color yellow --output-format png --output-filename /tmp/maze.png
  [ "$status" -eq 0 ]
}

@test "Magenta is not a named color" {
  run bin/tp2 --walls-color magenta --output-format png --output-filename /tmp/maze.png
  [ "$status" -eq 7 ]
}

@test "Color names can be in upper case" {
  run bin/tp2 --walls-color YELLOW --output-format png --output-filename /tmp/maze.png
  [ "$status" -eq 0 ]
}

@test "Format png with solution now implemented" {
  run bin/tp2 --with-solution --output-format png --output-filename /tmp/maze.png
  [ "$status" -eq 0 ]
}
