--- client/system/info_freebsd.go.orig	1979-11-30 00:00:00 UTC
+++ client/system/info_freebsd.go
@@ -39,10 +39,10 @@ func GetInfo(ctx context.Context) *Info {
 	systemHostname, _ := os.Hostname()
 
 	return &Info{
-		GoOS:               runtime.GOOS,
+		GoOS:               "linux",
 		Kernel:             osInfo[0],
 		Platform:           runtime.GOARCH,
-		OS:                 osName,
+ 		OS:                 strings.Replace(osName, "FreeBSD", "FakeBSD", -1),
 		OSVersion:          osVersion,
 		Hostname:           extractDeviceName(ctx, systemHostname),
 		CPUs:               runtime.NumCPU(),
