iptables -F
iptables -X
iptables -t nat -F
iptables -t nat -X
iptables -t mangle -F
iptables -t mangle -X
iptables -P INPUT ACCEPT
iptables -P FORWARD ACCEPT
iptables -P OUTPUT ACCEPT

iptables -A blacklist -m recent --name black_list --rcheck --seconds 300 -j DROP
iptables -N icmp-flood

iptables -A INPUT -p icmp -j icmp-flood
iptables -A FORWARD -p icmp -j icmp-flood

iptables -A icmp-flood -m limit --limit 2/s --limit-burst 4 -m comment --comment "ICMP Limit Reached" -j RETURN

iptables -A icmp-flood -m limit --limit 6/h --limit-burst 1 -j LOG --log-prefix "DDOS-Attack (ICMP) "

iptables -A icmp-flood -m recent --name black_list --set -m comment --comment "Black Listed IP" -j DROP