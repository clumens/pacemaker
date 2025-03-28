# Pacemaker-3.0.0 (08 Jan 2025)
* 2039 commits with 659 files changed, 23924 insertions(+), 32384 deletions(-)

## Features added since Pacemaker-2.1.9

* For more details, especially about build option changes, see
  https://projects.clusterlabs.org/w/projects/pacemaker/pacemaker_3.0_changes/
* **upgrades:** drop support for rolling upgrades from versions less than 2.0.0
* **Pacemaker Remote:** drop support for Pacemaker 1 cluster nodes connecting
  to Pacemaker Remote 3 or later nodes or bundles, and Pacemaker 3 or later
  cluster nodes connecting to Pacemaker Remote 1.1.14 or earlier nodes
* **build:** drop creation of deprecated `pacemaker_remoted` link to
  `pacemaker-remoted`
* **environment:** drop support for deprecated `HA_cib_timeout`,
  `HA_shutdown_delay`, `PCMK_cib_timeout`, `PCMK_dh_min_bits`, and
  `PCMK_shutdown_delay` variables
* **environment:** `PCMK_panic_action` values are case-sensitive
* **CIB:** XML syntax must be correctly formed (no errors will be ignored)
* **CIB:** `validate-with` must be set, case-sensitive, and not `pacemaker-0.6`,
  `pacemaker-0.7`, `pacemaker-1.1`, `pacemaker-next`, `transitional-0.6`, or
  unknown
* **CIB:** deprecate `concurrent-fencing` cluster option, which now defaults to
  true
* **CIB:** deprecate `record-pending` operation option
* **CIB:** drop support for deprecated cluster options
  `crmd-finalization-timeout`, `crmd-integration-timeout`, and
  `crmd-transition-delay`, and `remove-after-stop`
* **CIB:** drop support for deprecated `poweroff` value of `stonith-action`
  cluster option
* **CIB:** drop support for nodes with `type` set to deprecated value `ping` or
  an invalid value
* **CIB:** drop support for deprecated `nagios` and `upstart` resource classes
* **CIB:** drop support for deprecated `master` resources
* **CIB:** drop support for deprecated `masters` bundle option
* **CIB:** drop support for deprecated bundles using `rkt` containers
* **CIB:** drop support for `instance_attributes` in `rsc_defaults`
* **CIB:** drop support for deprecated `restart-type` resource option
* **CIB:** drop support for deprecated `can-fail`, `can_fail`, and
  `role_after_failure` operation options
* **CIB:** drop support for deprecated `rsc-instance`, `with-rsc-instance`,
  `first-instance`, and `then-instance` constraint options
* **CIB:** drop support for deprecated `lifetime` elements in constraints
* **CIB:** drop support for multiple top-level rules in location constraints or
  name/value blocks
* **CIB:** drop support for `name` attribute when `id-ref` attribute is present
* **CIB:** drop support for deprecated `moon` in `date_spec` elements of rules
* **CIB:** `globally-unique` clone option defaults to true if `clone-node-max`
  is greater than 1
* **CIB:** location constraints with an invalid `score`, `boolean-op`, or
  `role`, colocation constraints with an invalid `score`, `rsc-role`, or
  `with-rsc-role`, and ticket constraints with an invalid `rsc-role` are now
  ignored (previously, default values would be used)
* **CIB:** ignore node expressions for meta-attributes
* **CIB:** treat misconfigured rules and rule expressions as not passing
* **CIB:** treat negative `migration-threshold` as invalid and use default
* **CIB:** invalid fencing level indexes are rejected by schema
* **agents:** drop `ocf:pacemaker:o2cb` resource agent
* **agents:** the `ocf:pacemaker:controld` agent will now always manage
  `dlm_controld` (previously, it would try to manage the long-obsolete
  `gfs_controld` if the resource name started with `gfs`)
* **agents:** do not pass `HA_mcp`, `HA_quorum_type`, `PCMK_mcp`, or
  `PCMK_quorum_type`, environment variables to agents
* **alerts:** don't send deprecated alert environment variables to agents
* **fencer:** drop support for non-clustered mode in fencer
* **fencing:** default `pcmk_host_argument` to `none` if `port` not advertised
* **liblrmd,libstonithd:** use standard default timeout (20s) for meta-data
  actions
* **Pacemaker Remote and pacemaker-based:** support X.509 (SSL/TLS)
  certificates for encrypting Pacemaker Remote connections and remote CIB
  administration
* **pacemaker-based:** reject remote users if PAM not available
* **tools:** `crm_shadow --reset` now requires `--force`
* **tools:** define behavior of `attrd_updater -Q` without `-N`
* **tools:** deprecate `cibadmin --local` option
* **tools:** drop `--text-fancy` command-line option from all tools
* **tools:** drop deprecated `cibadmin --host` and `--no-bcast` options
* **tools:** drop deprecated `crm_resource --get-property`, `--set-property`,
  and `--xml-file` options
* **tools:** `cibadmin --md5-sum-versioned` no longer prints feature set
* **tools:** `crm_resource` rejects invalid timeouts
* **tools:** `crm_resource --delete` does not accept clone instances
* **tools:** `crm_resource --delete` without `-t opt` exits with a usage error
* **tools:** `crm_resource --delete` now succeeds if resource doesn't exist
* **tools:** `crm_resource --option` throws usage error if appropriate
* **tools:** drop deprecated `crm_mon` options `--as-html`,
  `--disable-ncurses`, `--simple-status`, and `--web-cgi`

## Fixes since Pacemaker-2.1.9

* **agents:** `ocf:pacemaker:ping` now uses `grep -E` instead of the obsolete
  `egrep`
* **executor:** avoid use-after-free during shutdown
* **libcrmcommon:** rule expressions with the empty string as value now pass
  when the corresponding node attribute is the empty string
* **libstonithd:** avoid use-after-free when retrieving metadata of Linux-HA
  fence agents
* **libstonithd:** free escaped metadata descriptions correctly
* **scheduler:** apply promotion priority to cloned group instances
* **scheduler:** correctly retrieve any existing fail-count for increment
* **scheduler:** don't apply colocations twice for promotion priority
* **scheduler:** ignore `nvpair` with invalid `id-ref`
* **scheduler:** ignore `value` in `nvpair` with `id-ref`
* **scheduler:** use first action meta-attribute if block has duplicates
* **scheduler:** consider group locations when member is explicit colocation
  dependent
* **tools:** don't trigger an assertion if stdout is closed
* **tools:** CIB clients retry signon if first try fails
* **tools:** don't double-free XML in `crm_verify` after schema update
* **tools:** when injecting a fail count with `crm_simulate`, use an `INFINITY`
  score when the cluster would
* **tools:** validate `stonith_admin --timeout` value

## Public API changes since Pacemaker-2.1.9

* **Python:** add `PACEMAKER_CONFIG_DIR` to `pacemaker.BuildOptions`
* **libcib:** drop `util_compat.h` header
* **libcib:** drop enum values `cib_database`, `cib_inhibit_bcast`,
  `cib_mixed_update`, `cib_quorum_override`, and `cib_zero_copy`
* **libcib:** drop `cib_api_operations_t` members `delete_absolute()`,
  `inputfd()`, `is_master()`, `quit()`, `set_master()`, `set_op_callback()`,
  `set_slave()`, `set_slave_all()`, `signon_raw()`, `update()`
* **libcib:** drop `cib_t` member `op_callback()`
* **libcib:** drop functions `cib_get_generation()`, `cib_metadata()`,
  `cib_pref()`, `get_object_parent()`, `get_object_path()`,
  `get_object_root()`, `query_node_uname()`, and `set_standby()`
* **libcrmcluster:** add `pcmk_cluster_t` member `priv`
* **libcrmcluster:** drop enums (including all their values)
  `crm_ais_msg_class`, `crm_ais_msg_types`, `crm_get_peer_flags`,
  `crm_join_phase`, `crm_node_flags`, and `crm_status_type`
* **libcrmcluster:** drop type alias `crm_node_t`
* **libcrmcluster:** drop struct `crm_peer_node_s`
* **libcrmcluster:** drop `pcmk_cluster_t` members `cpg_handle`,
  `group`, `nodeid`, `uname`, and `uuid`
* **libcrmcluster:** drop global variables `crm_have_quorum`, `crm_peer_cache`,
  `crm_peer_seq`, `crm_remote_peer_cache`
* **libcrmcluster:** drop enum value `crm_join_nack_quiet`
* **libcrmcluster:** drop string constants `CRM_NODE_LOST`, `CRM_NODE_MEMBER`
* **libcrmcluster:** drop functions `cluster_connect_cpg()`,
  `cluster_disconnect_cpg()`, `crm_active_peers()`, `crm_cluster_disconnect()`,
  `crm_get_peer()`, `crm_get_peer_full()`, `crm_is_corosync_peer_active()`,
  `crm_is_peer_active()`, `crm_join_phase_str()`, `crm_peer_destroy()`,
  `crm_peer_init()`, `crm_peer_uname()`, `crm_peer_uuid()`,
  `crm_remote_peer_cache_refresh()`, `crm_remote_peer_cache_remove()`,
  `crm_remote_peer_cache_size()`, `crm_remote_peer_get()`,
  `crm_set_autoreap()`, `crm_set_status_callback()`, `crm_terminate_member()`,
  `crm_terminate_member_no_mainloop()`, `get_local_nodeid()`,
  `get_local_node_name()`, `get_node_name()`, `is_corosync_cluster()`,
  `pcmk_cpg_membership()`, `pcmk_message_common_cs()`, `reap_crm_member()`,
  `send_cluster_message()`, `send_cluster_text()`, `set_uuid()`, and
  `text2msg_type()`
* **libcrmcluster:** rename struct `crm_cluster_s` to `pcmk__cluster`
* **libcrmcommon:** add enum `pcmk_ipc_server` value `pcmk_ipc_unknown`
* **libcrmcommon:** rename structs `pe_action_s` to `pcmk__action`, `pe_node_s`
  to `pcmk__scored_node`, `pe_node_shared_s` to `pcmk__node_details`,
  `pe_resource_s` to `pcmk__resource`, and `pe_working_set_s` to
  `pcmk__scheduler`
* **libcrmcommon:** add `pcmk_node_t` members `assign` and `private`
* **libcrmcommon:** add `pcmk_resource_t` member `private`
* **libcrmcommon:** change `pcmk_scheduler_t` member `flags` type to `uint64_t`
* **libcrmcommon:** add defined constants `PCMK_OCF_ROOT`,
  `PCMK_SCHEDULER_INPUT_DIR`, `PCMK_SCHEMA_DIR`, `PCMK_VALUE_CRASH`,
  `PCMK_VALUE_OFF`, and `PCMK_VALUE_REBOOT`
* **libcrmcommon:** add function `pcmk_common_cleanup()`
* **libcrmcommon:** deprecate  defined constants `CIB_OPTIONS_FIRST`,
  `CRM_SCHEMA_DIRECTORY`, `CRM_SYSTEM_STONITHD`, `CRM_XS`, `OCF_ROOT_DIR`, and
  `PE_STATE_DIR`
* **libcrmcommon:** deprecate functions `calculate_on_disk_digest()`,
  `calculate_operation_digest()`, `calculate_xml_versioned_digest()`,
  `char2score()`, `crm_extended_logging()`, `crm_ipc_connect()`,
  `crm_is_daemon_name()`, `crm_xml_cleanup()`, `crm_xml_init()`,
  `crm_xml_sanitize_id()`, `crm_xml_set_id()`, `expand_idref()`, `free_xml()`,
  `hash2nvpair()`, `pcmk_free_xml_subtree()`, `pcmk_nvpairs2xml_attrs()`,
  `pcmk_sort_nvpairs()`, `pcmk_xml_attrs2nvpairs()`, and `sorted_xml()`
* **libcrmcommon:** drop headers `agents_compat.h`, `compatibility.h`,
  `logging_compat.h`, `mainloop_compat.h`, `results_compat.h`,
  `scores_compat.h`, `tags.h`, `tickets.h`, and `xml_io_compat.h`
* **libcrmcommon:** drop global variables `crm_config_error`,
  `crm_config_warning`, `resource_class_functions[]`, `was_processing_error`,
  and `was_processing_warning`
* **libcrmcommon:** drop enums (including all their values)
  `action_fail_response`, `action_tasks`, `node_type`, `pcmk_rsc_flags`,
  `pcmk_sched_flags`, `pe_action_flags`, `pe_discover_e`, `pe_link_state`,
  `pe_obj_types`, `pe_ordering`, `pe_print_options`, `pe_restart`,
  `rsc_recovery_type`, `rsc_start_requirement`, and `xml_log_options`
* **libcrmcommon:** drop enum `crm_ipc_flags` value `crm_ipc_server_error`,
  and enum `crm_ipc_flags` value `crm_ipc_server_info`
* **libcrmcommon:** drop enum `ocf_exitcode` values `PCMK_OCF_CANCELLED`,
  `PCMK_OCF_DEGRADED_MASTER`, `PCMK_OCF_EXEC_ERROR`, `PCMK_OCF_FAILED_MASTER`,
  `PCMK_OCF_NOT_SUPPORTED`, `PCMK_OCF_OTHER_ERROR`, `PCMK_OCF_PENDING`,
  `PCMK_OCF_RUNNING_MASTER`, `PCMK_OCF_SIGNAL`, and `PCMK_OCF_TIMEOUT`
* **libcrmcommon:** drop enum `pe_find` values `pe_find_anon`, `pe_find_any`,
  `pe_find_clone`, `pe_find_current`, `pe_find_inactive`, and `pe_find_renamed`
* **libcrmcommon:** drop types `pcmk_assignment_methods_t`,
  `pcmk_rsc_methods_t`, `pcmk_tag_t`, `pcmk_ticket_t`,
  `resource_alloc_functions_t`, and `resource_object_functions_t`
* **libcrmcommon:** drop structs `pe_action_wrapper_s`, `pe_tag_s`,
  `pe_ticket_s`, `resource_alloc_functions_s`, and
  `resource_object_functions_s`
* **libcrmcommon:** drop `pcmk_scheduler_t` members `actions`, `action_id`,
  `blocked_resources`, `colocation_constraints`, `config_hash`, `dc_uuid`,
  `disabled_resources`, `failed`, `graph`, `localhost`, `max_valid_nodes`,
  `ninstances`, `node_pending_timeout`, `now`, `num_synapse`, `op_defaults`,
  `ordering_constraints`, `param_check`, `placement_constraints`,
  `placement_strategy`, `priority_fencing_delay`, `recheck_by`, `resources`,
  `rsc_defaults`, `shutdown_lock`, `singletons`, `stonith_action`,
  `stonith_timeout`, `stop_needed`, `tags`, `template_rsc_sets`, `tickets`, and
  `ticket_constraints`
* **libcrmcommon:** drop direct access to all members of `pcmk_action_t`
* **libcrmcommon:** drop `pcmk_node_t` members `count`, `fixed`,
  `rsc_discover_mode`, and `weight`
* **libcrmcommon:** drop `pcmk_resource_t` members `actions`, `allocated_to`,
  `allowed_nodes`, `children`, `clone_name`, `cluster`, `cmds`, `container`,
  `dangling_migrations`, `exclusive_discover`, `failure_timeout`, `fillers`,
  `fns`, `is_remote_node`, `known_on`, `lock_node`, `lock_time`, `meta`,
  `migration_threshold`, `next_role`, `ops_xml`, `orig_xml`, `parameters`,
  `parameter_cache`, `parent`, `partial_migration_source`,
  `partial_migration_target`, `pending_node`, `pending_task`, `priority`,
  `recovery_type`, `remote_reconnect_ms`, `restart_type`, `role`, `rsc_cons`,
  `rsc_cons_lhs`, `rsc_location`, `rsc_tickets`, `running_on`, `sort_index`,
  `stickiness`, `utilization`, `variant`, `variant_opaque`, and `xml`
* **libcrmcommon:** drop struct `pe_node_shared_s` members `allocated_rsc`,
  `attrs`, `digest_cache`, `expected_up`, `id`, `is_dc`, `num_resources`,
  `priority`, `remote_maintenance`, `remote_requires_reset`, `remote_rsc`,
  `remote_was_fenced`, `rsc_discovery_enabled`, `scheduler`, `standby`,
  `standby_onfail`, `type`, `uname`, `unpacked`, `unseen`, and `utilization`
* **libcrmcommon:** drop defined constants `CRMD_ACTION_CANCEL`,
  `CRMD_ACTION_DELETE`, `CRMD_ACTION_DEMOTE`, `CRMD_ACTION_DEMOTED`,
  `CRMD_ACTION_METADATA`, `CRMD_ACTION_MIGRATE`, `CRMD_ACTION_MIGRATED`,
  `CRMD_ACTION_NOTIFIED`, `CRMD_ACTION_NOTIFY`, `CRMD_ACTION_PROMOTE`,
  `CRMD_ACTION_PROMOTED`, `CRMD_ACTION_RELOAD`, `CRMD_ACTION_RELOAD_AGENT`,
  `CRMD_ACTION_START`, `CRMD_ACTION_STARTED`, `CRMD_ACTION_STATUS`,
  `CRMD_ACTION_STOP`, `CRMD_ACTION_STOPPED`, `CRMD_METADATA`,
  `CRM_ATTR_RA_VERSION`, `CRM_DEFAULT_OP_TIMEOUT_S`, `CRM_INFINITY_S`,
  `CRM_MINUS_INFINITY_S`, `CRM_OP_FENCE`, `CRM_OP_LOCAL_SHUTDOWN`,
  `CRM_OP_LRM_QUERY`, `CRM_OP_LRM_REFRESH`, `CRM_OP_RELAXED_CLONE`,
  `CRM_OP_RELAXED_SET`, `CRM_PLUS_INFINITY_S`, `EOS`, `F_CLIENTNAME`,
  `F_CRM_DATA`, `F_CRM_DC_LEAVING`, `F_CRM_ELECTION_AGE_S`,
  `F_CRM_ELECTION_AGE_US`, `F_CRM_ELECTION_ID`, `F_CRM_ELECTION_OWNER`,
  `F_CRM_HOST_FROM`, `F_CRM_HOST_TO`, `F_CRM_JOIN_ID`, `F_CRM_MSG_TYPE`,
  `F_CRM_ORIGIN`, `F_CRM_REFERENCE`, `F_CRM_SYS_FROM`, `F_CRM_SYS_TO`,
  `F_CRM_TASK`, `F_CRM_TGRAPH`, `F_CRM_TGRAPH_INPUT`, `F_CRM_THROTTLE_MAX`,
  `F_CRM_THROTTLE_MODE`, `F_CRM_USER`, `F_CRM_VERSION`, `F_ORIG`, `F_SEQ`,
  `F_SUBTYPE`, `F_TYPE`, `F_XML_TAGNAME`, `INFINITY`, `INFINITY_S`,
  `MAX_IPC_DELAY`, `MINUS_INFINITY_S`, `OFFLINESTATUS`, `ONLINESTATUS`,
  `PCMK_DEFAULT_METADATA_TIMEOUT_MS`, `PCMK_RESOURCE_CLASS_NAGIOS`,
  `PCMK_RESOURCE_CLASS_UPSTART`, `PCMK_XA_PROMOTED_MAX_LEGACY`,
  `PCMK_XA_PROMOTED_NODE_MAX_LEGACY`, `PCMK_XE_PROMOTABLE_LEGACY`,
  `PCMK_XE_PROMOTED_MAX_LEGACY`, `PCMK_XE_PROMOTED_NODE_MAX_LEGACY`,
  `RSC_CANCEL`, `RSC_DELETE`, `RSC_DEMOTE`, `RSC_DEMOTED`, `RSC_METADATA`,
  `RSC_MIGRATE`, `RSC_MIGRATED`, `RSC_NOTIFIED`, `RSC_NOTIFY`, `RSC_PROMOTE`,
  `RSC_PROMOTED`, `RSC_ROLE_MASTER`, `RSC_ROLE_PROMOTED`,
  `RSC_ROLE_PROMOTED_S`, `RSC_ROLE_SLAVE`, `RSC_ROLE_STARTED`,
  `RSC_ROLE_STOPPED`, `RSC_ROLE_UNKNOWN`, `RSC_ROLE_UNPROMOTED`, `RSC_START`,
  `RSC_STARTED`, `RSC_STATUS`, `RSC_STOP`, `RSC_STOPPED`, `SUPPORT_UPSTART`,
  `T_ATTRD`, `T_CRM`, `XML_ACL_ATTR_ATTRIBUTE`, `XML_ACL_ATTR_KIND`,
  `XML_ACL_ATTR_REF`, `XML_ACL_ATTR_REFv1`, `XML_ACL_ATTR_TAG`,
  `XML_ACL_ATTR_TAGv1`, `XML_ACL_ATTR_XPATH`, `XML_ACL_TAG_DENY`,
  `XML_ACL_TAG_GROUP`, `XML_ACL_TAG_PERMISSION`, `XML_ACL_TAG_READ`,
  `XML_ACL_TAG_ROLE`, `XML_ACL_TAG_ROLE_REF`, `XML_ACL_TAG_ROLE_REFv1`,
  `XML_ACL_TAG_USER`, `XML_ACL_TAG_USERv1`, `XML_ACL_TAG_WRITE`,
  `XML_AGENT_ATTR_CLASS`, `XML_AGENT_ATTR_PROVIDER`, `XML_ALERT_ATTR_PATH`,
  `XML_ALERT_ATTR_REC_VALUE`, `XML_ALERT_ATTR_TIMEOUT`,
  `XML_ALERT_ATTR_TSTAMP_FORMAT`, `XML_ATTR_CRM_VERSION`, `XML_ATTR_DC_UUID`,
  `XML_ATTR_DESC`, `XML_ATTR_DIGEST`, `XML_ATTR_GENERATION`,
  `XML_ATTR_GENERATION_ADMIN`, `XML_ATTR_HAVE_QUORUM`,
  `XML_ATTR_HAVE_WATCHDOG`, `XML_ATTR_ID`, `XML_ATTR_IDREF`,
  `XML_ATTR_ID_LONG`, `XML_ATTR_NAME`, `XML_ATTR_NUMUPDATES`, `XML_ATTR_OP`,
  `XML_ATTR_ORIGIN`, `XML_ATTR_QUORUM_PANIC`, `XML_ATTR_RA_VERSION`,
  `XML_ATTR_REFERENCE`, `XML_ATTR_REQUEST`, `XML_ATTR_RESPONSE`,
  `XML_ATTR_STONITH_DEVICES`, `XML_ATTR_STONITH_INDEX`,
  `XML_ATTR_STONITH_TARGET`, `XML_ATTR_STONITH_TARGET_ATTRIBUTE`,
  `XML_ATTR_STONITH_TARGET_PATTERN`, `XML_ATTR_STONITH_TARGET_VALUE`,
  `XML_ATTR_TE_NOWAIT`, `XML_ATTR_TE_TARGET_RC`, `XML_ATTR_TIMEOUT`,
  `XML_ATTR_TRANSITION_KEY`, `XML_ATTR_TRANSITION_MAGIC`, `XML_ATTR_TSTAMP`,
  `XML_ATTR_TYPE`, `XML_ATTR_UNAME`, `XML_ATTR_UPDATE_CLIENT`,
  `XML_ATTR_UPDATE_ORIG`, `XML_ATTR_UPDATE_USER`, `XML_ATTR_UUID`,
  `XML_ATTR_VALIDATION`, `XML_ATTR_VERBOSE`, `XML_ATTR_VERSION`,
  `XML_BOOLEAN_FALSE`, `XML_BOOLEAN_NO`, `XML_BOOLEAN_TRUE`, `XML_BOOLEAN_YES`,
  `XML_CIB_ATTR_PRIORITY`, `XML_CIB_ATTR_REPLACE`, `XML_CIB_ATTR_SHUTDOWN`,
  `XML_CIB_ATTR_SOURCE`, `XML_CIB_ATTR_WRITTEN`, `XML_CIB_TAG_ACLS`,
  `XML_CIB_TAG_ALERT`, `XML_CIB_TAG_ALERTS`, `XML_CIB_TAG_ALERT_ATTR`,
  `XML_CIB_TAG_ALERT_ATTRIBUTES`, `XML_CIB_TAG_ALERT_FENCING`,
  `XML_CIB_TAG_ALERT_NODES`, `XML_CIB_TAG_ALERT_RECIPIENT`,
  `XML_CIB_TAG_ALERT_RESOURCES`, `XML_CIB_TAG_ALERT_SELECT`,
  `XML_CIB_TAG_CONFIGURATION`, `XML_CIB_TAG_CONSTRAINTS`,
  `XML_CIB_TAG_CONTAINER`, `XML_CIB_TAG_CRMCONFIG`, `XML_CIB_TAG_DOMAINS`,
  `XML_CIB_TAG_GENERATION_TUPPLE`, `XML_CIB_TAG_GROUP`,
  `XML_CIB_TAG_INCARNATION`, `XML_CIB_TAG_LRM`, `XML_CIB_TAG_MASTER`,
  `XML_CIB_TAG_NODE`, `XML_CIB_TAG_NODES`, `XML_CIB_TAG_NVPAIR`,
  `XML_CIB_TAG_OBJ_REF`, `XML_CIB_TAG_OPCONFIG`, `XML_CIB_TAG_PROPSET`,
  `XML_CIB_TAG_RESOURCE`, `XML_CIB_TAG_RESOURCES`, `XML_CIB_TAG_RSCCONFIG`,
  `XML_CIB_TAG_RSC_TEMPLATE`, `XML_CIB_TAG_SECTION_ALL`, `XML_CIB_TAG_STATE`,
  `XML_CIB_TAG_STATUS`, `XML_CIB_TAG_TAG`, `XML_CIB_TAG_TAGS`,
  `XML_CIB_TAG_TICKETS`, `XML_CIB_TAG_TICKET_STATE`, `XML_COLOC_ATTR_INFLUENCE`,
  `XML_COLOC_ATTR_NODE_ATTR`, `XML_COLOC_ATTR_SOURCE`,
  `XML_COLOC_ATTR_SOURCE_INSTANCE`, `XML_COLOC_ATTR_SOURCE_ROLE`,
  `XML_COLOC_ATTR_TARGET`, `XML_COLOC_ATTR_TARGET_INSTANCE`,
  `XML_COLOC_ATTR_TARGET_ROLE`, `XML_CONFIG_ATTR_DC_DEADTIME`,
  `XML_CONFIG_ATTR_ELECTION_FAIL`, `XML_CONFIG_ATTR_FENCE_REACTION`,
  `XML_CONFIG_ATTR_FORCE_QUIT`, `XML_CONFIG_ATTR_NODE_PENDING_TIMEOUT`,
  `XML_CONFIG_ATTR_PRIORITY_FENCING_DELAY`, `XML_CONFIG_ATTR_RECHECK`,
  `XML_CONFIG_ATTR_SHUTDOWN_LOCK`, `XML_CONFIG_ATTR_SHUTDOWN_LOCK_LIMIT`,
  `XML_CONS_ATTR_SYMMETRICAL`, `XML_CONS_TAG_RSC_DEPEND`,
  `XML_CONS_TAG_RSC_LOCATION`, `XML_CONS_TAG_RSC_ORDER`, `XML_CONS_TAG_RSC_SET`,
  `XML_CONS_TAG_RSC_TICKET`, `XML_CRM_TAG_PING`, `XML_DIFF_ATTR`,
  `XML_DIFF_CHANGE`, `XML_DIFF_LIST`, `XML_DIFF_MARKER`, `XML_DIFF_OP`,
  `XML_DIFF_PATH`, `XML_DIFF_POSITION`, `XML_DIFF_RESULT`, `XML_DIFF_VERSION`,
  `XML_DIFF_VSOURCE`, `XML_DIFF_VTARGET`, `XML_EXPR_ATTR_ATTRIBUTE`,
  `XML_EXPR_ATTR_OPERATION`, `XML_EXPR_ATTR_TYPE`, `XML_EXPR_ATTR_VALUE`,
  `XML_EXPR_ATTR_VALUE_SOURCE`, `XML_FAILCIB_ATTR_ID`,
  `XML_FAILCIB_ATTR_OBJTYPE`, `XML_FAILCIB_ATTR_OP`, `XML_FAILCIB_ATTR_REASON`,
  `XML_FAIL_TAG_CIB`, `XML_GRAPH_TAG_CRM_EVENT`, `XML_GRAPH_TAG_DOWNED`,
  `XML_GRAPH_TAG_MAINTENANCE`, `XML_GRAPH_TAG_PSEUDO_EVENT`,
  `XML_GRAPH_TAG_RSC_OP`, `XML_LOCATION_ATTR_DISCOVERY`, `XML_LOC_ATTR_SOURCE`,
  `XML_LOC_ATTR_SOURCE_PATTERN`, `XML_LRM_ATTR_CALLID`,
  `XML_LRM_ATTR_EXIT_REASON`, `XML_LRM_ATTR_INTERVAL`,
  `XML_LRM_ATTR_INTERVAL_MS`, `XML_LRM_ATTR_MIGRATE_SOURCE`,
  `XML_LRM_ATTR_MIGRATE_TARGET`, `XML_LRM_ATTR_OPSTATUS`,
  `XML_LRM_ATTR_OP_DIGEST`, `XML_LRM_ATTR_OP_RESTART`, `XML_LRM_ATTR_OP_SECURE`,
  `XML_LRM_ATTR_RC`, `XML_LRM_ATTR_RESTART_DIGEST`, `XML_LRM_ATTR_ROUTER_NODE`,
  `XML_LRM_ATTR_RSCID`, `XML_LRM_ATTR_SECURE_DIGEST`, `XML_LRM_ATTR_TARGET`,
  `XML_LRM_ATTR_TARGET_UUID`, `XML_LRM_ATTR_TASK`, `XML_LRM_ATTR_TASK_KEY`,
  `XML_LRM_TAG_RESOURCE`, `XML_LRM_TAG_RESOURCES`, `XML_LRM_TAG_RSC_OP`,
  `XML_NODE_ATTR_RSC_DISCOVERY`, `XML_NODE_EXPECTED`, `XML_NODE_IN_CLUSTER`,
  `XML_NODE_IS_FENCED`, `XML_NODE_IS_MAINTENANCE`, `XML_NODE_IS_PEER`,
  `XML_NODE_IS_REMOTE`, `XML_NODE_JOIN_STATE`, `XML_NVPAIR_ATTR_NAME`,
  `XML_NVPAIR_ATTR_VALUE`, `XML_OP_ATTR_ALLOW_MIGRATE`,
  `XML_OP_ATTR_DIGESTS_ALL`, `XML_OP_ATTR_DIGESTS_SECURE`,
  `XML_OP_ATTR_ON_FAIL`, `XML_OP_ATTR_ORIGIN`, `XML_OP_ATTR_PENDING`,
  `XML_OP_ATTR_START_DELAY`, `XML_ORDER_ATTR_FIRST`,
  `XML_ORDER_ATTR_FIRST_ACTION`, `XML_ORDER_ATTR_FIRST_INSTANCE`,
  `XML_ORDER_ATTR_KIND`, `XML_ORDER_ATTR_THEN`, `XML_ORDER_ATTR_THEN_ACTION`,
  `XML_ORDER_ATTR_THEN_INSTANCE`, `XML_PARANOIA_CHECKS`,
  `XML_PING_ATTR_CRMDSTATE`, `XML_PING_ATTR_PACEMAKERDSTATE`,
  `XML_PING_ATTR_PACEMAKERDSTATE_INIT`,
  `XML_PING_ATTR_PACEMAKERDSTATE_REMOTE`,
  `XML_PING_ATTR_PACEMAKERDSTATE_RUNNING`,
  `XML_PING_ATTR_PACEMAKERDSTATE_SHUTDOWNCOMPLETE`
  `XML_PING_ATTR_PACEMAKERDSTATE_SHUTTINGDOWN`
  `XML_PING_ATTR_PACEMAKERDSTATE_STARTINGDAEMONS`
  `XML_PING_ATTR_PACEMAKERDSTATE_WAITPING`, `XML_PING_ATTR_STATUS`,
  `XML_PING_ATTR_SYSFROM`, `XML_REMOTE_ATTR_RECONNECT_INTERVAL`,
  `XML_RSC_ATTR_CLEAR_INTERVAL`, `XML_RSC_ATTR_CLEAR_OP`,
  `XML_RSC_ATTR_CONTAINER`, `XML_RSC_ATTR_CRITICAL`,
  `XML_RSC_ATTR_FAIL_STICKINESS`, `XML_RSC_ATTR_FAIL_TIMEOUT`,
  `XML_RSC_ATTR_INCARNATION`, `XML_RSC_ATTR_INCARNATION_MAX`,
  `XML_RSC_ATTR_INCARNATION_MIN`, `XML_RSC_ATTR_INCARNATION_NODEMAX`,
  `XML_RSC_ATTR_INTERLEAVE`, `XML_RSC_ATTR_INTERNAL_RSC`,
  `XML_RSC_ATTR_MAINTENANCE`, `XML_RSC_ATTR_MANAGED`, `XML_RSC_ATTR_MASTER_MAX`,
  `XML_RSC_ATTR_MASTER_NODEMAX`, `XML_RSC_ATTR_MULTIPLE`, `XML_RSC_ATTR_NOTIFY`,
  `XML_RSC_ATTR_ORDERED`, `XML_RSC_ATTR_PROMOTABLE`,
  `XML_RSC_ATTR_PROMOTED_MAX`, `XML_RSC_ATTR_PROMOTED_NODEMAX`,
  `XML_RSC_ATTR_PROVIDES`, `XML_RSC_ATTR_REMOTE_NODE`,
  `XML_RSC_ATTR_REMOTE_RA_ADDR`, `XML_RSC_ATTR_REMOTE_RA_PORT`,
  `XML_RSC_ATTR_REMOTE_RA_SERVER`, `XML_RSC_ATTR_REQUIRES`,
  `XML_RSC_ATTR_RESTART`, `XML_RSC_ATTR_STICKINESS`, `XML_RSC_ATTR_TARGET`,
  `XML_RSC_ATTR_TARGET_ROLE`, `XML_RSC_ATTR_UNIQUE`, `XML_RSC_OP_LAST_CHANGE`,
  `XML_RSC_OP_LAST_RUN`, `XML_RSC_OP_T_EXEC`, `XML_RSC_OP_T_QUEUE`,
  `XML_RULE_ATTR_BOOLEAN_OP`, `XML_RULE_ATTR_ROLE`, `XML_RULE_ATTR_SCORE`,
  `XML_RULE_ATTR_SCORE_ATTRIBUTE`, `XML_TAG_ATTRS`, `XML_TAG_ATTR_SETS`,
  `XML_TAG_DIFF`, `XML_TAG_DIFF_ADDED`, `XML_TAG_DIFF_REMOVED`,
  `XML_TAG_EXPRESSION`, `XML_TAG_FAILED`, `XML_TAG_FENCING_LEVEL`,
  `XML_TAG_FENCING_TOPOLOGY`, `XML_TAG_FRAGMENT`, `XML_TAG_GRAPH`,
  `XML_TAG_META_SETS`, `XML_TAG_OPTIONS`, `XML_TAG_OP_VER_ATTRS`,
  `XML_TAG_OP_VER_META`, `XML_TAG_PARAM`, `XML_TAG_PARAMS`,
  `XML_TAG_RESOURCE_REF`, `XML_TAG_RSC_VER_ATTRS`, `XML_TAG_RULE`,
  `XML_TAG_TRANSIENT_NODEATTRS`, `XML_TAG_UTILIZATION`,
  `XML_TICKET_ATTR_LOSS_POLICY`, and `XML_TICKET_ATTR_TICKET`
* **libcrmcommon:** drop support for patchset format 1 in
  `xml_apply_patchset()`, `xml_create_patchset()`, and `xml_patch_versions()`
* **libcrmcommon:** drop functions/macros `add_message_xml()`,
  `add_node_copy()`, `add_node_nocopy()`, `apply_xml_diff()`, `bz2_strerror()`,
  `can_prune_leaf()`, `copy_in_properties()` `create_hello_message()`,
  `create_reply()`, `create_reply_adv()`, `create_request()`,
  `create_request_adv()`, `create_xml_node()`, `crm_action_str()`,
  `crm_add_logfile()`, `crm_atoi()`, `crm_build_path()`, `crm_destroy_xml()`,
  `crm_errno2exit()`, `crm_ftoa()`, `crm_get_interval()`,
  `crm_hash_table_size()`, `crm_itoa()`, `crm_itoa_stack()`,
  `crm_log_cli_init()`, `crm_map_element_name()`, `crm_next_same_xml()`,
  `crm_parse_int()`, `crm_parse_interval_spec()`, `crm_parse_ll()`,
  `crm_provider_required()`, `crm_signal()`, `crm_str()`,
  `crm_strcase_equal()`, `crm_strcase_hash()`, `crm_strcase_table_new()`,
  `crm_strip_trailing_newline()`, `crm_str_eq()`, `crm_str_hash()`,
  `crm_str_table_dup()`, `crm_str_table_new()`, `crm_ttoa()`,
  `crm_xml_add_boolean()`, `crm_xml_escape()`, `crm_xml_replace()`,
  `diff_xml_object()`, `do_crm_log_always()`, `dump_xml_formatted()`,
  `dump_xml_formatted_with_text()`, `dump_xml_unformatted()`,
  `expand_plus_plus()`, `filename2xml()`, `find_entity()`,
  `find_xml_children()`, `find_xml_node()`, `first_named_child()`,
  `fix_plus_plus_recursive()`, `getDocPtr()`, `get_message_xml()`,
  `get_schema_name()`, `get_schema_version()`, `get_xpath_object_relative()`,
  `g_str_hash_traditional()`, `ID()`, `is_not_set()`, `is_set_any()`,
  `log_data_element()`, `pcmk_action_text()`, `pcmk_create_html_node()`,
  `pcmk_create_xml_text_node()`, `pcmk_format_named_time()`,
  `pcmk_format_nvpair()`, `pcmk_hostname()`, `pcmk_log_xml_impl()`,
  `pcmk_numeric_strcasecmp()`, `pcmk_on_fail_text()`, `pcmk_parse_action()`,
  `pcmk_scan_nvpair()`, `purge_diff_markers()`, `replace_xml_child()`,
  `safe_str_eq()`, `safe_str_neq()`, `score2char()`, `score2char_stack()`,
  `stdin2xml()`, `string2xml()` `subtract_xml_object()`, `TYPE()`,
  `update_validation()`, `update_xml_child()`, `validate_xml()`,
  `validate_xml_verbose()`, `write_xml_fd()`, `write_xml_file()`,
  `xml_get_path()`, `xml_has_children()`, `xml_latest_schema()`,
  `xml_log_changes()`, `xml_log_patchset()`, `xml_remove_prop()`, `__likely()`,
  and `__unlikely()`
* **libcrmservice:** drop header `services_compat.h`
* **libcrmservice:** deprecate function `services_ocf_exitcode_str()`
* **libcrmservice:** drop enums (including all their values) `nagios_exitcode`
  and `op_status`
* **libcrmservice:** drop defined constants `F_LRMD_ALERT`, `F_LRMD_ALERT_ID`,
  `F_LRMD_ALERT_PATH`, `F_LRMD_CALLBACK_TOKEN`, `F_LRMD_CALLDATA`,
  `F_LRMD_CALLID`, `F_LRMD_CALLOPTS`, `F_LRMD_CLASS`, `F_LRMD_CLIENTID`,
  `F_LRMD_CLIENTNAME`, `F_LRMD_EXEC_RC`, `F_LRMD_IPC_CLIENT`,
  `F_LRMD_IPC_IPC_SERVER`, `F_LRMD_IPC_MSG`, `F_LRMD_IPC_MSG_FLAGS`,
  `F_LRMD_IPC_MSG_ID`, `F_LRMD_IPC_OP`, `F_LRMD_IPC_SESSION`, `F_LRMD_IPC_USER`,
  `F_LRMD_IS_IPC_PROVIDER`, `F_LRMD_OPERATION`, `F_LRMD_OP_STATUS`,
  `F_LRMD_ORIGIN`, `F_LRMD_PROTOCOL_VERSION`, `F_LRMD_PROVIDER`, `F_LRMD_RC`,
  `F_LRMD_REMOTE_MSG_ID`, `F_LRMD_REMOTE_MSG_TYPE`, `F_LRMD_RSC`,
  `F_LRMD_RSC_ACTION`, `F_LRMD_RSC_DELETED`, `F_LRMD_RSC_EXEC_TIME`,
  `F_LRMD_RSC_EXIT_REASON`, `F_LRMD_RSC_ID`, `F_LRMD_RSC_INTERVAL`,
  `F_LRMD_RSC_OUTPUT`, `F_LRMD_RSC_QUEUE_TIME`, `F_LRMD_RSC_RCCHANGE_TIME`,
  `F_LRMD_RSC_RUN_TIME`, `F_LRMD_RSC_START_DELAY`, `F_LRMD_RSC_USERDATA_STR`,
  `F_LRMD_TIMEOUT`, `F_LRMD_TYPE`, `F_LRMD_WATCHDOG`, `T_LRMD`,
  `T_LRMD_IPC_PROXY`, `T_LRMD_NOTIFY`, `T_LRMD_REPLY`, and `T_LRMD_RSC_OP`
* **libcrmservice:** drop functions `services_action_create()`,
  `services_get_ocf_exitcode()`, `services_list()`, and
  `services_lrm_status_str()`
* **liblrmd:** drop header `lrmd_compat.h`
* **liblrmd:** redefine `lrmd_opt_drop_recurring` enum value
* **liblrmd:** change type of `lrmd_event_data_t` members `t_rcchange` and
  `t_run` to `time_t`
* **liblrmd:** drop defined constants `ALT_REMOTE_KEY_LOCATION` and
  `LRMD_MIN_PROTOCOL_VERSION`
* **libpacemaker:** add high-level API equivalents of `stonith_admin` options
  including `pcmk_request_fencing()`, `pcmk_fence_history()`,
  `pcmk_fence_installed()`, `pcmk_fence_last()`, `pcmk_fence_list_targets()`,
  `pcmk_fence_metadata()`, `pcmk_fence_registered()`,
  `pcmk_fence_register_level()`, `pcmk_fence_unregister_level()`, and
  `pcmk_fence_validate()`
* **libpe_rules:** drop functions `find_expression_type()`,
  `pe_evaluate_rules()`, `pe_eval_expr()`, `pe_eval_rules()`,
  `pe_eval_subexpr()`, `pe_expand_re_matches()`, `pe_test_expression()`,
  `pe_test_expression_full()`, `pe_test_expression_re()`, `pe_test_rule()`,
  `pe_test_rule_full()`, `pe_test_rule_re()`, `test_expression()`,
  `test_ruleset()`, and `unpack_instance_attributes()`
* **libpe_status,libpe_rules:** drop types `action_t`, `action_wrapper_t`,
  `no_quorum_policy_t`, `pe_action_t`, `pe_action_wrapper_t`, `pe_node_t`,
  `pe_resource_t`, `pe_tag_t`, `pe_ticket_t`, `tag_t`, and `ticket_t`
* **libpe_status,libpe_rules:** drop enums (including all their values)
  `pe_check_parameters` and `pe_graph_flags`
* **libpe_status,libpe_rules:** drop defined constants `pe_flag_check_config`,
  `pe_flag_concurrent_fencing`, `pe_flag_enable_unfencing`,
  `pe_flag_have_remote_nodes`, `pe_flag_have_status`,
  `pe_flag_maintenance_mode`, `pe_flag_no_compat`, `pe_flag_no_counts`,
  `pe_flag_quick_location`, `pe_flag_remove_after_stop`, `pe_flag_sanitized`,
  `pe_flag_show_scores`, `pe_flag_show_utilization`, `pe_flag_shutdown_lock`,
  `pe_flag_startup_fencing`, `pe_flag_startup_probes`,
  `pe_flag_start_failure_fatal`, `pe_flag_stdout`, `pe_flag_stonith_enabled`,
  `pe_flag_stop_action_orphans`, `pe_flag_stop_everything`,
  `pe_flag_stop_rsc_orphans`, `pe_flag_symmetric_cluster`, `pe_rsc_allocating`,
  `pe_rsc_allow_migrate`, `pe_rsc_allow_remote_remotes`, `pe_rsc_block`,
  `pe_rsc_critical`, `pe_rsc_detect_loop`, `pe_rsc_failed`,
  `pe_rsc_failure_ignored`, `pe_rsc_fence_device`, `pe_rsc_is_container`,
  `pe_rsc_maintenance`, `pe_rsc_merging`, `pe_rsc_needs_fencing`,
  `pe_rsc_needs_quorum`, `pe_rsc_needs_unfencing`, `pe_rsc_notify`,
  `pe_rsc_orphan`, `pe_rsc_orphan_container_filler`, `pe_rsc_promotable`,
  `pe_rsc_provisional`, `pe_rsc_reload`, `pe_rsc_replica_container`,
  `pe_rsc_restarting`, `pe_rsc_runnable`, `pe_rsc_starting`,
  `pe_rsc_start_pending`, `pe_rsc_stop`, `pe_rsc_stopping`,
  `pe_rsc_stop_unexpected`, `pe_rsc_unique`, `RSC_ROLE_MASTER_S`,
  `RSC_ROLE_MAX`, `RSC_ROLE_PROMOTED_LEGACY_S`, `RSC_ROLE_SLAVE_S`,
  `RSC_ROLE_STARTED_S`, `RSC_ROLE_STOPPED_S`, `RSC_ROLE_UNKNOWN_S`,
  `RSC_ROLE_UNPROMOTED_LEGACY_S`, and `RSC_ROLE_UNPROMOTED_S`
* **libpe_status,libpe_rules:** drop functions `fail2text(),` `pe_pref()`,
  `recovery2text()`, `role2text()`, `task2text()`, `text2role()`, and
  `text2task()`
* **libpe_status:** drop functions/macros `pe_rsc_is_anon_clone()`,
  `pe_rsc_is_bundled()`, `pe_rsc_is_clone()`, `pe_rsc_is_unique_clone()`, and
  `status_print()`
* **libstonithd:** drop `stonith_t` member `call_timeout`
* **libstonithd:** drop `stonith_event_t` members `message` and `type`
* **libstonithd:** drop defined constants `T_STONITH_NOTIFY_DISCONNECT`,
  `T_STONITH_NOTIFY_FENCE`, `T_STONITH_NOTIFY_HISTORY`, and
  `T_STONITH_NOTIFY_HISTORY_SYNCED`
* **libstonithd:** drop function `get_stonith_provider()`

# Pacemaker-2.1.9 (31 Oct 2024)
- 169 commits with 252 files changed, 4498 insertions(+), 2259 deletions(-)

## Features added since Pacemaker-2.1.8

  + **build:** support building with libxml2 2.13.0 or newer
  + **CIB:** new no-quorum-policy value "fence" replaces now-deprecated "suicide"
  + **tools:** iso8601 supports standard `--output-as/--output-to` arguments

## Fixes since Pacemaker-2.1.8

  + **tools:** restore crmadmin default timeout to 30 seconds instead of none
           *(regression introduced in 2.1.5)*
  + **tools:** `crm_resource` did not return error if schema upgrade failed
    *(regression introduced in 2.1.8)*
  + **CIB:** detect newly created alerts section *(regression introduced in 2.1.7)*
  + **CIB:** treat empty environment variables (`CIB_file` etc.) same as unset
  + **CIB:** remote CIB administration now cannot block server
  + **executor:** don't block during TLS handshakes
  + **executor:** discard any agent output after about 10MiB
  + **scheduler:** avoid memory leak when checking for unfencing-capable devices
  + **libcrmcommon:** check for overflow when parsing and manipulating date/times
  + **tools:** properly handle resources removed from configuration when
    displaying node history in `crm_mon`
  + **tools:** crmadmin -D/--dc_lookup no longer hangs when there is no DC
  + **tools:** don't assert if stdout or stderr is closed by caller

## Public API changes since Pacemaker-2.1.8

  + **libcrmcommon:** add enum `pcmk_ra_caps` value `pcmk_ra_cap_cli_exec`
  + **libcrmcommon:** add `pcmk_cib_node_shutdown()`
  + **libcrmcommon:** add `pcmk_parse_score()`
  + **libcrmcommon:** deprecate `CRM_ASSERT()`
  + **libcrmcommon:** deprecate `PCMK_VALUE_FENCE_LEGACY` defined constant
  + **libstonithd:** add enum `stonith_call_options` value `st_opt_allow_self_fencing`
  + **libstonithd:** deprecate enum `stonith_call_options` value `st_opt_allow_suicide`
  + **libstonithd:** deprecate enum `stonith_call_options` value `st_opt_scope_local`
  + **libstonithd:** deprecate enum `stonith_call_options` value `st_opt_verbose`

# Pacemaker-2.1.8 (08 Aug 2024)
- 2559 commits with 511 files changed, 46898 insertions(+), 23417 deletions(-)

## Features added since Pacemaker-2.1.7

  + **local options:** support `PCMK_panic_action="off"` or "sync-off"
  + **local options:** deprecate `PCMK_dh_min_bits` environment variable
  + **CIB:** deprecate omitting validate-with from the CIB or setting it to "none"
    or an unknown schema
  + **CIB:** deprecate "default" and "#default" as explicit meta-attribute values
  + **CIB:** deprecate resource-discovery-enabled node attribute
  + **CIB:** deprecate support for multiple top-level rules within a location
    constraint (a single rule may still contain multiple sub-rules)
  + **CIB:** deprecate support for node attribute expressions in rules beneath op,
    `op_defaults`, or fence device meta-attributes
  + **CIB:** deprecate support for rkt in bundles
  + **CIB:** drop support for (nonworking) rules based on the #role node attribute
    (role-based location constraints may still contain rules)
  + **CIB manager,controller,fencer,scheduler:** deprecate "metadata" command-line
    option (instead, use `crm_attribute` `--list-options` mentioned below)
  + **pacemaker-remoted:** newer schema files are now downloaded from the cluster,
    allowing more command-line tools to work when the Pacemaker Remote node
    has an older Pacemaker version than the cluster
  + **agents:** deprecate the ocf:pacemaker:o2cb resource agent
  + **tools:** deprecate `--text-fancy` command-line option in all tools
  + **tools:** `crm_attribute` `--list-options` lists all possible cluster options
  + **tools:** `crm_resource` `--list-options` lists all possible primitive
    meta-attributes or special fence device parameters
  + **tools:** `crm_verify` now reports invalid fence topology levels
  + **tools:** new `--score` option for cibadmin `--modify` and `crm_attribute` --update
    enables expansion of "++" and "+=" in attribute values without a warning
    (using such expansions without `--score` is now deprecated)
  + **tools:** `crm_ticket` supports standard `--output-as/--output-to` arguments

## Fixes since Pacemaker-2.1.7

  + **tools:** restore the (deprecated) ability to automatically correct malformed
    XML passed via standard input *(regression introduced in 2.1.7)*
  + **tools:** `crm_verify` distinguishes configuration warnings and errors
    *(regression introduced in 2.1.7)*
  + **tools:** `crm_node` -i must initialize nodeid before passing pointer
    *(regression introduced in 2.1.7)*
  + **CIB manager:** avoid memory leak from asynchronous client requests
    *(regression introduced in 2.1.7)*
  + **scheduler:** don't apply colocations twice for promotion priority
    *(regression introduced in 2.1.7)*
  + **CIB:** restore the (deprecated) ability to use validate-with="pacemaker-next"
    *(regression introduced in 2.1.6)*
  + **controller:** avoid zombie children when asynchronous actions exit while a
    synchronous meta-data action is in progress
    *(regression introduced in 2.1.5)*
  + **libcrmcommon:** avoid file descriptor leak in asynchronous IPC clients
    *(regression introduced in 2.1.3)*
  + **scheduler:** avoid crash when logging an invalid utilization attribute value
    *(regression introduced in 2.1.3)*
  + **tools:** `crm_mon` no longer crashes on some platforms when the fencer
    connection is lost *(regression introduced in 2.1.0)*
  + **attribute manager:** write Pacemaker Remote node attributes even if node is
    not cached
  + **attribute manager:** avoid use-after-free when remote node in cluster node
    cache
  + **attribute manager:** correctly propagate utilization attributes to peers
    to avoid the possibility of later being written out as regular node
    attributes
  + **fencer:** correctly parse action-specific timeouts with units other than
    seconds
  + **fencer:** avoid unnecessary timeouts when the watchdog timeout is greater
    than a query timeout, per-device fencing timeout, or stonith-timeout
  + **libcrmcommon:** avoid possible buffer overflows when parsing and formatting
    date/times
  + **libcrmcommon:** don't assume next schema will validate when not transforming
  + **libcrmcommon:** when displaying XML, don't show "<null>" for empty attribute
    values, and properly escape special characters
  + **libstonithd:** avoid double free when invalid replies are received
  + **scheduler:** if the user specifies a timeout of 0, use the default 20s as
    documented
  + **scheduler:** consider group's location constraints when a member is an
    explicit dependent in a colocation constraint
  + **scheduler:** sort promotable cloned group instances properly for promotion
  + **agents:** ocf:pacemaker:SysInfo respects `attrd_updater` dampening
  + **agents:** ocf:pacemaker:HealthSMART properly handles SMART data missing
    temperature
  + **tools:** cibadmin, `crm_attribute`, `crm_node`, `crm_resource`, `crm_shadow`, and
    `crm_ticket` now retry CIB connections after transient failures
  + **tools:** cibadmin `--replace` now leaves "++" and "+=" unexpanded in XML
    attribute values rather than wrongly treat them as 0
  + **tools:** cibsecret avoids possible truncation issue in process listing
  + **tools:** `crm_attribute` `--node` localhost or `--node` auto works
  + **tools:** `crm_resource` ignores resource meta-attribute node expressions
    for consistency with how the cluster works
  + **tools:** `crm_resource` honors rules when getting utilization attributes
  + **tools:** `crm_verify` `--output-as=xml` includes detailed messages
  + **tools:** `crm_mon` exits upon loss of an attached pseudo-terminal to avoid
    possibility of 100% CPU usage (seen when run via sudo with `use_pty`
    configured)

## Public API changes since Pacemaker-2.1.7

  + **libcib:** add `cib_score_update` `cib_call_options` value
  + **libcib:** deprecate functions `cib_get_generation()`, `cib_metadata()`,
    `cib_pref()`, `query_node_uname()`, and `set_standby()`
  + **libcib:** deprecate `T_CIB_DIFF_NOTIFY`
  + **libcib:** deprecate `<failed>` element in CIB create reply
  + **libcrmcluster:** add enum `pcmk_cluster_layer`
  + **libcrmcluster:** add functions `pcmk_cluster_connect()`,
    `pcmk_cluster_disconnect()`, `pcmk_cluster_layer_text()`,
    `pcmk_cluster_set_destroy_fn()`, `pcmk_cpg_set_confchg_fn()`,
    `pcmk_cpg_set_deliver_fn()`, and `pcmk_get_cluster_layer()`
  + **libcrmcluster:** add type `pcmk_cluster_t`
  + **libcrmcluster:** deprecate functions `cluster_connect_cpg()`,
    `cluster_disconnect_cpg()`, `crm_active_peers()`, `crm_cluster_connect()`,
    `crm_cluster_disconnect()`, `crm_get_peer()`, `crm_get_peer_full()`,
    `crm_is_corosync_peer_active()`, `crm_is_peer_active()`, `crm_join_phase_str()`,
    `crm_peer_destroy()`, `crm_peer_init()`, `crm_peer_uname()`,
    `crm_peer_uuid()`, `crm_remote_node_cache_size()`,
    `crm_remote_peer_cache_refresh()`, `crm_remote_peer_cache_remove()`,
    `crm_remote_peer_get()`, `crm_set_autoreap()`, `crm_set_status_callback()`,
    `get_cluster_type()`, `get_local_nodeid()`, `get_local_node_name()`,
    `get_node_name()`, `is_corosync_cluster()`, `name_for_cluster_type()`,
    `pcmk_cpg_membership()`, `pcmk_message_common_cs()`, `reap_crm_member()`,
    `send_cluster_message()`, `send_cluster_text()`, and `text2msg_type()`
  + **libcrmcluster:** deprecate enums `crm_ais_msg_types`, `crm_status_type`,
    `cluster_type_e`, `crm_ais_msg_class`, `crm_get_peer_flags`, `crm_join_phase`,
    and `crm_node_flags`, including all their values
  + **libcrmcluster:** deprecate global variables `crm_have_quorum`, `crm_peer_cache`,
    `crm_peer_seq`, and `crm_remote_peer_cache`
  + **libcrmcluster:** deprecate `crm_cluster_t` and struct `crm_cluster_s`, including
    all its members
  + **libcrmcluster:** deprecate `crm_node_t` and struct `crm_peer_node_s`, including
    all its members
  + **libcrmcluster:** deprecate constants `CRM_NODE_LOST` and `CRM_NODE_MEMBER`
  + **libcrmcommon:** add constants `PCMK_ACTION_METADATA`, `PCMK_META_ALLOW_MIGRATE`,
    `PCMK_META_ALLOW_UNHEALTHY_NODES`, `PCMK_META_CONTAINER_ATTRIBUTE_TARGET`,
    `PCMK_META_CRITICAL`, `PCMK_META_GLOBALLY_UNIQUE`, `PCMK_META_INTERLEAVE`,
    `PCMK_META_INTERVAL`, `PCMK_META_INTERVAL_ORIGIN`, `PCMK_META_IS_MANAGED`,
    `PCMK_META_MAINTENANCE`, `PCMK_META_MULTIPLE_ACTIVE`, `PCMK_META_NOTIFY`,
    `PCMK_META_ON_FAIL`, `PCMK_META_ORDERED`, `PCMK_META_PRIORITY`,
    `PCMK_META_PROMOTABLE`, `PCMK_META_RECORD_PENDING`, `PCMK_META_REMOTE_ADDR`,
    `PCMK_META_REMOTE_ALLOW_MIGRATE`, `PCMK_META_REMOTE_CONNECT_TIMEOUT`,
    `PCMK_META_REMOTE_NODE`, `PCMK_META_REMOTE_PORT`, `PCMK_META_REQUIRES`,
    `PCMK_META_RESOURCE_STICKINESS`, `PCMK_META_START_DELAY`,
    `PCMK_META_TARGET_ROLE`, `PCMK_META_TIMEOUT`, `PCMK_META_TIMESTAMP_FORMAT`,
    `PCMK_NODE_ATTR_MAINTENANCE`, `PCMK_NODE_ATTR_STANDBY`, `PCMK_OPT_BATCH_LIMIT`,
    `PCMK_OPT_CLUSTER_DELAY`, `PCMK_OPT_CLUSTER_INFRASTRUCTURE`,
    `PCMK_OPT_CLUSTER_IPC_LIMIT`, `PCMK_OPT_CLUSTER_NAME`,
    `PCMK_OPT_CLUSTER_RECHECK_INTERVAL`, `PCMK_OPT_CONCURRENT_FENCING`,
    `PCMK_OPT_DC_DEADTIME`, `PCMK_OPT_DC_VERSION`, `PCMK_OPT_ELECTION_TIMEOUT`,
    `PCMK_OPT_ENABLE_ACL`, `PCMK_OPT_ENABLE_STARTUP_PROBES`,
    `PCMK_OPT_FENCE_REACTION`, `PCMK_OPT_HAVE_WATCHDOG`,
    `PCMK_OPT_JOIN_FINALIZATION_TIMEOUT`, `PCMK_OPT_JOIN_INTEGRATION_TIMEOUT`,
    `PCMK_OPT_LOAD_THRESHOLD`, `PCMK_OPT_MAINTENANCE_MODE`,
    `PCMK_OPT_MIGRATION_LIMIT`, `PCMK_OPT_NODE_ACTION_LIMIT`,
    `PCMK_OPT_NODE_HEALTH_BASE`, `PCMK_OPT_NODE_HEALTH_GREEN`,
    `PCMK_OPT_NODE_HEALTH_RED`, `PCMK_OPT_NODE_HEALTH_STRATEGY`,
    `PCMK_OPT_NODE_HEALTH_YELLOW`, `PCMK_OPT_NODE_PENDING_TIMEOUT`,
    `PCMK_OPT_NO_QUORUM_POLICY`, `PCMK_OPT_PE_ERROR_SERIES_MAX`,
    `PCMK_OPT_PE_INPUT_SERIES_MAX`, `PCMK_OPT_PE_WARN_SERIES_MAX`,
    `PCMK_OPT_PLACEMENT_STRATEGY`, `PCMK_OPT_PRIORITY_FENCING_DELAY`,
    `PCMK_OPT_SHUTDOWN_ESCALATION`, `PCMK_OPT_SHUTDOWN_LOCK`,
    `PCMK_OPT_SHUTDOWN_LOCK_LIMIT`, `PCMK_OPT_STARTUP_FENCING`,
    `PCMK_OPT_START_FAILURE_IS_FATAL`, `PCMK_OPT_STONITH_ACTION`,
    `PCMK_OPT_STONITH_ENABLED`, `PCMK_OPT_STONITH_MAX_ATTEMPTS`,
    `PCMK_OPT_STONITH_TIMEOUT`, `PCMK_OPT_STONITH_WATCHDOG_TIMEOUT`,
    `PCMK_OPT_STOP_ALL_RESOURCES`, `PCMK_OPT_STOP_ORPHAN_ACTIONS`,
    `PCMK_OPT_STOP_ORPHAN_RESOURCES`, `PCMK_OPT_SYMMETRIC_CLUSTER`,
    `PCMK_OPT_TRANSITION_DELAY`, `PCMK_REMOTE_RA_ADDR`, `PCMK_REMOTE_RA_PORT`,
    `PCMK_REMOTE_RA_RECONNECT_INTERVAL`, `PCMK_REMOTE_RA_SERVER`,
    `PCMK_ROLE_PROMOTED`, `PCMK_ROLE_STARTED`, `PCMK_ROLE_STOPPED`,
    `PCMK_ROLE_UNPROMOTED`, `PCMK_SCORE_INFINITY`, `PCMK_VALUE_ALWAYS`,
    `PCMK_VALUE_AND`, `PCMK_VALUE_BALANCED`, `PCMK_VALUE_BLOCK`, `PCMK_VALUE_BOOLEAN`,
    `PCMK_VALUE_CIB_BOOTSTRAP_OPTIONS`, `PCMK_VALUE_COROSYNC`, `PCMK_VALUE_CREATE`,
    `PCMK_VALUE_CUSTOM`, `PCMK_VALUE_DATE_SPEC`, `PCMK_VALUE_DEFAULT`,
    `PCMK_VALUE_DEFINED`, `PCMK_VALUE_DELETE`, `PCMK_VALUE_DEMOTE`, `PCMK_VALUE_DENY`,
    `PCMK_VALUE_DURATION`, `PCMK_VALUE_DYNAMIC_LIST`, `PCMK_VALUE_EQ`,
    `PCMK_VALUE_EXCLUSIVE`, `PCMK_VALUE_FAILED`, `PCMK_VALUE_FALSE`,
    `PCMK_VALUE_FENCE`, `PCMK_VALUE_FENCE_LEGACY`, `PCMK_VALUE_FENCING`,
    `PCMK_VALUE_FREEZE`, `PCMK_VALUE_GRANTED`, `PCMK_VALUE_GREEN`, `PCMK_VALUE_GT`,
    `PCMK_VALUE_GTE`, `PCMK_VALUE_HOST`, `PCMK_VALUE_IGNORE`, `PCMK_VALUE_IN_RANGE`,
    `PCMK_VALUE_INFINITY`, `PCMK_VALUE_INTEGER`, `PCMK_VALUE_LITERAL`,
    `PCMK_VALUE_LT`, `PCMK_VALUE_LTE`, `PCMK_VALUE_MANDATORY`, `PCMK_VALUE_MEMBER`,
    `PCMK_VALUE_META`, `PCMK_VALUE_MIGRATE_ON_RED`, `PCMK_VALUE_MINIMAL`,
    `PCMK_VALUE_MINUS_INFINITY`, `PCMK_VALUE_MODIFY`, `PCMK_VALUE_MOVE`,
    `PCMK_VALUE_NE`, `PCMK_VALUE_NEVER`, `PCMK_VALUE_NONE`,
    `PCMK_VALUE_NONNEGATIVE_INTEGER`, `PCMK_VALUE_NOTHING`,
    `PCMK_VALUE_NOT_DEFINED`, `PCMK_VALUE_NUMBER`, `PCMK_VALUE_OFFLINE`,
    `PCMK_VALUE_ONLINE`, `PCMK_VALUE_ONLY_GREEN`, `PCMK_VALUE_OPTIONAL`,
    `PCMK_VALUE_OR`, `PCMK_VALUE_PANIC`, `PCMK_VALUE_PARAM`, `PCMK_VALUE_PENDING`,
    `PCMK_VALUE_PERCENTAGE`, `PCMK_VALUE_PLUS_INFINITY`, `PCMK_VALUE_PORT`,
    `PCMK_VALUE_PROGRESSIVE`, `PCMK_VALUE_QUORUM`, `PCMK_VALUE_READ`,
    `PCMK_VALUE_RED`, `PCMK_VALUE_REMOTE`, `PCMK_VALUE_RESTART`,
    `PCMK_VALUE_RESTART_CONTAINER`, `PCMK_VALUE_REVOKED`, `PCMK_VALUE_SCORE`,
    `PCMK_VALUE_SELECT`, `PCMK_VALUE_SERIALIZE`, `PCMK_VALUE_STANDBY`,
    `PCMK_VALUE_STATIC_LIST`, `PCMK_VALUE_STATUS`, `PCMK_VALUE_STOP`,
    `PCMK_VALUE_STOP_ONLY`, `PCMK_VALUE_STOP_START`, `PCMK_VALUE_STOP_UNEXPECTED`,
    `PCMK_VALUE_STRING`, `PCMK_VALUE_SUCCESS`, `PCMK_VALUE_TIMEOUT`,
    `PCMK_VALUE_TRUE`, `PCMK_VALUE_UNFENCING`, `PCMK_VALUE_UNKNOWN`,
    `PCMK_VALUE_UTILIZATION`, `PCMK_VALUE_VERSION`, `PCMK_VALUE_WRITE`,
    `PCMK_VALUE_YELLOW`, `PCMK_XA_ACTION`, `PCMK_XA_ACTIVE`, `PCMK_XA_ADD_HOST`,
    `PCMK_XA_ADMIN_EPOCH`, `PCMK_XA_ADVANCED`, `PCMK_XA_AGENT`, `PCMK_XA_API_VERSION`,
    `PCMK_XA_ATTRIBUTE`, `PCMK_XA_AUTHOR`, `PCMK_XA_AUTOMATIC`, `PCMK_XA_BLOCKED`,
    `PCMK_XA_BOOLEAN_OP`, `PCMK_XA_BUILD`, `PCMK_XA_CACHED`, `PCMK_XA_CALL`,
    `PCMK_XA_CIB_LAST_WRITTEN`, `PCMK_XA_CIB_NODE`, `PCMK_XA_CLASS`, `PCMK_XA_CLIENT`,
    `PCMK_XA_CODE`, `PCMK_XA_COMMENT`, `PCMK_XA_COMPLETED`, `PCMK_XA_CONTROL_PORT`,
    `PCMK_XA_COUNT`, `PCMK_XA_CRMD`, `PCMK_XA_CRM_DEBUG_ORIGIN`,
    `PCMK_XA_CRM_FEATURE_SET`, `PCMK_XA_CRM_TIMESTAMP`, `PCMK_XA_DAYS`,
    `PCMK_XA_DC_UUID`, `PCMK_XA_DEFAULT`, `PCMK_XA_DELEGATE`, `PCMK_XA_DESCRIPTION`,
    `PCMK_XA_DEST`, `PCMK_XA_DEVICE`, `PCMK_XA_DEVICES`, `PCMK_XA_DISABLED`,
    `PCMK_XA_DURATION`, `PCMK_XA_END`, `PCMK_XA_EPOCH`, `PCMK_XA_EXEC`,
    `PCMK_XA_EXECUTION_CODE`, `PCMK_XA_EXECUTION_DATE`, `PCMK_XA_EXECUTION_MESSAGE`,
    `PCMK_XA_EXEC_TIME`, `PCMK_XA_EXITCODE`, `PCMK_XA_EXITREASON`,
    `PCMK_XA_EXITSTATUS`, `PCMK_XA_EXIT_REASON`, `PCMK_XA_EXPECTED`,
    `PCMK_XA_EXPECTED_UP`, `PCMK_XA_EXTENDED_STATUS`, `PCMK_XA_FAILED`,
    `PCMK_XA_FAILURE_IGNORED`, `PCMK_XA_FAIL_COUNT`, `PCMK_XA_FEATURES`,
    `PCMK_XA_FEATURE_SET`, `PCMK_XA_FILE`, `PCMK_XA_FIRST`, `PCMK_XA_FIRST_ACTION`,
    `PCMK_XA_FOR`, `PCMK_XA_FUNCTION`, `PCMK_XA_GENERATED`, `PCMK_XA_HASH`,
    `PCMK_XA_HAVE_QUORUM`, `PCMK_XA_HEALTH`, `PCMK_XA_HOST`, `PCMK_XA_HOST_INTERFACE`,
    `PCMK_XA_HOST_NETMASK`, `PCMK_XA_HOURS`, `PCMK_XA_ID`, `PCMK_XA_ID_AS_RESOURCE`,
    `PCMK_XA_ID_REF`, `PCMK_XA_IMAGE`, `PCMK_XA_INDEX`, `PCMK_XA_INFLUENCE`,
    `PCMK_XA_INSTANCE`, `PCMK_XA_INTERNAL_PORT`, `PCMK_XA_INTERVAL`,
    `PCMK_XA_IP_RANGE_START`, `PCMK_XA_IS_DC`, `PCMK_XA_KIND`, `PCMK_XA_LANG`,
    `PCMK_XA_LAST_FAILURE`, `PCMK_XA_LAST_GRANTED`, `PCMK_XA_LAST_RC_CHANGE`,
    `PCMK_XA_LAST_UPDATED`, `PCMK_XA_LOCKED_TO`, `PCMK_XA_LOCKED_TO_HYPHEN`,
    `PCMK_XA_LOSS_POLICY`, `PCMK_XA_MAINTENANCE`, `PCMK_XA_MAINTENANCE_MODE`,
    `PCMK_XA_MANAGED`, `PCMK_XA_MESSAGE`, `PCMK_XA_MINUTES`, `PCMK_XA_MIXED_VERSION`,
    `PCMK_XA_MONTHDAYS`, `PCMK_XA_MONTHS`, `PCMK_XA_MULTI_STATE`, `PCMK_XA_NAME`,
    `PCMK_XA_NETWORK`, `PCMK_XA_NEXT_ROLE`, `PCMK_XA_NODE`, `PCMK_XA_NODEID`,
    `PCMK_XA_NODES_RUNNING_ON`, `PCMK_XA_NODE_ATTRIBUTE`, `PCMK_XA_NODE_NAME`,
    `PCMK_XA_NODE_PATH`, `PCMK_XA_NO_QUORUM_PANIC`, `PCMK_XA_NO_QUORUM_POLICY`,
    `PCMK_XA_NUMBER`, `PCMK_XA_NUMBER_RESOURCES`, `PCMK_XA_NUM_UPDATES`,
    `PCMK_XA_OBJECT_TYPE`, `PCMK_XA_ONLINE`, `PCMK_XA_ON_TARGET`, `PCMK_XA_OP`,
    `PCMK_XA_OPERATION`, `PCMK_XA_OPTIONS`, `PCMK_XA_OP_KEY`, `PCMK_XA_ORIGIN`,
    `PCMK_XA_ORPHAN`, `PCMK_XA_ORPHANED`, `PCMK_XA_PACEMAKERD_STATE`, `PCMK_XA_PATH`,
    `PCMK_XA_PENDING`, `PCMK_XA_PORT`, `PCMK_XA_PRESENT`,
    `PCMK_XA_PRIORITY_FENCING_DELAY_MS`, `PCMK_XA_PROGRAM`, `PCMK_XA_PROMOTABLE`,
    `PCMK_XA_PROMOTED_MAX`, `PCMK_XA_PROMOTED_ONLY`, `PCMK_XA_PROVIDER`,
    `PCMK_XA_QUEUED`, `PCMK_XA_QUEUE_TIME`, `PCMK_XA_QUORUM`, `PCMK_XA_RANGE`,
    `PCMK_XA_RC`, `PCMK_XA_RC_TEXT`, `PCMK_XA_REASON`, `PCMK_XA_REFERENCE`,
    `PCMK_XA_RELOADABLE`, `PCMK_XA_REMAIN_STOPPED`, `PCMK_XA_REMOTE_CLEAR_PORT`,
    `PCMK_XA_REMOTE_NODE`, `PCMK_XA_REMOTE_TLS_PORT`, `PCMK_XA_REPLICAS`,
    `PCMK_XA_REPLICAS_PER_HOST`, `PCMK_XA_REQUEST`, `PCMK_XA_REQUIRE_ALL`,
    `PCMK_XA_RESOURCE`, `PCMK_XA_RESOURCES_RUNNING`, `PCMK_XA_RESOURCE_AGENT`,
    `PCMK_XA_RESOURCE_DISCOVERY`, `PCMK_XA_RESULT`, `PCMK_XA_ROLE`, `PCMK_XA_RSC`,
    `PCMK_XA_RSC_PATTERN`, `PCMK_XA_RSC_ROLE`, `PCMK_XA_RULE_ID`, `PCMK_XA_RUNNING`,
    `PCMK_XA_RUNNING_ON`, `PCMK_XA_RUN_COMMAND`, `PCMK_XA_SCOPE`, `PCMK_XA_SCORE`,
    `PCMK_XA_SCORE_ATTRIBUTE`, `PCMK_XA_SECONDS`, `PCMK_XA_SEQUENTIAL`,
    `PCMK_XA_SHUTDOWN`, `PCMK_XA_SOURCE`, `PCMK_XA_SOURCE_DIR`,
    `PCMK_XA_SOURCE_DIR_ROOT`, `PCMK_XA_SPEC`, `PCMK_XA_STANDARD`, `PCMK_XA_STANDBY`,
    `PCMK_XA_STANDBY_ONFAIL`, `PCMK_XA_START`, `PCMK_XA_STATE`, `PCMK_XA_STATUS`,
    `PCMK_XA_STONITH_ENABLED`, `PCMK_XA_STONITH_TIMEOUT_MS`,
    `PCMK_XA_STOP_ALL_RESOURCES`, `PCMK_XA_SYMMETRICAL`,
    `PCMK_XA_SYMMETRIC_CLUSTER`, `PCMK_XA_SYS_FROM`, `PCMK_XA_TAG`, `PCMK_XA_TARGET`,
    `PCMK_XA_TARGET_ATTRIBUTE`, `PCMK_XA_TARGET_DIR`, `PCMK_XA_TARGET_PATTERN`,
    `PCMK_XA_TARGET_ROLE`, `PCMK_XA_TARGET_VALUE`, `PCMK_XA_TASK`, `PCMK_XA_TEMPLATE`,
    `PCMK_XA_THEN`, `PCMK_XA_THEN_ACTION`, `PCMK_XA_TICKET`, `PCMK_XA_TIME`,
    `PCMK_XA_TYPE`, `PCMK_XA_UNAME`, `PCMK_XA_UNCLEAN`, `PCMK_XA_UNHEALTHY`,
    `PCMK_XA_UNIQUE`, `PCMK_XA_UNMANAGED`, `PCMK_XA_UPDATE_CLIENT`,
    `PCMK_XA_UPDATE_ORIGIN`, `PCMK_XA_UPDATE_USER`, `PCMK_XA_USER`, `PCMK_XA_VALID`,
    `PCMK_XA_VALIDATE_WITH`, `PCMK_XA_VALUE`, `PCMK_XA_VALUE_SOURCE`,
    `PCMK_XA_VERSION`, `PCMK_XA_WATCHDOG`, `PCMK_XA_WEEKDAYS`, `PCMK_XA_WEEKS`,
    `PCMK_XA_WEEKYEARS`, `PCMK_XA_WEIGHT`, `PCMK_XA_WHEN`, `PCMK_XA_WITH_QUORUM`,
    `PCMK_XA_WITH_RSC`, `PCMK_XA_WITH_RSC_ROLE`, `PCMK_XA_XPATH`, `PCMK_XA_YEARDAYS`,
    `PCMK_XA_YEARS`, `PCMK_XE_ACLS`, `PCMK_XE_ACL_GROUP`, `PCMK_XE_ACL_PERMISSION`,
    `PCMK_XE_ACL_ROLE`, `PCMK_XE_ACL_TARGET`, `PCMK_XE_ACTION`, `PCMK_XE_ACTIONS`,
    `PCMK_XE_AGENT`, `PCMK_XE_AGENTS`, `PCMK_XE_AGENT_STATUS`, `PCMK_XE_ALERT`,
    `PCMK_XE_ALERTS`, `PCMK_XE_ALLOCATIONS`, `PCMK_XE_ALLOCATIONS_UTILIZATIONS`,
    `PCMK_XE_ATTRIBUTE`, `PCMK_XE_BAN`, `PCMK_XE_BANS`, `PCMK_XE_BUNDLE`,
    `PCMK_XE_CAPACITY`, `PCMK_XE_CHANGE`, `PCMK_XE_CHANGE_ATTR`,
    `PCMK_XE_CHANGE_LIST`, `PCMK_XE_CHANGE_RESULT`, `PCMK_XE_CHECK`, `PCMK_XE_CIB`,
    `PCMK_XE_CLONE`, `PCMK_XE_CLUSTER_ACTION`, `PCMK_XE_CLUSTER_INFO`,
    `PCMK_XE_CLUSTER_OPTIONS`, `PCMK_XE_CLUSTER_PROPERTY_SET`,
    `PCMK_XE_CLUSTER_STATUS`, `PCMK_XE_COMMAND`, `PCMK_XE_CONFIGURATION`,
    `PCMK_XE_CONSTRAINTS`, `PCMK_XE_CONTENT`, `PCMK_XE_CRM_CONFIG`, `PCMK_XE_CRM_MON`,
    `PCMK_XE_CRM_MON_DISCONNECTED`, `PCMK_XE_CURRENT_DC`, `PCMK_XE_DATE_SPEC`,
    `PCMK_XE_DC`, `PCMK_XE_DEPRECATED`, `PCMK_XE_DIFF`, `PCMK_XE_DIGEST`,
    `PCMK_XE_DIGESTS`, `PCMK_XE_DOCKER`, `PCMK_XE_DURATION`, `PCMK_XE_ERROR`,
    `PCMK_XE_ERRORS`, `PCMK_XE_EXPRESSION`, `PCMK_XE_FAILURE`, `PCMK_XE_FAILURES`,
    `PCMK_XE_FEATURE`, `PCMK_XE_FEATURES`, `PCMK_XE_FENCE_EVENT`,
    `PCMK_XE_FENCE_HISTORY`, `PCMK_XE_FENCING_ACTION`, `PCMK_XE_FENCING_LEVEL`,
    `PCMK_XE_FENCING_TOPOLOGY`, `PCMK_XE_GROUP`, `PCMK_XE_INJECT_ATTR`,
    `PCMK_XE_INJECT_SPEC`, `PCMK_XE_INSTANCE_ATTRIBUTES`, `PCMK_XE_INSTRUCTION`,
    `PCMK_XE_ITEM`, `PCMK_XE_LAST_CHANGE`, `PCMK_XE_LAST_FENCED`,
    `PCMK_XE_LAST_UPDATE`, `PCMK_XE_LIST`, `PCMK_XE_LONGDESC`, `PCMK_XE_METADATA`,
    `PCMK_XE_META_ATTRIBUTES`, `PCMK_XE_MODIFICATIONS`, `PCMK_XE_MODIFY_NODE`,
    `PCMK_XE_MODIFY_TICKET`, `PCMK_XE_NETWORK`, `PCMK_XE_NODE`, `PCMK_XE_NODES`,
    `PCMK_XE_NODES_CONFIGURED`, `PCMK_XE_NODE_ACTION`, `PCMK_XE_NODE_ATTRIBUTES`,
    `PCMK_XE_NODE_HISTORY`, `PCMK_XE_NODE_INFO`, `PCMK_XE_NODE_WEIGHT`,
    `PCMK_XE_NVPAIR`, `PCMK_XE_OBJ_REF`, `PCMK_XE_OP`, `PCMK_XE_OPERATION`,
    `PCMK_XE_OPERATIONS`, `PCMK_XE_OPERATION_HISTORY`, `PCMK_XE_OPTION`,
    `PCMK_XE_OP_DEFAULTS`, `PCMK_XE_OUTPUT`, `PCMK_XE_OVERRIDE`, `PCMK_XE_OVERRIDES`,
    `PCMK_XE_PACEMAKERD`, `PCMK_XE_PACEMAKER_RESULT`, `PCMK_XE_PARAMETER`,
    `PCMK_XE_PARAMETERS`, `PCMK_XE_PODMAN`, `PCMK_XE_PORT_MAPPING`,
    `PCMK_XE_POSITION`, `PCMK_XE_PRIMITIVE`, `PCMK_XE_PROMOTION_SCORE`,
    `PCMK_XE_PROVIDER`, `PCMK_XE_PROVIDERS`, `PCMK_XE_PSEUDO_ACTION`,
    `PCMK_XE_REASON`, `PCMK_XE_RECIPIENT`, `PCMK_XE_REPLICA`, `PCMK_XE_RESOURCE`,
    `PCMK_XE_RESOURCES`, `PCMK_XE_RESOURCES_CONFIGURED`, `PCMK_XE_RESOURCE_AGENT`,
    `PCMK_XE_RESOURCE_AGENT_ACTION`, `PCMK_XE_RESOURCE_CONFIG`,
    `PCMK_XE_RESOURCE_HISTORY`, `PCMK_XE_RESOURCE_REF`, `PCMK_XE_RESOURCE_SET`,
    `PCMK_XE_RESULT_CODE`, `PCMK_XE_REVISED_CLUSTER_STATUS`,
    `PCMK_XE_ROLE`, `PCMK_XE_RSC_ACTION`, `PCMK_XE_RSC_COLOCATION`,
    `PCMK_XE_RSC_DEFAULTS`, `PCMK_XE_RSC_LOCATION`, `PCMK_XE_RSC_ORDER`,
    `PCMK_XE_RSC_TICKET`, `PCMK_XE_RULE`, `PCMK_XE_RULE_CHECK`, `PCMK_XE_SELECT`,
    `PCMK_XE_SELECT_ATTRIBUTES`, `PCMK_XE_SELECT_FENCING`, `PCMK_XE_SELECT_NODES`,
    `PCMK_XE_SELECT_RESOURCES`, `PCMK_XE_SHADOW`, `PCMK_XE_SHORTDESC`,
    `PCMK_XE_SOURCE`, `PCMK_XE_SPECIAL`, `PCMK_XE_STACK`, `PCMK_XE_STATUS`,
    `PCMK_XE_STORAGE`, `PCMK_XE_STORAGE_MAPPING`, `PCMK_XE_SUMMARY`, `PCMK_XE_TAG`,
    `PCMK_XE_TAGS`, `PCMK_XE_TARGET`, `PCMK_XE_TEMPLATE`, `PCMK_XE_TICKET`,
    `PCMK_XE_TICKETS`, `PCMK_XE_TIMING`, `PCMK_XE_TIMINGS`, `PCMK_XE_TRANSITION`,
    `PCMK_XE_UTILIZATION`, `PCMK_XE_UTILIZATIONS`, `PCMK_XE_VALIDATE`,
    `PCMK_XE_VERSION`, `PCMK_XE_XML`, and `PCMK_XE_XML_PATCHSET`
  + **libcrmcommon:** add functions `pcmk_action_text()`, `pcmk_find_node()`,
    `pcmk_foreach_active_resource()`, `pcmk_get_dc()`, `pcmk_parse_interval_spec()`,
    `pcmk_get_no_quorum_policy()`, `pcmk_has_quorum()`,
    `pcmk_node_is_clean()`, `pcmk_update_configured_schema()`,
    `pcmk_node_is_in_maintenance()`, `pcmk_node_is_online()`,
    `pcmk_node_is_pending()`, `pcmk_node_is_shutting_down()`, `pcmk_on_fail_text()`,
    `pcmk_parse_action()`, `pcmk_parse_role()`, `pcmk_resource_id()`,
    `pcmk_resource_is_managed()`, `pcmk_role_text()`, and `pcmk_set_scheduler_cib()`
  + **libcrmcommon:** add type `pcmk_rule_input_t`
  + **libcrmcommon:** deprecate globals `crm_log_level`, `crm_trace_nonlog`,
    `was_processing_error`, and `was_processing_warning`
  + **libcrmcommon:** deprecate functions `add_message_xml()`, `add_node_copy()`,
    `can_prune_leaf()`, `cli_config_update()`, `copy_in_properties()`, `copy_xml()`,
    `create_hello_message()`, `pcmk_parse_action()`, `create_reply()`,
    `create_reply_adv()`, `create_request()`, `create_request_adv()`,
    `create_xml_node()`, `crm_map_element_name()`, `crm_next_same_xml()`,
    `crm_parse_interval_spec()`, `crm_xml_escape()`, `diff_xml_object()`,
    `dump_xml_formatted()`, `dump_xml_formatted_with_text()`,
    `dump_xml_unformatted()`, `expand_plus_plus()`, `filename2xml()`,
    `find_xml_children()`, `find_xml_node()`, `first_named_child()`,
    `fix_plus_plus_recursive()`, `get_message_xml()`, `get_schema_name()`,
    `get_schema_version()`, `get_xpath_object_relative()`, `ID()`,
    `pcmk_action_text()`, `pcmk_create_html_node()`, `pcmk_create_xml_text_node()`,
    `pcmk_hostname()`, `pcmk_on_fail_text()`, `purge_diff_markers()`,
    `replace_xml_child()`, `stdin2xml()`, `string2xml()`, `subtract_xml_object()`,
    `update_validation()`, `update_xml_child()`, `validate_xml()`,
    `validate_xml_verbose()`, `write_xml_fd()`, `write_xml_file()`,
    `xml_latest_schema()`, and `xml_remove_prop()`
  + **libcrmcommon:** deprecate constants `CIB_OPTIONS_FIRST`, `CRM_INFINITY_S`,
    `CRM_MINUS_INFINITY_S`, `CRM_OP_LOCAL_SHUTDOWN`, `CRM_PLUS_INFINITY_S`,
    `CRM_SCORE_INFINITY`, `F_CLIENTNAME`, `F_CRM_DATA`, `F_CRM_DC_LEAVING`,
    `F_CRM_ELECTION_AGE_S`, `F_CRM_ELECTION_AGE_US`, `F_CRM_ELECTION_ID`,
    `F_CRM_ELECTION_OWNER`, `F_CRM_HOST_FROM`, `F_CRM_HOST_TO`, `F_CRM_JOIN_ID`,
    `F_CRM_MSG_TYPE`, `F_CRM_ORIGIN`, `F_CRM_REFERENCE`, `F_CRM_SYS_FROM`,
    `F_CRM_SYS_TO`, `F_CRM_TASK`, `F_CRM_TGRAPH`, `F_CRM_TGRAPH_INPUT`,
    `F_CRM_THROTTLE_MAX`, `F_CRM_THROTTLE_MODE`, `F_CRM_USER`, `F_CRM_VERSION`,
    `F_ORIG`, `F_SEQ`, `F_SUBTYPE`, `F_TYPE`, `F_XML_TAGNAME`, `INFINITY`, `INFINITY_S`,
    `MINUS_INFINITY_S`, `OFFLINESTATUS`, `ONLINESTATUS`,
    `PCMK_XA_PROMOTED_MAX_LEGACY`, `PCMK_XA_PROMOTED_NODE_MAX_LEGACY`,
    `PCMK_XA_TARGET_PATTERN`, `PCMK_XA_UNAME`, `PCMK_XE_PROMOTABLE_LEGACY`,
    `SUPPORT_UPSTART`, `T_ATTRD`, `T_CRM`, `XML_ACL_ATTR_ATTRIBUTE`,
    `XML_ACL_ATTR_KIND`, `XML_ACL_ATTR_REF`, `XML_ACL_ATTR_REFv1`, `XML_ACL_ATTR_TAG`,
    `XML_ACL_ATTR_TAGv1`, `XML_ACL_ATTR_XPATH`, `XML_ACL_TAG_DENY`,
    `XML_ACL_TAG_GROUP`, `XML_ACL_TAG_PERMISSION`, `XML_ACL_TAG_READ`,
    `XML_ACL_TAG_ROLE`, `XML_ACL_TAG_ROLE_REF`, `XML_ACL_TAG_ROLE_REFv1`,
    `XML_ACL_TAG_USER`, `XML_ACL_TAG_USERv1`, `XML_ACL_TAG_WRITE`,
    `XML_AGENT_ATTR_CLASS`, `XML_AGENT_ATTR_PROVIDER`, `XML_ALERT_ATTR_PATH`,
    `XML_ALERT_ATTR_REC_VALUE`, `XML_ALERT_ATTR_TIMEOUT`,
    `XML_ALERT_ATTR_TSTAMP_FORMAT`, `XML_ATTR_CRM_VERSION`, `XML_ATTR_DC_UUID`,
    `XML_ATTR_DESC`, `XML_ATTR_DIGEST`, `XML_ATTR_GENERATION`,
    `XML_ATTR_GENERATION_ADMIN`, `XML_ATTR_HAVE_QUORUM`, `XML_ATTR_HAVE_WATCHDOG`,
    `XML_ATTR_ID`, `XML_ATTR_IDREF`, `XML_ATTR_ID_LONG`, `XML_ATTR_NAME`,
    `XML_ATTR_NUMUPDATES`, `XML_ATTR_OP`, `XML_ATTR_ORIGIN`, `XML_ATTR_QUORUM_PANIC`,
    `XML_ATTR_REFERENCE`, `XML_ATTR_REQUEST`, `XML_ATTR_RESPONSE`,
    `XML_ATTR_STONITH_DEVICES`, `XML_ATTR_STONITH_INDEX`, `XML_ATTR_STONITH_TARGET`,
    `XML_ATTR_STONITH_TARGET_ATTRIBUTE`, `XML_ATTR_STONITH_TARGET_VALUE`,
    `XML_ATTR_TE_NOWAIT`, `XML_ATTR_TE_TARGET_RC`, `XML_ATTR_TIMEOUT`,
    `XML_ATTR_TRANSITION_KEY`, `XML_ATTR_TRANSITION_MAGIC`, `XML_ATTR_TSTAMP`,
    `XML_ATTR_TYPE`, `XML_ATTR_UPDATE_CLIENT`, `XML_ATTR_UPDATE_ORIGIN`,
    `XML_ATTR_UPDATE_USER`, `XML_ATTR_VALIDATION`, `XML_ATTR_VERSION`,
    `XML_BOOLEAN_FALSE`, `XML_BOOLEAN_NO`, `XML_BOOLEAN_TRUE`, `XML_BOOLEAN_YES`,
    `XML_CIB_ATTR_PRIORITY`, `XML_CIB_ATTR_SHUTDOWN`, `XML_CIB_ATTR_WRITTEN`,
    `XML_CIB_TAG_ACLS`, `XML_CIB_TAG_ALERT`, `XML_CIB_TAG_ALERTS`,
    `XML_CIB_TAG_ALERT_ATTR`, `XML_CIB_TAG_ALERT_ATTRIBUTES`,
    `XML_CIB_TAG_ALERT_FENCING`, `XML_CIB_TAG_ALERT_NODES`,
    `XML_CIB_TAG_ALERT_RECIPIENT`, `XML_CIB_TAG_ALERT_RESOURCES`,
    `XML_CIB_TAG_ALERT_SELECT`, `XML_CIB_TAG_CONFIGURATION`,
    `XML_CIB_TAG_CONSTRAINTS`, `XML_CIB_TAG_CONTAINER`, `XML_CIB_TAG_CRMCONFIG`,
    `XML_CIB_TAG_GENERATION_TUPPLE`, `XML_CIB_TAG_GROUP`, `XML_CIB_TAG_INCARNATION`,
    `XML_CIB_TAG_LRM`, `XML_CIB_TAG_NODE`, `XML_CIB_TAG_NODES`, `XML_CIB_TAG_NVPAIR`,
    `XML_CIB_TAG_OBJ_REF`, `XML_CIB_TAG_OPCONFIG`, `XML_CIB_TAG_PROPSET`,
    `XML_CIB_TAG_RESOURCE`, `XML_CIB_TAG_RESOURCES`, `XML_CIB_TAG_RSCCONFIG`,
    `XML_CIB_TAG_RSC_TEMPLATE`, `XML_CIB_TAG_SECTION_ALL`, `XML_CIB_TAG_STATE`,
    `XML_CIB_TAG_STATUS`, `XML_CIB_TAG_TAG`, `XML_CIB_TAG_TAGS`,
    `XML_CIB_TAG_TICKETS`, `XML_CIB_TAG_TICKET_STATE`, `XML_COLOC_ATTR_INFLUENCE`,
    `XML_COLOC_ATTR_NODE_ATTR`, `XML_COLOC_ATTR_SOURCE`,
    `XML_COLOC_ATTR_SOURCE_INSTANCE`, `XML_COLOC_ATTR_SOURCE_ROLE`,
    `XML_COLOC_ATTR_TARGET`, `XML_COLOC_ATTR_TARGET_INSTANCE`,
    `XML_COLOC_ATTR_TARGET_ROLE`, `XML_CONFIG_ATTR_DC_DEADTIME`,
    `XML_CONFIG_ATTR_ELECTION_FAIL`, `XML_CONFIG_ATTR_FENCE_REACTION`,
    `XML_CONFIG_ATTR_FORCE_QUIT`, `XML_CONFIG_ATTR_NODE_PENDING_TIMEOUT`,
    `XML_CONFIG_ATTR_PRIORITY_FENCING_DELAY`, `XML_CONFIG_ATTR_RECHECK`,
    `XML_CONFIG_ATTR_SHUTDOWN_LOCK`, `XML_CONFIG_ATTR_SHUTDOWN_LOCK_LIMIT`,
    `XML_CONS_ATTR_SYMMETRICAL`, `XML_CONS_TAG_RSC_DEPEND`,
    `XML_CONS_TAG_RSC_LOCATION`, `XML_CONS_TAG_RSC_ORDER`, `XML_CONS_TAG_RSC_SET`,
    `XML_CONS_TAG_RSC_TICKET`, `XML_CRM_TAG_PING`, `XML_DIFF_ATTR`, `XML_DIFF_CHANGE`,
    `XML_DIFF_LIST`, `XML_DIFF_MARKER`, `XML_DIFF_OP`, `XML_DIFF_PATH`,
    `XML_DIFF_POSITION`, `XML_DIFF_RESULT`, `XML_DIFF_VERSION`, `XML_DIFF_VSOURCE`,
    `XML_DIFF_VTARGET`, `XML_EXPR_ATTR_ATTRIBUTE`, `XML_EXPR_ATTR_OPERATION`,
    `XML_EXPR_ATTR_TYPE`, `XML_EXPR_ATTR_VALUE`, `XML_EXPR_ATTR_VALUE_SOURCE`,
    `XML_FAILCIB_ATTR_ID`, `XML_FAILCIB_ATTR_OBJTYPE`, `XML_FAILCIB_ATTR_OP`,
    `XML_FAILCIB_ATTR_REASON`, `XML_FAIL_TAG_CIB`, `XML_GRAPH_TAG_CRM_EVENT`,
    `XML_GRAPH_TAG_DOWNED`, `XML_GRAPH_TAG_MAINTENANCE`,
    `XML_GRAPH_TAG_PSEUDO_EVENT`, `XML_GRAPH_TAG_RSC_OP`,
    `XML_LOCATION_ATTR_DISCOVERY`, `XML_LOC_ATTR_SOURCE`,
    `XML_LOC_ATTR_SOURCE_PATTERN`, `XML_LRM_ATTR_CALLID`,
    `XML_LRM_ATTR_EXIT_REASON`, `XML_LRM_ATTR_INTERVAL`, `XML_LRM_ATTR_INTERVAL_MS`,
    `XML_LRM_ATTR_MIGRATE_SOURCE`, `XML_LRM_ATTR_MIGRATE_TARGET`,
    `XML_LRM_ATTR_OPSTATUS`, `XML_LRM_ATTR_OP_DIGEST`, `XML_LRM_ATTR_OP_RESTART`,
    `XML_LRM_ATTR_OP_SECURE`, `XML_LRM_ATTR_RC`, `XML_LRM_ATTR_RESTART_DIGEST`,
    `XML_LRM_ATTR_ROUTER_NODE`, `XML_LRM_ATTR_RSCID`, `XML_LRM_ATTR_SECURE_DIGEST`,
    `XML_LRM_ATTR_TARGET`, `XML_LRM_ATTR_TARGET_UUID`, `XML_LRM_ATTR_TASK`,
    `XML_LRM_ATTR_TASK_KEY`, `XML_LRM_TAG_RESOURCE`, `XML_LRM_TAG_RESOURCES`,
    `XML_LRM_TAG_RSC_OP`, `XML_NODE_ATTR_RSC_DISCOVERY`, `XML_NODE_IS_FENCED`,
    `XML_NODE_IS_MAINTENANCE`, `XML_NODE_IS_REMOTE`, `XML_NVPAIR_ATTR_NAME`,
    `XML_NVPAIR_ATTR_VALUE`, `XML_OP_ATTR_ALLOW_MIGRATE`, `XML_OP_ATTR_DIGESTS_ALL`,
    `XML_OP_ATTR_DIGESTS_SECURE`, `XML_OP_ATTR_INTERVAL_ORIGIN`,
    `XML_OP_ATTR_ON_FAIL`, `XML_OP_ATTR_PENDING`, `XML_OP_ATTR_START_DELAY`,
    `XML_ORDER_ATTR_FIRST`, `XML_ORDER_ATTR_FIRST_ACTION`, `XML_ORDER_ATTR_KIND`,
    `XML_ORDER_ATTR_THEN`, `XML_ORDER_ATTR_THEN_ACTION`, `XML_PING_ATTR_CRMDSTATE`,
    `XML_PING_ATTR_PACEMAKERDSTATE`, `XML_PING_ATTR_PACEMAKERDSTATE_INIT`,
    `XML_PING_ATTR_PACEMAKERDSTATE_REMOTE`,
    `XML_PING_ATTR_PACEMAKERDSTATE_RUNNING`,
    `XML_PING_ATTR_PACEMAKERDSTATE_SHUTDOWNCOMPLETE`,
    `XML_PING_ATTR_PACEMAKERDSTATE_SHUTTINGDOWN`,
    `XML_PING_ATTR_PACEMAKERDSTATE_STARTINGDAEMONS`,
    `XML_PING_ATTR_PACEMAKERDSTATE_WAITPING`, `XML_PING_ATTR_STATUS`,
    `XML_PING_ATTR_SYSFROM`, `XML_REMOTE_ATTR_RECONNECT_INTERVAL`,
    `XML_RSC_ATTR_CLEAR_INTERVAL`, `XML_RSC_ATTR_CLEAR_OP`,
    `XML_RSC_ATTR_CONTAINER`, `XML_RSC_ATTR_CRITICAL`, `XML_RSC_ATTR_INCARNATION`,
    `XML_RSC_ATTR_INTERLEAVE`, `XML_RSC_ATTR_INTERNAL_RSC`,
    `XML_RSC_ATTR_MAINTENANCE`, `XML_RSC_ATTR_MANAGED`, `XML_RSC_ATTR_MULTIPLE`,
    `XML_RSC_ATTR_NOTIFY`, `XML_RSC_ATTR_ORDERED`, `XML_RSC_ATTR_PROMOTABLE`,
    `XML_RSC_ATTR_REMOTE_NODE`, `XML_RSC_ATTR_REMOTE_RA_ADDR`,
    `XML_RSC_ATTR_REMOTE_RA_PORT`, `XML_RSC_ATTR_REMOTE_RA_SERVER`,
    `XML_RSC_ATTR_REQUIRES`, `XML_RSC_ATTR_RESTART`, `XML_RSC_ATTR_STICKINESS`,
    `XML_RSC_ATTR_TARGET`, `XML_RSC_ATTR_TARGET_ROLE`, `XML_RSC_ATTR_UNIQUE`,
    `XML_RSC_OP_LAST_CHANGE`, `XML_RSC_OP_T_EXEC`, `XML_RSC_OP_T_QUEUE`,
    `XML_RULE_ATTR_BOOLEAN_OP`, `XML_RULE_ATTR_ROLE`, `XML_RULE_ATTR_SCORE`,
    `XML_RULE_ATTR_SCORE_ATTRIBUTE`, `XML_TAG_ATTRS`, `XML_TAG_ATTR_SETS`,
    `XML_TAG_CIB`, `XML_TAG_DIFF`, `XML_TAG_EXPRESSION`, `XML_TAG_FAILED`,
    `XML_TAG_FENCING_LEVEL`, `XML_TAG_FENCING_TOPOLOGY`, `XML_TAG_GRAPH`,
    `XML_TAG_META_SETS`, `XML_TAG_OPTIONS`, `XML_TAG_PARAM`, `XML_TAG_PARAMS`,
    `XML_TAG_RESOURCE_REF`, `XML_TAG_RULE`, `XML_TAG_TRANSIENT_NODEATTRS`,
    `XML_TAG_UTILIZATION`, `XML_TICKET_ATTR_LOSS_POLICY`, and
    `XML_TICKET_ATTR_TICKET`
  + **libcrmcommon:** deprecate direct access to all members of `pcmk_scheduler_t`,
    `pcmk_tag_t`, and `pcmk_ticket_t`
  + **libcrmcommon:** deprecate `pcmk_rsc_methods_t`, `pcmk_assignment_methods_t`,
    struct `pe_action_s`, struct `pe_resource_s`, struct `resource_alloc_functions_s`,
    struct `resource_object_functions_s`, struct `pe_node_s`, and
    struct `pe_node_shared_s`, including all their members
  + **libcrmcommon:** deprecate enums `action_fail_response`, `action_tasks`,
    `expression_type`, `node_type`, `pcmk_rsc_flags`, `pcmk_scheduler_flags`,
    `pe_action_flags`, `pe_discover_e`, `pe_obj_types`, `rsc_recovery_type`, and
    `rsc_start_requirement`, including all their values
  + **liblrmd:** deprecate constants `F_LRMD_ALERT`, `F_LRMD_ALERT_ID`,
    `F_LRMD_ALERT_PATH`, `F_LRMD_CALLBACK_TOKEN`, `F_LRMD_CALLDATA`, `F_LRMD_CALLID`,
    `F_LRMD_CALLOPTS`, `F_LRMD_CLASS`, `F_LRMD_CLIENTID`, `F_LRMD_CLIENTNAME`,
    `F_LRMD_EXEC_RC`, `F_LRMD_IPC_CLIENT`, `F_LRMD_IPC_IPC_SERVER`, `F_LRMD_IPC_MSG`,
    `F_LRMD_IPC_MSG_FLAGS`, `F_LRMD_IPC_MSG_ID`, `F_LRMD_IPC_OP`, `F_LRMD_IPC_USER`,
    `F_LRMD_IS_IPC_PROVIDER`, `F_LRMD_OPERATION`, `F_LRMD_OP_STATUS`, `F_LRMD_ORIGIN`,
    `F_LRMD_PROTOCOL_VERSION`, `F_LRMD_PROVIDER`, `F_LRMD_RC`, `F_LRMD_REMOTE_MSG_ID`,
    `F_LRMD_REMOTE_MSG_TYPE`, `F_LRMD_RSC`, `F_LRMD_RSC_ACTION`, `F_LRMD_RSC_DELETED`,
    `F_LRMD_RSC_EXEC_TIME`, `F_LRMD_RSC_EXIT_REASON`, `F_LRMD_RSC_ID`,
    `F_LRMD_RSC_INTERVAL`, `F_LRMD_RSC_OUTPUT`, `F_LRMD_RSC_QUEUE_TIME`,
    `F_LRMD_RSC_RCCHANGE_TIME`, `F_LRMD_RSC_RUN_TIME`, `F_LRMD_RSC_START_DELAY`,
    `F_LRMD_RSC_USERDATA_STR`, `F_LRMD_TIMEOUT`, `F_LRMD_TYPE`, `F_LRMD_WATCHDOG`,
    `T_LRMD`, `T_LRMD_IPC_PROXY`, `T_LRMD_NOTIFY`, `T_LRMD_REPLY`, and `T_LRMD_RSC_OP`
  + **libpacemaker:** distribute pacemaker.h header to allow high-level API usage
  + **libpe_rules:** deprecate functions `find_expression_type()`,
    `pe_evaluate_rules()`, `pe_eval_expr()`, `pe_eval_rules()`, `pe_eval_subexpr()`,
    `pe_expand_re_matches()`, `pe_test_expression()`, and `pe_test_rule()`
  + **libpe_rules,libpe_status:** move enum `expression_type` and globals
    `was_processing_error` and `was_processing_warning` to libcrmcommon
  + **libpe_rules,libpe_status:** deprecate role member of `pe_op_eval_data`
  + **libpe_rules,libpe_status:** deprecate functions `text2task()`, `fail2text()`,
    `recovery2text()`, `role2text()`, `task2text()`, and `text2role()`
  + **libpe_status:** deprecate functions `pe_find_node()`, `pe_pref()`,
    `pe_rsc_is_anon_clone()`, `pe_rsc_is_bundled()`, `pe_rsc_is_clone()`,
    and `pe_rsc_is_unique_clone()`
  + **libpe_status:** deprecate global `resource_class_functions`
  + **libstonithd:** deprecate constants `T_STONITH_NOTIFY_DISCONNECT`,
    `T_STONITH_NOTIFY_FENCE`, `T_STONITH_NOTIFY_HISTORY`, and
    `T_STONITH_NOTIFY_HISTORY_SYNCED`

# Pacemaker-2.1.7 (19 Dec 2023)
- 1388 commits with 358 files changed, 23771 insertions(+), 17219 deletions(-)

## Features added since Pacemaker-2.1.6

  + **build:** allow building with libxml2 2.12.0 and greater
  + **CIB:** deprecate "ordering" attribute of "resource_set"
  + **CIB:** new cluster option "node-pending-timeout" (defaulting to 0, meaning
    no timeout, to preserve existing behavior) allows fencing of nodes that do
    not join Pacemaker's controller group within this much time after joining
    the cluster
  + **controller:** `PCMK_node_start_state` now works with Pacemaker Remote nodes
  + **tools:** `crm_verify` now supports `--quiet` option (currently same as default
    behavior, but in the future, verbose behavior might become the default,
    so script writers are recommended to explicitly add `--quiet` if they do not
    want output)
  + **tools:** `crm_node` supports standard `--output-as/--output-to` arguments
  + **tests:** CTSlab.py was renamed to cts-lab

## Fixes since Pacemaker-2.1.6

  + **logging:** restore ability to enable XML trace logs by file and function
    *(regression introduced in 2.1.6)*
  + **scheduler:** avoid double free with disabled recurring actions
    *(regression introduced in 2.1.5)*
  + **tools:** consider dampening argument when setting values with `attrd_updater`
    *(regression introduced in 2.1.5)*
  + **tools:** wait for reply from `crm_node -R` *(regression introduced in 2.0.5)*
  + **agents:** handle dampening parameter consistently and correctly
  + **CIB:** be more strict about ignoring colocation elements without an ID
  + **controller:** do not check whether watchdog fencing is enabled
    if "stonith-watchdog-timeout" is not configured
  + **controller:** don't try to execute agent action at shutdown
  + **controller:** avoid race condition when updating node state during join
  + **controller:** correctly determine state of a fenced node without a name
  + **controller:** wait a second between fencer connection attempts
  + **libpacemaker:** avoid shuffling clone instances unnecessarily
  + **libpacemaker:** get bundle container's promotion score from correct node
  + **libpacemaker:** role-based colocations now work with bundles
  + **libpacemaker:** clone-node-max now works with cloned groups
  + **scheduler:** compare anti-colocation dependent negative preferences against
    stickiness
  + **scheduler:** consider explicit colocations with group members
  + **scheduler:** avoid fencing a pending node without a name
  + **scheduler:** properly evaluate rules in action meta-attributes
  + **scheduler:** properly sort rule-based blocks when overwriting values
  + **tools:** `crm_resource` `--wait` will now wait if any actions are pending
    (previously it would wait only if new actions were planned)
  + **tools:** `crm_verify` `--output-as=xml` now includes detailed messages
  + **tools:** avoid showing pending nodes as having "<3.15.1" feature set in
    `crm_mon`
  + **tools:** fix display of clone descriptions
  + **tools:** `crm_resource` now reports an error rather than timing out when
    trying to restart an unmanaged resource
  + **tools:** `crm_resource` now properly detects which promoted role name to use
    in ban and move constraints

## Public API changes since Pacemaker-2.1.6 (all API/ABI backward-compatible)

  + **libcib:** `cib_t` now supports transactions via new `cib_api_operations_t`
    methods, new `cib_transaction` value in enum `cib_call_options`, and new
    `cib_t` transaction and user members
  + **libcib:** `cib_t` now supports setting the ACL user for methods via new
    `cib_api_operations_t` `set_user()` method
  + **libcib:** deprecate `cib_api_operations_t` methods `inputfd()`, `noop()`,
    `quit()`, `set_op_callback()`, and `signon_raw()`
  + **libcib:** deprecate `cib_call_options` values `cib_mixed_update`,
    `cib_scope_local`, and `cib_zero_copy`
  + **libcib:** deprecate `cib_t` `op_callback` member
  + **libcrmcluster:** deprecate `set_uuid()`
  + **libcrmcluster:** `send_cluster_message()'s` data argument is const
  + **libcrmcommon:** add enum `pcmk_rc_e` values `pcmk_rc_compression`,
    `pcmk_rc_ns_resolution`, and `pcmk_rc_no_transaction`
  + **libcrmcommon,libpe_rules,libpe_status:** many APIs have been moved from
    `libpe_rules` and `libpe_status` to libcrmcommon, sometimes with new names
    (deprecating the old ones), as described below
  + **libcrmcommon:** add (and deprecate) `PCMK_DEFAULT_METADATA_TIMEOUT_MS` defined
    constant
  + **libcrmcommon:** add enum `pcmk_rsc_flags`
  + **libcrmcommon:** add enum `pcmk_scheduler_flags`
  + **libcrmcommon:** add `pcmk_action_added_to_graph`
  + **libcrmcommon:** add `pcmk_action_always_in_graph`
  + **libcrmcommon:** add `pcmk_action_attrs_evaluated`
  + **libcrmcommon:** add `PCMK_ACTION_CANCEL` string constant
  + **libcrmcommon:** add `PCMK_ACTION_CLEAR_FAILCOUNT` string constant
  + **libcrmcommon:** add `PCMK_ACTION_CLONE_ONE_OR_MORE` string constant
  + **libcrmcommon:** add `PCMK_ACTION_DELETE` string constant
  + **libcrmcommon:** add `PCMK_ACTION_DEMOTE` string constant
  + **libcrmcommon:** add `pcmk_action_demote` to enum `action_tasks`
  + **libcrmcommon:** add `PCMK_ACTION_DEMOTED` string constant
  + **libcrmcommon:** add `pcmk_action_demoted` to enum `action_tasks`
  + **libcrmcommon:** add `pcmk_action_detect_loop`
  + **libcrmcommon:** add `PCMK_ACTION_DO_SHUTDOWN` string constant
  + **libcrmcommon:** add `pcmk_action_fence` to enum `action_tasks`
  + **libcrmcommon:** add `pcmk_action_inputs_deduplicated`
  + **libcrmcommon:** add `PCMK_ACTION_LIST` string constant
  + **libcrmcommon:** add `PCMK_ACTION_LOAD_STOPPED` string constant
  + **libcrmcommon:** add `PCMK_ACTION_LRM_DELETE` string constant
  + **libcrmcommon:** add `PCMK_ACTION_MAINTENANCE_NODES` string constant
  + **libcrmcommon:** add `PCMK_ACTION_META_DATA` string constant
  + **libcrmcommon:** add `pcmk_action_migratable`
  + **libcrmcommon:** add `PCMK_ACTION_MIGRATE_FROM` string constant
  + **libcrmcommon:** add `PCMK_ACTION_MIGRATE_TO` string constant
  + **libcrmcommon:** add `pcmk_action_migration_abort`
  + **libcrmcommon:** add `pcmk_action_min_runnable`
  + **libcrmcommon:** add `PCMK_ACTION_MONITOR` string constant
  + **libcrmcommon:** add `pcmk_action_monitor` to enum `action_tasks`
  + **libcrmcommon:** add `PCMK_ACTION_NOTIFIED` string constant
  + **libcrmcommon:** add `pcmk_action_notified` to enum `action_tasks`
  + **libcrmcommon:** add `PCMK_ACTION_NOTIFY` string constant
  + **libcrmcommon:** add `pcmk_action_notify` to enum `action_tasks`
  + **libcrmcommon:** add `PCMK_ACTION_OFF` string constant
  + **libcrmcommon:** add `PCMK_ACTION_ON` string constant
  + **libcrmcommon:** add `PCMK_ACTION_ONE_OR_MORE` string constant
  + **libcrmcommon:** add `pcmk_action_on_dc`
  + **libcrmcommon:** add `pcmk_action_optional`
  + **libcrmcommon:** add `PCMK_ACTION_PROMOTE` string constant
  + **libcrmcommon:** add `pcmk_action_promote` to enum `action_tasks`
  + **libcrmcommon:** add `PCMK_ACTION_PROMOTED` string constant
  + **libcrmcommon:** add `pcmk_action_promoted` to enum `action_tasks`
  + **libcrmcommon:** add `pcmk_action_pseudo`
  + **libcrmcommon:** add `PCMK_ACTION_REBOOT` string constant
  + **libcrmcommon:** add `PCMK_ACTION_RELOAD` string constant
  + **libcrmcommon:** add `PCMK_ACTION_RELOAD_AGENT` string constant
  + **libcrmcommon:** add `pcmk_action_reschedule`
  + **libcrmcommon:** add `pcmk_action_runnable`
  + **libcrmcommon:** add `PCMK_ACTION_RUNNING` string constant
  + **libcrmcommon:** add `pcmk_action_shutdown` to enum `action_tasks`
  + **libcrmcommon:** add `PCMK_ACTION_START` string constant
  + **libcrmcommon:** add `pcmk_action_start` to enum `action_tasks`
  + **libcrmcommon:** add `pcmk_action_started` to enum `action_tasks`
  + **libcrmcommon:** add `PCMK_ACTION_STATUS` string constant
  + **libcrmcommon:** add `PCMK_ACTION_STONITH` string constant
  + **libcrmcommon:** add `PCMK_ACTION_STOP` string constant
  + **libcrmcommon:** add `pcmk_action_stop` to enum `action_tasks`
  + **libcrmcommon:** add `PCMK_ACTION_STOPPED` string constant
  + **libcrmcommon:** add `pcmk_action_stopped` to enum `action_tasks`
  + **libcrmcommon:** add `pcmk_action_t` type
  + **libcrmcommon:** add `pcmk_action_unspecified` to enum `action_tasks`
  + **libcrmcommon:** add `PCMK_ACTION_VALIDATE_ALL` string constant
  + **libcrmcommon:** add `pcmk_assignment_methods_t` type
  + **libcrmcommon:** add `PCMK_DEFAULT_ACTION_TIMEOUT_MS` defined constant
  + **libcrmcommon:** add `pcmk_log_xml_as()`
  + **libcrmcommon:** add `PCMK_META_CLONE_MAX` string constant
  + **libcrmcommon:** add `PCMK_META_CLONE_MIN` string constant
  + **libcrmcommon:** add `PCMK_META_CLONE_NODE_MAX` string constant
  + **libcrmcommon:** add `PCMK_META_FAILURE_TIMEOUT` string constant
  + **libcrmcommon:** add `PCMK_META_MIGRATION_THRESHOLD` string constant
  + **libcrmcommon:** add `PCMK_META_PROMOTED_MAX` string constant
  + **libcrmcommon:** add `PCMK_META_PROMOTED_NODE_MAX` string constant
  + **libcrmcommon:** add `pcmk_multiply_active_block` to enum `rsc_recovery_type`
  + **libcrmcommon:** add `pcmk_multiply_active_restart` to enum `rsc_recovery_type`
  + **libcrmcommon:** add `pcmk_multiply_active_stop` to enum `rsc_recovery_type`
  + **libcrmcommon:** add `pcmk_multiply_active_unexpected` to enum `rsc_recovery_type`
  + **libcrmcommon:** add `PCMK_NODE_ATTR_TERMINATE` string constant
  + **libcrmcommon:** add `pcmk_node_t` type
  + **libcrmcommon:** add `pcmk_node_variant_cluster`
  + **libcrmcommon:** add `pcmk_node_variant_remote`
  + **libcrmcommon:** add `pcmk_no_action_flags`
  + **libcrmcommon:** add `pcmk_no_quorum_demote`
  + **libcrmcommon:** add `pcmk_no_quorum_fence`
  + **libcrmcommon:** add `pcmk_no_quorum_freeze`
  + **libcrmcommon:** add `pcmk_no_quorum_ignore`
  + **libcrmcommon:** add `pcmk_no_quorum_stop`
  + **libcrmcommon:** add `pcmk_on_fail_ban` to enum `action_fail_response`
  + **libcrmcommon:** add `pcmk_on_fail_block` to enum `action_fail_response`
  + **libcrmcommon:** add `pcmk_on_fail_demote` to enum `action_fail_response`
  + **libcrmcommon:** add `pcmk_on_fail_fence_node` to enum `action_fail_response`
  + **libcrmcommon:** add `pcmk_on_fail_ignore` to enum `action_fail_response`
  + **libcrmcommon:** add `pcmk_on_fail_reset_remote` to enum `action_fail_response`
  + **libcrmcommon:** add `pcmk_on_fail_restart` to enum `action_fail_response`
  + **libcrmcommon:** add `pcmk_on_fail_restart_container` to enum `action_fail_response`
  + **libcrmcommon:** add `pcmk_on_fail_standby_node` to `action_fail_response`
  + **libcrmcommon:** add `pcmk_on_fail_stop` to enum `action_fail_response`
  + **libcrmcommon:** add `pcmk_probe_always` to enum `pe_discover_e`
  + **libcrmcommon:** add `pcmk_probe_exclusive` to enum `pe_discover_e`
  + **libcrmcommon:** add `pcmk_probe_never` to enum `pe_discover_e`
  + **libcrmcommon:** add `pcmk_requires_fencing` to enum `rsc_start_requirement`
  + **libcrmcommon:** add `pcmk_requires_nothing` to enum `rsc_start_requirement`
  + **libcrmcommon:** add `pcmk_requires_quorum` to enum `rsc_start_requirement`
  + **libcrmcommon:** add `pcmk_resource_t` type
  + **libcrmcommon:** add `pcmk_role_promoted` to enum `rsc_role_e`
  + **libcrmcommon:** add `pcmk_role_started` to enum `rsc_role_e`
  + **libcrmcommon:** add `pcmk_role_stopped` to enum `rsc_role_e`
  + **libcrmcommon:** add `pcmk_role_unknown` to enum `rsc_role_e`
  + **libcrmcommon:** add `pcmk_role_unpromoted` to enum `rsc_role_e`
  + **libcrmcommon:** add `pcmk_rsc_match_anon_basename`
  + **libcrmcommon:** add `pcmk_rsc_match_basename`
  + **libcrmcommon:** add `pcmk_rsc_match_clone_only`
  + **libcrmcommon:** add `pcmk_rsc_match_current_node`
  + **libcrmcommon:** add `pcmk_rsc_match_history`
  + **libcrmcommon:** add `pcmk_rsc_methods_t` type
  + **libcrmcommon:** add `pcmk_rsc_variant_bundle`
  + **libcrmcommon:** add `pcmk_rsc_variant_clone`
  + **libcrmcommon:** add `pcmk_rsc_variant_group`
  + **libcrmcommon:** add `pcmk_rsc_variant_primitive`
  + **libcrmcommon:** add `pcmk_rsc_variant_unknown`
  + **libcrmcommon:** add `pcmk_scheduler_t` type
  + **libcrmcommon:** add `pcmk_tag_t` type
  + **libcrmcommon:** add `pcmk_ticket_t` type
  + **libcrmcommon:** add `PCMK_XA_FORMAT` string constant
  + **libcrmcommon:** `crm_ipc_send()'s` message argument is now const
  + **libcrmcommon:** deprecate `action_demote` in enum `action_tasks`
  + **libcrmcommon:** deprecate `action_demoted` in enum `action_tasks`
  + **libcrmcommon:** deprecate `action_fail_block` in enum `action_fail_response`
  + **libcrmcommon:** deprecate `action_fail_demote` in enum `action_fail_response`
  + **libcrmcommon:** deprecate `action_fail_fence` in enum `action_fail_response`
  + **libcrmcommon:** deprecate `action_fail_ignore` in enum `action_fail_response`
  + **libcrmcommon:** deprecate `action_fail_migrate` in enum `action_fail_response`
  + **libcrmcommon:** deprecate `action_fail_recover` in enum `action_fail_response`
  + **libcrmcommon:** deprecate `action_fail_reset_remote` in enum `action_fail_response`
  + **libcrmcommon:** deprecate `action_fail_standby` in enum `action_fail_response`
  + **libcrmcommon:** deprecate `action_fail_stop` in `action_fail_response`
  + **libcrmcommon:** deprecate `action_notified` in enum `action_tasks`
  + **libcrmcommon:** deprecate `action_notify` in enum `action_tasks`
  + **libcrmcommon:** deprecate `action_promote` in enum `action_tasks`
  + **libcrmcommon:** deprecate `action_promoted` in enum `action_tasks`
  + **libcrmcommon:** deprecate `action_restart_container` in enum `action_fail_response`
  + **libcrmcommon:** deprecate `CRMD_ACTION_CANCEL` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_DELETE` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_DEMOTE` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_DEMOTED` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_METADATA` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_MIGRATE` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_MIGRATED` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_NOTIFIED` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_NOTIFY` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_PROMOTE` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_PROMOTED` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_RELOAD` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_RELOAD_AGENT` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_START` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_STARTED` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_STATUS` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_STOP` string constant
  + **libcrmcommon:** deprecate `CRMD_ACTION_STOPPED` string constant
  + **libcrmcommon:** deprecate `CRMD_METADATA_CALL_TIMEOUT` defined constant
  + **libcrmcommon:** deprecate `crm_action_str()`
  + **libcrmcommon:** deprecate `CRM_DEFAULT_OP_TIMEOUT_S` string constant
  + **libcrmcommon:** deprecate `crm_element_name()`
  + **libcrmcommon:** deprecate `CRM_OP_FENCE` string constant
  + **libcrmcommon:** deprecate `CRM_OP_RELAXED_CLONE` string constant
  + **libcrmcommon:** deprecate `CRM_OP_RELAXED_SET` string constant
  + **libcrmcommon:** deprecate `crm_xml_replace()`
  + **libcrmcommon:** deprecate enum `pe_link_state`
  + **libcrmcommon:** deprecate `getDocPtr()`
  + **libcrmcommon:** deprecate `monitor_rsc` in enum `action_tasks`
  + **libcrmcommon:** deprecate `node_member`
  + **libcrmcommon:** deprecate `node_remote`
  + **libcrmcommon:** deprecate `no_action` in enum `action_tasks`
  + **libcrmcommon:** deprecate `no_quorum_demote`
  + **libcrmcommon:** deprecate `no_quorum_freeze`
  + **libcrmcommon:** deprecate `no_quorum_ignore`
  + **libcrmcommon:** deprecate `no_quorum_stop`
  + **libcrmcommon:** deprecate `no_quorum_suicide`
  + **libcrmcommon:** deprecate `pcmk_log_xml_impl()`
  + **libcrmcommon:** deprecate `pcmk_scheduler_t` localhost member
  + **libcrmcommon:** deprecate `pe_action_dangle`
  + **libcrmcommon:** deprecate `pe_action_dc`
  + **libcrmcommon:** deprecate `pe_action_dedup`
  + **libcrmcommon:** deprecate `pe_action_dumped`
  + **libcrmcommon:** deprecate `pe_action_have_node_attrs`
  + **libcrmcommon:** deprecate `pe_action_implied_by_stonith`
  + **libcrmcommon:** deprecate `pe_action_migrate_runnable`
  + **libcrmcommon:** deprecate `pe_action_optional`
  + **libcrmcommon:** deprecate `pe_action_print_always`
  + **libcrmcommon:** deprecate `pe_action_processed`
  + **libcrmcommon:** deprecate `pe_action_pseudo`
  + **libcrmcommon:** deprecate `pe_action_requires_any`
  + **libcrmcommon:** deprecate `pe_action_reschedule`
  + **libcrmcommon:** deprecate `pe_action_runnable`
  + **libcrmcommon:** deprecate `pe_action_tracking`
  + **libcrmcommon:** deprecate `pe_clone`
  + **libcrmcommon:** deprecate `pe_container`
  + **libcrmcommon:** deprecate `pe_discover_always` in enum `pe_discover_e`
  + **libcrmcommon:** deprecate `pe_discover_exclusive` in enum `pe_discover_e`
  + **libcrmcommon:** deprecate `pe_discover_never` in enum `pe_discover_e`
  + **libcrmcommon:** deprecate `pe_find_anon`
  + **libcrmcommon:** deprecate `pe_find_any`
  + **libcrmcommon:** deprecate `pe_find_clone`
  + **libcrmcommon:** deprecate `pe_find_current`
  + **libcrmcommon:** deprecate `pe_find_inactive`
  + **libcrmcommon:** deprecate `pe_find_renamed`
  + **libcrmcommon:** deprecate `pe_group`
  + **libcrmcommon:** deprecate `pe_native`
  + **libcrmcommon:** deprecate `pe_unknown`
  + **libcrmcommon:** deprecate `recovery_block` in enum `rsc_recovery_type`
  + **libcrmcommon:** deprecate `recovery_stop_only` in enum `rsc_recovery_type`
  + **libcrmcommon:** deprecate `recovery_stop_start` in enum `rsc_recovery_type`
  + **libcrmcommon:** deprecate `recovery_stop_unexpected` in enum `rsc_recovery_type`
  + **libcrmcommon:** deprecate `RSC_CANCEL` string constant
  + **libcrmcommon:** deprecate `RSC_DELETE` string constant
  + **libcrmcommon:** deprecate `RSC_DEMOTE` string constant
  + **libcrmcommon:** deprecate `RSC_DEMOTED` string constant
  + **libcrmcommon:** deprecate `RSC_METADATA` string constant
  + **libcrmcommon:** deprecate `RSC_MIGRATE` string constant
  + **libcrmcommon:** deprecate `RSC_MIGRATED` string constant
  + **libcrmcommon:** deprecate `RSC_NOTIFIED` string constant
  + **libcrmcommon:** deprecate `RSC_NOTIFY` string constant
  + **libcrmcommon:** deprecate `RSC_PROMOTE` string constant
  + **libcrmcommon:** deprecate `RSC_PROMOTED` string constant
  + **libcrmcommon:** deprecate `rsc_req_nothing` in enum `rsc_start_requirement`
  + **libcrmcommon:** deprecate `rsc_req_quorum` in enum `rsc_start_requirement`
  + **libcrmcommon:** deprecate `rsc_req_stonith` in enum `rsc_start_requirement`
  + **libcrmcommon:** deprecate `RSC_ROLE_PROMOTED` in enum `rsc_role_e`
  + **libcrmcommon:** deprecate `RSC_ROLE_STARTED` in enum `rsc_role_e`
  + **libcrmcommon:** deprecate `RSC_ROLE_STOPPED` in enum `rsc_role_e`
  + **libcrmcommon:** deprecate `RSC_ROLE_UNKNOWN` in enum `rsc_role_e`
  + **libcrmcommon:** deprecate `RSC_ROLE_UNPROMOTED`
  + **libcrmcommon:** deprecate `RSC_START` string constant
  + **libcrmcommon:** deprecate `RSC_STARTED` string constant
  + **libcrmcommon:** deprecate `RSC_STATUS` string constant
  + **libcrmcommon:** deprecate `RSC_STOP` string constant
  + **libcrmcommon:** deprecate `RSC_STOPPED` string constant
  + **libcrmcommon:** deprecate `shutdown_crm` in enum `action_tasks`
  + **libcrmcommon:** deprecate `started_rsc` in enum `action_tasks`
  + **libcrmcommon:** deprecate `start_rsc` in enum `action_tasks`
  + **libcrmcommon:** deprecate `stonith_node` in enum `action_tasks`
  + **libcrmcommon:** deprecate `stopped_rsc` in enum `action_tasks`
  + **libcrmcommon:** deprecate `stop_rsc` in enum `action_tasks`
  + **libcrmcommon:** deprecate `TYPE()` macro
  + **libcrmcommon:** deprecate `XML_ATTR_VERBOSE` string constant
  + **libcrmcommon:** deprecate `XML_CIB_ATTR_SOURCE` string constant
  + **libcrmcommon:** deprecate `XML_CIB_TAG_DOMAINS` string constant
  + **libcrmcommon:** deprecate `xml_has_children()`
  + **libcrmcommon:** deprecate `XML_NODE_EXPECTED` string constant
  + **libcrmcommon:** deprecate `XML_NODE_IN_CLUSTER` string constant
  + **libcrmcommon:** deprecate `XML_NODE_IS_PEER` string constant
  + **libcrmcommon:** deprecate `XML_NODE_JOIN_STATE` string constant
  + **libcrmcommon:** deprecate `XML_RSC_ATTR_FAIL_STICKINESS` string constant
  + **libcrmcommon:** deprecate `XML_RSC_ATTR_FAIL_TIMEOUT` string constant
  + **libcrmcommon:** deprecate `XML_RSC_ATTR_INCARNATION_MAX` string constant
  + **libcrmcommon:** deprecate `XML_RSC_ATTR_INCARNATION_MIN` string constant
  + **libcrmcommon:** deprecate `XML_RSC_ATTR_INCARNATION_NODEMAX` string constant
  + **libcrmcommon:** deprecate `XML_RSC_ATTR_PROMOTED_MAX` string constant
  + **libcrmcommon:** deprecate `XML_RSC_ATTR_PROMOTED_NODEMAX` string constant
  + **libcrmcommon:** deprecate `XML_TAG_DIFF_ADDED` string constant
  + **libcrmcommon:** deprecate `XML_TAG_DIFF_REMOVED` string constant
  + **libcrmcommon:** deprecate `XML_TAG_FRAGMENT`
  + **libcrmcommon:** `dump_xml_formatted()'s` argument is now const
  + **libcrmcommon:** `dump_xml_formatted_with_text()'s` argument is const
  + **libcrmcommon:** `dump_xml_unformatted()'s` argument is now const
  + **libcrmcommon:** `save_xml_to_file()'s` xml argument is now const
  + **libcrmcommon:** `validate_xml_verbose()'s` `xml_blob` argument is const
  + **libcrmcommon:** `write_xml_fd()'s` xml argument is now const
  + **libcrmcommon:** `write_xml_file()'s` xml argument is now const
  + **libcrmcommon:** `xml_top` argument of `xpath_search()` is now const
  + **libcrmcommon,libpe_rules,libpe_status:** move enum `pe_ordering`, struct
    `pe_action_wrapper_s`, struct `pe_tag_s`, struct `pe_ticket_s`, struct
    `resource_object_functions_s`, enum `node_type`, enum `pe_action_flags`, enum
    `pe_discover_e`, enum `pe_find`, enum `pe_link_state`, enum `pe_obj_types`, enum
    `pe_quorum_policy`, enum `pe_restart`, struct `pe_action_s`, struct `pe_node_s`,
    struct `pe_node_shared_s`, struct `pe_resource_s`, struct `pe_working_set_s`,
    enum `action_fail_response`, enum `action_tasks`, enum `pe_print_options`, enum
    `rsc_recovery_type`, enum `rsc_role_e`, and enum `rsc_start_requirement` to
    libcrmcommon
  + **libpacemaker,libpe_rules,libpe_status:** use `pcmk_action_t` instead of
    `pe_action_t`, `pcmk_node_t` instead of `pe_node_t`, `pcmk_resource_t` instead of
    `pe_resource_t`, and `pcmk_scheduler_t` instead of `pe_working_set_t` in all API
    structs and functions
  + **libpacemaker:** add `pcmk_list_alternatives()`, `pcmk_list_providers()`,
    `pcmk_list_standards()`, and `pcmk_list_agents()` for functionality equivalent
    to `crm_resource` `--list-ocf-alternatives,` `--list-ocf-providers`,
    `--list-standards,` and `--list-agents`
  + **libpe_rules,libpe_status:** deprecate `pe_action_t` type
  + **libpe_rules,libpe_status:** deprecate `pe_action_wrapper_t`
  + **libpe_rules,libpe_status:** deprecate `pe_node_t` type
  + **libpe_rules,libpe_status:** deprecate `pe_resource_t` type
  + **libpe_rules,libpe_status:** deprecate `pe_tag_t`
  + **libpe_rules,libpe_status:** deprecate `pe_ticket_t`
  + **libpe_rules,libpe_status:** deprecate `pe_working_set_t` type
  + **libpe_rules,libpe_status:** deprecate `resource_alloc_functions_t` type
  + **libpe_rules,libpe_status:** deprecate `resource_object_functions_t`
  + **libpe_status,libpe_rules:** deprecate enum `pe_ordering` and all its values
  + **libpe_status,libpe_rules:** deprecate `RSC_ROLE_MAX`
  + **libpe_status,libpe_rules:** deprecate `RSC_ROLE_PROMOTED_LEGACY_S` string constant
  + **libpe_status,libpe_rules:** deprecate `RSC_ROLE_PROMOTED_S` string constant
  + **libpe_status,libpe_rules:** deprecate `RSC_ROLE_STARTED_S` string constant
  + **libpe_status,libpe_rules:** deprecate `RSC_ROLE_STOPPED_S` string constant
  + **libpe_status,libpe_rules:** deprecate `RSC_ROLE_UNKNOWN_S`
  + **libpe_status,libpe_rules:** deprecate `RSC_ROLE_UNPROMOTED_LEGACY_S` string constant
  + **libpe_status,libpe_rules:** deprecate `RSC_ROLE_UNPROMOTED_S` string constant
  + **libpe_status:** deprecate enum `pe_check_parameters`
  + **libpe_status:** deprecate `pe_flag_check_config`
  + **libpe_status:** deprecate `pe_flag_concurrent_fencing`
  + **libpe_status:** deprecate `pe_flag_enable_unfencing`
  + **libpe_status:** deprecate `pe_flag_have_quorum`
  + **libpe_status:** deprecate `pe_flag_have_remote_nodes`
  + **libpe_status:** deprecate `pe_flag_have_status`
  + **libpe_status:** deprecate `pe_flag_have_stonith_resource`
  + **libpe_status:** deprecate `pe_flag_maintenance_mode`
  + **libpe_status:** deprecate `pe_flag_no_compat`
  + **libpe_status:** deprecate `pe_flag_no_counts`
  + **libpe_status:** deprecate `pe_flag_quick_location`
  + **libpe_status:** deprecate `pe_flag_sanitized`
  + **libpe_status:** deprecate `pe_flag_show_scores`
  + **libpe_status:** deprecate `pe_flag_show_utilization`
  + **libpe_status:** deprecate `pe_flag_shutdown_lock`
  + **libpe_status:** deprecate `pe_flag_startup_fencing`
  + **libpe_status:** deprecate `pe_flag_startup_probes`
  + **libpe_status:** deprecate `pe_flag_start_failure_fatal`
  + **libpe_status:** deprecate `pe_flag_stonith_enabled`
  + **libpe_status:** deprecate `pe_flag_stop_action_orphans`
  + **libpe_status:** deprecate `pe_flag_stop_everything`
  + **libpe_status:** deprecate `pe_flag_stop_rsc_orphans`
  + **libpe_status:** deprecate `pe_flag_symmetric_cluster`
  + **libpe_status:** deprecate `pe_rsc_allow_migrate`
  + **libpe_status:** deprecate `pe_rsc_allow_remote_remotes`
  + **libpe_status:** deprecate `pe_rsc_assigning`
  + **libpe_status:** deprecate `pe_rsc_block`
  + **libpe_status:** deprecate `pe_rsc_critical`
  + **libpe_status:** deprecate `pe_rsc_detect_loop`
  + **libpe_status:** deprecate `pe_rsc_failed`
  + **libpe_status:** deprecate `pe_rsc_failure_ignored`
  + **libpe_status:** deprecate `pe_rsc_fence_device`
  + **libpe_status:** deprecate `pe_rsc_is_container`
  + **libpe_status:** deprecate `pe_rsc_maintenance`
  + **libpe_status:** deprecate `pe_rsc_managed`
  + **libpe_status:** deprecate `pe_rsc_merging`
  + **libpe_status:** deprecate `pe_rsc_needs_fencing`
  + **libpe_status:** deprecate `pe_rsc_needs_quorum`
  + **libpe_status:** deprecate `pe_rsc_needs_unfencing`
  + **libpe_status:** deprecate `pe_rsc_notify`
  + **libpe_status:** deprecate `pe_rsc_orphan`
  + **libpe_status:** deprecate `pe_rsc_orphan_container_filler`
  + **libpe_status:** deprecate `pe_rsc_promotable`
  + **libpe_status:** deprecate `pe_rsc_provisional`
  + **libpe_status:** deprecate `pe_rsc_reload`
  + **libpe_status:** deprecate `pe_rsc_replica_container`
  + **libpe_status:** deprecate `pe_rsc_restarting`
  + **libpe_status:** deprecate `pe_rsc_runnable`
  + **libpe_status:** deprecate `pe_rsc_start_pending`
  + **libpe_status:** deprecate `pe_rsc_stop`
  + **libpe_status:** deprecate `pe_rsc_stop_unexpected`
  + **libpe_status:** deprecate `pe_rsc_unique`

# Pacemaker-2.1.6 (24 May 2023)
- 1124 commits with 402 files changed, 25220 insertions(+), 14751 deletions(-)

## Features added since Pacemaker-2.1.5

  + **CIB:** deprecate "moon" in `date_spec` elements in rules
  + **CIB:** deprecate support for Nagios resources
  + **CIB:** utilization attributes may be set as transient
  + **CIB:** alerts and alert recipients support an "enabled" meta-attribute
  + All daemons support `--output-as/--output-to` options including
    XML output with interactive options
  + **tools:** `attrd_updater` supports `--wait` parameter that can be set to
    "no" (return immediately after submitting request, which is
    the default and previous behavior), "local" (return after the
    new value has taken effect on the local node), or "cluster" (return
    after new value has taken effect on all nodes)
  + **tools:** `attrd_updater` supports `-z/--utilization` to modify
    utilization attributes
  + **tools:** `attrd_updater` supports `--pattern` to affect all attributes
    matching a given pattern
  + **tools:** `crm_attribute` supports `--pattern` with permanent node attributes
    (in addition to previous support for transient attributes)
  + **tools:** `crm_mon` displays resource descriptions if `--show-description` or
    `--show-detail` is given
  + **tools:** `crm_mon` shows maintenance mode when enabled per-resource
  + **tools:** `crm_mon` `--interval` can be used to update XML and text output
    (in addition to previous support for HTML)
  + **tools:** `crm_mon` fencing history includes microseconds in timestamps
  + **tools:** `crm_mon` shows which node it was run on
  + **tools:** `crm_mon` shows whether Pacemaker or Pacemaker Remote is running or
    shutting down
  + **tools:** deprecate `crm_mon --simple-status`
  + **tools:** `crm_resource` `--element` option can be used with
    `--get-parameter`, `--set-parameter,` and `--delete-parameter` to modify
    resource properties such as class, provider, type, and description
  + **tools:** `crm_resource` `--list` shows resource descriptions better
    (including when `--output-as=xml` is used)
  + **tools:** `crm_shadow` supports standard `--output-as/--output-to` arguments

## Fixes since Pacemaker-2.1.5

  + **pacemakerd:** -S should wait for cluster to shut down before returning
                *(regression introduced in 2.1.1)*
  + **Pacemaker Remote:** remote nodes wait for all-clear from cluster before
                      shutting down *(regression introduced in 2.1.5)*
  + **tools:** `attrd_updater` `--query` without `--node` shows attributes from all
           nodes instead of local node *(regression introduced in 2.1.5)*
  + **pacemaker-attrd:** Preserve a Pacemaker Remote node's transient attributes
                     if its connection to the cluster is lost but reconnects
  + **CIB manager:** successful CIB schema upgrade always forces a write
  + **controller:** avoid election storm when joining node has CIB newer than DC
                can accept
  + **controller:** avoid election storm due to incompatible CIB
  + **controller:** avoid use-after-free when disconnecting proxy IPCs during shutdown
  + **controller:** avoid double-incrementing failcount for simulated failures
  + **controller:** avoid reprobing remote nodes when target is a cluster node
  + **controller:** delay join finalization if a transition is in progress
  + **controller:** initial fencing timeout includes any priority-fencing-delay
  + **controller:** shutdown gracefully if scheduler connection is interrupted
                during shutdown
  + **fencer:** avoid crash during shutdown when action is pending
  + **fencer:** calculate fencing timeout correctly when watchdog is used with
            topology
  + **fencer:** apply priority-fencing-delay only to first device tried
  + **fencer:** total and per-device fencing timeouts include any
            priority-fencing-delay and `pcmk_delay_base`
  + **scheduler:** fix a number of corner cases with colocations, including
               preventing a resource from starting if it has a mandatory
               colocation with a group whose start is blocked, preventing
               optional anti-colocation from overriding infinite stickiness,
               and correctly considering a group's colocation dependents
               when the group is itself colocated with a clone
  + **scheduler:** honor as many mandatory colocations as possible before
               considering any optional ones
  + **scheduler:** ensure earlier group member starts occur after later member stops
  + **scheduler:** handle orderings with bundles more correctly
  + **scheduler:** ensure expired results never affect resource state
  + **scheduler:** handle cleaned `migrate_from` history correctly
  + **scheduler:** prevent pending monitor of one clone instance from causing
               unexpected stop of other instances
  + **scheduler:** prevent inactive clone instances from starting if probe is
               unrunnable on any node
  + **agents:** SysInfo calculates `cpu_load` correctly
  + **tools:** `cibadmin --scope` accepts status
  + **tools:** `crm_attribute -p ""` works same as `-p` when called from
    resource agent
  + **tools:** `crm_attribute` recognizes "-INFINITY" as value instead of options
  + **tools:** `crm_mon` avoids displaying recurring monitors as pending if first
           attempt fails
  + **tools:** `crm_mon` `--daemonize` shows disconnected message when CIB connection
           is lost instead of continuing to display last known state
  + **tools:** `crm_mon` avoids crash when built without curses library support
  + **tools:** `crm_mon` supports `--output-as=none` correctly
  + **tools:** `crm_resource` `--ban` or `--move` works with single-replica bundles
  + **tools:** `crm_shadow` `--commit` now works with `CIB_file`
  + **tools:** `crm_simulate` failure injection avoids crash if node name is unknown

## Public API changes since Pacemaker-2.1.5

  + **Python:** New "pacemaker" Python module (packaged as python3-pacemaker in
            RPMs built with "make rpm") contains supported public API with
            BuildOptions and ExitStatus classes
  + **libcib:** add `client_id()` method member to `cib_api_operations_t`
  + **libcib:** deprecate `cib_database`
  + **libcib:** deprecate `cib_quorum_override`
  + **libcib:** deprecate the `cib_api_operations_t:update()` method
  + **libcrmcluster:** add `pcmk_cluster_new()`
  + **libcrmcluster:** add `crm_join_nack_quiet`
  + **libcrmcluster:** add `pcmk_cluster_free()`
  + **libcrmcluster:** node argument to `send_cluster_message()` is now const
  + **libcrmcluster:** node argument to `send_cluster_text()` is now const
  + **libcrmcommon:** add `crm_time_usecs`
  + **libcrmcommon:** add `PCMK_META_ENABLED`
  + **libcrmcommon:** add `pcmk_pacemakerd_state_remote`
  + **libcrmcommon:** add `pcmk_rc_bad_xml_patch`
  + **libcrmcommon:** add `pcmk_rc_bad_input`
  + **libcrmcommon:** add `pcmk_rc_disabled`
  + **libcrmcommon:** deprecate `add_xml_nocopy()`
  + **libcrmcommon:** deprecate `log_data_element()`
  + **libcrmcommon:** deprecate `PCMK_RESOURCE_CLASS_NAGIOS`
  + **libcrmcommon:** deprecate `PCMK_RESOURCE_CLASS_UPSTART`
  + **libcrmcommon:** deprecate `XML_ATTR_UUID`
  + **libcrmcommon:** deprecate `XML_CIB_ATTR_REPLACE`
  + **libcrmcommon:** deprecate `xml_log_changes()`
  + **libcrmcommon:** deprecate `xml_log_options` enum
  + **libcrmcommon:** deprecate `xml_log_patchset()`
  + **libcrmcommon:** argument to `pcmk_xe_is_probe()` is now const
  + **libcrmcommon:** argument to `pcmk_xe_mask_probe_failure()` is now const
  + **libcrmcommon:** patchset argument of `xml_log_patchset()` is now const
  + **libcrmcommon:** `rsc_op_expected_rc()` argument is now const
  + **libcrmcommon:** second argument to `copy_in_properties()` is now const
  + **libcrmcommon:** xml argument of `xml_log_changes()` is now const
  + **libcrmservice:** deprecate enum `nagios_exitcode`
  + **libpacemaker:** add `pcmk_query_node_info()`
  + **libpacemaker:** add `pcmk_query_node_name()`
  + **libpacemaker:** multiple arguments to `pcmk_simulate()` are now const
  + **libpacemaker:** node argument to `pcmk_resource_digests()` is now const
  + **libpacemaker:** `node_types` argument to `pcmk_list_nodes()` is now const
  + **libpacemaker:** `pcmk_controller_status()` node name arg is now const
  + **libpe_rules:** last argument to `pe_expand_re_matches()` is now const
  + **libpe_rules:** `rule_data` argument to `pe_eval_nvpairs()` is now const
  + **libpe_rules:** second argument to `pe_eval_expr()` and `pe_eval_subexpr()` is now const
  + **libpe_rules:** second argument to `pe_eval_rules()` is now const
  + **libpe_rules:** second argument to `pe_unpack_nvpairs()` is now const
  + **libpe_status:** add `pe_rsc_detect_loop`
  + **libpe_status:** add `pe_rsc_replica_container`
  + **libpe_status:** deprecate fixed member of `pe_node_t`
  + **libpe_status:** argument to `pe_rsc_is_bundled()` is now const
  + **libpe_status:** argument to `rsc_printable_id()` is now const
  + **libpe_status:** first argument to `calculate_active_ops()` is now const
  + **libpe_status:** first argument to `pe_find_node()` is now const
  + **libpe_status:** first argument to `pe_find_node_any()` is now const
  + **libpe_status:** first argument to `pe_find_node_id()` is now const
  + **libpe_status:** first argument to `resource_object_functions_t:is_filtered()` is now const

# Pacemaker-2.1.5 (7 Dec 2022)
- 1287 commits with 447 files changed, 33546 insertions(+), 21518 deletions(-)

## Features added since Pacemaker-2.1.4

  + **CIB:** access control lists (ACLs) for groups are supported
  + **CIB:** ACL target and group XML supports "name" attribute to specify a name
         that is not a unique XML ID
  + **CIB:** deprecate pacemaker-next schema
  + **CIB:** deprecate first-instance and then-instance in ordering constraints
         and rsc-instance and with-rsc-instance in colocation constraints
         (only usable with pacemaker-next schema)
  + **CIB:** deprecate "collocated" and "ordered" meta-attributes for groups
         (true is default, and resource sets should be used instead of false)
  + **build:** support building with -D_TIME_BITS=64
  + **build:** support building with compilers that are strict about void
  + **build:** allow building RPMs from source distribution
  + **fencer:** deprecate stand-alone mode
  + **agents:** ClusterMon, controld, HealthCPU, ifspeed, and SysInfo agents support
            OCF 1.1 standard
  + **agents:** non-functional SystemHealth agent has been removed
  + **tools:** non-functional ipmiservicelogd and notifyServicelogEvent tools have
           been removed
  + **tools:** `crm_attribute` supports querying all attributes on a given node
  + **tools:** `crm_attribute` `--query,` --delete, and `--update` support
           regular expressions
  + **tools:** `crm_error` supports standard `--output-as/--output-to` arguments
  + **tools:** `crm_error` lists all return codes if none are specified
  + **tools:** `crm_mon` `--show-detail` displays the CRM feature set of each node
           and makes display of fencing actions more technical
  + **tools:** `crm_resource` `--why` checks node health
  + **tools:** `crm_resource` `--constraints` now accepts `--recursive` (equivalent to
           `--stack)` and `--force` (to show constraints for a group member
           instead of the group)

## Fixes since Pacemaker-2.1.4

  + **tools:** `crm_error` does not print spurious output when given a negative
           return code argument *(regression introduced in 2.0.4)*
  + **tools:** avoid crash if `crm_resource` is given extraneous arguments
           *(regression introduced in 2.0.5)*
  + **tools:** `stonith_admin` `--validate` XML output shows correct validation status
           and errors *(regressions introduced in 2.0.5 and 2.1.2)*
  + **tools:** `crm_resource` `--list-operations` shows pending operations as pending
           instead of complete *(regression introduced in 2.1.0)*
  + **controller:** move resources if appropriate after they are reordered in CIB
                *(regression introduced in 2.1.3)*
  + **fencing:** allow fence devices to be registered if local node is not in CIB
             *(regression introduced in 2.1.3)*
  + **tools:** `crm_mon` `--one-shot` should succeed even if pacemaker is shutting down
           *(regression introduced in 2.1.3)*
  + **tools:** avoid memory leak in `crm_mon` *(regression introduced in 2.1.3)*
  + **tools:** `crm_attribute` `--quiet` outputs nothing instead of "(null)" if
           attribute has no value *(regression introduced in 2.1.3)*
  + **tools:** accept deprecated and unused `attrd_updater` `--quiet` option
           *(regression introduced in 2.1.3)*
  + **CIB:** avoid crashes when XML IDs grow very long
  + **controller:** pre-load agent metadata asynchronously to avoid timeout when
                agent's metadata action runs `crm_node`
  + **controller:** avoid timing issue that increments resource fail count twice
  + **fencing:** unfence all nodes after device configuration changes
  + **fencing:** ignore node that executed action when checking whether actions
             are equivalent
  + **scheduler,controller:** calculate secure digest consistently
  + **scheduler:** consider roles when blocking colocation dependents
  + **scheduler:** prioritize group colocations properly
  + **scheduler:** properly consider effect of "with group" colocations
  + **scheduler:** handle corner cases in live migrations
  + **scheduler:** avoid perpetual moving of bundle containers in certain situations
  + **scheduler:** properly calculate resource parameter digests without history
  + **scheduler:** do not enforce stop if newer monitor indicates resource was not
               running on target of failed `migrate_to`
  + **scheduler:** do not enforce stop on rejoined node after failed `migrate_to`
  + **scheduler:** don't demote on expected node when multiple-active is set to
               `stop_unexpected`
  + **scheduler:** prevent resources running on multiple nodes after partial live
               migration
  + **scheduler:** restart resource instead of reload if extra parameters in
               operation change
  + **schemas:** Consider days, minutes, seconds, and yeardays in date expressions
             valid
  + **schemas:** Consider `in_range` with an end and duration valid
  + **schemas:** Consider score and score-attribute optional in rules
  + **tools:** `crm_resource` `--digests` uses most recent operation history entry
  + **tools:** if multiple return code options are given to `crm_error`, use the
           last one
  + **tools:** `crm_resource` correctly detects if a resource is unmanaged
           or disabled even if there are multiple settings using rules

## Public API changes since Pacemaker-2.1.4

  + **libcib:** add `cib_api_operations_t:set_primary`
  + **libcib:** add `cib_api_operations_t:set_secondary`
  + **libcib:** deprecate `cib_api_operations_t:delete_absolute()`
  + **libcib:** deprecate `cib_api_operations_t:is_master`
  + **libcib:** deprecate `cib_api_operations_t:set_master`
  + **libcib:** deprecate `cib_api_operations_t:set_slave`
  + **libcib:** deprecate `cib_api_operations_t:set_slave_all`
  + **libcrmcommon:** deprecated `XML_CIB_TAG_MASTER` constant is usable again
                  *(regression introduced in 2.1.0)*
  + **libcrmcommon:** `pcmk_ipc_api_t` supports attribute manager IPC
  + **libcrmcommon:** add `pcmk_rc_unpack_error`
  + **libcrmcommon:** add `CRM_EX_FAILED_PROMOTED`
  + **libcrmcommon:** add `CRM_EX_NONE`
  + **libcrmcommon:** add `CRM_EX_PROMOTED`
  + **libcrmcommon:** add `pcmk_readable_score()`
  + **libcrmcommon:** add `PCMK_XA_PROMOTED_MAX_LEGACY` string constant
  + **libcrmcommon:** add `PCMK_XA_PROMOTED_NODE_MAX_LEGACY` string constant
  + **libcrmcommon:** argument to `crm_time_check()` is now const
  + **libcrmcommon:** argument to `pcmk_controld_api_replies_expected()` is now const
  + **libcrmcommon:** argument to `pcmk_xml_attrs2nvpairs()` is now const
  + **libcrmcommon:** argument to `xml2list()` is now const
  + **libcrmcommon:** argument to `xml_acl_denied()` is now const
  + **libcrmcommon:** argument to `xml_acl_enabled()` is now const
  + **libcrmcommon:** argument to `xml_get_path()` is now const
  + **libcrmcommon:** arguments to `crm_time_add()` are now const
  + **libcrmcommon:** arguments to `crm_time_compare()` are now const
  + **libcrmcommon:** arguments to `crm_time_subtract()` are now const
  + **libcrmcommon:** argv argument to `crm_log_preinit()` is now char *const *
  + **libcrmcommon:** `crm_time_calculate_duration()` arguments are now const
  + **libcrmcommon:** deprecate `CRM_ATTR_RA_VERSION`
  + **libcrmcommon:** deprecate `crm_destroy_xml()`
  + **libcrmcommon:** deprecate `crm_ipc_server_error`
  + **libcrmcommon:** deprecate `crm_ipc_server_info`
  + **libcrmcommon:** deprecate `CRM_OP_LRM_QUERY`
  + **libcrmcommon:** deprecate `crm_str()`
  + **libcrmcommon:** deprecate `PCMK_XE_PROMOTED_MAX_LEGACY` string constant
  + **libcrmcommon:** deprecate `PCMK_XE_PROMOTED_NODE_MAX_LEGACY` constant
  + **libcrmcommon:** deprecate `score2char()`
  + **libcrmcommon:** deprecate `score2char_stack()`
  + **libcrmcommon:** deprecate `XML_ATTR_RA_VERSION`
  + **libcrmcommon:** deprecate `xml_get_path()`
  + **libcrmcommon:** deprecate `XML_PARANOIA_CHECKS`
  + **libcrmcommon:** deprecate `XML_TAG_OP_VER_ATTRS`
  + **libcrmcommon:** deprecate `XML_TAG_OP_VER_META`
  + **libcrmcommon:** deprecate `XML_TAG_RSC_VER_ATTRS`
  + **libcrmcommon:** dt argument of `crm_time_get_gregorian()` is now const
  + **libcrmcommon:** dt argument of `crm_time_get_isoweek()` is now const
  + **libcrmcommon:** dt argument of `crm_time_get_ordinal()` is now const
  + **libcrmcommon:** dt argument of `crm_time_get_timeofday()` is now const
  + **libcrmcommon:** dt argument of `crm_time_get_timezone()` is now const
  + **libcrmcommon:** first argument to `create_reply()` is now const
  + **libcrmcommon:** first argument to `crm_copy_xml_element()` is now const
  + **libcrmcommon:** first argument to `find_xml_node()` is now const
  + **libcrmcommon:** first argument to `get_message_xml()` is now const
  + **libcrmcommon:** first argument to `pcmk_ipc_name()` is now const
  + **libcrmcommon:** first argument to `xml_patch_versions()` is now const
  + **libcrmcommon:** last argument to `crm_write_blackbox()` is now const
  + **libcrmcommon:** add `pcmk_rc_duplicate_id`
  + **libcrmcommon:** add `pcmk_result_get_strings()`
  + **libcrmcommon:** add `pcmk_result_type` enum
  + **libcrmcommon:** add `PCMK_XE_DATE_EXPRESSION` constant
  + **libcrmcommon:** add `PCMK_XE_OP_EXPRESSION` constant
  + **libcrmcommon:** add `PCMK_XE_RSC_EXPRESSION` constant
  + **libcrmcommon:** first argument to `crm_time_as_string()` is now const
  + **libcrmcommon:** `crm_time_t` argument to `crm_time_log_alias()` is now const
  + **libcrmcommon:** argument to `crm_time_get_seconds()` is now const
  + **libcrmcommon:** argument to `crm_time_get_seconds_since_epoch()` is now const
  + **libcrmcommon:** sixth argument to `log_data_element()` is now const
  + **libcrmcommon:** source argument to `crm_time_set()` is now const
  + **libcrmcommon:** source argument to `crm_time_set_timet()` is now const
  + **libcrmcommon:** source argument to `pcmk_copy_time()` is now const
  + **libpacemaker:** add `pcmk_check_rule()`
  + **libpacemaker:** add `pcmk_check_rules()`
  + **libpacemaker:** add `pcmk_show_result_code()`
  + **libpacemaker:** add `pcmk_list_result_codes()`
  + **libpacemaker:** add `pcmk_rc_disp_flags` enum
  + **libpacemaker:** `ipc_name` argument to `pcmk_pacemakerd_status()` is now const
  + **libpe_rules:** deprecate `version_expr` enum value
  + **libpe_rules:** second argument to `pe_eval_nvpairs()` is now const
  + **libpe_status:** argument to `pe_rsc_is_anon_clone()` is now const
  + **libpe_status:** argument to `pe_rsc_is_unique_clone()` is now const
  + **libpe_status:** deprecate enum `pe_graph_flags`
  + **libpe_status:** first argument to `pe_rsc_is_clone()` is now const
  + **libpe_status:** two arguments to `get_rsc_attributes()` are now const
  + **libpe_status:** second argument to `pe_eval_versioned_attributes()` is now const
  + **libpe_status:** second argument to `pe_rsc_params()` is now const
  + **libstonithd:** deprecate `stonith_event_t:message`
  + **libstonithd:** deprecate `stonith_event_t:type`
  + **libstonithd:** last argument to `stonith_api_operations_t:register_device()`
                 is now const
  + **libstonithd:** last argument to `stonith_api_operations_t:register_level()` is
                 now const
  + **libstonithd:** last argument to
                 `stonith_api_operations_t:register_level_full()` is now const
  + **libstonithd:** params argument to `stonith_api_operations_t:validate()` is now
                 const

# Pacemaker-2.1.4 (13 Jun 2022)
- 17 commits with 9 files changed, 52 insertions(+), 18 deletions(-)

## Fixes since Pacemaker-2.1.3

  + **fencing:** get target-by-attribute working again *(regression in 2.1.3)*
  + **fencing:** avoid use-after-free when processing self-fencing requests
             with topology *(regression in 2.1.3)*
  + **resources:** typo in HealthSMART meta-data *(regression in 2.1.3)*
  + **fencing:** avoid memory leaks when processing topology requests
  + **fencing:** delegate shouldn't matter when checking equivalent fencing
  + **tools:** fix CSS syntax error in `crm_mon --output-as=html`

# Pacemaker-2.1.3 (1 Jun 2022)
- 814 commits with 332 files changed, 23435 insertions(+), 12137 deletions(-)

## Features added since Pacemaker-2.1.2

  + Internal failures of resource actions (such as an OCF agent not being
    found) are shown with a detailed exit reason in logs, `crm_mon` output, etc.
  + Support for CIB <node> entries with type="ping" is deprecated (this was an
    undocumented means of defining a quorum-only node)
  + **build:** configure script supports experimental `--enable-nls` option to
           enable native language translations (currently only Chinese
           translations of certain help text are available)
  + **rpm:** `crm_attribute` is now part of the pacemaker-cli package instead of
         the pacemaker package
  + **CIB:** resources support allow-unhealthy-nodes meta-attribute to exempt
         the resource from bans due to node health checks (particularly useful
         for health monitoring resources themselves)
  + **CIB:** multiple-active cluster property can be set to "stop_unexpected" to
         leave the expected instance running and stop only any unexpected ones
  + **CIB:** bundles support resource utilization
  + **pacemakerd:** regularly check that subdaemons are active and accepting IPC
                connections so sbd can self-fence a node with a malfunctioning
                subdaemon
  + **pacemaker-schedulerd:** support `--output-as/--output-to` options including
                          XML output with interactive options
  + **tools:** cibadmin `--show-access` option to show CIB colorized for ACLs
  + **tools:** `crm_attribute` supports standard `--output-as/--output-to` options
  + **tools:** `crm_mon` output indicates if a node's health is yellow or red
  + **tools:** for probes that failed because the service is not installed or
           locally configured, `crm_mon` displays the resource as stopped rather
           than failed
  + **tools:** `crm_rule` supports standard `--output-as/--output-to` options,
           allows passing multiple -r options, and is no longer experimental
  + **tools:** `stonith_admin` fencing commands display reasons for failures
  + **resource agents:** HealthSMART supports OCF 1.1 standard and new
                     `OCF_RESKEY_dampen` and `OCF_RESKEY_smartctl` parameters

## Fixes since Pacemaker-2.1.2

  + **build:** avoid circular library dependency *(regression introduced in 2.1.0)*
  + **systemd:** if pacemakerd exits immediately after starting, wait 1 second
             before trying to respawn, and allow 5 attempts
  + **fencer:** get fencing completion time correctly
            *(regression introduced in 2.1.2)*
  + **fencer:** avoid memory leak when broadcasting history differences
            *(regression introduced in 2.1.0)*
  + **controller:** correctly match "node down" events so remote nodes don't get
                fenced when connection is stopped
                *(regression introduced in 2.1.2)*
  + **executor:** avoid possible double free during notify operation
              *(regression introduced in 2.1.1)*
  + **tools:** get `stonith_admin` -T/--tag option working again
           *(regression introduced in 2.0.3)*
  + **resources:** use correct syntax in Stateful meta-data
               *(regression introduced in 2.1.0)*
  + **corosync:** repeat `corosync_cfg_trackstart` if first attempt fails
  + **libcrmcommon:** retry IPC requests after EAGAIN errors
  + **executor,scheduler:** treat "no secrets" fence results as a hard error
  + **fencing:** handle dynamic target query failures better
  + **fencing:** don't set stonith action to pending if fork fails
  + **pacemakerd:** avoid race condition when subdaemaon is checked while exiting
  + **scheduler:** avoid memory leak when displaying clones in certain conditions
  + **scheduler:** properly set data set flags when scheduling actions
  + **tools:** support command-line `crm_attribute` calls on Pacemaker remote nodes
           whose node name in the cluster differs from their local hostname
  + **tools:** prevent possible `crm_resource` crashes if multiple commands specified

## Public API changes since Pacemaker-2.1.2

  + **libcrmcommon:** `pcmk_ipc_api_t` supports scheduler IPC
  + **libpacemaker:** add `pcmk_status()` (equivalent to `crm_mon)`
  + **libcib:** deprecate `get_object_parent()`
  + **libcib:** deprecate `get_object_path()`
  + **libcib:** deprecate `get_object_root()`
  + **libcrmcommon:** add `pcmk_cib_parent_name_for()`
  + **libcrmcommon:** add `pcmk_cib_xpath_for()`
  + **libcrmcommon:** add `pcmk_find_cib_element()`
  + **libcrmcommon:** deprecate `crm_xml_add_boolean()`
  + **libpe_status:** add `pe_flag_check_config`
  + **libpe_status:** add `pe_node_shared_s:data_set`
  + **libpe_status:** add `pe_rsc_restarting` flag
  + **libpe_status:** add `pe_rsc_stop_unexpected` flag
  + **libpe_status:** add `recovery_stop_unexpected` to enum `rsc_recovery_type`
  + **libpe_status:** deprecate `node_ping`
  + **libpe_status:** deprecate `pe_order_stonith_stop`
  + **libpe_status:** deprecate `pe_rsc_starting` and `pe_rsc_stopping`
  + **libstonithd:** add `exit_reason` member to `stonith_history_t`
  + **libstonithd:** deprecate `stonith_t:call_timeout`
  + **libstonithd:** `stonith_api_del_notification()` with NULL second argument
                 removes all notifications

# Pacemaker-2.1.2 (23 Nov 2021)
- 462 commits with 223 files changed, 16518 insertions(+), 11743 deletions(-)

## Features added since Pacemaker-2.1.1

  + **build:** when built with `--with-initdir,` Pacemaker uses the value to find
           LSB resources (in addition to being where Pacemaker's own
           init scripts are installed)
  + **build:** cmocka is new dependency for unit tests ("make check")
  + **rpm:** `fence_watchdog` now comes with pacemaker package (not pacemaker-cli)
  + **daemons:** metadata for cluster options supports OCF 1.1 standard
  + **executor:** nagios warning results now map to OCF "degraded" result code
  + **fencing:** `pcmk_delay_base` can optionally specify different delays per node
  + **fencing:** `pcmk_host_map` supports escaped characters such as spaces in values
  + **resources:** HealthIOWait agent supports OCF 1.1 standard, and validate works
  + **tools:** `crm_mon` shows exit reasons for actions failed due to internal errors
  + **tools:** `crm_mon` failed action display is more human-friendly by default
  + **tools:** `crm_resource` `--force-*` now outputs exit reasons if available

## Fixes since Pacemaker-2.1.1

  + **pkg-config:** return correct value for ocfdir *(regression introduced in 2.1.0)*
  + **tools:** fix `crm_mon` `--hide-headers` and related options
           *(regression introduced in 2.0.4)*
  + **attrd:** check election status upon node loss to avoid election timeout
  + **controller:** improved handling of executor connection failures
  + **executor:** properly detect systemd unit existence
  + **pacemakerd:** recover properly from Corosync crash
  + **fencing:** fencing results are now sorted with sub-second resolution
  + **fencing:** fix `fence_watchdog` version output, metadata output, and man page
  + **fencing:** mark state as done if remapped "on" times out
  + **tools:** map LSB status to OCF correctly with `crm_resource` --force-check

## Public API changes since Pacemaker-2.1.1

  + **libcrmcommon:** deprecate `PCMK_OCF_EXEC_ERROR`
  + **libcrmcommon:** deprecate `PCMK_OCF_PENDING`
  + **libcrmcommon:** deprecate `PCMK_OCF_SIGNAL`
  + **libcrmcommon:** add `CRM_EX_DEGRADED` and `CRM_EX_DEGRADED_PROMOTED`
  + **libcrmcommon:** add enum `pcmk_exec_status`
  + **libcrmcommon:** add `PCMK_EXEC_MAX`
  + **libcrmcommon:** add `PCMK_EXEC_NO_FENCE_DEVICE`
  + **libcrmcommon:** add `PCMK_EXEC_NO_SECRETS`
  + **libcrmcommon:** add `pcmk_exec_status_str()`
  + **libcrmcommon:** add `pcmk_rc2ocf()`
  + **libcrmcommon:** deprecate `PCMK_OCF_TIMEOUT`
  + **libcrmservice:** add `services_result2ocf()`
  + **libcrmservice:** deprecate enum `op_status`
  + **libcrmservice:** deprecate `LSB_ROOT_DIR`
  + **libcrmservice:** deprecate `NAGIOS_NOT_INSTALLED`
  + **libcrmservice:** deprecate `NAGIOS_STATE_DEPENDENT`
  + **libcrmservice:** deprecate `services_get_ocf_exitcode()`
  + **libcrmservice:** deprecate `services_list()` and `services_action_create()`
  + **libcrmservice:** deprecate `services_lrm_status_str()`
  + **libpacemaker:** add enum `pcmk_sim_flags`
  + **libpacemaker:** add `pcmk_injections_t`
  + **libpacemaker:** add `pcmk_free_injections()`
  + **libpacemaker:** add `pcmk_simulate()`
  + **libstonithd:** add opaque member to `stonith_event_t`
  + **libstonithd:** add opaque member to `stonith_callback_data_t`

# Pacemaker-2.1.1 (09 Sep 2021)
- 231 commits with 102 files changed, 4912 insertions(+), 3428 deletions(-)

## Features added since Pacemaker-2.1.0

  + enhanced support for OCF Resource Agent API 1.1 standard
    + **agents:** ocf:pacemaker:attribute and ocf:pacemaker:ping agents now
      support 1.1
    + **tools:** `crm_resource` passes output format to agents so they will use it if
      supported
    + **tools:** `crm_resource` `--validate` and `--force-check` options accept optional
      check level to pass to agent
  + **tools:** `crm_mon` XML output includes stonith-timeout-ms and
    priority-fencing-delay-ms cluster properties
  + **pacemakerd:** support `--output-as/--output-to` options including XML output
    with interactive options such as --features

## Fixes since Pacemaker-2.1.0

  + **pacemaker-attrd:** avoid repeated unfencing of remote nodes when DC
    joined cluster after remote was up
  + **controller:** ensure newly joining node learns the node names of non-DCs
  + **controller:** ensure lost node's transient attributes are cleared without
    DC
  + **scheduler:** avoid invalid transition when group member is unmanaged
    (CLBZ#5423)
  + **scheduler:** don't schedule probes of unmanaged resources on pending
    nodes
  + **executor:** avoid crash after TLS connection errors
    *(regression introduced in 2.0.4)*
  + **fencing:** avoid repeated attempts to get (nonexistent) meta-data for
    watchdog device *(regression introduced in 2.1.0)*
  + **fencing:** select correct device when `pcmk_host_check="dynamic-list"`
    and `pcmk_host_map` are both specified (CLBZ#5474)
  + **tools:** `crm_attribute` supports node attribute values starting with a
    '-' again *(regression introduced in 2.1.0)*
  + **tools:** `crm_attribute` deprecated `--get-value` option does not require
    an argument *(regression introduced in 2.1.0)*
  + **tools:** avoid `crm_mon` memory leaks when filtering by resource or node
    *(regressions introduced in 2.0.4 and 2.0.5)*
  + **tools:** exit with status 0 (not 64) for `--version` argument to
    `crm_rule`, `crm_error`, `crm_diff`, and `crm_node` *(regression introduced
    in 2.0.4)* and `crm_attribute` *(regression introduced in 2.1.0)*
  + **tools:** `crm_mon` should show active unmanaged resources on offline
    nodes without requiring `-r/--inactive`
  + **tools:** better `crm_resource` error messages for unsupported resource
    types
  + **tools:** `crm_simulate` `--show-failcounts` includes all relevant
    information
  + **tools:** `crm_mon` should not show inactive group members without
    `--inactive`
  + **tools:** `crm_mon` XML output should show members of cloned groups
  + **libcrmcommon:** correctly handle case-sensitive XML IDs

## Public API changes since Pacemaker-2.1.0

  + **libcrmcommon:** add `pcmk_section_e` type
  + **libcrmcommon:** add `pcmk_show_opt_e` type
  + **libcrmcommon:** add `pcmk_pacemakerd_api_shutdown()`
  + **libpe_status:** deprecate enum `pe_print_options`

# Pacemaker-2.1.0 (08 Jun 2021)
- 849 commits with 327 files changed, 22089 insertions(+), 12633 deletions(-)

## Features added since Pacemaker-2.0.5

  + support for OCF Resource Agent API 1.1 standard
    - allow Promoted and Unpromoted role names in CIB (in addition to Master
      and Slave, which are deprecated), and use new role names in output,
      logs, and constraints created by `crm_resource --ban`
    - advertise 1.1 support to agents, and provide `notify_promoted_*` and
      `notify_unpromoted_*` environment variables to agents with notify actions
    - support `reloadable` parameter attribute and `reload-agent` action in
      agents that advertise 1.1 support
    - support 1.1 standard in ocf:pacemaker:Dummy, ocf:pacemaker:remote, and
      ocf:pacemaker:Stateful resource agents
    - add "promoted-only" (in addition to "master-only", which is deprecated)
      in `crm_mon` XML output for bans
  + support for noncritical resources
    - colocation constraints accept an "influence" attribute that determines
      whether dependent influences main resource's location (the default of
      "true" preserves the previous behavior, while "false" makes the
      dependent stop if it reaches its migration-threshold in failures rather
      than cause both resources to move to another node)
    - resources accept a "critical" meta-attribute that serves as default for
      all colocation constraints involving the resource as the dependent, as
      well as groups involving the resource
  + detail log uses millisecond-resolution timestamps when Pacemaker is built
    with libqb 2.0 or later
  + **CIB:** deprecate the remove-after-stop cluster property, `can_fail` action
    meta-attribute, and support for Upstart-based resources
  + **controller:** the `PCMK_panic_action` environment variable may be set to
    sync-crash or sync-reboot to attempt to synchronize local
    disks before crashing or rebooting, which can be helpful to
    record cached log messages but runs the risk of the sync
    hanging and leaving the host running after a critical error
  + **tools:** `CIB_file="-"` can be used to get the CIB from standard input
  + **tools:** crmadmin, `crm_resource`, `crm_simulate`, and `crm_verify` support
    standard `--output-as/--output-to` options (including XML output,
    intended for parsing by scripts and higher-level tools)
  + **tools:** `crm_attribute` accepts `-p/--promotion` option to operate on
    promotion score (replacing `crm_master`, which is deprecated)
  + **tools:** `crm_resource` accepts `--promoted` option (replacing `--master,` which
    is deprecated)
  + **tools:** `crm_resource` accepts `--digests` advanced option
  + **tools:** `crm_simulate` accepts `--show-attrs` and `--show-failcounts` options

- Build process changes since Pacemaker-2.0.5
  + Pacemaker requires newer versions of certain dependencies, including
    Python 3.2 or later (support for Python 2 has been dropped), glib 2.32.0
    or later, libqb 0.17.0 or later, GnuTLS 2.12.0 or later (to enable
    Pacemaker Remote support), rpm 4.11.0 (if building RPMs), and a C library
    that provides setenv() and unsetenv()
  + **configure:** `--enable-legacy-links` (which is deprecated) defaults to
    "no", meaning that symbolic links will not be created for the Pacemaker 1
    daemon names
  + **configure:** `--enable-compat-2.0` prevents certain output changes (most
    significantly role names) to maintain compatibility with older tools,
    scripts, and resource agents that rely on previous output
  + **configure:** `--with-resource-stickiness-default` sets a
    `resource-stickiness` default in newly created CIBs
  + **configure:** `--with-concurrent-fencing-default` specifies default for
    `concurrent-fencing` cluster property
  + **configure:** `--with-sbd-sync-default` specifies default for syncing
    start-up with sbd
  + **configure:** `--with-ocfrapath` specifies resource agent directories to
    search
  + **configure:** `--with-ocfrainstalldir` specifies where to install
    ocf:pacemaker agents
  + **configure:** `--with-gnutls="no"` explicitly disables support for
    Pacemaker Remote and the `remote-tls-port` cluster property
  + **configure:** `--with-acl` has been removed (support for ACLs is always
    built)
  + **configure:** deprecated `--with-pkgname,` `--with-pkg-name`,
    `--with-brand`, `--enable-ansi,` and `--enable-no-stack` options have been
    removed
  + environment variables file (typically /etc/sysconfig/pacemaker or
    /etc/default/pacemaker) will be installed when `make install` is run
  + documentation has dependency on python3-sphinx instead of publican, and is
    generated beneath doc/sphinx

## Fixes since Pacemaker-2.0.5

  + **controller:** always refresh agent meta-data after start, in case agent was
    updated *(regression introduced in 1.1.18)*
  + **tools:** avoid crash when running `crm_mon` in daemonized mode with CGI output
    *(regression introduced in 2.0.3)*
  + **tools:** correctly treat unspecified node as all nodes instead of local node
    when `attrd_updater` `--query` or `crm_resource` `--cleanup` is run on a
    Pacemaker Remote node *(regressions introduced in 1.1.14 and 1.1.17)*
  + **tools:** exit with status 0 (not 64) for `--version` argument to `crm_simulate`
    *(regression introduced in 2.0.4)* and `crm_resource` and crmadmin
    *(regression introduced in 2.0.5)*
  + **pacemaker-attrd:** avoid race condition where transient attributes for a
    leaving node could be reinstated when the node rejoins,
    potentially causing a node that was just rebooted to exit
    the cluster immediately after rejoining
  + **controller,scheduler:** fix year 2038 issues affecting shutdowns,
    remote node fencing, last-rc-change, and
    ticket last-granted dates
  + **controller:** retry scheduler connection after failure, to avoid cluster
    stopping on a node without stopping resources (clbz#5445)
  + **fencing:** avoid pending fencing entry getting "stuck" in history if
    originating node was unreachable when result was received
  + **fencing:** retry getting agent meta-data if initial attempt fails
  + **fencing:** detect when devices have been removed from configuration
  + **scheduler:** constrain clone-min, clone-max, clone-node-max, promoted-max,
    and promoted-node-max options to non-negative values
  + **scheduler:** constrain resource priorities and node-health-base to score range
  + **scheduler:** treat invalid duration fields in time-based rules as 0, not -1
  + **scheduler:** node attribute rule expressions with a value-source of "param"
    or "meta" work when rsc or rsc-pattern with an inverted match
    is given, as well as when rsc-pattern with a regular
    match is given
  + **scheduler:** node attribute rule expressions with a value-source of "param"
    work with a resource parameter that itself is determined by a
    node attribute rule expression
  + **scheduler:** avoid remote connection shutdown hanging when connection
    history for node hosting connection is not last in CIB status
  + **scheduler:** route monitor cancellations behind moving remote connections correctly
  + **libcrmcommon:** avoid potential integer overflow when adding seconds to times
  + **tools:** cibsecret syncs to remote nodes and guest nodes as well as
    cluster nodes
  + **tools:** show other available cluster information in `crm_mon` even if
    fence history is not available
  + **tools:** retry failed fencer and CIB connections in `crm_mon`
  + **tools:** `crm_mon` reports if Pacemaker is waiting for sbd at start-up
  + **tools:** respect rules when showing node attributes in `crm_mon`
  + **tools:** improve messages when `crm_mon` is run on disconnected remote node
  + **tools:** constrain node IDs to non-negative values for `crm_node -N`
  + **tools:** `crm_node` -l on restarted node works even when Corosync 2 is used
    without node names specified in Corosync configuration
  + **tools:** fix issues in calculation of non-sensitive resource parameter
    digests that made `crm_simulate` wrongly think configuration changed

- C API changes since Pacemaker-2.0.5
  + **all:** new `PCMK_ALLOW_DEPRECATED` constant controls API availability
  + **libcrmcluster:** deprecate `crm_terminate_member()`
  + **libcrmcluster:** deprecate `crm_terminate_member_no_mainloop()`
  + **libcrmcommon:** add `CRMD_ACTION_RELOAD_AGENT` string constant
  + **libcrmcommon:** add `PCMK_OCF_MAJOR_VERSION` string constant
  + **libcrmcommon:** add `PCMK_OCF_MINOR_VERSION` string constant
  + **libcrmcommon:** add `PCMK_OCF_RUNNING_PROMOTED` enum value
  + **libcrmcommon:** add `PCMK_OCF_VERSION` string constant
  + **libcrmcommon:** add `PCMK_XE_PROMOTABLE_LEGACY` string constant
  + **libcrmcommon:** add `PCMK_XE_PROMOTED_MAX_LEGACY` string constant
  + **libcrmcommon:** add `PCMK_XE_PROMOTED_NODE_MAX_LEGACY` string constant
  + **libcrmcommon:** add enum `ocf_exitcode` (moved from libcrmservice)
  + **libcrmcommon:** deprecate `__builtin_expect()`
  + **libcrmcommon:** deprecate `__likely()`
  + **libcrmcommon:** deprecate `__unlikely()`
  + **libcrmcommon:** deprecate `crm_atoi()`
  + **libcrmcommon:** deprecate `crm_build_path()`
  + **libcrmcommon:** deprecate `crm_config_error` global variable
  + **libcrmcommon:** deprecate `crm_config_warning` global variable
  + **libcrmcommon:** deprecate `crm_ftoa()`
  + **libcrmcommon:** deprecate `crm_hash_table_size()`
  + **libcrmcommon:** deprecate `crm_itoa()`
  + **libcrmcommon:** deprecate `crm_itoa_stack()`
  + **libcrmcommon:** deprecate `crm_log_cli_init()`
  + **libcrmcommon:** deprecate `crm_parse_int()`
  + **libcrmcommon:** deprecate `crm_parse_ll()`
  + **libcrmcommon:** deprecate `crm_str_hash()`
  + **libcrmcommon:** deprecate `crm_str_table_dup()`
  + **libcrmcommon:** deprecate `crm_str_table_new()`
  + **libcrmcommon:** deprecate `crm_strcase_equal()`
  + **libcrmcommon:** deprecate `crm_strcase_hash()`
  + **libcrmcommon:** deprecate `crm_strcase_table_new()`
  + **libcrmcommon:** deprecate `crm_strip_trailing_newline()`
  + **libcrmcommon:** deprecate `crm_ttoa()`
  + **libcrmcommon:** deprecate `EOS` constant
  + **libcrmcommon:** deprecate `GListPtr` type
  + **libcrmcommon:** deprecate `g_str_hash_traditional()`
  + **libcrmcommon:** deprecate `MAX_IPC_DELAY` constant
  + **libcrmcommon:** deprecate `pcmk_format_named_time()`
  + **libcrmcommon:** deprecate `pcmk_format_nvpair()`
  + **libcrmcommon:** deprecate `pcmk_numeric_strcasecmp()`
  + **libcrmcommon:** deprecate `PCMK_OCF_DEGRADED_MASTER` enum value
  + **libcrmcommon:** deprecate `PCMK_OCF_FAILED_MASTER` enum value
  + **libcrmcommon:** deprecate `PCMK_OCF_RUNNING_MASTER` enum value
  + **libcrmcommon:** deprecate `pcmk_scan_nvpair()`
  + **libcrmcommon:** deprecate `XML_CIB_TAG_MASTER` string constant
  + **libcrmcommon:** deprecate `XML_RSC_ATTR_MASTER_MAX` string constant
  + **libcrmcommon:** deprecate `XML_RSC_ATTR_MASTER_NODEMAX` string constant
  + **libcrmservice:** enum `ocf_exitcode` is obtained from libcrmcommon
  + **libpacemaker:** add `pcmk_controller_status()` function
  + **libpacemaker:** add `pcmk_designated_controller()` function
  + **libpacemaker:** add `pcmk_list_nodes()` function
  + **libpacemaker:** add `pcmk_pacemakerd_status()` function
  + **libpacemaker:** add `pcmk_resource_digests()` function
  + **libpe_status:** add `parameter_cache` member to `pe_resource_t`
  + **libpe_status:** add `pe_order_promoted_implies_first` enum value
  + **libpe_status:** add `pe_rsc_params()`
  + **libpe_status:** add `RSC_ROLE_PROMOTED` enum value
  + **libpe_status:** add `RSC_ROLE_PROMOTED_LEGACY_S` string constant
  + **libpe_status:** add `RSC_ROLE_PROMOTED_S` string constant
  + **libpe_status:** add `RSC_ROLE_UNPROMOTED` enum value
  + **libpe_status:** add `RSC_ROLE_UNPROMOTED_LEGACY_S` string constant
  + **libpe_status:** add `RSC_ROLE_UNPROMOTED_S` string constant
  + **libpe_status:** add priv member to `pcmk_working_set_t`, for Pacemaker use only
  + **libpe_status:** deprecate `pe_order_implies_first_master` enum value
  + **libpe_status:** deprecate `pe_print_details` enum value
  + **libpe_status:** deprecate `pe_print_dev` enum value
  + **libpe_status:** deprecate `pe_print_html` enum value
  + **libpe_status:** deprecate `pe_print_log` enum value
  + **libpe_status:** deprecate `pe_print_max_details` enum value
  + **libpe_status:** deprecate `pe_print_ncurses` enum value
  + **libpe_status:** deprecate `pe_print_xml` enum value
  + **libpe_status:** deprecate `pe_resource_t` parameters member
  + **libpe_status:** deprecate `RSC_ROLE_MASTER` enum value
  + **libpe_status:** deprecate `RSC_ROLE_MASTER_S` string constant
  + **libpe_status:** deprecate `RSC_ROLE_SLAVE` enum value
  + **libpe_status:** deprecate `RSC_ROLE_SLAVE_S` string constant
  + **libpe_status:** ignore `->parameter()` resource object function's create
    argument

# Pacemaker-2.0.5 (02 Dec 2020)
- 534 commits with 286 files changed, 23133 insertions(+), 14626 deletions(-)

## Features added since Pacemaker-2.0.4

  + **configuration:** Add type="integer" to rule elements, allowing for
                   specifying 64-bit integers and specifying
                   double-precision floating point numbers when
                   type="number".
  + **daemons:** Recognize new OCF agent status codes 190 (degraded) and 191
             (degraded master) to be treated as success but displayed as
             errors.
  + **sbd-integration:** support `SBD_SYNC_RESOURCE_STARTUP` environment
                     variable to better synchronize Pacemaker start-up
                     and shutdown with SBD
  + **scheduler:** Add rule-based tests to `op_defaults` and `rsc_defaults.`
  + **scheduler:** Add on-fail=demote and no-quorum-policy=demote recovery
               policies for promoted resources.
  + **tools:** Add `--resource=` to filter `crm_mon` output for a resource.
  + **tools:** Add -P to crmadmin to show pacemakerd status.
  + **tools:** In cibsecret, read value to set from input (or stdin) if not specified.

## Fixes for regressions introduced in Pacemaker-2.0.4

  + **tools:** Add the node name back to bundle instances in `crm_mon.`
  + **tools:** get `stonith_admin` `--list-targets` working again

## Fixes for regressions introduced in Pacemaker-2.0.3

  + **tools:** Fix adding HTTP headers to `crm_mon` in daemon mode.
  + **tools:** Show expected score of ping attributes in `crm_mon` XML output

## Fixes for regressions introduced in Pacemaker-2.0.1

  + **scheduler:** require pre-/post-start notifications correctly.

## Changes since Pacemaker-2.0.4

  + Prevent the bypassing of ACLs by direct IPC (CVE-2020-25654)
  + **build:** Fix a build issue on Fedora s390x.
  + **build:** Fix python2 vs. python3 packaging problems on openSUSE Tumbleweed
  + **build:** Update pkgconfig files for CI testing
  + **controller:** avoid recovery delay when shutdown locks expire
  + **controller:** Log correct timeout for timed-out stonith monitor
  + **fencer:** avoid infinite loop if device is removed during operation
  + **fencer:** avoid possible use-of-NULL when parsing metadata
  + **libfencing:** add `port` or `plug` parameter according to metadata on
    `validate` if no `pcmk_host_argument` specified
  + **libfencing:** respect `pcmk_host_argument=none` on `validate`
  + **scheduler:** disallow on-fail=stop for stop operations
  + **scheduler:** don't schedule a dangling migration stop if one already occurred
  + **scheduler:** don't select instance to be promoted on a guest that can't run
  + **scheduler:** fix build when `DEFAULT_CONCURRENT_FENCING_TRUE` is set
  + **scheduler:** Remove `pe_print_expanded_xml` print option.
  + **scheduler:** Use `pcmk_monitor_timeout` as stonith start timeout
  + **tools:** Add management status to `crm_mon`'s group output.
  + **tools:** Add "No active resources" to one case in `crm_mon` output.
  + **tools:** Allow tags and alerts in `cibadmin --scope`
  + **tools:** Avoid `crm_node` on Pacemaker Remote nodes failing when other
    executor actions are occurring.
  + **tools:** Avoid pending fence actions getting stuck in `crm_mon` display
  + **tools:** "Connectivity is lost" may not be displayed even if the ping
    communication is lost.
  + **tools:** Display stop-all-resources in `crm_mon's` cluster options.
  + **tools:** don't use pssh -q option in cibsecret unless supported
  + **tools:** Fix adding the http-equiv header to `crm_mon` in daemon mode.
  + **tools:** If a clone or group is disabled, display that in `crm_mon` as part
    of the resource's header.
  + **tools:** `crm_node` -l and -p now work from Pacemaker Remote nodes
  + **tools:** Don't display `crm_resource` error messages twice.
  + **tools:** Print inactive resources by default with `crm_mon` xml output.
  + **tools:** properly detect local node name in cibsecret
  + **tools:** Revert some `crm_resource` string-related checks on variables
    that aren't strings
  + **tools:** Use bash in cibsecret
  + **xml:** Mark new `crm_mon` attributes as optional in schema

# Pacemaker-2.0.4 (15 Jun 2020)
- 515 commits with 269 files changed, 22560 insertions(+), 13726 deletions(-)

## Features added since Pacemaker-2.0.3

  + **build:** Add support for glib-based unit tests.
  + **controller:** add new feature 'shutdown-locks'
        Optionally allow a gracefully shutdown node to have the resources
        locked to it for a configurable time.
        So that it can be restarted with exactly the same resources
        running as before.
  + **controller/fencing/scheduler:** add new feature 'priority-fencing-delay'
        Optionally derive the priority of a node from the resource-priorities
        of the resources it is running.
        In a fencing-race the node with the highest priority has a certain
        advantage over the others as fencing requests for that node are
        executed with an additional delay.
        controlled via cluster option priority-fencing-delay (default = 0)
  + **tools:** `stonith_admin`: add `--delay` option (default = 0) to support enforced
                   fencing delay
  + **tools:** Add `--include=` and `--exclude=` to `crm_mon.`
  + **tools:** Add `--node=` to filter `crm_mon` output for a node (or tag).
  + **tools:** Allow more fine grained filtering of fence-history in `crm_mon.`
  + **tools:** Allow `crm_rule` to check some `date_specs.`

## Fixes for regressions introduced in Pacemaker-2.0.0

  + **tools:** ensure that getting the local node name using `crm_node`
           always works from Pacemaker Remote node command line

## Changes since Pacemaker-2.0.3

  + **build:** improve checking headers for C++ fitness
  + **build:** restore build on latest OpenSUSE
  + **fencing:** Report an error getting history in output instead of empty history
  + **fencing:** Improve parameter handling for RHCS-style fence-agents
                 - make parameter `action` shown as not required
                 - add `port` or `plug` parameter according to metadata
                 - `plug` parameter shown as non-required in the metadata
  + **controller:** clear leaving node's transient attributes even if there is no DC
  + **controller:** don't ack same request twice
  + **iso8601:** Fix `crm_time_parse_offset()` to parse offset with plus sign.
  + **libcrmcommon, libpe:** validate interval specs correctly
  + **libcrmcommon:** Add `pcmk_str_is_infinity`, `pcmk_str_is_minus_infinity` and
                  `pcmk__unregister_formats.`
  + **libcrmcommon:** Extend what `pcmk__split_range` can do.
  + **libfencing:** Export formatted output functions.
  + **libpe_status:** Add node list arg to output messages preventing weird
                  behavior + potential segfaults
  + **libpe_status:** Update the maint mode message for HTML output.
  + **fencing, tools:** Fix arguments to stonith-event.
  + **scheduler:** don't incorporate dependencies' colocations multiple times
  + **scheduler:** ensure attenuated scores still have some effect
  + **scheduler:** ignore colocation constraints with 0 score
  + **scheduler:** make sure cluster-wide maintenance-mode=true overrides
               per-resource settings
  + **scheduler:** properly detect whether guest node is fenceable
  + **scheduler:** do not differentiate case where all the nodes have equal priority
  + **tests:** Add tests for `pe_cron_range_satisfied.`
  + **tests:** Add tests for the current behavior of `pcmk__split_range.`
  + **tools, lib:** Use standard pacemaker return codes in `crm_rule.`
  + **tools:** Correct stonith-event arguments in `crm_mon.`
  + **tools:** Fix man pages for `crm_mon` & `crm_diff.`
  + **tools:** Make `crm_mon` `--interval` understand more formats.
  + **tools:** Fix `--html-title=` in `crm_mon.`
  + **tools:** Print errors to stderr for `crm_mon's` legacy xml.
  + **tools:** use return codes consistently in `stonith_admin`
  + **tools:** Use glib for cmdline handling in `crm_diff`, `crm_simulate` & `crm_error`
  + **xml:** Add a new version of the tags schema.
  + **based:** populate `cib_nodes` when `cibadmin -R --scope=configuration`
  + **cibsecret:** don't use pssh -q option unless supported
  + **fencing:** avoid infinite loop if device is removed during operation
  + **fencing:** avoid possible use-of-NULL when parsing metadata
  + **fencing:** Remove dangling 'pending' for completed DC fencing. (CLBZ#5401)

# Pacemaker-2.0.3 (25 Nov 2019)
- 601 commits with 227 files changed, 17862 insertions(+), 10471 deletions(-)

## Features added since Pacemaker-2.0.2

  + **controller:** new 'fence-reaction' cluster option specifies whether local node
                should 'stop' or 'panic' if notified of own fencing
  + **controller:** more cluster properties support ISO 8601 time specifications
  + **controller:** calculate cluster recheck interval dynamically when possible
  + **Pacemaker Remote:** allow file for environment variables when used in bundle
  + **Pacemaker Remote:** allow configurable listen address and TLS priorities
  + **tools:** `crm_mon` now supports standard `--output-as/--output-to` options
  + **tools:** `crm_mon` HTML output supports user-defined CSS stylesheet
  + **tools:** `stonith_admin` supports HTML output in addition to text and XML
  + **tools:** `crm_simulate` supports `--repeat` option to repeat profiling tests
  + **tools:** new `pcmk_simtimes` tool compares `crm_simulate` profiling output
  + **agents:** SysInfo supports K, T, and P units in addition to Kb and G

## Changes since Pacemaker-2.0.2

  + **fencer:** do not block concurrent fencing actions on a device
            *(regression since 2.0.2)*
  + **all:** avoid Year 2038 issues
  + **all:** allow ISO 8601 strings of form "<date>T<time> <offset>"
  + **rpm:** pacemaker-cts package now explicitly requires pacemaker-cli
  + **controller:** set timeout on scheduler responses to avoid infinite wait
  + **controller:** confirm cancel of failed monitors, to avoid transition timeout
  + **executor:** let controller cancel monitors, to avoid transition timeout
  + **executor:** return error for stonith probes if stonith connection was lost
  + **fencer:** ensure concurrent fencing commands always get triggered to execute
  + **fencer:** fail pending actions and re-sync history after crash and restart
  + **fencer:** don't let command with long delay block other pending commands
  + **fencer:** allow functioning even if CIB updates arrive unceasingly
  + **scheduler:** wait for probe actions to complete to prevent unnecessary
               restart/re-promote of dependent resources
  + **scheduler:** avoid invalid transition when guest node host is not fenceable
  + **scheduler:** properly detect dangling migrations, to avoid restart loop
  + **scheduler:** avoid scheduling actions on remote node that is shutting down
  + **scheduler:** avoid delay in recovery of failed remote connections
  + **scheduler:** clarify action failure log messages by including failure time
  + **scheduler:** calculate secure digests for unfencing, for replaying saved CIBs
  + **libcrmcommon:** avoid possible use-of-NULL when applying XML diffs
  + **libcrmcommon:** correctly apply XML diffs with multiple move/create changes
  + **libcrmcommon:** return error when applying XML diffs with unknown operations
  + **tools:** avoid duplicate lines between nodes in `crm_simulate` dot graph
  + **tools:** count disabled/blocked resources correctly in `crm_mon/crm_simulate`
  + **tools:** `crm_mon` `--interval` now accepts ISO 8601 and has correct help
  + **tools:** organize `crm_mon` text output with list headings, indents, bullets
  + **tools:** `crm_report:` fail if tar is not available
  + **tools:** `crm_report:` correct argument parsing
  + **tools:** `crm_report:` don't ignore log if unrelated file is too large
  + **tools:** `stonith_admin` `--list-targets` should show what fencer would use
  + **agents:** calculate #health_disk correctly in SysInfo
  + **agents:** handle run-as-user properly in ClusterMon

# Pacemaker-2.0.2 (04 Jun 2019)
- 288 commits with 225 files changed, 28494 insertions(+), 24465 deletions(-)

## Features added since Pacemaker-2.0.1

  + **tools:** `crm_resource` `--validate` can get resource parameters from command line
  + **tools:** `crm_resource` `--clear` prints out any cleared constraints
  + **tools:** new `crm_rule` tool for checking rule expiration (experimental)
  + **tools:** `stonith_admin` supports XML output for machine parsing (experimental)
  + **resources:** new HealthIOWait resource agent for node health tracking

## Changes since Pacemaker-2.0.1

  + Important security fixes for CVE-2018-16878, CVE-2018-16877, CVE-2019-3885
  + **build:** `crm_report` bug report URL is now configurable at build time
  + **build:** private libpengine/libtransitioner libraries combined as libpacemaker
  + **controller:** avoid memory leak when duplicate monitor is scheduled
  + **scheduler:** respect order constraints when resources are being probed
  + **scheduler:** one group stop shouldn't make another required
  + **libcrmcommon:** handle out-of-range integers in configuration better
  + **libcrmcommon:** export logfile environment variable if using default
  + **libcrmcommon:** avoid segmentation fault when beginning formatted text list
  + **libcrmservice:** fix use-after-free memory error in alert handling
  + **libstonithd:** handle more than 64KB output from fence agents


# Pacemaker-2.0.1 (4 Mar 2019)
- 592 commits with 173 files changed, 9268 insertions(+), 5344 deletions(-)

## Features added since Pacemaker-2.0.0

  + Pacemaker bundles support podman for container management
  + **fencing:** SBD may be used in a cluster that has guest nodes or bundles
  + **fencing:** fencing history is synchronized among all nodes
  + **fencing:** `stonith_admin` has option to clear fence history
  + **tools:** `crm_mon` can show fencing action failures and history
  + **tools:** `crm_resource --clear` supports new `--expired` option
  + **Pacemaker Remote:** new options to restrict TLS Diffie-Hellman prime length

## Changes since Pacemaker-2.0.0

  + **scheduler:** clone notifications could be scheduled for a stopped
    Pacemaker Remote node and block all further cluster actions
    *(regression since 2.0.0)*
  + **libcrmcommon:** correct behavior for completing interrupted live migrations
    *(regression since 2.0.0)*
  + **tools:** `crm_resource -C` could fail to clean up all failures in one run
    *(regression since 2.0.0)*
  + **Pacemaker Remote:** avoid unnecessary downtime when moving resource to
    Pacemaker Remote node that fails to come up *(regression since 1.1.18)*
  + **tools:** restore `stonith_admin` ability to confirm unseen nodes are down
    *(regression since 1.1.12)*
  + **build:** minor logging fixes to allow compatibility with GCC 9 -Werror
  + **build:** spec file now puts XML schemas in new pacemaker-schemas package
  + **build:** spec file now provides virtual pcmk-cluster-manager package
  + **pacemaker-attrd:** wait a short time before re-attempting failed writes
  + **pacemaker-attrd:** ignore attribute delays when writing after node (re-)join
  + **pacemaker-attrd:** start new election immediately if writer is lost
  + **pacemaker-attrd:** clear election dampening when the writer leaves
  + **pacemaker-attrd:** detect alert configuration changes when CIB is replaced
  + **CIB:** inform originator of CIB upgrade failure
  + **controller:** support resource agents that require node name even for meta-data
  + **controller:** don't record pending clone notifications in CIB
  + **controller:** DC detects completion of another node's shutdown more accurately
  + **controller:** shut down DC if unable to update node attributes
  + **controller:** handle corosync peer/join notifications for new node in any order
  + **controller:** clear election dampening when DC is lost
  + **executor:** cancel recurring monitors if fence device registration is lost
  + **fencing:** check for fence device update when resource defaults change
  + **fencing:** avoid pacemaker-fenced crash possible with `stonith_admin` misuse
  + **fencing:** limit fencing history to 500 entries
  + **fencing:** `stonith_admin` now complains if no action option is specified
  + **pacemakerd:** do not modify kernel.sysrq on Linux
  + **scheduler:** regression test compatibility with glib 2.59.0
  + **scheduler:** avoid unnecessary recovery of cleaned guest nodes and bundles
  + **scheduler:** ensure failures causing fencing not expired until fencing done
  + **scheduler:** start unique clone instances in numerical order
  + **scheduler:** convert unique clones to anonymous clones when not supported
  + **scheduler:** associate pending tasks with correct clone instance
  + **scheduler:** ensure bundle clone notifications are directed to correct host
  + **scheduler:** avoid improper bundle monitor rescheduling or fail count clearing
  + **scheduler:** honor asymmetric orderings even when restarting
  + **scheduler:** don't order non-DC shutdowns before DC fencing
  + **ACLs:** assume unprivileged ACL user if can't get user info
  + **Pacemaker Remote:** get Diffie-Hellman prime bit length from GnuTLS API
  + **libcrmservice:** cancel DBus call when cancelling systemd/upstart actions
  + **libcrmservice:** order systemd resources relative to `pacemaker_remote`
  + **libpe_status:** add public API constructor/destructor for `pe_working_set_t`
  + **tools:** fix `crm_resource` `--clear` when lifetime was used with ban/move
  + **tools:** fix `crm_resource` `--move` when lifetime was used with previous move
  + **tools:** make `crm_mon` CIB connection errors non-fatal if previously successful
  + **tools:** improve `crm_mon` messages when generating HTML output
  + **tools:** `crm_mon` cluster connection failure is now "critical" in nagios mode
  + **tools:** `crm_mon` listing of standby nodes shows if they have active resources
  + **tools:** `crm_diff` now ignores attribute ordering when comparing in CIB mode
  + **tools:** improve `crm_report` detection of logs, CIB directory, and processes
  + **tools:** `crm_verify` returns reliable exit codes
  + **tools:** `crm_simulate` resource history uses same name as live cluster would


# Pacemaker-2.0.0 (6 Jul 2018)
- 885 commits with 549 files changed, 89865 insertions(+), 95100 deletions(-)

- Deprecated features removed since Pacemaker-1.1.18
  + All of these have newer forms, and the cluster will automatically convert
    most older syntax usage in saved configurations to newer syntax as needed
  + Drop support for heartbeat and corosync 1 (whether using CMAN or plugin)
  + Drop support for rolling upgrades from Pacemaker versions older than 1.1.11
  + Drop support for built-in SMTP and SNMP in `crm_mon`
  + Drop support for legacy option aliases including default-action-timeout,
    default-resource-stickiness, resource-failure-stickiness,
    default-resource-failure-stickiness, is-managed-default,
    and all names using underbar instead of dash
  + Drop support for "requires" operation meta-attribute
  + Drop support for the `pcmk_*_cmd`, `pcmk_arg_map`, and `pcmk_poweroff_action`
    fence resource parameters
  + Drop support for deprecated command-line options to crmadmin,
    `crm_attribute`, `crm_resource`, `crm_verify`, `crm_mon`, and `stonith_admin`
  + Drop support for operation meta-attributes in `instance_attributes`
  + Drop support for `PCMK_legacy` and `LRMD_MAX_CHILDREN` environment variables
  + Drop support for undocumented resource isolation feature
  + Drop support for processing very old saved CIB files (including
    pre-0.6.0 start failure entries, pre-0.6.5 operation history entries,
    pre-0.7 transition keys, pre-1.1.4 migration history entries,
    pre-1.0 XML configuration schemas, pre-1.1.6 ticket state entries, and
    pre-1.1.7 failed recurring operation history entries)

## Features added since Pacemaker-1.1.18

  + The pacemaker daemons have been renamed to make logs more intuitive
    and easier to search
  + The default location of the Pacemaker detail log is now
    /var/log/pacemaker/pacemaker.log (instead of being directly in /var/log),
    and Pacemaker will no longer use Corosync's logging preferences;
    configure script options are available to change default log locations
  + The detail log's message format has been improved
  + The master XML tag is deprecated in favor of using a standard clone tag
    with a new "promotable" meta-attribute set to true, and the "master-max"
    and "master-node-max" master meta-attributes are deprecated in favor of
    new "promoted-max" and "promoted-node-max" clone meta-attributes;
    documentation now refers to these as promotable clones rather than
    master/slave, stateful, or multistate clones, and refers to
    promotion scores instead of master scores
  + Administration-related documentation has been moved from the
    "Pacemaker Explained" document to a new "Pacemaker Administration" document
  + record-pending now defaults to TRUE (pending actions are shown in status)
  + All Python code in Pacemaker now supports both Python 2.7 and Python 3
  + The command-line tools now return consistent, well-defined exit codes;
    `crm_error` has an `--exit` option to list these
  + Pacemaker's systemd unit files now remove systemd's spawned process limit
  + mount, path, and timer systemd unit types are now supported as resources
  + A negative stonith-watchdog-timeout now tells the cluster to automatically
    calculate the value based on `SBD_WATCHDOG_TIMEOUT` (which was the behavior
    of 0 before 1.1.15; 0 retains its post-1.1.15 behavior of disabling use of
    the watchdog as a fencing device)
  + The undocumented `restart-type` resource option and `role_after_failure`
    operation option are now deprecated
  + Regression testing code has been consolidated and overhauled
    (the most obvious change is new command names)
  + **build:** create /etc/pacemaker directory when installing
  + **build:** improved portability to BSD-based platforms
  + **tools:** `crm_resource` `--cleanup` now cleans only failed operation history;
    `crm_resource` `--reprobe` retains the previous behavior of cleaning all
    operation history
  + **tools:** add `stonith_admin` `--validate` option to check device configuration
  + **tools:** `crm_node` is now in the pacemaker-cli package (instead of pacemaker)
  + **alerts:** add epoch and usec alert variables for improved SNMP alerts
  + **controller:** deprecate "crmd-*" cluster options in favor of new names
  + **scheduler:** deprecate stonith-action value "poweroff" (use "off" instead)
  + **scheduler:** deprecate require-all in `rsc_order`
  + **libcrmcluster:** prefer corosync name over `ring0_addr`
  + **xml:** allow local "kind" in `resource_set` within `rsc_order`

## Changes since Pacemaker-1.1.18

  + Restore systemd unit dependency on DBus *(regression in 1.1.17)*
  + **CIB:** handle mixed-case node names when modifying attributes *(regression in 1.1.17)*
  + **scheduler:** avoid crash when logging ignored failure timeout *(regression in 1.1.17)*
  + **attrd:** ensure node name is broadcast at start-up *(regression in 1.1.18)*
  + **scheduler:** unfence before probing or starting fence devices *(regression in 1.1.18)*
  + **tools:** treat INFINITY correctly in `crm_failcount` *(regression in 1.1.17)*
  + **tools:** show master scores with `crm_simulate -sL` *(regression in 1.1.18)*
  + **tools:** `crm_master` did not work without explicit `--lifetime` *(regression in 1.1.18)*
  + Numerous changes to public C API of libraries
  + Choose current node correctly when a resource is multiply active
  + **controller,executor,tools:** avoid minor memory leaks
  + **CIB:** don't use empty CIB if real CIB has bad permissions
  + **controller:** avoid double free after ACL rejection of resource deletion
  + **controller:** don't record pending clone notifications in CIB
  + **controller:** always write faked failures to CIB whenever possible
  + **controller:** quorum gain without a node join should cause new transition
  + **executor:** handle systemd actions correctly when used with "service:"
  + **executor:** find absolute LSB paths when used with "service:"
  + **scheduler:** handle "requires" of "quorum" or "nothing" properly
  + **scheduler:** ensure orphaned recurring monitors have interval set
  + **scheduler:** handle pending migrations correctly when record-pending is true
  + **scheduler:** don't time out failures that cause fencing until fencing completes
  + **scheduler:** handle globally-unique bundle children correctly
  + **scheduler:** use correct default timeout for monitors
  + **scheduler:** "symmetrical" defaults to "false" for serialize orders
  + **scheduler:** avoid potential use-of-NULL when unpacking ordering constraint
  + **scheduler:** properly cancel recurring monitors
  + **scheduler:** do not schedule notifications for unrunnable actions
  + **scheduler:** ensure stops occur after stopped remote connections come back up
  + **scheduler:** consider only allowed nodes when ordering start after all recovery
  + **scheduler:** avoid graph loop from ordering bundle child stops/demotes after container fencing
  + **scheduler:** remote connection resources are safe to require only quorum
  + **scheduler:** correctly observe colocation with bundles in Master role
  + **scheduler:** restart resource after failed demote when appropriate
  + **Pacemaker Remote:** always use most recent remote proxy
  + **tools:** `crm_node` now gets correct node name and ID on Pacemaker Remote nodes
  + **tools:** correctly check `crm_resource` `--move` for master role
  + **tools:** cibsecret `--help/--version` doesn't require cluster to be running
  + **tools:** ignore attribute placement when `crm_diff` compares in cib mode
  + **tools:** prevent notify actions from causing `crm_resource` `--wait` to hang
  + **resources:** drop broken configdir parameter from ocf:pacemaker:controld

- **For further details, see:**
  https://projects.clusterlabs.org/w/projects/pacemaker/pacemaker_2.0_changes/


# Pacemaker-1.1.18 (14 Nov 2017)
- 644 commits with 167 files changed, 9753 insertions(+), 5596 deletions(-)

## Features added since Pacemaker-1.1.17

  + warnings are now logged when using legacy syntax to be removed in 2.0
  + **agents:** ifspeed agent is now installed when building
  + **agents:** ifspeed agent can optionally detect interface name from IP address
  + **alerts:** support alert filters
  + **alerts:** experimental support for alerts for node attribute changes
  + **crmd,pengine:** support unfencing of remote nodes
  + **pengine:** bundles now support all constraint types
  + **pengine:** bundles now support rkt containers
  + **pengine:** bundles support new container-attribute-target parameter
  + **pengine,tools:** logs and `crm_mon` show why resources changed state
  + **stonith-ng:** support new fencing resource parameter `pcmk_delay_base`
  + **tools:** new `crm_resource` option `--why` explains why resources are stopped

## Changes since Pacemaker-1.1.17

  + many documentation improvements
  + **agents:** ifspeed properly calculates speed of hfi1 interfaces
  + **agents:** ClusterMon now interprets "update" less than 1000 as seconds
  + **attrd:** don't lose attributes set between attrd start-up and cluster join
  + **attrd:** fix multiple minor memory leaks
  + **crmd:** correctly record that unfencing is complete
  + **crmd:** error more quickly if remote start fails due to missing key
  + **lrmd:** remote resource operations return immediate error if key setup fails
  + **lrmd:** allow pre-1.1.15 cluster nodes to connect to current Pacemaker Remote
  + **pengine:** guest nodes are now probed like other nodes
  + **pengine:** probe remote nodes for guest node resources
  + **pengine:** do not probe guest/bundle connections until guest/bundle is active
  + **pengine:** allow resources to stop prior to probes completing
  + **pengine:** bundles wait only for other containers on same node to be probed
  + **pengine:** have bundles log to stderr so 'docker logs'/'journalctl -M' works
  + **pengine:** only pass requests for promote/demote flags onto the bundle's child
  + **pengine:** do not map ports into Docker container when net=host is specified
  + **pengine:** allow resources inside bundles to receive clone notifications
  + **pengine:** default to non-interleaved bundle ordering for safety
  + **pengine:** ensure bundle nodes and child resources are correctly cleaned up
  + **pengine:** prevent graph loops when fencing the host underneath a bundle
  + **pengine:** fix multiple memory issues (use-after-free, use-of-NULL) with bundles
  + **pengine:** resources in bundles respect failcounts
  + **pengine:** ensure nested container connections run on the same host
  + **pengine:** ensure unrecoverable remote nodes are fenced even with no resources
  + **pengine:** handle resource migrating behind a migrating remote connection
  + **pengine:** don't prefer to keep unique instances on same node
  + **pengine:** exclude exclusive resources and nodes from symmetric default score
  + **pengine:** if ignoring failure, also ignore migration-threshold
  + **pengine:** restore the ability to send the transition graph via the disk if it gets too big
  + **pengine:** validate no-quorum-policy=suicide correctly
  + **pengine:** avoid crash when alerts section has comments
  + **pengine:** detect permanent master scores at start-up
  + **pengine:** do not re-add a node's default score for each location constraint
  + **pengine:** make sure calculated resource scores are consistent on different architectures
  + **pengine:** retrigger unfencing for changed device parameters only when necessary
  + **pengine:** don't schedule reload and restart in same transition (CLBZ#5309, regression introduced in 1.1.15)
  + **stonith-ng:** make fencing-device reappear properly after reenabling
  + **stonith-ng:** include `pcmk_on_action` in meta-data so 'on' can be overridden
  + **tools:** allow `crm_report` to work with no log files specified
  + **tools:** fix use-after-free in `crm_diff` introduced in 1.1.17
  + **tools:** allow `crm_resource` to operate on anonymous clones in unknown states
  + **tools:** `crm_resource --cleanup` on appropriate nodes if we don't know state of resource
  + **tools:** prevent disconnection from crmd during `crm_resource --cleanup`
  + **tools:** improve messages for `crm_resource` `--force-*` options
  + **tools:** `crm_mon:` avoid infinite process spawning if -E script can't be run
  + **tools:** `crm_mon:` don't show previous exit-reason for failed action with none
  + **libcrmservice:** list systemd unit files, not only active units (CLBZ#5299)
  + **libcrmservice:** parse long description correctly for LSB meta-data


# Pacemaker-1.1.17 (06 Jul 2017)
- 539 commits with 177 files changed, 11525 insertions(+), 5036 deletions(-)

## Features added since Pacemaker-1.1.16

  + New `bundle` resource type for Docker container use cases (experimental)
  + New `PCMK_node_start_state` environment variable to start node in standby
  + New `value-source` rule expression attribute in location constraints to
    compare a node attribute against a resource parameter
  + New `stonith-max-attempts` cluster option to specify how many times
    fencing can fail for a target before the cluster will no longer
    immediately re-attempt it (previously hard-coded at 10)
  + New `cluster-ipc-limit` cluster option to avoid IPC client eviction in
    large clusters
  + Failures are now tracked per operation type, as well as per node and
    resource (the `fail-count` and `last-failure` node attribute names now end
    in `#OPERATION_INTERVAL`)
  + **attrd:** Pacemaker Remote node attributes and regular expressions are now
    supported on legacy cluster stacks (heartbeat, CMAN, and corosync plugin)
  + **tools:** New `crm_resource --validate` option
  + **tools:** New `stonith_admin --list-targets` option
  + **tools:** New `crm_attribute --pattern` option to match a regular
    expression
  + **tools:** `crm_resource --cleanup` and `crm_failcount` can now take
    `--operation` and `--interval` options to operate on a single operation
    type

## Changes since Pacemaker-1.1.16

  + Fix multiple memory issues (leaks, use-after-free) in libraries
  + **pengine:** unmanaging a guest node resource puts guest in maintenance mode
  + **cib:** broadcasts of cib changes should always pass ACL checks
  + **crmd,libcrmcommon:** update throttling when CPUs are hot-plugged
  + **crmd:** abort transition whenever we lose quorum
  + **crmd:** avoid attribute write-out on join when atomic attrd is used
  + **crmd:** check for too many stonith failures only when aborting for that reason
  + **crmd:** correctly clear failure counts only for a specified node
  + **crmd:** don't fence old DC if it's shutting down as soon-to-be DC joins
  + **crmd:** forget stonith failures when forgetting node
  + **crmd:** all nodes should track stonith failure counts in case they become DC
  + **crmd:** update cache status for guest node whose host is fenced
  + **dbus:** prevent lrmd from hanging on dbus calls
  + **fencing:** detect newly added constraints for stonith devices
  + **pengine:** order remote actions after connection recovery
    *(regression introduced in 1.1.15)*
  + **pengine:** quicker recovery from failed demote
  + **libcib:** determine remote nodes correctly from node status entries
  + **libcrmcommon:** avoid evicting IPC client if messages spike briefly
  + **libcrmcommon:** better XML comment handling prevents infinite election loop
  + **libcrmcommon:** set month correctly in date/time string sent to alert agents
  + **libfencing,fencing:** intelligently remap "action" wrongly specified in config
  + **libservices:** ensure completed ops aren't on blocked ops list
  + **libservices:** properly detect and cancel in-flight systemd/upstart ops
  + **libservices:** properly watch writable DBus handles
  + **libservices:** systemd service that is reloading doesn't cause monitor failure
  + **pacemaker_remoted:** allow graceful shutdown while unmanaged
  + **pengine,libpe_status:** don't clear same fail-count twice
  + **pengine:** consider guest node unclean if its host is unclean
  + **pengine:** do not re-add a node's default score for each location constraint
  + **pengine:** avoid restarting services when recovering remote connection
  + **pengine:** better guest node recovery when host fails
  + **pengine:** guest node fencing doesn't require stonith enabled
  + **pengine:** allow probes of guest node connection resources
  + **pengine:** properly handle allow-migrate explicitly set for remote connection
  + **pengine:** fence failed remote nodes even if no resources can run on them
  + **tools:** resource agents will now get the correct node name on
    Pacemaker Remote nodes when using `crm_node` and `crm_attribute`
  + **tools:** avoid grep crashes in `crm_report` when looking for system logs
  + **tools:** `crm_resource -C` now clears `last-failure` as well as
    `fail-count`
  + **tools:** implement `crm_failcount` command-line options correctly
  + **tools:** properly ignore version with `crm_diff --no-version`


# Pacemaker-1.1.16 (30 Nov 2016)
- 382 commits with 145 files changed, 7200 insertions(+), 5621 deletions(-)

## Features added since Pacemaker-1.1.15

  + Location constraints may use rsc-pattern, with submatches expanded
  + node-health-base available with node-health-strategy=progressive
  + new Pacemaker Development document for working on pacemaker code base
  + new `PCMK_panic_action` variable allows crash instead of reboot on panic
  + **resources:** add resource agent for managing a node attribute
  + **systemd:** include socket units when listing all systemd agents

## Changes since Pacemaker-1.1.15

  + Important security fix for CVE-2016-7035
  + Logging is now synchronous when blackboxes are enabled
  + All python code except CTS is now compatible with python 2.6+ and 3.2+
  + **build:** take advantage of compiler features for security and performance
  + **build:** update SuSE spec modifications for recent spec changes
  + **build:** avoid watchdog reboot when upgrading `pacemaker_remote` with sbd
  + **build:** numerous other improvements in environment detection, etc.
  + **cib:** fix infinite loop when no schema validates
  + **crmd:** cl#5185 - record pending operations in CIB before they are performed
  + **crmd:** don't abort transitions for CIB comment changes
  + **crmd:** resend shutdown request if DC loses original request
  + **documentation:** install improved README in doc instead of now-removed AUTHORS
  + **documentation:** clarify licensing and provide copy of all licenses
  + **documentation:** document various features and upgrades better
  + **fence_legacy:** use "list" action when searching cluster-glue agents
  + **libcib:** don't stop sending alerts after releasing DC role
  + **libcrmcommon:** properly handle XML comments when comparing v2 patchset diffs
  + **libcrmcommon:** report errors consistently when waiting for data on connection
  + **libpengine:** avoid potential use-of-NULL
  + **libservices:** use DBusError API properly
  + **pacemaker_remote:** init script stop should always return 0
  + **pacemaker_remote:** allow remote clients to timeout/reconnect
  + **pacemaker_remote:** correctly calculate remaining timeout when receiving messages
  + **pengine:** avoid transition loop for start-then-stop + unfencing
  + **pengine:** correctly update dependent actions of un-runnable clones
  + **pengine:** do not fence a node in maintenance mode if it shuts down cleanly
  + **pengine:** set `OCF_RESKEY_CRM_meta_notify_active_*` for multistate resources
  + **resources:** ping - avoid temporary files for fping check, support FreeBSD
  + **resources:** SysInfo - better support for FreeBSD
  + **resources:** variable name typo in docker-wrapper
  + **systemd:** order pacemaker after time-sync target
  + **tools:** correct `attrd_updater` help and error messages when using CMAN
  + **tools:** `crm_standby` `--version/--help` should work without cluster running
  + **tools:** make `crm_report` sanitize CIB before generating readable version
  + **tools:** display pending resource state by default when available
  + **tools:** avoid matching other process with same PID in ClusterMon


# Pacemaker-1.1.15 (21 Jun 2016)
- 533 commits with 219 files changed, 6659 insertions(+), 3989 deletions(-)

## Features added since Pacemaker-1.1.14

  + Event-driven alerts allow scripts to be called after significant events
  + **build:** Some files moved from pacemaker package to pacemaker-cli for cleaner pacemaker-remote dependencies
  + **build:** ./configure `--with-configdir` argument for /etc/sysconfig, /etc/default, etc.
  + **fencing:** Simplify watchdog integration
  + **fencing:** Support concurrent fencing actions via new `pcmk_action_limit` option
  + **remote:** `pacemaker_remote` may be stopped without disabling resource first
  + **remote:** Report integration status of Pacemaker Remote nodes in CIB `node_state`
  + **tools:** `crm_mon` now reports why resources are not starting
  + **tools:** `crm_report` now obscures passwords in logfiles
  + **tools:** `attrd_updater --update-both/--update-delay` options allow
    changing dampening value
  + **tools:** allow `stonith_admin -H '*'` to show history for all nodes

## Changes since Pacemaker-1.1.14

  + Fix multiple memory issues (leaks, use-after-free) in daemons, libraries and tools
  + Make various log messages more user-friendly
  + Improve FreeBSD and Hurd support
  + **attrd:** Prevent possible segfault on exit
  + **cib:** Fix regression to restore support for compressed CIB larger than 1MB
  + **common:** fix regression in 1.1.14 that made have-watchdog always true
  + **controld:** handle DLM "wait fencing" state better
  + **crmd:** Fix regression so that fenced unseen nodes do not remain unclean
  + **crmd:** Take start-delay into account when calculation action timeouts
  + **crmd:** Avoid timeout on older peers when cancelling a resource operation
  + **fencing:** Allow fencing by node ID (e.g. by DLM) even if node left cluster
  + **lrmd:** Fix potential issues when cluster is stopped via systemd shutdown
  + **pacemakerd:** Properly respawn stonithd if it fails
  + **pengine:** Fix regression with multiple monitor levels that could ignore failure
  + **pengine:** Correctly set `OCF_RESKEY_CRM_meta_timeout` when start-delay is configured
  + **pengine:** Properly order actions for master/slave resources in anti-colocations
  + **pengine:** Respect asymmetrical ordering when trying to move resources
  + **pengine:** Properly order stop actions on guest node relative to host stonith
  + **pengine:** Correctly block actions dependent on unrunnable clones
  + **remote:** Allow remote nodes to have node attributes even with legacy attrd
  + **remote:** Recover from remote node fencing more quickly
  + **remote:** Place resources on newly rejoined remote nodes more quickly
  + **resources:** ping agent can now use fping6 for IPv6 hosts
  + **resources:** SysInfo now resets #health_disk to green when there's sufficient free disk
  + **tools:** `crm_report` is now more efficient and handles Pacemaker Remote nodes better
  + **tools:** Prevent `crm_resource` segfault when `--resource` is not supplied with --restart
  + **tools:** `crm_shadow` `--display` option now works
  + **tools:** `crm_resource` `--restart` handles groups, target-roles and moving resources better


# Pacemaker-1.1.14 (14 Jan 2016)
- 724 commits with 179 files changed, 13142 insertions(+), 7695 deletions(-)

## Features added since Pacemaker-1.1.13

  + **crm_resource:** Indicate common reasons why a resource may not start after a cleanup
  + **crm_resource:** New `--force-promote` and `--force-demote` options for debugging
  + **fencing:** Support targeting fencing topologies by node name pattern or node attribute
  + **fencing:** Remap sequential topology reboots to all-off-then-all-on
  + **pengine:** Allow resources to start and stop as soon as their state is known on all nodes
  + **pengine:** Include a list of all and available nodes with clone notifications
  + **pengine:** Addition of the clone resource clone-min metadata option
  + **pengine:** Support of multiple-active=block for resource groups
  + **remote:** Resources that create guest nodes can be included in a group resource
  + **remote:** `reconnect_interval` option for remote nodes to delay reconnect after fence

## Changes since Pacemaker-1.1.13

  + improve support for building on FreeBSD and Debian
  + fix multiple memory issues (leaks, use-after-free, double free, use-of-NULL) in components and tools
  + **cib:** Do not terminate due to badly behaving clients
  + **cman:** handle corosync-invented node names of the form Node{id} for peers not in its node list
  + **controld:** replace bashism
  + **crm_node:** Display node state with -l and quorum status with -q, if available
  + **crmd:** resources would sometimes be restarted when only non-unique parameters changed
  + **crmd:** fence remote node after connection failure only once
  + **crmd:** handle resources named the same as cluster nodes
  + **crmd:** Pre-emptively fail in-flight actions when lrmd connections fail
  + **crmd:** Record actions in the CIB as failed if we cannot execute them
  + **crm_report:** Enable password sanitizing by default
  + **crm_report:** Allow log file discovery to be disabled
  + **crm_resource:** Allow the resource configuration to be modified for
    `--force-{check,start,..}` calls
  + **crm_resource:** Compensate for -C and -p being called with the child resource for clones
  + **crm_resource:** Correctly clean up all children for anonymous cloned groups
  + **crm_resource:** Correctly clean up failcounts for inactive anonymous clones
  + **crm_resource:** Correctly observe `--force` when deleting and updating attributes
  + **crm_shadow:** Fix `crm_shadow --diff`
  + **crm_simulate:** Prevent segfault on arches with 64bit `time_t`
  + **fencing:** ensure `required`/`automatic` apply only to `on` actions
  + **fencing:** Return a provider for the internal fencing agent `#watchdog`
    instead of logging an error
  + **fencing:** ignore stderr output of fence agents (often used for debug
    messages)
  + **fencing:** fix issue where deleting a fence device attribute can delete
    the device
  + **libcib:** potential user input overflow
  + **libcluster:** overhaul peer cache management
  + **log:** make syslog less noisy
  + **log:** fix various misspellings in log messages
  + **lrmd:** cancel currently pending STONITH op if stonithd connection is
    lost
  + **lrmd:** Finalize all pending and recurring operations when cleaning up a
    resource
  + **pengine:** Bug cl#5247 - Imply resources running on a container are
    stopped when the container is stopped
  + **pengine:** cl#5235 - Prevent graph loops that can be introduced by
    `load_stopped -> migrate_to` ordering
  + **pengine:** Correctly bypass fencing for resources that do not require it
  + **pengine:** do not timeout remote node recurring monitor op failure until
    after fencing
  + **pengine:** Ensure recurring monitor operations are cancelled when clone
    instances are de-allocated
  + **pengine:** fixes segfault in pengine when fencing remote node
  + **pengine:** properly handle blocked clone actions
  + **pengine:** ensure failed actions that occurred in node shutdown are
    displayed
  + **remote:** correctly display the usage of the ocf:pacemaker:remote
    resource agent
  + **remote:** do not fail operations because of a migration
  + **remote:** enable reloads for select remote connection options
  + **resources:** allow for top output with or without percent sign in
    HealthCPU
  + **resources:** Prevent an error message on stopping `Dummy` resource
  + **systemd:** Prevent segfault when logging failed operations
  + **systemd:** Reconnect to System DBus if the connection is closed
  + **systemd:** set systemd resources' timeout values higher than systemd's
    own default
  + **tools:** Do not send command lines to syslog
  + **tools:** update SNMP MIB
  + **upstart:** Ensure pending structs are correctly unreferenced


# Pacemaker-1.1.13 (24 Jun 2015)
- 750 commits with 156 files changed, 11323 insertions(+), 3725 deletions(-)

## Features added since Pacemaker-1.1.12

  + Allow fail-counts to be removed en-mass when the new attrd is in operation
  + attrd supports private attributes (not written to CIB)
  + **crmd:** Ensure a watchdog device is in use if stonith-watchdog-timeout is configured
  + **crmd:** If configured, trigger the watchdog immediately if we lose quorum and no-quorum-policy=suicide
  + **crm_diff:** Support generating a difference without versions details if `--no-version/-u` is supplied
  + **crm_resource:** Implement an intelligent restart capability
  + **Fencing:** Advertise the watchdog device for fencing operations
  + **Fencing:** Allow the cluster to recover resources if the watchdog is in use
  + **fencing:** cl#5134 - Support random fencing delay to avoid double fencing
  + **mcp:** Allow orphan children to initiate node panic via SIGQUIT
  + **mcp:** Turn on sbd integration if pacemakerd finds it running
  + **mcp:** Two new error codes that result in machine reset or power off
  + Officially support the resource-discovery attribute for location constraints
  + **PE:** Allow natural ordering of colocation sets
  + **PE:** Support non-actionable degraded mode for OCF
  + **pengine:** cl#5207 - Display "UNCLEAN" for resources running on unclean offline nodes
  + **remote:** pcmk remote client tool for use with container wrapper script
  + Support machine panics for some kinds of errors (via sbd if available)
  + **tools:** add `crm_resource` `--wait` option
  + **tools:** `attrd_updater` supports `--query` and `--all` options
  + **tools:** `attrd_updater:` Allow attributes to be set for other nodes

## Changes since Pacemaker-1.1.12

  + **pengine:** exclusive discovery implies rsc is only allowed on exclusive subset of nodes
  + **acl:** Correctly implement the 'reference' acl directive
  + **acl:** Do not delay evaluation of added nodes in some situations
  + **attrd:** b22b1fe did uuid test too early
  + **attrd:** Clean out the node cache when requested by the admin
  + **attrd:** fixes double free in attrd legacy
  + **attrd:** properly write attributes for peers once uuid is discovered
  + **attrd:** refresh should force an immediate write-out of all attributes
  + **attrd:** Simplify how node deletions happen
  + **Bug rhbz#1067544 - Tools:** Correctly handle `--ban,` --move and `--locate` for master/slave groups
  + Bug rhbz#1181824 - Ensure the DC can be reliably fenced
  + **cib:** Ability to upgrade cib validation schema in legacy mode
  + **cib:** Always generate digests for cib diffs in legacy mode
  + **cib:** assignment where comparison intended
  + **cib:** Avoid nodeid conflicts we don't care about
  + **cib:** Correctly add "update-origin", "update-client" and "update-user" attributes for cib
  + **cib:** Correctly set up signal handlers
  + **cib:** Correctly track node state
  + **cib:** Do not update on disk backups if we're just querying them
  + **cib:** Enable cib legacy mode for plugin-based clusters
  + **cib:** Ensure file-based backends treat '-o section' consistently with the native backend
  + **cib:** Ensure upgrade operations from a non-DC get an acknowledgement
  + **cib:** No need to enforce cib digests for v2 diffs in legacy mode
  + **cib:** Revert d153b86 to instantly get cib synchronized in legacy mode
  + **cib:** tls sock cleanup for remote cib connections
  + **cli:** Ensure subsequent unknown long options are correctly detected
  + **cluster:** Invoke `crm_remove_conflicting_peer()` only when the new node's uname is being assigned in the node cache
  + **common:** Increment current and age for lib common as a result of APIs being added
  + **corosync:**  Bug cl#5232 - Somewhat gracefully handle nodes with invalid UUIDs
  + **corosync:** Avoid unnecessary repeated CMAP API calls
  + **crmd/pengine:** handle on-fail=ignore properly
  + **crmd:** Add "on_node" attribute for *_last_failure_0 lrm resource operations
  + **crmd:** All peers need to track node shutdown requests
  + **crmd:** Cached copies of transient attributes cease to be valid once a node leaves the membership
  + **crmd:** Correctly add the local option that validates against schema for pengine to calculate
  + **crmd:** Disable debug logging that results in significant overhead
  + **crmd:** do not remove connection resources during re-probe
  + **crmd:** don't update fail count twice for same failure
  + **crmd:** Ensure remote connection resources timeout properly during 'migrate_from' action
  + **crmd:** Ensure `throttle_mode()` does something on Linux
  + **crmd:** Fixes crash when remote connection migration fails
  + **crmd:** gracefully handle remote node disconnects during op execution
  + **crmd:** Handle remote connection failures while executing ops on remote connection
  + **crmd:** include remote nodes when forcing cluster wide resource reprobe
  + **crmd:** never stop recurring monitor ops for pcmk remote during incomplete migration
  + **crmd:** Prevent the old version of DC from being fenced when it shuts down for rolling-upgrade
  + **crmd:** Prevent use-of-NULL during reprobe
  + **crmd:** properly update job limit for baremetal remote-nodes
  + **crmd:** Remote-node throttle jobs count towards cluster-node hosting conneciton rsc
  + **crmd:** Reset stonith failcount to recover transitioner when the node rejoins
  + **crmd:** resolves memory leak in crmd.
  + **crmd:** respect `start-failure-is-fatal` even for artifically injected
    events
  + **crmd:** Wait for all pending operations to complete before poking the
    policy engine
  + **crmd:** When container's host is fenced, cancel in-flight operations
  + **crm_attribute:** Correctly update config options when `-o crm_config` is
    specified
  + **crm_failcount:** Better error reporting when no resource is specified
  + **crm_mon:** add exit reason to resource failure output
  + **crm_mon:** Fill `CRM_notify_node` in traps with node's uname rather than node's id if possible
  + **crm_mon:** Repair notification delivery when the v2 patch format is in use
  + **crm_node:** Correctly remove nodes from the CIB by nodeid
  + **crm_report:** More patterns for finding logs on non-DC nodes
  + **crm_resource:** Allow resource restart operations to be node specific
  + **crm_resource:** avoid deletion of lrm cache on node with resource discovery disabled.
  + **crm_resource:** Calculate how long to wait for a restart based on the resource timeouts
  + **crm_resource:** Clean up memory in `--restart` error paths
  + **crm_resource:** Display the locations of all anonymous clone children when supplying the children's common ID
  + **crm_resource:** Ensure `--restart` sets/clears meta attributes
  + **crm_resource:** Ensure fail-counts are purged when we redetect the state of all resources
  + **crm_resource:** Implement `--timeout` for resource restart operations
  + **crm_resource:** Include group members when calculating the next timeout
  + **crm_resource:** Memory leak in error paths
  + **crm_resource:** Prevent use-after-free
  + **crm_resource:** Repair regression test outputs
  + **crm_resource:** Use-after-free when restarting a resource
  + **dbus:** ref count leaks
  + **dbus:** Ensure both the read and write queues get dispatched
  + **dbus:** Fail gracefully if malloc fails
  + **dbus:** handle dispatch queue when multiple replies need to be processed
  + **dbus:** Notice when dbus connections get disabled
  + **dbus:** Remove double-free introduced while trying to make coverity shut up
  + ensure if B is colocated with A, B can never run without A
  + **fence_legacy:** Avoid passing 'port' to cluster-glue agents
  + **fencing:** Allow nodes to be purged from the member cache
  + **fencing:** Correctly make args for fencing agents
  + **fencing:** Correctly wait for self-fencing to occur when the watchdog is in use
  + **fencing:** Ensure the hostlist parameter is set for watchdog agents
  + **fencing:** Force 'stonith-ng' as the system name
  + **fencing:** Gracefully handle invalid metadata from agents
  + **fencing:** If configured, wait stonith-watchdog-timer seconds for self-fencing to complete
  + **fencing:** Reject actions for devices that haven't been explicitly registered yet
  + **ipc:** properly allocate server enforced buffer size on client
  + **ipc:** use server enforced buffer during ipc client send
  + **lrmd, services:** interpret LSB status codes properly
  + **lrmd:** add back support for class heartbeat agents
  + **lrmd:** cancel pending async connection during disconnect
  + **lrmd:** enable ipc proxy for docker-wrapper privileged mode
  + **lrmd:** fix rescheduling of systemd monitor op during start
  + **lrmd:** Handle systemd reporting 'done' before a resource is actually stopped
  + **lrmd:** Hint to child processes that using `sd_notify` is not required
  + **lrmd:** Log with the correct personality
  + **lrmd:** Prevent glib assert triggered by timers being removed from mainloop more than once
  + **lrmd:** report original timeout when systemd operation completes
  + **lrmd:** store failed operation exit reason in cib
  + **mainloop:** resolves race condition mainloop poll involving modification of ipc connections
  + make targetted reprobe for remote node work, `crm_resource` -C -N <remote node>
  + **mcp:** Allow a configurable delay when debugging shutdown issues
  + **mcp:** Avoid requiring 'export' for SYS-V sysconfig options
  + **Membership:** Detect and resolve nodes that change their ID
  + **pacemakerd:** resolves memory leak of xml structure in pacemakerd
  + **pengine:** ability to launch resources in isolated containers
  + **pengine:** add #kind=remote for baremetal remote-nodes
  + **pengine:** allow baremetal remote-nodes to recover without requiring fencing when cluster-node fails
  + **pengine:** allow remote-nodes to be placed in maintenance mode
  + **pengine:** Avoid trailing whitespaces when printing resource state
  + **pengine:** cl#5130 - Choose nodes capable of running all the colocated utilization resources
  + **pengine:** cl#5130 - Only check the capacities of the nodes that are allowed to run the resource
  + **pengine:** Correctly compare feature set to determine how to unpack meta attributes
  + **pengine:** disable migrations for resources with isolation containers
  + **pengine:** disable reloading of resources within isolated container wrappers
  + **pengine:** Do not aggregate children in a pending state into the started/stopped/etc lists
  + **pengine:** Do not record duplicate copies of the failed actions
  + **pengine:** Do not reschedule monitors that are no longer needed while resource definitions have changed
  + **pengine:** Fence baremetal remote when recurring monitor op fails
  + **pengine:** Fix colocation with unmanaged resources
  + **pengine:** Fix the behaviors of multi-state resources with asymmetrical ordering
  + **pengine:** fixes pengine crash with orphaned remote node connection resource
  + **pengine:** fixes segfault caused by malformed log warning
  + **pengine:** handle cloned isolated resources in a sane way
  + **pengine:** handle isolated resource scenario, cloned group of isolated resources
  + **pengine:** Handle ordering between stateful and migratable resources
  + **pengine:** imply stop in container node resources when host node is fenced
  + **pengine:** only fence baremetal remote when connection can fails or can not be recovered
  + **pengine:** only kill process group on timeout when on-fail does not equal block.
  + **pengine:** per-node control over resource discovery
  + **pengine:** prefer migration target for remote node connections
  + **pengine:** prevent disabling rsc discovery per node in certain situations
  + **pengine:** Prevent use-after-free in `sort_rsc_process_order()`
  + **pengine:** properly handle ordering during remote connection partial migration
  + **pengine:** properly recover remote-nodes when cluster-node proxy goes offline
  + **pengine:** remove unnecessary whitespace from notify environment variables
  + **pengine:** require-all feature for ordered clones
  + **pengine:** Resolve memory leaks
  + **pengine:** resource discovery mode for location constraints
  + **pengine:** restart master instances on instance attribute changes
  + **pengine:** Turn off legacy unpacking of resource options into the meta hashtable
  + **pengine:** Watchdog integration is sufficient for fencing
  + Perform systemd reloads asynchronously
  + **ping:** Correctly advertise multiplier default
  + Prefer to inherit the  watchdog timeout from SBD
  + properly record stop args after reload
  + provide fake meta data for ra class heartbeat
  + **remote:** report timestamps for remote connection resource operations
  + **remote:** Treat recv msg timeout as a disconnect
  + **service:** Prevent potential use-of-NULL in metadata lookups
  + **solaris:** Allow compilation when dirent.d_type is not available
  + **solaris:** Correctly replace the linux swab functions
  + **solaris:** Disable throttling since /proc doesn't exist
  + **stonith-ng:** Correctly observe the watchdog completion timeout
  + **stonith-ng:** Correctly track node state
  + **stonith-ng:** Reset mainloop source IDs after removing them
  + **systemd:** Correctly handle long running stop actions
  + **systemd:** Ensure failed monitor operations always return
  + **systemd:** Ensure we don't call `dbus_message_unref()` with NULL
  + **systemd:** fix crash caused when canceling in-flight operation
  + **systemd:** Kindly ask dbus NOT to kill the process if the dbus connection fails
  + **systemd:** Perform actions asynchronously
  + **systemd:** Perform monitor operations without blocking
  + **systemd:** Tell systemd not to take DBus down from underneath us
  + **systemd:** Trick systemd into not stopping our services before us during shutdown
  + **tools:** Improve `crm_mon` output with certain option combinations
  + **upstart:** Monitor actions always return 'ok' or 'not running'
  + **upstart:** Perform more parts of monitor operations without blocking
  + **xml:** add 'require-all' to xml schema for constraints
  + **xml:** cl#5231 - Unset the deleted attributes in the resulting diffs
  + **xml:** Clone the latest constraint schema in preparation for changes"
  + **xml:** Correctly create v1 patchsets when deleting attributes
  + **xml:** Do not change the ordering of properties when applying v1 cib diffs
  + **xml:** Do not dump deleted attributes
  + **xml:** Do not prune leaves from v1 cib diffs that are being created with digests
  + **xml:** Ensure ACLs are reapplied before calculating what a replace operation changed
  + **xml:** Fix upgrade-1.3.xsl to correctly transform ACL rules with "attribute"
  + **xml:** Prevent assert errors in `crm_element_value()` on applying a patch without version information
  + **xml:** Prevent potential use-of-NULL


# Pacemaker-1.1.12 (22 Jul 2014)
- 795 commits with 195 files changed, 13772 insertions(+), 6176 deletions(-)

## Features added since Pacemaker-1.1.11

  + Changes to the ACL schema to support nodes and unix groups
  + **cib:** Check ACLs prior to making the update instead of parsing the diff afterwards
  + **cib:** Default ACL support to on
  + **cib:** Enable the more efficient xml patchset format
  + **cib:** Implement zero-copy status update
  + **cib:** Send all r/w operations via the cluster connection and have all
    nodes process them
  + **crmd:** Set `cluster-name` property to Corosync's `cluster_name` by
    default for Corosync 2
  + **crm_mon:** Display brief output if `-b/--brief` is supplied or `b` is
    toggled
  + **crm_report:** Allow ssh alternatives to be used
  + **crm_ticket:** Support multiple modifications for a ticket in an atomic operation
  + **extra:** Add logrotate configuration file for /var/log/pacemaker.log
  + **Fencing:** Add the ability to call `stonith_api_time()` from `stonith_admin`
  + **logging:** daemons always get a log file, unless explicitly set to configured 'none'
  + **logging:** allows the user to specify a log level that is output to syslog
  + **PE:** Automatically re-unfence a node if the fencing device definition changes
  + **pengine:** cl#5174 - Allow resource sets and templates for location constraints
  + **pengine:** Support cib object tags
  + **pengine:** Support cluster-specific instance attributes based on rules
  + **pengine:** Support id-ref in nvpair with optional "name"
  + **pengine:** Support per-resource maintenance mode
  + **pengine:** Support site-specific instance attributes based on rules
  + **tools:** Allow `crm_shadow` to create older configuration versions
  + **tools:** Display pending state in `crm_mon/crm_resource/crm_simulate` if `--pending/-j` is supplied (cl#5178)
  + **xml:** Add the ability to have lightweight schema revisions
  + **xml:** Enable resource sets in location constraints for 1.2 schema
  + **xml:** Support resources that require unfencing

## Changes since Pacemaker-1.1.11

  + **acl:** Authenticate pacemaker-remote requests with the node name as the client
  + **acl:** Read access must be explicitly granted
  + **attrd:** Ensure attribute dampening is always observed
  + **attrd:** Remove offline nodes from node cache for "peer-remove" requests
  + Bug cl#5055 - Improved migration support.
  + Bug cl#5184 - Ensure pending probes that ultimately fail are correctly updated
  + **Bug cl#5196 - pengine:** Check values after expanding templates
  + Bug cl#5212 - Do not promote instances when quorum is lots and no-quorum-policy=freeze
  + Bug cl#5213 - Ensure role colocation with -INFINITY is enforced
  + Bug cl#5213 - Limit the scope of the previous commit to the masters role
  + **Bug cl#5219 - pengine:** Allow unrelated resources with a common colocation target to remain promoted
  + **Bug cl#5222 - cib:** Repair rolling update capability
  + Bug cl#5222 - Enable legacy mode whenever a broadcast update is detected
  + Bug rhbz#1036631 - Stop members of cloned groups when dependencies are stopped
  + Bug rhbz#1054307 - cname pattern match should be more restrictive in init script
  + Bug rhbz#1057697 - Use native DBus library for systemd/upstart support to avoid problematic use of threads
  + Bug rhbz#1097457 - Limit the scope of the previous fix and include a helpful comment
  + Bug rhbz#1097457 - Prevent invalid transition when resource are ordered to start after the container they're started in
  + **cib:** allow setting permanent remote-node attributes
  + **cib:** Auto-detect which patchset format to use
  + **cib:** Determine the best value of `validate-with` if one is not supplied
  + **cib:** Do not disable cib disk writes if on-disk cib is corrupt
  + **cib:** Ensure `cibadmin -R/--replace` commands get replies
  + **cib:** Erasing the cib is an admin action, bump the `admin_epoch` instead
  + **cib:** Fix remote cib based on TLS
  + **cib:** Ignore patch failures if we already have their contents
  + **cib:** Validate that everyone still sees the same configuration once all updates have completed
  + **cibadmin:** Allow priviliged clients to perform tasks as unpriviliged users
  + **cibadmin:** Remove dangerous commands that exposed unnecessary implementation internal details
  + **cluster:** Fix segfault on removing a node
  + **cluster:** Prevent search of unames from attempting to create node entries for unknown nodes
  + **cluster:** Remove unknown offline nodes with conflicting unames from node cache
  + **controld:** Do not consider the dlm up until the address list is present
  + **controld:** handling startup fencing within the controld agent, not the dlm
  + **controld:** Return `OCF_ERR_INSTALLED` instead of `OCF_NOT_INSTALLED`
  + **crmd:** Ack pending operations that were cancelled due to rsc deletion
  + **crmd:** Actions can only be executed if their pre-requisits completed successfully
  + **crmd:** avoid double free caused by nested hash table removal
  + **crmd:** Avoid spamming the cib by triggering a transition only once per non-status change
  + **crmd:** Correctly react to successful unfencing operations
  + **crmd:** Correctly recognise operation cancellations we initiated
  + **crmd:** Do not erase the status section for unfenced nodes
  + **crmd:** Do not overwrite existing node state when fencing completes
  + **crmd:** Do not start timers for already completed operations
  + **crmd:** Ensure `crm_config` options are re-read on updates
  + **crmd:** Fenced nodes that return prior to an election do not need to have their status section reset
  + **crmd:** make `lrm_state` hash table not case sensitive
  + **crmd:** make `node_state` erase correctly
  + **crmd:** Only write `fence_averride` if open() returns a positive file descriptor
  + **crmd:** Prevent manual fencing confirmations from attempting to create node entries for unknown nodes
  + **crmd:** Prevent SIGPIPE when notifying CMAN about fencing operations
  + **crmd:** Remove state of unknown nodes with conflicting unames from CIB
  + **crmd:** Remove unknown nodes with conflicting unames from CIB
  + **crmd:** Report unsuccessful unfencing operations
  + **crm_diff:** Allow the generation of xml patchsets without digests
  + **crm_mon:** Allow the file created by `--as-html` to be world readable
  + **crm_mon:** Ensure resource attributes have been unpacked before displaying connectivity data
  + **crm_node:** Only remove the named resource from the cib
  + **crm_report:** Gracefully handle rediculously large logfiles
  + **crm_report:** Only gather dlm data if `dlm_controld` is running
  + **crm_resource:** Gracefully handle -EACCESS when querying the cib
  + **crm_verify:** Perform a full set of calculations whenever the status section is present
  + **fencing:** Advertise support for reboot/on/off in the metadata for legacy agents
  + **fencing:** Automatically switch from 'list' to 'status' to 'static-list' if those actions are not advertised in the metadata
  + **fencing:** Cache metadata lookups to avoid repeated blocking during device registration
  + **fencing:** Correctly record which peer performed the fencing operation
  + **fencing:** default to 'off' when agent does not advertise 'reboot' in metadata
  + **fencing:** Do not unregister/register all stonith devices on every resource agent change
  + **fencing:** Execute all required fencing devices regardless of what topology level they are at
  + **fencing:** Fence using all required devices
  + **fencing:** Pass the correct options when looking up the history by node name
  + **fencing:** Update stonith device list only if stonith is enabled
  + **get_cluster_type:** failing concurrent tool invocations on heartbeat
  + ignore SIGPIPE when gnutls is in use
  + **iso8601:** Different logic is needed when logging and calculating durations
  + **iso8601:** Fix memory leak in duration calculation
  + **Logging:** Bootstrap daemon logging before processing arguments but configure it afterwards
  + **lrmd:** Cancel recurring operations before stop action is executed
  + **lrmd:** Expose logging variables expected by OCF agents
  + **lrmd:** Handle systemd reporting 'done' before a resource is actually stopped/started
  + **lrmd:** Merge duplicate recurring monitor operations
  + **lrmd:** Prevent OCF agents from logging to random files due to "value" of setenv() being NULL
  + **lrmd:** Provide stderr output from agents if available, otherwise fall back to stdout
  + **mainloop:** Better handle the killing of processes in the act of exiting
  + **mainloop:** Canceling in-flight operations should not fail if child process has already exited.
  + **mainloop:** Fixes use after free in process monitor code
  + **mcp:** Tell systemd not to respawn us if we exit with rc=100
  + **membership:** Avoid duplicate peer entries in the peer cache
  + **pengine:** Allow container nodes to migrate with connection resource
  + **pengine:** avoid assert by searching for stop action on correct node during LogActions
  + **pengine:** Block restart of resources if any dependent resource in a group is unmanaged
  + **pengine:** cl#5186 - Avoid running rsc on two nodes when node is fenced during migration
  + **pengine:** cl#5187 - Prevent resources in an anti-colocation from even temporarily running on a same node
  + **pengine:** cl#5200 - Before migrating utilization-using resources to a node, take off the load that will no longer run there if it's not introducing transition loop
  + **pengine:** Correctly handle origin offsets in the future
  + **pengine:** Correctly observe requires=nothing
  + **pengine:** Default sequential to TRUE for resource sets for consistency with colocation sets
  + **pengine:** Delay unfencing until after we know the state of all resources that require unfencing
  + **pengine:** Do not initiate fencing for unclean nodes when fencing is disabled
  + **pengine:** Ensure instance numbers are preserved for cloned templates
  + **pengine:** Ensure unfencing only happens once, even if the transition is interrupted
  + **pengine:** Fencing devices default to only requiring quorum in order to start
  + **pengine:** fixes invalid transition caused by clones with more than 10 instances
  + **pengine:** Force record pending for `migrate_to` actions
  + **pengine:** handles edge case where container order constraints are not honored during migration
  + **pengine:** Ignore failure-timeout only if the failed operation has on-fail="block"
  + **pengine:** Mark unrunnable stop actions as "blocked" and show the correct current locations
  + **pengine:** Memory leaks
  + **pengine:** properly handle fencing of container remote-nodes when the container is orphaned
  + **pengine:** properly place resource within a container when container is a remote-node.
  + **pengine:** Unfencing is based on device probes, there is no need to unfence when normal resources are found active
  + **pengine:** Use "#cluster-name" in rules for setting cluster-specific instance attributes
  + **pengine:** Use "#site-name" in rules for setting site-specific instance attributes
  + **remote:** Allow baremetal remote-node connection resources to migrate
  + **remote:** clear remote-node status correctly
  + **remote:** Enable migration support for baremetal connection resources by default
  + **remote:** Handle request/response ipc proxy correctly
  + **services:** Correctly reset the nice value for lrmd's children
  + **services:** Do not allow duplicate recurring op entries
  + **services:** Do not block synced service executions
  + **services:** Fixes segfault associated with cancelling in-flight recurring operations.
  + **services:** Remove cancelled recurring ops from internal lists as early as possible
  + **services:** Remove file descriptors from mainloop as soon as we have drained them
  + **services:** Reset the scheduling policy and priority for lrmd's children without replying on `SCHED_RESET_ON_FORK`
  + **services_action_cancel:** Interpret return code from `mainloop_child_kill()` correctly
  + **stonith_admin:** Ensure pointers passed to sscanf() are properly initialized
  + `stonith_api_time_helper` now returns when the most recent fencing operation completed
  + **systemd:** Prevent use-of-NULL when determining if an agent exists
  + **systemd:** Try to handle dbus actions that complete prior to configuring a callback
  + **Tools:** Non-daemons shouldn't abort just because xml parsing failed
  + **Upstart:** Allow comilation with glib versions older than 2.28
  + **Upstart:** Do not attempt upstart jobs if we cannot connect to dbus
  + When data was old, it fixed so that the newest cib might not be acquired.
  + **xml:** Check all available schemas when doing upgrades
  + **xml:** Correctly determine the lowest allowed schema version
  + **xml:** Correctly enforce ACLs after a replace operation
  + **xml:** Correctly infer attribute changes after a replace operation
  + **xml:** Create the correct diff when only part of a document is changed
  + **xml:** Detect attribute ordering changes
  + **xml:** Detect content that is added and removed in the same update
  + **xml:** Do not prune meaningful leaves from v1 patchsets
  + **xml:** Empty patchsets are considered to have applied cleanly
  + **xml:** Ensure patches always have version details set
  + **xml:** Find the minimal set of changes when part of a document is replaced
  + **xml:** If validate-with is missing, we find the most recent schema that accepts it and go from there
  + **xml:** Introduce a 'move' primitive for v2 patch sets
  + **xml:** Preserve the attribute order in the patch for subsequent digest validation
  + **xml:** Resolve memory leak when logging xml blobs
  + **xml:** Update xml validation to allow '<node type=remote />'


# Pacemaker-1.1.11 (13 Feb 2014)
- 462 commits with 147 files changed, 6810 insertions(+), 4057 deletions(-)

## Features added since Pacemaker-1.1.10


  + **attrd:** A truly atomic version of attrd for use where CPG is used for cluster communication
  + **cib:** Allow values to be added/updated and removed in a single update
  + **cib:** Support XML comments in diffs
  + **Core:** Allow blackbox logging to be disabled with SIGUSR2
  + **crmd:** Do not block on proxied calls from `pacemaker_remoted`
  + **crmd:** Enable cluster-wide throttling when the cib heavily exceeds its target load
  + **crmd:** Make the per-node action limit directly configurable in the CIB
  + **crmd:** Slow down recovery on nodes with IO load
  + **crmd:** Track CPU usage on cluster nodes and slow down recovery on nodes with high CPU/IO load
  + **crm_mon:** add `--hide-headers` option to hide all headers
  + **crm_node:** Display partition output in sorted order
  + **crm_report:** Collect logs directly from journald if available
  + **Fencing:** On timeout, clean up the agent's entire process group
  + **Fencing:** Support agents that need the host to be unfenced at startup
  + **ipc:** Raise the default buffer size to 128k
  + **PE:** Add a special attribute for distinguishing between real nodes and containers in constraint rules
  + **PE:** Allow location constraints to take a regex pattern to match against resource IDs
  + **pengine:** Distinguish between the agent being missing and something the agent needs being missing
  + **remote:** Properly version the remote connection protocol

## Changes since Pacemaker-1.1.10


  + Bug rhbz#1011618 - Consistently use 'Slave' as the role for unpromoted master/slave resources
  + Bug rhbz#1057697 - Use native DBus library for systemd and upstart support to avoid problematic use of threads
  + **attrd:** Any variable called 'cluster' makes the daemon crash before reaching main()
  + **attrd:** Avoid infinite write loop for unknown peers
  + **attrd:** Drop all attributes for peers that left the cluster
  + **attrd:** Give remote-nodes ability to set attributes with attrd
  + **attrd:** Prevent inflation of attribute dampen intervals
  + **attrd:** Support SI units for attribute dampening
  + **pengine:** Don't prevent clones from running due to dependent resources
    (bug cl#5171)
  + **corosync:** Attempt to retrieve a peer's node name if it is not already
    known (bug cl#5179)
  + **corosync:** Ensure node IDs are written to the CIB as unsigned integers
    (bug cl#5181)
  + **tools:** Handle `crm_resource --ban` for master/slave resources as
    advertised (bug rhbz#902407)
  + **cib:** Correctly check for archived configuration files
  + **cib:** Correctly log short-form xml diffs
  + **cib:** Fix remote cib based on TLS
  + **cibadmin:** Report errors during sign-off
  + **cli:** Do not enabled blackbox for cli tools
  + **cluster:** Fix segfault on removing a node
  + **cman:** Do not start pacemaker if cman startup fails
  + **cman:** Start clvmd and friends from the init script if enabled
  + Command-line tools should stop after an assertion failure
  + **controld:** Use the correct variant of `dlm_controld` for corosync-2 clusters
  + **cpg:** Correctly set the group name length
  + **cpg:** Ensure the CPG group is always null-terminated
  + **cpg:** Only process one message at a time to allow other priority jobs to be performed
  + **crmd:** Correctly observe the configured batch-limit
  + **crmd:** Correctly update expected state when the previous DC shuts down
  + **crmd:** Correcty update the history cache when recurring ops change their return code
  + **crmd:** Don't add `node_state` to cib, if we have not seen or fenced this node yet
  + **crmd:** don't segfault on shutdown when using heartbeat
  + **crmd:** Prevent recurring monitors being cancelled due to notify operations
  + **crmd:** Reliably detect and act on reprobe operations from the policy engine
  + **crmd:** When a peer expectedly shuts down, record the new join and expected states into the cib
  + **crmd:** When the DC gracefully shuts down, record the new expected state into the cib
  + **crm_attribute:** Do not swallow hostname lookup failures
  + **crm_mon:** Do not display duplicates of failed actions
  + **crm_mon:** Reduce flickering in interactive mode
  + **crm_resource:** Observe `--master` modifier for `--move`
  + **crm_resource:** Provide a meaningful error if `--master` is used for primitives and groups
  + **fencing:** Allow fencing for node after topology entries are deleted
  + **fencing:** Apply correct score to the resource of group
  + **fencing:** Ignore changes to non-fencing resources
  + **fencing:** Observe `pcmk_host_list` during automatic unfencing
  + **fencing:** Put all fencing agent processes into their own process group
  + **fencing:** Wait until all possible replies are recieved before continuing with unverified devices
  + **ipc:** Compress msgs based on client's actual max send size
  + **ipc:** Have the ipc server enforce a minimum buffer size all clients must use.
  + **iso8601:** Prevent dates from jumping backwards a day in some timezones
  + **lrmd:** Correctly calculate metadata for the 'service' class
  + **lrmd:** Correctly cancel monitor actions for lsb/systemd/service resources on cleaning up
  + **mcp:** Remove LSB hints that instruct chkconfig to start pacemaker at boot time
  + **mcp:** Some distros complain when LSB scripts do not include Default-Start/Stop directives
  + **pengine:** Allow fencing of baremetal remote nodes
  + **pengine:** cl#5186 - Avoid running rsc on two nodes when node is fenced during migration
  + **pengine:** Correctly account for the location preferences of things colocated with a group
  + **pengine:** Correctly handle demotion of grouped masters that are partially demoted
  + **pengine:** Disable container node probes due to constraint conflicts
  + **pengine:** Do not allow colocation with blocked clone instances
  + **pengine:** Do not re-allocate clone instances that are blocked in the Stopped state
  + **pengine:** Do not restart resources that depend on unmanaged resources
  + **pengine:** Force record pending for `migrate_to` actions
  + **pengine:** Location constraints with role=Started should prevent masters from running at all
  + **pengine:** Order demote/promote of resources on remote nodes to happen only once the connection is up
  + **pengine:** Properly handle orphaned multistate resources living on remote-nodes
  + **pengine:** Properly shutdown orphaned remote connection resources
  + **pengine:** Recover unexpectedly running container nodes.
  + **remote:** Add support for ipv6 into `pacemaker_remote` daemon
  + **remote:** Handle endian changes between client and server and improve forward compatibility
  + **services:** Fixes segfault associated with cancelling in-flight recurring operations.
  + **services:** Reset the scheduling policy and priority for lrmd's children without replying on `SCHED_RESET_ON_FORK`

# Pacemaker-1.1.10 (26 Jul 2013)
- 602 commits with 143 files changed, 8162 insertions(+), 5159 deletions(-)

## Features added since Pacemaker-1.1.9

  + **Core:** Convert all exit codes to positive errno values
  + **crm_error:** Add the ability to list and print error symbols
  + **crm_resource:** Allow individual resources to be reprobed
  + **crm_resource:** Allow options to be set recursively
  + **crm_resource:** Implement `--ban` for moving resources away from nodes
    and `--clear` (replaces `--unmove`)
  + **crm_resource:** Support OCF tracing when using
    `--force-(check|start|stop)`
  + **PE:** Allow active nodes in our current membership to be fenced without quorum
  + **PE:** Suppress meaningless IDs when displaying anonymous clone status
  + Turn off auto-respawning of systemd services when the cluster starts them
  + **PE:** Support maintenance mode for a single node (bug cl#5128)

## Changes since Pacemaker-1.1.9

  + **crmd:** cib: stonithd: Memory leaks resolved and improved use of glib reference counting
  + **attrd:** Fixes deleted attributes during dc election
  + Bug cf#5153 - Correctly display clone failcounts in `crm_mon`
  + **Bug cl#5133 - pengine:** Correctly observe on-fail=block for failed demote operation
  + **Bug cl#5148 - legacy:** Correctly remove a node that used to have a different nodeid
  + Bug cl#5151 - Ensure node names are consistently compared without case
  + **Bug cl#5152 - crmd:** Correctly clean up fenced nodes during membership changes
  + Bug cl#5154 - Do not expire failures when on-fail=block is present
  + **Bug cl#5155 - pengine:** Block the stop of resources if any depending resource is unmanaged
  + Bug cl#5157 - Allow migration in the absence of some colocation constraints
  + **Bug cl#5161 - crmd:** Prevent memory leak in operation cache
  + **Bug cl#5164 - crmd:** Fixes crash when using pacemaker-remote
  + **Bug cl#5164 - pengine:** Fixes segfault when calculating transition with remote-nodes.
  + **Bug cl#5167 - `crm_mon:**` Only print "stopped" node list for incomplete clone sets
  + Bug cl#5168 - Prevent clones from being bounced around the cluster due to location constraints
  + Bug cl#5170 - Correctly support on-fail=block for clones
  + **cib:** Correctly read back archived configurations if the primary is corrupted
  + **cib:** The result is not valid when diffs fail to apply cleanly for CLI tools
  + **cib:** Restore the ability to embed comments in the configuration
  + **cluster:** Detect and warn about node names with capitals
  + **cman:** Do not pretend we know the state of nodes we've never seen
  + **cman:** Do not unconditionally start cman if it is already running
  + **cman:** Support non-blocking CPG calls
  + **Core:** Ensure the blackbox is saved on abnormal program termination
  + **corosync:** Detect the loss of members for which we only know the nodeid
  + **corosync:** Do not pretend we know the state of nodes we've never seen
  + **corosync:** Ensure removed peers are erased from all caches
  + **corosync:** Nodes that can persist in sending CPG messages must be alive afterall
  + **crmd:** Do not get stuck in `S_POLICY_ENGINE` if a node we couldn't fence returns
  + **crmd:** Do not update fail-count and last-failure for old failures
  + **crmd:** Ensure all membership operations can complete while trying to cancel a transition
  + **crmd:** Ensure operations for cleaned up resources don't block recovery
  + **crmd:** Ensure we return to a stable state if there have been too many fencing failures
  + **crmd:** Initiate node shutdown if another node claims to have successfully fenced us
  + **crmd:** Prevent messages for remote crmd clients from being relayed to wrong daemons
  + **crmd:** Properly handle recurring monitor operations for remote-node agent
  + **crmd:** Store last-run and last-rc-change for all operations
  + **crm_mon:** Ensure stale pid files are updated when a new process is started
  + **crm_report:** Correctly collect logs when 'uname -n' reports fully qualified names
  + **fencing:** Fail the operation once all peers have been exhausted
  + **fencing:** Restore the ability to manually confirm that fencing completed
  + **ipc:** Allow unpriviliged clients to clean up after server failures
  + **ipc:** Restore the ability for members of the haclient group to connect to the cluster
  + **legacy:** Support "crm_node `--remove"` with a node name for corosync plugin (bnc#805278)
  + **lrmd:** Default to the upstream location for resource agent scratch directory
  + **lrmd:** Pass errors from lsb metadata generation back to the caller
  + **pengine:** Correctly handle resources that recover before we operate on them
  + **pengine:** Delete the old resource state on every node whenever the resource type is changed
  + **pengine:** Detect constraints with inappropriate actions (ie. promote for a clone)
  + **pengine:** Ensure per-node resource parameters are used during probes
  + **pengine:** If fencing is unavailable or disabled, block further recovery for resources that fail to stop
  + **pengine:** Implement the rest of `get_timet_now()` and rename to `get_effective_time`
  + **pengine:** Re-initiate `_active_` recurring monitors that previously failed but have timed out
  + **remote:** Workaround for inconsistent tls handshake behavior between gnutls versions
  + **systemd:** Ensure we get shut down correctly by systemd
  + **systemd:** Reload systemd after adding/removing override files for cluster services
  + **xml:** Check for and replace non-printing characters with their octal equivalent while exporting xml text
  + **xml:** Prevent lockups by setting a more reliable buffer allocation strategy

# Pacemaker-1.1.9 (08 Mar 2013)
- 731 commits with 1301 files changed, 92909 insertions(+), 57455 deletions(-)

## Features added in Pacemaker-1.1.9

  + **corosync:** Allow cman and corosync 2.0 nodes to use a name other than uname()
  + **corosync:** Use queues to avoid blocking when sending CPG messages
  + **ipc:** Compress messages that exceed the configured IPC message limit
  + **ipc:** Use queues to prevent slow clients from blocking the server
  + **ipc:** Use shared memory by default
  + **lrmd:** Support nagios remote monitoring
  + **lrmd:** Pacemaker Remote Daemon for extending pacemaker functionality outside corosync cluster.
  + **pengine:** Check for master/slave resources that are not OCF agents
  + **pengine:** Support a 'requires' resource meta-attribute for controlling whether it needs quorum, fencing or nothing
  + **pengine:** Support for resource container
  + **pengine:** Support resources that require unfencing before start

## Changes since Pacemaker-1.1.8

  + **attrd:** Correctly handle deletion of non-existant attributes
  + Bug cl#5135 - Improved detection of the active cluster type
  + Bug rhbz#913093 - Use `crm_node` instead of uname
  + **cib:** Avoid use-after-free by correctly support `cib_no_children` for non-xpath queries
  + **cib:** Correctly process XML diff's involving element removal
  + **cib:** Performance improvements for non-DC nodes
  + **cib:** Prevent error message by correctly handling peer replies
  + **cib:** Prevent ordering changes when applying xml diffs
  + **cib:** Remove text nodes from cib replace operations
  + **cluster:** Detect node name collisions in corosync
  + **cluster:** Preserve corosync membership state when matching node name/id entries
  + **cman:** Force fenced to terminate on shutdown
  + **cman:** Ignore qdisk 'nodes'
  + **core:** Drop per-user core directories
  + **corosync:** Avoid errors when closing failed connections
  + **corosync:** Ensure peer state is preserved when matching names to nodeids
  + **corosync:** Clean up CMAP connections after querying node name
  + **corosync:** Correctly detect corosync 2.0 clusters even if we don't have permission to access it
  + **crmd:** Bug cl#5144 - Do not updated the expected status of failed nodes
  + **crmd:** Correctly determin if cluster disconnection was abnormal
  + **crmd:** Correctly relay messages for remote clients (bnc#805626, bnc#804704)
  + **crmd:** Correctly stall the FSA when waiting for additional inputs
  + **crmd:** Detect and recover when we are evicted from CPG
  + **crmd:** Differentiate between a node that is up and coming up in `peer_update_callback()`
  + **crmd:** Have cib operation timeouts scale with node count
  + **crmd:** Improved continue/wait logic in `do_dc_join_finalize()`
  + **crmd:** Prevent election storms caused by getrusage() values being too close
  + **crmd:** Prevent timeouts when performing pacemaker level membership negotiation
  + **crmd:** Prevent use-after-free of `fsa_message_queue` during exit
  + **crmd:** Store all current actions when stalling the FSA
  + **crm_mon:** Do not try to render a blank cib and indicate the previous output is now stale
  + **crm_mon:** Fixes `crm_mon` crash when using snmp traps.
  + **crm_mon:** Look for the correct error codes when applying configuration updates
  + **crm_report:** Ensure policy engine logs are found
  + **crm_report:** Fix node list detection
  + **crm_resource:** Have `crm_resource` generate a valid transition key when sending resource commands to the crmd
  + **date/time:** Bug cl#5118 - Correctly convert seconds-since-epoch to the current time
  + **fencing:** Attempt to provide more information that just 'generic error' for failed actions
  + **fencing:** Correctly record completed but previously unknown fencing operations
  + **fencing:** Correctly terminate when all device options have been exhausted
  + **fencing:** cov#739453 - String not null terminated
  + **fencing:** Do not merge new fencing requests with stale ones from dead nodes
  + **fencing:** Do not start fencing until entire device topology is found or query results timeout.
  + **fencing:** Do not wait for the query timeout if all replies have arrived
  + **fencing:** Fix passing of parameters from CMAN containing '='
  + **fencing:** Fix non-comparison when sorting devices by priority
  + **fencing:** On failure, only try a topology device once from the remote level.
  + **fencing:** Only try peers for non-topology based operations once
  + **fencing:** Retry stonith device for duration of action's timeout period.
  + **heartbeat:** Remove incorrect assert during cluster connect
  + **ipc:** Bug cl#5110 - Prevent 100% CPU usage when looking for synchronous replies
  + **ipc:** Use 50k as the default compression threshold
  + **legacy:** Prevent assertion failure on routing ais messages (bnc#805626)
  + **legacy:** Re-enable logging from the pacemaker plugin
  + **legacy:** Relax the 'active' check for plugin based clusters to avoid false negatives
  + **legacy:** Skip peer process check if the process list is empty in `crm_is_corosync_peer_active()`
  + **mcp:** Only define `HA_DEBUGLOG` to avoid agent calls to `ocf_log` printing everything twice
  + **mcp:** Re-attach to existing pacemaker components when mcp fails
  + **pengine:** Any location constraint for the slave role applies to all roles
  + **pengine:** Avoid leaking memory when cleaning up failcounts and using containers
  + **pengine:** Bug cl#5101 - Ensure stop order is preserved for partially active groups
  + **pengine:** Bug cl#5140 - Allow set members to be stopped when the subseqent set has require-all=false
  + **pengine:** Bug cl#5143 - Prevent shuffling of anonymous master/slave instances
  + **pengine:** Bug rhbz#880249 - Ensure orphan masters are demoted before being stopped
  + **pengine:** Bug rhbz#880249 - Teach the PE how to recover masters into primitives
  + **pengine:** cl#5025 - Automatically clear failcount for start/monitor failures after resource parameters change
  + **pengine:** cl#5099 - Probe operation uses the timeout value from the minimum interval monitor by default (#bnc776386)
  + **pengine:** cl#5111 - When clone/master child rsc has on-fail=stop, insure all children stop on failure.
  + **pengine:** cl#5142 - Do not delete orphaned children of an anonymous clone
  + **pengine:** Correctly unpack active anonymous clones
  + **pengine:** Ensure previous migrations are closed out before attempting another one
  + **pengine:** Introducing the whitebox container resources feature
  + **pengine:** Prevent double-free for cloned primitive from template
  + **pengine:** Process `rsc_ticket` dependencies earlier for correctly allocating resources (bnc#802307)
  + **pengine:** Remove special cases for fencing resources
  + **pengine:** rhbz#902459 - Remove rsc node status for orphan resources
  + **systemd:** Gracefully handle unexpected DBus return types
  + Replace the use of the insecure mktemp(3) with mkstemp(3)

# Pacemaker-1.1.8 (20 Sep 2012)
- 1019 commits with 2107 files changed, 117258 insertions(+), 73606 deletions(-)

## Changes since Pacemaker-1.1.7

  + All APIs have been cleaned up and reduced to essentials
  + Pacemaker now includes a replacement lrmd that supports systemd and upstart agents
  + Config and state files (cib.xml, PE inputs and core files) have moved to new locations
  + The crm shell has become a separate project and no longer included with Pacemaker
  + All daemons/tools now have a unified set of error codes based on errno.h (see `crm_error)`
  + **Core:** Bug cl#5032 - Rewrite the iso8601 date handling code
  + **Core:** Correctly extract the version details from a diff
  + **Core:** Log blackbox contents, if enabled, when an error occurs
  + **Core:** Only `LOG_NOTICE` and higher are sent to syslog
  + **Core:** Replace use of IPC from clplumbing with IPC from libqb
  + **Core:** SIGUSR1 now enables blackbox logging, SIGTRAP to write out
  + **Core:** Support a blackbox for additional logging detail after crashes/errors
  + Promote support for advanced fencing logic to the stable schema
  + Promote support for node starting scores to the stable schema
  + Promote support for service and systemd to the stable schema
  + **attrd:** Differentiate between updating all our attributes and everybody updating all theirs too
  + **attrd:** Have single-shot clients wait for an ack before disconnecting
  + **cib:** cl#5026 - Synced cib updates should not return until the cpg broadcast is complete.
  + **corosync:** Detect when the first corosync has not yet formed and handle it gracefully
  + **corosync:** Obtain a full list of configured nodes, including their names, when we connect to the quorum API
  + **corosync:** Obtain a node name from DNS if one was not already known
  + **corosync:** Populate the cib nodelist from corosync if available
  + **corosync:** Use the CFG API and DNS to determine node names if not configured in corosync.conf
  + **crmd:** Block after 10 failed fencing attempts for a node
  + **crmd:** cl#5051 - Fixes file leak in PE ipc connection initialization.
  + **crmd:** cl#5053 - Fixes fail-count not being updated properly.
  + **crmd:** cl#5057 - Restart sub-systems correctly (bnc#755671)
  + **crmd:** cl#5068 - Fixes `crm_node` -R option so it works with corosync 2.0
  + **crmd:** Correctly re-establish failed attrd connections
  + **crmd:** Detect when the quorum API isn't configured for corosync 2.0
  + **crmd:** Do not overwrite any configured node type (eg. quorum node)
  + **crmd:** Enable use of new lrmd daemon and client library in crmd.
  + **crmd:** Overhaul the way node state is recorded and updated in the CIB
  + **fencing:** Bug rhbz#853537 - Prevent use-of-NULL when the cib libraries are not available
  + **fencing:** cl#5073 - Add 'off' as an valid value for stonith-action option.
  + **fencing:** cl#5092 - Always timeout stonith operations if timeout period expires.
  + **fencing:** cl#5093 - Stonith per device timeout option
  + **fencing:** Clean up if we detect a failed connection
  + **fencing:** Delegate complex self fencing requests - we wont be around to see it to completion
  + **fencing:** Ensure all peers are notified of complex fencing op completion
  + **fencing:** Fix passing of `fence_legacy` parameters containing '='
  + **fencing:** Gracefully handle metadata requests for unknown agents
  + **fencing:** Return cached dynamic target list for busy devices.
  + **fencing:** rhbz#801355 - Abort transition on DC when external fencing operation is detected
  + **fencing:** rhbz#801355 - Merge fence requests for identical operations already in progress.
  + **fencing:** rhbz#801355 - Report fencing operations external of pacemaker to cib
  + **fencing:** Specify the action to perform using action= instead of the older option=
  + **fencing:** Stop building fake metadata for broken agents
  + **fencing:** Tolerate agents that report empty metadata in the admin tool
  + **mcp:** Correctly retry the connection to corosync on failure
  + **mcp:** Do not shut down IPC until the last client exits
  + **mcp:** Prevent use-after-free when running against corosync 1.x
  + **pengine:** Bug cl#5059 - Use the correct action's status when calculating required actions for interleaved clones
  + **pengine:** Bypass online/offline checking resource detection for ping/quorum nodes
  + **pengine:** cl#5044 - `migrate_to` no longer requires `load_stopped` for avoiding possible transition loop
  + **pengine:** cl#5069 - Honor 'on-fail=ignore' even when operation is disabled.
  + **pengine:** cl#5070 - Allow influence of promotion score when multistate rsc is left hand of colocation
  + **pengine:** cl#5072 - Fixes monitor op stopping after rsc promotion.
  + **pengine:** cl#5072 - Fixes pengine regression test failures
  + **pengine:** Correctly set the status for nodes not intended to run Pacemaker
  + **pengine:** Do not append instance numbers to anonymous clones
  + **pengine:** Fix failcount expiration
  + **pengine:** Fix memory leaks found by valgrind
  + **pengine:** Fix use-after-free and use-of-NULL errors detected by coverity
  + **pengine:** Fixes use of colocation scores other than +/- INFINITY
  + **pengine:** Improve detection of rejoining nodes
  + **pengine:** Prevent use-of-NULL when tracing is enabled
  + **pengine:** Stonith resources are allowed to start even if their probes haven't completed on partially active nodes
  + **services:** New class called 'service' which expands to the correct (LSB/systemd/upstart) standard
  + **services:** Support Asynchronous systemd/upstart actions
  + **Tools:** `crm_shadow` - Bug cl#5062 - Correctly set argv[0] when forking a shell process
  + **Tools:** `crm_report:` Always include system logs (if we can find them)

# Pacemaker-1.1.7 (28 Mar 2012)
- 513 commits with 1171 files changed, 90472 insertions(+), 19368 deletions(-)

## Changes since Pacemaker-1.1.6.1

  + **ais:** Prepare for corosync versions using IPC from libqb
  + **cib:** Correctly shutdown in the presence of peers without relying on timers
  + **cib:** Don't halt disk writes if the previous digest is missing
  + **cib:** Determine when there are no peers to respond to our shutdown request and exit
  + **cib:** Ensure no additional messages are processed after we begin terminating
  + **Cluster:** Hook up the callbacks to the corosync quorum notifications
  + **Core:** basename() may modify its input, do not pass in a constant
  + **Core:** Bug cl#5016 - Prevent failures in recurring ops from being lost
  + **Core:** Bug rhbz#800054 - Correctly retrieve heartbeat uuids
  + **Core:** Correctly determine when an XML file should be decompressed
  + **Core:** Correctly track the length of a string without reading from uninitialzied memory (valgrind)
  + **Core:** Ensure signals are handled eventually in the absense of timer sources or IPC messages
  + **Core:** Prevent use-of-NULL in `crm_update_peer()`
  + **Core:** Strip text nodes from on disk xml files
  + **Core:** Support libqb for logging
  + **corosync:** Consistently set the correct uuid with `get_node_uuid()`
  + **Corosync:** Correctly disconnect from corosync variants
  + **Corosync:** Correctly extract the node id from membership udpates
  + **corosync:** Correctly infer lost members from the quorum API
  + **Corosync:** Default to using the nodeid as the node's uuid (instead of uname)
  + **corosync:** Ensure we catch nodes that leave the membership, even if the ringid doesn't change
  + **corosync:** Hook up CPG membership
  + **corosync:** Relax a development assert and gracefully handle the error condition
  + **corosync:** Remove deprecated member of the CFG API
  + **corosync:** Treat `CS_ERR_QUEUE_FULL` the same as `CS_ERR_TRY_AGAIN`
  + **corosync:** Unset the process list when nodes dissappear on us
  + **crmd:** Also purge fencing results when we enter `S_NOT_DC`
  + **crmd:** Bug cl#5015 - Remove the failed operation as well as the resulting fail-count and last-failure attributes
  + **crmd:** Correctly determine when a node can suicide with fencing
  + **crmd:** Election - perform the age comparison only once
  + **crmd:** Fast-track shutdown if we couldn't request it via attrd
  + **crmd:** Leave it up to the PE to decide which ops can/cannot be reload
  + **crmd:** Prevent use-after-free when calling `delete_resource` due to `CRM_OP_REPROBE`
  + **crmd:** Supply format arguments in the correct order
  + **fencing:** Add missing format parameter
  + **fencing:** Add the fencing topology section to the 1.1 configuration schema
  + **fencing:** `fence_legacy` - Drop spurilous host argument from status query
  + **fencing:** `fence_legacy` - Ensure port is available as an environment variable when calling monitor
  + **fencing:** `fence_pcmk` - don't block if nothing is specified on stdin
  + **fencing:** Fix log format error
  + **fencing:** Fix segfault caused by passing garbage to dlsym()
  + **fencing:** Fix use-of-NULL in `process_remote_stonith_query()`
  + **fencing:** Fix use-of-NULL when listing installed devices
  + **fencing:** Implement support for advanced fencing topologies: eg. kdump || (network && disk) || power
  + **fencing:** More gracefully handle failed 'list' operations for devices that only support a single connection
  + **fencing:** Prevent duplicate free when listing devices
  + **fencing:** Prevent uninitialized pointers being passed to free
  + **fencing:** Prevent use-after-free, we may need the query result for subsequent operations
  + **fencing:** Provide enough data to construct an entry in the node's fencing history
  + **fencing:** Standardize on /one/ method for clients to request members be fenced
  + **fencing:** Supress errors when listing all registered devices
  + **mcp:** `corosync_cfg_state_track` was removed from the corosync API, luckily we didnt use it for anything
  + **mcp:** Do not specify a WorkingDirectory in the systemd unit file - startup fails if its not available
  + **mcp:** Set the `HA_quorum_type` env variable consistently with our corosync plugin
  + **mcp:** Shut down if one of our child processes can/should not be respawned
  + **pengine:** Bug cl#5000 - Ensure ordering is preserved when depending on partial sets
  + **pengine:** Bug cl#5028 - Unmanaged services should block shutdown unless in maintenance mode
  + **pengine:** Bug cl#5038 - Prevent restart of anonymous clones when clone-max decreases
  + **pengine:** Bug cl#5007 - Fixes use of colocation constraints with multi-state resources
  + **pengine:** Bug cl#5014 - Prevent asymmetrical order constraints from causing resource stops
  + **pengine:** Bug cl#5000 - Implements ability to create `rsc_order` constraint sets such that A can start after B or C has started.
  + **pengine:** Correctly migrate a resource that has just migrated
  + **pengine:** Correct return from error path
  + **pengine:** Detect reloads of previously migrated resources
  + **pengine:** Ensure post-migration stop actions occur before node shutdown
  + **pengine:** Log as loudly as possible when we cannot shut down a cluster node
  + **pengine:** Reload of a resource no longer causes a restart of dependent resources
  + **pengine:** Support limiting the number of concurrent live migrations
  + **pengine:** Support referencing templates in constraints
  + **pengine:** Support of referencing resource templates in resource sets
  + **pengine:** Support to make tickets standby for relinquishing tickets gracefully
  + **stonith:** A "start" operation of a stonith resource does a "monitor" on the device beyond registering it
  + **stonith:** Bug rhbz#745526 - Ensure `stonith_admin` actually gets called by `fence_pcmk`
  + **Stonith:** Ensure all nodes receive and deliver notifications of the manual override
  + **stonith:** Fix the stonith timeout issue (cl#5009, bnc#727498)
  + **Stonith:** Implement a manual override for when nodes are known to be safely off
  + **Tools:** Bug cl#5003 - Prevent use-after-free in `crm_simlate`
  + **Tools:** `crm_mon` - Support to display tickets (based on Yuusuke Iida's work)
  + **Tools:** `crm_simulate` - Support to grant/revoke/standby/activate tickets from the new ticket state section
  + **Tools:** Implement `crm_node` functionality for native corosync
  + Fix a number of potential problems reported by coverity

# Pacemaker-1.1.6 (31 Aug 2011)
- 376 commits with 1761 files changed, 36259 insertions(+), 140578 deletions(-)

## Changes since Pacemaker-1.1.5

  + **ais:** check for retryable errors when dispatching AIS messages
  + **ais:** Correctly disconnect from Corosync and Cman based clusters
  + **ais:** Followup to previous patch - Ensure we drain the corosync queue of messages when Glib tells us there is input
  + **ais:** Handle IPC error before checking for NULL data (bnc#702907)
  + **cib:** Check the validation version before adding the originator details of a CIB change
  + **cib:** Remove disconnected remote connections from mainloop
  + **cman:** Correctly override existing fenced operations
  + **cman:** Dequeue all the cman emitted events and not only the first one leaving the others in the event's queue.
  + **cman:** Don't call `fenced_join` and `fenced_leave` when notifying cman of a fencing event.
  + **cman:** We need to run the crmd as root for CMAN so that we can ACK fencing operations
  + **Core:** Cancelled and pending operations do not count as failed
  + **Core:** Ensure there is sufficient space for EOS when building short-form option strings
  + **Core:** Fix variable expansion in pkg-config files
  + **Core:** Partial revert of accidental commit in previous patch
  + **Core:** Use dlopen to load heartbeat libraries on-demand
  + **crmd:** Bug lf#2509 - Watch for config option changes from the CIB even if we're not the DC
  + **crmd:** Bug lf#2528 - Introduce a slight delay when creating a transition to allow attrd time to perform its updates
  + **crmd:** Bug lf#2559 - Fail actions that were scheduled for a failed/fenced node
  + **crmd:** Bug lf#2584 - Allow nodes to fence themselves if they're the last one standing
  + **crmd:** Bug lf#2632 - Correctly handle nodes that return faster than stonith
  + **crmd:** Cancel timers for actions that were pending on dead nodes
  + **crmd:** Catch fence operations that claim to succeed but did not really
  + **crmd:** Do not wait for actions that were pending on dead nodes
  + **crmd:** Ensure we do not attempt to perform action on failed nodes
  + **crmd:** Prevent use-of-NULL by `g_hash_table_iter_next()`
  + **crmd:** Recurring actions shouldn't cause the last non-recurring action to be forgotten
  + **crmd:** Store only the last and last failed operation in the CIB
  + **mcp:** dirname() modifies the input path - pass in a copy of the logfile path
  + **mcp:** Enable stack detection logic instead of forcing 'corosync'
  + **mcp:** Fix spelling mistake in systemd service script that prevents shutdown
  + **mcp:** Shut down if corosync becomes unavailable
  + **mcp:** systemd control file is now functional
  + **pengine:** Before migrating an utilization-using resource to a node, take off the load which will no longer run there (lf#2599, bnc#695440)
  + **pengine:** Before migrating an utilization-using resource to a node, take off the load which will no longer run there (regression tests) (lf#2599, bnc#695440)
  + **pengine:** Bug lf#2574 - Prevent shuffling by choosing the correct clone instance to stop
  + **pengine:** Bug lf#2575 - Use uname for migration variables, id is a UUID on heartbeat
  + **pengine:** Bug lf#2581 - Avoid group restart when clone (re)starts on an unrelated node
  + **pengine:** Bug lf#2613, lf#2619 - Group migration after failures and non-default utilization policies
  + **pengine:** Bug suse#707150 - Prevent services being active if dependencies on clones are not satisfied
  + **pengine:** Correctly recognise which recurring operations are currently active
  + **pengine:** Demote from Master does not clear previous errors
  + **pengine:** Ensure restarts due to definition changes cause the start action to be re-issued not probes
  + **pengine:** Ensure role is preserved for unmanaged resources
  + **pengine:** Ensure unmanaged resources have the correct role set so the correct monitor operation is chosen
  + **pengine:** Fix memory leak for re-allocated resources reported by valgrind
  + **pengine:** Implement cluster ticket and deadman
  + **pengine:** Implement resource template
  + **pengine:** Correctly determine the state of multi-state resources with a partial operation history
  + **pengine:** Only allocate master/slave resources once
  + **pengine:** Partial revert of 'Minor code cleanup CS: cf6bca32376c On: 2011-08-15'
  + **pengine:** Resolve memory leak reported by valgrind
  + **pengine:** Restore the ability to save inputs to disk
  + **Shell:** implement -w,--wait option to wait for the transition to finish
  + **Shell:** repair template list command
  + **Shell:** set of commands to examine logs, reports, etc
  + **Stonith:** Consolidate `pcmk_host_map` into `run_stonith_agent` so that it is applied consistently
  + **Stonith:** Deprecate `pcmk_arg_map` for the saner `pcmk_host_argument`
  + **Stonith:** Fix use-of-NULL by `g_hash_table_lookup`
  + **Stonith:** Improved `pcmk_host_map` parsing
  + **Stonith:** Prevent use-of-NULL by `g_hash_table_lookup`
  + **Stonith:** Prevent use-of-NULL when no Linux-HA stonith agents are present
  + **stonith:** Add missing entries to `stonith_error2string()`
  + **Stonith:** Correctly finish sending agent options if the initial write is interrupted
  + **stonith:** Correctly handle synchronous calls
  + **stonith:** Coverity - Correctly construct result list for the query API call
  + **stonith:** Coverity - Remove badly constructed memory allocation from the query API call
  + **stonith:** Ensure completed operations are recorded as such in the history
  + **Stonith:** Ensure device parameters are passed to the daemon during registration
  + **stonith:** Fix use-of-NULL in `stonith_api_device_list()`
  + **stonith:** `stonith_admin` - Prevent use of uninitialized pointer by `--history` command
  + **Tools:** Bug lf#2528 - Make progress when `attrd_updater` is called repeatedly within the dampen interval but with the same value
  + **Tools:** `crm_report` - Correctly extract data from the local node
  + **Tools:** `crm_report` - Remove newlines when detecting the node list
  + **Tools:** `crm_report` - Repair the ability to extract data from the local machine
  + **Tools:** `crm_report` - Report on all detected backtraces

# Pacemaker-1.1.5 (11 Feb 2011)
- 184 commits with 605 files changed, 46103 insertions(+), 26417 deletions(-)

## Changes since Pacemaker-1.1.4

  + Add the ability to delegate sub-sections of the cluster to non-root users via ACLs
    Needs to be enabled at compile time, not enabled by default.
  + **ais:** Bug lf#2550 - Report failed processes immediately
  + **Core:** Prevent recently introduced use-after-free in `replace_xml_child()`
  + **Core:** Reinstate the logic that skips past non-XML_ELEMENT_NODE children
  + **Core:** Remove extra calls to xmlCleanupParser resulting in use-after-free
  + **Core:** Repair reference to child-of-child after removal of `xml_child_iter_filter` from `get_message_xml()`
  + **crmd:** Bug lf#2545 - Ensure notify variables are accurate for stop operations
  + **crmd:** Cancel recurring operations while we're still connected to the lrmd
  + **crmd:** Reschedule the `PE_START` action if its not already running when we try to use it
  + **crmd:** Update failcount for failed promote and demote operations
  + **pengine:** Bug lf#2445 - Avoid relying on stickness for stable clone placement
  + **pengine:** Bug lf#2445 - Do not override configured clone stickiness values
  + **pengine:** Bug lf#2493 - Don't imply colocation requirements when applying ordering constraints with clones
  + **pengine:** Bug lf#2495 - Prevent segfault by validating the contents of ordering sets
  + **pengine:** Bug lf#2508 - Correctly reconstruct the status of anonymous cloned groups
  + **pengine:** Bug lf#2518 - Avoid spamming the logs with errors for orphan resources
  + **pengine:** Bug lf#2544 - Prevent unstable clone placement by factoring in the current node's score before all others
  + **pengine:** Bug lf#2554 - target-role alone is not sufficient to promote resources
  + **pengine:** Correct `target_rc` for probes of inactive resources (fix regression introduced by cs:ac3f03006e95)
  + **pengine:** Ensure that fencing has completed for stop actions on stonith-dependent resources (lf#2551)
  + **pengine:** Only update the node's promotion score if the resource is active there
  + **pengine:** Only use the promotion score from the current clone instance
  + **pengine:** Prevent use-of-NULL resulting from variable shadowing spotted by Coverity
  + **pengine:** Prevent use-of-NULL when there is status for an undefined node
  + **pengine:** Prevet use-after-free resulting from unintended recursion when chosing a node to promote master/slave resources
  + **Shell:** don't create empty optional sections (bnc#665131)
  + **Stonith:** Teach `stonith_admin` to automagically obtain the current node attributes for the target from the CIB
  + **tools:** Bug lf#2527 - Prevent use-of-NULL in `crm_simulate`
  + **Tools:** Prevent `crm_resource` commands from being lost due to the use of `cib_scope_local`

# Pacemaker-1.1.4 (20 Oct 2010)
- 169 commits with 772 files changed, 56172 insertions(+), 39309 deletions(-)

## Changes since Pacemaker-1.1.3

  + Italian translation of Clusters from Scratch
  + Significant performance enhancements to the Policy Engine and CIB
  + **cib:** Bug lf#2506 - Don't remove client's when notifications fail, they might just be too big
  + **cib:** Drop invalid/failed connections from the client hashtable
  + **cib:** Ensure all diffs sent to peers have sufficient ordering information
  + **cib:** Ensure non-change diffs can preserve the ordering on the other side
  + **cib:** Fix the feature set check
  + **cib:** Include version information on our synthesised diffs when nothing changed
  + **cib:** Optimize the way we detect group/set ordering changes - 15% speedup
  + **cib:** Prevent false detection of config updates with the new diff format
  + **cib:** Reduce unnecessary copying when comparing xml objects
  + **cib:** Repair the processing of updates sent from peer nodes
  + **cib:** Revert part of a recent commit that purged still valid connections
  + **cib:** The feature set version check is only valid if the current value is non-NULL
  + **Core:** Actually removing diff markers is necessary
  + **Core:** Bug lf#2506 - Drop the compression limit because Heartbeat's IPC code sucks
  + **Core:** Cache Relax-NG schemas - profiling indicates many cycles are wasted needlessly re-parsing them
  + **Core:** Correctly compare against `crm_log_level` in the logging macros
  + **Core:** Correctly extract the version details from a diff
  + **Core:** Correctly hook up the RNG schema cache
  + **Core:** Correctly use `lazy_xml_sort()` for v2 digests
  + **Core:** Don't compress large payload elements unless we're approaching message limits
  + **Core:** Don't insert empty ID tags when applying diffs
  + **Core:** Enable the improve v2 digests
  + **Core:** Ensure ordering is preserved when applying diffs
  + **Core:** Fix the `CRM_CHECK` macro
  + **Core:** Modify the v2 digest algorithm so that some fields are sorted
  + **Core:** Prevent use-after-free when creating a CIB update for a timed out action
  + **Core:** Prevent use-of-NULL when cleaning up RelaxNG data structures
  + **Core:** Provide significant performance improvements by implementing versioned diffs and digests
  + **crmd:** All pending operations should be recorded, even recurring ones with high start delays
  + **crmd:** Don't abort transitions when probes are completed on a node
  + **crmd:** Don't hide stop events that time out - allowing faster recovery in the presence of overloaded hosts
  + **crmd:** Ensure the CIB is always writable on the DC by removing a timing hole
  + **crmd:** Include the correct transition details for timed out operations
  + **crmd:** Prevent use of NULL by making copies of the operation's hash table
  + **crmd:** There's no need to check the cib version from the 'added' part of diff updates
  + **crmd:** Use the supplied timeout for stop actions
  + **mcp:** Ensure valgrind is able to log its output somewhere
  + **mcp:** Use 99/01 for the start/stop sequence to avoid problems with services (such as libvirtd) started by init - Patch from Vladislav Bogdanov
  + **pengine:** Ensure fencing of the DC preceeds the `STONITH_DONE` operation
  + **pengine:** Fix memory leak introduced as part of the conversion to GHashTables
  + **pengine:** Fix memory leak when processing completed migration actions
  + **pengine:** Fix typo leading to use-of-NULL in the new ordering code
  + **pengine:** Free memory in recently introduced helper function
  + **pengine:** lf#2478 - Implement improved handling and recovery of atomic resource migrations
  + **pengine:** Obtain massive speedup by prepending to the list of ordering constraints (which can grow quite large)
  + **pengine:** Optimize the logic for deciding which non-grouped anonymous clone instances to probe for
  + **pengine:** Prevent clones from being stopped because resources colocated with them cannot be active
  + **pengine:** Try to ensure atomic migration ops occur within a single transition
  + **pengine:** Use hashtables instead of linked lists for performance sensitive datastructures
  + **pengine:** Use the original digest algorithm for parameter lists
  + **stonith:** cleanup children on timeout in `fence_legacy`
  + **Stonith:** Fix two memory leaks
  + **Tools:** `crm_shadow` - Avoid replacing the entire configuration (including status)

# Pacemaker-1.1.3 (21 Sep 2010)
- 352 commits with 481 files changed, 14130 insertions(+), 11156 deletions(-)

## Changes since Pacemaker-1.1.2.1

  + **ais:** Bug lf#2401 - Improved processing when the peer crmd processes join/leave
  + **ais:** Correct the logic for conecting to plugin based clusters
  + **ais:** Do not supply a process list in mcp-mode
  + **ais:** Drop support for whitetank in the 1.1 release series
  + **ais:** Get an initial dump of the node membership when connecting to quorum-based clusters
  + **ais:** Guard against saturated cpg connections
  + **ais:** Handle `CS_ERR_TRY_AGAIN` in more cases
  + **ais:** Move the code for finding uid before the fork so that the child does no logging
  + **ais:** Never allow quorum plugins to affect connection to the pacemaker plugin
  + **ais:** Sign everyone up for peer process updates, not just the crmd
  + **ais:** The cluster type needs to be set before initializing classic openais connections
  + **cib:** Also free query result for xpath operations that return more than one hit
  + **cib:** Attempt to resolve memory corruption when forking a child to write the cib to disk
  + **cib:** Correctly free memory when writing out the cib to disk
  + **cib:** Fix the application of unversioned diffs
  + **cib:** Remove old developmental error logging
  + **cib:** Restructure the 'valid peer' check for deciding which instructions to ignore
  + **cman:** Correctly process membership/quorum changes from the pcmk plugin. Allow other message types through untouched
  + **cman:** Filter directed messages not intended for us
  + **cman:** Grab the initial membership when we connect
  + **cman:** Keep the list of peer processes up-to-date
  + **cman:** Make sure our common hooks are called after a cman membership update
  + **cman:** Make sure we can compile without cman present
  + **cman:** Populate sender details for cpg messages
  + **cman:** Update the ringid for cman based clusters
  + **Core:** Correctly unpack `HA_Messages` containing multiple entries with the same name
  + **Core:** `crm_count_member()` should only track nodes that have the full stack up
  + **Core:** New developmental logging system inspired by the kernel and a PoC from Lars Ellenberg
  + **crmd:** All nodes should see status updates, not just he DC
  + **crmd:** Allow non-DC nodes to clear failcounts too
  + **crmd:** Base DC election on process relative uptime
  + **crmd:** Bug lf#2439 - `cancel_op()` can also return `HA_RSCBUSY`
  + **crmd:** Bug lf#2439 - Handle asynchronous notification of resource deletion events
  + **crmd:** Bug lf#2458 - Ensure stop actions always have the relevant resource attributes
  + **crmd:** Disable age as a criteria for cman based clusters, its not reliable enough
  + **crmd:** Ensure we activate the DC timer if we detect an alternate DC
  + **crmd:** Factor the nanosecond component of process uptime in elections
  + **crmd:** Fix assertion failure when performing async resource failures
  + **crmd:** Fix handling of async resource deletion results
  + **crmd:** Include the action for crm graph operations
  + **crmd:** Make sure the membership cache is accurate after a sucessful fencing operation
  + **crmd:** Make sure we always poke the FSA after a transition to clear any `TE_HALT` actions
  + **crmd:** Offer crm-level membership once the peer starts the crmd process
  + **crmd:** Only need to request quorum update for plugin based clusters
  + **crmd:** Prevent assertion failure for stop actions resulting from cs: 3c0bc17c6daf
  + **crmd:** Prevent everyone from loosing DC elections by correctly initializing all relevant variables
  + **crmd:** Prevent segmentation fault
  + **crmd:** several fixes for async resource delete (thanks to beekhof)
  + **crmd:** Use the correct define/size for lrm resource IDs
  + Introduce two new cluster types 'cman' and 'corosync', replaces 'quorum_provider' concept
  + **mcp:** Add missing headers when built without heartbeat support
  + **mcp:** Correctly initialize the string containing the list of active daemons
  + **mcp:** Fix macro expansion in init script
  + **mcp:** Fix the expansion of the pid file in the init script
  + **mcp:** Handle `CS_ERR_TRY_AGAIN` when connecting to libcfg
  + **mcp:** Make sure we can compile the mcp without cman present
  + **mcp:** New master control process for (re)spawning pacemaker daemons
  + **mcp:** Read config early so we can re-initialize logging asap if daemonizing
  + **mcp:** Rename the mcp binary to pacemakerd and create a 'pacemaker' init script
  + **mcp:** Resend our process list after every CPG change
  + **mcp:** Tell chkconfig we need to shut down early on
  + **pengine:** Avoid creating invalid ordering constraints for probes that are not needed
  + **pengine:** Bug lf#1959 - Fail unmanaged resources should not prevent other services from shutting down
  + **pengine:** Bug lf#2422 - Ordering dependencies on partially active groups not observed properly
  + **pengine:** Bug lf#2424 - Use notify oepration definition if it exists in the configuration
  + **pengine:** Bug lf#2433 - No services should be stopped until probes finish
  + **pengine:** Bug lf#2453 - Enforce clone ordering in the absense of colocation constraints
  + **pengine:** Bug lf#2476 - Repair on-fail=block for groups and primitive resources
  + **pengine:** Correctly detect when there is a real failcount that expired and needs to be cleared
  + **pengine:** Correctly handle pseudo action creation
  + **pengine:** Correctly order clone startup after group/clone start
  + **pengine:** Correct use-after-free introduced in the prior patch
  + **pengine:** Do not demote resources because something that requires it can not run
  + **pengine:** Fix colocation for interleaved clones
  + **pengine:** Fix colocation with partially active groups
  + **pengine:** Fix potential use-after-free defect from coverity
  + **pengine:** Fix previous merge
  + **pengine:** Fix use-after-free in `order_actions()` reported by valgrind
  + **pengine:** Make the current data set a global variable so it does not need to be passed around everywhere
  + **pengine:** Prevent endless loop when looking for operation definitions in the configuration
  + **pengine:** Prevent segfault by ensuring the arguments to `do_calculations()` are initialized
  + **pengine:** Rewrite the ordering constraint logic to be simplicity, clarity and maintainability
  + **pengine:** Wait until stonith is available, do not fall back to shutdown for nodes requesting termination
  + Resolve coverity `RESOURCE_LEAK` defects
  + **Shell:** Complete the transition to using `crm_attribute` instead of `crm_failcount` and `crm_standby`
  + **stonith:** Advertise stonith-ng options in the metadata
  + **stonith:** Bug lf#2461 - Prevent segfault by not looking up operations if the hashtable has not been initialized yet
  + **stonith:** Bug lf#2473 - Add the timeout at the top level where the daemon is looking for it
  + **Stonith:** Bug lf#2473 - Ensure stonith operations complete within the timeout and are terminated if they run too long
  + **stonith:** Bug lf#2473 - Ensure timeouts are included for fencing operations
  + **stonith:** Bug lf#2473 - Gracefully handle remote operations that arrive late (after we have done notifications)
  + **stonith:** Correctly parse `pcmk_host_list` parameters that appear on a single line
  + **stonith:** Map poweron/poweroff back to on/off expected by the stonith tool from cluster-glue
  + **stonith:** pass the configuration to the stonith program via environment variables (bnc#620781)
  + **Stonith:** Use the timeout specified by the user
  + Support starting plugin-based Pacemaker clusters with the MCP as well
  + **Tools:** Bug lf#2456 - Fix assertion failure in `crm_resource`
  + **tools:** `crm_node` - Repair the ability to connect to openais based clusters
  + **tools:** `crm_node` - Use the correct short option for --cman
  + **tools:** `crm_report` - corosync.conf wont necessarily contain the text 'pacemaker' anymore
  + **Tools:** `crm_simulate` - Fix use-after-free in when terminating
  + **tools:** `crm_simulate` - Resolve coverity `USE_AFTER_FREE` defect
  + **Tools:** Drop the 'pingd' daemon and resource agent in favor of ocf:pacemaker:ping
  + **Tools:** Fix recently introduced use-of-NULL
  + **Tools:** Fix use-after-free defects from coverity

# Pacemaker-1.1.2 (12 May 2010)
- 339 commits with 708 files changed, 37918 insertions(+), 10584 deletions(-)

## Changes since Pacemaker-1.1.1

  + **ais:** Do not count votes from offline nodes and calculate current votes before sending quorum data
  + **ais:** Ensure the list of active processes sent to clients is always up-to-date
  + **ais:** Look for the correct conf variable for turning on file logging
  + **ais:** Need to find a better and thread-safe way to set `core_uses_pid.` Disable for now.
  + **ais:** Use the threadsafe version of getpwnam
  + **Core:** Bump the feature set due to the new failcount expiry feature
  + **Core:** fix memory leaks exposed by valgrind
  + **Core:** Bug lf#2414 - Prevent use-after-free reported by valgrind when doing xpath based deletions
  + **crmd:** Bug lf#2414 - Prevent use-after-free of the PE connection after it dies
  + **crmd:** Bug lf#2414 - Prevent use-after-free of the stonith-ng connection
  + **crmd:** Bug lf#2401 - Improved detection of partially active peers
  + **crmd:** Bug lf#2379 - Ensure the cluster terminates when the PE is not available
  + **crmd:** Do not allow the `target_rc` to be misused by resource agents
  + **crmd:** Do not ignore action timeouts based on FSA state
  + **crmd:** Ensure we don't get stuck in `S_PENDING` if we lose an election to someone that never talks to us again
  + **crmd:** Fix memory leaks exposed by valgrind
  + **crmd:** Remove race condition that could lead to multiple instances of a clone being active on a machine
  + **crmd:** Send `erase_status_tag()` calls to the local CIB when the DC is fenced, since there is no DC to accept them
  + **crmd:** Use global fencing notifications to prevent secondary fencing operations of the DC
  + **pengine:** Bug lf#2317 - Avoid needless restart of primitive depending on a clone
  + **pengine:** Bug lf#2361 - Ensure clones observe mandatory ordering constraints if the LHS is unrunnable
  + **pengine:** Bug lf#2383 - Combine failcounts for all instances of an anonymous clone on a host
  + **pengine:** Bug lf#2384 - Fix intra-set colocation and ordering
  + **pengine:** Bug lf#2403 - Enforce mandatory promotion (colocation) constraints
  + **pengine:** Bug lf#2412 - Correctly find clone instances by their prefix
  + **pengine:** Do not be so quick to pull the trigger on nodes that are coming up
  + **pengine:** Fix memory leaks exposed by valgrind
  + **pengine:** Rewrite `native_merge_weights()` to avoid Fix use-after-free
  + **Shell:** Bug bnc#590035 - always reload status if working with the cluster
  + **Shell:** Bug bnc#592762 - Default to using the status section from the live CIB
  + **Shell:** Bug lf#2315 - edit multiple `meta_attributes` sets in resource management
  + **Shell:** Bug lf#2221 - enable comments
  + **Shell:** Bug bnc#580492 - implement new cibstatus interface and commands
  + **Shell:** Bug bnc#585471 - new cibstatus import command
  + **Shell:** check timeouts also against the default-action-timeout property
  + **Shell:** new configure filter command
  + **Tools:** `crm_mon` - fix memory leaks exposed by valgrind

# Pacemaker-1.1.1 (16 Feb 2010)
- First public release of Pacemaker 1.1
- Package reference documentation in a doc subpackage
- Move cts into a subpackage so that it can be easily consumed by others
- New stonith daemon that supports global notifications
- Service placement influenced by the physical resources
- A new tool for simulating failures and the cluster’s reaction to them
- Ability to serialize an otherwise unrelated a set of resource actions (eg. Xen migrations)

# Pacemaker-1.0.7 (18 Jan 2010)
- 193 commits with 220 files changed, 15933 insertions(+), 8782 deletions(-)

## Changes since 1.0.5-4

  + **pengine:** Bug 2213 - Ensure groups process location constraints so that clone-node-max works for cloned groups
  + **pengine:** Bug lf#2153 - non-clones should not restart when clones stop/start on other nodes
  + **pengine:** Bug lf#2209 - Clone ordering should be able to prevent startup of dependent clones
  + **pengine:** Bug lf#2216 - Correctly identify the state of anonymous clones when deciding when to probe
  + **pengine:** Bug lf#2225 - Operations that require fencing should wait for 'stonith_complete' not 'all_stopped'.
  + **pengine:** Bug lf#2225 - Prevent clone peers from stopping while another is instance is (potentially) being fenced
  + **pengine:** Correctly anti-colocate with a group
  + **pengine:** Correctly unpack ordering constraints for resource sets to avoid graph loops
  + **Tools:** crm: load help from `crm_cli.txt`
  + **Tools:** crm: resource sets (bnc#550923)
  + **Tools:** crm: support for comments (LF 2221)
  + **Tools:** crm: support for description attribute in resources/operations (bnc#548690)
  + **Tools:** hb2openais: add EVMS2 CSM processing (and other changes) (bnc#548093)
  + **Tools:** hb2openais: do not allow empty rules, clones, or groups (LF 2215)
  + **Tools:** hb2openais: refuse to convert pure EVMS volumes
  + **cib:** Ensure the loop for login message terminates
  + **cib:** Finally fix reliability of receiving large messages over remote plaintext connections
  + **cib:** Fix remote notifications
  + **cib:** For remote connections, default to `CRM_DAEMON_USER` since thats the only one that the cib can validate the password for using PAM
  + **cib:** Remote plaintext - Retry sending parts of the message that did not fit the first time
  + **crmd:** Ensure batch-limit is correctly enforced
  + **crmd:** Ensure we have the latest status after a transition abort
  + **(bnc#547579,547582):** Tools: crm: status section editing support
  + **shell:** Add allow-migrate as allowed meta-attribute (bnc#539968)
  + **Build:** Do not automatically add -L/lib, it could cause 64-bit arches to break
  + **pengine:** Bug lf#2206 - `rsc_order` constraints always use score at the top level
  + **pengine:** Only complain about target-role=master for non m/s resources
  + **pengine:** Prevent non-multistate resources from being promoted through target-role
  + **pengine:** Provide a default action for resource-set ordering
  + **pengine:** Silently fix requires=fencing for stonith resources so that it can be set in `op_defaults`
  + **Tools:** Bug lf#2286 - Allow the shell to accept template parameters on the command line
  + **Tools:** Bug lf#2307 - Provide a way to determin the nodeid of past cluster members
  + **Tools:** crm: add update method to template apply (LF 2289)
  + **Tools:** crm: direct RA interface for ocf class resource agents (LF 2270)
  + **Tools:** crm: direct RA interface for stonith class resource agents (LF 2270)
  + **Tools:** crm: do not add score which does not exist
  + **Tools:** crm: do not consider warnings as errors (LF 2274)
  + **Tools:** crm: do not remove sets which contain id-ref attribute (LF 2304)
  + **Tools:** crm: drop empty attributes elements
  + **Tools:** crm: exclude locations when testing for pathological constraints (LF 2300)
  + **Tools:** crm: fix exit code on single shot commands
  + **Tools:** crm: fix node delete (LF 2305)
  + **Tools:** crm: implement -F (--force) option
  + **Tools:** crm: rename status to cibstatus (LF 2236)
  + **Tools:** crm: revisit configure commit
  + **Tools:** crm: stay in crm if user specified level only (LF 2286)
  + **Tools:** crm: verify changes on exit from the configure level
  + **ais:** Some clients such as `gfs_controld` want a cluster name, allow one to be specified in corosync.conf
  + **cib:** Clean up logic for receiving remote messages
  + **cib:** Create valid notification control messages
  + **cib:** Indicate where the remote connection came from
  + **cib:** Send password prompt to stderr so that stdout can be redirected
  + **cts:** Fix rsh handling when stdout is not required
  + **doc:** Fill in the section on removing a node from an AIS-based cluster
  + **doc:** Update the docs to reflect the 0.6/1.0 rolling upgrade problem
  + **doc:** Use Publican for docbook based documentation
  + **fencing:** stonithd: add metadata for stonithd instance attributes (and support in the shell)
  + **fencing:** stonithd: ignore case when comparing host names (LF 2292)
  + **tools:** Make `crm_mon` functional with remote connections
  + **xml:** Add stopped as a supported role for operations
  + **xml:** Bug bnc#552713 - Treat node unames as text fields not IDs
  + **xml:** Bug lf#2215 - Create an always-true expression for empty rules when upgrading from 0.6

# Pacemaker-1.0.5-4 (29 Oct 2009)
- Include the fixes from CoroSync integration testing
- Move the resource templates - they are not documentation
- Ensure documentation is placed in a standard location
- Exclude documentation that is included elsewhere in the package

- Update the tarball from upstream to version ee19d8e83c2a
  + **cib:** Correctly clean up when both plaintext and tls remote ports are requested
  + **pengine:** Bug bnc#515172 - Provide better defaults for lt(e) and gt(e) comparisions
  + **pengine:** Bug lf#2197 - Allow master instances placemaker to be influenced by colocation constraints
  + **pengine:** Make sure promote/demote pseudo actions are created correctly
  + **pengine:** Prevent target-role from promoting more than master-max instances
  + **ais:** Bug lf#2199 - Prevent expected-quorum-votes from being populated with garbage
  + **ais:** Prevent deadlock - don't try to release IPC message if the connection failed
  + **cib:** For validation errors, send back the full CIB so the client can display the errors
  + **cib:** Prevent use-after-free for remote plaintext connections
  + **crmd:** Bug lf#2201 - Prevent use-of-NULL when running heartbeat

# Pacemaker-1.0.5-3 (13 Oct 2009)
- Update the tarball from upstream to version 38cd629e5c3c
  + **Core:** Bug lf#2169 - Allow dtd/schema validation to be disabled
  + **pengine:** Bug lf#2106 - Not all anonymous clone children are restarted after configuration change
  + **pengine:** Bug lf#2170 - stop-all-resources option had no effect
  + **pengine:** Bug lf#2171 - Prevent groups from starting if they depend on a complex resource which can not
  + **pengine:** Disable resource management if stonith-enabled=true and no stonith resources are defined
  + **pengine:** do not include master score if it would prevent allocation
  + **ais:** Avoid excessive load by checking for dead children every 1s (instead of 100ms)
  + **ais:** Bug rh#525589 - Prevent shutdown deadlocks when running on CoroSync
  + **ais:** Gracefully handle changes to the AIS nodeid
  + **crmd:** Bug bnc#527530 - Wait for the transition to complete before leaving `S_TRANSITION_ENGINE`
  + **crmd:** Prevent use-after-free with `LOG_DEBUG_3`
  + **xml:** Mask the "symmetrical" attribute on `rsc_colocation` constraints (bnc#540672)
  + bnc#520707: Tools: crm: new templates ocfs2 and clvm
  + **Build:** Invert the disable ais/heartbeat logic so that `--without` (ais|heartbeat) is available to rpmbuild
  + **pengine:** Bug lf#2178 - Indicate unmanaged clones
  + **pengine:** Bug lf#2180 - Include node information for all failed ops
  + **pengine:** Bug lf#2189 - Incorrect error message when unpacking simple ordering constraint
  + **pengine:** Correctly log resources that would like to start but can not
  + **pengine:** Stop ptest from logging to syslog
  + **ais:** Include version details in plugin name
  + **crmd:** Requery the resource metadata after every start operation

# Pacemaker-1.0.5-2.1 (21 Aug 2009)
- rebuilt with new openssl

# Pacemaker-1.0.5-2 (19 Aug 2009)
- Add versioned perl dependency as specified by
    https://fedoraproject.org/wiki/Packaging/Perl#Packages_that_link_to_libperl
- No longer remove RPATH data, it prevents us finding libperl.so and no other
  libraries were being hardcoded
- Compile in support for heartbeat
- Conditionally add heartbeat-devel and corosynclib-devel to the -devel requirements
  depending on which stacks are supported

# Pacemaker-1.0.5 (17 Aug 2009)
- Add dependency on resource-agents
- Use the version of the configure macro that supplies `--prefix,` --libdir, etc
- Update the tarball from upstream to version 462f1569a437 (Pacemaker 1.0.5 final)
  + **Tools:** `crm_resource` - Advertise `--move` instead of --migrate
  + **Extra:** New node connectivity RA that uses system ping and `attrd_updater`
  + **crmd:** Note that dc-deadtime can be used to mask the brokeness of some switches

# Tue Aug 11 2009 Ville Skyttä <ville.skytta@iki.fi> - 1.0.5-0.7.c9120a53a6ae.hg
- Use bzipped upstream tarball.

# Wed Jul  29 2009 Andrew Beekhof <andrew@beekhof.net> - 1.0.5-0.6.c9120a53a6ae.hg
- Add back missing build auto* dependencies
- Minor cleanups to the install directive

# Tue Jul  28 2009 Andrew Beekhof <andrew@beekhof.net> - 1.0.5-0.5.c9120a53a6ae.hg
- Add a leading zero to the revision when alphatag is used

# Tue Jul  28 2009 Andrew Beekhof <andrew@beekhof.net> - 1.0.5-0.4.c9120a53a6ae.hg
- Incorporate the feedback from the cluster-glue review
- Realistically, the version is a 1.0.5 pre-release
- Use the global directive instead of define for variables
- Use the haclient/hacluster group/user instead of daemon
- Use the `_configure` macro
- Fix install dependencies

# Pacemaker-1.0.4-3 Fri Jul  24 2009 Andrew Beekhof <andrew@beekhof.net> -
- Initial Fedora checkin
- Include an AUTHORS and license file in each package
- Change the library package name to pacemaker-libs to be more
  Fedora compliant
- Remove execute permissions from xml related files
- Reference the new cluster-glue devel package name
- Update the tarball from upstream to version c9120a53a6ae
  + **pengine:** Only prevent migration if the clone dependency is stopping/starting on the target node
  + **pengine:** Bug 2160 - Don't shuffle clones due to colocation
  + **pengine:** New implementation of the resource migration (not stop/start) logic
  + **Tools:** `crm_resource` - Prevent use-of-NULL by requiring a resource name for the -A and -a options
  + **pengine:** Prevent use-of-NULL in `find_first_action()`

# Pacemaker-1.0.4-2 (14 Jul 2009)
- Reference authors from the project AUTHORS file instead of listing in description
- Change Source0 to reference the Mercurial repo
- Cleaned up the summaries and descriptions
- Incorporate the results of Fedora package self-review

# Pacemaker-1.0.4 (04 Jun 2009)
- 209 commits with 266 files changed, 12010 insertions(+), 8276 deletions(-)

## Changes since Pacemaker-1.0.3

  + **(bnc#488291):** ais: do not rely on byte endianness on ptr cast
  + **(bnc#507255):** Tools: crm: delete rsc/op_defaults (these `meta_attributes` are killing me)
  + **(bnc#507255):** Tools: crm: import properly rsc/op_defaults
  + **(LF 2114):** Tools: crm: add support for operation instance attributes
  + **ais:** Bug lf#2126 - Messages replies cannot be routed to transient clients
  + **ais:** Fix compilation for the latest Corosync API (v1719)
  + **attrd:** Do not perform all updates as complete refreshes
  + **cib:** Fix huge memory leak affecting heartbeat-based clusters
  + **Core:** Allow xpath queries to match attributes
  + **Core:** Generate the help text directly from a tool options struct
  + **Core:** Handle differences in 0.6 messaging format
  + **crmd:** Bug lf#2120 - All transient node attribute updates need to go via attrd
  + **crmd:** Correctly calculate how long an FSA action took to avoid spamming the logs with errors
  + **crmd:** Fix another large memory leak affecting Heartbeat based clusters
  + **lha:** Restore compatibility with older versions
  + **pengine:** Bug bnc#495687 - Filesystem is not notified of successful STONITH under some conditions
  + **pengine:** Make running a cluster with STONITH enabled but no STONITH resources an error and provide details on resolutions
  + **pengine:** Prevent use-ofNULL when using resource ordering sets
  + **pengine:** Provide inter-notification ordering guarantees
  + **pengine:** Rewrite the notification code to be understanable and extendable
  + **Tools:** attrd - Prevent race condition resulting in the cluster forgetting the node wishes to shut down
  + **Tools:** crm: regression tests
  + **Tools:** `crm_mon` - Fix smtp notifications
  + **Tools:** `crm_resource` - Repair the ability to query meta attributes
  + **Build:** Bug lf#2105 - Debian package should contain pacemaker doc and crm templates
  + bnc#507255: Tools: crm: handle empty rsc/op_defaults properly
  + bnc#507255: Tools: crm: use the right `obj_type` when creating objects from xml nodes
  + LF#2107: Tools: crm: revisit exit codes in configure
  + **cib:** Do not bother validating updates that only affect the status section
  + **Core:** Include supported stacks in version information
  + **crmd:** Record in the CIB, the cluster infrastructure being used
  + **cts:** Do not combine `crm_standby` arguments - the wrapper can not process them
  + **cts:** Fix the CIBAusdit class
  + **Extra:** Refresh showscores script from Dominik
  + **pengine:** Build a statically linked version of ptest
  + **pengine:** Correctly log the actions for resources that are being recovered
  + **pengine:** Correctly log the occurrence of promotion events
  + **pengine:** Implememt node health based on a patch from Mark Hamzy
  + **Tools:** Add examples to help text outputs
  + **Tools:** crm: catch syntax errors for configure load
  + **Tools:** crm: implement erasing nodes in configure erase
  + **Tools:** crm: work with parents only when managing xml objects
  + **Tools:** `crm_mon` - Add option to run custom notification program on resource operations (Patch by Dominik Klein)
  + **Tools:** `crm_resource` - Allow `--cleanup` to function on complex resources and cluster-wide
  + **Tools:** haresource2cib.py - Patch from horms to fix conversion error
  + **Tools:** Include stack information in `crm_mon` output
  + **Tools:** Two new options (`--stack`, `--constraints`) to `crm_resource`
    for querying how a resource is configured

# Pacemaker-1.0.3 (08 Apr 2009)
- 383 commits with 329 files changed, 15471 insertions(+), 15119 deletions(-)

## Changes since Pacemaker-1.0.2

  + Added tag SLE11-HAE-GMC for changeset 9196be9830c2
  + **ais plugin:** Fix quorum calculation (bnc#487003)
  + **ais:** Another memory fix leak in error path
  + **ais:** Bug bnc#482847, bnc#482905 - Force a clean exit of OpenAIS once Pacemaker has finished unloading
  + **ais:** Bug bnc#486858 - Fix `update_member()` to prevent spamming clients with membership events containing no changes
  + **ais:** Centralize all quorum calculations in the ais plugin and allow expected votes to be configured int he cib
  + **ais:** Correctly handle a return value of zero from `openais_dispatch_recv()`
  + **ais:** Disable logging to a file
  + **ais:** Fix memory leak in error path
  + **ais:** IPC messages are only in scope until a response is sent
  + All signal handlers used with `CL_SIGNAL()` need to be as minimal as possible
  + **cib:** Bug bnc#482885 - Simplify CIB disk-writes to prevent data loss.  Required a change to the backup filename format
  + **cib:** crmd: Revert part of 9782ab035003.  Complex shutdown routines need `G_main_add_SignalHandler` to avoid race coditions
  + **crm:** Avoid infinite loop during crm configure edit (bnc#480327)
  + **crmd:** Avoid a race condition by waiting for the attrd update to trigger a transition automatically
  + **crmd:** Bug bnc#480977 - Prevent extra, partial, shutdown when a node restarts too quickly
  + **crmd:** Bug bnc#480977 - Prevent extra, partial, shutdown when a node restarts too quickly (verified)
  + **crmd:** Bug bnc#489063 - Ensure the DC is always unset after we 'lose' an election
  + **crmd:** Bug BSC#479543 - Correctly find the migration source for timed out `migrate_from` actions
  + **crmd:** Call `crm_peer_init()` before we start the FSA - prevents a race condition when used with Heartbeat
  + **crmd:** Erasing the status section should not be forced to the local node
  + **crmd:** Fix memory leak in cib notication processing code
  + **crmd:** Fix memory leak in transition graph processing
  + **crmd:** Fix memory leaks found by valgrind
  + **crmd:** More memory leaks fixes found by valgrind
  + **fencing:** stonithd: `is_heartbeat_cluster` is a no-no if there is no heartbeat support
  + **pengine:** Bug bnc#466788 - Exclude nodes that can not run resources
  + **pengine:** Bug bnc#466788 - Make colocation based on node attributes work
  + **pengine:** Bug BNC#478687 - Do not crash when clone-max is 0
  + **pengine:** Bug bnc#488721 - Fix id-ref expansion for clones, the doc-root for clone children is not the cib root
  + **pengine:** Bug bnc#490418 - Correctly determine node state for nodes wishing to be terminated
  + **pengine:** Bug LF#2087 - Correctly parse the state of anonymous clones that have multiple instances on a given node
  + **pengine:** Bug lf#2089 - Meta attributes are not inherited by clone children
  + **pengine:** Bug lf#2091 - Correctly restart modified resources that were found active by a probe
  + **pengine:** Bug lf#2094 - Fix probe ordering for cloned groups
  + **pengine:** Bug LF:2075 - Fix large pingd memory leaks
  + **pengine:** Correctly attach orphaned clone children to their parent
  + **pengine:** Correctly handle terminate node attributes that are set to the output from time()
  + **pengine:** Ensure orphaned clone members are hooked up to the parent when clone-max=0
  + **pengine:** Fix memory leak in LogActions
  + **pengine:** Fix the determination of whether a group is active
  + **pengine:** Look up the correct promotion preference for anonymous masters
  + **pengine:** Simplify handling of start failures by changing the default migration-threshold to INFINITY
  + **pengine:** The ordered option for clones no longer causes extra start/stop operations
  + **RA:** Bug bnc#490641 - Shut down `dlm_controld` with -TERM instead of -KILL
  + **RA:** pingd: Set default ping interval to 1 instead of 0 seconds
  + **Resources:** pingd - Correctly tell the ping daemon to shut down
  + **Tools:** Bug bnc#483365 - Ensure the command from `cluster_test` includes
    a value for `--log-facility`
  + **Tools:** cli: fix and improve delete command
  + **Tools:** crm: add and implement templates
  + **Tools:** crm: add support for command aliases and some common commands (i.e. cd,exit)
  + **Tools:** crm: create top configuration nodes if they are missing
  + **Tools:** crm: fix parsing attributes for rules (broken by the previous changeset)
  + **Tools:** crm: new ra set of commands
  + **Tools:** crm: resource agents information management
  + **Tools:** crm: `rsc/op_defaults`
  + **Tools:** crm: support for no value attribute in nvpairs
  + **Tools:** crm: the new configure monitor command
  + **Tools:** crm: the new configure node command
  + **Tools:** `crm_mon` - Prevent use-of-NULL when summarizing an orphan
  + **Tools:** hb2openais: create clvmd clone for respawn evmsd in ha.cf
  + **Tools:** hb2openais: fix a serious recursion bug in xml node processing
  + **Tools:** hb2openais: fix ocfs2 processing
  + **Tools:** pingd - prevent double free of getaddrinfo() output in error path
  + **Tools:** The default re-ping interval for pingd should be 1s not 1ms
  + bnc#479049: Tools: crm: add validation of resource type for the configure primitive command
  + bnc#479050: Tools: crm: add help for RA parameters in tab completion
  + bnc#479050: Tools: crm: add tab completion for primitive params/meta/op
  + bnc#479050: Tools: crm: reimplement cluster properties completion
  + bnc#486968: Tools: crm: listnodes function requires no parameters (do not mix completion with other stuff)
  + **ais:** Remove the ugly hack for dampening AIS membership changes
  + **cib:** Fix memory leaks by using `mainloop_add_signal`
  + **cib:** Move more logging to the debug level (was info)
  + **cib:** Overhaul the processing of synchronous replies
  + **Core:** Add library functions for instructing the cluster to terminate nodes
  + **crmd:** Add new expected-quorum-votes option
  + **crmd:** Allow up to 5 retires when an attrd update fails
  + **crmd:** Automatically detect and use new values for `crm_config` options
  + **crmd:** Bug bnc#490426 - Escalated shutdowns stall when there are pending resource operations
  + **crmd:** Clean up and optimize the DC election algorithm
  + **crmd:** Fix memory leak in shutdown
  + **crmd:** Fix memory leaks spotted by Valgrind
  + **crmd:** Ignore join messages from hosts other than our DC
  + **crmd:** Limit the scope of resource updates to the status section
  + **crmd:** Prevent the crmd from being respawned if its told to shut down when it did not ask to be
  + **crmd:** Re-check the election status after membership events
  + **crmd:** Send resource updates via the local CIB during elections
  + **pengine:** Bug bnc#491441 - `crm_mon` does not display operations returning 'uninstalled' correctly
  + **pengine:** Bug lf#2101 - For location constraints, role=Slave is equivalent to role=Started
  + **pengine:** Clean up the API - removed ->children() and renamed ->find_child() to `fine_rsc()`
  + **pengine:** Compress the display of healthy anonymous clones
  + **pengine:** Correctly log the actions for resources that are being recovered
  + **pengine:** Determin a promotion score for complex resources
  + **pengine:** Ensure clones always have a value for globally-unique
  + **pengine:** Prevent orphan clones from being allocated
  + **RA:** controld: Return proper exit code for stop op.
  + **Tools:** Bug bnc#482558 - Fix logging test in `cluster_test`
  + **Tools:** Bug bnc#482828 - Fix quoting in `cluster_test` logging setup
  + **Tools:** Bug bnc#482840 - Include directory path to CTSlab.py
  + **Tools:** crm: add more user input checks
  + **Tools:** crm: do not check resource status of we are working with a shadow
  + **Tools:** crm: fix id-refs and allow reference to top objects (i.e. primitive)
  + **Tools:** crm: ignore comments in the CIB
  + **Tools:** crm: multiple column output would not work with small lists
  + **Tools:** crm: refuse to delete running resources
  + **Tools:** crm: rudimentary if-else for templates
  + **Tools:** crm: Start/stop clones via target-role.
  + **Tools:** `crm_mon` - Compress the node status for healthy and offline nodes
  + **Tools:** `crm_shadow` - Return 0/`cib_ok` when `--create-empty` succeeds
  + **Tools:** `crm_shadow` - Support `-e`, the short form of `--create-empty`
  + **Tools:** Make attrd quieter
  + **Tools:** pingd - Avoid using various clplumbing functions as they seem to leak
  + **Tools:** Reduce pingd logging

# Pacemaker-1.0.2 (16 Feb 2009)
- 441 commits with 639 files changed, 20871 insertions(+), 21594 deletions(-)

## Changes since Pacemaker-1.0.1

  + **Tools:** Bug BNC#450815 - crm cli: do not generate id for the operations tag
  + **ais:** Add support for the new AIS IPC layer
  + **ais:** Always set header.error to the correct default: `SA_AIS_OK`
  + **ais:** Bug BNC#456243 - Ensure the membership cache always contains an entry for the local node
  + **ais:** Bug BNC#456208 - Prevent deadlocks by not logging in the child process before exec()
  + **ais:** By default, disable supprt for the WIP openais IPC patch
  + **ais:** Detect and handle situations where ais and the crm disagree on the node name
  + **ais:** Ensure `crm_peer_seq` is updated after a membership update
  + **ais:** Make sure all IPC header fields are set to sane defaults
  + **ais:** Repair and streamline service load now that whitetank startup functions correctly
  + **build:** create and install doc files
  + **cib:** Allow clients without mainloop to connect to the cib
  + **cib:** CID:18 - Fix use-of-NULL in `cib_perform_op`
  + **cib:** CID:18 - Repair errors introduced in b5a18704477b - Fix use-of-NULL in `cib_perform_op`
  + **cib:** Ensure diffs contain the correct values of `admin_epoch`
  + **cib:** Fix four moderately sized memory leaks detected by Valgrind
  + **Core:** CID:10 - Prevent indexing into an array of schemas with a negative value
  + **Core:** CID:13 - Fix memory leak in `log_data_element`
  + **Core:** CID:15 - Fix memory leak in `crm_get_peer`
  + **Core:** CID:6 - Fix use-of-NULL in `copy_ha_msg_input`
  + **Core:** Fix crash in the membership code preventing node shutdown
  + **Core:** Fix more memory leaks foudn by valgrind
  + **Core:** Prevent unterminated strings after decompression
  + **crmd:** Bug BNC:467995 - Delay marking STONITH operations complete until STONITH tells us so
  + **crmd:** Bug LF:1962 - Do not NACK peers because they are not (yet) in our membership.  Just ignore them.
  + **crmd:** Bug LF:2010 - Ensure fencing cib updates create the `node_state` entry if needed to preent re-fencing during cluster startup
  + **crmd:** Correctly handle reconnections to attrd
  + **crmd:** Ensure updates for lost migrate operations indicate which node it tried to migrating to
  + **crmd:** If there are no nodes to finalize, start an election.
  + **crmd:** If there are no nodes to welcome, start an election.
  + **crmd:** Prevent node attribute loss by detecting attrd disconnections immediately
  + **crmd:** Prevent node re-probe loops by ensuring mandatory actions always complete
  + **pengine:** Bug 2005 - Fix startup ordering of cloned stonith groups
  + **pengine:** Bug 2006 - Correctly reprobe cloned groups
  + **pengine:** Bug BNC:465484 - Fix the no-quorum-policy=suicide option
  + **pengine:** Bug LF:1996 - Correctly process disabled monitor operations
  + **pengine:** CID:19 - Fix use-of-NULL in `determine_online_status`
  + **pengine:** Clones now default to globally-unique=false
  + **pengine:** Correctly calculate the number of available nodes for the clone to use
  + **pengine:** Only shoot online nodes with no-quorum-policy=suicide
  + **pengine:** Prevent on-fail settings being ignored after a resource is successfully stopped
  + **pengine:** Prevent use-of-NULL for failed migrate actions in `process_rsc_state()`
  + **pengine:** Remove an optimization for the terminate node attribute that caused the cluster to block indefinitly
  + **pengine:** Repar the ability to colocate based on node attributes other than uname
  + **pengine:** Start the correct monitor operation for unmanaged masters
  + **stonith:** CID:3 - Fix another case of exceptionally poor error handling by the original stonith developers
  + **stonith:** CID:5 - Checking for NULL and then dereferencing it anyway is an interesting approach to error handling
  + **stonithd:** Sending IPC to the cluster is a privileged operation
  + **stonithd:** wrong checks for shmid (0 is a valid id)
  + **Tools:** attrd - Correctly determine when an attribute has stopped changing and should be committed to the CIB
  + **Tools:** Bug 2003 - pingd does not correctly detect failures when the interface is down
  + **Tools:** Bug 2003 - pingd does not correctly handle node-down events on multi-NIC systems
  + **Tools:** Bug 2021 - pingd does not detect sequence wrapping correctly, incorrectly reports nodes offline
  + **Tools:** Bug BNC:468066 - Do not use the result of uname() when its no longer in scope
  + **Tools:** Bug BNC:473265 - `crm_resource -L` dumps core
  + **Tools:** Bug LF:2001 - Transient node attributes should be set via attrd
  + **Tools:** Bug LF:2036 - `crm_resource` cannot set/get parameters for cloned resources
  + **Tools:** Bug LF:2046 - Node attribute updates are lost because attrd can take too long to start
  + **Tools:** Cause the correct clone instance to be failed with
    `crm_resource -F`
  + **Tools:** `cluster_test` - Allow the user to select a stack and fix CTS invocation
  + **Tools:** crm cli: allow rename only if the resource is stopped
  + **Tools:** crm cli: catch system errors on file operations
  + **Tools:** crm cli: completion for ids in configure
  + **Tools:** crm cli: drop '-rsc' from attributes for order constraint
  + **Tools:** crm cli: exit with an appropriate exit code
  + **Tools:** crm cli: fix wrong order of action and resource in order constraint
  + **Tools:** crm cli: fox wrong exit code
  + **Tools:** crm cli: improve handling of cib attributes
  + **Tools:** crm cli: new command: configure rename
  + **Tools:** crm cli: new command: configure upgrade
  + **Tools:** crm cli: new command: node delete
  + **Tools:** crm cli: prevent key errors on missing cib attributes
  + **Tools:** crm cli: print long help for help topics
  + **Tools:** crm cli: return on syntax error when parsing score
  + **Tools:** crm cli: `rsc_location` can be without nvpairs
  + **Tools:** crm cli: short node preference location constraint
  + **Tools:** crm cli: sometimes, on errors, level would change on single shot use
  + **Tools:** crm cli: syntax: drop a bunch of commas (remains of help tables conversion)
  + **Tools:** crm cli: verify user input for sanity
  + **Tools:** crm: find expressions within rules (do not always skip xml nodes due to used id)
  + **Tools:** `crm_master` should not define a set id now that attrd is used.  Defining one can break lookups
  + **Tools:** `crm_mon` Use the OID assigned to the project by IANA for SNMP traps
  + bnc#445622: Tools: crm cli: improve the node show command and drop node status
  + LF#2009: stonithd: improve timeouts for remote fencing
  + **ais:** Allow dead peers to be removed from membership calculations
  + **ais:** Pass node deletion events on to clients
  + **ais:** Sanitize ipc usage
  + **ais:** Supply the node uname in addtion to the id
  + **Build:** Clean up configure to ensure `NON_FATAL_CFLAGS` is consistent with CFLAGS (ie. includes -g)
  + **Build:** Install `cluster_test`
  + **Build:** Use more restrictive CFLAGS and fix the resulting errors
  + **cib:** CID:20 - Fix potential use-after-free in `cib_native_signon`
  + **Core:** Bug BNC:474727 - Set a maximum time to wait for IPC messages
  + **Core:** CID:12 - Fix memory leak in `decode_transition_magic` error path
  + **Core:** CID:14 - Fix memory leak in `calculate_xml_digest` error path
  + **Core:** CID:16 - Fix memory leak in `date_to_string` error path
  + **Core:** Try to track down the cause of XML parsing errors
  + **crmd:** Bug BNC:472473 - Do not wait excessive amounts of time for lost actions
  + **crmd:** Bug BNC:472473 - Reduce the transition timeout to `action_timeout+network_delay`
  + **crmd:** Do not fast-track the processing of LRM refreshes when there are pending actions.
  + **crmd:** `do_dc_join_filter_offer` - Check the 'join' message is for the current instance before deciding to NACK peers
  + **crmd:** Find option values without having to do a config upgrade
  + **crmd:** Implement shutdown using a transient node attribute
  + **crmd:** Update the crmd options to use dashes instead of underscores
  + **cts:** Add 'cluster reattach' to the suite of automated regression tests
  + **cts:** `cluster_test` - Make some usability enhancements
  + **CTS:** `cluster_test` - suggest a valid port number
  + **CTS:** Fix python import order
  + **cts:** Implement an automated SplitBrain test
  + **CTS:** Remove references to deleted classes
  + **Extra:** Resources - Use `HA_VARRUN` instead of `HA_RSCTMP` for state files as Heartbeat removes `HA_RSCTMP` at startup
  + **HB:** Bug 1933 - Fake `crmd_client_status_callback()` calls because HB does not provide them for already running processes
  + **pengine:** CID:17 - Fix memory leak in `find_actions_by_task` error path
  + **pengine:** CID:7,8 - Prevent hypothetical use-of-NULL in LogActions
  + **pengine:** Defer logging the actions performed on a resource until we have processed ordering constraints
  + **pengine:** Remove the symmetrical attribute of colocation constraints
  + **Resources:** pingd - fix the meta defaults
  + **Resources:** Stateful - Add missing meta defaults
  + **stonithd:** exit if we the pid file cannot be locked
  + **Tools:** Allow attrd clients to specify the ID the attribute should be created with
  + **Tools:** attrd - Allow attribute updates to be performed from a hosts peer
  + **Tools:** Bug LF:1994 - Clean up `crm_verify` return codes
  + **Tools:** Change the pingd defaults to ping hosts once every second (instead of 5 times every 10 seconds)
  + **Tools:** cibmin - Detect resource operations with a view to providing email/snmp/cim notification
  + **Tools:** crm cli: add back symmetrical for order constraints
  + **Tools:** crm cli: generate role in location when converting from xml
  + **Tools:** crm cli: handle shlex exceptions
  + **Tools:** crm cli: keep order of help topics
  + **Tools:** crm cli: refine completion for ids in configure
  + **Tools:** crm cli: replace inf with INFINITY
  + **Tools:** crm cli: streamline cib load and parsing
  + **Tools:** crm cli: supply provider only for ocf class primitives
  + **Tools:** `crm_mon` - Add support for sending mail notifications of resource events
  + **Tools:** `crm_mon` - Include the DC version in status summary
  + **Tools:** `crm_mon` - Sanitize startup and option processing
  + **Tools:** `crm_mon` - switch to event-driven updates and add support for sending snmp traps
  + **Tools:** `crm_shadow` - Replace the `--locate` option with the saner
    `--edit`
  + **Tools:** hb2openais: do not remove Evmsd resources, but replace them with clvmd
  + **Tools:** hb2openais: replace crmadmin with `crm_mon`
  + **Tools:** hb2openais: replace the lsb class with ocf for o2cb
  + **Tools:** hb2openais: reuse code
  + **Tools:** LF:2029 - Display an error if `crm_resource` is used to reset the operation history of non-primitive resources
  + **Tools:** Make pingd resilient to attrd failures
  + **Tools:** pingd - fix the command line switches
  + **Tools:** Rename `ccm_tool` to `crm_node`

# Pacemaker-1.0.1 (18 Nov 2008)
- 170 commits with 816 files changed, 7633 insertions(+), 6286 deletions(-)

## Changes since Pacemaker-1.0.1

  + **ais:** Allow the crmd to get callbacks whenever a node state changes
  + **ais:** Create an option for starting the mgmtd daemon automatically
  + **ais:** Ensure `HA_RSCTMP` exists for use by resource agents
  + **ais:** Hook up the openais.conf config logging options
  + **ais:** Zero out the PID of disconnecting clients
  + **cib:** Ensure global updates cause a disk write when appropriate
  + **Core:** Add an extra snaity check to getXpathResults() to prevent segfaults
  + **Core:** Do not redefine `__FUNCTION__` unnecessarily
  + **Core:** Repair the ability to have comments in the configuration
  + **crmd:** Bug:1975 - crmd should wait indefinitely for stonith operations to complete
  + **crmd:** Ensure PE processing does not occur for all error cases in `do_pe_invoke_callback`
  + **crmd:** Requests to the CIB should cause any prior PE calculations to be ignored
  + **heartbeat:** Wait for membership 'up' events before removing stale node status data
  + **pengine:** Bug LF:1988 - Ensure recurring operations always have the correct target-rc set
  + **pengine:** Bug LF:1988 - For unmanaged resources we need to skip the usual `can_run_resources()` checks
  + **pengine:** Ensure the terminate node attribute is handled correctly
  + **pengine:** Fix optional colocation
  + **pengine:** Improve up the detection of 'new' nodes joining the cluster
  + **pengine:** Prevent assert failures in `master_color()` by ensuring unmanaged masters are always reallocated to their current location
  + **Tools:** crm cli: parser: return False on syntax error and None for comments
  + **Tools:** crm cli: unify template and edit commands
  + **Tools:** `crm_shadow` - Show more line number information after validation failures
  + **Tools:** hb2openais: add option to upgrade the CIB to v3.0
  + **Tools:** hb2openais: add U option to getopts and update usage
  + **Tools:** hb2openais: backup improved and multiple fixes
  + **Tools:** hb2openais: fix class/provider reversal
  + **Tools:** hb2openais: fix testing
  + **Tools:** hb2openais: move the CIB update to the end
  + **Tools:** hb2openais: update logging and set logfile appropriately
  + **Tools:** LF:1969 - Attrd never sets any properties in the cib
  + **Tools:** Make attrd functional on OpenAIS
  + **ais:** Hook up the options for specifying the expected number of nodes and total quorum votes
  + **ais:** Look for pacemaker options inside the service block with 'name: pacemaker' instead of creating an addtional configuration block
  + **ais:** Provide better feedback when nodes change nodeids (in openais.conf)
  + **cib:** Always store cib contents on disk with `num_updates=0`
  + **cib:** Ensure remote access ports are cleaned up on shutdown
  + **crmd:** Detect deleted resource operations automatically
  + **crmd:** Erase a nodes resource operations and transient attributes after a successful STONITH
  + **crmd:** Find a more appropriate place to update quorum and refresh attrd attributes
  + **crmd:** Fix the handling of unexpected PE exits to ensure the current CIB is stored
  + **crmd:** Fix the recording of pending operations in the CIB
  + **crmd:** Initiate an attrd refresh `_after_` the status section has been fully repopulated
  + **crmd:** Only the DC should update quorum in an openais cluster
  + Ensure meta attributes are used consistantly
  + **pengine:** Allow group and clone level resource attributes
  + **pengine:** Bug N:437719 - Ensure scores from colocated resources count when allocating groups
  + **pengine:** Prevent lsb scripts from being used in globally unique clones
  + **pengine:** Make a best-effort guess at a migration threshold for people with 0.6 configs
  + **Resources:** controld - ensure we are part of a clone with `globally_unique=false`
  + **Tools:** attrd - Automatically refresh all attributes after a CIB replace operation
  + **Tools:** Bug LF:1985 - `crm_mon` - Correctly process failed cib queries to allow reconnection after cluster restarts
  + **Tools:** Bug LF:1987 - `crm_verify` incorrectly warns of configuration upgrades for the most recent version
  + **Tools:** crm (bnc#441028): check for key error in attributes management
  + **Tools:** `crm_mon` - display the meaning of the operation rc code instead of the status
  + **Tools:** `crm_mon` - Fix the display of timing data
  + **Tools:** `crm_verify` - check that we are being asked to validate a complete config
  + **xml:** Relax the restriction on the contents of `rsc_locaiton.node`

# Pacemaker-1.0.0 (16 Oct 2008)
- 261 commits with 3021 files changed, 244985 insertions(+), 111596 deletions(-)

## Changes since f805e1b30103

  + add the crm cli program
  + **ais:** Move the service id definition to a common location and make sure it is always used
  + **build:** rename hb2openais.sh to .in and replace paths with vars
  + **cib:** Implement `--create` for `crm_shadow`
  + **cib:** Remove dead files
  + **Core:** Allow the expected number of quorum votes to be configrable
  + **Core:** `cl_malloc` and friends were removed from Heartbeat
  + **Core:** Only call xmlCleanupParser() if we parsed anything.  Doing so unconditionally seems to cause a segfault
  + **hb2openais.sh:** improve pingd handling; several bugs fixed
  + **hb2openais:** fix clone creation; replace EVMS strings
  + new hb2openais.sh conversion script
  + **pengine:** Bug LF:1950 - Ensure the current values for all notification variables are always set (even if empty)
  + **pengine:** Bug LF:1955 - Ensure unmanaged masters are unconditionally repromoted to ensure they are monitored correctly.
  + **pengine:** Bug LF:1955 - Fix another case of filtering causing unmanaged master failures
  + **pengine:** Bug LF:1955 - Umanaged mode prevents master resources from being allocated correctly
  + **pengine:** Bug N:420538 - Anit-colocation caused a positive node preference
  + **pengine:** Correctly handle unmanaged resources to prevent them from being started elsewhere
  + **pengine:** `crm_resource` - Fix the `--migrate` command
  + **pengine:** MAke stonith-enabled default to true and warn if no STONITH resources are found
  + **pengine:** Make sure orphaned clone children are created correctly
  + **pengine:** Monitors for unmanaged resources do not need to wait for start/promote/demote actions to complete
  + **stonithd (LF 1951):** fix remote stonith operations
  + **stonithd:** fix handling of timeouts
  + **stonithd:** fix logic for stonith resource priorities
  + **stonithd:** implement the fence-timeout instance attribute
  + **stonithd:** initialize value before reading fence-timeout
  + **stonithd:** set timeouts for fencing ops to the timeout of the start op
  + **stonithd:** stonith rsc priorities (new feature)
  + **Tools:** Add hb2openais - a tool for upgrading a Heartbeat cluster to use OpenAIS instead
  + **Tools:** `crm_verify` - clean up the upgrade logic to prevent crash on invalid configurations
  + **Tools:** Make pingd functional on Linux
  + Update version numbers for 1.0 candidates
  + **ais:** Add support for a synchronous call to retrieve the nodes nodeid
  + **ais:** Use the agreed service number
  + **Build:** Reliably detect heartbeat libraries during configure
  + **Build:** Supply prototypes for libreplace functions when needed
  + **Build:** Teach configure how to find corosync
  + **Core:** Provide better feedback if Pacemaker is started by a stack it does not support
  + **crmd:** Avoid calling GHashTable functions with NULL
  + **crmd:** Delay raising `I_ERROR` when the PE exits until we have had a chance to save the current CIB
  + **crmd:** Hook up the stonith-timeout option to stonithd
  + **crmd:** Prevent potential use-of-NULL in `global_timer_callback`
  + **crmd:** Rationalize the logging of graph aborts
  + **pengine:** Add a `stonith_timeout` option and remove new options that are better set in `rsc_defaults`
  + **pengine:** Allow external entities to ask for a node to be shot by creating a terminate=true transient node attribute
  + **pengine:** Bug LF:1950 - Notifications do not contain all documented resource state fields
  + **pengine:** Bug N:417585 - Do not restart group children whos individual score drops below zero
  + **pengine:** Detect clients that disconnect before receiving their reply
  + **pengine:** Implement a true maintenance mode
  + **pengine:** Implement on-fail=standby for NTT.  Derived from a patch by Satomi TANIGUCHI
  + **pengine:** Print the correct message when stonith is disabled
  + **pengine:** ptest - check the input is valid before proceeding
  + **pengine:** Revert group stickiness to the 'old way'
  + **pengine:** Use the correct attribute for action 'requires' (was prereq)
  + **stonithd:** Fix compilation without full heartbeat install
  + **stonithd:** exit with better code on empty host list
  + **tools:** Add a new regression test for CLI tools
  + **tools:** `crm_resource` - return with non-zero when a resource migration command is invalid
  + **tools:** `crm_shadow` - Allow the admin to start with an empty CIB (and no cluster connection)
  + **xml:** pacemaker-0.7 is now an alias for the 1.0 schema

# Pacemaker-0.7.3 (22 Sep 2008)
- 133 commits with 89 files changed, 7492 insertions(+), 1125 deletions(-)

## Changes since f805e1b30103

  + **Tools:** add the crm cli program
  + **Core:** `cl_malloc` and friends were removed from Heartbeat
  + **Core:** Only call xmlCleanupParser() if we parsed anything.  Doing so unconditionally seems to cause a segfault
  + new hb2openais.sh conversion script
  + **pengine:** Bug LF:1950 - Ensure the current values for all notification variables are always set (even if empty)
  + **pengine:** Bug LF:1955 - Ensure unmanaged masters are unconditionally repromoted to ensure they are monitored correctly.
  + **pengine:** Bug LF:1955 - Fix another case of filtering causing unmanaged master failures
  + **pengine:** Bug LF:1955 - Umanaged mode prevents master resources from being allocated correctly
  + **pengine:** Bug N:420538 - Anit-colocation caused a positive node preference
  + **pengine:** Correctly handle unmanaged resources to prevent them from being started elsewhere
  + **pengine:** `crm_resource` - Fix the `--migrate` command
  + **pengine:** MAke stonith-enabled default to true and warn if no STONITH resources are found
  + **pengine:** Make sure orphaned clone children are created correctly
  + **pengine:** Monitors for unmanaged resources do not need to wait for start/promote/demote actions to complete
  + **stonithd (LF 1951):** fix remote stonith operations
  + **Tools:** `crm_verify` - clean up the upgrade logic to prevent crash on invalid configurations
  + **ais:** Add support for a synchronous call to retrieve the nodes nodeid
  + **ais:** Use the agreed service number
  + **pengine:** Allow external entities to ask for a node to be shot by creating a terminate=true transient node attribute
  + **pengine:** Bug LF:1950 - Notifications do not contain all documented resource state fields
  + **pengine:** Bug N:417585 - Do not restart group children whos individual score drops below zero
  + **pengine:** Implement a true maintenance mode
  + **pengine:** Print the correct message when stonith is disabled
  + **stonithd:** exit with better code on empty host list
  + **xml:** pacemaker-0.7 is now an alias for the 1.0 schema

# Pacemaker-0.7.1 (20 Aug 2008)
- 184 commits with 513 files changed, 43408 insertions(+), 43783 deletions(-)

## Changes since 0.7.0-19

  + Fix compilation when GNUTLS isn't found
  + **admin:** Fix use-after-free in `crm_mon`
  + **Build:** Remove testing code that prevented heartbeat-only builds
  + **cib:** Use single quotes so that the xpath queries for nvpairs will succeed
  + **crmd:** Always connect to stonithd when the TE starts and ensure we notice if it dies
  + **crmd:** Correctly handle a dead PE process
  + **crmd:** Make sure async-failures cause the failcount to be incremented
  + **pengine:** Bug LF:1941 - Handle failed clone instance probes when clone-max < #nodes
  + **pengine:** Parse resource ordering sets correctly
  + **pengine:** Prevent use-of-NULL - order->rsc_rh will not always be non-NULL
  + **pengine:** Unpack colocation sets correctly
  + **Tools:** `crm_mon` - Prevent use-of-NULL for orphaned resources
  + **ais:** Add support for a synchronous call to retrieve the nodes nodeid
  + **ais:** Allow transient clients to receive membership updates
  + **ais:** Avoid double-free in error path
  + **ais:** Include in the mebership nodes for which we have not determined their hostname
  + **ais:** Spawn the PE from the ais plugin instead of the crmd
  + **cib:** By default, new configurations use the latest schema
  + **cib:** Clean up the CIB if it was already disconnected
  + **cib:** Only increment `num_updates` if something actually changed
  + **cib:** Prevent use-after-free in client after abnormal termination of the CIB
  + **Core:** Fix memory leak in xpath searches
  + **Core:** Get more details regarding parser errors
  + **Core:** Repair `expand_plus_plus` - do not call char2score on unexpanded values
  + **Core:** Switch to the libxml2 parser - its significantly faster
  + **Core:** Use a libxml2 library function for xml -> text conversion
  + **crmd:** Asynchronous failure actions have no parameters
  + **crmd:** Avoid calling glib functions with NULL
  + **crmd:** Do not allow an election to promote a node from `S_STARTING`
  + **crmd:** Do not vote if we have not completed the local startup
  + **crmd:** Fix `te_update_diff()` now that `get_object_root()` functions differently
  + **crmd:** Fix the lrmd xpath expressions to not contain quotes
  + **crmd:** If we get a join offer during an election, better restart the election
  + **crmd:** No further processing is needed when using the LRMs API call for failing resources
  + **crmd:** Only update have-quorum if the value changed
  + **crmd:** Repair the input validation logic in `do_te_invoke`
  + **cts:** CIBs can no longer contain comments
  + **cts:** Enable a bunch of tests that were incorrectly disabled
  + **cts:** The libxml2 parser wont allow v1 resources to use integers as parameter names
  + Do not use the cluster UID and GID directly.  Look them up based on the configured value of `HA_CCMUSER`
  + Fix compilation when heartbeat is not supported
  + **pengine:** Allow groups to be involved in optional ordering constraints
  + **pengine:** Allow sets of operations to be reused by multiple resources
  + **pengine:** Bug LF:1941 - Mark extra clone instances as orphans and do not show inactive ones
  + **pengine:** Determin the correct migration-threshold during resource expansion
  + **pengine:** Implement no-quorum-policy=suicide (FATE #303619)
  + **pengine:** Clean up resources after stopping old copies of the PE
  + **pengine:** Teach the PE how to stop old copies of itself
  + **Tools:** Backport `hb_report` updates
  + **Tools:** `cib_shadow` - On create, spawn a new shell with `CIB_shadow` and PS1 set accordingly
  + **Tools:** Rename `cib_shadow` to `crm_shadow`

# Pacemaker-0.7.0-19 (18 Jul 2008)
- 108 commits with 216 files changed, 4632 insertions(+), 4173 deletions(-)

## Changes added since unstable-0.7

  + **admin:** Fix use-after-free in `crm_mon`
  + **ais:** Change the tag for the ais plugin to "pacemaker" (used in openais.conf)
  + **ais:** Log terminated processes as an error
  + **cib:** Performance - Reorganize things to avoid calculating the XML diff twice
  + **pengine:** Bug LF:1941 - Handle failed clone instance probes when clone-max < #nodes
  + **pengine:** Fix memory leak in action2xml
  + **pengine:** Make `OCF_ERR_ARGS` a node-level error rather than a cluster-level one
  + **pengine:** Properly handle clones that are not installed on all nodes
  + **admin:** cibadmin - Show any validation errors if the upgrade failed
  + **admin:** `cib_shadow` - Implement `--locate` to display the underlying filename
  + **admin:** `cib_shadow` - Implement a `--diff` option
  + **admin:** `cib_shadow` - Implement a `--switch` option
  + **admin:** `crm_resource` - create more compact constraints that do not use lifetime (which is deprecated)
  + **ais:** Approximate `born_on` for OpenAIS based clusters
  + **cib:** Remove `do_id_check`, it is a poor substitute for ID validation by a schema
  + **cib:** Skip construction of pre-notify messages if no-one wants one
  + **Core:** Attempt to streamline some key functions to increase performance
  + **Core:** Clean up XML parser after validation
  + **crmd:** Detect and optimize the CRMs behavior when processing diffs of an LRM refresh
  + Fix memory leaks when resetting the name of an XML object
  + **pengine:** Prefer the current location if it is one of a group of nodes with the same (highest) score

# Pacemaker-0.7.0 (25 Jun 2008)
- 439 commits with 676 files changed, 41310 insertions(+), 52071 deletions(-)

## Changes added since stable-0.6

  + A new tool for setting up and invoking CTS
  + **Admin:** All tools now use `--node` (-N) for specifying node unames
  + **Admin:** All tools now use `--xml-file` (-x) and `--xml-text` (-X) for specifying where to find XML blobs
  + **cib:** Cleanup the API - remove redundant input fields
  + **cib:** Implement `CIB_shadow` - a facility for making and testing changes before uploading them to the cluster
  + **cib:** Make registering per-op callbacks an API call and renamed (for clarity) the API call for requesting notifications
  + **Core:** Add a facility for automatically upgrading old configurations
  + **Core:** Adopt libxml2 as the XML processing library - all external clients need to be recompiled
  + **Core:** Allow sending TLS messages larger than the MTU
  + **Core:** Fix parsing of time-only ISO dates
  + **Core:** Smarter handling of XML values containing quotes
  + **Core:** XML memory corruption - catch, and handle, cases where we are overwriting an attribute value with itself
  + **Core:** The xml ID type does not allow UUIDs that start with a number
  + **Core:** Implement XPath based versions of query/delete/replace/modify
  + **Core:** Remove some HA2.0.(3,4) compatibility code
  + **crmd:** Overhaul the detection of nodes that are starting vs. failed
  + **pengine:** Bug LF:1459 - Allow failures to expire
  + **pengine:** Have the PE do non-persistent configuration upgrades before performing calculations
  + **pengine:** Replace failure-stickiness with a simple 'migration-threshold'
  + **tengine:** Simplify the design by folding the tengine process into the crmd
  + **Admin:** Bug LF:1438 - Allow the list of all/active resource operations to be queried by `crm_resource`
  + **Admin:** Bug LF:1708 - `crm_resource` should print a warning if an attribute is already set as a meta attribute
  + **Admin:** Bug LF:1883 - `crm_mon` should display fail-count and operation history
  + **Admin:** Bug LF:1883 - `crm_mon` should display operation timing data
  + **Admin:** Bug N:371785 - `crm_resource` -C does not also clean up fail-count attributes
  + **Admin:** `crm_mon` - include timing data for failed actions
  + **ais:** Read options from the environment since objdb is not completely usable yet
  + **cib:** Add sections for `op_defaults` and `rsc_defaults`
  + **cib:** Better matching notification callbacks (for detecting duplicates and removal)
  + **cib:** Bug LF:1348 - Allow rules and attribute sets to be referenced for use in other objects
  + **cib:** BUG LF:1918 - By default, all cib calls now timeout after 30s
  + **cib:** Detect updates that decrease the version tuple
  + **cib:** Implement a client-side operation timeout - Requires LHA update
  + **cib:** Implement callbacks and async notifications for remote connections
  + **cib:** Make cib->cmds->update() an alias for modify at the API level (also implemented in cibadmin)
  + **cib:** Mark the CIB as disconnected if the IPC connection is terminated
  + **cib:** New call option 'cib_can_create' which can be passed to modify actions - allows the object to be created if it does not exist yet
  + **cib:** Reimplement get|set|delete attributes using XPath
  + **cib:** Remove some useless parts of the API
  + **cib:** Remove the 'attributes' scaffolding from the new format
  + **cib:** Implement the ability for clients to connect to remote servers
  + **Core:** Add support for validating xml against RelaxNG schemas
  + **Core:** Allow more than one item to be modified/deleted in XPath based operations
  + **Core:** Fix the `sort_pairs` function for creating sorted xml objects
  + **Core:** iso8601 - Implement `subtract_duration` and fix `subtract_time`
  + **Core:** Reduce the amount of xml copying
  + **Core:** Support value='value+=N' XML updates (in addtion to value='value++')
  + **crmd:** Add support for `lrm_ops->fail_rsc` if its available
  + **crmd:** HB - watch link status for node leaving events
  + **crmd:** Bug LF:1924 - Improved handling of lrmd disconnects and shutdowns
  + **crmd:** Do not wait for actions with a `start_delay` over 5 minutes. Confirm them immediately
  + **pengine:** Bug LF:1328 - Do not fencing nodes in clusters without managed resources
  + **pengine:** Bug LF:1461 - Give transient node attributes (in <status/>) preference over persistent ones (in <nodes/>)
  + **pengine:** Bug LF:1884, Bug LF:1885 - Implement N:M ordering and colocation constraints
  + **pengine:** Bug LF:1886 - Create a resource and operation 'defaults' config section
  + **pengine:** Bug LF:1892 - Allow recurring actions to be triggered at known times
  + **pengine:** Bug LF:1926 - Probes should complete before stop actions are invoked
  + **pengine:** Fix the standby when its set as a transient attribute
  + **pengine:** Implement a global 'stop-all-resources' option
  + **pengine:** Implement cibpipe, a tool for performing/simulating config changes "offline"
  + **pengine:** We do not allow colocation with specific clone instances
  + **Tools:** pingd - Implement a stack-independent version of pingd
  + **xml:** Ship an xslt for upgrading from 0.6 to 0.7

# Pacemaker-0.6.5 (19 Jun 2008)
- 48 commits with 37 files changed, 1204 insertions(+), 234 deletions(-)

## Changes since Pacemaker-0.6.4

  + **Admin:** Repair the ability to delete failcounts
  + **ais:** Audit IPC handling between the AIS plugin and CRM processes
  + **ais:** Have the plugin create needed /var/lib directories
  + **ais:** Make sure the sync and async connections are assigned correctly (not swapped)
  + **cib:** Correctly detect configuration changes - `num_updates` does not count
  + **pengine:** Apply stickiness values to the whole group, not the individual resources
  + **pengine:** Bug N:385265 - Ensure groups are migrated instead of remaining partially active on the current node
  + **pengine:** Bug N:396293 - Enforce mandatory group restarts due to ordering constraints
  + **pengine:** Correctly recover master instances found active on more than one node
  + **pengine:** Fix memory leaks reported by Valgrind
  + **Admin:** `crm_mon` - Misc improvements from Satomi Taniguchi
  + Bug LF#1900 - Resource stickiness should not allow placement in asynchronous clusters
  + **crmd:** Ensure joins are completed promptly when a node taking part dies
  + **pengine:** Avoid clone instance shuffling in more cases
  + **pengine:** Bug LF:1906 - Remove an optimization in `native_merge_weights()` causing group scores to behave eratically
  + **pengine:** Make use of `target_rc` data to correctly process resource operations
  + **pengine:** Prevent a possible use of NULL in `sort_clone_instance()`
  + **tengine:** Include target rc in the transition key - used to correctly determin operation failure

# Pacemaker-0.6.4 (22 May 2008)
- 55 commits with 199 files changed, 7103 insertions(+), 12378 deletions(-)

## Changes since Pacemaker-0.6.3

  + **crmd:** Bug LF:1881 LF:1882 - Overhaul the logic for operation cancelation and deletion
  + **crmd:** Bug LF:1894 - Make sure cancelled recurring operations are cleaned out from the CIB
  + **pengine:** Bug N:387749 - Colocation with clones causes unnecessary clone instance shuffling
  + **pengine:** Ensure 'master' monitor actions are cancelled `_before_` we demote the resource
  + **pengine:** Fix assert failure leading to core dump - make sure variable is properly initialized
  + **pengine:** Make sure 'slave' monitoring happens after the resource has been demoted
  + **pengine:** Prevent failure stickiness underflows (where too many failures become a `_positive_` preference)
  + **Admin:** `crm_mon` - Only complain if the output file could not be opened
  + **Common:** `filter_action_parameters` - enable legacy handling only for older versions
  + **pengine:** Bug N:385265 - The failure stickiness of group children is ignored until it reaches -INFINITY
  + **pengine:** Implement master and clone colocation by exlcuding nodes rather than setting ones score to INFINITY (similar to cs: 756afc42dc51)
  + **tengine:** Bug LF:1875 - Correctly find actions to cancel when their node leaves the cluster

# Pacemaker-0.6.3 (23 Apr 2008)
- 117 commits with 354 files changed, 19094 insertions(+), 11338 deletions(-)

## Changes since Pacemaker-0.6.2

  + **Admin:** Bug LF:1848 - `crm_resource` - Pass set name and id to `delete_resource_attr()` in the correct order
  + **Build:** SNMP has been moved to the management/pygui project
  + **crmd:** Bug LF1837 - Unmanaged resources prevent crmd from shutting down
  + **crmd:** Prevent use-after-free in lrm interface code (Patch based on work by Keisuke MORI)
  + **pengine:** Allow the cluster to make progress by not retrying failed demote actions
  + **pengine:** Anti-colocation with slave should not prevent master colocation
  + **pengine:** Bug LF 1768 - Wait more often for STONITH ops to complete before starting resources
  + **pengine:** Bug LF1836 - Allow is-managed-default=false to be overridden by individual resources
  + **pengine:** Bug LF185 - Prevent pointless master/slave instance shuffling by ignoring the master-pref of stopped instances
  + **pengine:** Bug N-191176 - Implement interleaved ordering for clone-to-clone scenarios
  + **pengine:** Bug N-347004 - Ensure clone notifications are always sent when an instance is stopped/started
  + **pengine:** Bug N-347004 - Include notification ordering is correct for interleaved clones
  + **pengine:** Bug PM-11 - Directly link `probe_complete` to starting clone instances
  + **pengine:** Bug PM1 - Fix setting failcounts when applied to complex resources
  + **pengine:** Bug PM12, LF1648 - Extensive revision of group ordering
  + **pengine:** Bug PM7 - Ensure masters are always demoted before they are stopped
  + **pengine:** Create probes after allocation to allow smarter handling of anonymous clones
  + **pengine:** Do not prioritize clone instances that must be moved
  + **pengine:** Fix error in previous commit that allowed more than the required number of masters to be promoted
  + **pengine:** Group start ordering fixes
  + **pengine:** Implement promote/demote ordering for cloned groups
  + **tengine:** Repair failcount updates
  + **tengine:** Use the correct offset when updating failcount
  + **Admin:** Add a summary output that can be easily parsed by CTS for audit purposes
  + **Build:** Make configure fail if bz2 or libxml2 are not present
  + **Build:** Re-instate a better default for LCRSODIR
  + **CIB:** Bug LF-1861 - Filter irrelvant error status from synchronous CIB clients
  + **Core:** Bug 1849 - Invalid conversion of ordinal leap year to gregorian date
  + **Core:** Drop compatibility code for 2.0.4 and 2.0.5 clusters
  + **crmd:** Bug LF-1860 - Automatically cancel recurring ops before demote and promote operations (not only stops)
  + **crmd:** Save the current CIB contents if we detect the PE crashed
  + **pengine:** Bug LF:1866 - Fix version check when applying compatibility handling for failed start operations
  + **pengine:** Bug LF:1866 - Restore the ability to have start failures not be fatal
  + **pengine:** Bug PM1 - Failcount applies to all instances of non-unique clone
  + **pengine:** Correctly set the state of partially active master/slave groups
  + **pengine:** Do not claim to be stopping an already stopped orphan
  + **pengine:** Ensure `implies_left` ordering constraints are always effective
  + **pengine:** Indicate each resources 'promotion' score
  + **pengine:** Prevent a possible use-of-NULL
  + **pengine:** Reprocess the current action if it changed (so that any prior dependencies are updated)
  + **tengine:** Bug LF-1859 - Wait for fail-count updates to complete before terminating the transition
  + **tengine:** Bug LF:1859 - Do not abort graphs due to our own failcount updates
  + **tengine:** Bug LF:1859 - Prevent the TE from interupting itself

# Pacemaker-0.6.2 (14 Feb 2008)
- 11 commits with 7 files changed, 58 insertions(+), 18 deletions(-)

## Changes since Pacemaker-0.6.1

  + **haresources2cib.py:** set default-action-timeout to the default (20s)
  + **haresources2cib.py:** update ra parameters lists
  + **SNMP:** Allow the snmp subagent to be built (patch from MATSUDA, Daiki)
  + **Tools:** Make sure the autoconf variables in haresources2cib are expanded

# Pacemaker-0.6.1 (12 Feb 2008)
- 25 commits with 37 files changed, 1323 insertions(+), 227 deletions(-)

## Changes since Pacemaker-0.6.0

  + **CIB:** Ensure changes to top-level attributes (like `admin_epoch)` cause a disk write
  + **CIB:** Ensure the archived file hits the disk before returning
  + **CIB:** Repair the ability to do 'atomic increment' updates (value="value++")
  + **crmd:** Bug #7 - Connecting to the crmd immediately after startup causes use-of-NULL
  + **CIB:** Mask `cib_diff_resync` results from the caller - they do not need to know
  + **crmd:** Delay starting the IPC server until we are fully functional
  + **CTS:** Fix the startup patterns
  + **pengine:** Bug 1820 - Allow the first resource in a group to be migrated
  + **pengine:** Bug 1820 - Check the colocation dependencies of resources to be migrated

# Pacemaker-0.6.0 (14 Jan 2008)
- 347 commits with 2272 files changed, 132508 insertions(+), 305991 deletions(-)
- This is the first release of the Pacemaker Cluster Resource Manager formerly part of Heartbeat.
- For those looking for the GUI, mgmtd, CIM or TSA components, they are now found in
  the new pacemaker-pygui project.  Build dependencies prevent them from being
  included in Heartbeat (since the built-in CRM is no longer supported) and,
  being non-core components, are not included with Pacemaker.
- Test hardware:
    + 6-node vmware cluster (sles10-sp1/256MB/vmware stonith) on a single host (opensuse10.3/2GB/2.66GHz Quad Core2)
    + 7-node EMC Centera cluster (sles10/512MB/2GHz Xeon/ssh stonith)
- Notes: Heartbeat Stack
    + All testing was performed with STONITH enabled
    + The CRM was enabled using the "crm respawn" directive
- Notes: OpenAIS Stack
    + This release contains a preview of support for the OpenAIS cluster stack
    + The current release of the OpenAIS project is missing two important
    patches that we require.  OpenAIS packages containing these patches are
    available for most major distributions at:
    http://download.opensuse.org/repositories/server:/ha-clustering
    + The OpenAIS stack is not currently recommended for use in clusters that
    have shared data as STONITH support is not yet implimented
    + pingd is not yet available for use with the OpenAIS stack
    + 3 significant OpenAIS issues were found during testing of 4 and 6 node
    clusters.  We are activly working together with the OpenAIS project to
    get these resolved.
- Pending bugs encountered during testing:
    + OpenAIS   #1736 - Openais membership took 20s to stabilize
    + Heartbeat #1750 - `ipc_bufpool_update:` magic number in head does not match
    + OpenAIS   #1793 - Assertion failure in `memb_state_gather_enter()`
    + OpenAIS   #1796 - Cluster message corruption

## Changes since Heartbeat-2.1.2-24

  + Add OpenAIS support
  + **Admin:** `crm_uuid` - Look in the right place for Heartbeat UUID files
  + **admin:** Exit and indicate a problem if the crmd exits while crmadmin is performing a query
  + **cib:** Fix `CIB_OP_UPDATE` calls that modify the whole CIB
  + **cib:** Fix compilation when supporting the heartbeat stack
  + **cib:** Fix memory leaks caused by the switch to `get_message_xml()`
  + **cib:** `HA_VALGRIND_ENABLED` needs to be set `_and_` set to 1|yes|true
  + **cib:** Use `get_message_xml()` in preference to `cl_get_struct()`
  + **cib:** Use the return value from call to write() in `cib_send_plaintext()`
  + **Core:** ccm nodes can legitimately have a node id of 0
  + **Core:** Fix peer-process tracking for the Heartbeat stack
  + **Core:** Heartbeat does not send status notifications for nodes that were already part of the cluster.  Fake them instead
  + **CRM:** Add children to `HA_Messages` such that the field name matches `F_XML_TAGNAME`
  + **crm:** Adopt a more flexible appraoch to enabling Valgrind
  + **crm:** Fix compilation when bzip2 is not installed
  + **CRM:** Future-proof `get_message_xml()`
  + **crmd:** Filter election responses based on time not FSA state
  + **crmd:** Handle all possible peer states in `crmd_ha_status_callback()`
  + **crmd:** Make sure the current date/time is set - prevents use-of-NULL when evaluating rules
  + **crmd:** Relax an assertion regrading  ccm membership instances
  + **crmd:** Use (node->processes&crm_proc_ais) to accurately update the CIB after replace operations
  + **crmd:** Heartbeat: Accurately record peer client status
  + **pengine:** Bug 1777 - Allow colocation with a resource in the Stopped state
  + **pengine:** Bug 1822 - Prevent use-of-NULL in PromoteRsc()
  + **pengine:** Implement three recovery policies based on `op_status` and `op_rc`
  + **pengine:** Parse fail-count correctly (it may be set to ININFITY)
  + **pengine:** Prevent graph-loop when stonith agents need to be moved around before a STONITH op
  + **pengine:** Prevent graph-loops when two operations have the same name+interval
  + **tengine:** Cancel active timers when destroying graphs
  + **tengine:** Ensure failcount is set correctly for failed stops/starts
  + **tengine:** Update failcount for oeprations that time out
  + **admin:** Prevent hang in `crm_mon -1` when there is no cib connection
    (patch from Junko IKEDA)
  + **cib:** Require `--force|-f` when performing potentially dangerous commands with cibadmin
  + **cib:** Tweak the shutdown code
  + **Common:** Only count peer processes of active nodes
  + **Core:** Create generic cluster sign-in method
  + **core:** Fix compilation when Heartbeat support is disabled
  + **Core:** General cleanup for supporting two stacks
  + **Core:** iso6601 - Support parsing of time-only strings
  + **core:** Isolate more code that is only needed when `SUPPORT_HEARTBEAT` is enabled
  + **crm:** Improved logging of errors in the XML parser
  + **crmd:** Fix potential use-of-NULL in string comparison
  + **crmd:** Reimpliment syncronizing of CIB queries and updates when invoking the PE
  + **tools:** `crm_mon`: Indicate when a node is both in standby mode and offline
  + **pengine:** Bug 1822 - Do not try an promote groups if not all of it is active
  + **pengine:** `on_fail=nothing` is an alias for 'ignore' not 'restart'
  + **pengine:** Prevent a potential use-of-NULL in `cron_range_satisfied()`
  + **snmp subagent:** fix a problem on displaying an unmanaged group
  + **snmp subagent:** use the syslog setting
  + **snmp:** v2 support (thanks to Keisuke MORI)
  + **snmp subagent:** made it not complain about some things if shutting down
