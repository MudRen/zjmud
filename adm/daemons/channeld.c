// channeld.c
#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <mudlib.h>
#include <net/macros.h>
#include <net/dns.h>
#include <localtime.h>

inherit F_DBASE;

#define ALLOW_LIST ({ })
#define SPECIAL_NPC     ({ "/adm/npc/youxun" })

#define REMOTE_Q	"/adm/daemons/network/services/remote_q.c"

string remove_addresses(string, int);
int filter_listener(object ppl, string only, object me);
string channel_filter(object me,string input);

static string msg_log;
static int log_from;

string query_msg_log() { return msg_log; }

mapping channels = ([
	"sys":  ([      "msg_speak": HIR "��ϵͳ��%s��%s"NOR"\n",
			"msg_emote": HIR "��ϵͳ��%s" NOR"\n",
			"msg_color": HIR,
			"only"     : "wiz",
			"name"     : "ϵͳ",
			"omit_log" : 1,
		]),

	"wiz":  ([      "msg_speak": HIY "����ʦ��%s��%s"NOR"\n",
			"msg_emote": HIY "����ʦ��%s" NOR"\n",
			"msg_color": HIY,
			"name"     : "��ʦ",
			"only"     : "wiz",
			"intermud" : GCHANNEL,
			"intermud_emote"   : 1,
			"intermud_channel" : "wiz",
			"omit_address": 0,
			"omit_log" : 1,
			"filter"   : (: $1["MUDLIB"] == MUDLIB_NAME :)
		]),

	"debug":([      "msg_speak": HIW "�����ԡ�%s��%s"NOR"\n",
			"msg_emote": HIW "�����ԡ�%s" NOR"\n",
			"msg_color": HIW,
			"name"     : "����",
			"only"     : "wiz",
			"omit_log" : 1,
		]),

	"inter":([      "msg_speak": HIR "��ͬ�ˡ�%s��%s"NOR"\n",
			"msg_emote": HIR "��ͬ�ˡ�%s" NOR"\n",
			"msg_color": HIR,
			"only"     : "league",
			"name_raw" : 1,
			"name"     : "ͬ��",
			"omit_log" : 1,
		]),

	"chat": ([      "msg_speak": HIC "�����ġ�%s��%s"NOR"\n",
			"msg_emote": HIC "�����ġ�%s" NOR"\n",
			"msg_color": HIC,
			"name"     : "����",
		]),

	"ic"  : ([      "msg_speak": HIC "������%s��%s"NOR"\n",
			"msg_emote": HIC "������%s" NOR"\n",
			"msg_color": HIC,
			"intermud" : GCHANNEL,
			"intermud_emote"   : 1,
			"intermud_channel" : "ic",
			"name"     : "����",
			"filter"   : (: $1["MUDLIB"] == MUDLIB_NAME :)
		]),

	"bill": ([      "msg_speak": YEL "�����ס�%s��%s"NOR"\n",
			"msg_color": YEL,
			"name"     : "����",
			"name_raw" : 1,
			"omit_log" : 1,
		]),

	"ultra": ([     "msg_speak": WHT "����ʦ��%s��%s"NOR"\n",
			"msg_emote": WHT "����ʦ��%s" NOR"\n",
			"msg_color": WHT,
			"name"     : "����ʦ",
			"intermud" : GCHANNEL,
			"intermud_emote"    : 1,
			"intermud_channel"  : "rultra",
			"filter"   : (: $1["MUDLIB"] == MUDLIB_NAME :)
		]),

	"shout":([      "msg_speak": HIW "%s������Х��%s"NOR"\n",
		]),

	"rumor":([      "msg_speak": HIM "��ҥ�ԡ�%s��%s"NOR"\n",
			"msg_emote": HIM "��ҥ�ԡ�%s" NOR"\n",
			"msg_color": HIM,
			"name"     : "ҥ��",
			"anonymous": "ĳ��",
		]),
	"sos":  ([      "msg_speak": HIG "��������%s��%s"NOR"\n",
			"msg_color": HIG,
			"name_raw" : 1,
			"name"     : "����",
		]),
	"party":([      "msg_speak": HIG "�����ɡ�%s��%s"NOR"\n",
			"msg_emote": HIG "�����ɡ�%s" NOR"\n",
			"msg_color": HIG,
			"only"     : "party",
			"name"     : "����",
			"omit_log" : 1,
		]),
	"family":([     "msg_speak": HIG "��ͬ�š�%s��%s"NOR"\n",
			"msg_emote": HIG "��ͬ�š�%s" NOR"\n",
			"msg_color": HIG,
			"only"     : "family",
			"name"     : "ͬ��",
			"omit_log" : 1,
		]),
	"rultra":([     "msg_speak": WHT "��������ʦ��%s��%s"NOR"\n",
			"msg_emote": WHT "��������ʦ��%s" NOR"\n",
			"msg_color": WHT,
			"name"     : "������ʦ",
			"for_listen": 1,
		]),
	"jiaoyi":([	"msg_speak": HIW "��������%s��%s"NOR"\n",
			"msg_color": HIW,
			"name"     : "������",
		]),
]);

