// Object: /d/xiangyang/obj/shuipiao.c  ҩ��ׯˮư
// Date: Feb . 3 2002 by Pound

#include <ansi.h>
#include <localtime.h>

inherit ITEM;
string long_desc();
string* use_phrase = ({"��", "��", });
string* use_name = ({"ˮư�е�", "ư�е�", "ˮư���", "ư���", "", });
string* use_what = ({"ˮ", "��ˮ", });
string* use_arj = ({"�������", "�������ɵ�", "С�������", "����", "���ɵ�", "", "��������", "����", });
string* use_action = ({"��", "��", });
string* use_where = ({"ǰ", "��", "��", "��", "��", "��", });
string* action_arj = ({"һ��", "��", "��", "һ��", });

void create()
{
	set_name("ˮư", ({"shui piao", "shuipiao", "piao"}));
	set_weight(100);
	if (clonep())
	    set_default_object(__FILE__);
	else
	{
	    set("long", "����һ������Ҩˮ����������ˮư��\n");
	    set("unit", "��");
	    set("material", "wood");
	    set("value", 0);
	    set("no_give", 1);
	    set("no_steal", 1);
	    set("no_drop", 1);
	}
}

int init()
{
	add_action("do_yao", "yao");
	add_action("do_yao", "Ҩ");
	add_action("do_sa", "sa");
	add_action("do_sa", "��");
	add_action("do_sa", "jiao");
	add_action("do_sa", "��");
}

int do_yao(string arg)
{
	object ob1, ob2, me;
	string what, target;

	me = this_player();
	if (! arg)
	    return notify_fail("��ҪҨʲô��\n");
	if (! objectp(ob1 = present("shui piao", me)))
	    return notify_fail("��û��ˮư����ôҨˮ��\n");

	if (sscanf(arg, "%s from %s", what, target) == 2)
	{
	    if (what != "shui" && what != "water" && what != "ˮ") 
		return notify_fail("��ҪҨʲô��\n");
	    if (! objectp(ob2 = present(target, environment(me)))) 
		return notify_fail("��Ҫ������Ҩˮ��\n");
	    if (me->is_busy())
		return notify_fail("����æ����Ҩ������\n");
	    if (! ob2->query("yaowang") && (! wizardp(me)))
		return notify_fail("����û�����ҩ��ׯ���Ƶ�ľͰ��\n");
// ������Ϸ����������ʦ����ˮͰ���������ҡ�
	    if (ob2->query("water_level") <= 0)
		return notify_fail("ľͰ���Ѿ�ûˮ�ˡ�\n");

	    if (ob1->query("filled")) // �����Ѿ���ˮ��ˮư
	    {
		message_vision("$N��ˮư���ˮ����ˮͰ�����˼��£�����Ҩ��һưˮ��\n", me);
		ob1->set("water_level", ob2->query("water_level"));
		me->start_busy(1 + random(2));
		me->receive_damage("jing", (22 + random(3)));
		ob2->set("long", (: long_desc :));
		return 1;
	    }

	    message_vision("$N��ˮͰ��Ҩ��һưˮ��\n", me);
	    ob1->set("filled", 1);
	    ob2->add("water_level", -1);
	    ob1->set("water_level", ob2->query("water_level"));
	    me->start_busy(1 + random(2));
	    me->receive_damage("jing", (16 + random(3)));
	    ob2->set("long", (: long_desc :)); // �˴�����Ҫ��������һ��ˮͰ�Ĳ�����
	    return 1;
	}
	else
	{   
// ���Ͱ��Ū���ˣ����Ե�é�����СϪ��Ҩˮ��
	    if (arg != "shui" && arg != "water") 
		return notify_fail("��ҪҨʲô��\n");
	    if (environment(me) != find_object("/d/xiangyang/xibian")) 
		return notify_fail("������Ҩ�������õ�ˮ��\n");
	    if (me->is_busy()) 
		return notify_fail("����æ����Ҩ������\n");

	    message_vision("$N�߽�Ϫ�ߣ������������峺��Ϫˮ��Ҩ��һưˮ��\n", me);
	    ob1->set("filled", 1);
	    me->start_busy(1 + random(2));
	    me->receive_damage("jing", (20 + random(3)));
	    return 1;
	}
}

