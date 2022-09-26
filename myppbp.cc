/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <iostream>
#include <fstream>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/log.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("PPBP");

int
main (int argc, char *argv[])
{
  uint32_t nNodes = 1;
  Time simulationTime = Seconds (10);
  double hurst = 0.5;

  CommandLine cmd (__FILE__);
  cmd.AddValue ("n", "Number of source nodes.", nNodes);
  cmd.AddValue ("h", "Desired hurst parameter value.", hurst);
  cmd.AddValue ("t", "Total simulation time.", simulationTime);
  cmd.Parse (argc, argv);

  NS_LOG_INFO ("Build network topology.");
  NodeContainer nodes;
  nodes.Create (nNodes + 1);

  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  csma.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices = csma.Install(nodes);
  InternetStackHelper internet;
  internet.Install (nodes);

  NS_LOG_INFO ("Assign IP Addresses.");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.1.0.0", "255.255.255.0");
  Ipv4InterfaceContainer addresses = ipv4.Assign (devices);

  NS_LOG_INFO ("Create applications.");
  uint16_t port = 8080;

  Address targetAddress (InetSocketAddress (addresses.GetAddress (0), port));
  PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", targetAddress);
  ApplicationContainer serverApp = packetSinkHelper.Install (nodes.Get (0));
  serverApp.Start (Seconds (0));
  serverApp.Stop (simulationTime);

  for (uint32_t i = 1; i < nodes.GetN (); i++)
    {
      PPBPHelper ppbp ("ns3::TcpSocketFactory", targetAddress);
      ppbp.SetAttribute ("H", DoubleValue (hurst));
      ppbp.SetAttribute ("BurstIntensity", DataRateValue (DataRate ("100Kb/s")));
      ApplicationContainer clientApp = ppbp.Install (nodes.Get (i));
      clientApp.Start (Seconds (0));
      clientApp.Stop (simulationTime);
    }

  NS_LOG_INFO ("Enable static global routing.");
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  NS_LOG_INFO ("Enable pcap tracing.");
  std::ostringstream filename;
  filename << "ppbp"
           << "_h"
           << std::to_string(hurst).substr(0, 3)
           << "-"
           << RngSeedManager::GetRun ()
           << ".pcap";
  csma.EnablePcap (filename.str (), devices.Get (0), true, true);

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Stop (simulationTime);
  Simulator::Run ();
  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");
  NS_LOG_INFO ("See " << filename.str ());
}
