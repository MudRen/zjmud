// baiyunwan.c �����ܵ���

inherit ITEM;

void create()
{
	set_name("�����ܵ���", ({"baiyunxiudan wan", "wan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��������ʿ�������������ʥҩ��\n");
		set("value", 50000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	me->receive_curing("qi", 800);
	me->receive_curing("jing", 400);
	message_vision("$N����һ�Ű����ܵ��裬ֻ��������������ɫ��á�\n", me);
	destruct(this_object());
	return 1;
}
