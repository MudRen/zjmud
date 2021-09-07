// Room: /d/xiangyang/maoshe.c  é��
// Date: Feb . 2 2002 by Pound

#include "room.h"

inherit ROOM;

int do_find(string);
int do_fang(string);

void create()
{
	set("short", "é��");
	set("long", @LONG
����һ��é�ᣬ����ľ��ľ�ʣ��ݽ��и����ճ��þߵ�ľ�ܣ������
Ѱ��ũ�����죬ֻ���˳���Ⱦ���ɾ��ù��˷ݣ�������ǽ��֮�£���ڷ�
�У�Ҳ��ϴ��û���°�������������������������ľ���ĳ����Ǵ���
�ģ�����ո�����������Ѱ�ң�find����ʲô�����������ݣ���һ��Сľ
�ţ�door�����š�
LONG);
	set("item_desc", ([
	    "door" : "����һ��ľ�š�\n",
	]));    

	set("exits", ([
	    "north" : __DIR__"liwu",
	    "west"  : __DIR__"huapu",
	    "south" : __DIR__"huafang",
	]));
	create_door("north", "ľ��", "south", DOOR_CLOSED);
	set("no_sleep_room", 1);
	setup();
}

// ���ĺ����˼������֮����Ժ͹�Ч�޴���Ӧ�Ӵ������Ѷȡ�
// ������Ƹ÷���Ϊno_refresh���Ӷ�ʹÿ��������ֻ��9�����ӿ����ṩ�������ֲ��
void reset()
{
	::reset();
	set("no_clean_up", 1);
}

void init()
{
	add_action("do_find", "find");
	add_action("do_fang", "fang");
}

int do_find(string arg)
{
	mapping log; 
	object ob, me, room;
	me = this_player();
	room = find_object("/d/xiangyang/maoshe.c");

	if (me->is_busy())
	    return notify_fail("����æ���ء�\n");
	if (! arg || (arg != "zhongzi" && arg != "shuipiao"))
	    return notify_fail("������ʲô������\n");

	if (me->query("family/family_name") != "�������" ||  
	    me->query_skill("yaowang-miaoshu", 1) < 200)
	    return notify_fail("����ҩ�����������㵣�������ж������������˻�����\n");

	if (arg == "zhongzi" && me->query_skill("yaowang-miaoshu", 1) < 200)
	    return notify_fail("��������ڷ��źܶ����ӣ�����ȴ������ʶ����֪���Ӻ�����\n");

	if (ob = present(arg, me))
	    return notify_fail("���������ϲ�����������������ỹ���ã�\n");

	if (arg == "zhongzi")
	{
	    log = room->query_temp("zhongzi");
	    if (mapp(log) && log[me->query("id")])
		return notify_fail("��ղŲ�����ȡ�������������ỹ���ã�\n");
	    if (query("zhongzi_count") >= 9)
		return notify_fail("�����˰��죬ʼ���Ҳ�����Ҫ�����ӡ�\n");
	    room->set_temp("zhongzi/" + me->query("id"), 1);
	    ob = new(__DIR__"obj/" + arg);
	    tell_object(me, "�����ҷ����������ҵ�������Ҫ��" + ob->name() + "��\n");
	    ob->move(me);
	    add("zhongzi_count", 1);
	    me->start_busy(2 + random(2));
	    return 1;
	}

	if (arg == "shuipiao")
	{
	    log = room->query_temp("shuipiao");
	    if (mapp(log) && log[me->query("id")])
		return notify_fail("��ղŲ��Ǹ�����һ��ˮưô�������������ˣ�\n");
	    if (query("piao_count") >= 15)
		return notify_fail("�����˰��죬ʼ���Ҳ���ˮư��\n");
	    room->set_temp("shuipiao/" + me->query("id"), 1);
	    ob = new(__DIR__"obj/" + arg);
	    tell_object(me, "����ݽ�ľ�����ҵ���һ��" + ob->name() + "��\n");
	    ob->move(me);
	    add("piao_count", 1);
	    me->start_busy(2 + random(2));
	    return 1;
	}
	return 0;
}

int do_fang(string arg)
{
	object ob, me, room;
	me = this_player();
	room = find_object("/d/xiangyang/maoshe.c");

	if (me->query("family/family_name") != "�������" || ! arg || ! ob = present(arg, me))
	    return 0;
	if (arg == "zhongzi")
	{
	    tell_object(me, "������ĺ���" + ob->query("name") + "�ַŻص������\n");
	    destruct(ob);
	    room->delete_temp("zhongzi/" + me->query("id"));
	    add("zhongzi_count", -1);
	    tell_object(me, "��Ը���������ܹ��л�������ĺ�����ֲ�ɹ���\n");
	    return 1;
	}
	if (arg == "shuipiao")
	{
	    tell_object(me, "���" + ob->query("name") + "�Żص�ľ���ϡ�\n");
	    destruct(ob);
	    room->delete_temp("shuipiao/" + me->query("id"));
	    add("piao_count", -1);
	    return 1;
	}
	return 0;
}

int valid_leave(object me, string dir)
{
	object *inv;
	int i;
	inv = all_inventory(me);

	if (dir == "south") 
	{
	    for (i = 0; i < sizeof(inv); i++)
	    {
		if (inv[i]->is_character())
		    return notify_fail("�����Ȱѿ��ŵĶ��������ٽ�ȥ��\n");
	    }
	}

	if (! wizardp(me) && me->query("family/family_name") != "�������" && dir == "south")
	    return notify_fail("����ҩ����������������һ�������˻�����\n");

	return ::valid_leave(me, dir);
}
