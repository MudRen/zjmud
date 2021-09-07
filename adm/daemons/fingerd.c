// fingerd.c

#include <net/dns.h>
#include <net/messaged.h>
#include <ansi.h>
#include <getconfig.h>

int sort_by_ip(object ob1, object ob2);

void create() { seteuid(getuid()); }

int sort_by_ip(object ob1, object ob2)
{
	string ip1, ip2;

	if (! wizardp(ob1) && wizardp(ob2))
		return -1;

	if (wizardp(ob1) && ! wizardp(ob2))
		return 1;

	if (interactive(ob1) && ! interactive(ob2))
		return -1;

	if (! interactive(ob1) && interactive(ob2))
		return 1;

	if (interactive(ob1) && interactive(ob2))
	{
		ip1 = query_ip_number(ob1);
		ip2 = query_ip_number(ob2);
		if (ip1 != ip2)
			return strcmp(ip1, ip2);
	}

	return strcmp(getuid(ob1), getuid(ob2));
}

string age_string(int time)
{
	int month, day, hour, min, sec;

	sec = time % 60;
	time /= 60;
	min = time % 60;
	time /= 60;
	hour = time % 24;
	time /= 24;
	day = time % 30;
	month = time / 30;
	return (month?month + "m":"") + (day?day + "d":"") + 
	(hour?hour + "h":"") + min + "m";
}

string user_list(object *ob, int flag)
{
	object me;
	string msg;
	string *lines;
	string desc_color, desc;
	string ipname;
	int admin;
	int i;

	if (! ob || ! sizeof(ob))
		return "û���κη�����������ҡ�\n";

	me = this_player();
	admin = me->is_admin() || (SECURITY_D->query_site_privilege("finger") == "enable");
	ob = filter_array(ob, (: $1 != $(me) && $(me)->visible($1) :));
	lines = allocate(sizeof(ob));
	for (i = 0; i < sizeof(ob); i++)
	{
		ipname = admin ? query_ip_number(ob[i]) : "--------";
		if (interactive(ob[i]))
		{
			desc = query_idle(ob[i]) + "s";
			if (query_idle(ob[i]) > 120)
				desc_color = HIG;
			else
				desc_color = NOR;
		} else
		{
			switch (ob[i]->query("doing"))
			{
			case "breakup":
				desc_color = HIC;
				desc = "�ƹ�";
				break;

			case "animout":
				desc_color = HIM;
				desc = "����";
				break;

			case "closed":
				desc_color = HIY;
				desc = "�չ�";
				break;

			default:
				desc_color = HIR;
				desc = "����";
				break;
			}
		}
		lines[i] = sprintf("%s%-" + (14 + color_len(ob[i]->name(flag))) + "s%s%-14s%-14s%s%-7s" NOR "%s\n",
			      (ob[i]->name() != ob[i]->name(flag) ? HIM : NOR),
			      ob[i]->name(flag), NOR, ob[i]->query("id"),
			      age_string( (int)ob[i]->query("mud_age")), 
			      desc_color, desc, ipname);
	}

	msg = "������������������������������������������������"
	      "������������������\n" +
	      BBLU WHT "����	  �ʺ�	  ����	  ����   ����	     "NOR"\n" +
	      "������������������������������������������������"
	      "������������������\n" +
	      implode(lines, "") +
	      "������������������������������������������������"
	      "������������������\n";
	return msg;
}

