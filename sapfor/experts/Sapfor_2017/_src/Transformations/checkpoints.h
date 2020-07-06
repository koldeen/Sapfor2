#pragma once

struct UserFiles
{
    std::vector<SgStatement*> placesOpen;
    std::vector<SgStatement*> placesClose;
    std::vector<SgStatement*> placesWrite;
    std::vector<SgStatement*> placesRead;
};

void createCheckpoints(SgFile* file, const std::map<std::string, CommonBlock>& commonBlocks, const std::map<int, UserFiles>& filesInfo);
void convertSaveToModule(SgFile* file);
void preprocessOpenOperators(SgFile* file, std::map<int, UserFiles>& filesInfo);