void create()
{
	// This is required to pass intermud access check.
	seteuid(getuid());
	set("channel_id", "Ƶ������");
}

// ��¼Ƶ����Ϣ����־
void channel_log(string msg, string verb, object user)
{
	string lfn;
	mixed lt;
	int t;

	if (! mapp(channels[verb]) || ! objectp(user) || ! userp(user))
		return;

	if (channels[verb]["omit_log"])
		return;

	if (! stringp(msg_log)) msg_log = "";

	t = time();
	msg_log += sprintf(" %s(%s) on %s\n%s",
			   user->name(1), user->query("id"), log_time(), filter_color(msg));
	if (strlen(msg_log) > 8000 || t - log_from > 900)
	{
		lt = localtime(t);

		lfn = sprintf("channel/%d-%d-%d", lt[LT_YEAR],
			      lt[LT_MON] + 1, lt[LT_MDAY]);
		assure_file(LOG_DIR + lfn);
		log_file(lfn, msg_log);
		msg_log = "";
		log_from = t;
	}
}

// ����REMOTE_Q����������Ϣ����ʾ֮
void do_remote_channel(object me, string verb, string arg)
{
	object *obs;
	string msg;

	if (undefinedp(channels[verb]) || ! userp(me))
		return;

	// Ok, I will direct send the message to those people listening us.
	obs = all_interactive();
	if (stringp(channels[verb]["only"]))
		obs = filter_array(obs, (: filter_listener :),
				   channels[verb]["only"], me);

	msg = sprintf(channels[verb]["msg_emote"], arg);
	message("channel:" + verb, msg, obs);
	channel_log(msg, verb, me);

	// �����վ�㷢��EMOTE��Ϣ
	channels[verb]["intermud"]->send_msg(channels[verb]["intermud_channel"],
					     me->query("id"), me->name(1),
					     arg, 1,
					     channels[verb]["filter"]);
}

