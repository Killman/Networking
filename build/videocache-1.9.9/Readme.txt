Name and Description
    Videocache (http://cachevideos.com/) - A Squid url rewriter plugin to cache dynamic audio/video content from different video portals/websites.


    Videocache  is a Squid url rewriter plugin written in Python to facilitate caching youtube, aol, bing, bliptv, break, dailymotion, facebook, metacafe,
    myspace, vimeo, wrzuta, redtube, tube8, xtube, youporn videos. It can cache videos from various websites in a separate  directory  (other  than  Squid
    cache),  in  a  browsable  fashion  and  can  serve the subsequent requests from the cache. It helps in saving bandwidth and reducing load time of the
    videos. Videocache is currently used by a number of ISPs in various parts of the world.


    NOTE : If you are new to Squid or you are willing to explore Squid in details, please check my new book Squid Proxy Server 3.1:  Beginner’s  Guide  at
    http://tinyurl.com/squidbook.


Dependencies
           1. Squid >= 2.6

           2. python >= 2.4.3

           3. python-iniparse

           4. Apache or any other Web Server


Installation & Configuration
    See INSTALL file in Videocache source or visit http://cachevideos.com/installation for installation instructions.


Squid Configuration
    Depending  on  your version of Squid, open the file vc_squid_x.conf shipped with the software bundle and copy the contents to your Squid configuration
    file generally located at /etc/squid/squid.conf.


    For Squid versions 2.x, use the file vc_squid_2.conf and for Squid version 3.x, use the file vc_squid_3.conf.


    Save squid.conf and reload the squid service using the following command

      [root@proxy root]# /etc/init.d/squid reload



Running or Updating Videocache
    If you update your Videocache configuration file located at /etc/videocache.conf or you just finished installing Videocache, then you need to  perform
    the following four steps. These steps are mandatory and Videocache will not work properly unless you perform these steps.


1. Update Script (vc-update)
    NOTE : Please check http://cachevideos.com/vc-update for latest documentation.


    Once  you  are  done  updating  the Videocache configuration file and ready to deploy the new options, you should, first of all, run the update script
    (vc-update) which will update your cache directories, Apache configuration file and other system file accordingly. You can run this command as follows

      [root@proxy root]# vc-update


    To know the available options, please use the following command

      [root@proxy root]# vc-update -h



2. Videocache Scheduler
    NOTE : Please check http://cachevideos.com/vc-scheduler for latest documenation.


    Make sure that the Videocache scheduler (vc-scheduler) is running. Restart vc-scheduler using the following command

      [root@proxy root]# vc-scheduler -s restart


    To see the list of options availbale, please use the following command

      [root@proxy root]# vc-scheduler -h



3. Apache Web Server
    Restart the Apache web server using the following command

      [root@proxy root]# apachectl -k restart



4. Squid Proxy Server
    Once all the above steps have succeeded, you need to reload or restart your proxy server daemon which will run Videocache with the updating configura-
    tion.


    To reload Squid proxy server, use the following command

      [root@proxy root]# /etc/init.d/squid reload


    Or to restart Squid proxy server, use the following command

      [root@proxy root]# /etc/init.d/squid restart



Videocache Global Configuration
    Below is a description of various options you can use to configure Videocache. A description of these options  is  also  available  at  http://cachev-
    ideos.com/configure.


    Config file : /etc/videocache.conf


    client_email
           Please set this option to the email address using which you purchased Videocache license.

           IMPORTANT : This must be set appropriately otherwise Videocache will not work.


    cache_host
           The hostname or IP address of the system on which caching is being done. This is used for serving the videos from the cache.

           IMPORTANT  :  Please don’t use http:// or slashes (/). Just specify the domain name or IP address.  Additionally you can select an alternative
           port to use.
             Example : proxy.example.com or 192.168.36.204 or 192.168.36.204:81

           Default: <blank>


    videocache_user
           Use this option to set the user which should be running Videocache scheduler. This user must be same as the Squid user. On  RedHat/CentOS/SuSE,
           it’s generally squid and on Debian/Ubuntu/BSDs, it generally proxy. Default: squid.

           IMPORTANT : This must be set appropriately otherwise Videocache will not work.


    base_dir
           Base directories for caching the videos. You can specify multiple caching directories here separated by ’|’ symbol. Please try to avoid special
           characters in directory names like spaces, $ etc.
             Example : base_dir = /var/spool/videocache/ | /videocache2/stuff-new/|/new_videocache.

           Default: /var/spool/videocache/.


    base_dir_selection
           The option base_dir_selection can be used to specify the algorithm which videocache will use to store cached videos  in  cache  directories  in
           case you are using more than one cache directory. Please select one of the values as described below. Default: 2.



           ·  1 : Sequential. Videocache will fill the first cache dir, then second and so on.

           ·  2 : Round Robin (default). Videocache will round robin among cache directories to save videos.

           ·  3 : Disk Space (Highest first). Videocache will save a video to a cache directory with max free space at that time.



    disk_avail_threshold
           This  option  sets  the  minimum  available free space in Mega Bytes that is left in a partition containing a cache directory before Videocache
           treats that partition as FULL. Default: 15000.

           EXAMPLE: If disk_avail_threshold = 200, Videocache will stop caching videos in a cache directory if the free  space  available  in  that  cache
           directory is less than 200 Mega Bytes.


    enable_videocache
           This  option  controls  the  global  behavior of Videocache plugin. If it is 0, Videocache will stop caching or serving anything. This option’s
           value can be either 0 or 1. Default: 1.


    offline_mode
           When Offline Mode is enabled, Videocache will serve the videos already in cache and will skip caching the new videos. When set to 0, Videocache
           will  cache  new  video  and  when  set  to 1, Videocache will serve the already cached videos and will not cache the new videos is encounters.
           Default: 0.


    hit_threshold
           No of times a video should be requested before we start caching it. Default: 1


    max_cache_processes
           The maximum number of parallel cache processes allowed. If all connections are consumed, videos will be queued for caching. Default: 10.


    max_cache_speed
           The maximum bandwidth allocated to a cache process. For example, when max_cache_speed is set to 100, a cache process can cache  a  video  at  a
           maximum speed of 100 kilobytes per second. Set this to zero (0) if you want a cache process to use unlimited bandwidth.
             Example: max_cache_speed = 100 (Please don’t append KB or MB).

           Default: 0

           IMPORTANT : The maximum bandwidth used by Videocache at any time can not exceed max_cache_processes x max_cache_speed kilobytes per second. So,
           you can configure these options depending on bandwidth availability.


    max_cache_queue_size
           The maximum number of videos the videocache scheduler can keep in queue for caching. Videocache scheduler consumes some main memory  (~256bytes
           per  video)  for storing video metadata information. Please don’t set max_cache_queue_size too high otherwise vc-scheduler can consume signifi-
           cant amount of main memory. Default: 200000.


    cache_period
           The option cache_period specifies the time interval when the scheduler part of videocache is allowed to cache videos. You can use  this  option
           to configure videocache to cache videos in off-peak hours so that you can provide maximum possible bandwidth to your clients in peak hours. The
           format for specifying cache_period is HH1:MM1-HH2:MM2, HH3:MM3-HH4:MM4, HH5:MM5-HH6-MM6, (...). Time must be specified in 24 hour format. Also,
           HH1:MM1 must be less than HH2:MM2. Multiple time intervals can be specified by using comma (,) as a separator.
             Exmaple: cache_period = 00:20-06:30, 12:30-03:30

           The above cache_period option will force videocache to cache videos only from 00:20AM to 6:30AM and from 12:30PM to 3:30PM.

           Default: <blank>

           IMPORTANT  :  If  you  want  videocache  to  cache  videos  only  during night from 11PM to 7AM, then you’ll have to specify two time intervals
           23:00-23:59 and 00:00-07:00 to meet the condition that start time must be less than end time.


    proxy  Warning : USE THIS ONLY IF Videocache Server should go via anohter proxy.

           Proxy for http content. Default: <blank>.
             Example : http_proxy = http://<Proxy_Server_IP_OR_Domain>:<Proxy_port>/
             or http://proxy.example.com:3128/



    proxy_username
           If the above proxy requires authentication, please specify the username. Default: <blank>.


    proxy_password
           If the above proxy requires authentication, please specify the password. Default: <blank>.


    max_video_size
           The video of size more than max_video_size (MegaBytes) will not be cached. Default: 0.
             EXAMPLE: If max_video_size = 50, Videocache will not cache videos of size more than 50MB.  Set this to 0 to disable this check. Don’t append MB.



    min_video_size
           The video of size less than min_video_size (MegaBytes) will not be cached. Default: 0.
             EXAMPLE: If min_video_size = 2, Videocache will not cache videos of size less than 2MB.  Set this to 0 to disable this check. Don’t append MB.



    scheduler_pidfile
           The scheduler_logfile option can be used to specify the location of a file which will be used to track process  ID  of  the  currently  running
           Videocache scheduler. Default: /var/run/videocache.pid.


    enable_videocache_cleaner
           Enables  the Videocache cleaner script which will remove videos from cache which have not been used since long. The value of this option can be
           0 or 1. Default: 1.


    video_lifetime
           The maximum life of a video in cache without being used. If the video was not accessed for more than video_lifetime days, it’ll be removed from
           the cache. The unit of video_lifetime is days. Default: 30.
             Example : video_lifetime = 15 will remove videos which were not used since last 15 or more days.



    logformat, scheduler_logformat, cleaner_logformat
           Logformat allows you to get log messages in your preferred format. The logformat, scheduler_logformat, cleaner_logformat are applicable to main
           Videocache log, scheduler log and cleaner log respectively. Use the format codes described below.
             %  - A literal % character
             ts - Seconds since epoch
             tu - Time in millisecond
             tl - Local Time
             tg - GMT Time
             p  - Process ID of the process logging the message
             s  - Severity level of the log message
             i  - Client’s IP address
             w  - Website ID (eg. YOUTUBE/FACEBOOK/VIMEO etc.)
             c  - Status Code (CACHE_HIT/CACHE_MISS etc.)
             v  - Video ID of current video
             m  - Additional Message (for verbose logs)
             d  - Debug message (for debugging purpose)

             Example: logformat = %ts %i %w %c %v

           Default logformats:
             logformat = %tl %p %s %i %w %c %v %m %d
             scheduler_logformat =  %tl %p %s %i %w %c %v %m %d
             cleaner_logformat = %tl %p %s %w %c %v %m %d



    timeformat
           You can use a custom format for displaying time in log messages. Use the format codes described below

           IMPORTANT : This format will be applicable to localtime and GMT time in the log messages.
             %a    Abbreviated weekday name (Sun, Mon, Tue, Wed, Thu, Fri, Sat)
             %A    Full weekday name (Sunday, Monday, ...)
             %b    Abbreviated month name (Jan, Feb, Mar, ...)
             %B    Full month name (January, February, ...)
             %d    Day of the month as a decimal number [01..31]
             %H    Hour (24-hour clock) as a decimal number [00..23]
             %I    Hour (12-hour clock) as a decimal number [01..12]
             %j    Day of the year as a decimal number [001..366]
             %m    Month as a decimal number [01..12]
             %M    Minute as a decimal number [00..59]
             %p    Either AM or PM
             %S    Second as a decimal number [00..59]
             %y    Year without century as a decimal number [00..99]
             %Y    Year with century as a decimal number

             Example: timeformat = %B %d, %Y %H:%M:%S

           Default: %d/%b/%Y:%H:%M:%S


    logdir Directory where Videocache logs will be stored. Default: /var/log/videocache/.


    enable_videocache_log, enable_scheduler_log, enable_cleaner_log, enable_trace_log
           Using these options, you can control the logging activity of the various components of videocache. When a particular option is set to 0, video-
           cache will not log anything to the respective logfile.

           Default: 1


    logfile, scheduler_logfile, cleaner_logfile, tracefile
           The name of log file can be specified using different logfile options. Please avoid any special characters in filename.

           Default logfile names:
             logfile : videocache.log
             scheduler_logfile : scheduler.log
             cleaner_logfile : cleaner.log
             tracefile : trace.log



    max_logfile_size, max_scheduler_logfile_size, max_cleaner_logfile_size, max_tracefile_size
           Maximum size of logfiles specified above. The size is in mega bytes.

           IMPORTANT : Please don’t use max_logfile_size = 10MB. Don’t append MB.

           Default logfile sizes:
             max_logfile_size : 10
             max_scheduler_logfile_size : 10
             max_cleaner_logfile_size : 10
             max_tracefile_size : 10



    max_logfile_backups, max_scheduler_logfile_backups, max_cleaner_logfile_backups, max_tracefile_backups
           The  logfiles are automatically rotated once they have exceeded the max_logfile_size. The max_logfile_backups is the number of backup files you
           want to keep.
             Example: max_logfile_backups = 2 will keep videocache.log and videocache.log.1 and videocache.log.2 as logfiles.

           Default logfile backups:
             max_logfile_backups : 10
             max_scheduler_logfile_backups : 10
             max_cleaner_logfile_backups : 5
             max_tracefile_backups : 1



    enable_youtube_cache
           This option enables the caching of Youtube videos. This option’s value can be either 0 or 1. Default: 1.


    max_youtube_video_quality
           This option forces the maximum video quality from Youtube. If a user browses a video in higher quality mode, videocache will  still  cache  the
           video in the format specified below or a lower quality format depending on the availability.
             Valid values : 240p, 360p, 480p, 720p, 1080p, 3072p (Please don’t use quotes)

           Default: 480p


    min_youtube_views
           This option will help in enhancing the performance of videocache. If min_youtube_views is set to 10000, then videocache will cache a video only
           if it has received at least 10000 views on Youtube. Otherwise, it’ll not be cached at all. Set this to 0  to  disable  this  option.   Default:
           10000


    rpc_host
           XMLRPCServer  is used for memory sharing across different instances of Videocache. Leave these settings as it is if you don’t have a fair idea
           of XMLRPCServer. This will be same as cache_host in almost all the cases. Default: 127.0.0.1.


    rpc_port
           Please make sure this port is not currently in use. If it is in use by some other program, change this to some port above 1024 which is not  in
           use by any other program. Default: 9100.


See Also
           ·  Squid Proxy Server 3.1: Beginner’s Guide : http://tinyurl.com/squidbook

           ·  Project Website : http://cachevideos.com/

           ·  How to configure Squid : http://gofedora.com/how-to-configure-squid-proxy-server/


Author
    Kulbir Saini <saini AT saini.co.in>. Check http://saini.co.in/ for more information on author.


Bugs, Suggestions, Comments
    Please visit http://cachevideos.com/forum/.


Copyright
    Copyright (c) 2008-2011 Kulbir Saini.
