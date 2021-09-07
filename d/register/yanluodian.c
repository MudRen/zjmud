
#include <ansi.h>
#include <login.h>
#include <command.h>

inherit ROOM;

int is_chat_room() { return 1; }

int do_wash(string arg);
int do_washto(string arg);
int do_born(string arg);
int do_pianshu(string arg);

mapping born = ([
	"��������" : "/d/guanwai/kedian",
	"��������" : "/d/beijing/kedian",
	"��³����" : "/d/taishan/kedian",
	"�ؽ�����" : "/d/changan/kezhan",
	"��ԭ����" : "/d/shaolin/kedian1",
	"��������" : "/d/xingxiu/kedian",
	"��������" : "/d/xiangyang/kedian",
	"��������" : "/d/city/kedian",
	"��������" : "/d/suzhou/kedian",
	"��������" : "/d/hangzhou/kedian",
	"��������" : "/d/fuzhou/kedian",
	"��������" : "/d/city3/kedian",
	"��������" : "/d/dali/kedian",
	"��������" : "/d/foshan/beidimiao",
	"ŷ������" : ([ "born"      : "��������",
			"surname"   : "ŷ��",
			"startroom" : "/d/baituo/dating",
		     ]),
	"�������" : ([ "born"      : "��������",
			"surname"   : "��",
			"startroom" : "/d/guanwai/xiaowu",
		     ]),
	"���ϻ���" : ([ "born"      : "��������",
			"surname"   : "��",
			"startroom" : "/d/dali/wangfugate",
		     ]),
	"Ľ������" : ([ "born"      : "��������",
			"surname"   : "Ľ��",
			"startroom" : "/d/yanziwu/cuixia",
		     ]),
]);

void create()
{
	int i, k;
	string desc;
	string *position;

	set("short", HIR "���޵�" NOR);
	set("long", @LONG
��������ֲ������˸о���һ����ĺ��⣬��������ţͷ���棬ڤ
�����䣬�����������¡�ʮ�����ޣ������ڴˣ��ز������ڴ���֮�ϣ�
��ŭ������
    ��������һ��ʯͷ���ɵĳ��ӣ�����ˮ�峺ȴ�����ף���֪����
�����ж��
    �Ա��м������ӣ���Ҳ��Ӧ����ϸ������
LONG );
	set("no_fight", 1);
	set("item_desc", ([
		"ƫ��" : "��ѡ���������ƫ����Ȼ�����ϴ�㣡\n"ZJOBACTS"��ʿ�ͣ��߱���ƫ����:pianshu msx$zj#�ǻ��ͣ�������ƫ����:pianshu zhx$zj#�����ͣ��߸���ƫ����:pianshu nlx$zj#�����ͣ�����ƫ����:pianshu mjx$zj#�����ͣ�����ƽ��20���ԡ�:pianshu jhx\n",
		"ϴ��" : "Ͷ̥֮ǰ������ϴһ�����Ե㣬ֱ���Լ����⣺\n"ZJOBACTS"ƫ�����ϴ��:wash$zj#ָ������ϴ��:washto\n",
		"ת��" : "Ͷ̥���������£��мǲ��ɲ��ʣ�"ZJBR"��ѡ�����ת���ص㣺\n"ZJOBACTS,
	]));

	set("objects", ([
		__DIR__"npc/dizangwang" : 1,
	]));

	set("no_say", "���޵�����ɭ�ֲ������������˵����\n");

	desc = query("item_desc/ת��");
	position = keys(born);

	for (i = 0, k = 1; i < sizeof(position); i++)
	{
		if (! stringp(born[position[i]]))
			continue;
		desc += sprintf("%2d. " HIW "%s" NOR ":born %s$zj#", k++, position[i], position[i]);
	}
	for (i = 0; i < sizeof(position); i++)
	{
		if (! mapp(born[position[i]]))
			continue;
		desc += sprintf("%2d. " HIC "%s" NOR ":born %s$zj#", k++, position[i], position[i]);
	}
	set("item_desc/ת��", desc+"\n");

	setup();
}

void init()
{
	add_action("do_wash", "wash");
	add_action("do_washto", "washto");
	add_action("do_born", "born");
	add_action("do_pianshu", "pianshu");
}

