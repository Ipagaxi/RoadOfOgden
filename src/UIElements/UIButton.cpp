#include "UIElements/UIButton.hpp"

UIButton::UIButton(std::string filePath) {
    int sep_pos = filePath.find(".");
    std::string fileName = fileName.substr(0, sep_pos);
    std::string fileType = fileName.substr(sep_pos + 1);
    UIButton::basicTX.loadFromFile(RESOURCE_PATH + filePath);
    UIButton::clickedTX.loadFromFile(RESOURCE_PATH  + fileName + "_click" + fileType);
    UIButton::hoveredTX.loadFromFile(RESOURCE_PATH + fileName + "_hover" + fileType);
}