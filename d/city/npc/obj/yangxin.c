// yangxin.c ������

inherit ITEM;

void create()
{
	set_name("������", ({"yangxin wan", "wan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�Ű��췢���������衣\n");
		set("value", 10000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	me->add("qi", 200);
	message_vision("$N����һ�������裬ֻ������������ԴԴ�������������ơ�\n", me);
	destruct(this_object());
	return 1;
}
