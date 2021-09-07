/*
 * File    : gtell.c
 * Creator : Pinkfish@Discworld
 *	 : Grendel@Tmi-2
 * When    : 93-08-15
 *
 * This file is part of the tmi mudlib.  Please keep this header intact.
 *
 * This protocol is used to convey intermud tells.
 */

// Ported to ES2 mudlib by Annihilator (06/16/95)

#include <command.h>
#include <net/dns.h>
#include <net/macros.h>
#include <net/daemons.h>

inherit F_CLEAN_UP;
inherit F_DBASE;

// Tell to someone on another mud.

int send_gtell(string mud, string wiz_to, object source, string msg)
{
	mapping minfo;

	if (! ACCESS_CHECK(previous_object()) &&
	    is_root(previous_object())) return 0;

	mud = htonn(mud);
	if (mud == mud_nname() || ! source) return 0;

	minfo = (mapping)DNS_MASTER->query_mud_info(mud);
	if (! minfo)
	{
		write(LOCAL_MUD_NAME() + "��û�к� " + mud + " ��ϵ�ϡ�\n");
		return 0;
	}


	msg = replace_string(msg, "|", "");
	msg = replace_string(msg, "@@@", "");
	DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
		"@@@" + DNS_GTELL +
		"||NAME:" + Mud_name() +
		"||PORTUDP:" + udp_port() +
		"||WIZTO:" + wiz_to +
		"||WIZFROM:" + capitalize(source->query("id")) +
		"||CNAME:" + source->name(1) +
		"||WIZ_LEVEL:" + wiz_level(source) +
		"||MSG:" + msg + "@@@\n");
	return 1;
}

// Someone on another mud has sent us a tell.
void incoming_request(mapping info)
{
	mapping minfo;
	object pl;
	string reply;

	if (info["NAME"] && info["PORTUDP"])
	{
		// dont want to tell to ourselves
		if (info["NAME"] == Mud_name())	return;

		// get our info about the sender, ping them if we don't have any
		minfo = DNS_MASTER->query_mud_info(info["NAME"]);
		if (! minfo || ! DNS_MASTER->dns_mudp(info["NAME"]))
			PING_Q->send_ping_q(info["HOSTADDRESS"], info["PORTUDP"]);

		if (minfo && minfo["HOSTADDRESS"] != info["HOSTADDRESS"])
		{
			// Its been faked! 
			dns_log("dns_fake", "Tell: " + info["WIZFROM"] + "@" + info["NAME"] +
				"("+info["HOSTADDRESS"] + ") telling " + info["WIZTO"] +
				" " + info["MSG"] + "\n");
			DNS_MASTER->send_udp(minfo["HOSTADDRESS"], minfo["PORTUDP"],
				"@@@" + DNS_WARNING +
				"||MSG: Faked gtell message " + info["WIZFROM"]+
				"@" + info["NAME"] + "> " + info["WIZTO"]+
				" " + info["MSG"] +
				"||FAKEHOST:" + info["name"]+
				"@@@\n");
			return ;
		}

		reply = TELL_CMD->remote_tell(info["CNAME"], info["WIZFROM"], info["NAME"],
					      info["WIZTO"], info["MSG"],
					      stringp("WIZ_LEVEL") ? atoi(info["WIZ_LEVEL"]) : 0);
	
		(AUX_PATH + "affirmation_a")->send_affirmation_a(info["HOSTADDRESS"],
			info["PORTUDP"], "Gtell@" + Mud_name(),
			info["WIZFROM"], reply, "gtell");
	}
}
