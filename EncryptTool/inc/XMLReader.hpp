/*
** EPITECH PROJECT, 2020
** OOP - Arcade 3000
** File description:
** OOP_arcade_2019 : XMLReader
*/

#ifndef __XML_READER__
#define __XML_READER__

#include <iostream>
#include <list>
#include <vector>
#include <map>

class XMLReader
{
    public:
        XMLReader();
        static std::list<std::vector<std::string> >getGroup(const std::string &groupStart,
            const std::string &groupEnd, const std::list<std::string> &content);
        static std::vector<std::string> splitString(const std::string &delimiter, std::string str);
        static std::string removeTabulation(const std::string &line);
        void startGroup(const std::string &groupName);
        void endGroup(const std::string &groupName);
        void clearFile();
        std::list<std::string> getContent() const;
        void writeInfo(const std::map<std::string, std::string> &content);
        static void putOnTab(std::list<std::vector<std::string> > &list, const std::vector<std::string> &tab);

    private:
        const std::string _header = "<?xml version='1.0' encoding='utf-8'?>";
        unsigned int _tabCounter;
        std::list<std::string> _content;
};

#endif //__XML_READER__