Delete the old nexthops on BSD after an interface goes down.

When an interface loses carrier, zebra_nhg_check_valid()/zebra_nhg_set_valid()
clear NEXTHOP_FLAG_ACTIVE on the shared nexthop group of every route using it.
kernel_rtm() skipped inactive nexthops for RTM_DELETE as well, so the delete of
the old route sent nothing and the route through the dead interface stayed in
the kernel: next to the new one with net.route.multipath=1, or instead of it
with net.route.multipath=0.  Only skip inactive nexthops when adding; deleting
a gateway that is not in the kernel gives ESRCH, which is already ignored.

Upstream: https://github.com/FRRouting/frr/pull/24221 (cea6abfd7c)
Backport: https://github.com/FRRouting/frr/pull/24290

--- zebra/rt_socket.c.orig	2026-08-31 13:24:03 UTC
+++ zebra/rt_socket.c	2026-08-31 13:24:03 UTC
@@ -108,10 +108,15 @@ static int kernel_rtm(int cmd, const struct prefix *p,
 	/* Make gateway. */
 	for (ALL_NEXTHOPS_PTR(ng, nexthop)) {
 		/*
-		 * We only want to use the actual good nexthops
+		 * We only want to install the actual good nexthops.  When
+		 * deleting, an interface going down has already cleared
+		 * ACTIVE on the nexthops that are still in the kernel, so
+		 * try all of them; a gateway that isn't there just gives
+		 * ESRCH.
 		 */
-		if (CHECK_FLAG(nexthop->flags, NEXTHOP_FLAG_RECURSIVE) ||
-		    !CHECK_FLAG(nexthop->flags, NEXTHOP_FLAG_ACTIVE))
+		if (CHECK_FLAG(nexthop->flags, NEXTHOP_FLAG_RECURSIVE))
+			continue;
+		if (cmd != RTM_DELETE && !CHECK_FLAG(nexthop->flags, NEXTHOP_FLAG_ACTIVE))
 			continue;
 
 		smplsp = NULL;