varargs int do_channel(object me, string verb, string arg, int emote)
{
	object *obs;
	string *tuned_ch, who;
	int is_player;
	string imsg = 0, local;
	string msg;

	string party;
	string family;
	string svip,tit,fname;

	// Check if this is a channel emote.
	if (sizeof(verb) > 2)
	{
		if (verb[sizeof(verb) - 1] == '*')
		{
			emote = 1;
			verb = verb[0..<2];
		}
	}

	// Check if this is a channel messsage.
	if (! mapp(channels) || undefinedp(channels[verb])) return 0;

	if (me->is_chatter())
		return notify_fail("�������Ŀǰ����ʹ�ø���Ƶ����\n");

	is_player = playerp(me);
	if (is_player && ! wizardp(me))
	{
		if (!me->query("born"))
			return notify_fail("�㻹û�����ء�����\n");

		if (! me->query("registered"))
			return notify_fail("�������ע���Ժ���ܹ�ʹ�ø���Ƶ����\n");

		if( strlen(arg)>60)
			return notify_fail("һ�仰˵��ô������ô��\n");

		if (verb == "ic" && me->query("age") < 18)
			return notify_fail("���������Ժ����ʹ��" + channels[verb]["name"] +  "Ƶ����\n");
		if (verb == "jiaoyi")
			return notify_fail("���޷�ʹ��" + channels[verb]["name"] +"Ƶ����\n");
	}

	// now we can be sure it's indeed a channel message:
	if (! stringp(arg) || arg == "" || arg == " " ) arg = "...";

	if (ultrap(me))
	{
		if (verb == "chat" && ! me->query("env/no_autoultra"))
			verb = "ultra";
	} else
		if (is_player && verb == "ultra")
			return notify_fail("������˴���ʦ��ʹ�����Ƶ���ɣ�\n");

	// player broadcasting need consume jing
	if (userp(me) && verb == "rumor" && ! objectp(present("rumor generator", me)))
		if (me->query("jing") > 200) me->add("jing", -150);
		else
		return notify_fail("��ľ�������ɢ��ҥ�ԣ�\n");

	if (userp(me) && me->ban_say(1)) return 0;

	// check if rumor or chat is blocked
	if (me->query("chblk_on"))
		return notify_fail("���Ƶ�����ر��ˣ�\n");

	if (userp(me))
	{
		if (time() - me->query_temp("last_use_channel") < 4)
		{
			if (me->query_temp("last_message") == arg)
				return notify_fail("��Ҫ�ڶ�����ʹ��Ƶ�������ظ�����Ϣ��\n");
			me->set_temp("last_message", arg);
		} else
		{
			me->set_temp("last_message", arg);
			me->set_temp("last_use_channel", time());
		}

		switch (channels[verb]["only"])
		{
		case "wiz":
			if (wiz_level(me) < 3)
				return 0;
			break;

		case "arch":
			if (wiz_level(me) < 4)
				return 0;
			break;

		case "party":
			if (! (party = me->query("banghui/name")))
				return notify_fail("�㻹���ȼ���һ��������˵�ɡ�\n");

			if (strlen(party) == 6)
			{
				party = party[0..1] + " " +
					party[2..3] + " " +
					party[4..5];
			}
			channels[verb]["msg_speak"] = HIG "��" + party +
						      "��%s��%s"NOR"\n";
			channels[verb]["msg_emote"] = HIG "��" + party +
						      "��%s" NOR"\n";
			break;

		case "family":
			if (! (family = me->query("family/family_name")))
				return notify_fail("�㻹���ȼ���һ��������˵�ɡ�\n");

			if (strlen(family) == 6)
			{
				family = family[0..1] + " " +
					 family[2..3] + " " +
					 family[4..5];
			}
			channels[verb]["msg_speak"] = HIG "��" + family +
						      "��%s��%s"NOR"\n";
			channels[verb]["msg_emote"] = HIG "��" + family +
						      "��%s" NOR"\n";
			break;

		case "league":
			if (! (fname = me->query("league/league_name")))
				return notify_fail("�㻹���Ⱥͱ��˽���ͬ����˵�ɡ�\n");

			switch (strlen(fname))
			{
			case 4:
				fname = "�� " + fname[0..1] + "  " + fname[2..3] + " ��";
				break;
	
			case 6:
				fname = "�� " + fname + " ��";
				break;
	
			case 8:
				fname = "��" + fname + "��";
				break;
	
			case 10:
				fname = "��" + fname[0..7] + "��";
				break;
			}
			channels[verb]["msg_speak"] = HIR + fname + "%s��%s"NOR"\n";
			channels[verb]["msg_emote"] = HIR + fname + "%s" NOR;
			break;
		}
	}

	if(userp(me)) arg = channel_filter(me,arg);

	if (verb == "shout")
	{
	    	if (! arg) return notify_fail("����Ҫ���ʲô��\n");
	    
		if (! wizardp(me) && userp(me))
		{
			if (me->query("neili") < 500)
				return notify_fail("�������̫��޷�������ô���������\n");
		    
			me->add("neili", - (random(200) + 300));
		}

		msg = HIW + me->name(1) + "������Х��" + arg  + NOR + "\n";
	    	shout(msg);
	    	write(HIW + "��������Х��" + arg + NOR + "\n");
		channel_log(msg, verb, me);
		return 1;
	}

	// If we speaks something in this channel, then must tune it in.
	if (userp(me))
	{
		if (! pointerp(tuned_ch = me->query("channels")))
		{
			me->set("channels", ({ verb }));
			write("�����" + channels[verb]["name"] + "Ƶ����\n");
		} else
		if (member_array(verb, tuned_ch) == -1)
		{
			me->set("channels", tuned_ch + ({ verb }));
			write("�����" + channels[verb]["name"] + "Ƶ����\n");
		}

		if (channels[verb]["for_listen"])
		{
			write("���Ƶ��ֻ��������ȡ���˵Ľ�̸��\n");
			return 1;
		}
	}

	// Support of channel emote
	if (emote && me->is_character())
	{
		string vb, emote_arg, mud;

		if (undefinedp(channels[verb]["msg_emote"]))
			return notify_fail("���Ƶ����֧�ֱ��鶯�ʡ�\n");

		if (sscanf(arg, "%s %s", vb, emote_arg) != 2)
		{
			vb = arg;
			emote_arg = "";
		}

		// internet channel emote
		if (channels[verb]["intermud_emote"])
		{
			if (sscanf(emote_arg, "%s@%s", emote_arg, mud) == 2 &&
			    htonn(mud) != mud_nname())
			{
				REMOTE_Q->send_remote_q(mud, verb, me->query("id"), emote_arg, vb);
				write("��·ѶϢ���ͳ������Ժ�\n");
				return 1;
			}

			local = sprintf("%s(%s@%s)", me->name(1), capitalize(me->query("id")),
						     upper_case(INTERMUD_MUD_NAME));
			imsg = EMOTE_D->do_emote(me, vb, emote_arg, 3, local,
						 channels[verb]["msg_color"]);
			if (stringp(imsg))
				arg = replace_string(imsg, local, me->name());
			else
				arg = 0;
		} else
		if (verb == "rumor")
			arg = EMOTE_D->do_emote(me, vb, emote_arg, 2,
					channels[verb]["anonymous"],
					channels[verb]["msg_color"]);
		else
			arg = EMOTE_D->do_emote(me, vb, emote_arg, 1,
					0, channels[verb]["msg_color"]);
	
		if (! arg && emote == 2)
			arg = (channels[verb]["anonymous"] ? channels[verb]["anonymous"]
							   : me->name(channels[verb]["name_raw"])) +
							     vb + "\n";
	
		if (! arg)
			return 0;
	}

	// Make the identity of speaker.
	if (channels[verb]["anonymous"])
	{
		who = channels[verb]["anonymous"];
	} else
	if (is_player || ! stringp(who = me->query("channel_id")))
	{
		if((tit=FAMILY_D->check_lunjian_leader(me)) && tit!="")
			svip = sprintf(YEL"%s%s "NOR,ZJSIZE(23),tit);
		else if(wizardp(me))
			svip = sprintf(HIW"%s��ʦ "NOR,ZJSIZE(23));
		else if(me->query("game_manager"))
		{
			svip = sprintf(HIW"%s���� "NOR,ZJSIZE(23));
		}
		else if(me->query("game_master"))
		{
			svip = sprintf(HIW"%s��ʦ "NOR,ZJSIZE(23));
		}
		else svip = "";
		who = me->name(channels[verb]["name_raw"]);
		if (who == me->name(1))
			who = svip + channels[verb]["msg_color"]+ZJURL("cmds:look "+me->query("id"))+ZJSIZE(22)+who+NOR;
		if (who[0] == 27) who = NOR + who;
		who += channels[verb]["msg_color"];
	}

	// Ok, now send the message to those people listening us.
	obs = all_interactive();
	if (stringp(channels[verb]["only"]))
		obs = filter_array(obs, (: filter_listener :),
				   channels[verb]["only"], me);

	if (! arg || arg == "" || arg == " ") arg = "...";

	if (emote)
	{
		string localmsg = arg;
		string ecol = channels[verb]["msg_color"];
		if (emote == 2 && ! arg)
			arg = me->name(channels[verb]["name_raw"]) +
			      ecol + "[" + me->query("id") + "@" +
			      INTERMUD_MUD_NAME + "]" + arg + "\n";
		if (! stringp(arg)) return 0;

		if (channels[verb]["msg_emote"])
			localmsg = remove_addresses(arg, 0); // 98-1-22 14:30

		if (channels[verb]["omit_address"])
			localmsg = remove_addresses(arg, 1);
		else
		if (channels[verb]["intermud_emote"])
			localmsg = remove_addresses(arg, 0);

		if (! stringp(localmsg)) return 0;
		msg = sprintf(channels[verb]["msg_emote"],
			      sprintf(localmsg, ecol, ecol, ecol));
	} else
		msg = sprintf(channels[verb]["msg_speak"], who, arg);

	if (channels[verb]["anonymous"] && userp(me))
	{
		do_channel(this_object(), "sys",
			   sprintf("%s(%s)������%sƵ��������Ϣ��",
			      me->query("name"), me->query("id"), verb));
		SPECIAL_NPC->receive_report(me, verb);
	}

	message("channel:" + ((verb == "ultra") ? "chat" : verb), msg, obs);
	channel_log(msg, verb, me);

	if (! undefinedp(channels[verb]["intermud"]) && me->is_character())
	{
		channels[verb]["intermud"]->send_msg(channels[verb]["intermud_channel"],
						     me->query("id"), me->name(1),
						     imsg ? imsg : arg, emote,
						     channels[verb]["filter"]);
	}

	return 1;
}

