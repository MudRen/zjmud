// more work needed to use this object to make poison

inherit ITEM;

void create()
{
	set_name("���ߵ�", ({"qing dan", "qing"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һֻ��ӨӨ�����ߵ���\n");
		set("value", 100);
		set("only_do_effect", 1);
	}

	setup();
}

int do_effect(object me)
{
	message_vision("$Nһ��ͷ��������$n��\n", me, this_object());
	me->set_temp("die_reason", "����һö�ߵ����ж�����");
	me->die();
	destruct(this_object());
	return 1;
}