string finger_all()
{
	object *ob;
	string msg, fip;
	string *lines;
	int i;
	int admin;
	object me;

	me = this_player();
	ob = users();
	msg = "";
	admin = me->is_admin() || (SECURITY_D->query_site_privilege("finger") == "enable");
	if (wiz_level(me) < 2)  // player finger
	{
		ob = filter_array(ob, (: $1 != $(me) && $(me)->visible($1) :));
		lines = allocate(sizeof(ob));
		for (i = 0; i < sizeof(ob); i++)
		{
			lines[i] = sprintf("%-14s%-14s%-14s\n",
				ob[i]->query("name"), ob[i]->query("id"),
				(interactive(ob[i]) ? (query_idle(ob[i]) + "s") : HIR "������" NOR));
		}
		return "�� " + LOCAL_MUD_NAME() + "\n" +
			"������������������������������������\n"
			+ "����	  �ʺ�	  ����\n" +
			"������������������������������������\n"
			+ implode(lines, "") +
			"������������������������������������\n";
	} else  	// wizard finger
	{
		string *counter;
		string ipname;
		int pcnt;
		int lcnt;

		pcnt = 0;
		lcnt = 0;
		counter = ({ });
		if (admin) ob = sort_array(ob, (: sort_by_ip :));
		for(i = 0; i < sizeof(ob); i++)
		{
			if (me && ! me->visible(ob[i])) continue;
			ipname = query_ip_number(ob[i]);
			if (environment(ob[i]))
			{
				pcnt++;
				if (interactive(ob[i]) &&
				    member_array(ipname, counter) == -1 )
					counter += ({ ipname });
			} else
				lcnt++;
		}

		msg = WHT "�� " + LOCAL_MUD_NAME() + ""NOR"\n" + user_list(ob, 1) +
		      sprintf("%d�������������%d����ͬ�ĵص㣬"
			      "%s��ҽ�����Ϸ�С�\n",
			      pcnt, sizeof(counter),
			      lcnt ? (string) lcnt + "��" : "Ŀǰû��");
		return msg;
	}
}

varargs string finger_user(string name, mixed me)
{
	object ob, body;
	string msg, mud;
	int public_flag;
	string cname;
	string email;
	int admin;

	object *uob;
	int same;
	int i;

	if (! me) me = this_player();
	if (sscanf(name, "%s@%s", name, mud) == 2)
		if (msg = GFINGER_Q->send_gfinger_q(mud, name, me))
			return msg;

	admin = me->is_admin() || (SECURITY_D->query_site_privilege("finger") == "enable");

	ob = new(LOGIN_OB);
	ob->set("id", name);
	if (! ob->restore())
	{
		destruct(ob);
		return "û�������ҡ�\n";
	}

	if (objectp(body = find_player(name)) && getuid(body) == name)
	{
		public_flag = body->query("env/public") ? 1 : 0;
		cname = body->query("name");
		email = body->query("email");
	} else
	{
		body = LOGIN_D->make_body(ob);
		if (! body->restore())
		{
			destruct(body);
			return "�����ҵ������˹��ϣ��޷���ѯ��\n";
		}
		public_flag = body->query("env/public") ? 1 : 0;
		cname = body->query("name");
		email = body->query("email");
		destruct(body);
	}

	if (objectp(me) && me->query("id") == name ||
	    stringp(me) && me == name)
		public_flag = 1;

	if (wiz_level(me) < 2)  // player finger
	{
		msg =  sprintf("Ӣ�Ĵ��ţ�\t%s\n��    ����\t%s\nȨ�޵ȼ���\t%s\n"
			"�����ʼ���ַ��\t%s\n�ϴ����ߣ�\t%s\n",
			ob->query("id"),
			cname,
			SECURITY_D->get_status(name),
			(public_flag) ? email : "��������",
			ctime(ob->query("last_on")));

		if (objectp(body = find_player(name)) &&
		    getuid(body) == name)
		{
			if (interactive(body))
				msg += sprintf("\n%sĿǰ���������С�\n", cname);
			else
				msg += sprintf("\n%sĿǰ�����С�\n", cname);
		}
	} else  	// wizard finger
	{
		msg =  sprintf("Ӣ�Ĵ��ţ�\t%s\n��    ����\t%s\nȨ�޵ȼ���\t%s\n"
			"�����ʼ���ַ��\t%s\n�ϴ����ߵ�ַ��\t%s( %s )\n",
			ob->query("id"),
			cname,
			SECURITY_D->get_status(name),
			email,
			ob->query("last_from"),
			ctime(ob->query("last_on"))
		);

		if (objectp(body = find_player(name)) &&
		    getuid(body) == name)
		{
			if (interactive(body))
			{
				if (admin)
				{
					uob = filter_array(all_interactive(),
						(: query_ip_number($1) == $(query_ip_number(body)) :));
					same = sizeof(uob);
					msg += sprintf("\n%sĿǰ���ڴ� %s ������", cname,
						       query_ip_number(body));
					if (same > 1)
					{
						msg += sprintf("���õ�ַһ���� %d λʹ���ߡ�\n", same);
						msg += user_list(uob, 1);
					} else
						msg += "��\n";
				} else
					msg += sprintf("\n%sĿǰ���������С�\n", cname);
			} else
				msg += sprintf("\n%sĿǰ�����С�\n", cname);

			if (body->name() != body->name(1))
				msg += sprintf("�����Ŀǰ��%s����ж���\n", body->name());
		}
	}	

	if (! objectp(body) )
	{
		msg += "\n" + cname + "Ŀǰ���������С�\n";
	}

	destruct(ob);
	return msg;
}

