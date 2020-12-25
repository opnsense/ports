--- device-common.c.orig	2020-12-25 18:51:39 UTC
+++ device-common.c
@@ -216,6 +216,7 @@ int update_device_index(struct Interface *iface)
 	if (iface->props.if_index != index) {
 		dlog(LOG_DEBUG, 4, "%s if_index changed from %d to %d", iface->props.name, iface->props.if_index, index);
 		iface->props.if_index = index;
+		iface->state_info.changed = 1;
 	}
 
 	return 0;
