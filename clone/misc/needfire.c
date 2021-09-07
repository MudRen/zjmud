// needfire.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIR "����" NOR, ({ "needfire", "gou huo", "huo" }) );
	set_weight(100);
	if (clonep())
	{
		set_default_object(__FILE__);
		call_out("light", 30 + random(20));
	} else
	{
		set("unit", "��");
		set("long", "����һ������ȼ�յ����𣬿���ȥ���������濾������(kao)��\n");
		set("no_get", "��Ҳ���������֣�\n");
		set("no_fire", "������ȼ�հ�����������ǲ��������⣿\n");
	}
	setup();
}

void init()
{
	add_action("do_kao", "kao");
}

void set_light_time(int n)
{
	remove_call_out("light");
	call_out("light", n + random(n / 2));
}

void light()
{
	call_out("destroy", 10 + random(10));
	if (environment())
		message("vision", HIR "���𽥽�����������ȥ����"
			"����ҪϨ���ˡ�"NOR"\n", environment());
	set("long", "����һ������ȼ�յ����𣬻�ⰵ��������ȥ��ҪϨ���ˡ�\n");
}

void destroy()
{
	if (environment())
		message("visoin", RED "������������������˼��£�"
			"������Ϩ���ˣ�ֻ������һ��ҽ���"NOR"\n",
			environment());
	destruct(this_object());
}

int do_kao(string arg)
{
	object ob;
	object me;

	if (! arg)
		return notify_fail("����ʲô�����أ�\n");

	me = this_player();
	if (! objectp(ob = present(arg, me)))
		return notify_fail("�����Ϻ���û������������\n");

	return ob->broil(me, this_object());
}

int move(mixed dest, int raw)
{
	int res;

	if (objectp(dest) && dest->is_character())
		return 0;

	if (environment())
		environment()->add_temp("warm", -20);

	res = ::move(dest, raw);

	if (environment())
		environment()->add_temp("warm", 20);

	return res;
}

void remove(string euid)
{
	::remove(euid);
	if (environment())
		environment()->add_temp("warm", -20);
}
