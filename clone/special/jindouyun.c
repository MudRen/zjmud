// sunfenger.c

#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name("���", ({ "jindou yun" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "���������ħ�����ߣ�����˲�����(fly)��������ߡ�\n");
		set("no_sell", "����ʲô������\n");
		set("base_value", 1);
		set("base_weight", 10);
		set("base_unit", "Ƭ");
	}
	set_amount(1);
	setup();
}

void init()
{
	add_action("do_flyto", "flyto");
}

int do_flyto(string arg)
{
	object me;
	object who;
	object env;

	if (! query_amount())
		return 0;

	if (! arg)
		return notify_fail("����ɵ�˭����ߣ�\n");

	who = find_player(arg);
	if (! objectp(who)) who = find_living(arg);
	if (! objectp(who))
		return notify_fail("û������˰���\n");

	if (! objectp(env = environment(who)))
		return notify_fail("����˲�֪��������Ү��\n");

	me = this_player();
	if (env == environment(me))
		return notify_fail("����ԭ���ұ��յ�ɶ��\n");

	if (me->is_busy())
		return notify_fail("����æ������˵��\n");

	if (me->query("doing"))
		return notify_fail("����ƻ�������˵��\n");

	message_vision(HIM "$N" HIM "˺��һƬ��ƣ�����ȥ��"
		       "�ȵ�����̫���Ͼ�����������������\n"
		       "ֻ����������һ�£�$N" HIM "�����ˣ�"NOR"\n",
		       me);
	message("vision", HIM "����һ���Ʋʻ���Ʈ�£�" + me->name() + HIM
			      "����������������"NOR"\n", env);
	tell_object(me, HIM "�Ʋʷ�ѽ��..."NOR"\n");
	me->move(env);

	add_amount(-1);
	return 1;
}

string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}