int do_sa(string arg)
{
	mixed *local;
	int totaltime, water_time, curent_time, seeded, hour, day, month;
	object room, ob, me, obnew, pound;
	string msg;

	ob = this_object();
	me = this_player();
	room = find_object("/d/xiangyang/huafang.c");
	local = localtime(time());

	hour = 100;
	day = 10000;
	month = 1000000;
	curent_time = (local[LT_MON] + 1) * month + local[LT_MDAY] * day + local[LT_HOUR] * hour + local[LT_MIN];
// ����11��23������3��21���õ���curent_time����11231521

// û��ˮư��ư��û��ˮ��æʱ���ж�
	if (! objectp(ob = present("shui piao", me)))
	    return notify_fail("��û��ˮư����ô��ˮ��\n");
	if (! arg || (arg != "shui" && arg != "water"))
	    return notify_fail("��Ҫ��ʲô��\n");
	if (me->is_busy()) 
	    return notify_fail("����æ������������\n");
	if (! ob->query("filled")) 
	    return notify_fail("ư��ûˮ��\n");

// ��������ڻ�����ˮ�ĺ��
	if (environment(me) != room)
	{
	    message_vision("$N������İ�ˮ���ڵ��ϡ�\n", me);
	    ob->delete("filled");
	    me->start_busy(1 + random(2));
	    me->receive_damage("jing", (20 + random(5)));
	    return 1;
	}

// û�в������ӵĺ�������ֵı�Ƿ����������ˡ�
	if (! me->query("yaowang/seeded"))
	{
	    message_vision("$N��ˮư���ˮ�����˴��ڵĻ����\n", me);   
	    ob->delete("filled");
	    me->start_busy(1 + random(2));
	    me->receive_damage("jing", (20 + random(5)));
	    tell_object(me, "��ͻȻ����û�а����������£�������ưˮ�׽��ˡ�\n");
	    return 1;
	}

	water_time = me->query("yaowang/seeded");
// ����water_timeΪ�ϴθɻ��ʱ�䣬�ɻ�����ǲ��ֺͽ�ˮ��
// ����waterΪ�ܽ�ˮ�Ĵ��������ڿ����ܵ���ֲʱ��ͽ׶�������
// ÿ�ν�ˮ��Ҫ���5-10���ӣ�waterΪ30�Σ����ܵ���ֲʱ��Ϊ��ʵ�е�3-5Сʱ��
	if (! me->query("yaowang/water"))
	{
// ��һ�ν�����ֻ���Ե����г���������Ϊ�Ӳ��ֵ���������ҿ�����Ҫ����Щ����������Ӧ��ʱ�䡣
	    message_vision("$NС������ذѻ���ŵ���ǰ��\n", me);   
//	    ob->delete("filled");
//	    me->start_busy(1+random(2));
//	    me->receive_damage("jing", (20 + random(5)));
//	    me->set("yaowang/water", 1);
//	    me->set("yaowang/seeded", curent_time);
//	    return 1;
	}

	if (me->query("yaowang/water") && water_time + 5 > curent_time) // ����һ�κ�5���Ӳſ����ٽ���
	{
	    me->start_busy(2 + random(3));
	    return notify_fail("���ǲŸչ�ȹ�ô����ôһֱ����ѻ������ģ�\n");
	}
	if (me->query("yaowang/water") && water_time + 10 < curent_time)// 10�����ڲ���ˮ��ֲʧ�ܡ�
	{
	    tell_object(me, "��⣬�ܾ�û�����ĺ��Ľ�ˮ����ֲʧ�ܡ�:(\n");
	    me->delete("yaowang/water");
	    me->delete("yaowang/seeded");
	    me->add("yaowang/fail", 1);
	    return 1;
	}

	message_vision("$N" + use_phrase[random(sizeof(use_phrase))] + use_name[random(sizeof(use_name))] +
			      use_what[random(sizeof(use_what))] + use_arj[random(sizeof(use_arj))] +
			      use_action[random(sizeof(use_action))] + use_where[random(sizeof(use_where))] +
			      action_arj[random(sizeof(action_arj))] + "��\n", me);
	ob->delete("filled");
	me->add("yaowang/water", 1);
	totaltime = me->query("yaowang/water");
	me->start_busy(3 + random(3));
	me->receive_damage("jing", (60 + random(60)));
	me->set("yaowang/seeded", curent_time);

// ��ʮ�ν�����ÿ�ζ��Ի��ĸ����ǲ�һ���ġ�
	switch (me->query("yaowang/water"))
	{
		case 1:
			msg = "�տ�ʼ��������о�����Щ���ʸУ�Ҳ�������ۡ�";
			break;
		case 2:
			msg = "��ĬĬ�����ţ�ϣ�������ܿ�Щ��ѿ��";
			break;
		case 3:
			me->receive_damage("qi", 100);
			msg = "���ӻ�û�з�ѿ����ȵ���Щ�ļ��ˡ�";
			break;
		case 4:
			me->receive_damage("qi", 10);
			msg = "���磡�������ڷ�ѿ�ˣ�����˵�����������";
			break;
		case 5:
		case 6:
			msg = "���������ѿ��һ��㳤�ߣ������������ϲ�á�";
			break;
		case 7:
		case 8:
		case 9:
			me->receive_damage("qi", 50);
			msg = "���ĺ��ĵľ�Ҳ��һ�ڽ������������Ѿ���" + totaltime + "���ˡ�";
			break;
		case 11:
		case 12:
			me->receive_damage("qi", 30);
			msg = "���ĺ���������Щ����Ҷ��ɫ���������������������������";
			break;
		case 13:
			msg = "���ĺ���Ҷ������Բ�εģ�������ɫ���й���";
			break;
		case 14:
			me->receive_damage("qi", 20);
			msg = "���ĺ��ĵ�Ҷ��Ҷ��ϸ����������������������Ҷ��";
			break;
		case 15:
			msg = "��ͻȻ��������������˺���Ҷ�Ӿͻ��죬�ܹ������ֻ��ɵ��̡�������Ȥ��";
			break;
		case 17:
			me->receive_damage("qi", 30);
			msg = "ѽ�����ĺ��Ŀ���ȥ��Ҫ�����ˡ�";
			break;
		case 19:
			me->receive_damage("qi", 20);
			msg = "ֻ�������ĺ��ĺ�ɫ�Ļ��ٺ������ţ�����������";
			break;
		case 20:
		case 21:
			msg = "���ĺ��Ļ����𽥿��ţ���ɫҲ������ɷۺ�ɫ��";
			break;
		case 23:
		case 28:
			me->receive_damage("qi", 30);
			msg = "ϸ�����ĺ��Ļ���ֻ������ɫ�������ˣ�����һ����Ȼ���ֵ����ϡ�";
			break;
		case 24:
		case 25:
			msg = "���ĺ��Ļ���Ա���ȣ����ɫ�Ļ����ջ�һ����С�����硣";
			break;
		case 27:
			msg = "�⺣���������ţ�����\"�ɺ����̼����ɣ���������ѣ���ա�\"";
			break;
		case 29:
			me->receive_damage("qi", 50);
			msg = "�����ʣ������ʣ������ĺ졣˭���뵽�����Ķ�����ĺ��Ļ��Ǿ�����Ʒҩ�ġ�";
			break;
		case 30:
			me->receive_damage("qi", 60);
			msg = "����ȥ���ĺ����Ѿ���ֲ�ɹ����Ͽ�������(get)������ҩ��ɡ�";
			break;
		default:
			msg = "Ϊ���ܰ����ĺ�����ֲ�ɹ����Ͳ����½����������ࡣ";
			break;
	}

	msg += "\n";
	tell_object(me, HIY + msg + NOR + "\n");
	if (totaltime > 30)// ���������������²�����֣��Ӵ�CODE�Ƿ�����δȻ�����������ѭ����
	{
	    tell_object(me, "��⣬������Ĳ���ʧ�����ĺ�����ֲʧ�ܡ�:(\n");
	    me->delete("yaowang/water");
	    me->delete("yaowang/seeded");
	    me->add("yaowang/fail", 1);
	    return 1;
	}
	if (totaltime == 30) // ����30�κ���ֲ�ɹ���
	{
	    me->delete("yaowang/water");
	    me->delete("yaowang/seeded");
	    obnew = new("/clone/herb/haitang");
	    obnew->move(room);
	    me->add("yaowang/qxhtget", 1);
	    me->set("yaowang/qxht/have", 1);
	}
	return 1;
}

string long_desc()
{
	string descrp;
	object ob;
	ob = this_object();

// ��������Ҩˮ��ˮͰ��Long������
	descrp = HIY "����һ�����Ƶ�ˮͰ��" NOR;
	if (ob->query("water_level") == 0)
	    descrp += HIC "Ͱ����һ��ˮ��û�С�"NOR"\n";
	else if (ob->query("water_level") <= 1)
		descrp += HIC "������һ���ˮ��"NOR"\n";
	else if (ob->query("water_level") <= 3)
		descrp += HIC "�����а�Ͱˮ��"NOR"\n";
	else if (ob->query("water_level") <= 4)
		descrp += HIC "�����ˮ�����ˡ�"NOR"\n";
	else
	    descrp += HIC "����װ����ˮ��"NOR"\n";
	return descrp;
}
