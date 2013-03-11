// The Firmament project
// Copyright (c) 2013 Malte Schwarzkopf <malte.schwarzkopf@cl.cam.ac.uk>
//
// Representation of a Quincy-style scheduling flow graph.

#ifndef FIRMAMENT_MISC_FLOW_GRAPH_H
#define FIRMAMENT_MISC_FLOW_GRAPH_H

#include <string>

#include "base/common.h"
#include "base/types.h"
#include "misc/flow_graph_arc.h"
#include "misc/flow_graph_node.h"
#include "engine/topology_manager.h"
#include "base/resource_topology_node_desc.pb.h"

namespace firmament {

class FlowGraph {
 public:
  FlowGraph();
  void AddJobNodes();
  void AddResourceNode(ResourceTopologyNodeDescriptor* rtnd);
  void AddResourceTopology(ResourceTopologyNodeDescriptor* resource_tree);
  void AddTaskNode();

 protected:
  FlowGraphArc* AddArcInternal(uint64_t src, uint64_t dst);
  FlowGraphArc* AddArcInternal(FlowGraphNode* src, FlowGraphNode* dst);
  FlowGraphNode* AddNodeInternal(uint64_t id);
  void AddSpecialNodes();
  FlowGraphNode* NodeForResourceID(const ResourceID_t& res_id);
  inline uint64_t next_id() { return current_id_++; }

  // Graph structure containers and helper fields
  uint64_t current_id_;
  unordered_map<uint64_t, FlowGraphNode*> node_map_;
  unordered_set<FlowGraphArc*> arc_set_;
  FlowGraphNode* cluster_agg_node_;
  FlowGraphNode* sink_node_;
  // Resource and task mappings
  unordered_map<TaskID_t, uint64_t> task_to_nodeid_map_;
  unordered_map<ResourceID_t, uint64_t> resource_to_nodeid_map_;
};

}  // namespace firmament

#endif  // FIRMAMENT_MISC_FLOW_GRAPH_H