int filter_listener(object ppl, string only, object me)
{
	// Don't bother those in the login limbo.
	if (! environment(ppl)) return 0;

	switch (only)
	{
	case "arch":
		return (wiz_level(ppl) >= 4);

	case "wiz":
		return (wiz_level(ppl) >= 3);

	case "family":
		return (ppl->query("family/family_name") == me->query("family/family_name"));

	case "party":
		return (ppl->query("banghui/name") == me->query("banghui/name"));

	case "league":
		return (ppl->query("league/league_name") == me->query("league/league_name"));
	}

	return 1;
}

string remove_addresses(string msg, int all)
{
	int i;
	mixed tmp;
	string pattern;

	if (! stringp(msg)) return msg;
	if (all)
		pattern = "[(][A-Za-z]+@[a-zA-Z]+[0-9]+[.]?[)]";
	else
		pattern = "[(][A-Za-z]+@" + INTERMUD_MUD_NAME + "[)]";

	tmp = reg_assoc(msg, ({ pattern }), ({ 1 }));

	if (! arrayp(tmp)) return msg;
	msg = "";
	for (i = 0; i < sizeof(tmp[0]); i++)
		if (tmp[1][i] == 0) msg += tmp[0][i];
	return msg;
}

//fuck array ȫ��ʹ��СдӢ��
string *fuck = ({
      	"fuck","����","����",
        "ĸ��","���","����","��Ů",
      	"ƨ��","ƨ��","����","����",
	});

