// lianzi.c ������

inherit ITEM;

void create()
{
	set_name("������", ({"bailian zi", "zi"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�Ž������İ����ӡ�\n");
		set("value", 2000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (me->query("potential") >= me->query_potential_limit())
		return notify_fail("�����ڲ���Ҫ�ð����ӡ�\n");

	me->add("potential", 1);
	message_vision("$N����һ�Ű����ӣ�����һ��������ˬ��\n", me);
	destruct(this_object());
	return 1;
}
