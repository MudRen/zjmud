// shedangao.c

inherit ITEM;

void create()
{
	set_name("�ߵ���", ({"shedan gao", "gao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "�������Ʒ���ߵ��ࡻ��\n");
		set("value", 1000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (me->query("max_jingli") < me->query_jingli_limit())
		message_vision( "$N����һ���ߵ��࣬�پ�һ�ɺƵ�����ֱӿ��������������...\n" , me);
	else
		return notify_fail("������ߵ�������Ч�á�\n");

	me->add("max_jingli", 2);
	if (me->query("max_jingli") > me->query_jingli_limit())
		me->set("max_jingli", me->query_jingli_limit());

	destruct(this_object());
	return 1;
}
