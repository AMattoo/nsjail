/*

   nsjail
   -----------------------------------------

   Copyright 2014 Google Inc. All Rights Reserved.
   Copyright 2016 Sergiusz Bazanski. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

*/

#ifndef NS_NSJAIL_H
#define NS_NSJAIL_H

#include <linux/filter.h>
#include <netinet/ip6.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <string>
#include <vector>

#include "logs.h"

static const int nssigs[] = {
    SIGINT,
    SIGQUIT,
    SIGUSR1,
    SIGALRM,
    SIGCHLD,
    SIGTERM,
};

struct pids_t {
	pid_t pid;
	time_t start;
	char remote_txt[64];
	struct sockaddr_in6 remote_addr;
	int pid_syscall_fd;
};

struct mount_t {
	std::string src;
	std::string src_content;
	std::string dst;
	std::string fs_type;
	std::string options;
	uintptr_t flags;
	bool isDir;
	bool isSymlink;
	bool mandatory;
	bool mounted;
};

struct idmap_t {
	uid_t inside_id;
	uid_t outside_id;
	size_t count;
	bool is_newidmap;
};

enum ns_mode_t {
	MODE_LISTEN_TCP = 0,
	MODE_STANDALONE_ONCE,
	MODE_STANDALONE_EXECVE,
	MODE_STANDALONE_RERUN
};

struct nsjconf_t {
	const char* exec_file;
	bool use_execveat;
	int exec_fd;
	const char** argv;
	std::string hostname;
	std::string cwd;
	std::string chroot;
	int port;
	std::string bindhost;
	std::string logfile;
	logs::llevel_t loglevel;
	bool daemonize;
	time_t tlimit;
	size_t max_cpus;
	bool keep_env;
	bool keep_caps;
	bool disable_no_new_privs;
	uint64_t rl_as;
	uint64_t rl_core;
	uint64_t rl_cpu;
	uint64_t rl_fsize;
	uint64_t rl_nofile;
	uint64_t rl_nproc;
	uint64_t rl_stack;
	unsigned long personality;
	bool clone_newnet;
	bool clone_newuser;
	bool clone_newns;
	bool clone_newpid;
	bool clone_newipc;
	bool clone_newuts;
	bool clone_newcgroup;
	enum ns_mode_t mode;
	bool is_root_rw;
	bool is_silent;
	bool skip_setsid;
	unsigned int max_conns_per_ip;
	size_t tmpfs_size;
	std::string proc_path;
	bool is_proc_rw;
	bool iface_lo;
	std::string iface_vs;
	std::string iface_vs_ip;
	std::string iface_vs_nm;
	std::string iface_vs_gw;
	const char* cgroup_mem_mount;
	const char* cgroup_mem_parent;
	size_t cgroup_mem_max;
	const char* cgroup_pids_mount;
	const char* cgroup_pids_parent;
	unsigned int cgroup_pids_max;
	const char* cgroup_net_cls_mount;
	const char* cgroup_net_cls_parent;
	unsigned int cgroup_net_cls_classid;
	const char* cgroup_cpu_mount;
	const char* cgroup_cpu_parent;
	unsigned int cgroup_cpu_ms_per_sec;
	std::string kafel_file_path;
	std::string kafel_string;
	struct sock_fprog seccomp_fprog;
	long num_cpus;
	uid_t orig_uid;
	std::vector<mount_t> mountpts;
	std::vector<pids_t> pids;
	std::vector<idmap_t> uids;
	std::vector<idmap_t> gids;
	std::vector<std::string> envs;
	std::vector<int> openfds;
	std::vector<int> caps;
};

#endif /* _NSJAIL_H */
