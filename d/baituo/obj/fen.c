//fen.c

inherit ITEM;

void create()
{
	set_name("�ߵ���", ({ "fen"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "�������˵ġ��ߵ��ۡ���\n");
		set("value", 2000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (me->query("eff_qi") >=  me->query("max_qi") - 20)
		return notify_fail("�����ڲ���Ҫ�ý�ҩ��\n");

	if (random(2) == 0)
	{
		message_vision("$N����һ���ߵ��ۣ��������������ۣ������ϵ�����\n", me);
		destruct(this_object());
		return 1;
	}

	me->add("qi", 30);
	me->add("eff_qi", 20);
	message_vision("$N����һ���ߵ��ۣ��پ�������ӿ���������Щ��\n", me);
	destruct(this_object());
	return 1;
}
