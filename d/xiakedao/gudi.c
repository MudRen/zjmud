// gudi.c �ȵ�

#include <ansi.h>

inherit ROOM;

int do_climb(string arg);
int do_swim(string arg);
int do_mai(string arg);

void create()
{
	set("short", "�ȵ�");
	set("long", @LONG
��������¹ȵ��ˣ������Ǹ��ʵ�ɽ�壬һ���Ǵ󺣣�����û��
���ڣ��ȵ׵������ܴ��������ţ�������ԼԼ����ǰ����ϥ����һ
λ����(Oldman)��
LONG );
	set("outdoors", "xiakedao");
	set("item_desc",([
		"��ɽ�塿" : "��ʲôѽ? ��ô�ߵ�ɽ����������ȥ�ġ�\n"
		ZJOBACTS2"�ʵ�:climb shan\n",
		"�����ߡ�" : "����ϸһ������λ�����Ѿ���ȥ�ܶ����ˣ����µ�ֻ�������Ź�(gu)���ÿ���ѽ!\n"
		ZJOBACTS2"����:mai gu\n",
		"���󺣡�" : "��ʲôѽ? ���ѵ�����Ӿ��? \n"
		ZJOBACTS2"��Ӿ:swim sea\n",
	]));
	set("no_clean_up", 0);
	setup();
}
void init()
{
	add_action("do_climb","climb");
	add_action("do_mai","mai");
	add_action("do_swim","swim");

}

int do_mai(string arg)
{
	int n;
	object me;

	if (! arg || arg != "gu")
	{
		write("ʲô��\n");
		return 1;
	}

	me = this_player();
	n = me->query("neili");

	message_vision("$N����һ�������ĵ��棬��������������\n", me);
	if (n > 100)
	{
		message_vision("��Լ���˰��ʱ����$N���������İ����ߵ�"
			       "�ŹǷ��˽�ȥ������������ͻȻ�������"
			       "��һ��ʯ�š�\n", me);
		set("exits/east",__DIR__"midao6");
		me->add("neili", -100);
		remove_call_out("close");
		call_out("close", 5, me);
	} else
	{
		message_vision("$N���������㣬���˼��¾͸ɲ����ˡ�\n", me);
		me->set("neili",0);
	}

	return 1;
}

void close(object room)
{
	message("vision", "ʯ���Զ��ĺ����ˡ�\n", room);
	room->delete("exits/east");
}

int do_swim(string arg)
{
	object me;

	me = this_player();

	if (arg != "sea")
	{
		write("�����ʲôѽ���ڵ�����Ӿ��\n");
		return 1;
	}

	message_vision("$N������һ�����������������������������\n", me);
	if (random(30) > 23)
	{
		message_vision("���ϵķ���̫��$N����ʧȥ��֪����\n", me);
		me->receive_damage("qi", 50);
		me->receive_wound("qi", 50);
		me->move(__DIR__"haitan");
		tell_object(me, HIR "�����������������ʹ�������˼����ˡ�"NOR"\n");
		message("vision", HIR "ֻ��" + me->query("name") +
				  "�����˳嵽��̲�ϡ�"NOR"\n", environment(me), me);
	} else
	{
		message_vision("���ϵķ���̫��$N���ò����˻�����\n", me);
		me->receive_damage("qi", 10);
		me->receive_wound("qi", 10);
	}

	return 1;
}

int do_climb(string arg)
{
	int n;
	object me;

	if (arg !="shan")
	{
		write("��Ҫ��ʲôѽ? \n");
		return 1;
	}

	me = this_player();
	n = me->query_skill("dodge", 1);

	message_vision("$N������һ��������������������\n", me);
	if (n > 50)
	{
		message_vision("$N���˰��죬ͻȻ������һ�����ڣ�$N"
			       "����һ�����˽�ȥ��\n", me);
		me->move(__DIR__"midao8");
	} else
	{
		message_vision("$N����һ�ᣬ̫���ˣ���С�Ļ���������\n", me);
		this_player()->receive_damage("qi", 10);
		this_player()->receive_wound("qi", 10);
	}
	return 1;
}