//
// Created by 胡宇森 on 2022/6/1.
//

#ifndef FINAL_PROJECT_SRC_NPC_H_
#define FINAL_PROJECT_SRC_NPC_H_
#include "base/model.h"
#include <memory>
#include <string>
#include <vector>

class npc {
public:
  npc();
  std::shared_ptr<Model> changeModel();
  ~npc() = default;

private:
  int count;
  int index;
  std::vector<std::shared_ptr<Model>> _npcVector;
};

#endif // FINAL_PROJECT_SRC_NPC_H_
