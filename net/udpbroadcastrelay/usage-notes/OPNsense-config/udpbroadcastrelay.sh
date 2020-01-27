#!/bin/sh
#
# $FreeBSD$
#

# PROVIDE: udpbroadcastrelay
# KEYWORD: shutdown

. /etc/rc.subr

name="udpbroadcastrelay"
rcvar="udpbroadcastrelay_enable"
command="/usr/local/sbin/udpbroadcastrelay"
extra_commands="reload"
reload_cmd="udpbroadcastrelay_reload"
load_rc_config "udpbroadcastrelay.conf"


if [ -n "$2" ]; then
   eval udpbroadcastrelay_flags=\$udpbroadcastrelay_${2}
   pidfile="/var/run/udpbroadcastrelay_$2.pid"
fi


udpbroadcastrelay_start () {
   udpbroadcastrelay_status
   if [ $? -eq 0 ]; then # already running
      return 0
   fi
   run_rc_command "start"
   if [ $? -eq 0 ]; then
      cmd_string=`basename ${procname:-${command}}`

      ps_pid=`ps ax -o pid= -o command= | grep $cmd_string | grep -e "$udpbroadcastrelay_flags" | grep -v grep | awk '{ print $1 }'`
      if [ -z "$ps_pid" ]; then
         err 1 "Cannot get pid for $cmd_string $udpbroadcastrelay_flags"
      fi
      return $?
   fi
   return 1
}

udpbroadcastrelay_stop () {
   udpbroadcastrelay_status
   if [ $? -eq 1 ]; then # already stopped
      return 0
   fi
   run_rc_command "stop"
   if [ $? -ne 0 ]; then
      err 1 "Cannot stop udpbroadcastrelay with pid from $pidfile"
   fi
   rm -f $pidfile
   return $?
}

udpbroadcastrelay_restart () {
   udpbroadcastrelay_stop
   if [ $? -ne 0 ]; then
      return $?
   fi
   udpbroadcastrelay_start
   return $?
}

udpbroadcastrelay_status () {
   if [ -z "$pidfile" ]; then
      err 1 "Instance name unknown"
   fi
   run_rc_command "status"
   return $?
}

udpbroadcastrelay_reload () {
   
   echo "In Reload" >> "/tmp/udr.log"
   udpbroadcastrelay_flags=""
   pidfile=""
   # get running instances
   ps ax -o pid= -o command= | grep "udpbroadcastrelay" | grep -v grep | while read line; do
      # get instance name
      instance=`echo $line | awk '{printf "%s", $4 }' | sed 's/\./_/g'`
      # get instance flags
      instance_flags="${line#*udpbroadcastrelay}"
      # check if it should run
      echo 
      eval udpbroadcastrelay_flags=\$udpbroadcastrelay_${instance}

      if [ -n "$udpbroadcastrelay_flags" -a "$udpbroadcastrelay_flags" = "$instance_flags" ]; then
         echo "running instance $instance match config"
         continue
      fi
      echo "running instance $instance not configured"
      udpbroadcastrelay_flags=$instance_flags
      pidfile="/var/run/udpbroadcastrelay_$instance.pid"
      udpbroadcastrelay_stop
   done
   # start configured instances
  
   if [ -n "$udpbroadcastrelay_instances" ]; then
 
      for i in $udpbroadcastrelay_instances; do
         eval udpbroadcastrelay_flags=\$udpbroadcastrelay_${i}
         pidfile="/var/run/udpbroadcastrelay_$i.pid"
         run_rc_command "start"
      done
   fi
   return 0
}

case $1 in
   start)
    
      if [ -z "$udpbroadcastrelay_flags=\$udpbroadcastrelay_${i}" -o -z "$pidfile" ]; then
         if [ -n "$udpbroadcastrelay_instances" ]; then
            for i in $udpbroadcastrelay_instances; do
               eval udpbroadcastrelay_flags=\$udpbroadcastrelay_${i}
               pidfile="/var/run/udpbroadcastrelay_$i.pid"
              
               udpbroadcastrelay_start
            done
         fi
      else
         udpbroadcastrelay_start
      fi
      exit $?
      ;;
   stop)
      if [ -z "$udpbroadcastrelay_flags" -o -z "$pidfile" ]; then
         if [ -n "$udpbroadcastrelay_instances" ]; then
            for i in $udpbroadcastrelay_instances; do
               eval udpbroadcastrelay_flags=\$udpbroadcastrelay_${i}
               pidfile="/var/run/udpbroadcastrelay_$i.pid"
               udpbroadcastrelay_stop
            done
         fi
      else
         udpbroadcastrelay_stop
      fi
      exit $?
      ;;
   restart)
      if [ -z "$udpbroadcastrelay_flags" -o -z "$pidfile" ]; then
         if [ -n "$udpbroadcastrelay_instances" ]; then
            for i in $udpbroadcastrelay_instances; do
               eval udpbroadcastrelay_flags=\$udpbroadcastrelay_${i}
               pidfile="/var/run/udpbroadcastrelay_$i.pid"
               udpbroadcastrelay_restart
            done
         fi
      else
         udpbroadcastrelay_restart
      fi
      exit $?
      ;;
   status)
      if [ -z "$udpbroadcastrelay_flags" -a -z "$pidfile" ]; then
         if [ -n "$udpbroadcastrelay_instances" ]; then
            for i in $udpbroadcastrelay_instances; do
               eval udpbroadcastrelay_flags=\$udpbroadcastrelay_${i}
               pidfile="/var/run/udpbroadcastrelay_$i.pid"
               udpbroadcastrelay_status
            done
         fi
      else
         udpbroadcastrelay_status
      fi
      exit $?
      ;;
   reload)
      udpbroadcastrelay_reload;
      exit $?
      ;;
esac
