// menshen.c

#include <ansi.h>
#include <room.h>

inherit ITEM;

void setup() {}

void create()
{
	set_name(HIM "����" NOR, ({ "men shen", "menshen" }));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ�Ż���������ɫ�����񣬳���"
			    "����������������������а��\n");
		set("unit", "��");
	}

	set("no_get", 1);
	setup();
}

void init()
{
	object env;
	object me;
	object ob;

	if (! objectp(env = environment()))
		return;

	if (! clonep(env) || base_name(env) != CHAT_ROOM)
		return;

	if (! stringp(env->query("owner_id")) ||
	    ! stringp(env->query("startroom")))
		return;

	me = this_player();
	if (! interactive(me) || env->welcome(me))
		return;

	if (objectp(ob = present("magic gourd", me)) &&
	    ob->query_temp("onwer_id") == me->query_temp("id"))
	{
		message_vision("������һ�������η�������Ҳ"
			       "�����ˣ���˵������ͭ��һ��...\n"
			       "$N�Ͻ�����" + ob->name() + "��ȡ�����ӣ�"
			       "ֻ��һ��������������������˺�«��\n"
			       "���˰��Σ�һ�����̴Ӻ�«����������...\n", me);
		destruct(this_object());
		return;
	}

	message_vision("������һ�������η�������Ҳ"
		       "�����ˣ���˵������ͭ��һ����"
		       "��$Nһ����÷��˳�ȥ��\n", me);
	me->move(env->query("startroom"));
	me->start_busy(3);
	message("vision", "ֻ�����һ����" + me->name() +
		"���˳�����������һ�����һ����ġ�\n",
		environment(me), ({ me }));
}
