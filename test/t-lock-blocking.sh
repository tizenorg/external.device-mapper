#!/bin/sh
# Copyright (C) 2008 Red Hat, Inc. All rights reserved.
#
# This copyrighted material is made available to anyone wishing to use,
# modify, copy, or redistribute it subject to the terms and conditions
# of the GNU General Public License v.2.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

test_description='test some blocking / non-blocking multi-vg operations'

. ./test-utils.sh

aux prepare_devs 3
test -n "$LOCAL_CLVMD" && exit 200
pvcreate $dev1 $dev2
vgcreate $vg $dev1 $dev2

# if wait_for_locks set, vgremove should wait for orphan lock
# flock process should have exited by the time first vgremove completes
flock -w 5 $TESTDIR/var/lock/lvm/P_orphans -c "sleep 10" &
flock_pid=`jobs -p`
vgremove --config 'global { wait_for_locks = 1 }' $vg
not vgremove --config 'global { wait_for_locks = 1 }' $vg
not ps $flock_pid # finished

# if wait_for_locks not set, vgremove should fail on non-blocking lock
# we must wait for flock process at the end - vgremove won't wait
vgcreate $vg $dev1 $dev2
flock -w 5 $TESTDIR/var/lock/lvm/P_orphans -c "sleep 10" &
flock_pid=`jobs -p`
not vgremove --config 'global { wait_for_locks = 0 }' $vg
ps $flock_pid # still running
kill $flock_pid