//�����������Ǹ�Admin Call �� �Ա���ʱ���� �����ļ����µ�׼��

int add_fuck(string arg)
{
	if(!arg) return 0;
	fuck += ({arg});
	return 1;
}

int del_fuck(string arg)
{
	if(!arg) return 0;
	fuck -= ({arg});
	return 1;
}

//����
string channel_filter(object me,string input)
{
	string output;
	int i,flag=0;
	
	output = input;
	
        i = strlen(input);
        while (i--) {
                if (input[i] >= 'A' && input[i] <='Z') {input[i]+=32; continue;}
                if (input[i] >= 'a' && input[i] <='z') continue;
                if (input[i] > 128)
                {
                	if(input[i]==163 && !undefinedp(input[i+1]) )
                	{
                		if ( input[i+1]>=193 && input[i+1]<=218 )
                		{
                			input[i+1] = (int)input[i+1]-96;
                			input = input[0..i-1] + input[i+1..<1];
                		}                		
                		if ( input[i+1]>=225 && input[i+1]<=250 )
                		{
                			input[i+1] = (int)input[i+1]-(96+32);
                			input = input[0..i-1] + input[i+1..<1];
                		}                		                		
                	}
                	continue;
                }
                input = input[0..i-1] + input[i+1..<1];
        }
        
	for(i=0;i<sizeof(fuck);i++){
		if (strsrch(input, fuck[i]) >= 0)
		{
			flag=1;
			//break;
			input = replace_string(input,fuck[i],"������");
		}
	}
	if(flag)
	{
		output = input;
		tell_object(me,BYEL+HIR"�����к��в����������ϵͳ���ˣ�����¼�ڰ���"NOR"\n");
		me->add_temp("bad_word",1);
		//		
	}
	return output;
}

void shoutmsg(string arg)
{
	if(!arg) return;
	message("shout", HIC "��ͨ�桿" + arg + "�ڹ���Ƶ�������к��в����Դʣ���ʱ�ر����н�̸Ƶ��������¼�ڰ����Ⱥ���"NOR"\n",users());
}
