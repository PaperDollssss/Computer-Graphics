cmake_minimum_required(VERSION 3.15)

project(obj_loader)

aux_source_directory(. OBJ_LOADER_SRC)

add_library(obj_loader ${OBJ_LOADER_SRC})

set_target_properties(obj_loader PROPERTIES FOLDER "lib")