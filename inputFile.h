//
//  inputFile.h
//  airticket
//
//  Created by lazybone on 11/6/13.
//  Copyright (c) 2013 lazybone. All rights reserved.
//

#ifndef __airticket__inputFile__
#define __airticket__inputFile__

class inputFile
{
public:
    inputFile();
    ~inputFile();
    static inputFile* Instance();
    void readFile(const char *strpath);
    void putoutResult();
private:
    void readfile(const char *strpath);
    int readM(int &ipos,char *str);
    int readC(int &ipos,char *str);
    int readP(int &ipos,char *str);
    int readNum(int &ipos,char *str);
    int string2int(char *str);
};

#define InputF inputFile::Instance() 

#endif /* defined(__airticket__inputFile__) */
