#!/usr/bin/env bats

@test "No argument" {
  run bin/tp3
  [ "$status" -eq 0 ]
}

@test "Too many arguments" {
  run bin/tp3 alpha
  [ "$status" -eq 1 ]
}

@test "Format not supported" {
  run bin/tp3 --output-format image
  [ "$status" -eq 2 ]
}

@test "Format text" {
  run bin/tp3 --output-format text
  [ "$status" -eq 0 ]
}

@test "Format png" {
  run bin/tp3 --output-format png --output-filename maze.png
  [ "$status" -eq 0 ]
}

@test "Invalid number of rows" {
  run bin/tp3 --num-rows a
  [ "$status" -eq 3 ]
}

@test "Invalid number of columns" {
  run bin/tp3 --num-rows 3 --num-cols b
  [ "$status" -eq 3 ]
}

@test "Format png without filename" {
  run bin/tp3 --output-format png
  [ "$status" -eq 4 ]
}

@test "Bad option" {
  run bin/tp3 --bad-option
  [ "$status" -eq 5 ]
}

@test "With solution" {
  run bin/tp3 --with-solution
  [ "$status" -eq 0 ]
}

@test "Format png With solution not implemented" {
  run bin/tp3 --with-solution --output-format png --output-filename maze.png
  [ "$status" -eq 6 ]
}
