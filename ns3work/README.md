# NS3 work

## WorkTraces

### 2020-02-28

An event executation parser, which can be very helpful for analyse and design the new simulator.
The python script **2parseEvent.py** is based on the log file of ns3, and there is an example **logout.x**.
The usage of the script is here:
```bash
# log all to a file named logout.x
NS_LOG="*" ./waf --run scratch/first > logout.x 2>&1
python 2parseEvent.py
```

The output looks like following:

```
['[INST]', '0.000000000s', 'Object:Initialize(0x555bb9c51b40)']
['[INST]', '0.000000000s', 'Object:Initialize(0x555bb9c7f5f0)']
['[INST]', '0.000000000s', 'Object:Initialize(0x555bb9c1c8c0)']
['[INST]', '0.000000000s', 'Object:Initialize(0x555bb9c1cb40)']
['[INST]', '0.000000000s', 'UdpEchoClientApplication:Send(0x555bb9c191d0)']
['[INST]', '0.000000000s', 'Object:Initialize(0x555bb9c1dfd0)']
['[INST]', '0.000000000s', 'Object:Initialize(0x555bb9bb67a0)']
['[INST]', '0.000000000s', 'Object:Initialize(0x555bb9c191d0)']
['[EXEC]', '0.000000000s', 'Object:Initialize(0x555bb9c51b40)']
['[INST]', '2.000000000s', 'UdpEchoClientApplication:StartApplication(0x555bb9c191d0)']
['[INST]', '10.000000000s', ' UdpEchoClientApplication:StopApplication(0x555bb9c191d0)']
['[EXEC]', '0.000000000s', 'Object:Initialize(0x555bb9c7f5f0)']
['[INST]', '1.000000000s', 'UdpEchoServerApplication:StartApplication(0x555bb9bb67a0)']
['[INST]', '10.000000000s', ' UdpEchoServerApplication:StopApplication(0x555bb9bb67a0)']
['[EXEC]', '0.000000000s', 'Object:Initialize(0x555bb9c1c8c0)']
['[EXEC]', '0.000000000s', 'Object:Initialize(0x555bb9c1cb40)']
['[EXEC]', '0.000000000s', 'UdpEchoClientApplication:Send(0x555bb9c191d0)']
['[EXEC]', '0.000000000s', 'Object:Initialize(0x555bb9c1dfd0)']
['[EXEC]', '0.000000000s', 'Object:Initialize(0x555bb9bb67a0)']
['[EXEC]', '0.000000000s', 'Object:Initialize(0x555bb9c191d0)']
['[EXEC]', '1.000000000s', 'UdpEchoServerApplication:StartApplication(0x555bb9bb67a0)']
['[EXEC]', '2.000000000s', 'UdpEchoClientApplication:StartApplication(0x555bb9c191d0)']
['[INST]', '2.000000000s', 'UdpEchoClientApplication:Send(0x555bb9c191d0)']
['[EXEC]', '2.000000000s', 'UdpEchoClientApplication:Send(0x555bb9c191d0)']
['[INST]', '2.001686400s', 'PointToPointNetDevice:TransmitComplete(0x555bb9c1c8c0)']
['[INST]', '2.003686400s', 'PointToPointNetDevice:Receive(0x555bb9c1cb40, 0x555bb9c21690)']
['[EXEC]', '2.001686400s', 'PointToPointNetDevice:TransmitComplete(0x555bb9c1c8c0)']
['[EXEC]', '2.003686400s', 'PointToPointNetDevice:Receive(0x555bb9c1cb40, 0x555bb9c21690)']
['[INST]', '2.005372800s', 'PointToPointNetDevice:TransmitComplete(0x555bb9c1cb40)']
['[INST]', '2.007372800s', 'PointToPointNetDevice:Receive(0x555bb9c1c8c0, 0x555bb9bea750)']
['[EXEC]', '2.005372800s', 'PointToPointNetDevice:TransmitComplete(0x555bb9c1cb40)']
['[EXEC]', '2.007372800s', 'PointToPointNetDevice:Receive(0x555bb9c1c8c0, 0x555bb9bea750)']
['[EXEC]', '10.000000000', ' UdpEchoClientApplication:StopApplication(0x555bb9c191d0)']
['[EXEC]', '10.000000000', ' UdpEchoServerApplication:StopApplication(0x555bb9bb67a0)']
```

