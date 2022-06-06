#pragma once
#if _WIN32
#include <string>
#include <vector>

const std::string modelPath = "../media/sphere.obj";
const std::string modelPath1 = "../media/rock.obj";
const std::string modelPath2 = "../media/untitled.obj";
const std::string modelPath4 = "../media/door.obj";
const std::string modelPath6 = "../media/Arms_Left.obj";
const std::string modelPath7 = "../media/Arms_Right.obj";
const std::string modelPath8 = "../media/bear.obj";

const std::string earthTexturePath = "../media/earthmap.jpg";
const std::string planetTexturePath = "../media/planet_Quom1200.png";
const std::vector<std::string> skyboxTexturePaths = {
    "../media/starfield/Right_Tex.jpg",
    "../media/starfield/Left_Tex.jpg",
    "../media/starfield/Down_Tex.jpg",
    "../media/starfield/Up_Tex.jpg",
    "../media/starfield/Front_Tex.jpg",
    "../media/starfield/Back_Tex.jpg" };

const std::string musicPath = "../media/night.mp3";
#endif

#if __APPLE__
#include <string>
#include <vector>

const std::string modelPath = "../../media/sphere.obj";
const std::string modelPath1 = "../../media/rock.obj";
const std::string modelPath2 = "../../media/untitled.obj";
const std::string modelPath4 = "../../media/door.obj";
const std::string modelPath6 = "../../media/Arms_Left.obj";
const std::string modelPath7 = "../../media/Arms_Right.obj";
const std::string modelPath8 = "../../media/bear.obj";

const std::string earthTexturePath = "../../media/earthmap.jpg";
const std::string planetTexturePath = "../../media/planet_Quom1200.png";
const std::vector<std::string> skyboxTexturePaths = {
    "../../media/starfield/Right_Tex.jpg",
    "../../media/starfield/Left_Tex.jpg",
    "../../media/starfield/Down_Tex.jpg",
    "../../media/starfield/Up_Tex.jpg",
    "../../media/starfield/Front_Tex.jpg",
    "../../media/starfield/Back_Tex.jpg" };

const std::string musicPath = "../../media/night.mp3";
#endif