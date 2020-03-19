/***************************************************
* A DDoS Simulation Model(simple udp flood)
* Author: Hox Zheng
* Data: 2020/03/13
****************************************************/

#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"

using namespace ns3;


/* 10.0.2.0      
N-----------| 10.0.1.0           20.0.1.0   |--------V
N-----------R-----------R(Core)-------------R--------V
N-----------|           |                   |--------V
   10.0.4.0             |
N-----------| 10.0.3.0  |        
N-----------R-----------|
N-----------|           |
              10.0.5.0  |
.........................
*/

NS_LOG_COMPONENT_DEFINE ("MyDDoSExample");

int 
main (int argc, char *argv[])
{
  //Open log.
  LogComponentEnable("MyDDoSExample", LOG_LEVEL_INFO);
  //Open Udp log
  // LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  // LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  //Topo Scale. 
  uint32_t botNetNum = 10; 
  uint32_t botNumPerNet = 10;
  uint32_t victimNum = 5;

  //Send rate.
  uint32_t packetSize = 512;
  uint32_t packetCount = 100000000;
  double packetInterval = 1000;  //  100 ms
  double time = 60;

  //Args parser.
  CommandLine cmd;
  cmd.AddValue ("BotNetNum", "Number of botnet", botNetNum);
  cmd.AddValue ("BotNumPerNet", "Number of host in a botnet", botNumPerNet);
  cmd.AddValue ("VictimNum", "Number of victim server", victimNum);
  cmd.AddValue ("PacketSize", "Packet size in bytes", packetSize);
  cmd.AddValue ("PacketCount", "Number of packets to send", packetCount);
  cmd.AddValue ("PacketInterval", "Interval between packets", packetInterval);
  cmd.AddValue ("Time", "Clients send time.", time);
  cmd.Parse (argc, argv);
   
  //Model Creation.
  //Create core router.
  NS_LOG_INFO ("Create core router.");
  Ptr<Node> coreRouter = CreateObject<Node> ();
  //VictimNet holder.
  NodeContainer victimNetToCore;
  NetDeviceContainer p2pDevices_100G;
  std::vector<NodeContainer> victimNet(victimNum);
  std::vector<NetDeviceContainer> victimNetDevices(victimNum);
  //BotNets holder.
  std::vector<NodeContainer> botNetToCores(botNetNum);
  std::vector<NetDeviceContainer> botNetToCoreDevices(botNetNum);
  std::vector<std::vector<NodeContainer>> botNets(botNetNum, std::vector<NodeContainer>(botNumPerNet));
  std::vector<std::vector<NetDeviceContainer>> botNetsDevices(botNetNum, std::vector<NetDeviceContainer>(botNumPerNet));

  NS_LOG_INFO ("Create Victim Net:  " << victimNum << " servers and an edge router.");
  victimNetToCore.Add(coreRouter);
  victimNetToCore.Create(1);
  PointToPointHelper pointToPoint_100G;
  pointToPoint_100G.SetDeviceAttribute ("DataRate", StringValue ("100Gbps"));
  pointToPoint_100G.SetChannelAttribute ("Delay", StringValue ("1ms"));
  p2pDevices_100G = pointToPoint_100G.Install(victimNetToCore);
  for(uint32_t i=0; i < victimNum; ++i)
  {
    NodeContainer& server = victimNet[i];
    NetDeviceContainer& devices = victimNetDevices[i];
    server.Add(victimNetToCore.Get(1));
    server.Create(1);
    PointToPointHelper pointToPoint_10G;
    pointToPoint_10G.SetDeviceAttribute ("DataRate", StringValue ("10Gbps"));
    pointToPoint_10G.SetChannelAttribute ("Delay", StringValue ("1ms"));
    devices = pointToPoint_10G.Install(server);
  }
  NS_LOG_INFO ("Create BotNets :  " << botNetNum << " botnets, " << "each has "<< botNumPerNet <<" bots." );
  for(uint32_t i=0; i < botNetNum; ++i)
  {
    NodeContainer& botNetToCore = botNetToCores[i];
    NetDeviceContainer& devices = botNetToCoreDevices[i];
    botNetToCore.Add(coreRouter);
    botNetToCore.Create(1);
    PointToPointHelper pointToPoint_1000M;
    pointToPoint_1000M.SetDeviceAttribute ("DataRate", StringValue ("1000Mbps"));
    pointToPoint_1000M.SetChannelAttribute ("Delay", StringValue ("1ms"));
    devices = pointToPoint_1000M.Install(botNetToCore);
    std::vector<NodeContainer>& botNet = botNets[i];
    std::vector<NetDeviceContainer>& botNetDevices= botNetsDevices[i];
    for(uint32_t j=0; j < botNumPerNet; ++j)
    {
        NodeContainer& bot = botNet[j];
        NetDeviceContainer& devices = botNetDevices[j];
        bot.Add(botNetToCore.Get(1));
        bot.Create(1);
        PointToPointHelper pointToPoint_100M;
        pointToPoint_100M.SetDeviceAttribute ("DataRate", StringValue ("100Mbps"));
        pointToPoint_100M.SetChannelAttribute ("Delay", StringValue ("1ms"));
        NetDeviceContainer p2pDevices_100M;
        devices = pointToPoint_100M.Install(bot);
    }
  }

  // Install internet stack.
  NS_LOG_INFO ("Install internet stack to all nodes." );
  InternetStackHelper stack;
  stack.Install(coreRouter);
  stack.Install(victimNetToCore.Get(1));
  for(uint32_t i=0; i < victimNum; ++i)
    stack.Install(victimNet[i].Get(1));
  for(uint32_t i=0; i < botNetNum; ++i)
  {
    stack.Install(botNetToCores[i].Get(1));
    for(uint32_t j=0; j < botNumPerNet; ++j)
      stack.Install(botNets[i][j].Get(1));
  }

  //Interfaces holder.
  Ipv4InterfaceContainer victimNetToCoreInfs;
  std::vector<Ipv4InterfaceContainer> victimNetInfs(victimNum);
  std::vector<Ipv4InterfaceContainer> botNetToCoreInfs(botNetNum);
  std::vector<std::vector<Ipv4InterfaceContainer>> botNetsInfs(botNetNum, std::vector<Ipv4InterfaceContainer>(botNumPerNet));

  // Alloc ipv4 address to all nodes and all interfaces.
  NS_LOG_INFO ("Alloc ipv4 address to all nodes and all interfaces." );
  Ipv4AddressHelper address;
  address.SetBase ("20.0.0.0", "255.255.255.0");
  victimNetToCoreInfs = address.Assign (p2pDevices_100G);
  for(uint32_t i=0; i < victimNet.size(); ++i){
    Ipv4InterfaceContainer& inf = victimNetInfs[i];
    address.SetBase (std::string("20.0."+std::to_string(i+1)+".0").c_str(), "255.255.255.0");
    inf = address.Assign (victimNetDevices[i]); 
  }
  for(uint32_t i=0; i<botNetNum; ++i){
    Ipv4InterfaceContainer& toCoreinf = botNetToCoreInfs[i];
    address.SetBase (std::string("10."+std::to_string(i+1)+".0.0").c_str(), "255.255.255.0");
    toCoreinf = address.Assign (botNetToCoreDevices[i]); 
    for(uint32_t j=0; j<botNumPerNet; ++j){
      Ipv4InterfaceContainer& inf = botNetsInfs[i][j];
      address.SetBase (std::string("10."+std::to_string(i+1)+"."+std::to_string(j+1)+".0").c_str(), "255.255.255.0");
      inf = address.Assign (botNetsDevices[i][j]); 
    }
  }
  
  UdpEchoServerHelper echoServer (9);
  std::vector<ApplicationContainer> serverApps(victimNum);
  for(uint32_t i=0; i < victimNum; ++i){
    serverApps[i] = echoServer.Install(victimNet[i].Get(1));
    serverApps[i].Start (Seconds (1.0));
    serverApps[i].Stop (Seconds (time));
  }

  std::vector<std::vector<ApplicationContainer>> clientApps(botNetNum,std::vector<ApplicationContainer>(botNumPerNet));
  for(uint32_t i=0; i<botNetNum; ++i){
      for(uint32_t j=0; j<botNumPerNet; ++j){
        uint32_t serverIndex = j % victimNum;
        UdpEchoClientHelper echoClient(victimNetInfs[serverIndex].GetAddress(1),9);
        echoClient.SetAttribute ("MaxPackets", UintegerValue (packetCount));
        echoClient.SetAttribute ("Interval", TimeValue (MilliSeconds (packetInterval)));
        echoClient.SetAttribute ("PacketSize", UintegerValue (packetSize));
        clientApps[i][j] = echoClient.Install(botNets[i][j]);
        clientApps[i][j].Start (Seconds (1.0));
        clientApps[i][j].Stop (Seconds (time));
      }
  }
  
  // Start global routing...
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();
  
  NS_LOG_INFO ("Run Simulation.");
  std::clock_t tBegin = std::clock();
  Simulator::Run ();
  std::clock_t tEnd = std::clock();
  Simulator::Destroy ();
  std::clock_t costTime = (tEnd - tBegin)/CLOCKS_PER_SEC;
  NS_LOG_INFO ("Done. Cost real time: " << costTime << " seconds.");
}
