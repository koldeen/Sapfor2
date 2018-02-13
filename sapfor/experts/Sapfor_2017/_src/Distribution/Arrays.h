#pragma once
#include <string>
#include <map>
#include <set>
#include "Array.h"

#define MAP std::map
#define SET std::set
#define VECTOR std::vector
#define STRING std::string
#define PAIR std::pair

namespace Distribution
{
    template<typename vType>
    class Arrays
    {
    private:
        unsigned nextVertexNum;

        MAP<Array*, VECTOR<vType>> numVertsInGraph;
        MAP<STRING, Array*> arraysByName;
        SET<Array*> arrays;
        VECTOR<STRING> arrayNameByVertex;
        VECTOR<PAIR<int, Array*>> arrayDimInfoByVertex;
    public:
        Arrays() { nextVertexNum = 0; }

        Arrays(const Arrays &copy)
        {
            nextVertexNum = copy.nextVertexNum;
            numVertsInGraph = copy.numVertsInGraph;
            arraysByName = copy.arraysByName;
            arrays = copy.arrays;
            arrayNameByVertex = copy.arrayNameByVertex;
            arrayDimInfoByVertex = copy.arrayDimInfoByVertex;
        }
        
        void UpdateLinks(const MAP<Array*, Array*> &oldNewArrays)
        {
            SET<Array*> newArrays;
            for (auto &array : arrays)
                newArrays.insert(oldNewArrays.find(array)->second);
            arrays = newArrays;

            for (auto &elem : arraysByName)
                elem.second = oldNewArrays.find(elem.second)->second;

            for (auto &elem : arrayDimInfoByVertex)
                elem.second = oldNewArrays.find(elem.second)->second;

            MAP<Array*, VECTOR<vType>> newNumVertsInGraph;
            for (auto &elem : numVertsInGraph)
                newNumVertsInGraph.insert(std::make_pair(oldNewArrays.find(elem.first)->second, elem.second));
            numVertsInGraph = newNumVertsInGraph;
        }

        void cleanData()
        {
            nextVertexNum = 0;
            numVertsInGraph.clear();
            arraysByName.clear();
            arrays.clear();
            arrayNameByVertex.clear();
            arrayDimInfoByVertex.clear();
        }

        int AddArrayToGraph(Array *array)
        {
            int status = 0;
            auto foundIt = numVertsInGraph.find(array);
            if (foundIt == numVertsInGraph.end())
            {
                const int dimSize = array->GetDimSize();
                VECTOR<vType> vertexNum(dimSize);

                for (int i = 0; i < dimSize; ++i)
                {
                    vertexNum[i] = nextVertexNum + i;

                    STRING newName(array->GetName());
                    newName += "." + std::to_string(i);
                    arrayNameByVertex.push_back(newName);
                    arrayDimInfoByVertex.push_back(std::make_pair(i, array));
                }

                nextVertexNum += dimSize;
                numVertsInGraph.insert(foundIt, make_pair(array, vertexNum));
                arrays.insert(array);
                arraysByName.insert(arraysByName.end(), make_pair(array->GetName(), array));
            }
            else
                status = 1;

            return status;
        }

        int GetVertNumber(Array *array, const int dimNum, vType &retVal) const
        {
            int err = 0;
            auto foundIt = numVertsInGraph.find(array);
            if (foundIt == numVertsInGraph.end())
                err = -1;
            else
            {
                const int maxDims = array->GetDimSize();
                if (dimNum >= maxDims)
                    err = -1;
                else
                    retVal = foundIt->second[dimNum];
            }
            return err;
        }


        int GetAllVertNumber(const Array *array, std::vector<vType> &retVal) const
        {
            int err = 0;
            auto foundIt = numVertsInGraph.find((Array*)array);
            if (foundIt == numVertsInGraph.end())
                err = -1;
            else
                retVal = foundIt->second;
            return err;
        }

        int GetDimNumber(const Array *array, const vType vertexN, vType &retVal) const
        {
            int err = 0;
            auto foundIt = numVertsInGraph.find((Array*)array);
            if (foundIt == numVertsInGraph.end())
                err = -1;
            else
            {
                const int maxDims = array->GetDimSize();
                for (int i = 0; i < maxDims; ++i)
                {
                    if (foundIt->second[i] == vertexN)
                    {
                        retVal = i;
                        return 0;
                    }
                }
                err = -1;
            }
            return err;
        }