int do_pianshu(string arg)
{
	object me = this_player();

	if (arg=="msx")
	{
		me->set("type","��ʿ��");
		me->delete_temp("washed");
  		write(ZJOBLONG"��ѡ������ʿ�ͽ�ɫ���ԣ������趨�ɹ���"ZJBR"����ϴ���������ѡ��\n",me);
		return 1;
	}
	else if (arg=="zhx")
	{
		me->set("type","�ǻ���");
		me->delete_temp("washed");
  		write(ZJOBLONG"��ѡ�����ǻ��ͽ�ɫ���ԣ������趨�ɹ���"ZJBR"����ϴ�������������ѡ��\n",me);
		return 1;
	}
	else if (arg=="nlx")
	{
		me->set("type","������");
		me->delete_temp("washed");
  		write(ZJOBLONG"��ѡ���������ͽ�ɫ���ԣ������趨�ɹ���"ZJBR"����ϴ�������������ѡ��\n",me);
		return 1;
	}
	else if (arg=="mjx")
	{
		me->set("type","������");
		me->delete_temp("washed");
  		write(ZJOBLONG"��ѡ���������ͽ�ɫ���ԣ������趨�ɹ���"ZJBR"����ϴ�������������ѡ��\n",me);
		return 1;
	}
	else if (arg=="jhx")
	{
		me->set("type","������");
		me->delete_temp("washed");
  		write(ZJOBLONG"��ѡ���˾����ͽ�ɫ���ԣ������趨�ɹ���"ZJBR"����ϴ�������������ѡ��\n",me);
		return 1;
	}
	else
	{
  		write(ZJOBLONG"ѡ�����������ѡ��\n",me);
		return 1;
	}
}

int do_wash(string arg)
{
	int i;
	int points;
	int tmpstr, tmpint, tmpcon, tmpdex;
	object me;
	mapping my;

	if (! objectp(me = this_player()) ||
	    ! userp(me))
		return 1;

	if(!me->query("type"))
	{
  		write(ZJOBLONG"�㻹û���趨����ƫ���������趨ƫ����\n",me);
  		return 1;
	}
	write(HIC "���������ǳأ���ʱ��һ�ɼ������˽�ȥ��"NOR"\n", me);

	tmpstr = tmpint = tmpcon = tmpdex = 13;

	switch (me->query("type"))
	{
	case "��ʿ��":
		tmpstr = 30;
		tmpcon = 24;
		break;

	case "�ǻ���":
		tmpint = 30;
		tmpcon = 24;
		break;

	case "������":
		tmpcon = 30;
		tmpint = 24;
		break;

	case "������":
		tmpdex = 30;
		tmpint = 24;
		break;

	case "������":
		tmpstr = 20;
		tmpcon = 20;
		tmpint = 20;
		tmpdex = 20;
		break;

	default:
		break;
	}

	points = 80 - (tmpstr + tmpint + tmpcon + tmpdex);
	for (i = 0; i < points; i++) {
		switch (random(4)) {
		case 0: if (tmpstr < 30) tmpstr++; else i--; break;
		case 1: if (tmpint < 30) tmpint++; else i--; break;
		case 2: if (tmpcon < 30) tmpcon++; else i--; break;
		case 3: if (tmpdex < 30) tmpdex++; else i--; break;
		}
	}

	my = me->query_entire_dbase();

	my["str"] = tmpstr;
	my["int"] = tmpint;
	my["con"] = tmpcon;
	my["dex"] = tmpdex;
	my["kar"] = 10 + random(21);
	my["per"] = 10 + random(21);

	write(HIC "��ž����һ�����㱻ʪ���������˳�����"NOR"\n", me);
	write(sprintf(HIY "\n����λ�õ����������츳�ֱ��ǣ�\n"
			  "�������� " HIG "%d" HIY " �� "
			  "���ԣ��� " HIG "%d" HIY " ��\n"
			  "���ǣ��� " HIG "%d" HIY " �� "
			  "������ " HIG "%d" HIY " ��\n"
			  "��������⣬��ȥת���ɣ�"NOR"\n",
		      tmpstr, tmpint, tmpcon, tmpdex));
	me->set_temp("washed", 1);

	return 1;
}
int do_washto(string arg)
{
	int i,n;
	int points;
	int tmpstr, tmpint, tmpcon, tmpdex;
	object me;
	mapping my;

	if (! objectp(me = this_player()) || ! userp(me))
		return 1;
	if (!arg||!stringp(arg))
	{
		tell_object(me,INPUTTXT("�������������ķ�����$br#"
						"���ձ��������ԡ����ǡ�����������4����"
						"�ո�ֿ�������ע��ÿ�������ܵ���13�����30��4����֮�ͱ���Ϊ80��","washto $txt#")+"\n");
		return 1;
	}

	if(sscanf(arg, "%d %d %d %d",tmpstr,tmpint,tmpcon,tmpdex)  != 4)
	{
		tell_object(me,INPUTTXT("�����ʽ���ԣ������������������ķ�����$br#"
						"���ձ��������ԡ����ǡ�����������4����"
						"�ո�ֿ�������ע��ÿ�������ܵ���13�����30��4����֮�ͱ���Ϊ80��","washto $txt#")+"\n");
		return 1;
	}

	if(tmpstr<13||tmpint<13||tmpcon<13||tmpdex<13||tmpstr>30||tmpint>30||tmpcon>30||tmpdex>30||(tmpstr+tmpint+tmpcon+tmpdex)!=80)
	{
		tell_object(me,INPUTTXT("�����ʽ���ԣ������������������ķ�����$br#"
						"���ձ��������ԡ����ǡ�����������4����"
						"�ո�ֿ�������ע��ÿ�������ܵ���13�����30��4����֮�ͱ���Ϊ80��","washto $txt#")+"\n");
		return 1;
	}

	write(HIC "���������ǳأ���ʱ��һ�ɼ������˽�ȥ��"NOR"\n", me);

	my = me->query_entire_dbase();

	my["str"] = tmpstr;
	my["int"] = tmpint;
	my["con"] = tmpcon;
	my["dex"] = tmpdex;
	my["kar"] = 10 + random(21);
	my["per"] = 10 + random(21);

	write(HIC "��ž����һ�����㱻ʪ���������˳�����"NOR"\n", me);
	write(sprintf(HIY "\n����λ�õ����������츳�ֱ��ǣ�\n"
			  "�������� " HIG "%d" HIY " �� "
			  "���ԣ��� " HIG "%d" HIY " ��\n"
			  "���ǣ��� " HIG "%d" HIY " �� "
			  "������ " HIG "%d" HIY " ��\n"
			  "��������⣬��ȥת���ɣ�"NOR"\n",
		      tmpstr, tmpint, tmpcon, tmpdex));
	me->set_temp("washed", 1);

	return 1;
}

