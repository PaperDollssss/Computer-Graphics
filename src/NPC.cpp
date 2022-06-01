//
// Created by 胡宇森 on 2022/6/1.
//

#include "NPC.h"
#include <iostream>
npc::npc() {
  index = 0;
  count = 0;
  for (int i = 0; i <= 100; i++) {
    std::string filePath = "../../media/postures/pose";
    if (count < 10) {
      filePath += "00";
      filePath += std::to_string(count);
    } else if (count < 100) {
      filePath += "0";
      filePath += std::to_string(count);
    } else {
      filePath += std::to_string(count);
    }
    filePath += ".obj";
    //    Model *_npc = new Model(filePath);
    //    _npc->scale = glm::vec3(0.01f, 0.01f, 0.01f);
    //    _npc->position = glm::vec3(-5, -5, -5);
    std::shared_ptr<Model> _npc;
    _npc.reset(new Model(filePath));
    _npc->scale = glm::vec3(0.01f, 0.01f, 0.01f);
    _npc->position = glm::vec3(-5, -5, -5);
    _npcVector.push_back(_npc);
    count++;
  }
}

std::shared_ptr<Model> npc::changeModel() {
  std::shared_ptr<Model> curNPC = _npcVector[index];
  if (index < 100)
    index++;
  else
    index = 0;
  return curNPC;
}