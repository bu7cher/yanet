#pragma once

#include <nlohmann/json.hpp>

#include "base.h"
#include "common/idp.h"

namespace acl
{

// starting id for autogenerated firewall rules
const uint32_t FW_GENRULES_START_ID = 0x3FFFFF;
const uint32_t FW_STATES_START_ID = 0x0FFFFFF;
const uint32_t FW_DISPATCHER_START_ID = 0x1FFFFFFF;

using ids_t = std::vector<uint32_t>;

struct result_t
{
	common::idp::updateGlobalBase::acl_network_ipv4_source::request acl_network_ipv4_source;
	common::idp::updateGlobalBase::acl_network_ipv4_destination::request acl_network_ipv4_destination;
	common::idp::updateGlobalBase::acl_network_ipv6_source::request acl_network_ipv6_source;
	common::idp::updateGlobalBase::acl_network_ipv6_destination_ht::request acl_network_ipv6_destination_ht;
	common::idp::updateGlobalBase::acl_network_ipv6_destination::request acl_network_ipv6_destination;
	common::idp::updateGlobalBase::acl_network_table::request acl_network_table;
	common::idp::updateGlobalBase::acl_network_flags::request acl_network_flags;
	common::idp::updateGlobalBase::acl_transport_layers::request acl_transport_layers;
	std::vector<common::idp::updateGlobalBase::acl_transport_table::request> acl_transport_tables;
	common::idp::updateGlobalBase::acl_total_table::request acl_total_table;
	common::idp::updateGlobalBase::acl_values::request acl_values;

	std::vector<ids_t> ids_map;
	std::vector<acl::rule_info_t> dispatcher;
	std::map<uint32_t, std::vector<acl::rule_info_t>> rules;
	std::map<std::string, tAclId> in_iface_map;
	std::map<std::string, tAclId> out_iface_map;
	std::map<tAclId, std::set<tAclId>> acl_map;

	std::vector<std::string> dump_id_to_tag;
	std::map<std::string, uint32_t> tag_to_dump_id;
};

iface_map_t ifaceMapping(std::map<std::string, controlplane::base::logical_port_t> logicalPorts,
                         std::map<std::string, controlplane::route::config_t> routes);

using unwind_result = std::vector<std::tuple<std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>,
                                             std::optional<std::string>>>;

unwind_result unwind(const std::map<std::string, controlplane::base::acl_t>& acls,
                     const acl::iface_map_t& ifaces,
                     const std::optional<std::string>& module,
                     const std::optional<std::string>& direction,
                     const std::optional<std::string>& network_source,
                     const std::optional<std::string>& network_destination,
                     const std::optional<std::string>& fragment,
                     const std::optional<std::string>& protocol,
                     const std::optional<std::string>& transport_source,
                     const std::optional<std::string>& transport_destination,
                     const std::optional<std::string>& transport_flags,
                     const std::optional<std::string>& recordstate);

std::set<uint32_t> lookup(const std::map<std::string, controlplane::base::acl_t>& acls,
                          const acl::iface_map_t& ifaces,
                          const std::optional<std::string>& module,
                          const std::optional<std::string>& direction,
                          const std::optional<std::string>& network_source,
                          const std::optional<std::string>& network_destination,
                          const std::optional<std::string>& fragment,
                          const std::optional<std::string>& protocol,
                          const std::optional<std::string>& transport_source,
                          const std::optional<std::string>& transport_destination);

void compile(const std::map<std::string, controlplane::base::acl_t>& acls,
             const acl::iface_map_t& ifaces,
             result_t& result);

} // namespace acl
