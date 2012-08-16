/*
 * Copyright (C) 2001-2004 Sistina Software, Inc. All rights reserved.
 * Copyright (C) 2004-2010 Red Hat, Inc. All rights reserved.
 *
 * This file is part of LVM2.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions
 * of the GNU Lesser General Public License v.2.1.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef _LVM_PV_H
#define _LVM_PV_H

struct id;
struct device;
struct format_type;
struct volume_group;

struct physical_volume {
	struct id id;
	struct device *dev;
	const struct format_type *fmt;

	/*
	 * vg_name and vgid are used before the parent VG struct exists.
	 * FIXME: Investigate removal/substitution with 'vg' fields.
	 */
	const char *vg_name;
	struct id vgid;

	/*
	 * 'vg' is set and maintained when the PV belongs to a 'pvs'
	 * list in a parent VG struct.
	 */
	struct volume_group *vg;

	uint64_t status;
	uint64_t size;

	/* physical extents */
	uint32_t pe_size;
	uint64_t pe_start;
	uint32_t pe_count;
	uint32_t pe_alloc_count;
	unsigned long pe_align;
	unsigned long pe_align_offset;

	struct dm_list segments;	/* Ordered pv_segments covering complete PV */
	struct dm_list tags;
};

char *pv_fmt_dup(const struct physical_volume *pv);
char *pv_name_dup(const struct physical_volume *pv);
struct device *pv_dev(const struct physical_volume *pv);
const char *pv_vg_name(const struct physical_volume *pv);
char *pv_attr_dup(struct dm_pool *mem, const struct physical_volume *pv);
const char *pv_dev_name(const struct physical_volume *pv);
char *pv_uuid_dup(const struct physical_volume *pv);
char *pv_tags_dup(const struct physical_volume *pv);
uint64_t pv_size(const struct physical_volume *pv);
uint64_t pv_size_field(const struct physical_volume *pv);
uint64_t pv_dev_size(const struct physical_volume *pv);
uint64_t pv_free(const struct physical_volume *pv);
uint64_t pv_status(const struct physical_volume *pv);
uint32_t pv_pe_size(const struct physical_volume *pv);
uint64_t pv_pe_start(const struct physical_volume *pv);
uint32_t pv_pe_count(const struct physical_volume *pv);
uint32_t pv_pe_alloc_count(const struct physical_volume *pv);
uint64_t pv_mda_size(const struct physical_volume *pv);
uint64_t pv_mda_free(const struct physical_volume *pv);
uint64_t pv_used(const struct physical_volume *pv);
uint32_t pv_mda_count(const struct physical_volume *pv);
uint32_t pv_mda_used_count(const struct physical_volume *pv);
unsigned pv_mda_set_ignored(const struct physical_volume *pv, unsigned ignored);
int is_orphan(const struct physical_volume *pv);
int is_missing_pv(const struct physical_volume *pv);
int is_pv(const struct physical_volume *pv);

#endif /* _LVM_PV_H */