int do_born(string arg)
{
	object me;
	object obj;
	object item;
	mixed dest;
	string new_name;
	string msg;

	if (! objectp(me = this_player()) ||
	    ! userp(me))
		return 1;

	if (! me->query_temp("washed"))
		return notify_fail(ZJOBLONG"����ѡ����츳�������ǳ���ϴ�õ���Ͷ̥Ҳ���ٰ���\n");

	if (arg && arg[0] < 160)
		return notify_fail("������������ĵ���������born �������ϣ�������born ŷ�������Ա���Ͷ��̥��\n");

	new_name = 0;
	if (arg) sscanf(arg, "%s %s", arg, new_name);

	if (! arg || (! stringp(dest = born[arg]) && ! mapp(dest)))
	{
		message_vision("ţͷ��ݺݵĶ�$N˵����Ҫ��ʲô��Ͷ̥ȥ���\n", me);
		return 1;
	}

	if (mapp(dest) && stringp(dest["notice"]))
		return notify_fail(dest["notice"]);

	if (stringp(dest))
	{
		if (! objectp(obj = find_object(dest)))
			obj = load_object(dest);
		me->set("startroom", dest);
		me->set("born", arg);
		me->set("born_family", "û��");
	} else
	{
		if (! objectp(obj = find_object(dest["startroom"])))
			obj = load_object(dest["startroom"]);

		if (new_name)
		{
			if (! sscanf(new_name, dest["surname"] + "%*s"))
				new_name = dest["surname"] + new_name;

			if (strlen(new_name) > 8)
				return notify_fail("�������̫���ˡ�\n");

			if (strlen(new_name) < 4)
				return notify_fail("�������̫���ˡ�\n");

			if (! is_chinese(new_name))
				return notify_fail("���������������֡�\n");
		}

		if (me->query("surname") != dest["surname"])
		{
			// ������Ҫ�仯
			NAME_D->remove_name(me->name(1), me->query("id"));
			if (! new_name) new_name = dest["surname"] + me->query("purename");
			if (stringp(msg = NAME_D->invalid_new_name(new_name)))
			{
				write(msg);
				write("����Կ�����Ͷ�����ҵ�ʱ������ѡ�����֣�born <����> <����>\n");
				return 1;
			}
			me->set("surname", dest["surname"]);
			me->set("purename", new_name[strlen(dest["surname"])..<1]);
			me->set_name();
			NAME_D->map_name(me->name(1), me->query("id"));
		}

		me->set("startroom", dest["startroom"]);
		me->set("born", dest["born"]);
		me->set("born_family", arg);

		if (mapp(dest["family"]))
		{
			me->set("family", dest["family"]);
			me->assign_apprentice(dest["family"]["title"], 0);
		}
	}
	if (! objectp(obj))
	{
		message_vision("ţͷһ����ɦɦͷ˵����ô����������...\n", me);
		return 1;
	}

	message_vision("ţͷ����һ�ţ���$N���˳�ȥ��\n", me);

	// ѡ�����⼼��
	UPDATE_D->born_player(me);

	me->move(obj);
	me->set("mud_age", 0);
	me->set("age", 14);
	me->save();
//	HELP_CMD->main(me, "rules");
	message_vision("$N�����۾�����㯵��������İ�������硣\n", me);

	return 1;
}
