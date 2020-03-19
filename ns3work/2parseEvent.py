# -*- coding: UTF-8 -*-
from __future__ import division
import os
import re

TYPE_INST = "[INST]"
TYPE_EXEC= "[EXEC]"
TYPE_REMV = "[REMV]"

eventAddrMap = {} 
simulatorTrace = []

with open("logout.x") as logfile:
    lines = logfile.readlines()
    index = 0
    while index != len(lines):
         line = lines[index]
         if re.match("^[0-9]+\.[0-9]{9}s (-1|1|0) EventImpl:Invoke\(", line) != None:
             #先拿到地址
             pos = line.find("(")
             addr = line[pos+1:-2]
             eventAddrMap[addr] = ""
             #拿到事件handler
             count = 0
             while index+1 != len(lines) and count < 20:
                 index += 1
                 count += 1
                 line = lines[index]
                 if  re.match("^[0-9]+\.[0-9]{9}s.*", line) != None:
                     event = line[15:-1]
                     eventAddrMap[addr] = event
                     break
         index += 1

#for k in eventAddrMap.keys():
#    print k + " : " + eventAddrMap[k]
#print len(eventAddrMap)

with open("logout.x") as logfile:
    lines = logfile.readlines()
    index = -1
    while index+1 != len(lines):
        index += 1
        line = lines[index]
        if line.find("Scheduler:Insert(") != -1:
            posL = line.find("(") + 1
            posR = line.find(")")
            #print line[posL:-2]
            paras = line[posL:posR].split(",")
            if len(paras) != 4:
                print "ERROR! insert's paras must be 4!"
                exit(0)
            eventAddr = paras[1].strip()
            timestamp = ("%.9f" % (int(paras[2].strip()) / 10**9)) + 's'
            #print line
            if eventAddr in eventAddrMap.keys():
                simulatorTrace.append([TYPE_INST,timestamp,eventAddrMap[eventAddr]])
            else:
                simulatorTrace.append([TYPE_INST,timestamp,"UnKnown:Event"])
        elif line.find("Scheduler:Remove(") != -1:
            posL = line.find("(") 
            posR = line.find(")") 
            paras = line[posL+1, posR].split(",")
            eventAddr = paras[1].strip()
            timestamp = paras[2].strip()
            if eventAddr in eventAddrMap.keys():
                simulatorTrace.append([TYPE_REMV,timestamp,eventAddrMap[eventAddr]])
            else:
                simulatorTrace.append([TYPE_REMV,timestamp,"UnKnown:Event"])
#        elif re.match("^[0-9]+\.[0-9]{9}s (-1|1|0) .*?SimulatorImpl:ProcessOneEvent\(0x.*$",line) != None:
        elif re.match("^[0-9]+\.[0-9]{9}s (-1|1|0) .*?SimulatorImpl:ProcessOneEvent\(.*$",line) != None:
            while index+1 != len(lines):
                index += 1
                line = lines[index]
                pos = line.find("EventImpl:Invoke(")
                if pos != -1:
                    pos =  line.find("(")
                    eventAddr = line[pos+1:-2]
                    timestamp = line[:12]
                    if eventAddr in eventAddrMap.keys():
                        simulatorTrace.append([TYPE_EXEC,timestamp,eventAddrMap[eventAddr]])
                    else:
                        simulatorTrace.append([TYPE_EXEC,timestamp,"UnKnown:Event"])
                    break
                
for trace in simulatorTrace:
    print trace
        



