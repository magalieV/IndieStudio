/*
** EPITECH PROJECT, 2020
** OOP - Arcade 3000
** File description:
** OOP_arcade_2019 : XMLReader
*/

#include "../inc/XMLReader.hpp"
#include <fstream>

XMLReader::XMLReader()
{
    _tabCounter = 0;
}

std::vector<std::string> XMLReader::splitString(const std::string &delimiter, std::string str)
{
    std::string buffer;
    std::vector<std::string> result;
    bool found = false;

    for (char index : str) {
        found = false;
        for (char idx : delimiter) {
            if (index == idx)
                found = true;
        }
        if (found && !buffer.empty()) {
            result.emplace_back(buffer);
            buffer.clear();
        } else if (!found) {
            buffer.push_back(index);
        }
    }
    if (!buffer.empty())
        result.emplace_back(buffer);
    return result;
}

std::string XMLReader::removeTabulation(const std::string &line)
{
    std::string str;

    for (char c : line) {
        if (c != '\t' && c != '\n')
            str.push_back(c);
    }
    return str;
}

void XMLReader::putOnTab(std::list<std::vector<std::string> > &list, const std::vector<std::string> &tab)
{
    unsigned int count = 0;
    std::vector<std::string> values;

    if (tab.empty())
        return;
    for (const std::string line : tab) {
        if (count < 2) {
            values.emplace_back(line);
        } else {
            count = 0;
        }
        count++;
    }
    list.emplace_back(values);
}

std::list<std::vector<std::string> > XMLReader::getGroup(const std::string &groupStart, const std::string &groupEnd,
    const std::list<std::string> &content)
{
    std::list<std::vector<std::string> > list;
    bool mustBeSplit = false;

    for (auto line : content) {
        line = XMLReader::removeTabulation(line);
        if (line == groupStart) {
            mustBeSplit = true;
        } else if (line == groupEnd) {
            mustBeSplit = false;
        }
        if (mustBeSplit) {
            std::vector<std::string> tab = XMLReader::splitString("><\t\n", line);
            XMLReader::putOnTab(list, tab);
        }
    }
    return list;
}

void XMLReader::clearFile()
{
    _content.clear();
    _content.push_back(_header);
}

void XMLReader::startGroup(const std::string &groupName)
{
    std::string tmp;

    for (int i = 0; i < _tabCounter; i++)
        tmp.push_back('\t');
    _content.push_back(tmp + "<" + groupName + ">");
    _tabCounter++;
}

void XMLReader::endGroup(const std::string &groupName)
{
    std::string tmp;

    _tabCounter--;
    if (_tabCounter < 0)
        _tabCounter = 0;
    for (int i = 0; i < _tabCounter; i++)
        tmp.push_back('\t');
    _content.push_back(tmp + "</" + groupName + ">");
}

std::list<std::string> XMLReader::getContent() const
{
    return _content;
}

void XMLReader::writeInfo(const std::map<std::string, std::string> &content)
{
    std::string tmp;

    for (int i = 0; i < _tabCounter; i++)
        tmp.push_back('\t');
    for (const auto &info : content) {
        _content.push_back(tmp + "<" + info.first + ">" + info.second + "</" + info.first + ">");
    }
}