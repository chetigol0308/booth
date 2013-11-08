/* 
 * Copyright (C) 2011 Jiaju Zhang <jjzhang@suse.de>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _TRANSPORT_H
#define _TRANSPORT_H

#include "booth.h"

struct booth_node {
	int nodeid;
	int type;
	int local;

	char addr_string[BOOTH_NAME_LEN];

	int tcp_fd;

	unsigned short family;
	union {
		struct in_addr in4;
		struct in6_addr in6;
	};
	int addrlen;
} __attribute__((packed));

typedef enum {
	TCP = 0,
	UDP = 1,
	SCTP = 2,
	TRANSPORT_ENTRIES = 3,
} transport_layer_t;

typedef enum {
	ARBITRATOR = 1,
	SITE,
	CLIENT,
} node_type_t;

struct booth_transport {
	const char *name;
	int (*init) (void *);
	int (*get_myid) (void);
	int (*open) (struct booth_node *);
	int (*send) (struct booth_node *, void *, int);
	int (*recv) (struct booth_node *, void *, int);
	int (*broadcast) (void *, int);
	int (*close) (struct booth_node *);
	int (*exit) (void);
};

struct booth_transport booth_transport[TRANSPORT_ENTRIES];
int find_myself(struct booth_node **me, int fuzzy_allowed);

#endif /* _TRANSPORT_H */