string get_killer()
{
	int i;
	string msg;
	object *ob = users();

	msg = "";
	for (i = 0; i < sizeof(ob); i++)
		if ((int)ob[i]->query_condition("killer"))
			msg += (ob[i]->short()+"(����ֵ��"+ ob[i]->query_condition("killer") + ")\n");
	if (msg == "")
		return "�����ΰ����á�\n";
	else
		return "���ڱ������ڼ��������˷���\n" + msg;
}

varargs string remote_finger_user(string name, int chinese_flag)
{
	object ob, body;
	string msg;
	mapping conn;
	int public_flag;
	string cname, email;

	ob = new(LOGIN_OB);
	ob->set("id", name);
	if (! ob->restore())
	{
		destruct(ob);
		return chinese_flag ? "û�������ҡ�\n" : "No such user.\n";
	}

	if (objectp(body = find_player(name)) && getuid(body) == name)
	{
		public_flag = body->query("env/public") ? 1 : 0;
		cname = body->query("name");
		email = body->query("email");
	} else
	{
		body = LOGIN_D->make_body(ob);
		if (! body->restore()) return "û�������ҡ�\n";
		public_flag = body->query("env/public") ? 1 : 0;
		cname = body->query("name");
		email = body->query("email");
		destruct(body);
	}

	if (! public_flag)
		email = "��������";

	if (chinese_flag)
		msg = sprintf("Ӣ�Ĵ��ţ�\t%s\n��    ����\t%s\nȨ�޵ȼ���\t%s\n"
			      "�����ʼ���ַ��\t%s\n�ϴ����ߣ�\t%s\n",
			      ob->query("id"),
			      cname, SECURITY_D->get_status(name), email,
			      ctime(ob->query("last_on")));
	else msg =  sprintf("Name\t: %s\nStatus\t: %s\nEmail\t: %s\nLastOn\t: %s\n",
			    capitalize(ob->query("id")),
			    SECURITY_D->get_status(name),
			    email,
			    ctime(ob->query("last_on")));

	if (objectp(body = find_player(name)) && ! body->query("env/invisible"))
	{
		if (chinese_flag)
			msg += "\n" + cname + "Ŀǰ���������С�\n";
		else
			msg += "\n" + capitalize(name) + " is currently connected.\n";
	}

	destruct(ob);
	return msg;
}

//�������� get_last_on()���ڻ�������һ���Զ�����ʱ���ʱ��
string get_last_on(string name)
{
	object ob;
	string msg;
	ob = new(LOGIN_OB);
	ob->set("id",name);
	if(!ob->restore()) return 0;
	msg = ob->query("last_on");
	destruct(ob);
	return msg;
}

string get_name(string id)
{
	object ob;
	string msg;
	ob = new(LOGIN_OB);
	ob->set("id",id);
	if(!ob->restore()) return 0;
	msg = ob->query("name");
	destruct(ob);
	return msg;
}
