// Object: /d/xiangyang/obj/shuitong.c  ҩ��ׯˮͰ
// Date: Feb. 3 2002 by Pound

#include <ansi.h>

inherit ITEM;
string long_desc();

void create()
{
	int water_level;
	set_name("ˮͰ", ({"shui tong", "tong", "bucket"}));
	set_weight(1000);
	if (clonep())
	    set_default_object(__FILE__);
	else 
	{
	    set("water_level", 3);
	    set("long", (: long_desc :));
	    set("unit", "��");
	    set("material", "wood");
	    set("value", 5000);
	    set("no_sell", 1);
	    set("no_get", 1);
	    set("yaowang", 1);
	}
}

string long_desc()
{
	string descrp;
	object ob;
	ob = this_object();
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

int init()
{
	add_action("do_tiao", "carry");
	add_action("do_tiao", "tiao");
	add_action("do_fang", "putdown");
	add_action("do_fang", "fang");
}

int do_tiao(string arg)
{
	object me, ob;
	me = this_player();
	ob = present("shui tong", environment(me));

	if (! arg || (arg != "shui tong" && arg != "tong" && arg != "bucket"))
	    return notify_fail("��Ҫ��ʲô��\n");
	if (! ob)
	    return notify_fail("���︽��û������������\n");
	if (me->is_busy())
	    return notify_fail("����æ���أ�\n");
	if (! wizardp(me) && me->query("family/family_name") != "�������")
	    return notify_fail("ҩ�����˼����ˮͰ��������Ϊ�á�\n");

	message_vision(HIR "$N" HIR "���۵��������˫����������ˮͰ����������"NOR"\n", me);
	me->receive_damage("jing", 33 + random(5));
	ob->move(me);
	me->start_busy(1 + random(2));
	return 1;
}

int do_fang(string arg)
{
	object me, ob;
	me = this_player();
	ob = present("shui tong", me);

	if (! arg || (arg != "shui tong" && arg != "tong" && arg != "bucket"))   
	    return notify_fail("��Ҫ����ʲô��\n");
	if (! ob)
	    return notify_fail("�㲢û�������κζ�����\n");
	if (me->is_busy())
	    return notify_fail("����æ����! \n");

	message_vision(HIB "$N" HIB "��ˮͰ��������˵��ϡ�"NOR"\n", me);
	me->receive_damage("qi", (20 + random(10)));
	ob->move(environment(me));
	me->start_busy(1);
	return 1;
}