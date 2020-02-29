#pragma once

void createCheckpoints(SgFile* file, const std::map<std::string, CommonBlock>& commonBlocks);
void convertSaveToModule(SgFile* file);