        int GetNameByVertex(const vType vert, STRING &name) const
        {
            if (vert >= (vType)arrayNameByVertex.size())
                return -1;
            else
            {
                name = arrayNameByVertex[vert];
                return 0;
            }
        }

        Array* GetArrayByVertex(const vType vert) const
        {
            STRING name;
            int res = GetNameByVertex(vert, name);
            Array *retVal = NULL;

            if (res != -1)
            {
                int count = 0;
                for (int k = (int)name.size() - 1; k >= 0; --k, ++count)
                {
                    if (name[k] == '.')
                    {
                        name[k] = '\0';
                        break;
                    }
                }
                name.resize(name.size() - count - 1);
                retVal = GetArrayByName(name);
            }
            
            return retVal;
        }

        Array* GetArrayByName(const STRING &name) const
        {
            auto res = arraysByName.find(name);
            if (res != arraysByName.end())
                return res->second;
            else
                return NULL;
        }
        
        int GetInfoByVertex(const vType vertex, std::pair<int, Array*> &info) const
        {
            int err = (arrayDimInfoByVertex.size() >= vertex) ? 1 : 0;
            if (arrayDimInfoByVertex.size() < vertex)
                info = arrayDimInfoByVertex[vertex];
            return err;
        }

        const SET<Array*>& GetArrays() const { return arrays; }

        unsigned GetMaxVertexNum() const { return nextVertexNum; }

        void SaveArraysToFile(FILE *file) const
        {
            if (file)
            {
                fprintf(file, "%d\n", nextVertexNum);
                int count = numVertsInGraph.size();
                fprintf(file, "%d\n", count);
                for (auto &elem : numVertsInGraph)
                {
                    fprintf(file, "%d\n", elem.first->GetArrayUniqKey().size());
                    fprintf(file, "%s\n", elem.first->GetArrayUniqKey().c_str());
                    int dimCount = elem.second.size();
                    fprintf(file, "%d\n", dimCount);
                    for (int z = 0; z < dimCount; ++z)
                        fprintf(file, "%d\n", elem.second[z]);
                }
            }
        }

        //load and check
        bool LoadArraysFromFile(FILE *file, const SET<Array*> &currArrays, const int nextVertexNumOld)
        {
            bool status = true;
            if (file)
            {
                char tmpChar;
                MAP<STRING, Array*> keys;
                for (auto &elem : currArrays)
                    keys.insert(std::make_pair(elem->GetArrayUniqKey(), elem));

                fscanf(file, "%d", &nextVertexNum);
                fscanf(file, "%c", &tmpChar);
                if (nextVertexNumOld != nextVertexNum)
                    return false;                

                int count;
                fscanf(file, "%d", &count);
                fscanf(file, "%c", &tmpChar);
                for (int i = 0; i < count; ++i)
                {
                    int strLen = 0;
                    fscanf(file, "%d", &strLen);
                    fscanf(file, "%c", &tmpChar);

                    string uniqKey = "";
                    for (int k = 0; k < strLen; ++k)
                    {
                        char symb;
                        fscanf(file, "%c", &symb);
                        uniqKey += symb;
                    }
                    fscanf(file, "%c", &tmpChar);
                    
                    int dimCount = 0;
                    fscanf(file, "%d", &dimCount);
                    fscanf(file, "%c", &tmpChar);
                    vector<vType> tmp(dimCount);
                    for (int z = 0; z < dimCount; ++z)
                    {
                        fscanf(file, "%d", &(tmp[z]));
                        fscanf(file, "%c", &tmpChar);
                    }

                    auto found = keys.find(uniqKey);
                    if (found == keys.end())
                    {
                        status = false;
                        break;
                    }
                    else
                    {
                        numVertsInGraph.insert(std::make_pair(found->second, tmp));
                        arraysByName.insert(std::make_pair(found->second->GetName(), found->second));
                        arrays.insert(found->second);
                    }
                }
            }
            else
                status = false;
            return status;
        }
    };
}
#undef MAP
#undef SET
#undef VECTOR
#undef STRING
#undef PAIR